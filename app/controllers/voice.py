import time
from threading import Semaphore, Thread
from app import request, redirect, request_ps, render_template, app, Response

@app.route("/", methods=["POST", "GET"])
def voice():
    if request.method == "POST":
        if request.data is None:
            return redirect(request.url)
        elif request.headers.get("Content-Type") == "audio/raw":
            result = request_ps.process(request.data)
            return result
        return redirect("/")
    return render_template("index.html")

# An actually working SSE implementation.

# TODO: Move to separate class or is it ok here?
CLIENTS = []
class SemaQueue():
    def __init__(self):
        self.queue = []
        self.lock = Semaphore(0)

    def acquire(self, timeout=None):
        return self.lock.acquire(True, timeout)

    def pop(self):
        return self.queue.pop(0)

    def push(self, entry):
        self.queue.append(entry)
        self.lock.release()

def push_event(text):
    print("Running like a maniac")
    text += " At: " + str(time.time())
    for client in CLIENTS:
        client.push(text)

@app.route("/push")
def push():
    Thread(target=push_event, args=("fuck yes this works", )).start()
    return "pls isa"

@app.route("/events")
def events():
    def gen():
        q = SemaQueue()
        CLIENTS.append(q)
        while q.acquire(app.config['CLIENT_SSE_TIMEOUT']):
            entry = q.pop()
            yield "data: {}\n\n".format(entry)
        CLIENTS.remove(q)
    return Response(gen(), mimetype="text/event-stream")
