from flask import Flask, request
app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload():
    # print(request.headers)
    print(request.data)

    # if data:
    #     with open('esp.jpg', 'wb') as pic:
    #         pic.write(request.data)
    #     return "OK"
    # else:
    #     return 400, "EROR"
    return 'ok', 200

app.run(host='0.0.0.0', port=5000)
