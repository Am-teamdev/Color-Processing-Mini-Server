from flask import Flask, request, url_for
import os
import select_color
import threading

app = Flask(__name__)

UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)


@app.route('/upload', methods=['POST'])
def upload_image():
    img_data = request.data

    if not img_data:
        return "No data has been received.", 400

    file_path = os.path.join(UPLOAD_FOLDER, 'esp32_image.jpg')

    with open(file_path, 'wb') as f:
        f.write(img_data)
    try:
        infor_img = select_color.detect_card_color(file_path)
        threed = threading.Thread(target=select_color.process_and_show,
                                  args=(infor_img[0], infor_img[1], infor_img[2]), daemon=True)
        threed.start()
        if infor_img[0] is None:
            return 'No color found.', 422
        else:
            return infor_img[0], 200


    except Exception as e:
        return e, 500


if __name__ == '__main__':
    try:
        host = input('Server host: (Default: localhost) ')
        host = '0.0.0.0' if host == '' else host
        port = input('Server port: (Default: 8080) ')
        port = 8080 if not bool(port) else int(port)
    except ValueError:
        host = 'localhost'
        port = 8080
    try:
        threading.Thread(target=select_color.show_loop, daemon=True).start()
        app.run(host=host, port=port)
    except KeyboardInterrupt:
        print('Server stopped by user.')