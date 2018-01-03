import time
from threading import Thread
from app import request, redirect, corpus_ps, render_template, app, Response, push_event, SemaQueue, login_required, g
from app.parse import parse_command
from flask_login import current_user

# An actually working SSE implementation.

@app.route("/", methods=["POST", "GET"])
@login_required
def index():
    if request.method == "POST":
        if request.data is None:
            return redirect(request.url)
        elif request.headers.get("Content-Type") == "audio/raw":
            corpus = corpus_ps.process(request.data)
            push_event("\"" + corpus + "\"")
            Thread(target=parse_command, args=(corpus, {
                "ip": request.remote_addr,
                "yes": "no",
                "username": current_user.username,
                "data": request.data,
                "email": current_user.email
            }, push_event)).start()
            return "OK"
        return redirect("/")
    return render_template("index.html")

@app.route("/response")
@login_required
def events():
    def gen(username):
        q = SemaQueue(username)
        while True:
            if q.acquire(1):
                entry = q.pop()
                q.ts = int(time.time())
                yield "data: {}\n\n".format(entry)
            q.ts = int(time.time())
            yield ""
    return Response(gen(g.user.username), mimetype="text/event-stream")
