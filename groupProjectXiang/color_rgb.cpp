/*
* Author: Xiang Gao
* Assignment Title: color_rgb
* Assignment Description: This class represent the color rgb value
* Due Date: 1/28/2019
* Date Created: 1/22/2019
* Date Last Modified: 1/22/2019
    -Create color_rgb class
 */
 #include "color_rgb.h"
color_rgb::color_rgb(){
    this->r = 0;
    this->g = 0;
    this->b = 0;
}
color_rgb::~color_rgb(){

}
color_rgb::color_rgb(int r, int g, int b){
    this->r = r;
    this->g = g;
    this->b = b;
}
int color_rgb::getR(){
    return this->r;
}
int color_rgb::getG(){
    return this->g;
}
int color_rgb::getB(){
    return this->b;
}
void color_rgb::setR(int r){
    this->r = r;
}
void color_rgb::setG(int g){
    this->g = g;
}
void color_rgb::setB(int b){
    this->b = b;
}
void color_rgb::operator=(const color_rgb& c){
        this->r = c.r;
        this->g = c.g;
        this->b = c.b;
}
