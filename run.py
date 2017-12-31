#!/usr/bin/env python3

from app import app

if __name__ == "__main__":
    app.run(debug=False,threaded=True,host="0.0.0.0")

