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

	for (int i = 0 ; i<octaveSize; i++)
	{
		vector<Mat> tempVector;
		for(int j = 0; j< levelSize; j++)
		{
			Mat temp ;
			tempVector.push_back(temp);
		}
		pyramidImage.push_back(tempVector);
	}
}

GassianPyramid::~GassianPyramid()
{

}

void GassianPyramid::genGassianFunc(float sigmaValue,int winSize)
{	
	float arrSum = 0;
	sigma = sigmaValue;
	win_size = winSize;
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
	printf("\n");
	for (int i = -win_size ; i <= win_size; i++)
	{
		for (int j = -win_size ; j<= win_size; j++)
		{
			arr[i+win_size][j+win_size] /= arrSum;
			arr[i+win_size][j+win_size] *= 256;
			printf("%f ",arr[i+win_size][j+win_size]);
		}
		printf("\n");
	}
}

void GassianPyramid::gassianBlur(float sigma,int winSize, Mat src, Mat& result)
{
	//genGassianFunc(sigma,winSize);
	float arr[5][5]={1,4,6,4,1,4,16,24,16,4,6,24,36,24,6,4,16,24,16,4,1,4,6,4,1};
	for (int i = 0;i<5;i++)
	{
		for (int j = 0; j<5; j++)
		{
			arr[i][j] /=64;
		}
	}

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

void GassianPyramid::gassianBlur2(float sigma,int winSize, Mat src, Mat& result)
{
	//genGassianFunc(sigma,winSize);
	double *kernel = new double[2*winSize+1];
	double scale = -0.5/(sigma*sigma);  
	const double PI = 3.141592653;  
	double cons = 1/sqrt(-scale / PI); 
	double sum = 0;

	for (int i = 0; i<= 2*winSize+1; i++)
	{
		kernel[i] = 0;
	}

	for (int j = -winSize; j<=win_size; j++)
	{
		kernel[j+win_size] = cons * exp(j * j * scale);
		sum += kernel[j+win_size];
	}

	for(int j = -winSize; j<=win_size; j++)  
	{  
		kernel[j+win_size] /= sum;  
		//kernel[j+win_size] *= 4;
		printf("%f ",kernel[j+win_size]);
	}

	Mat temp;
	temp.create(Size(src.cols,src.rows),src.type());
	result.create(Size(src.cols,src.rows),src.type());


	for (int row = 0 ;row <src.rows ;row++)//x orientation
	{
		for (int col = 0 ; col <src.cols; col++)
		{
			float sumRed = 0,sumGreen = 0,sumBlue = 0;
			for (int subcol = -win_size;subcol<=win_size;subcol++)
			{
				int srccol = col+subcol;
				if (srccol<0)
				{
					srccol *= -1;
				}
				if (srccol>=src.cols)
				{
					srccol = src.cols*2 - srccol - 2;
				}

				sumRed += kernel[subcol+win_size]*src.at<Vec3b>(row,srccol)[2];
				sumGreen += kernel[subcol+win_size]*src.at<Vec3b>(row,srccol)[1];
				sumBlue += kernel[subcol+win_size]*src.at<Vec3b>(row,srccol)[0];


			}
			temp.at<Vec3b>(row,col)[2] = sumRed;
			temp.at<Vec3b>(row,col)[1] = sumGreen;
			temp.at<Vec3b>(row,col)[0] = sumBlue;
		}
	}

	for (int row = 0 ;row <src.rows ;row++)//y orientation
	{
		for (int col = 0 ; col <src.cols; col++)
		{
			float sumRed = 0,sumGreen = 0,sumBlue = 0;
			for (int subrow = -win_size;subrow<=win_size;subrow++)
			{
				int srcrow = row+subrow;
				if (srcrow<0)
				{
					srcrow *= -1;
				}
				if (srcrow>=src.rows)
				{
					srcrow = src.rows*2 - srcrow - 2;;
				}
				sumRed += kernel[subrow+win_size]*temp.at<Vec3b>(srcrow,col)[2];
				sumGreen += kernel[subrow+win_size]*temp.at<Vec3b>(srcrow,col)[1];
				sumBlue += kernel[subrow+win_size]*temp.at<Vec3b>(srcrow,col)[0];
			}
			result.at<Vec3b>(row,col)[2] = sumRed;
			result.at<Vec3b>(row,col)[1] = sumGreen;
			result.at<Vec3b>(row,col)[0] = sumBlue;
		}
	}


}

void GassianPyramid::gassianBlur3(float sigma,int winSize, Mat src, Mat& result)
{
	double *kernel = new double[2*winSize+1];
	double scale = -0.5/(sigma*sigma);  
	const double PI = 3.141592653;  
	double cons = 1/sqrt(-scale / PI); 
	double sum = 0;

	for (int i = 0; i<= 2*winSize+1; i++)
	{
		kernel[i] = 0;
	}

	for (int j = -winSize; j<=win_size; j++)
	{
		kernel[j+win_size] = cons * exp(j * j * scale);
		sum += kernel[j+win_size];
	}

	for(int j = -winSize; j<=win_size; j++)  
	{  
		kernel[j+win_size] /= sum;  
		printf("%f ",kernel[j+win_size]);
	}

	Mat temp;
	temp.create(Size(src.cols,src.rows),src.type());
	result.create(Size(src.cols,src.rows),src.type());

	for (int row = 0 ;row <src.rows ;row++)//y orientation
	{
		for (int col = 0 ; col <src.cols; col++)
		{
			float sumRed = 0,sumGreen = 0,sumBlue = 0;
			for (int subrow = -win_size;subrow<=win_size;subrow++)
			{
				int srcrow = row+subrow;
				//if (srcrow<0||srcrow>=src.rows)
				//{
				//	srcrow = row;
				//}
				if (srcrow<0)
				{
					srcrow *= -1;
				}
				if (srcrow>=src.rows)
				{
					srcrow = (src.rows - 1) - (srcrow - (src.rows-1));
				}

				sumRed += kernel[subrow+win_size]*src.at<Vec3b>(srcrow,col)[2];
				sumGreen += kernel[subrow+win_size]*src.at<Vec3b>(srcrow,col)[1];
				sumBlue += kernel[subrow+win_size]*src.at<Vec3b>(srcrow,col)[0];

			}
			temp.at<Vec3b>(row,col)[2] = sumRed;
			temp.at<Vec3b>(row,col)[1] = sumGreen;
			temp.at<Vec3b>(row,col)[0] = sumBlue;
		}
	}

	for (int row = 0 ;row <src.rows ;row++)//x orientation
	{
		for (int col = 0 ; col <src.cols; col++)
		{
			float sumRed = 0,sumGreen = 0,sumBlue = 0;
			for (int subcol = -win_size;subcol<=win_size;subcol++)
			{
				int srccol = col+subcol;

				if (srccol<0)
				{
					srccol *= -1;
				}
				if (srccol>=src.cols)
				{
					srccol = (src.cols - 1) - (srccol - (src.cols-1));
				}
				sumRed += kernel[subcol+win_size]*temp.at<Vec3b>(row,srccol)[2];
				sumGreen += kernel[subcol+win_size]*temp.at<Vec3b>(row,srccol)[1];
				sumBlue += kernel[subcol+win_size]*temp.at<Vec3b>(row,srccol)[0];


			}
			result.at<Vec3b>(row,col)[2] = sumRed;
			result.at<Vec3b>(row,col)[1] = sumGreen;
			result.at<Vec3b>(row,col)[0] = sumBlue;
		}
	}




}

void GassianPyramid::downSampleFunc(Mat src, Mat& result)
{
	int width = src.cols;
	int height = src.rows;
	int ow = width/2;  
	int oh = height/2;  
	result.create(Size(ow,oh),src.type());

	float tempArr[5][5]={1,4,6,4,1,4,16,24,16,4,6,24,36,24,6,4,16,24,16,4,1,4,6,4,1};
	for (int i = 0;i<5;i++)
	{
		for (int j = 0; j<5; j++)
		{
			tempArr[i][j] /=256;
		}
	}
	Mat temp;
	temp.create(Size(src.cols,src.rows),src.type());
	for (int row = 0 ;row <src.rows ;row++)
	{
		for (int col = 0 ; col <src.cols; col++)
		{
			float sumRed = 0,sumGreen = 0,sumBlue = 0;
			for (int subrow = -win_size;subrow<=win_size;subrow++)
			{
				int srcrow = row+subrow;
				//if (srcrow<0||srcrow>=src.rows)
				//{
				//	srcrow = row;
				//}
				if (srcrow<0)
				{
					srcrow *= -1;
				}
				if (srcrow>=src.rows)
				{
					srcrow = (src.rows - 1) - (srcrow - (src.rows-1));
				}
				for (int subcol = -win_size;subcol<=win_size;subcol++)
				{
					int srccol = col+subcol;
					//if (srccol<0||srccol>=src.cols)
					//{
					//	srccol = col;
					//}
					if (srccol<0)
					{
						srccol *= -1;
					}
					if (srccol>=src.cols)
					{
						srccol = (src.cols - 1) - (srccol - (src.cols-1));
					}

					sumRed += tempArr[subrow+win_size][subcol+win_size]*src.at<Vec3b>(srcrow,srccol)[2];
					sumGreen += tempArr[subrow+win_size][subcol+win_size]*src.at<Vec3b>(srcrow,srccol)[1];
					sumBlue += tempArr[subrow+win_size][subcol+win_size]*src.at<Vec3b>(srcrow,srccol)[0];
				}
			}
			temp.at<Vec3b>(row,col)[2] = sumRed;
			temp.at<Vec3b>(row,col)[1] = sumGreen;
			temp.at<Vec3b>(row,col)[0] = sumBlue;
		}
	}




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
			result.at<Vec3b>(row,col)[2]= temp.at<Vec3b>(inRow,inCol)[2];
			result.at<Vec3b>(row,col)[1]= temp.at<Vec3b>(inRow,inCol)[1];
			result.at<Vec3b>(row,col)[0]= temp.at<Vec3b>(inRow,inCol)[0];
			//float sumRed = 0, sumGreen = 0, sumBlue = 0;  
			//for(int subRow = -win_size; subRow <= win_size; subRow++) 
			//{  
			//	int inRowOff = inRow + subRow;  
			//	if(inRowOff >= height || inRowOff < 0) 
			//	{  
			//		inRowOff = 0;  
			//	}  
			//	for(int subCol = -win_size; subCol <= win_size; subCol++) 
			//	{  
			//		int inColOff = inCol + subCol;  
			//		if(inColOff >= width || inColOff < 0) 
			//		{  
			//			inColOff = 0;  
			//		}  

			//		int red = src.at<Vec3b>(inRowOff,inColOff)[2];
			//		int green = src.at<Vec3b>(inRowOff,inColOff)[1];
			//		int blue = src.at<Vec3b>(inRowOff,inColOff)[0];
			//		sumRed += arr[subRow + win_size][subCol + win_size] * red;  
			//		sumGreen += arr[subRow + win_size][subCol + win_size] * green;  
			//		sumBlue += arr[subRow + win_size][subCol + win_size] * blue;  

			//	}  
			//}  
			//result.at<Vec3b>(row,col)[2] = sumRed;
			//result.at<Vec3b>(row,col)[1] = sumGreen;
			//result.at<Vec3b>(row,col)[0] = sumBlue;
		}  
	}
}

