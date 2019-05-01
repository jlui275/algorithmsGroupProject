/*
* Author: Justin Lui
* Assignment Title: Programming Assignment 1
* Assignment Description: Visualization of different Big O notation
* Due Date: 1/28/2019
* Date Created: 1/23/2019
* Date Last Modified: 1/23/2019
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "SDL_Plotter.h"
#include "color_rgb.h"
#include "point.h"
#include "line.h"
#include "curve.h"
#include <cstdlib>
#include <algorithm>
#include <climits>
using namespace std;

const int ROW_MAX = 500;
const int COL_MAX = 1000;
point p1(50,50);
point p2(50,50);

void plotPoint(point p, SDL_Plotter& g);
void BruteForceClosetPair(DataSet_t data,SDL_Plotter& g);
void plotData(DataSet_t,SDL_Plotter& g);
double distance( pair<int,long double> x,pair<int,long double> y);
void plotLine(DataSet_t data,int x,int y,SDL_Plotter &g,int r,int gr,int b);
void BruteForceConvexHull(DataSet_t data,SDL_Plotter &g);
double DacClosetPair(DataSet_t data,SDL_Plotter& g,int start,int n,int &x,int &y);
void DacConvexHull();
line s;
color_rgb c;
int indexX;
int indexY;

DataSet_t minDistance;
int main(int argc, char** argv) {
	SDL_Plotter g(ROW_MAX,COL_MAX);
	curve crv;

    vector<DataSet_t> data;

    DataSet_t set1;
    for (int i = 0; i < 20; i ++){
        int x =  rand() % (COL_MAX-1) + 1;
        int y =  rand() % (ROW_MAX-1) + 1;
        set1.push_back(make_pair(x,y));
    }


while(!g.getQuit()){
    int x, y;
    double mind;
    bool mouseClicks = true;
		if(g.kbhit()){
			switch(g.getKey()){
			     case 'S':
				//crv.setSameScale(!crv.getSameScale());
				g.clear();
                    BruteForceClosetPair(set1,g);

                    while(mouseClicks) {
                        if(g.getMouseClick(x, y)) {
                            set1.push_back(make_pair(x,y));
                            BruteForceClosetPair(set1, g);
                        }
                        if (g.getKey() == 'O') {
                            mouseClicks = false;
                            cout << "Out of loop" << endl;
                        }
                    }
				//crv.draw(data,g);
				break;
				case 'H':
                    //crv.setSameScale(!crv.getSameScale());
                    g.clear();
                    BruteForceConvexHull(set1,g);

                    while(mouseClicks) {
                        if(g.getMouseClick(x, y)) {
                            set1.push_back(make_pair(x,y));
                            BruteForceConvexHull(set1, g);
                        }
                        if (g.getKey() == 'O') {
                            mouseClicks = false;
                            cout << "Out of loop" << endl;
                        }
                    }
                    //crv.draw(data,g);
                    break;
			    case 'C':
			        //sort data first;
                  sort(set1.begin(), set1.end());
                    //initialize variable
                    indexX = 0;
                    indexY = 0;
                    minDistance.clear();
                    int x1,y1;
                    mind = DacClosetPair(set1,g,0,set1.size(),x1,y1);
                    cout << mind << endl;
                    cout << "-x> " << distance(set1[indexX],set1[indexY]) << endl;
			        break;
                case 'Q':
                g.setQuit(true);
                break;
			}
		}
		g.update();
	}
    return 0;
}

double distance(pair<int,long double> x,pair<int,long double> y){
    double distance = sqrt(pow(x.first - y.first,2.0)+pow(x.second - y.second,2.0));
    return distance;
}
void BruteForceClosetPair(DataSet_t data,SDL_Plotter& g){
    double d = 0;
    double min = distance(data[0],data[1]);
    int x,y;
    x = 0;
    y = 1;
    for (int i = 0; i < data.size() - 1; i++){
        for (int j = i + 1; j < data.size(); j++){
            //clear screen
            g.clear();
            //plot all point;
            plotData(data,g);
            //plot current min line in green
            plotLine(data,x,y,g,0,255,0);
            //plot current processing line in blue
            plotLine(data,i,j,g,0,0,255);
            d = distance(data[i],data[j]);
            g.Sleep(100);
            if (d < min){
                min = d;
                x = i;
                y = j;
            }
            g.update();
        }
    }
    cout <<"Shortest Pair: "<< min << endl;
    g.clear();
    plotLine(data,x,y,g,0,255,0);
    //plot all point;
    plotData(data,g);

}
void BruteForceConvexHull(DataSet_t data,SDL_Plotter &g ){
    double d = 0;
    double min = distance(data[0],data[1]);
    DataSet_t Convex;
    for (int i = 0; i< data.size() -1; i ++){
        for (int j = i +1; j < data.size(); j ++){
            double a = data[j].second - data[i].second;
            double b = data[i].first - data[j].first;
            double ck = data[i].first*data[j].second -  data[j].first*data[i].second;
            bool samerightside = true;
            bool sameleftside = true;
            bool up = false;
            for (int k = 0; k < data.size();k++){
                if (k != i && k!= j){
                    double num = data[k].first*a + b*data[k].second -ck;
                    if (num < 0){
                        samerightside = false;
                    }
                    if (num > 0){
                        sameleftside = false;
                    }
                    p1.setX(data[k].first);
                    p1.setY(data[k].second);
                    c.setR(255);
                    c.setG(0);
                    c.setB(0);
                    p1.setColor(c);
                    p1.draw(g);
                }

            }
          //  cout <<sameleftside <<" --" << samerightside << endl;
            if (samerightside || sameleftside){
                Convex.push_back(make_pair(data[i].first,data[i].second));
                Convex.push_back(make_pair(data[j].first,data[j].second));
               // plotLine(data,i,j,g,0,255,0);
            }
            //plot all convex HULL
             g.clear();
            plotData(data,g);
            //plot current processing line
            plotLine(data,i,j,g,0,0,255);
           for (int h = 0; h < Convex.size() ; h=h+2){
                plotLine(Convex,h,h+1,g,0,255,0);
               // cout << Convex[h].first << " " <<  Convex[h].second << " --" <<  Convex[h+1].first << " " <<  Convex[h+1].second <<endl;
            }
            g.update();
           /* //clear screen
            g.clear();
            //plot all point;
            plotData(data,g);
            //plot current min line in green
            plotLine(data,x,y,g,0,255,0);
            //plot curent processing line in blue
            plotLine(data,i,j,g,0,0,255);
            g.Sleep(100);
            g.update();*/
        }
    }
    g.clear();
    //plot all point;
    plotData(data,g);
    for (int h = 0; h < Convex.size(); h=h+2){
        plotLine(Convex,h,h+1,g,0,255,0);
        // cout << Convex[h].first << " " <<  Convex[h].second << " --" <<  Convex[h+1].first << " " <<  Convex[h+1].second <<endl;
    }
}

