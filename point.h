#ifndef GROUPPROJECT_POINT_H
#define GROUPPROJECT_POINT_H

#include "SDL_Plotter.h"

class point {
public:
    point();
    point(int x_coordinate, int y_coordinate);
    point(const point& p);
    virtual ~point();

    void setY(int y);
    void setX(int x);

    int getX();
    int getY();

    point& operator=(const point& rhs);

    void display(ostream&);
    void draw(SDL_Plotter& g);

private:
    int x, y;
};

/*
 * description: Point object destructor
 * return: nothing
 * precondition: point object exists
 * postcondition: Point object memory is released
 *
*/

point::~point(){
}

/*
 * description: Point object constructor
 * return: nothing
 * precondition: nothing
 * postcondition: Point object is created
 *
*/

point::point()
{
    this-> x = 0;
    this-> y = 0;
}

/*
 * description: Point object constructor w/ parameters
 * return: point object
 * precondition: nothing
 * postcondition: point object is created w/ the given parameters
 *
*/
point::point(int x_coordinate, int y_coordinate)
{
    this-> x = x_coordinate;
    this-> y = y_coordinate;
}

/*
 * description: Point object copy constructor
 * return: point object
 * precondition: a point object exists
 * postcondition: Point object is created and is identical to the first point
 *
*/
point::point(const point& p)
{
    this-> x = p.x;
    this-> y = p.y;
}

/*
 * description: Sets the y value
 * return: nothing
 * precondition: point object exists
 * postcondition: Y value of the point is set
 *
*/

void point::setY(int y_coordinate)
{
    this-> y = y_coordinate;
}

/*
 * description: Sets the x value
 * return: nothing
 * precondition: point object exists
 * postcondition: X value of the point is set
 *
*/

void point::setX(int x_coordinate)
{
    this-> x = x_coordinate;
}

/*
 * description: Gets the x value
 * return: int
 * precondition: point object exists
 * postcondition: returns the x value of the point
 *
*/

int point::getX()
{
    return this-> x;
}

/*
 * description: Gets the y value
 * return: int
 * precondition: point object exists
 * postcondition: returns the y value of the point
 *
*/

int point::getY()
{
    return this-> y;
}

/*
 * description: Overloaded assignment operator
 * return: point&
 * precondition: 2 point objects exist
 * postcondition: first point object is the same as second point object
 *
*/

point& point::operator=(const point& rhs)
{
    if (this != &rhs)
    {
        this-> x = rhs.x;
        this-> y = rhs.y;
    }

    return *this;
}

/*
 * description: Displays information about the plot
 * return: nothing
 * precondition: point object exists
 * postcondition: point information is outputted to ostream
 *
*/

void point::display(ostream& out)
{
    out << "(" << this-> x << ", " << this-> y << ")";
}

/*
 * description: Draws the point on the plotter
 * return: nothing
 * precondition: plotter and point objects exist
 * postcondition: Pixel is plotted on plotter
 *
*/

void point::draw(SDL_Plotter& g)
{
    int R = rand()%256;
    int G = rand()%256;
    int B = rand()%256;

    g.plotPixel(x, y, R, G, B);
}
#endif //GROUPPROJECT_POINT_H
