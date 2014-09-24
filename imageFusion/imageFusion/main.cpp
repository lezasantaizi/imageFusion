#include "gassianPyramid.h"

#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")
#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249.lib")
#pragma comment(lib, "opencv_imgproc249.lib")
#pragma comment(lib, "opencv_core249.lib")

int main(int argc, char** argv)
{
	const char* filename = argc >= 2 ? argv[1] : "left4.jpg";
	Mat src = imread(filename,1);

	if(src.empty())
	{
		cout << "can not open " << filename << endl;
		return -1;
	}
	Mat dst;

	//namedWindow("hello");
	//imshow("hello",src);

	//src.copyTo(dst);
	Mat temp, downSampleMat, expandMat;
	//
	GassianPyramid gp2(2,4);
	//gp2.createPyramid(src);
	//imshow("hello1",gp2.pyramidImage[0][0] - gp2.pyramidImage[0][1]);
	//imshow("hello2",gp2.pyramidImage[0][1] - gp2.pyramidImage[0][2]);
	//imshow("hello3",gp2.pyramidImage[1][0] - gp2.pyramidImage[1][1]);
	////gp2.gassianBlur(1,1,src,dst);
	////cout<<src<<endl;
	////gp2.gassianBlur2(1,1,src,temp);
	////cout <<endl;
	////gp2.gassianBlur3(1,2,src,temp);
	////gp2.downSampleFunc(src,dst);
	//gp2.genGassianFunc(1,2);
	//gp2.expendSampleFunc(src,expandMat,Size( src.cols*2+1, src.rows*2+1 ));


	//want to know the method of pyrdown and pyrup
	//Mat srcM = (sMat_<double>(2,2) << 1,0,1,0);//,0,0,0,0,1,0,1,0);
	//pyrDown(src,downSampleMat,Size(src.cols/2, src.rows/2));
	src.at<Vec3b>(0,0)[0] = 1;
	src.at<Vec3b>(0,0)[1] = 1;
	src.at<Vec3b>(0,0)[2] = 0;
	pyrUp(src,temp,Size( src.cols*2+1, src.rows*2+1 ));
	//imshow("hello",src - temp+50);
	cout<< src <<endl<< temp <<endl;
	waitKey(0);



	//Mat l8u = imread("left1.jpg");  
	//Mat r8u = imread("right1.jpg");  
	//Mat mask(l8u.rows,l8u.cols,CV_8UC1, Scalar(0,0,0));                 //将m全部赋值为0  
	//mask(Range::all(),Range(0,mask.cols/2)) = 1;
	//GassianPyramid gp2(4,2);
	//gp2.pyramidImage[0][0] = l8u;
	//gp2.pyramidImage[0][1] = r8u;
	//Mat temp1,temp2;

	//gp2.downSampleFunc(gp2.pyramidImage[0][0],gp2.pyramidImage[1][0]);
	//gp2.expendSampleFunc(gp2.pyramidImage[1][0],temp1);
	//gp2.pyramidImage[0][0] = gp2.pyramidImage[0][0] - temp1;

	//gp2.downSampleFunc(gp2.pyramidImage[0][1],gp2.pyramidImage[1][1]);
	//gp2.expendSampleFunc(gp2.pyramidImage[1][1],temp2);
	//gp2.pyramidImage[0][1] = gp2.pyramidImage[0][1] - temp2;

	//gp2.downSampleFunc(gp2.pyramidImage[1][0],gp2.pyramidImage[2][0]);
	//gp2.expendSampleFunc(gp2.pyramidImage[2][0],temp1);
	//gp2.pyramidImage[1][0] = gp2.pyramidImage[1][0] - temp1;

	//gp2.downSampleFunc(gp2.pyramidImage[1][1],gp2.pyramidImage[2][1]);
	//gp2.expendSampleFunc(gp2.pyramidImage[2][1],temp2);
	//gp2.pyramidImage[1][1] = gp2.pyramidImage[1][1] - temp2;

	//gp2.downSampleFunc(gp2.pyramidImage[2][0],gp2.pyramidImage[3][0]);
	//gp2.expendSampleFunc(gp2.pyramidImage[3][0],temp1);
	//gp2.pyramidImage[2][0] = gp2.pyramidImage[2][0] - temp1;

	//gp2.downSampleFunc(gp2.pyramidImage[2][1],gp2.pyramidImage[3][1]);
	//gp2.expendSampleFunc(gp2.pyramidImage[3][1],temp2);
	//gp2.pyramidImage[2][1] = gp2.pyramidImage[2][1] - temp2;

	//imshow("diff1",gp2.pyramidImage[0][0]);
	//imshow("diff1",gp2.pyramidImage[0][1]);
	//return 0;
}



