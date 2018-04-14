import requests
import time

#these functions are just sample
def do_this():
    print('do this')

def do_that():
    print('do that')

def do_it():
    print('do it')

while True:
    time.sleep(1)
    url = 'http://gomjellie.iptime.org:7777/gps'
    r = requests.get(url)

    gps_dict = r.json().get('results')[0]
    
    x = int(gps_dict.get('x'))
    y = int(gps_dict.get('y'))

    if 10 < x < 20 and 20 < y < 40:
        do_this()
    elif 20 < x < 40 and 40 < y <70:
        do_that()
    else:
        do_it()