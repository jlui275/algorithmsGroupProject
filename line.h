#include <algorithm>
#include "point.h"

#ifndef GROUPPROJECT_LINE_H
#define GROUPPROJECT_LINE_H

class line {
public:
    line();
    line(point point1, point point2);
    virtual ~line();

    void display(ostream&  out);
    void draw(SDL_Plotter& g);

    void setP1(point p);
    void setP2(point p);

    point getP1(){return p1;}
    point getP2(){return p2;}

private:
    point p1, p2;
    bool slope(double& m);
    bool intercept(double& b);

};

/*
 * description: Line Destructor
 * return: nothing
 * precondition: line object exists
 * postcondition: line object memory is released
 *
*/

line::~line(){
}


/*
 * description: Line Constructor
 * return: line object
 * precondition: nothing
 * postcondition: line object is created
 *
*/

line::line()
{
    p1 = point(0,0);
    p2 = point(1,1);
}

/*
 * description: Line constructor w/ parameters
 * return: line object
 * precondition: nothing
 * postcondition: Line object is created w/ the given parameters
 *
*/

line::line(point point1, point point2)
{
    this-> p1 = point1;
    this-> p2 = point2;
}

/*
 * description: Displays information about the line
 * return: void
 * precondition: line object exists
 * postcondition: Displays line information out of ostream
 *
*/

void line::display(ostream& out)
{
    out << "p1: (" << this-> p1.getX() - 50 << ", " << 450 - this-> p1.getY() << ")\n";
    out << "p2: (" << this-> p2.getX() - 50<< ", " << 450 - this-> p2.getY() << ")\n";
}

/*
 * description: Draws the line of the plotter
 * return: void
 * precondition: line object exists
 * postcondition: Line is plotted on the SDL Plotter object
 *
*/

void line::draw(SDL_Plotter& g)
{
    double m, b;
    bool slopeExists = true;
    slopeExists = this-> slope(m);
    this-> intercept(b);

    int R = rand()%256;
    int G = rand()%256;
    int B = rand()%256;

    if(slopeExists)
    {
        int difference = abs(this-> p2.getX() - this-> p1.getX());
        for(int i = 0; i < difference; i++)
        {
            int yCoordinate = m*(p1.getX() + i) + b;
            g.plotPixel((this-> p1.getX() + i), yCoordinate,
                        R, G, B);
        }
    }
    else //vertical lines
    {
        int difference = abs(this-> p2.getY() - this-> p1.getY());
        int minimum = min(p1.getY(), p2.getY());

        for(int i = 0; i < difference; i++)
        {
            g.plotPixel(this-> p1.getX(), (minimum + i),
                        R, G, B);
        }
    }
}

/*
 * description: Sets the p1 value
 * return: void
 * precondition: line object exists
 * postcondition: point 1 of the line object is set
 *
*/

void line::setP1(point p)
{
    this-> p1 = p;
}

/*
 * description: Sets the p2 value
 * return: void
 * precondition: line object exists
 * postcondition: point 2 of the line object is set
 *
*/

void line::setP2(point p)
{
    this-> p2 = p;
}

/*
 * description: Finds the slope if there is one
 * return: bool
 * precondition: line object exists
 * postcondition: returns true or false if line has a slope
 *                puts the slope in variable m
*/

bool line::slope(double& m)
{
    if(p2.getX() != p1.getX())
    {
        double yDifference = p2.getY() - p1.getY();
        double xDifference = p2.getX() - p1.getX();
        m = yDifference/xDifference;
        return true;
    }
    return false;
}

/*
 * description: Finds the y-intercept if there is one
 * return: bool
 * precondition: line object exists
 * postcondition: returns true or false if line has a y-intercept
 *                puts the y-intercept in variable b
*/

bool line::intercept(double& b)
{
    double slope;
    if(p2.getX() != p1.getX())
    {
        this-> slope(slope);
        b = p1.getY() - (slope * p1.getX());
        return true;
    }
    return false;
}


#endif //GROUPPROJECT_LINE_H