void GassianPyramid::expendSampleFunc(Mat src, Mat& result)
{
	int width = src.cols;
	int height = src.rows;
	int ow = 2*width;  
	int oh =2*height; 
	Mat temp;
	temp.create(Size(ow,oh),src.type());
	
	result.create(Size(ow,oh),src.type());
	for(int row=0; row<oh; row++) 
	{  
		for(int col=0; col<ow; col++) 
		{  
			int inRow = row/2;  
			int inCol = col/2;

			if(row - inRow*2 > 0 || col - inCol*2 > 0) 
			{  
				temp.at<Vec3b>(row,col)[2] = 0;
				temp.at<Vec3b>(row,col)[1] = 0;
				temp.at<Vec3b>(row,col)[0] = 0;
				continue;
			} 

			temp.at<Vec3b>(row,col)[2] = src.at<Vec3b>(inRow,inCol)[2];
			temp.at<Vec3b>(row,col)[1] = src.at<Vec3b>(inRow,inCol)[1];
			temp.at<Vec3b>(row,col)[0] = src.at<Vec3b>(inRow,inCol)[0];
		}  
	}  

	float tempArr[5][5]={1,4,6,4,1,4,16,24,16,4,6,24,36,24,6,4,16,24,16,4,1,4,6,4,1};
	for (int i = 0;i<5;i++)
	{
		for (int j = 0; j<5; j++)
		{
			tempArr[i][j] /=64;
		}
	}
	//Mat temp;
	//temp.create(Size(src.cols,src.rows),src.type());
	for (int row = 0 ;row <temp.rows ;row++)
	{
		for (int col = 0 ; col <temp.cols; col++)
		{
			float sumRed = 0,sumGreen = 0,sumBlue = 0;
			for (int subrow = -win_size;subrow<=win_size;subrow++)
			{
				int srcrow = row+subrow;
				//if (srcrow<0||srcrow>=src.rows)
				//{
				//	srcrow = row;
				//}
				if (srcrow<0)
				{
					srcrow *= -1;
				}
				if (srcrow>=temp.rows)
				{
					srcrow = (temp.rows - 1) - (srcrow - (temp.rows-1));
				}
				for (int subcol = -win_size;subcol<=win_size;subcol++)
				{
					int srccol = col+subcol;
					//if (srccol<0||srccol>=src.cols)
					//{
					//	srccol = col;
					//}
					if (srccol<0)
					{
						srccol *= -1;
					}
					if (srccol>=temp.cols)
					{
						srccol = (temp.cols - 1) - (srccol - (temp.cols-1));
					}

					sumRed += tempArr[subrow+win_size][subcol+win_size]*temp.at<Vec3b>(srcrow,srccol)[2];
					sumGreen += tempArr[subrow+win_size][subcol+win_size]*temp.at<Vec3b>(srcrow,srccol)[1];
					sumBlue += tempArr[subrow+win_size][subcol+win_size]*temp.at<Vec3b>(srcrow,srccol)[0];
				}
			}
			result.at<Vec3b>(row,col)[2] = sumRed;
			result.at<Vec3b>(row,col)[1] = sumGreen;
			result.at<Vec3b>(row,col)[0] = sumBlue;
		}
	}


	//for (int row = 0 ;row <temp.rows ;row++)
	//{
	//	for (int col = 0 ; col <temp.cols; col++)
	//	{
	//		float sumRed = 0,sumGreen = 0,sumBlue = 0;
	//		for (int subrow = -win_size;subrow<=win_size;subrow++)
	//		{
	//			int srcrow = row+subrow;
	//			if (srcrow<0||srcrow>=temp.rows)
	//			{
	//				srcrow = row;
	//			}
	//			for (int subcol = -win_size;subcol<=win_size;subcol++)
	//			{
	//				int srccol = col+subcol;
	//				if (srccol<0||srccol>=temp.cols)
	//				{
	//					srccol = col;
	//				}
	//				sumRed += arr[subrow+win_size][subcol+win_size]*temp.at<Vec3b>(srcrow,srccol)[2];
	//				sumGreen += arr[subrow+win_size][subcol+win_size]*temp.at<Vec3b>(srcrow,srccol)[1];
	//				sumBlue += arr[subrow+win_size][subcol+win_size]*temp.at<Vec3b>(srcrow,srccol)[0];

	//			}
	//		}
	//		result.at<Vec3b>(row,col)[2] = sumRed;
	//		result.at<Vec3b>(row,col)[1] = sumGreen;
	//		result.at<Vec3b>(row,col)[0] = sumBlue;
	//	}
	//}
}

