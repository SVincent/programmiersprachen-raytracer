#ifndef SHAPE
#define SHAPE

class Shape {
public:
    //constructors
    Shape();

    //functions
    virtual double area() const = 0;
	virtual double volume() const = 0;
};

#endif