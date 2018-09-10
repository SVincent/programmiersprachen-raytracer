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
  unsigned const image_width = 800;
  unsigned const image_height = 700;
  std::string const filename = "./testScene.ppm";

  sdfReader sdfR;
  Scene newScene;
  newScene = sdfR.readSdf("/home/vincent/Documents/programming/programmiersprachen-raytracer/sceneOne.sdf");
  newScene.ambientLightCol_= Color(0.1,0.1,0.1);
  //newScene.shapes_[0]->translate(glm::vec3{0,1,1});
  //newScene.shapes_[0]->setMaterial(newScene.materials_[0]);

  Renderer renderer{newScene, image_width, image_height, filename};

  //create separate thread to see updates of pixels while rendering
  std::thread render_thread([&renderer]() {renderer.render3();});

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
