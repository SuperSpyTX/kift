import random

def command_greeting(arg=None):
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

def parse_command(command, client_send):
    if command in COMMANDS:
        client_send("[true,\"" + COMMANDS[command](command) + "\"]")
    else:
        client_send("[false]")
