#include<iostream>
#include "../3rdparty/include/opencv.hpp"
#include<math.h>
using namespace std;
using namespace cv;

using namespace std;

#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")
#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249.lib")
#pragma comment(lib, "opencv_imgproc249.lib")
#pragma comment(lib, "opencv_core249.lib")

void genGaussian(int win_size,float sigma,float** arr)
{
	float arrSum = 0;
	for (int i = -win_size ; i <= win_size; i++)
	{
		for (int j = -win_size ; j<= win_size; j++)
		{
			int r = i*i + j*j;
			float k = -r/(2*sigma*sigma);
			arr[i+win_size][j+win_size] = exp(k)/sqrt(2*3.1415926*sigma*sigma);

			arrSum += arr[i+win_size][j+win_size];
		}
	}

	for (int i = -win_size ; i <= win_size; i++)
	{
		for (int j = -win_size ; j<= win_size; j++)
		{
			arr[i+win_size][j+win_size] /= arrSum;
			//printf("%f ",arr[i+win_size][j+win_size]);
		}
		//printf("\n");
	}
}

void gaussianblurFunc(int win_size, float sigma, Mat& src, float** arr, Mat& result)
{
	genGaussian(win_size,sigma,arr);
	result.create(Size(src.cols,src.rows),src.type());
	for (int row = 0 ;row <src.rows ;row++)
	{
		for (int col = 0 ; col <src.cols; col++)
		{
			float sumRed = 0,sumGreen = 0,sumBlue = 0;
			for (int subrow = -win_size;subrow<=win_size;subrow++)
			{
				int srcrow = row+subrow;
				if (srcrow<0||srcrow>=src.rows)
				{
					srcrow = row;
				}
				for (int subcol = -win_size;subcol<=win_size;subcol++)
				{
					int srccol = col+subcol;
					if (srccol<0||srccol>=src.cols)
					{
						srccol = col;
					}
					sumRed += arr[subrow+win_size][subcol+win_size]*src.at<Vec3b>(srcrow,srccol)[2];
					sumGreen += arr[subrow+win_size][subcol+win_size]*src.at<Vec3b>(srcrow,srccol)[1];
					sumBlue += arr[subrow+win_size][subcol+win_size]*src.at<Vec3b>(srcrow,srccol)[0];

				}
			}
			result.at<Vec3b>(row,col)[2] = sumRed;
			result.at<Vec3b>(row,col)[1] = sumGreen;
			result.at<Vec3b>(row,col)[0] = sumBlue;
		}
	}
}


void downSampleFunc(int win_size, float sigma, Mat& src, float** arr, Mat& result)
{
	genGaussian(win_size,sigma,arr);
	int width = src.cols;
	int height = src.rows;
	int ow = width/2;  
	int oh = height/2;  
	result.create(Size(ow,oh),src.type());

	int inRow=0, inCol = 0;  		
	for(int row=0; row<oh; row++) 
	{  
		for(int col=0; col<ow; col++) 
		{  
			inRow = 2* row;  
			inCol = 2* col;  
			if(inRow >= height) 
			{  
				inRow = height;  
			}  
			if(inCol >= width) 
			{  
				inCol = width;  
			}  

			float sumRed = 0, sumGreen = 0, sumBlue = 0;  
			for(int subRow = -win_size; subRow <= win_size; subRow++) 
			{  
				int inRowOff = inRow + subRow;  
				if(inRowOff >= height || inRowOff < 0) 
				{  
					inRowOff = 0;  
				}  
				for(int subCol = -win_size; subCol <= win_size; subCol++) 
				{  
					int inColOff = inCol + subCol;  
					if(inColOff >= width || inColOff < 0) 
					{  
						inColOff = 0;  
					}  

					int red = src.at<Vec3b>(inRowOff,inColOff)[2];
					int green = src.at<Vec3b>(inRowOff,inColOff)[1];
					int blue = src.at<Vec3b>(inRowOff,inColOff)[0];
					sumRed += arr[subRow + win_size][subCol + win_size] * red;  
					sumGreen += arr[subRow + win_size][subCol + win_size] * green;  
					sumBlue += arr[subRow + win_size][subCol + win_size] * blue;  

				}  
			}  
			result.at<Vec3b>(row,col)[2] = sumRed;
			result.at<Vec3b>(row,col)[1] = sumGreen;
			result.at<Vec3b>(row,col)[0] = sumBlue;
		}  
	}
}

