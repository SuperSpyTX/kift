import random
import subprocess

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

# List may contian any number of aliases, last element must be command to execute
DEF = [
    ["lights on", command_lights_on],
    ["lights off", command_lights_off]
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
