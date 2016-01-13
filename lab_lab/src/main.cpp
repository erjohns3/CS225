/**
 * @file main.cpp
 * CS 225 lab_lab
 */

#include "epng.h"    // to use the PNG class
#include <iostream>

using namespace epng;

void removeColor()
{
    // todo    
	png image("in.png");

	for(unsigned long i=0;i<image.width();i++){
		for(unsigned long j=0;j<image.height();j++){
			image(i,j)->green = 0;
		}
	}
	
	image.save("removed.png");
}

int main()
{
	int a = 0;
	int b = 1;
	
	std::cout <<"a: "<< a << std::endl;
    std::cout <<"b: "<< b << std::endl;
	
	flipflop(a,b);
	
	std::cout <<"a: "<< a << std::endl;
    std::cout <<"b: "<< b << std::endl;
	
	return 0;
}

void flipflop(int x, int y)
{
	int tmp = x;
	x = y;
	y = tmp;
}
