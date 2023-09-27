#!/usr/bin/env python3

import cgi
import os
import http.cookies
import pickle
import random
import string

# Get the directory where the script is located
script_directory = os.path.dirname(os.path.abspath(__file__))

# Set the working directory to the script's directory
os.chdir(script_directory)

# Function to generate a random cookie
def generate_random_cookie():
    cookie_characters = string.ascii_letters + string.digits
    return ''.join(random.choice(cookie_characters) for _ in range(16))

# Function to load the session dictionary from a file
def load_session():
    try:
        with open('./session.pickle', 'rb') as f:
            return pickle.load(f)
    except FileNotFoundError:
        return {}

# Function to save the session dictionary to a file
def save_session(session_dict):
    with open('./session.pickle', 'wb') as f:
        pickle.dump(session_dict, f)

# Create a CGIFieldStorage instance to parse the POST data
form = cgi.FieldStorage()

# Get the "loggedIn" cookie from the client
cookie = http.cookies.SimpleCookie()

# Check if the "HTTP_COOKIE" header is present in the request
if "HTTP_COOKIE" in os.environ:
    cookie.load(os.environ["HTTP_COOKIE"])

# Load the session dictionary from the file
session_dict = load_session()

# Get the value of the "loggedIn" cookie (assuming that's the name of the cookie)
logged_in_status = cookie.get("loggedIn")

# Set the response content type to plain text
print("Content-type: text/plain\r")

if logged_in_status is not None:
    # The user has a valid cookie, check if it exists in the session dictionary
    username = session_dict.get(logged_in_status.value, "null")
    print("\r")
    print(username, end="")
else:
    # Generate a random cookie
    new_cookie = generate_random_cookie()
    
    # Set the "loggedIn" cookie in the response header
    print(f"Set-Cookie: loggedIn={new_cookie}\r")
    
    # Add the new cookie to the session dictionary with a null value
    session_dict[new_cookie] = "null"
    
    # Save the updated session dictionary to the file
    save_session(session_dict)
    
    # Return "null" as the response
    print("\r")
    print("null", end="")
