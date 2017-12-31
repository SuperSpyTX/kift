import time
from threading import Semaphore
from werkzeug.serving import WSGIRequestHandler

CLIENTS = []
class SemaQueue():
    def __init__(self):
        self.queue = []
        self.acquiring = False
        self.ts = int(time.time())
        self.lock = Semaphore(0)
        CLIENTS.append(self)

    def __del__(self):
        try:
            CLIENTS.remove(self)
        except:
            pass

    def acquire(self, timeout=None):
        self.acquiring = True
        res = self.lock.acquire(True, timeout)
        self.acquiring = False
        return res

    def pop(self):
        return self.queue.pop(0)

    def haslife(self):
        if (int(time.time()) - self.ts) > 1:
            return False
        return True

    def push(self, entry, check=True):
        if check is True:
            if not self.haslife():
                return False
        self.queue.append(entry)
        self.lock.release()
        return True

def push_event(text):
    toremove = []
    for client in CLIENTS:
        if not client.push(text):
            toremove.append(client)
    for rem in toremove:
        try:
            CLIENTS.remove(rem)
        except:
            pass

def heartbeat():
    toremove = []
    for client in CLIENTS:
        if not client.haslife():
            toremove.append(client)
    for rem in toremove:
        try:
            CLIENTS.remove(rem)
        except:
            pass

# Monkey patch connection_dropped in Werkzeug
# to be able to properly clean up WebSocket connections.

# TODO: Determine if we can do heartbeat check in:
# - Old Request Thread (here)
# - Spawn a new Thread
# pylint: disable=W0613
def connection_dropped(self, error, environ=None):
    heartbeat()

WSGIRequestHandler.connection_dropped = connection_dropped
