/*
* Author: Xiang Gao
* Assignment Title: curve
* Assignment Description: This class represent a curve
* Due Date: 1/28/2019
* Date Created: 1/22/2019
* Date Last Modified: 1/22/2019
    -Create color_rgb class
 */
#ifndef CURVE_H_INCLUDED
#define CURVE_H_INCLUDED
#include <vector>
#include "line.h"
typedef vector<pair<int,int>> DataSet_t;
typedef vector<DataSet_t> Data_t;

class curve {
public:
	curve();
	virtual ~curve();
	void display(Data_t data, ostream&);
	void draw(Data_t data, SDL_Plotter&);
	bool getSameScale(){ return sameScale;}
	void setSameScale(bool t){sameScale = t;}

private:
	void plotAxis(int margin, int maxX, int maxY, SDL_Plotter& g);
	void plotTickMarks(int margin, int maxX, int maxY, SDL_Plotter& g);
	bool goodPoints(line a, int margin, SDL_Plotter& g);
	bool sameScale;

};
curve::curve(){
    sameScale = false;
}
curve::~curve(){
}

 void curve::plotAxis(int margin, int maxX, int maxY, SDL_Plotter& g){
    //plot x axis
    for (int i = margin; i < maxX ; i++){
        g.plotPixel(i,maxY,0,0,0);
    }
    for (int i = margin; i < maxY; i++){
        g.plotPixel(margin,i,0,0,0);
    }
    //plot y axis
}
void curve::plotTickMarks(int margin, int maxX, int maxY, SDL_Plotter& g){
    int gapX = (maxX - margin)/10;
    int gapY = (maxY - margin)/10;
    int HalfTickLength = 10;
    //plot x axis tick
    for (int i = margin + gapX; i < maxX + gapX; i+=gapX){
       for (int j = maxY - HalfTickLength;j < maxY + HalfTickLength;j++){
            g.plotPixel(i,j,0,0,0);
       }
    }
    //plot y axis tick
    for (int i = margin; i < (maxY ); i += gapY){
       for (int j = margin-HalfTickLength;j < margin+HalfTickLength;j++){
            g.plotPixel(j,i,0,0,0);
       }
    }
}
void curve::draw(Data_t data, SDL_Plotter& g){
    //graph setting
    int MaxX = 950;
    int MaxY = 450;
    int Margin = 50;
    //scale setting
    //find MaxYv and MaxXv
    long double MaxXv = data[0][0].first;
    long double MaxYv = data[0][0].second;
    for (int i =1;i < data.size();i++){
        long double newValueX = data[i][data[i].size()-1].first;
        long double newValueY = data[i][data[i].size()-1].second;
        if (newValueX > MaxXv){
            MaxXv = newValueX;
        }
        if (newValueY > MaxYv){
            MaxYv = newValueY;
        }
    }
    long double MaxXvdiff = MaxXv;
    long double MaxYvdiff = MaxYv;


    //plor axis
    this->plotAxis(Margin,MaxX,MaxY,g);
    this->plotTickMarks(Margin,MaxX,MaxY,g);
    point p1;
    point p2;
    line Line;
    //darw the line
    //prepare for scale
     long double eachY =  MaxYv/10;
    long double eachPointY = eachY/((MaxY-Margin)/10);
    //scale of X
    double eachX = MaxXv/10;
    double eachPointX = eachX /((MaxX-Margin)/10);
    for (int dataSetIndex = 0; dataSetIndex < data.size();dataSetIndex++){
        if (sameScale == true){
            MaxXv = data[dataSetIndex][data[dataSetIndex].size()-1].first;
            MaxYv = data[dataSetIndex][data[dataSetIndex].size()-1].second;
        }else{
            MaxXv = MaxXvdiff;
            MaxYv = MaxYvdiff;

        }
        //Scale X

            eachX = MaxXv/10;
            eachPointX = eachX /((MaxX-Margin)/10);

        //scale Y
            eachY =  MaxYv/10;
            eachPointY = eachY/((MaxY-Margin)/10);
        for (int i = 0; i < data[dataSetIndex].size()- 1 ;i++){

            long double p1X = (data[dataSetIndex][i].first/eachPointX)+Margin;
            long double p1Y = MaxY-(data[dataSetIndex][i].second/eachPointY);
            long double p2X = (data[dataSetIndex][i+1].first/eachPointX)+Margin;
            long double p2Y = MaxY-(data[dataSetIndex][i+1].second/eachPointY);
            /*if (p1Y == p2Y){
                p2Y = p1Y+1;
            }*/
            p1.setX(p1X);
            p1.setY(p1Y);
            p2.setX(p2X);
            p2.setY(p2Y);
            Line.setP1(p1);
            Line.setP2(p2);
            if (p1.getY() <MaxY && p2.getY() < MaxY && p1.getX() < MaxX && p2.getX() < MaxX &&p1.getY() > 0 &&p2.getY() >0){
                if (goodPoints(Line,Margin,g)){
                    Line.draw(g);
                }
            }

        }
        Line.nextColor();
    }


}
bool curve::goodPoints(line a, int margin, SDL_Plotter& g){
    if (a.getP1().getX() < margin || a.getP2().getX() < margin||a.getP1().getY() < margin||a.getP1().getY() < margin ){
        return false;
    }else{
        return true;
    }


}
void curve::display(Data_t data, ostream& out){
    for (int i = 0; i < data.size();i ++){
        out << "dataset " << i << endl;
        for (int j = 0; j < data[i].size();j++){
            out << data[i][j].first <<" " << data[i][j].second << endl;
        }

    }
}

#endif // CURVE_H_INCLUDED
