import random
import gevent

def command_greeting(arg):
	return random.choice(["Greetings.", "Hello.", "Well Met."])

def command_brightness_down(arg):
	print("Turning brightness down")
	return random.choice(["Adjusting lights"])

def command_brightness_up(arg):
	return random.choice(["Adjusting lights"])

DISPATCH = [
    (frozenset(["hello", "hi", "hey max", "aloha", "max"]), command_greeting),
    (frozenset(["brightness down", "lights down", "too bright"]), command_brightness_down),
    (frozenset(["brightness up", "lights up", "too dark"]), command_brightness_up)
]

def sendResponse(txt):
    def respond():
        response = str(txt)
        for client in CLIENTS[:]:
            client.put(response)
    gevent.spawn(respond)

def parse_command(command):
    for switch in DISPATCH:
        if command in switch[0]:
            sendResponse(switch[1](command))
            break
