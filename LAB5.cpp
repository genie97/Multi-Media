#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>

#define d2r(x) (x * CV_PI / 180.0)

using namespace cv;
using namespace std;

Mat mm_scaling(Mat src, int zoom)
{
	Mat dst(src.rows * zoom, src.cols * zoom, src.type());
	for (int r = 0; r < dst.rows; r++) {
		for (int c = 0; c < dst.cols; c++) {
			int x = int(c / zoom);
			int y = int(r / zoom);
			dst.at<Vec3b>(r, c) = src.at<Vec3b>(y, x);
		}
	}
	return dst;
}

// rotation: based center of image
Mat mm_rotation(Mat src, float angle)
{
	Mat dst = Mat::zeros(src.size(), src.type());

	float cenX = (float)dst.cols / 2.0;
	float cenY = (float)dst.rows / 2.0;

	for (int r = 0; r < dst.rows; r++) {
		for (int c = 0; c < dst.cols; c++) {
			float x = cos(d2r(angle)) * (c - cenX) - sin(d2r(angle)) * (r - cenY) + cenX;
			float y = sin(d2r(angle)) * (c - cenX) + cos(d2r(angle)) * (r - cenY) + cenY;
			if ((int)x >= 0 && (int)x < dst.cols && (int)y >= 0 && (int)y < dst.rows) {
				dst.at<Vec3b>(r, c) = src.at<Vec3b>(y, x);
			}
		}
	}
	return dst;
}

void  mm_warp(Mat src, Mat& dst, Mat H)
{
	Mat Hi = H.inv();
	for (int r = 0; r < dst.rows; r++) {
		for (int c = 0; c < dst.cols; c++) {
			float x = c * Hi.at<float>(0, 0) + r * Hi.at<float>(1, 0) + Hi.at<float>(2, 0);
			float y = c * Hi.at<float>(0, 1) + r * Hi.at<float>(1, 1) + Hi.at<float>(2, 1);
			float w = c * Hi.at<float>(0, 2) + r * Hi.at<float>(1, 2) + Hi.at<float>(2, 2);
			int nx = (int)x / w;
			int ny = (int)y / w;
			if (nx >= 0 && nx < src.cols && ny >= 0 && ny < src.rows) {
				dst.at<Vec3b>(r,c) = src.at<Vec3b>(ny,nx);
			}
		}
	}
}

int main()
{
	Mat img = imread("book.jpg", IMREAD_COLOR);

	Mat img_scaling = mm_scaling(img, 2);
	Mat img_rotation = mm_rotation(img, 45);

	Mat img_warp(600, 400, CV_8UC3);
	Mat H = (Mat_<float>(3, 3) << 0.8296, 0.9072, 0, -1.3801, 1.0188, 0, 164.4752, -252.7859, 1);
	mm_warp(img, img_warp, H);

	imshow("original", img);
	imshow("scaling", img_scaling);
	imshow("rotation", img_rotation);
	imshow("warping", img_warp);
	waitKey(0);

	return 0;
}
