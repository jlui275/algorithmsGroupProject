/*
* Author: Xiang Gao
* Assignment Title: color_rgb
* Assignment Description: This class represent the color rgb value
* Due Date: 1/28/2019
* Date Created: 1/22/2019
* Date Last Modified: 1/22/2019
    -Create color_rgb class
 */
#ifndef COLOR_RGB_H_INCLUDED
#define COLOR_RGB_H_INCLUDED
class color_rgb {
public:
	color_rgb();
	color_rgb(int r, int g, int b);
	virtual ~color_rgb();
	int getR();
	int getG();
	int getB();

	void setR(int r);
	void setG(int g);
	void setB(int b);

	void operator=(const color_rgb& c);

private:
	int r,g,b;
};

#endif // COLOR_RGB_H_INCLUDED
