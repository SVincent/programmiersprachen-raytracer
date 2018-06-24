#ifndef SHAPE
#define SHAPE

class Shape {
public:
    //constructors
    Shape() {};

    //functions
    virtual double area() = 0;
	virtual double volume() = 0;
};

#endif