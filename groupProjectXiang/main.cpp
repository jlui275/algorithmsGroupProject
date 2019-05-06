/*
* Author: Justin Lui, Xiang Gao, Calvin Manesh, Sterling Trafford, Janna Palavado
* Assignment Title: Group Project
* Assignment Description: Implementation of the Brute Force Closest Pair and Convex Hull Algorithms and Implementations
*                         of the Divide and Conquer Closest Pair and Convex Hull Algoirthms
* Due Date: 5/7/2019
* Date Created: 4/15/2019
* Date Last Modified: 5/5/2019
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
#include <set>
#include <time.h>
#include <ctime>
#include <map>
#include <iomanip>

using namespace std;

const int ROW_MAX = 750;
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

void plotConvexHull(DataSet_t data,SDL_Plotter &g,int r,int gr,int b);
DataSet_t DacConvexHull(DataSet_t data,SDL_Plotter& g,DataSet_t ex);
DataSet_t combineHull(DataSet_t Convex1,DataSet_t Convex2,SDL_Plotter & g,DataSet_t ex);
int Direction(pair<int,int> one, pair<int,int> two,pair<int,int> three);
bool compare(pair<int,int> d1,pair<int,int> d2);
int check(pair<int,int>);

void printRunTimes(ostream& out, map<string, pair<double, int> > runTime){
    map<string, pair<double, int> >::iterator it;
    out << endl << "Run Time Values: " << endl;
    out << setw(35) << left << "Algorithm";
    out << setw(10) << right << "Time(s)";
    out << setw(15) << right << "Set Size (n)" << endl;
    for(it = runTime.begin(); it != runTime.end(); it++){
        out << setw(35) << left << it-> first;
        out << setw(10) << right << it-> second.first;
        out << setw(10) << right << it-> second.second;
        out << endl;
    }
}

line s;
color_rgb c;
int indexX;
int indexY;

pair<int,int> middleC;
DataSet_t minDistance;
DataSet_t set1;

int main(int argc, char** argv) {
    //tracks the run time of each algorithm
    clock_t start;
    double duration;
    map<string, pair<double, int> >runTime;
    map<string, pair<double, int> >::iterator runTimeIterator;
    runTime.insert(make_pair("Brute Force Closest Pair", make_pair(-1, 0)));
    runTime.insert(make_pair("Brute Force Convex Hull", make_pair(-1, 0)));
    runTime.insert(make_pair("Divide and Conquer Closest Pair", make_pair(-1, 0)));
    runTime.insert(make_pair("Divide and Conquer Convex Hull", make_pair(-1, 0)));


    srand(time(0));
	SDL_Plotter g(ROW_MAX,COL_MAX);
	curve crv;

    vector<DataSet_t> data;

    DataSet_t set1;
    //generates 20 random points initially
    for (int i = 0; i < 20; i ++){
        int randX =  rand() % (COL_MAX-1) + 1;
        int randY =  rand() % (ROW_MAX-1) + 1;
        set1.push_back(make_pair(randX, randY));
    }

while(!g.getQuit()){
    int x, y;
    double mind;
    bool mouseClicks = true;
		if(g.kbhit()){
			switch(g.getKey()){
			    case 'S':
				 g.clear();
				 start = clock();
				 BruteForceClosetPair(set1,g);
				 duration = (clock() - start) / (double) CLOCKS_PER_SEC;
				 cout << "Brute Force Closest Pair: " << duration << " seconds" << endl;

				 runTimeIterator = runTime.find("Brute Force Closest Pair");
				 if(runTimeIterator != runTime.end()){
				     runTimeIterator-> second = make_pair(duration, set1.size());
				 }
                    while(mouseClicks) {
                        if(g.getMouseClick(x, y)) {
                            g.clear();
                            set1.push_back(make_pair(x,y));
                            start = clock();
                            BruteForceClosetPair(set1,g);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << "Brute Force Closest Pair: " << duration << " seconds" << endl;

                            runTimeIterator = runTime.find("Brute Force Closest Pair");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }
                        }
                        if (g.getKey() == 'R') {
                            for (int i = 0; i < 20; i ++){
                                int randX =  rand() % (COL_MAX-1) + 1;
                                int randY =  rand() % (ROW_MAX-1) + 1;
                                set1.push_back(make_pair(randX, randY));
                            }
                            g.clear();
                            start = clock();
                            BruteForceClosetPair(set1,g);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << "Brute Force Closest Pair: " << duration << " seconds" << endl;

                            runTimeIterator = runTime.find("Brute Force Closest Pair");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }
                        }
                        if (g.getKey() == 'O') {
                            mouseClicks = false;
                            cout << "Out of loop" << endl;
                        }
                    }
				break;
				case 'H':
                    g.clear();
                    start = clock();
                    BruteForceConvexHull(set1,g);
                    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                    cout << "Brute Force Convex Hull: " << duration << " seconds" << endl;
                    runTimeIterator = runTime.find("Brute Force Convex Hull");
                    if(runTimeIterator != runTime.end()){
                        runTimeIterator-> second = make_pair(duration, set1.size());
                    }

                    while(mouseClicks) {
                        if(g.getMouseClick(x, y)) {
                            g.clear();
                            set1.push_back(make_pair(x,y));
                            start = clock();
                            BruteForceConvexHull(set1,g);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << "Brute Force Convex Hull: " << duration << " seconds" << endl;
                            runTimeIterator = runTime.find("Brute Force Convex Hull");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }
                        }
                        if (g.getKey() == 'R') {
                            for (int i = 0; i < 20; i ++){
                                int randX =  rand() % (COL_MAX-1) + 1;
                                int randY =  rand() % (ROW_MAX-1) + 1;
                                set1.push_back(make_pair(randX, randY));
                            }
                            g.clear();
                            start = clock();
                            BruteForceConvexHull(set1,g);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << "Brute Force Convex Hull: " << duration << " seconds" << endl;
                            runTimeIterator = runTime.find("Brute Force Convex Hull");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }
                        }

                        if (g.getKey() == 'O') {
                            mouseClicks = false;
                            cout << "Out of loop" << endl;
                        }
                    }
                    break;
			    case 'C':
			        g.clear();
			        //sort data first;
                    sort(set1.begin(), set1.end());
                    //initialize variable
                    indexX = 0;
                    indexY = 0;
                    minDistance.clear();
                    int x1,y1;

                    start = clock();
                    mind = DacClosetPair(set1,g,0,set1.size(),x1,y1);
                    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                    cout << mind << endl;
                    cout << "Closest Pair: " << distance(set1[indexX],set1[indexY]) << endl;
                    cout << "Divide and Conquer Closest Pair: " << duration << " seconds" << endl;
                    runTimeIterator = runTime.find("Divide and Conquer Closest Pair");
                    if(runTimeIterator != runTime.end()){
                        runTimeIterator-> second = make_pair(duration, set1.size());
                    }
                    g.clear();
                    plotData(set1, g);
                    plotLine(set1,indexX,indexY,g,255,0,0);
                    g.update();

                    while(mouseClicks) {
                        if(g.getMouseClick(x, y)) {
                            g.clear();
                            set1.push_back(make_pair(x,y));
                            sort(set1.begin(), set1.end());
                            indexX = 0;
                            indexY = 0;
                            minDistance.clear();
                            int xt,yt;

                            start = clock();
                            mind = DacClosetPair(set1,g,0,set1.size(),x1,y1);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << mind << endl;
                            cout << "Closest Pair: " << distance(set1[indexX], set1[indexY]) << endl;
                            cout << "Divide and Conquer Closest Pair: " << duration << " seconds" << endl;
                            runTimeIterator = runTime.find("Divide and Conquer Closest Pair");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }
                            g.clear();
                            plotData(set1, g);
                            plotLine(set1, indexX, indexY, g, 255, 0, 0);
                            g.update();
                        }
                        if (g.getKey() == 'R') {
                            for (int i = 0; i < 20; i ++){
                                int randX =  rand() % (COL_MAX-1) + 1;
                                int randY =  rand() % (ROW_MAX-1) + 1;
                                set1.push_back(make_pair(randX, randY));
                            }
                            g.clear();
                            sort(set1.begin(), set1.end());
                            indexX = 0;
                            indexY = 0;
                            minDistance.clear();
                            int xt,yt;

                            start = clock();
                            mind = DacClosetPair(set1,g,0,set1.size(),x1,y1);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << mind << endl;
                            cout << "Closest Pair: " << distance(set1[indexX], set1[indexY]) << endl;
                            cout << "Divide and Conquer Closest Pair: " << duration << " seconds" << endl;
                            runTimeIterator = runTime.find("Divide and Conquer Closest Pair");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }

                            g.clear();
                            plotData(set1, g);
                            plotLine(set1, indexX, indexY, g, 255, 0, 0);
                            g.update();
                        }
                        if (g.getKey() == 'O') {
                            mouseClicks = false;
                            cout << "Out of loop" << endl;
                        }
                    }
			        break;

                case 'D':
                    sort(set1.begin(), set1.end());
                    start = clock();
                    plotConvexHull(DacConvexHull(set1, g,set1), g, 0, 255, 0);
                    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                    cout << "Divide and Conquer Convex Hull: " << duration << " seconds" << endl;
                    runTimeIterator = runTime.find("Divide and Conquer Convex Hull");
                    if(runTimeIterator != runTime.end()){
                        runTimeIterator-> second = make_pair(duration, set1.size());
                    }
                    plotData(set1,g);
                    g.update();

                    while(mouseClicks) {
                        if(g.getMouseClick(x, y)) {
                            g.clear();
                            set1.push_back(make_pair(x,y));
                            sort(set1.begin(), set1.end());
                            start = clock();
                            plotConvexHull(DacConvexHull(set1, g,set1), g, 0, 255, 0);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << "Divide and Conquer Convex Hull: " << duration << " seconds" << endl;
                            runTimeIterator = runTime.find("Divide and Conquer Convex Hull");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }
                            plotData(set1, g);
                            g.update();
                        }
                        if(g.getKey() == 'R') {
                            g.clear();
                            for (int i = 0; i < 20; i ++){
                                int randX =  rand() % (COL_MAX-1) + 1;
                                int randY =  rand() % (ROW_MAX-1) + 1;
                                set1.push_back(make_pair(randX, randY));
                            }
                            sort(set1.begin(), set1.end());
                            start = clock();
                            plotConvexHull(DacConvexHull(set1, g,set1), g, 0, 255, 0);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << "Divide and Conquer Convex Hull: " << duration << " seconds" << endl;
                            runTimeIterator = runTime.find("Divide and Conquer Convex Hull");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }
                            plotData(set1, g);
                            g.update();
                        }
                        if (g.getKey() == 'O') {
                            mouseClicks = false;
                            cout << "Out of loop" << endl;
                        }
                    }
                    break;
			    case 'P':
                    printRunTimes(cout, runTime);
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
            g.update();
            g.Sleep(50);
            if (d < min){
                min = d;
                x = i;
                y = j;
            }
            plotLine(data,i,j,g,255,255,255);
            g.update();
        }
    }
    cout <<"Shortest Pair: "<< min << endl;
    g.clear();
    plotLine(data,x,y,g,255,0,0);
    //plot all point;
    plotData(data,g);
    g.update();

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
            g.Sleep(50);
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
    //plost all point;
    plotData(data,g);
    for (int h = 0; h < Convex.size(); h=h+2){
        plotLine(Convex,h,h+1,g,0,255,0);
        // cout << Convex[h].first << " " <<  Convex[h].second << " --" <<  Convex[h+1].first << " " <<  Convex[h+1].second <<endl;
    }
    g.update();
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
    if (n-start <= 3) {

        double min = 1000000;
        for (int i = start; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                plotData(data, g);
                //plot current processing line in blue
                plotLine(data, i, j, g, 0, 0, 255);
                g.update();
                g.Sleep(100);
                if (distance(data[i], data[j]) < min) {
                    min = distance(data[i], data[j]);
                    x = i;
                    y = j;
                }
                plotLine(data, i, j, g, 255, 255, 255);
                g.update();
            }
        }
        //plot minimum line in green
        plotLine(data, x, y, g, 0, 255, 0);
        g.update();
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

        //coloring left and right comparisons in orange
        plotLine(data, x1, y1, g, 255, 165, 0);
        plotLine(data, x2, y2, g, 255, 165, 0);
        g.update();
        g.Sleep(300);

        if (left <= right){
            minD = left;
            indexX = x1;
            indexY = y1;
            x = x1;
            y = y1;
            plotLine(data, x2, y2, g, 255, 255, 255);
            g.update();
        }else{
            minD = right;
            indexX = x2;
            indexY = y2;
            x = x2;
            y = y2;
            plotLine(data, x1, y1, g, 255, 255, 255);
            g.update();
        }

        //check middle range
        vector<int> range;
        for ( int i = start; i < n  ; i++){
            if (abs(data[i].first - data[middle].first) < minD){
                range.push_back(i);
            }
        }
        double min_middle = minD;
        for (int i = 0; i < range.size();i++){
            for (int j = i+1; j < range.size() && (data[range[j]].second- data[range[i]].second) < min_middle; j++){
                if (distance(data[range[i]],data[range[j]]) < min_middle){
                    min_middle = distance(data[range[i]],data[range[j]]);
                    x = range[i];
                    y = range[j];
                    //min of middle ranges
                    //plot the new min in brown
                    //plotLine(data, x, y, g, 165, 42, 42);
//                    plotLine(data, x1, y1, g, 255, 255, 255);
//                    plotLine(data, x2, y2, g, 255, 255, 255);
//                    g.update();
//                    g.Sleep(500);
                }
            }
        }

        if (min_middle < minD){
            minD = min_middle;
            indexX = x;
            indexY = y;
        }
        cout << left << " " << right << " " << min_middle << endl;
        cout << "return " << minD << endl;

        return minD;

    }

}

void plotConvexHull(DataSet_t data, SDL_Plotter &g,int r,int gr,int b){
    for (int i = 0; i < data.size() - 1; i++) {
        plotLine(data, i, i + 1, g, r, gr, b);
    }
    plotLine(data, 0, data.size() - 1, g, r, gr, b);
    g.update();
}

DataSet_t DacConvexHull(DataSet_t data,SDL_Plotter& g,DataSet_t ex){
    if (data.size() <= 5){
        double d = 0;
        double min = distance(data[0],data[1]);
        set<pair<int,int>> Convex;
        for (int i = 0; i< data.size(); i ++){
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
                    }

                }
                //  cout <<sameleftside <<" --" << samerightside << endl;
                if (samerightside || sameleftside){
                    Convex.insert(data[i]);
                    Convex.insert(data[j]);
                    // plotLine(data,i,j,g,0,255,0);
                }


            }
        }
        DataSet_t result;

        for (auto i:Convex){
            result.push_back(i);
        }

        middleC = make_pair(0,0);
        int size = result.size();
        for (int i = 0 ;i < size ;i ++){
            middleC.first += result[i].first;
            middleC.second += result[i].second;
            result[i].first *= size;
            result[i].second *= size;
        }
        sort(result.begin(),result.end(),compare);
        for (int i = 0; i < size;i++){
            result[i] = make_pair(result[i].first/size,result[i].second/size);
        }
        g.clear();
        plotData(ex,g);
        g.update();
        plotConvexHull(result,g,0,255,0);
        plotData(ex, g);
        g.update();
        cout <<"new data" <<endl;
        for (int i =0; i < data.size();i++){
            cout << data[i].first << " " << data[i].second <<endl;
        }
        return result;
    }
    DataSet_t Left,Right;
    for (int i = 0; i < data.size()/2;i++){
        Left.push_back(data[i]);
    }
    for (int i = data.size() /2; i < data.size();i++){
        Right.push_back(data[i]);
    }
    DataSet_t LC,RC;
    LC = DacConvexHull(Left,g,ex);
    RC = DacConvexHull(Right,g,ex);

    return combineHull(LC,RC,g,ex);
}

DataSet_t combineHull(DataSet_t Convex1,DataSet_t Convex2,SDL_Plotter & g,DataSet_t ex){
    int size1 = Convex1.size();
    int size2 = Convex2.size();
    int indexA = 0;
    int indexB = 0;
    for (int i=1; i < size1; i++){
        if (Convex1[i].first > Convex1[indexA].first){
            indexA = i;
        }
    }
    for (int i = 1; i < size2; i++){
        if (Convex2[i].first < Convex2[indexB].first){
            indexB = i;
        }
    }
    bool finish = false;
    int t1;
    int t2;
    t1 = indexA;
    t2 = indexB;
    while(!finish){
        finish = true;
        while(Direction(Convex2[t2],Convex1[t1],Convex1[(t1+1)%size1])>=0){
            t1 = (t1+1)%size1;
        }
        while(Direction(Convex1[t1],Convex2[t2],Convex2[(size2+t2-1)%size2])<=0){
            t2 = (size2+t2-1)%size2;
            finish = false;
        }
    }
    int u1 = t1;
    int u2 = t2;
    finish = false;
    t1 = indexA;
    t2 = indexB;
    int temp = 0;
    while(!finish){
        finish = true;
        while (Direction(Convex1[t1], Convex2[t2], Convex2[(t2+1)%size2])>=0)
            t2=(t2+1)%size2;

        while (Direction(Convex2[t2], Convex1[t1], Convex1[(size1+t1-1)%size1])<=0)
        {
            t1=(size1+t1-1)%size1;
            finish=false;
        }

    }
    int l1 = t1;
    int l2 = t2;
    DataSet_t result;
    temp = u1;
    result.push_back(Convex1[u1]);
    while(temp!=l1){
        temp = (temp+1)%size1;
        result.push_back(Convex1[temp]);
    }
    temp = l2;
    result.push_back(Convex2[l2]);

    while(temp!=u2) {
        temp = (temp + 1) % size2;
        result.push_back(Convex2[temp]);
    }
    plotData(ex,g);
    g.Sleep(100);
    plotConvexHull(Convex1,g,0,0,255);
    plotConvexHull(Convex2,g,0,0,255);
    plotData(ex,g);
    g.update();
    g.Sleep(100);
    plotConvexHull(result,g,255,0,0);
    g.clear();
    plotData(ex, g);
    plotConvexHull(result,g,255,0,0);
    g.update();
    g.Sleep(100);
    plotData(ex,g);
    g.update();
    return result;
}


int Direction(pair<int,int> one, pair<int,int> two,pair<int,int> three){
    int temp = (two.second - one.second)*(three.first-two.first) - (three.second-two.second)*(two.first - one.first);
    if (temp == 0){
        return 0;
    }
    if(temp > 0)
        return 1;
    return -1;
}

bool compare(pair<int,int> d1,pair<int,int> d2){
    pair<int,int> t1 = make_pair(d1.first-middleC.first,d1.second - middleC.second);
    pair<int,int> t2 = make_pair(d2.first-middleC.first,d2.second - middleC.second);
    int temp1 = check(t1);
    int temp2 = check(t2);
    if (temp1 != temp2){
        return (temp1 < temp2);
    }
    return (t1.second*t2.first < t2.second*t1.first);
}

int check(pair<int,int> point){
    if (point.first >= 0 && point.second >= 0){
        return 1;
    }
    if (point.first <=0 && point.second >= 0)
        return 2;
    if (point.first <= 0 && point.second <= 0){
        return 3;
    }
    return 4;
}