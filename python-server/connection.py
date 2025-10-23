from flask import Flask, request
app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload():
    print(request.headers)
    data = request.data
    if data:
        with open('esp.jpg', 'wb') as pic:
            pic.write(data)
        return 'ok', 200
    else:
        return 'error', 400


app.run(host='0.0.0.0', port=5000)
