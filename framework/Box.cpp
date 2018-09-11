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

bool Box::intersectBool(Ray const& ray) {
    return false;
}

glm::vec3 Box::getNormalized(const glm::vec3 pi) const{
    return glm::vec3{1,1,1};
}
/*
bool Box::intersectBoolTwo(Ray const& ray, float& t)const {
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


Hit Box::intersect(Ray const& ray) {
     Hit returnHit;
    //calculate intersections with lines parallel to X, Y and Z axis which contain minimum_ and maximum_
    float tx_min = (minimum_.x - ray.origin.x) / ray.direction.x;
    float tx_max = (maximum_.x - ray.origin.x) / ray.direction.x;
    float ty_min = (minimum_.y - ray.origin.y) / ray.direction.y;
    float ty_max = (maximum_.y - ray.origin.y) / ray.direction.y;
    float tz_min = (minimum_.z - ray.origin.z) / ray.direction.z;
    float tz_max = (maximum_.z - ray.origin.z) / ray.direction.z;
    //select the two points which possibly intersect with XY-plane of the box
    
    // check if coordinates correct
    if (tx_min > tx_max){
        std::swap(tx_min, tx_max);
    }
    if (ty_min > ty_max){
        std::swap(ty_min, ty_max);
    }
    if (tz_min > tz_max){
        std::swap(tz_min, tz_max);
    }

    //hit not possible
    if (tx_min > ty_max || ty_min > tx_max) {
        returnHit.hit_=false;
        return returnHit;
    }

    if (ty_min > tx_min){
        tx_min = ty_min;
    }

    if (ty_max < tx_max){
        tx_max = ty_max;
    }

    if ((tx_min > tz_max) || (tz_min > tx_max)){
        returnHit.hit_=false;
        return returnHit;
    }

    if (tz_min > tx_min){
        tx_min = tz_min;
    }

    if (tz_max < tx_max){
        tx_max = tz_max;
    }

    // nearest and farthest intersection point
    float t_min = (tx_min > ty_min) ? tx_min : ty_min;
    if (t_min = tx_min){
        glm::vec3 intersectPoint = glm::vec3(tx_min, minimum_.y,t_min);
        returnHit.intersectionPoint_= intersectPoint;
    }
    else{
        glm::vec3 intersectPoint = glm::vec3(minimum_.x, ty_min, t_min);
        returnHit.intersectionPoint_= intersectPoint;
    }
    float t_max = (tx_max < ty_max) ? tx_max : ty_max;

    if (tz_min > t_min) {
        t_min = tz_min; 
    }
    if (tz_max < t_max) {
        t_max = tz_max;
    }

    float t = t_min;

    returnHit.hit_ = true;
    returnHit.shape_=this;
    //returnHit.intersectionPoint_ = ; //todo: meinen eigenen code verstehen und rausfinden wo der intersectionpoint ist
    returnHit.distance_ = t;


    //todo: store t_min and t_max in Hit-struct

    return returnHit;
};
*/

