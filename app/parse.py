from app import app
import requests
import random
import subprocess
import os
import math

def applescript(script):
    osa = subprocess.Popen(["osascript", "-"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE)
    return osa.communicate(bytes(script, "UTF-8"))

def command_lights_on(arg=None):
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

def command_lights_off(arg=None):
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

def command_identity(arg=None):
    return "You are " + os.environ["USER"] + "."

def command_weather(args):
	#city = requests.get("http://geoip.nekudo.com/api/" + ip).json()
    weather = requests.get("http://api.openweathermap.org/data/2.5/weather?q=Fremont&APPID=" + app.config["OPEN_WEATHER_MAP"] + "&units=metric").json()
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
	["who am i", command_identity],
	["weather", "what is the weather", command_weather]
]

COMMANDS = {};

for rule in DEF:
    for alias in rule[:-1]:
        COMMANDS[alias] = rule[-1]

def parse_command(command, client_send):
    if command in COMMANDS:
        client_send("[true,\"" + COMMANDS[command](command) + "\"]")
    else:
        client_send("[false,\"" + command + "\"]")
