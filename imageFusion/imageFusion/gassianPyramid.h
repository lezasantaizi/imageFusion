#ifndef GASSIAN_PYRAMID
#define GASSIAN_PYRAMID

#include<iostream>
#include "../3rdparty/include/opencv.hpp"
#include<math.h>
#include <vector>
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
	float sigma2;  
	float sigma4;
	vector<vector<Mat>> pyramidImage;
 

	GassianPyramid(int octaveSize, int levelSize,int winSize,float sigmaValue);
	~GassianPyramid();

	void genGassianFunc(float sigmaValue,int winSize);
	void gassianBlur(float sigma,int winSize, Mat src, Mat& result);
	void downSampleFunc(Mat src, Mat& result);
	void expendSampleFunc(Mat src, Mat& result);
	void printMat(Mat result);

	void createPyramid(Mat src);
	void getDoG(Mat src1, Mat src2, Mat& result);
};

#endif