//class LaplacianBlending {  
//private:  
//    Mat_<Vec3f> left;  
//    Mat_<Vec3f> right;  
//    Mat_<float> blendMask;  
//  
//    vector<Mat_<Vec3f> > leftLapPyr,rightLapPyr,resultLapPyr;//Laplacian Pyramids  
//    Mat leftHighestLevel, rightHighestLevel, resultHighestLevel;  
//    vector<Mat_<Vec3f> > maskGaussianPyramid; //masks are 3-channels for easier multiplication with RGB  
//  
//    int levels;  
//  
//    void buildPyramids() {  
//        buildLaplacianPyramid(left,leftLapPyr,leftHighestLevel);  
//        buildLaplacianPyramid(right,rightLapPyr,rightHighestLevel);  
//        buildGaussianPyramid();  
//    }  
//  
//    void buildGaussianPyramid() {//金字塔内容为每一层的掩模  
//        assert(leftLapPyr.size()>0);  
//  
//        maskGaussianPyramid.clear();  
//        Mat currentImg;  
//        cvtColor(blendMask, currentImg, CV_GRAY2BGR);//store color img of blend mask into maskGaussianPyramid  
//        maskGaussianPyramid.push_back(currentImg); //0-level  
//  
//        currentImg = blendMask;  
//        for (int l=1; l<levels+1; l++) {  
//            Mat _down;  
//            if (leftLapPyr.size() > l)  
//                pyrDown(currentImg, _down, leftLapPyr[l].size());  
//            else  
//                pyrDown(currentImg, _down, leftHighestLevel.size()); //lowest level  
//  
//            Mat down;  
//            cvtColor(_down, down, CV_GRAY2BGR);  
//            maskGaussianPyramid.push_back(down);//add color blend mask into mask Pyramid  
//            currentImg = _down;  
//        }  
//    }  
//  
//    void buildLaplacianPyramid(const Mat& img, vector<Mat_<Vec3f> >& lapPyr, Mat& HighestLevel) {  
//        lapPyr.clear();  
//        Mat currentImg = img;  
//        for (int l=0; l<levels; l++) {  
//            Mat down,up;  
//            pyrDown(currentImg, down);  
//            pyrUp(down, up,currentImg.size());  
//            Mat lap = currentImg - up;  
//            lapPyr.push_back(lap);  
//            currentImg = down;  
//        }  
//        currentImg.copyTo(HighestLevel);  
//    }  
//  
//    Mat_<Vec3f> reconstructImgFromLapPyramid() {  
//        //将左右laplacian图像拼成的resultLapPyr金字塔中每一层  
//        //从上到下插值放大并相加，即得blend图像结果  
//        Mat currentImg = resultHighestLevel;  
//        for (int l=levels-1; l>=0; l--) {  
//            Mat up;  
//  
//            pyrUp(currentImg, up, resultLapPyr[l].size());  
//            currentImg = up + resultLapPyr[l];  
//        }  
//        return currentImg;  
//    }  
//  
//    void blendLapPyrs() {  
//        //获得每层金字塔中直接用左右两图Laplacian变换拼成的图像resultLapPyr  
//        resultHighestLevel = leftHighestLevel.mul(maskGaussianPyramid.back()) +  
//            rightHighestLevel.mul(Scalar(1.0,1.0,1.0) - maskGaussianPyramid.back());  
//        for (int l=0; l<levels; l++) {  
//            Mat A = leftLapPyr[l].mul(maskGaussianPyramid[l]);  
//            Mat antiMask = Scalar(1.0,1.0,1.0) - maskGaussianPyramid[l];  
//            Mat B = rightLapPyr[l].mul(antiMask);  
//            Mat_<Vec3f> blendedLevel = A + B;  
//  
//            resultLapPyr.push_back(blendedLevel);  
//        }  
//    }  
//  
//public:  
//    LaplacianBlending(const Mat_<Vec3f>& _left, const Mat_<Vec3f>& _right, const Mat_<float>& _blendMask, int _levels)://construct function, used in LaplacianBlending lb(l,r,m,4);  
//      left(_left),right(_right),blendMask(_blendMask),levels(_levels)  
//      {  
//          assert(_left.size() == _right.size());  
//          assert(_left.size() == _blendMask.size());  
//          buildPyramids();  //construct Laplacian Pyramid and Gaussian Pyramid  
//          blendLapPyrs();   //blend left & right Pyramids into one Pyramid  
//      };  
//  
//      Mat_<Vec3f> blend() {  
//          return reconstructImgFromLapPyramid();//reconstruct Image from Laplacian Pyramid  
//      }  
//};  
//  
//Mat_<Vec3f> LaplacianBlend(const Mat_<Vec3f>& l, const Mat_<Vec3f>& r, const Mat_<float>& m) {  
//    LaplacianBlending lb(l,r,m,4);  
//    return lb.blend();  
//}  
//  
//int main() {  
//    Mat l8u = imread("left.jpg");  
//    Mat r8u = imread("right.jpg");  
//  
//    imshow("left",l8u);   
//    imshow("right",r8u);  
//  
//    Mat_<Vec3f> l; l8u.convertTo(l,CV_32F,1.0/255.0);//Vec3f表示有三个通道，即 l[row][column][depth]  
//    Mat_<Vec3f> r; r8u.convertTo(r,CV_32F,1.0/255.0);  
//    /*****************    void convertTo( OutputArray m, int rtype, double alpha=1, double beta=0 ) const;******************/  
//	//思路:使用pyrDown（src,temp） 和 pyrUp(temp,dst)，
//	//src-dst 计算出一个降采样的 diff金字塔.
//	//对于左图和右图，分别计算出一个这样的 diff金字塔
//	//针对mask，也建立一个降采样金字塔
//	//将mask的降采样金字塔结合左右图的diff： maskCombinePyr = 左图diff金字塔 *mask + 右图diff金字塔 * (1 - mask)
//	//将左图和右图的金字塔最顶层低通滤波图像 计算mask,得到result
//	// 将result依次向上进行 上采样和叠加maskCombinePyr，到金字塔最底层的时候得到最终结果。
// // 
//    //create blend mask matrix m  
//    Mat_<float> m(l.rows,l.cols,0.0);                 //将m全部赋值为0  
//    m(Range::all(),Range(0,m.cols/2)) = 1.0;    //取m全部行&[0,m.cols/2]列，赋值为1.0  
//	//cout <<m<<endl;
//    Mat_<Vec3f> blend = LaplacianBlend(l, r, m);  
//    imshow("blended",blend);  
//  
//    waitKey(0);  
//    return 0;  
//} 