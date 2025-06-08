import json
import os

DATA_FILE = os.path.join(os.path.dirname(__file__), '..', 'sms_data.json')

def load_data():
    if not os.path.exists(DATA_FILE):
        # Start with empty data if file doesn't exist
        return {
            'instructors': {},
            'students': {},
            'courses': {},
            'enrollments': {},
            'grades': {}
        }
    try:
        with open(DATA_FILE, 'r', encoding='utf-8') as f:
            return json.load(f)
    except (json.JSONDecodeError, ValueError):
        # File exists but is empty or corrupted
        return {
            'instructors': {},
            'students': {},
            'courses': {},
            'enrollments': {},
            'grades': {}
        }

def save_data(data):
    with open(DATA_FILE, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=4)
