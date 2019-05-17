#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat left = imread("left.png", IMREAD_GRAYSCALE);
	Mat right = imread("right.png", IMREAD_GRAYSCALE);
	Mat disp = Mat::zeros(left.size(), CV_8UC1);
	int patch_size = 11;
	for (int r = 0; r < left.rows - patch_size;r++ ) {
		Mat roR = Mat(right, Rect(0, r, left.cols, patch_size)); //row 한 줄 (직선라인)
		Mat res;
		for (int c = 0; c < left.cols-patch_size; c++) {
			// row 한 줄 직선을 확인하면서 patch_size만큼씩 보기
			Mat roL = Mat(left, Rect(c, r, patch_size, patch_size));
			Point min_loc;
			matchTemplate(roR, roL, res, TM_SQDIFF);
			minMaxLoc(res, NULL, NULL, &min_loc, NULL); //가장 작은 곳의 위치
			int min_x = min_loc.x;
			if (min_x < c) {
				int d = c - min_x;
				if (0 < d && d < 40)
					disp.at<uchar>(r, c) = c - min_x;
				else
					disp.at<uchar>(r, c) = 0;
			}
		}
	}
	imshow("windowL", left);
	imshow("windowR", right);
	imshow("windowD", disp*5);
	imwrite("disp.png", disp);
	waitKey(0);
}
# point_cloud_gen
/*
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
using namespace cv;

int main()
{
Mat imL = imread("left.png", IMREAD_COLOR);
Mat disp = imread("disp.png", IMREAD_GRAYSCALE);

ofstream ofs;
ofs.open("result.txt", ios::out);
ofs.seekp(0, ios::beg);

for (int r = 0; r < disp.rows; r++) {
for (int c = 0; c < disp.cols; c++) {
if (disp.at<unsigned char>(r, c) != 0) {
float Z = (50 - disp.at<unsigned char>(r, c) );
float X = (float)(disp.cols / 2 - c) * 0.01 * Z;
float Y = (float)(disp.rows / 2 - r) * 0.01 * Z;
Vec3b rgb = imL.at<Vec3b>(r, c);

ofs << X << ";" << Y << ";" << Z << ";" << (int)rgb[2] << ";" << (int)rgb[1] << ";" << (int)rgb[0]  << endl;
}
}
}
ofs.close();
}
*/