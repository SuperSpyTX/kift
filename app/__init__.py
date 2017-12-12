from flask import Flask
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__, static_url_path='/static')
app.config.from_object("config")
db = SQLAlchemy(app)


from .pocketsphinx import PocketSphinx
pocketsphinx = PocketSphinx("wrapper/sphinx-wrapper.dylib", b"wrapper/model")
if pocketsphinx.init() is None:
    print("Failed to load pocketsphinx!")

from app import views, models
