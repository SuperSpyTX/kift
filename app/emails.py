from flask_mail import Message, Mail
from app import app
mail = Mail(app)

def send_email(to, subject, template):
    msg = Message(
            subject,
            recipients=[to],
            html=template,
            sender="camagru@gmx.com"
            )
    mail.send(msg)
