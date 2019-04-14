#include <iostream>

#include "SDL_Plotter.h"
#include "point.h"
#include "line.h"

using namespace std;

void plotRandomPoints(int points, int screenX, int screenY, SDL_Plotter &g){
    int x;
    int y;

    int R = rand()%256;
    int G = rand()%256;
    int B = rand()%256;

    for (int i = 0; i < points; i++) {
        x = rand() % screenX;
        y = rand() % screenY;
        g.plotPixel(x, y, R, G, B);
    }
}


int main(int argc, char ** argv)
{
    int screenX = 1000;
    int screenY = 1000;

    SDL_Plotter g(screenX, screenY);
    bool stopped = false;
    bool colored = true;
    int x,y, xd, yd;
    int R,G,B;

    R = rand()%256;
    G = rand()%256;
    B = rand()%256;

    g.update();

    while (!g.getQuit())
    {
//        if(!stopped){
//            x = rand()%g.getCol();
//            y = rand()%g.getRow();
//            R = rand()%256;
//            G = rand()%256;
//            B = rand()%256;
//            for(xd = 0; xd < 10 && x + xd < g.getCol(); xd++ ){
//                for(yd = 0; yd < 10 && y + yd < g.getRow(); yd++ ){
//                    if(colored){
//                        g.plotPixel( x + xd, y + yd, R, G, B);
//                    }
//                    else{
//                        g.plotPixel( x + xd, y + yd, 0, G, 0);
//                    }
//
//                }
//            }
//        }

        if(g.kbhit()){
                switch(g.getKey()){
                    case 'Q':
                        g.setQuit(true);
                        break;
                    case 'P':
                        plotRandomPoints(1000, screenX, screenY, g);
                        break;
                }
        }

        if(g.getMouseClick(x,y)){
            //creates a new point
            point p1(x, y);
            p1.draw(g);

            point p2(25, 25);
            point p3(500, 500);
            line l1(p2, p3);

            l1.draw(g);

//            for(xd = 0; xd < 10 && x + xd < g.getCol(); xd++ ){
//                for(yd = 0; yd < 10 && y + yd < g.getRow(); yd++ ){
//                    if(colored){
//                        g.plotPixel( x + xd, y + yd, R, G, B);
//                    }
//                }
//            }
        }

        g.update();
    }
}