void GassianPyramid::printMat(Mat result)
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

void GassianPyramid::createPyramid(Mat src)
{
	gassianBlur(sigma,1,src,pyramidImage[0][0]);
	for (int i = 0; i<octave; i++)
	{
		
		for (int j = 0; j<s-1; j++)
		{
			gassianBlur(pow(k,j+1)*sigma,1,pyramidImage[i][0],pyramidImage[i][j+1]);
		}
		if (i < octave - 1)
		{
			Mat temp;
			gassianBlur(sigma,1,pyramidImage[i][s-1],temp);
			downSampleFunc(temp,pyramidImage[i+1][0]);
		}

	}
}

void GassianPyramid::getDoG(Mat src1, Mat src2, Mat& result)
{
	result.create(Size(src1.cols,src1.rows),src1.type());
	for (int i = 0 ;i < src1.rows;i++ )
	{
		for (int j = 0; j< src1.cols; j++)
		{
			int temp1 = src2.at<Vec3b>(i,j)[2] - src1.at<Vec3b>(i,j)[2];
			int temp2 = src2.at<Vec3b>(i,j)[1] - src1.at<Vec3b>(i,j)[1];
			int temp3 = src2.at<Vec3b>(i,j)[0] - src1.at<Vec3b>(i,j)[0];
			result.at<Vec3b>(i,j)[2] = temp1<0?0:temp1+50;
			result.at<Vec3b>(i,j)[1] = temp2<0?0:temp2+50;
			result.at<Vec3b>(i,j)[0] = temp3<0?0:temp3+50;
		}
	}
}