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
#pragma comment(lib, "opencv_world320" CV_EXT) // OpenCV3.3.0の場合は、"opencv_core330"に

using namespace cv;
using namespace std;


int main(int argc, char* argv[]){


	string SRC_IMAGE = "test.png";

	// 読み込み
	cv::Mat_<cv::Vec3b>img_src = cv::imread(SRC_IMAGE);
	if (!img_src.data)
		return -1;

	// 結果画像
	cv::Vec3b zero(0, 0, 0);
	cv::Mat_<cv::Vec3b> img_dst(img_src.rows, img_src.cols, zero);

	// 変換前の画像での座標
	const cv::Point2f src_pt[] = {
		cv::Point2f(100, 100),
		cv::Point2f(400 , 100),
		cv::Point2f(400 , 400),
		cv::Point2f(100, 400) };

	// 変換後の画像での座標
	const cv::Point2f dst_pt[] = {
		cv::Point2f(100, 100),
		cv::Point2f(400 , 100),
		cv::Point2f(400 , 400),
		cv::Point2f(100, 500) 
	};

	// homography 行列を計算

	const cv::Mat homography_matrix = cv::getPerspectiveTransform(src_pt, dst_pt);


	cout << homography_matrix << endl;

	ofstream outputfile("homography_matrix.txt");
	outputfile << homography_matrix;
	outputfile.close();
	// 変換
	cv::warpPerspective(img_src, img_dst, homography_matrix, img_src.size());

	// 書き出し
	cv::imwrite("out.tif", img_dst);


	cv::waitKey(0);


	return 0;
}
