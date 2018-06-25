#include "Box.hpp"
#include <cmath>

using namespace std;

//constructors
Box::Box() :
    Shape("default",Color{0.0f,0.0f,0.0f}),
	minimum_({0.0,0.0,0.0}),
	maximum_({0.0,0.0,0.0})
    {};

Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
    Shape("default",Color{0.0f,0.0f,0.0f}),
	minimum_{min},
	maximum_{max}
    {};

//Task 5.3
Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Color const& color) : 
    Shape(name,color),
	minimum_{min},
	maximum_{max}
    {};

//destructors
//Task 5.8
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
    /* double lenght = maximum_.x - minimum_.x;
    double width = maximum_.y - minimum_.y;
    double height = maximum_.z - minimum_.z; */

    //return length*width*height;
    return (maximum_.x - minimum_.x)*(maximum_.y - minimum_.y)*(maximum_.z - minimum_.z);
};

//Task 5.5
std::ostream& Box::print(std::ostream& os) const {
	Shape::print(os);
	os << "Minimum: " << "x: " << minimum_.x << " y: " << minimum_.y << " z: " << minimum_.z << endl;
	os << "Maximum: " << "x: " << maximum_.x << " y: " << maximum_.y << " z: " << maximum_.z << endl;
	return os;
};

//getter
glm::vec3 Box::getMinimum() const {
    return minimum_;
};

glm::vec3 Box::getMaximum() const {
    return maximum_;
};
