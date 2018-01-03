from app import app
import socket
import requests
import random
import subprocess
from app import natural_ps, corpus_ps
import os
import math

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

def command_identity(args=None):
    return "You are " + os.environ["USER"] + "."

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
    ["lights on", "lights up", command_lights_on],
    ["lights off", command_lights_off],
	["who am i", "who am", "i am", command_identity],
	["weather", "what is the weather", command_weather],
	["where am i", "what is my location", "where am", "where", command_location]
]

COMMANDS = {}

for rule in DEF:
    for alias in rule[:-1]:
        COMMANDS[alias] = rule[-1]

def parse_command(command, user, client_send):
    if command in COMMANDS:
        client_send("[true,\"" + str(COMMANDS[command]({**{
            "command": command
        }, **user})) + "\"]")
    else:
        client_send("[false,\"" + command + "\"]")