void expendSampleFunc(int win_size, Mat& src, float** arr, Mat& result)
{
	int width = src.cols;
	int height = src.rows;
	int ow = 2*width;  
	int oh =2*height; 
	result.create(Size(ow,oh),src.type());
	for(int row=0; row<oh; row++) 
	{  
		for(int col=0; col<ow; col++) 
		{  
			float sumRed = 0, sumGreen = 0, sumBlue = 0;  
			for(int subRow = -win_size; subRow <= win_size; subRow++) 
			{  
				double srcRow = (row + subRow)/2.0;  
				double j = floor(srcRow);  
				double t = srcRow - j;   
				if(t > 0) 
				{  
					continue;  
				}  
				if(srcRow >= height || srcRow < 0) 
				{  
					srcRow = 0;  
				}  
				for(int subCol = -win_size; subCol <= win_size; subCol++) 
				{  
					double srcCol = (col + subCol)/2.0;  
					j = floor(srcCol);  
					t = srcCol - j;  
					if(t > 0) 
					{  
						continue;  
					}  
					if(srcCol >= width || srcCol < 0) 
					{  
						srcCol = 0;  
					}   

					int red = src.at<Vec3b>(srcRow,srcCol)[2];
					int green = src.at<Vec3b>(srcRow,srcCol)[1];
					int blue = src.at<Vec3b>(srcRow,srcCol)[0];
					sumRed += arr[subRow + win_size][subCol + win_size] * red;  
					sumGreen += arr[subRow + win_size][subCol + win_size] * green;  
					sumBlue += arr[subRow + win_size][subCol + win_size] * blue;  
				}  
			}  
			result.at<Vec3b>(row,col)[2] = sumRed;
			result.at<Vec3b>(row,col)[1] = sumGreen;
			result.at<Vec3b>(row,col)[0] = sumBlue;
		}  
	}   
}

void printMat(Mat result)
{
	for (int i = 129 ;i < 135; i++)
	{
		for (int j = 69 ;j < 75;j++)
		{
			printf("%d,%d,%d  ",result.at<Vec3b>(i,j)[2],result.at<Vec3b>(i,j)[1],result.at<Vec3b>(i,j)[0]);
		}
		printf("\n");
	}
}

int main(int argc, char** argv)
{
	const char* filename = argc >= 2 ? argv[1] : "hello3.jpg";
	Mat src = imread(filename,1);

	if(src.empty())
	{
		cout << "can not open " << filename << endl;
		return -1;
	}
	Mat dst;

	namedWindow("hello");
	imshow("hello",src);

	src.copyTo(dst);
	int width = src.cols;  
	int height = src.rows;  

	int octave = 2;
	int s = 4;
	float k = pow(2,1.0/s);

	int win_size;
	float sigma ;
	float** arr;
	double sigma2;  
	double sigma4;

	win_size = 1;
	sigma = 1;

	sigma2 = sigma * sigma;  
	sigma4 = sigma2 * sigma2;  
	arr = new float*[2*win_size+1];
	for (int i = 0;i< 2*win_size+1;i++)
	{
		arr[i] = new float[2*win_size+1];

		for (int j = 0 ;j < 2*win_size+1;j++)
		{
			arr[i][j] = 0; 
		}
	}
	vector<Mat>firstSampleArr;	
	vector<Mat>secondSampleArr;

	Mat firstSample, secondSample;
	gaussianblurFunc(win_size, sigma,src, arr, firstSample);
	firstSampleArr.push_back(firstSample);
	for (int j = 0 ;j<s ;j++)
	{
		Mat firstSample1;		
		gaussianblurFunc(win_size, pow(k,1)*sigma,firstSampleArr[j], arr, firstSample1);	
		firstSampleArr.push_back(firstSample1);
	}
	downSampleFunc(win_size,pow(k,1)*sigma, firstSampleArr[s-1], arr, secondSample);
	secondSampleArr.push_back(secondSample);
	for (int j = 0 ;j<s ;j++)
	{
		Mat secondSample1;	
		gaussianblurFunc(win_size, pow(k,1)*sigma,secondSampleArr[j], arr, secondSample1);
		secondSampleArr.push_back(secondSample1);
	}


	Mat result ;
	result.create(Size(firstSampleArr[0].cols,firstSampleArr[0].rows),secondSampleArr[0].type());
	for (int i = 0 ;i < firstSampleArr[0].rows;i++ )
	{
		for (int j = 0; j< firstSampleArr[0].cols; j++)
		{
			int temp1 = firstSampleArr[1].at<Vec3b>(i,j)[2] - firstSampleArr[0].at<Vec3b>(i,j)[2];
			int temp2 = firstSampleArr[1].at<Vec3b>(i,j)[1] - firstSampleArr[0].at<Vec3b>(i,j)[1];
			int temp3 = firstSampleArr[1].at<Vec3b>(i,j)[0] - firstSampleArr[0].at<Vec3b>(i,j)[0];
			result.at<Vec3b>(i,j)[2] = temp1<0?0:temp1+50;
			result.at<Vec3b>(i,j)[1] = temp2<0?0:temp2+50;
			result.at<Vec3b>(i,j)[0] = temp3<0?0:temp3+50;
		}
	}
	namedWindow("hello2");
	imshow("hello2",firstSampleArr[0]);
	namedWindow("hello21");
	imshow("hello21",firstSampleArr[3]);

	namedWindow("hello3");
	imshow("hello3",secondSampleArr[0]);

	namedWindow("hello4");
	imshow("hello4",result);

	waitKey(0);

	return 0;
}