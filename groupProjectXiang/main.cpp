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
#include "alphabet.h"
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

//plots the pixels around the point in a 2x2 square
void plotPoint(point p, SDL_Plotter& g);
//performs a brute force closest pair algorithm on the given data and shows the animation on screen
void BruteForceClosetPair(DataSet_t data,SDL_Plotter& g);
//plots all the data points in the data set
void plotData(DataSet_t,SDL_Plotter& g);
//calculates the distance from one point to another
double distance( pair<int,long double> x,pair<int,long double> y);
//plots a line connected two points in the data set given the indexes of the points in the data set
void plotLine(DataSet_t data,int index1,int index2,SDL_Plotter &g,int r,int gr,int b);
//performs a brute fofce convex hull algorithm on the given data and shows the animation on screen
void BruteForceConvexHull(DataSet_t data,SDL_Plotter &g);
//performs a divide and conquer closest pair algorithm on the data set and shows the animation on screen
//It will start at the start index and end at the n index
//The indices of the current closest pair points are at x and y
double DacClosetPair(DataSet_t data,SDL_Plotter& g,int start,int n, int &x,int &y);

//plots the algorithm and shows the animation on the screen
void plotConvexHull(DataSet_t data,SDL_Plotter &g,int r,int gr,int b);
//performs the divide and conquer convex hull algorithm on the data set
DataSet_t DacConvexHull(DataSet_t data,SDL_Plotter& g,DataSet_t ex);
//merges the local convex hulls
DataSet_t combineHull(DataSet_t Convex1,DataSet_t Convex2,SDL_Plotter & g,DataSet_t ex);
//checks the orientation of three lines that are the boundary of the local convex hulls
int Direction(pair<int,int> one, pair<int,int> two,pair<int,int> three);
//compare function for sorting the points
bool compare(pair<int,int> d1,pair<int,int> d2);
//returns the quadrant that the point is in
int check(pair<int,int>);

//prints out the instruction to use the program
void printInstruction(ostream& out){
    out << "Press the 'S' key to run the Brute Force Closest Pair Algorithm" << endl;
    out << "Press the 'H' key to run the Brute Force Convex Hull Algorithm" << endl;
    out << "Press the 'C' key to run the Divide and Conquer Closest Pair Algorithm" << endl;
    out << "Press the 'D' key to run the Divide and Conquer Convex Hull Algorithm" << endl;
    out << "Press the 'P' key to print out the run time tableau" << endl;
    out << "Press the 'I' key for the help screen" << endl;
    out << "Press the 'Q' key to quit the program" << endl << endl;
}

//prints the run time tableau of each algorithm
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
    out << endl;
}

line s;
color_rgb c;
int indexX;
int indexY;

//middle point between two points
pair<int,int> middleC;
//holds all the data points
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

    //generates 20 random points initially
    for (int i = 0; i < 20; i ++){
        int randX =  rand() % (COL_MAX-1) + 1;
        int randY =  rand() % (ROW_MAX-1) + 1;
        set1.push_back(make_pair(randX, randY));
    }
  //  plotData(set1, g);
    drawMessage(&g,"s for brute force closest pair",50,100,255,0,0);
    drawMessage(&g,"",50,150,255,0,0);
    drawMessage(&g,"h for brute force convex hull",50,200,255,0,0);
    drawMessage(&g,"c for dac closest pair",50,300,255,0,0);
    drawMessage(&g,"d for dac convex hull ",50,400,255,0,0);
    drawMessage(&g,"p print run time tableau",50,500,255,0,0);
    drawMessage(&g,"i for help screen:",50,600,255,0,0);
    drawMessage(&g,"q quit the program",50,700,255,0,0);
    g.update();
    printInstruction(cout);
