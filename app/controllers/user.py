from werkzeug.security import generate_password_hash, check_password_hash
from app import app, db, models, forms, render_template, redirect, request, url_for, login_manager, flash, g
from flask_login import login_required, login_user, current_user, logout_user

@login_manager.user_loader
def load_user(id):
    return models.User.query.get(int(id))

@app.before_request
def before_request():
    g.user = current_user

@app.route("/register", methods=["POST", "GET"])
def register():
    form = forms.RegisterForm()
    if current_user.is_authenticated:
        flash("logged in")
        return redirect(url_for("index"))

    if request.method == "GET":
        return render_template("register.html", form=form)

    if form.validate_on_submit():
        username = request.form["username"]
        password = request.form["password"]
        email = request.form["email"]
        phone = request.form["phone"]
        test_unique = models.User.query.filter_by(username=username).first()
        if test_unique is not None:
            flash("username already exits, try again")
            return render_template("register.html", form=form)
        hashed_pw = generate_password_hash(password)
        new_user = models.User()
        new_user.password_hash = hashed_pw
        new_user.email = email
        new_user.username = username
        new_user.phone = phone
        db.session.add(new_user)
        db.session.commit()
        return redirect(url_for("login"))
    else:
        flash("Double check your fields")

    return redirect(url_for("register"))

@app.route("/login", methods=["POST", "GET"])
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
                print(reg_user)
                login_user(reg_user)
                flash("login successful")
                return redirect(url_for("index"))
            flash("wrong password")
            return redirect(url_for("login"))
        else:
            return render_template("login.html", form=form)
    else:
        return render_template("login.html", form=form)

@app.route("/logout")
@login_required
def logout():
    logout_user()
    return redirect(url_for("index"))
