#ifndef SHAPE
#define SHAPE

class Shape {
public:
    //constructors
    Shape();

    //functions
    virtual float area() const = 0;
	virtual float volume() const = 0;
};

#endif