while(!g.getQuit()){
    int x, y;
    double minD;

    bool mouseClicks = true;
    bool needHelp = true;
		if(g.kbhit()){
			switch(g.getKey()){
                case 'I':
                    g.clear();
                    needHelp = true;
                    for (int i = 0; i < g.getCol(); i++) {
                        for (int j = 0; j < g.getRow(); j++) {
                            g.plotPixel(i, j, 0, 0, 255);
                        }
                    }
                    g.update();

                    drawMessage(&g, "after choosing algorithm", 50, 50, 255, 0, 0);
                    drawMessage(&g,"pressing r",50,100,255,0,0);
                    drawMessage(&g,"      adds twenty more points",50,150,255,0,0);
                    drawMessage(&g,"mouseclick:",50,200,255,0,0);
                    drawMessage(&g,"     adds point on click location:",50,250,255,0,0);
                    drawMessage(&g,"pressing o:",50,300,255,0,0);
                    drawMessage(&g,"     clears screen, choose new algo",50,350,255,0,0);

                    drawMessage(&g, "pick algorithm to get out of help", 50, 450, 255, 0 ,0);
                    drawMessage(&g,"s for brute force closest pair",50,550,255,0,0);
                    drawMessage(&g,"h for brute force convex hull",50,600,255,0,0);
                    drawMessage(&g,"c for dac closest pair",50,650,255,0,0);
                    drawMessage(&g,"d for dac convex hull ",50,700,255,0,0);


                    g.update();

                    //print out words
                    //while(needHelp) {s
                    //q}
                    break;
			    //Performs the brute force closest pair algorithm
			    case 'S':
			        //runs the brute force algorithm and times the run time
                   g.clear();
                   start = clock();
                   BruteForceClosetPair(set1,g);
                   duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                   cout << "Brute Force Closest Pair: " << duration << " seconds" << endl;
                    drawMessage(&g,"i for help screen:",50,50,255,0,0);
                   //updates the run time tableau
                   runTimeIterator = runTime.find("Brute Force Closest Pair");
                   if(runTimeIterator != runTime.end()){
                       runTimeIterator-> second = make_pair(duration, set1.size());
                   }
                      //after the first run occurs, user has the option to add more points via mouse clicks or by
                      //pressing the 'R' key which will plot 20 more random points

                      cout << endl << "Press the mouse to generate a point on click coordinate" << endl;
                      cout << "Press the 'R' key to generate 20 more random points" << endl;
                      cout << "Once finished, press the 'O' key to exit the loop and choose another algorithm" << endl << endl;
                      while(mouseClicks) {
                          //plots the mouse click point and runs the algorithm again
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
                          //adds 20 random points to the data set and plots the algorithm again
                          if (g.getKey() == 'R') {
                              for (int i = 0; i < 20; i ++){
                                  int randX =  rand() % (COL_MAX-1) + 1;
                                  int randY =  rand() % (ROW_MAX-1) + 1;
                                  set1.push_back(make_pair(randX, randY));
                              }
                              g.clear();
                              start = clock();
                              BruteForceClosetPair(set1,g);
                              drawMessage(&g,"i for help screen:",50,50,255,0,0);
                              duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                              cout << "Brute Force Closest Pair: " << duration << " seconds" << endl;

                              runTimeIterator = runTime.find("Brute Force Closest Pair");
                              if(runTimeIterator != runTime.end()){
                                  runTimeIterator-> second = make_pair(duration, set1.size());
                              }
                          }
                          //exits the loop so that the user can run another algorithm
                          if (g.getKey() == 'O') {
                              mouseClicks = false;
                              cout << "Out of loop" << endl;
                              printInstruction(cout);
                          }
                          if (g.getKey() == 'I') {
                              mouseClicks = false;
                              cout << "Out of loop" << endl;
                              printInstruction(cout);
                              break;
                          }
                      }
				break;
                    //performs the brute force convex hull algorithm
                case 'H':
                    //times the run time of the brute force convex hull algorithm
                    g.clear();
                    start = clock();
                    BruteForceConvexHull(set1,g);
                    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                    cout << "Brute Force Convex Hull: " << duration << " seconds" << endl;
                    drawMessage(&g,"i for help screen:",50,50,255,0,0);
                    //updates the run time tableau
                    runTimeIterator = runTime.find("Brute Force Convex Hull");
                    if(runTimeIterator != runTime.end()){
                        runTimeIterator-> second = make_pair(duration, set1.size());
                    }

                    cout << endl << "Press the mouse to generate a point on click coordinate" << endl;
                    cout << "Press the 'R' key to generate 20 more random points" << endl;
                    cout << "Once finished, press the 'O' key to exit the loop and choose another algorithm" << endl << endl;
                    while(mouseClicks) {
                        if(g.getMouseClick(x, y)) {
                            g.clear();
                            set1.push_back(make_pair(x,y));
                            start = clock();
                            BruteForceConvexHull(set1,g);
                            drawMessage(&g,"i for help screen:",50,50,255,0,0);
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
                            drawMessage(&g,"i for help screen:",50,50,255,0,0);
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
                            printInstruction(cout);
                        }
                        if (g.getKey() == 'I') {
                            mouseClicks = false;
                            cout << "Out of loop" << endl;
                            printInstruction(cout);
                            break;
                        }
                    }
                break;
                //performs the divide and conquer closest pair algorithm
			    case 'C':
			        g.clear();
			        //sorts data first;
                    sort(set1.begin(), set1.end());
                    //global variable that keeps the final closest pair indices
                    indexX = 0;
                    indexY = 0;
                    //holds the indices of the current closest pair
                    int x1,y1;

                    //runs and times the algorithm
                    start = clock();
                    minD = DacClosetPair(set1,g,0,set1.size(),x1,y1);
                    drawMessage(&g,"i for help screen:",50,50,255,0,0);
                    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                    cout << "Closest Pair: " << distance(set1[indexX],set1[indexY]) << endl;
                    cout << "Divide and Conquer Closest Pair: " << duration << " seconds" << endl;

                    runTimeIterator = runTime.find("Divide and Conquer Closest Pair");
                    if(runTimeIterator != runTime.end()){
                        runTimeIterator-> second = make_pair(duration, set1.size());
                    }
                    g.clear();
                    drawMessage(&g,"i for help screen:",50,50,255,0,0);
                    plotData(set1, g);
                    plotLine(set1,indexX,indexY,g,255,0,0);
                    g.update();

                    cout << endl << "Press the mouse to generate a point on click coordinate" << endl;
                    cout << "Press the 'R' key to generate 20 more random points" << endl;
                    cout << "Once finished, press the 'O' key to exit the loop and choose another algorithm" << endl << endl;
                    while(mouseClicks) {
                        if(g.getMouseClick(x, y)) {
                            g.clear();
                            set1.push_back(make_pair(x,y));
                            sort(set1.begin(), set1.end());
                            indexX = 0;
                            indexY = 0;
                            int xt,yt;

                            start = clock();
                            minD = DacClosetPair(set1,g,0,set1.size(),x1,y1);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << "Closest Pair: " << distance(set1[indexX], set1[indexY]) << endl;
                            cout << "Divide and Conquer Closest Pair: " << duration << " seconds" << endl;
                            runTimeIterator = runTime.find("Divide and Conquer Closest Pair");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }
                            g.clear();
                            drawMessage(&g,"i for help screen:",50,50,255,0,0);
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
                            int xt,yt;

                            start = clock();
                            minD = DacClosetPair(set1,g,0,set1.size(),x1,y1);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << "Closest Pair: " << distance(set1[indexX], set1[indexY]) << endl;
                            cout << "Divide and Conquer Closest Pair: " << duration << " seconds" << endl;
                            runTimeIterator = runTime.find("Divide and Conquer Closest Pair");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }

                            g.clear();
                            drawMessage(&g,"i for help screen:",50,50,255,0,0);
                            plotData(set1, g);
                            plotLine(set1, indexX, indexY, g, 255, 0, 0);
                            g.update();
                        }
                        if (g.getKey() == 'O') {
                            mouseClicks = false;
                            cout << "Out of loop" << endl;
                            printInstruction(cout);
                        }
                        if (g.getKey() == 'I') {
                            mouseClicks = false;
                            cout << "Out of loop" << endl;
                            printInstruction(cout);
                            break;
                        }
                    }
			        break;
                //performs the divide and conquer convex hull
                case 'D':
                    //sorts the data
                    sort(set1.begin(), set1.end());
                    //performs and runs the divide and conquer convex hull algorithm
                    start = clock();
                    plotConvexHull(DacConvexHull(set1, g,set1), g, 0, 255, 0);
                    drawMessage(&g,"i for help screen:",50,50,255,0,0);
                    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                    cout << "Divide and Conquer Convex Hull: " << duration << " seconds" << endl;

                    runTimeIterator = runTime.find("Divide and Conquer Convex Hull");
                    if(runTimeIterator != runTime.end()){
                        runTimeIterator-> second = make_pair(duration, set1.size());
                    }
                    plotData(set1,g);
                    g.update();

                    cout << endl << "Press the mouse to generate a point on click coordinate" << endl;
                    cout << "Press the 'R' key to generate 20 more random points" << endl;
                    cout << "Once finished, press the 'O' key to exit the loop and choose another algorithm" << endl << endl;
                    while(mouseClicks) {
                        if(g.getMouseClick(x, y)) {
                            g.clear();
                            set1.push_back(make_pair(x,y));
                            sort(set1.begin(), set1.end());
                            start = clock();
                            plotConvexHull(DacConvexHull(set1, g,set1), g, 0, 255, 0);
                            drawMessage(&g,"i for help screen:",50,50,255,0,0);
                            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                            cout << "Divide and Conquer Convex Hull: " << duration << " seconds" << endl;
                            runTimeIterator = runTime.find("Divide and Conquer Convex Hull");
                            if(runTimeIterator != runTime.end()){
                                runTimeIterator-> second = make_pair(duration, set1.size());
                            }
                            plotData(set1, g);
                            g.update();
                        }
                        cout << g.getKey() << endl;
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
                            drawMessage(&g,"i for help screen:",50,50,255,0,0);
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
                            printInstruction(cout);
                        }
                        if (g.getKey() == 'I') {
                            mouseClicks = false;
                            cout << "Out of loop" << endl;
                            printInstruction(cout);
                            break;
                        }
                    }
                    break;
                //prints the run time tableau
                case 'P':
                    printRunTimes(cout, runTime);
                    break;
                //quits the loop
			    case 'R':
                    g.clear();
                    for (int i = 0; i < 20; i ++){
                        int randX =  rand() % (COL_MAX-1) + 1;
                        int randY =  rand() % (ROW_MAX-1) + 1;
                        set1.push_back(make_pair(randX, randY));
                    }
                    plotData(set1,g);
                    g.update();
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

