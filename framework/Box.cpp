#include "Box.hpp"
#include <cmath>
#include <glm/gtx/intersect.hpp>

using namespace std;

//constructors
Box::Box() :
    Shape("default", make_shared<Material>(Material())),
	minimum_({0.0,0.0,0.0}),
	maximum_({0.0,0.0,0.0})
    {};

Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
    Shape("default", make_shared<Material>(Material())),
	minimum_{min},
	maximum_{max}
    {};

Box::Box(glm::vec3 const& min, glm::vec3 const& max, string name, shared_ptr<Material> material) : 
    Shape(name, material),
	minimum_{min},
	maximum_{max}
    {};

//destructors
Box::~Box() {
    cout << "destructor class Box\n";
};

//functions
double Box::area()  {
    double lenght = maximum_.x - minimum_.x;
    double width = maximum_.y - minimum_.y;
    double height = maximum_.z - minimum_.z;

    return 2*(lenght*height+lenght*width+height*width);
};

double Box::volume()  {
    /* functionally equivalent to the following
    double lenght = maximum_.x - minimum_.x;
    double width = maximum_.y - minimum_.y;
    double height = maximum_.z - minimum_.z; 
    return length*width*height; */

    return (maximum_.x - minimum_.x)*(maximum_.y - minimum_.y)*(maximum_.z - minimum_.z);
};

std::ostream& Box::print(std::ostream& os) const {
	Shape::print(os);
	os << "Minimum: " << "x: " << minimum_.x << " y: " << minimum_.y << " z: " << minimum_.z << endl;
	os << "Maximum: " << "x: " << maximum_.x << " y: " << maximum_.y << " z: " << maximum_.z << endl;
	return os;
};

bool Box::intersect(Ray const& ray, float& t) {
    //calculate intersections with lines parallel to X, Y and Z axis which contain minimum_ and maximum_
    float tx_min = (minimum_.x - ray.origin.x) / ray.direction.x;
    float tx_max = (maximum_.x - ray.origin.x) / ray.direction.x;
    float ty_min = (minimum_.y - ray.origin.y) / ray.direction.y;
    float ty_max = (maximum_.y - ray.origin.y) / ray.direction.y;
    float tz_min = (minimum_.z - ray.origin.z) / ray.direction.z;
    float tz_max = (maximum_.z - ray.origin.z) / ray.direction.z;
    //select the two points which possibly intersect with XY-plane of the box
    float t_min = (tx_min > ty_min) ? tx_min : ty_min;
    float t_max = (tx_max < ty_max) ? tx_max : ty_max;
    //check whether ray even intersects the XY-ground-plane the box is made up of 
    //if not, checking the z component is unnecessary
    if (tx_min > ty_max || ty_min > tx_max) {
        return false;
    }
    //check whether possible intersection points are above or below the box
    if (t_min > tz_max || tz_min > t_max) {
        return false;
    }
    //check which intersection point is the nearest and which one the farthest away
    if (tz_min > t_min) {
        t_min = tz_min; 
    }
    if (tz_max < t_max) {
        t_max = tz_max;
    }

    t = t_min; //distance to the nearest intersection-point
    //todo: store t_min and t_max in Hit-struct

    return true;
};

Hit intersect(Ray const& ray){
    Hit hitFalse;
    return hitFalse;
}

//getter
glm::vec3 Box::getMinimum() const {
    return minimum_;
};

glm::vec3 Box::getMaximum() const {
    return maximum_;
};
