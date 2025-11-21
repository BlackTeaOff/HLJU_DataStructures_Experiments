import os
import ctypes
import json
from flask import Flask, jsonify

# --- Basic Setup ---
app = Flask(__name__)

# --- DLL Loading and Function Definition ---

# Construct the absolute path to the DLL file
# This makes sure the script can find the DLL regardless of where it's run from
dll_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'HLJU_Guide.dll')

try:
    # Load the DLL
    guide_lib = ctypes.CDLL(dll_path)
except OSError as e:
    print(f"Error loading DLL: {e}")
    print(f"Please make sure 'HLJU_Guide.dll' is in the same directory as this script: {os.path.dirname(os.path.abspath(__file__))}")
    exit()


# Define the argument types and return types for the C functions
# This is crucial for ctypes to work correctly.

# void initialize()
guide_lib.initialize.argtypes = []
guide_lib.initialize.restype = None

# const char* query_from_gate(int dest)
guide_lib.query_from_gate.argtypes = [ctypes.c_int]
guide_lib.query_from_gate.restype = ctypes.c_char_p # The return is a pointer to a char (a C string)

# const char* query_from_place(int start, int dest)
guide_lib.query_from_place.argtypes = [ctypes.c_int, ctypes.c_int]
guide_lib.query_from_place.restype = ctypes.c_char_p

# --- Initialization ---
# Call the C initialize function once when the application starts
guide_lib.initialize()
print("C library initialized.")


# --- API Routes ---

@app.route('/')
def index():
    return "Welcome to the Campus Guide API (powered by C DLL)!"

@app.route('/path/from_gate/to/<int:dest_id>')
def get_path_from_gate(dest_id):
    """
    Calls the C function to get the shortest path from the main gate.
    """
    if not (0 <= dest_id < 10):
        return jsonify({"error": "Invalid destination ID"}), 400

    # Call the C function
    result_ptr = guide_lib.query_from_gate(dest_id)
    
    # The result is a bytes string (e.g., b'{"path": ...}'), decode it to a normal string
    json_string = result_ptr.decode('utf-8')
    
    # Parse the JSON string into a Python dictionary
    data = json.loads(json_string)
    
    return jsonify(data)


@app.route('/path/from/<int:start_id>/to/<int:end_id>')
def get_path_between_places(start_id, end_id):
    """
    Calls the C function to get the shortest path between two places.
    """
    if not (0 <= start_id < 10 and 0 <= end_id < 10):
        return jsonify({"error": "Invalid start or destination ID"}), 400

    # Call the C function
    result_ptr = guide_lib.query_from_place(start_id, end_id)
    
    # Decode and parse the JSON result
    json_string = result_ptr.decode('utf-8')
    data = json.loads(json_string)
    
    return jsonify(data)

if __name__ == '__main__':
    # Make sure to install Flask: pip install Flask
    app.run(debug=True, port=5000)
