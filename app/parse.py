from app import app
import math
import os
import random
import requests
import socket
import subprocess
import webbrowser
from app import natural_ps, corpus_ps, app
from app.emails import send_email

def applescript(script):
    osa = subprocess.Popen(["osascript", "-"],
                           stdin=subprocess.PIPE,
                           stdout=subprocess.PIPE)
    return osa.communicate(bytes(script, "UTF-8"))

def command_lights_on(args=None):
    applescript("""
    tell application "System Events"
        repeat 16 times
            key code 144
        end repeat
    end tell
    """)
    return random.choice([
        "Turning the lights on.",
        "Going bright."
    ])

def command_lights_off(args=None):
    applescript("""
    tell application "System Events"
        repeat 16 times
            key code 145
        end repeat
    end tell
    """)
    return random.choice([
        "Turning the lights off.",
        "Going dark."
    ])

def command_search(arg):
    words = natural_ps.process(arg["data"])
    if words is None:
        return "I could not understand you"
    term = ""
    words = words.split()[len(arg["command_match"].split(" ")):]
    for word in words:
        term += word + " "
    term = term[:-1]
    webbrowser.open("http://lmgtfy.com/?q=" + term)
    return "I am now searching for '" + term + "'"

def command_note(arg):
    words = natural_ps.process(arg["data"])
    if words is None:
        return "I could not understand you"
    note = ""
    words = words.split()[len(arg["command_match"].split(" ")):]
    for word in words:
        note += word + " "
    note = note[:-1]
    with app.app_context():
        send_email(arg["email"], "Hello From Maxwell",
                   "Hi there,<br><br>Here is your note:<br><br>" + note + "<br><br>Regards,<br><br>Maxwell.")
    return "I've sent it to your email."

def command_personalize(arg):
    match = arg["command_match"]
    if "old" in match or "age" in match:
        return "I seriously have no idea."
    elif "are you" in match:
        return "I am Maxwell, an artificial voice-controlled butler designed by a team of engineers at 42.  How can I help you today?"
    elif "can you" in match:
        return "I am programmed to perform the basic tasks outlined in the PDF, like sending an email, search for something, or set a reminder."
    elif "time to stop" in match:
        return "It's time to stop.  No more.  I am really lazy at implementing this meme, so I have left it to my developers who are also lazy."
    return "I do not understand"

def command_identity(args=None):
    return "You are " + arg["username"] + "."

def command_location(args=None):
    return "You are at " + socket.gethostname() + "."

def command_weather(args):
    if args["ip"] != "127.0.0.1":
        city = requests.get("http://geoip.nekudo.com/api/" + args["ip"]).json()["ip"]
    else:
        city = "Fremont"
    weather = requests.get("http://api.openweathermap.org/data/2.5/weather?q=" + city + "&APPID=" + app.config["OPEN_WEATHER_MAP"] + "&units=metric").json()
    temp = str(round(weather["main"]["temp"], 1))
    speed = str(round(weather["wind"]["speed"], 1))
    cardinals = {0: "East", 1: "South", 2: "West", 3: "North", 4:"East"}
    heading = cardinals[math.floor(weather["wind"]["deg"] / 90 + 0.5)]
    desc = weather["weather"][0]["description"]
    return ("It is %sy, the temperature is %s Celsius there is a %s kilometer per hour wind from the %s." % (desc, temp, speed, heading))

# List may contain any number of sentences to match past the first, last element is the command to execute
DEF = [
    ["lights on", command_lights_on],
    ["lights off", command_lights_off],
    ["save a note with", command_note],
    ["search for", command_search],
    ["how old are you", "who are you", "what can you do", "time to stop", "its time to stop", command_personalize],
    ["who am i", "who am", "i am", command_identity],
    ["weather", "what is the weather", command_weather],
    ["where am i", "what is my location", "where am", "where", command_location]
]

COMMANDS = {}

for rule in DEF:
    for alias in rule[:-1]:
        COMMANDS[alias] = rule[-1]

def search(words):
    LIMIT = 5
    wordspl = words.split(" ")
    wordjoin = ""
    for word in wordspl:
        if LIMIT == 0:
            return None
        LIMIT -= 1
        wordjoin += word + " "
        if wordjoin[:-1] in COMMANDS:
            return [wordjoin[:-1], COMMANDS[wordjoin[:-1]]]
    return None

def parse_command(command, user, client_send):
    cmd = search(command)
    if cmd is not None:
        client_send("[true,\"" + str(cmd[1]({**{
            "command_match": cmd[0],
            "command": command
        }, **user})) + "\"]", user["username"])
    else:
        client_send("[false,\"" + command + "\"]", user["username"])
