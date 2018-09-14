#include <renderer.hpp>
#include <window.hpp>
#include "sdfreader.hpp"
#include "scene.hpp"
#include "shape.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  std::string const filename = "./testScene.ppm";

  sdfReader sdfR;
  Scene newScene;
  newScene = sdfR.readSdf("sceneOne.sdf");

  unsigned const image_width = newScene.mainCam_.xres_;
  unsigned const image_height = newScene.mainCam_.yres_;

  Renderer renderer{newScene, image_width, image_height, sdfR.fileOutputName_};
  //create separate thread to see updates of pixels while rendering
  std::thread render_thread([&renderer]() {renderer.render();});

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  render_thread.join();
  return 0;
}