//returns the distance of two different points
double distance(pair<int,long double> x,pair<int,long double> y){
    double distance = sqrt(pow(x.first - y.first,2.0)+pow(x.second - y.second,2.0));
    return distance;
}

void BruteForceClosetPair(DataSet_t data,SDL_Plotter& g){
    double d = 0;
    //initialize minimum with first two data points
    double min = distance(data[0],data[1]);
    int x,y;
    x = 0;
    y = 1;
    //comparison data point
    for (int i = 0; i < data.size() - 1; i++){
        //loops through all other data points
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
            //checks if distance is shorter than minimum and updates indices and minimum value if it is
            if (d < min){
                min = d;
                x = i;
                y = j;
            }
            //deletes the blue processing line in the the animation
            plotLine(data,i,j,g,255,255,255);
            g.update();
        }
    }
    //outputs the shortest pair distance
    cout <<"Shortest Pair: "<< min << endl;
    g.clear();
    //red line is the final closest pair line
    plotLine(data,x,y,g,255,0,0);
    //plot all point;
    plotData(data,g);
    g.update();

}
void BruteForceConvexHull(DataSet_t data,SDL_Plotter &g ){
    double d = 0;
    double min = distance(data[0],data[1]);
    //holds the data for the convex hull
    DataSet_t Convex;
    //comparison point
    for (int i = 0; i< data.size() -1; i ++){
        //loop through all other points
        for (int j = i +1; j < data.size(); j ++){
            //calculates difference in x and y coordinates of the points
            double a = data[j].second - data[i].second;
            double b = data[i].first - data[j].first;
            //subtract the slopes of the line
            double ck = data[i].first*data[j].second -  data[j].first*data[i].second;
            bool samerightside = true;
            bool sameleftside = true;
            bool up = false;

            //checks all other points with the line that is created from the other two points
            //if they are all on the same side then they are in the convex hull
            //if they are not all on the same side then they are not in the convex hull
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

            //pushes the convex points into the data set
            if (samerightside || sameleftside){
                Convex.push_back(make_pair(data[i].first,data[i].second));
                Convex.push_back(make_pair(data[j].first,data[j].second));
            }
            //plots current convex hull data points
             g.clear();
            plotData(data,g);
            //plot current processing line
            plotLine(data, i, j, g, 0, 0, 255);
            g.Sleep(50);
           for (int h = 0; h < Convex.size() ; h = h + 2){
                plotLine(Convex, h, h + 1, g, 0, 255, 0);
           }
           g.update();
        }
    }
    g.clear();
    //plot all point;
    plotData(data,g);
    for (int h = 0; h < Convex.size(); h = h + 2){
        plotLine(Convex, h, h+1, g, 0, 255, 0);
    }
    g.update();
}

