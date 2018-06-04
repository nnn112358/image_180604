#include <iostream> 
#include <cmath>
#include <string>
#include <sstream>
#include<fstream>


#include <vector>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world320" CV_EXT) // OpenCV3.3.0�̏ꍇ�́A"opencv_core330"��

using namespace cv;
using namespace std;


int main(int argc, char* argv[]){


	string SRC_IMAGE = "test.png";

	// �ǂݍ���
	cv::Mat_<cv::Vec3b>img_src = cv::imread(SRC_IMAGE);
	if (!img_src.data)
		return -1;

	// ���ʉ摜
	cv::Vec3b zero(0, 0, 0);
	cv::Mat_<cv::Vec3b> img_dst(img_src.rows, img_src.cols, zero);

	// �ϊ��O�̉摜�ł̍��W
	const cv::Point2f src_pt[] = {
		cv::Point2f(100, 100),
		cv::Point2f(400 , 100),
		cv::Point2f(400 , 400),
		cv::Point2f(100, 400) };

	// �ϊ���̉摜�ł̍��W
	const cv::Point2f dst_pt[] = {
		cv::Point2f(100, 100),
		cv::Point2f(400 , 100),
		cv::Point2f(400 , 400),
		cv::Point2f(100, 500) 
	};

	// homography �s����v�Z

	const cv::Mat homography_matrix = cv::getPerspectiveTransform(src_pt, dst_pt);


	cout << homography_matrix << endl;

	ofstream outputfile("homography_matrix.txt");
	outputfile << homography_matrix;
	outputfile.close();
	// �ϊ�
	cv::warpPerspective(img_src, img_dst, homography_matrix, img_src.size());

	// �����o��
	cv::imwrite("out.tif", img_dst);


	cv::waitKey(0);


	return 0;
}
