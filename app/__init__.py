from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from .pocketsphinx import PocketSphinx

app = Flask(__name__, static_url_path='/static')
app.config.from_object("config")
db = SQLAlchemy(app)

pocketsphinx = PocketSphinx("wrapper/sphinx-wrapper.dylib", "wrapper/model", None, False)
request_ps = pocketsphinx.initialize()

from app import views, models
