import os
from flask import Flask, render_template, flash, redirect, url_for, request, Response
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager, login_required, login_user, current_user, logout_user
from .pocketsphinx import PocketSphinx
from .sockets import SemaQueue, CLIENTS, push_event

app = Flask(__name__, static_url_path='/static')
app.config.from_object("config")
db = SQLAlchemy(app)

# TODO: Rename global to be more accurate (action word)
# TODO: Make a static function that does this garbage in pocketsphinx class.
pocketsphinx = PocketSphinx(app.config['POCKETSPHINX_LIBPATH'], app.config['POCKETSPHINX_MODELDIR'],
                            app.config['POCKETSPHINX_CORPUSDIR'] + "/corpus.lm.bin",
                            app.config['POCKETSPHINX_CORPUSDIR'] + "/corpus.dic")
request_ps = pocketsphinx.initialize()

uploads = os.path.dirname(os.path.abspath(__file__)) + "/static/"
login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = "unauthorized"
db.create_all()

# pylint: disable=C0411,C0413
from app import models

# pylint: disable=C0411,C0413,W0401
from .controllers import *
