#include "gassianPyramid.h"

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


	/*	getGaussianKernel( int n, double sigma, int ktype )  
	{ */ 

		//int n = 3;
		//double sigma = 1;
		//int ktype = CV_32F;
		//const int SMALL_GAUSSIAN_SIZE = 7;  
		//static const float small_gaussian_tab[][SMALL_GAUSSIAN_SIZE] =  
		//{  
		//	{1.f},  
		//	{0.25f, 0.5f, 0.25f},  
		//	{0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f},  
		//	{0.03125f, 0.109375f, 0.21875f, 0.28125f, 0.21875f, 0.109375f, 0.03125f}  
		//};  

		//const float* fixed_kernel = n % 2 == 1 && n <= SMALL_GAUSSIAN_SIZE && sigma <= 0 ?  
		//	small_gaussian_tab[n>>1] : 0;  

		//CV_Assert( ktype == CV_32F || ktype == CV_64F );  
		//Mat kernel(n, 1, ktype);  
		//float* cf = (float*)kernel.data;  
		//double* cd = (double*)kernel.data;  

		//double sigmaX = sigma > 0 ? sigma : ((n-1)*0.5 - 1)*0.3 + 0.8;  
		//double scale2X = -0.5/(sigmaX*sigmaX);  
		//double sum = 0;  

		//int i;  
		//for( i = 0; i < n; i++ )  
		//{  
		//	double x = i - (n-1)*0.5;  
		//	double t = fixed_kernel ? (double)fixed_kernel[i] : std::exp(scale2X*x*x);  
		//	if( ktype == CV_32F )  
		//	{  
		//		cf[i] = (float)t;  
		//		sum += cf[i];  
		//	}  
		//	else  
		//	{  
		//		cd[i] = t;  
		//		sum += cd[i];  
		//	}  
		//}  

		//sum = 1./sum;  
		//for( i = 0; i < n; i++ )  
		//{  
		//	if( ktype == CV_32F )  
		//	{
		//		cf[i] = (float)(cf[i]*sum);  
		//		printf("%f ",cf[i]);
		//	}
		//	else 
		//	{
		//		cd[i] *= sum;  
		//		printf("%f ",cd[i]);
		//	}
		//	
		//}  
		//printf("\n");


	//	return kernel;  
	//}  

	//GassianPyramid gp(2,4,1,1);
	//gp.createPyramid(src);

	//imshow("hello1",src);
	//imshow("hello2",gp.pyramidImage[0][0]);
	//imshow("hello3",gp.pyramidImage[0][1]);
	//imshow("hello4",gp.pyramidImage[1][0]);
	//imshow("hello5",gp.pyramidImage[1][1]);

	//Mat result;
	//gp.getDoG(gp.pyramidImage[0][2],gp.pyramidImage[0][3],result);

	//Mat srcM(4,4, CV_8UC3, Scalar(10,20,30)); 

	//for (int i = 0; i< src.rows; i++)
	//{
	//	for (int j = 0; j<src.cols; j++)
	//	{
	//		src.at<Vec3b>(i,j)[0] = i+j;
	//		src.at<Vec3b>(i,j)[1] = i+j;
	//		src.at<Vec3b>(i,j)[2] = i+j;
	//	}
	//}

	//Mat srcM = (Mat_<double>(4,3) << 1,2,3,1,0,0,0,0,1,0,1,0);
	//Mat dst;
	//cout <<srcM<<endl;
	GaussianBlur(src,dst,Size(3,3),1,1);
	//cout <<dst<<endl;
	//imshow("dst",dst);

	Mat temp, downSampleMat, expandMat;
	
	GassianPyramid gp2(2,4,1,1);

	//gp2.gassianBlur(1,1,src,dst);
	//cout<<src<<endl;
	//gp2.gassianBlur2(1,1,src,temp);
	//cout <<endl;
	gp2.gassianBlur3(1,1,src,temp);
	cout <<endl;
	cout<<temp - dst<<endl;
	//imshow("temp",temp);
	//cout<<dst-temp<<endl;
	//imshow("diff",dst-temp);
	//gp2.downSampleFunc(src,downSampleMat);
	//gp2.expendSampleFunc(downSampleMat,expandMat);
	//gp2.gassianBlur(1.6,2,temp,expandMat);
	//imshow("result",expandMat);

	//want to know the method of pyrdown and pyrup
	//pyrDown(src,temp,Size(src.cols/2, src.rows/2));
	//pyrUp(temp,expandMat,Size( temp.cols*2, temp.rows*2 ));
	//imshow("result",src - expandMat);

	//imshow("result2",result);
	waitKey(0);

	return 0;
}