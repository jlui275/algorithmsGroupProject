/*
* Author: Xiang Gao
* Assignment Title: curve
* Assignment Description: This class represent a line
* Due Date: 1/28/2019
* Date Created: 1/22/2019
* Date Last Modified: 1/22/2019
    -Create color_rgb class
 */
#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED
#include "point.h"
#include <vector>
class line {
public:
	line();
	line(point p1, point p2);
	virtual ~line();

	void display(ostream&  out);
	void draw(SDL_Plotter& g);

	void setP1(point p);
	void setP2(point p);
	void setColor(color_rgb c){color = c;}

	point getP1(){return p1;}
	point getP2(){return p2;}
	color_rgb getColor(){return color;}

	void nextColor();
	void resetColor();

private:
	point p1, p2;
	color_rgb color;
	bool slope(double& m);
	bool intercept(double& b);
	int currentColor;

};
line::line(){
    currentColor = 0;
    color.setR(0);
    color.setG(255);
    color.setB(255);
}
line::line(point p1,point p2){
    this->p1 = p1;
    this->p2 = p2;
}
line::~line(){
}
void line::setP1(point p){
    p1 = p;
}
void line::setP2(point p){
    p2 = p;
}
bool line::slope(double &m){
    if (p1.getX()== p2.getX()){
        return false;
    }
    else{
        double p1Y =  p1.getY();
        double p1X = p1.getX();
        double p2X = p2.getX();
        double p2Y = p2.getY();
        m = ( p2Y - p1Y )/(p2X- p1X);
        return true;
    }
}
bool line::intercept(double& b){
    if (p1.getX()==p2.getX()){
        return false;
    }
    else{
        double s;
        slope(s);
        b = p1.getY() - s*p1.getX();
    }
    return true;
}
    void line::draw(SDL_Plotter& g){
        vector<point> drawpoint;
                //get the small x,y value between x and y;
               int bigX;
        bigX = max(p1.
                getX(), p2.getX());
        int smallX = min(p1.getX(),p2.getX());
        int bigY = max(p1.getY(),p2.getY());
        int smallY = min(p1.getY(),p2.getY());
        // get slope and yintercept of the line
        double m;
        double b;
        bool slopeExist = true;
        slopeExist = this->slope(m);
        this->intercept(b);
        //draw point if slope do  exist
        point temp(smallX,smallY);
        temp.setColor(color);
        if (slopeExist){
            // draw point by point between 2 point
            for (int i = smallX; i <= bigX;i++ ){
                temp.setX(i);
                temp.setY(m*i+b);
                temp.setColor(color);
                drawpoint.push_back(temp);
               // temp.draw(g);
            }

        }
        else{
            for (int i = smallY; i <= bigY;i++ ){
                temp.setX(smallX);
                temp.setY(i);
                temp.draw(g);
            }
        }
        //if two point are too close draw vertical or
      if (abs(bigX - smallX) == 1){
            for (int i = smallY; i <= bigY;i++ ){
                temp.setX(bigX);
                temp.setY(i);
                temp.draw(g);
            }
        }
        if (abs(bigY - smallY) ==1){
             temp.setY(bigY);
            for (int i = smallX; i <= bigX;i++ ){
                temp.setY(bigY);
                temp.setX(i);
                temp.draw(g);
            }
        }
        if (drawpoint.size() > 0){
            for(int i = 0; i < (drawpoint.size()-1) ;i++){
                bigX = max(drawpoint[i].
                        getX(), drawpoint[i+1].getX());
                smallX = min(drawpoint[i].getX(),drawpoint[i+1].getX());
                bigY = max(drawpoint[i].getY(),drawpoint[i+1].getY());
                smallY = min(drawpoint[i].getY(),drawpoint[i+1].getY());
                if (bigX - smallX == 1){
                    for (int j = smallY; j <= bigY;j++ ){
                        temp.setX(bigX);
                        temp.setY(j);
                        temp.draw(g);
                    }
                }else if (bigY - smallY ==1){
                    temp.setY(bigY);
                    for (int i = smallX; i <= bigX;i++ ){
                        temp.setY(bigY);
                        temp.setX(i);
                        temp.setColor(color);
                        temp.draw(g);
                    }
                }
                else{
                    drawpoint[i].draw(g);
                }
        }

       }



}
void line::nextColor(){
    currentColor++;
    if (currentColor == 1){
        color.setR(255);
        color.setG(0);
        color.setB(0);
        p1.setColor(color);
        p2.setColor(color);
    }
    else if (currentColor == 2){
        color.setR(0);
        color.setG(255);
        color.setB(0);
         p1.setColor(color);
         p2.setColor(color);
    }
    else if (currentColor == 3){
        color.setR(0);
        color.setG(0);
        color.setB(255);
         p1.setColor(color);
         p2.setColor(color);
    }else if (currentColor == 4){
        color.setR(255);
        color.setG(255);
        color.setB(0);
         p1.setColor(color);
         p2.setColor(color);
    }
}
void line::resetColor(){
    currentColor = 0;
    color.setR(0);
    color.setG(255);
    color.setB(255);
     p1.setColor(color);
         p2.setColor(color);
}
void line::display(ostream& out){
    out << "P1 is (" << p1.getX() << " , ";
    out << p1.getY() << ")" << endl;
    out << "P2 is (" << p2.getX() << " , ";
    out << p2.getY() << ")" << endl;
    out << "color : (" << this->color.getR() << " , ";
    out << this->color.getG() << " , ";
    out << this->color.getB() << " )" << endl;
    out << "currentColor" << this->currentColor << endl;
}

#endif // LINE_H_INCLUDED
