import random
import gevent

def command_greeting(arg):
    return random.choice([
        "Greetings.",
        "Hello.",
        "Well Met."
    ])

COMMANDS = {
    "hello":command_greeting,
    "hi":command_greeting,
    "hey max":command_greeting,
    "aloha":command_greeting,
}

def sendResponse(txt):
    def respond():
        response = str(txt)
        for client in CLIENTS[:]:
            client.put(response)
    gevent.spawn(respond)

def parse_command(command):
    if command in COMMANDS:
        sendResponse("[true," + DISPATCH[command](command) + "]")
    else:
        sendResponse("[false]")