bool Box::intersectBoolTwo(Ray const& ray, float& t) const {
    //based on this algorithm: http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

    //intersect ray with parallel lines to x (of same x value as the boxes' minimum and maximum) to calculate t
    float t_min = (minimum_.x - ray.origin.x) / ray.direction.x;
    float t_max = (maximum_.x - ray.origin.x) / ray.direction.x;

    if (t_min > t_max) {
        swap(t_min, t_max);
    }

    //intersect ray with parallel lines to y (of same y value as the boxes' minimum and maximum) to calculate t
    float ty_min = (minimum_.y - ray.origin.y) / ray.direction.y;
    float ty_max = (maximum_.y - ray.origin.y) / ray.direction.y;

    if (ty_min > ty_max) {
        swap(ty_min, ty_max);
    } 

    //checks whether the t values actually lay on the xy plane
    if ((t_min > ty_max) || (ty_min > t_max)) {
        return false; 
    }
 
    if (ty_min > t_min) {
        t_min = ty_min; 
    }
 
    if (ty_max < t_max) {
        t_max = ty_max; 
    }

    //intersect ray with parallel lines to z (of same z value as the boxes' minimum and maximum) to calculate t
    float tz_min = (minimum_.z - ray.origin.z) / ray.direction.z;
    float tz_max = (maximum_.z - ray.origin.z) / ray.direction.z;

    if (tz_min > tz_max) {
        swap(tz_min, tz_max); 
    }
 
    //checks whether the t values actually lay on the xz plane
    if ((t_min > tz_max) || (tz_min > t_max)) {
        return false;
    }
 
    if (tz_min > t_min) {
        t_min = tz_min;
    } 
 
    if (tz_max < t_max) {
       t_max = tz_max; 
    }

    return true;
}
/*
Hit Box::intersect(Ray const& ray){
    //based on this algorithm: http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

    Hit returnHit;

    //intersect ray with parallel lines to x (of same x value as the boxes' minimum and maximum) to calculate t
    float t_min = (minimum_.x - ray.origin.x) / ray.direction.x;
    float t_max = (maximum_.x - ray.origin.x) / ray.direction.x;

    if (t_min > t_max) {
        swap(t_min, t_max);
    }

    //intersect ray with parallel lines to y (of same y value as the boxes' minimum and maximum) to calculate t
    float ty_min = (minimum_.y - ray.origin.y) / ray.direction.y;
    float ty_max = (maximum_.y - ray.origin.y) / ray.direction.y;

    if (ty_min > ty_max) {
        swap(ty_min, ty_max);
    } 

    //checks whether the t values actually lay on the xy plane
    if ((t_min > ty_max) || (ty_min > t_max)) {
        returnHit.hit_=false;
        return returnHit;
    }
 
    if (ty_min > t_min) {
        t_min = ty_min; 
    }
 
    if (ty_max < t_max) {
        t_max = ty_max; 
    }

    //intersect ray with parallel lines to z (of same z value as the boxes' minimum and maximum) to calculate t
    float tz_min = (minimum_.z - ray.origin.z) / ray.direction.z;
    float tz_max = (maximum_.z - ray.origin.z) / ray.direction.z;

    if (tz_min > tz_max) {
        swap(tz_min, tz_max); 
    }
 
    //checks whether the t values actually lay on the xz plane
    if ((t_min > tz_max) || (tz_min > t_max)) {
        returnHit.hit_=false;
        return returnHit;
    }
 
    if (tz_min > t_min) {
        t_min = tz_min;
    } 
 
    if (tz_max < t_max) {
        t_max = tz_max; 
    }

    //at this point t_min contains the intersection-point closest to the camera and t_max the one furthest away

    //check whether the point is in front of the camera or behind it
    if (t_max > std::max(0.0, double(t_min))) {
        returnHit.hit_ = true;
        returnHit.distance_ = sqrt(t_min*t_min*(ray.direction.x*ray.direction.x + ray.direction.y*ray.direction.y + ray.direction.z*ray.direction.z));
        returnHit.shape_ = this;
        returnHit.intersectionPoint_ = glm::vec3{t_min*ray.direction.x, t_min*ray.direction.y, t_min*ray.direction.z} + ray.origin;
    }

    return returnHit;
};
*/

  Hit Box::intersect(Ray const& ray) {
    Hit boxhit;
    double t1 = (minimum_.x - ray.origin.x)*ray.direction.x;
    double t2 = (maximum_.x - ray.origin.x)*ray.direction.x;
    double tmin = std::min(t1, t2);
    double tmax = std::max(t1, t2);

    t1 = (minimum_.y - ray.origin.y)*ray.direction.y;
    t2 = (maximum_.y - ray.origin.y)*ray.direction.y;
    tmin = std::max(tmin, std::min(t1, t2));
    tmax = std::min(tmax, std::max(t1, t2));

    t1 = (minimum_.z - ray.origin.z)*ray.direction.z;
    t2 = (maximum_.z - ray.origin.z)*ray.direction.z;
    tmin = std::max(tmin, std::min(t1, t2));
    tmax = std::min(tmax, std::max(t1, t2));

    if (tmax > std::max(0.0, tmin)) //Hit?
    {   
        boxhit.hit_ = true;
        boxhit.distance_ = sqrt(tmin*tmin*(
                                ray.direction.x*ray.direction.x +
                                ray.direction.y*ray.direction.y +
                                ray.direction.z*ray.direction.z));
        
        boxhit.shape_ = this;

        boxhit.intersectionPoint_ =
        glm::vec3{tmin*ray.direction.x, tmin*ray.direction.y, tmin*ray.direction.z}
        +ray.origin;
                
        if ((boxhit.intersectionPoint_.x)==Approx(maximum_.x))
        {
           boxhit.m_normal=glm::vec3(1.0f,0.0f,0.0f); // right 
        }else if ((boxhit.intersectionPoint_.x)==Approx(minimum_.x))
        {
          boxhit.m_normal=glm::vec3(-1.0f,0.0f,0.0f); //left
        }else if ((boxhit.intersectionPoint_.y)==Approx(maximum_.y))
        {
          boxhit.m_normal=glm::vec3(0.0f,1.0f,0.0f); //fup
        }else if ((boxhit.intersectionPoint_.y)==Approx(minimum_.y))
        {
          boxhit.m_normal=glm::vec3(0.0f,-1.0f,0.0f); //down
        }else if ((boxhit.intersectionPoint_.z)==Approx(maximum_.z))
        {
          boxhit.m_normal=glm::vec3(0.0f,0.0f,1.0f); //front
        }else
        {
          boxhit.m_normal=glm::vec3(0.0f,0.0f,-1.0f); //back
        }   
    }
    return boxhit;
  }
//getter
glm::vec3 Box::getMinimum() const {
    return minimum_;
};

glm::vec3 Box::getMaximum() const {
    return maximum_;
};