//plots pixels around the given point so it's easier to see
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

//connects two points with a line
void plotLine(DataSet_t data,int index1,int index2,SDL_Plotter &g,int r,int gr,int b){
    p1.setX(data[index1].first);
    p1.setY(data[index1].second);
    p2.setX(data[index2].first);
    p2.setY(data[index2].second);
    c.setR(r);
    c.setG(gr);
    c.setB(b);
    s.setP1(p1);
    s.setP2(p2);
    s.setColor(c);
    s.draw(g);
}

//plots all the data points
void plotData(DataSet_t data,SDL_Plotter& g){
    point p;
    for (int i = 0; i < data.size(); i++) {
        p.setX(data[i].first);
        p.setY(data[i].second);
        c.setR(0);
        c.setG(0);
        c.setB(0);
        p.setColor(c);
        plotPoint(p,g);
    }
}

double DacClosetPair(DataSet_t data,SDL_Plotter& g,int start,int n,int &x,int &y){
    //each section is 3 or less data points
    if (n-start <= 3) {

        double min = 1000000;
        //comparison point
        for (int i = start; i < n - 1; i++) {
            //loop through all other points in the section
            for (int j = i + 1; j < n; j++) {
                plotData(data, g);
                //plot current processing line in blue
                plotLine(data, i, j, g, 0, 0, 255);
                g.update();
                g.Sleep(100);
                //updates min if distance is shorter than current min
                if (distance(data[i], data[j]) < min) {
                    min = distance(data[i], data[j]);
                    x = i;
                    y = j;
                }
                //deletes the blue line
                plotLine(data, i, j, g, 255, 255, 255);
                g.update();
            }
        }
        //plot minimum line in green
        plotLine(data, x, y, g, 0, 255, 0);
        g.update();
        return min;
    }
    else{
        //closest pair indices for left and right sections
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;
        //middle index of the section
        int middle = start + (n - start) / 2;

        //recurse left section
        double left = DacClosetPair(data,g,start,middle,x1,y1);
        //recurse right section
        double right = DacClosetPair(data,g,middle,n,x2,y2);
        double minD = -1;

        //coloring left and right comparisons in orange
        plotLine(data, x1, y1, g, 255, 165, 0);
        plotLine(data, x2, y2, g, 255, 165, 0);
        g.update();
        g.Sleep(300);

        //compares the left and right shortest pair distances
        if (left <= right){
            minD = left;
            indexX = x1;
            indexY = y1;
            x = x1;
            y = y1;
            //deletes the right line
            plotLine(data, x2, y2, g, 255, 255, 255);
            g.update();
        }else{
            minD = right;
            indexX = x2;
            indexY = y2;
            x = x2;
            y = y2;
            //deletes the left line
            plotLine(data, x1, y1, g, 255, 255, 255);
            g.update();
        }

        //check middle range of the minimum distance in between the right and left sections
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
                }
            }
        }

        //if there is a pair of points that are the shortest pair in the middle range then we update the
        //minimum distance
        if (min_middle < minD){
            minD = min_middle;
            indexX = x;
            indexY = y;
        }
        return minD;
    }
}

