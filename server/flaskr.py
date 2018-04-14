import os
from flask import Flask, request, session, g, redirect, url_for, abort, \
        render_template, flash, jsonify

app = Flask(__name__)
app.config.from_object(__name__)

app.config.update(dict(
    DATABASE=os.path.join(app.root_path, 'flaskr.db'),
    SECRET_KEY='development key',
    USERNAME='admin',
    PASSWORD='default'
    ))
app.config.from_envvar('FLASKR_SETTINGS', silent=True)

gps_x = 0
gps_y = 0

class Gps():
    def __init__(self):
        self.x = 0
        self.y = 0
    def update(self, x, y):
        self.x = x
        self.y = y

gps = Gps()

@app.route('/gps', methods =['GET','POST'])
def show_entries():
    global gps
    if request.method == 'POST':
        if 'x' in request.args and 'y' in request.args:
            gps.update(request.args.get('x'),request.args.get('y'))
            lst = [
                    {'x' : gps.x,
                        'y' : gps.y}
                    ]
            return jsonify(results=lst)
        else:
            return 'send like https://167.1.2.3:8080/gps?x=10&y=20'
    elif request.method == 'GET':
        if 'x' in request.args and 'y' in request.args:
            gps.update(request.args.get('x'),request.args.get('y'))
            lst = [
                    {'x' : gps.x,
                        'y' : gps.y}
                    ]
            return jsonify(results=lst)
        else:
            lst = [
                    {'x' : gps.x,
                        'y' : gps.y}
                    ]

            return jsonify(results=lst)
    else:
        return 'send like https://gomjellie.iptime.org:7777/gps?x=20&y=30'


if __name__ == '__main__':
    app.run(host='0.0.0.0',debug=True, port=8888)

