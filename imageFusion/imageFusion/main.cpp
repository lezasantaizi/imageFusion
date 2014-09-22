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

	//namedWindow("hello");
	//imshow("hello",src);

	src.copyTo(dst);

	//GassianPyramid gp(2,4,1,1);
	//gp.createPyramid(src);

	//imshow("hello1",src);
	//imshow("hello2",gp.pyramidImage[0][0]);
	//imshow("hello3",gp.pyramidImage[0][1]);
	//imshow("hello4",gp.pyramidImage[1][0]);
	//imshow("hello5",gp.pyramidImage[1][1]);

	//Mat result;
	//gp.getDoG(gp.pyramidImage[0][2],gp.pyramidImage[0][3],result);

	Mat temp, downSampleMat, expandMat;
	GassianPyramid gp2(2,4,2,1.6);
	//gp2.gassianBlur(1.6,2,src,temp);
	
	//gp2.downSampleFunc(src,downSampleMat);
	//gp2.expendSampleFunc(downSampleMat,expandMat);
	//gp2.gassianBlur(1.6,2,temp,expandMat);
	//imshow("result",expandMat);

	//want to know the method of pyrdown and pyrup
	pyrDown(src,temp,Size(src.cols/2, src.rows/2));
	pyrUp(temp,expandMat,Size( temp.cols*2, temp.rows*2 ));
	imshow("result",src - expandMat);

	//imshow("result2",result);
	waitKey(0);

	return 0;
}