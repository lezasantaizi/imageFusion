#ifndef GASSIAN_PYRAMID
#define GASSIAN_PYRAMID

#include<iostream>
#include "../3rdparty/include/opencv.hpp"
#include<math.h>
using namespace std;
using namespace cv;

class GassianPyramid
{
public:
/*	int width = src.cols;  
	int height = src.rows;*/  
	int octave ;
	int s ;
	float k;

	int win_size;
	float sigma ;
	float** arr;
	double sigma2;  
	double sigma4;
 

	GassianPyramid(int octave, int s);
	~GassianPyramid();

	void genGassianFunc();
	void gassianBlur();

#endif