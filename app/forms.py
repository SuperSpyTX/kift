from flask_wtf import Form
from wtforms import StringField, IntegerField
from wtforms.validators import DataRequired, Email

class RegisterForm(Form):
    username = StringField('username', validators=[DataRequired()])
    password = StringField('password', validators=[DataRequired()])

class LoginForm(Form):
    username = StringField('username', validators=[DataRequired()])
    password = StringField('password', validators=[DataRequired()])
