/*
* Author: Xiang Gao
* Assignment Title: curve
* Assignment Description: This class represent a point
* Due Date: 1/28/2019
* Date Created: 1/22/2019
* Date Last Modified: 1/22/2019
    -Create color_rgb class
 */
#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include "color_rgb.h"
#include <iostream>
#include "SDL_Plotter.h"
class point {
public:
	point();
	point(int x, int y);
	point(const point& p);
	virtual ~point();
	void setY(int y);
	void setX(int x);
	void setColor(color_rgb c);
	int getX();
	int getY();
	color_rgb getColor();
	point& operator=(const point& rhs);
	void display(ostream&);
	void draw(SDL_Plotter&);

private:
	int x, y;
	color_rgb color;
};
point::point(){
    x = -1;
    y = -1;
}
point::point(int x, int y){
    this->x = x;
    this->y = y;
}
point::point(const point& p){
    this->x = p.x;
    this->y = p.y;
}
point::~point(){

}
void point::setX(int x){
    this-> x = x;
}
void point::setY(int y){
    this -> y = y;
}
int point::getX(){
    return x;
}
int point::getY(){
    return y;
}
color_rgb point::getColor(){
    return this->color;
}
void point::setColor(color_rgb c){
    color = c;
}
point& point::operator=(const point& rhs){
    this->x = rhs.x;
    this->y = rhs.y;
    this->color = rhs.color;

    return *this;
}
void point::draw(SDL_Plotter& g){
    g.plotPixel(x,y,color.getR(),color.getG(),color.getB());
}
void point::display(ostream& out){
    out << "This is a point " << endl;
    out << "x : " << this->x << endl;
    out << "y : " << this->y << endl;
    out << "color : (" << this->color.getR() << " , ";
    out << this->color.getG() << " , ";
    out << this->color.getB() << " )" << endl;
    out << "point Complete" << endl;
}


#endif // POINT_H_INCLUDED