//loops through the data points that are in the convex hull and connects them
void plotConvexHull(DataSet_t data, SDL_Plotter &g,int r,int gr,int b){
    for (int i = 0; i < data.size() - 1; i++) {
        plotLine(data, i, i + 1, g, r, gr, b);
    }
    plotLine(data, 0, data.size() - 1, g, r, gr, b);
    g.update();
}

DataSet_t DacConvexHull(DataSet_t data,SDL_Plotter& g,DataSet_t ex){
    //splits sections to 5 or less points
    if (data.size() <= 5){
        double d = 0;
        double min = distance(data[0],data[1]);
        //set of Convex point
        set<pair<int,int>> Convex;
        for (int i = 0; i< data.size(); i++){
            for (int j = i + 1; j < data.size(); j++){
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
                //if they are on the same side put in to convex set
                if (samerightside || sameleftside){
                    Convex.insert(data[i]);
                    Convex.insert(data[j]);
                }


            }
        }
        DataSet_t result;
        //convert set to a data_set
        for (auto i:Convex){
            result.push_back(i);
        }

        middleC = make_pair(0,0);
        int size = result.size();
        //convert result in to sort able format
        for (int i = 0 ;i < size ;i ++){
            middleC.first += result[i].first;
            middleC.second += result[i].second;
            result[i].first *= size;
            result[i].second *= size;
        }
        //sorting
        sort(result.begin(),result.end(),compare);
        //convert in to normal form
        for (int i = 0; i < size;i++){
            result[i] = make_pair(result[i].first/size,result[i].second/size);
        }
        //plots the convex hull and the data points
        g.clear();
        plotData(ex,g);
        g.update();
        plotConvexHull(result,g,0,255,0);
        plotData(ex, g);
        g.update();
        return result;
    }
    //split in to left and right
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
    //returns merged convex hull
    return combineHull(LC,RC,g,ex);
}

DataSet_t combineHull(DataSet_t Convex1,DataSet_t Convex2,SDL_Plotter & g,DataSet_t ex){
    int size1 = Convex1.size();
    int size2 = Convex2.size();
    int indexA = 0;
    int indexB = 0;
    //get leftest and rightest point
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
    //get up point
    while(!finish){
        finish = true;
        //check if line is cross polygon
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
    //get lower point
    while(!finish){
        finish = true;
        //check if line is cross polygon
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
    //put other valid point in to result
    while(temp!=l1){
        temp = (temp+1)%size1;
        result.push_back(Convex1[temp]);
    }
    temp = l2;
    result.push_back(Convex2[l2]);
    //put other valid point in to result
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

//checks whether the line is crossing the convex hull
int Direction(pair<int,int> one, pair<int,int> two,pair<int,int> three){
    int temp = (two.second - one.second)*(three.first-two.first) - (three.second-two.second)*(two.first - one.first);
    if (temp == 0){
        return 0;
    }
    if(temp > 0) {
        return 1;
    }
    return -1;
}

//comparing the points for sorting
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

//checks the quadrants of a point
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