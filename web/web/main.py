import requests
import pathlib
import logging
from flask import render_template

_LOGGER = logging.getLogger(__name__)

current_dir = pathlib.Path(__file__).parent
static_dir = current_dir.joinpath("static")
static_dir.mkdir(exist_ok=True)
os_dir = static_dir.joinpath("os")
os_dir.mkdir(exist_ok=True)

def download_v86():
    URL_BASE = "https://github.com/copy/v86/releases/download/latest/"

    FILES = [
        static_dir.joinpath("libv86.js"),
        static_dir.joinpath("v86.wasm")
    ]


    for required_file in FILES:
        

        if not required_file.exists():
            _LOGGER.info(f"{required_file} does not exists. Downloading...")
            resp = requests.get(f"{URL_BASE}{required_file.name}")
            with required_file.open("wb+") as f:
                f.write(resp.content)
            _LOGGER.info(f"{required_file} download was successful.")
        else:
            _LOGGER.info(f"{required_file} exists. Skipping download")



if __name__ == "__main__":
    download_v86()

    from flask import Flask

    app = Flask(
        __name__,
        static_url_path='', 
        static_folder=current_dir.joinpath("static"),
    )

    @app.route('/')
    @app.route('/index')
    def index():
        os_list = [str(x.name) for x in list(os_dir.glob("*.img")) + list(os_dir.glob("*.bin"))]
        return render_template('index.html', os_list=os_list)

    app.run(debug=True)