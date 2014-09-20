#include "gassianPyramid.h"

GassianPyramid::GassianPyramid(int octaveSize, int levelSize,int winSize,float sigmaValue)
{
	octave = octaveSize;
	s = levelSize;
	win_size = winSize;
	sigma = sigmaValue;
	k = pow(2,1.0/s);

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
}

GassianPyramid::~GassianPyramid()
{

}

void GassianPyramid::genGassianFunc()
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

void GassianPyramid::gassianBlur(Mat& src, Mat& result)
{
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