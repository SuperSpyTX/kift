from threading import Thread
import time
from app import request, redirect, corpus_ps, natural_ps, render_template, app, Response, push_event, SemaQueue
from app.parse import parse_command

# An actually working SSE implementation.

@app.route("/", methods=["POST", "GET"])
def voice():
    if request.method == "POST":
        if request.data is None:
            return redirect(request.url)
        elif request.headers.get("Content-Type") == "audio/raw":
            corpus = corpus_ps.process(request.data)
            natural = natural_ps.process(request.data)
            push_event("\"" + corpus + "\"")
            Thread(target=parse_command, args=(corpus, natural, push_event)).start()
            return "OK"
        return redirect("/")
    return render_template("index.html")

@app.route("/response")
def events():
    def gen():
        q = SemaQueue()
        while True:
            if q.acquire(1):
                entry = q.pop()
                q.ts = int(time.time())
                yield "data: {}\n\n".format(entry)
            q.ts = int(time.time())
            yield ""
    return Response(gen(), mimetype="text/event-stream")
