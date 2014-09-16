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

	for (int i = -win_size ; i <= win_size; i++)
	{
		for (int j = -win_size ; j<= win_size; j++)
		{
			int r = i*i + j*j;
			float k = -r/(2*sigma*sigma);
			arr[i+win_size][j+win_size] = exp(k);
		}
	}


	//private BufferedImage pyramidReduce(BufferedImage src) {  

	Mat hello ;
		
	int ow = width/2;  
	int oh = height/2;  
	hello.create(Size(ow,oh),src.type());
	hello.at<Vec3b>(y,x)[c];

	int inRow=0, inCol = 0, index = 0, oudex =0, ta = 0;  		
	for(int row=0; row<oh; row++) 
	{  
		for(int col=0; col<ow; col++) 
		{  
			inRow = 2* row;  
			inCol = 2* col;  
			if(inRow >= height) 
			{  
				inRow = 0;  
			}  
			if(inCol >= width) 
			{  
				inCol = 0;  
			}  

			float sumRed = 0, sumGreen = 0, sumBlue = 0;  
			for(int subRow = -2; subRow <= 2; subRow++) 
			{  
				int inRowOff = inRow + subRow;  
				if(inRowOff >= height || inRowOff < 0) 
				{  
					inRowOff = 0;  
				}  
				for(int subCol = -2; subCol <= 2; subCol++) 
				{  
					int inColOff = inCol + subCol;  
					if(inColOff >= width || inColOff < 0) 
					{  
						inColOff = 0;  
					}  

					int red = src.at<Vec3b>[0](inRowOff,inColOff);
					int green = src.at<Vec3b>[1](inRowOff,inColOff);
					int blue = src.at<Vec3b>[2](inRowOff,inColOff);
					sumRed += keneralData[subRow + 2][subCol + 2] * red;  
					sumGreen += keneralData[subRow + 2][subCol + 2] * green;  
					sumBlue += keneralData[subRow + 2][subCol + 2] * blue;  
 
				}  
			}  

			oudex = row * ow + col;  
			outPixels[oudex] = (ta << 24) | (clamp(sumRed) << 16) | (clamp(sumGreen) << 8) | clamp(sumBlue);  
		}  
	}  



	return 0;
}