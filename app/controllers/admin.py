from functools import wraps
from app import app, redirect, url_for, current_user, login_required

def admin_only(f):
    @wraps(f)
    def wrapped(*args, **kwargs):
        if current_user.admin != True:
            return redirect(url_for("unauthorized"))
        return f(*args, **kwargs)
    return wrapped

@app.route("/testadmin")
@login_required
@admin_only
def testadmin():
    return "AREA 51 SHIT"