void plotPoint(point p, SDL_Plotter& g){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            g.plotPixel(p.getX() + j, p.getY() + i, p.getColor().getR(), p.getColor().getG(), p.getColor().getB());
        }
    }

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            g.plotPixel(p.getX() - j, p.getY() + i, p.getColor().getR(), p.getColor().getG(), p.getColor().getB());
        }
    }

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            g.plotPixel(p.getX() + j, p.getY() - i, p.getColor().getR(), p.getColor().getG(), p.getColor().getB());
        }
    }

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            g.plotPixel(p.getX() - j, p.getY() - i, p.getColor().getR(), p.getColor().getG(), p.getColor().getB());
        }
    }
}

void plotLine(DataSet_t data,int x,int y,SDL_Plotter &g,int r,int gr,int b){
    p1.setX(data[x].first);
    p1.setY(data[x].second);
    p2.setX(data[y].first);
    p2.setY(data[y].second);
    c.setR(r);
    c.setG(gr);
    c.setB(b);
    s.setP1(p1);
    s.setP2(p2);
    s.setColor(c);
    s.draw(g);
}
void plotData(DataSet_t data,SDL_Plotter& g){
    point p;
 for (int i = 0; i < data.size(); i++) {
     p.setX(data[i].first);
     p.setY(data[i].second);
     c.setR(0);
     c.setG(0);
     c.setB(0);
     p.setColor(c);
     // cout << p.getX() << " " << p.getY() << endl;
     plotPoint(p,g);
 }
}
double DacClosetPair(DataSet_t data,SDL_Plotter& g,int start,int n,int &x,int &y){
    if (n-start <=3){

        double min = 1000000;
        for (int i = start; i < n - 1; i ++  ){
            for (int j = i + 1; j <n;j++){

                if (distance(data[i],data[j]) < min){
                    min = distance(data[i],data[j]);
                    x = i;
                    y = j;
                }
            }
        }
        cout << " --> " << x << " " << y << endl;
        return min;
    }
   else{
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;
        int middle = start + (n-start)/2;

        double left = DacClosetPair(data,g,start,middle,x1,y1);
        double right = DacClosetPair(data,g,middle,n,x2,y2);
        double minD = -1;

        if (left <=right){
            minD = left;
            indexX = x1;
            indexY = y1;
            x = x1;
            y = y1;

        }else{
            minD = right;
            indexX = x2;
            indexY = y2;
            x = x2;
            y = y2;
        }

        //check middle range
        vector<int> range;
        for ( int i = 0; i < n -start ; i++){
            if (abs(data[i].first - data[middle].first) < minD){
                range.push_back(i);
            }
        }
        double min_middle = minD;
        sort(range.begin(),range.end());
        for (int i = 0; i < range.size();i++){
            for (int j = i+1; j < range.size() && (data[range[j]].second- data[range[i]].second) < min_middle; j++){
                if (distance(data[range[i]],data[range[j]]) < min_middle){
                    min_middle = distance(data[range[i]],data[range[j]]);
                    x = range[i];
                    y = range[j];
                }
            }
        }
        if (min_middle < minD){
            minD = min_middle;
            indexX = x;
            indexY = y;
        }
        cout << indexX << " " << indexY << endl;
        cout << "return " << minD << endl;
        return minD;

    }

}