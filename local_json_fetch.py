from flask import Flask, jsonify
from faker import Faker
import random
import datetime

app = Flask(__name__)
fake = Faker()

def safe_fake_date(start_year=1971, end_year=2015):
    while True:
        dt = fake.date_time_between(start_date='-80y', end_date='-10y')
        if dt.year >= start_year:
            return dt

@app.route('/generate', methods=['GET'])
def generate_user():
    dob = safe_fake_date()
    reg = fake.date_time_between(start_date='-10y', end_date='now')

    user_data = {
        "cell": fake.phone_number(),
        "dateOfBirth": {
            "date": dob.day,
            "day": dob.weekday(),
            "hours": dob.hour,
            "minutes": dob.minute,
            "month": dob.month - 1,
            "seconds": dob.second,
            "time": int(dob.timestamp() * 1000),
            "timezoneOffset": -60,
            "year": dob.year - 1900
        },
        "email": fake.email(),
        "gender": random.choice(["male", "female"]),
        "location": {
            "city": fake.city().lower(),
            "postCode": fake.postcode(),
            "state": fake.state().lower(),
            "street": fake.street_address()
        },
        "name": {
            "firstName": fake.first_name().lower(),
            "lastName": fake.last_name().lower(),
            "title": fake.prefix()
        },
        "nationality": fake.country_code(),
        "phone": fake.phone_number(),
        "picture": "...",
        "registrationDate": {
            "date": reg.day,
            "day": reg.weekday(),
            "hours": reg.hour,
            "minutes": reg.minute,
            "month": reg.month - 1,
            "seconds": reg.second,
            "time": int(reg.timestamp() * 1000),
            "timezoneOffset": -60,
            "year": reg.year - 1900
        }
    }

    return jsonify(user_data)

if __name__ == '__main__':
    app.run(port=4242)
