import os
from functools import wraps
from flask import render_template, flash, redirect, url_for, request
from app import app, db, models, forms
from flask_login import LoginManager, login_required, login_user, current_user, logout_user
from werkzeug.security import generate_password_hash, check_password_hash
from ffmpy import FFmpeg

uploads = os.path.dirname(os.path.abspath(__file__)) + '/static/'
login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = "unauthorized"
db.create_all()

@login_manager.user_loader
def load_user(username):
    try:
        return models.User.query.filter_by(username=username).first()
    except:
        return None

def admin_only(f):
    @wraps(f)
    def wrapped(*args, **kwargs):
        if current_user.admin != True:
            return redirect(url_for("unauthorized"))
        return f(*args, **kwargs)
    return wrapped

def convert_ogg_to_wav(ogg_file):
    input_f = uploads + "audio.ogg"
    output_f = uploads + "audio.wav"
    ff = FFmpeg(inputs={input_f: None},
                outputs={output_f: None})
    ff.run()

@app.route("/upload", methods=["POST", "GET"])
#@login_required
#@admin_only
def upload():
    if request.method == 'POST':
        if request.files is None:
            return redirect(request.url)
        audio = request.files['file']
        if audio.filename == '':
            return redirect(request.url)
        if audio and audio.filename.split('.')[1] == 'ogg':
            audio.save(uploads + "audio.ogg")
            convert_ogg_to_wav(audio)
            return redirect(url_for("index"))
        return redirect('url_for_index')
    return render_template("upload.html")

@app.route('/index')
def index():
    return render_template("index.html")

@app.route('/register', methods=['POST', 'GET'])
def register():
    form = forms.RegisterForm()
    if current_user.is_authenticated:
        flash("logged in")
        return redirect(url_for("index"))

    if request.method == 'GET':
        return render_template("register.html", form=form)

    if form.validate_on_submit():
        username = request.form["username"]
        password = request.form["password"]
        test_unique = models.User.query.filter_by(username=username).first()

        if test_unique is not None:
            flash("username already exits, try again")
            return render_template("register.html", form=form)
        hashed_pw = generate_password_hash(password)
        new_user = models.User()
        new_user.password_hash = hashed_pw
        new_user.username = username
        db.session.add(new_user)
        db.session.commit()
        return redirect(url_for("index"))

    return redirect(url_for("index"))

@app.route('/login', methods=['POST', 'GET'])
def login():
    form = forms.LoginForm()

    if current_user.is_authenticated:
        flash("logged in")
        return redirect(url_for("index"))

    if request.method == "POST":
        if form.validate_on_submit():
            username = request.form["username"]
            password = request.form["password"]
            reg_user = models.User.query.filter_by(username=username).first()
            if reg_user is None:
                flash("Bad username/password combination")
                return render_template("login.html", form=form)
            if check_password_hash(reg_user.password_hash, password):
                login_user(reg_user)
                flash("login successful")
                return redirect(url_for("index"))
            flash("wrong password")
            return redirect(url_for("unauthorized"))
    else:
        return render_template("login.html", form=form)

@app.route("/logout")
@login_required
def logout():
    logout_user()
    return redirect(url_for("index"))

@app.route('/unauthorized')
def unauthorized():
    return "NICE TRY ASSHOLE"

@app.route("/testauth")
@login_required
def testauth():
    return "Acutally did it you moron"

@app.route("/testadmin")
@login_required
@admin_only
def testadmin():
    return "AREA 51 SHIT"
