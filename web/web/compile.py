
import pathlib
import logging
from jinja2 import Environment, PackageLoader, select_autoescape
import jinja2
import shutil

_LOGGER = logging.getLogger(__name__)
current_dir = pathlib.Path(__file__).parent
static_dir = current_dir.joinpath("static")
static_dir.mkdir(exist_ok=True)
template_dir = current_dir.joinpath("templates")
os_dir = static_dir.joinpath("os")
os_dir.mkdir(exist_ok=True)

if __name__ == "__main__":
    os_list = []
    for build_dir in current_dir.parent.parent.glob("build_*"):
        group_name = build_dir.name.replace("build_", "")
        images = list(build_dir.glob("*.img"))

        for image in images:
            new_image_name = f"{group_name}-{image.name}"
            new_kernel_path = os_dir.joinpath(new_image_name)
            shutil.copy(image, new_kernel_path)
            os_list.append(new_kernel_path.name)

 
    templateLoader = jinja2.FileSystemLoader(searchpath=template_dir)
    templateEnv = jinja2.Environment(loader=templateLoader)
    TEMPLATE_FILE = "index.html"
    template = templateEnv.get_template(TEMPLATE_FILE)
    outputText = template.render(os_list=os_list)  # this is where to put args to the template renderer

    print(outputText)

