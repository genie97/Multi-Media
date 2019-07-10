// 201635844 Lim Hyo Jin MM_HW2

#include <opencv2/opencv.hpp>
#include <iostream>
#include<cmath>
#include<queue>
#define d2r(x) (x * CV_PI / 180.0) //angle: radian
#define CV_8UC1 CV_MAKETYPE(CV_8U,1)

using namespace cv;
using namespace std;

// Description: Read image
Mat readImage() {
	Mat src = imread("beach.png", IMREAD_COLOR);
	return src;
}

Mat Original(Mat src) {
	src = readImage();
	return src;
}

Mat Brightness(Mat src, float value) {
	Mat dst = Mat::zeros(src.size(), src.type());
	dst = src + Scalar(value, value, value);
	return dst;
}

Mat GammaCorrection(Mat src, float value) {
	Mat lut(1, 256, CV_8UC1);
	uchar *ptr = lut.ptr();
	for (int i = 0; i < 256; i++) {
		ptr[i] = saturate_cast<uchar>(pow((float)i / 255.0, value) * 255.0f);
	}
	Mat dst = src.clone();
	LUT(src, lut, dst);
	return dst;
}

Mat EdgeDetection(Mat src) {
	Mat dst = Mat::zeros(src.size(), src.type()); // final reusult
	if (src.type() != CV_8UC1)
		cvtColor(src, dst, COLOR_BGR2GRAY);
	Canny(src, dst, 20, 160, 3, false);
	return dst;
}

Mat Blur(Mat src, int kernel) {
	Mat dst = Mat::zeros(src.size(), src.type());
	medianBlur(src, dst, kernel);
	return dst;
}

Mat Rotation(Mat src, float angle) {
	double scale = 1.0;
	Point2f center(src.cols / 2.0, src.rows / 2.0);
	Mat rotateMat = getRotationMatrix2D(center, angle, scale);
	Mat dst;
	warpAffine(src, dst, rotateMat, src.size());
	return dst;
}

Mat RotateColor(Mat src, float hueAngle) {
	Mat dst = Mat::zeros(src.size(), CV_32FC3);
	if (src.type() == CV_8UC1)
		cvtColor(src, src, COLOR_GRAY2RGB); // case: grayscale(example: edge detection->rotate color)
	cvtColor(src, dst, COLOR_RGB2HSV);
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			dst.at<Vec3b>(i, j)[0] += hueAngle / 2;
			dst.at<Vec3b>(i, j)[0] %= 180;
		}
	}
	Mat temp = Mat::zeros(src.size(), CV_32FC3);
	cvtColor(dst, temp, COLOR_HSV2RGB);
	return temp;
}

void Comment() {
	cout << "rotation을 계속 하다보면 픽셀정보가 사라지는데 이를 복원하려면 어떤 방식으로 구현하는게 좋을까요?" << endl;
	cout << "rectangle을 이용해서 boundary를 주는 방식으로 해봤는데 window 창이 계속 커지는 문제가 있었습니다." << endl;
	cout << "파이썬에서 opencv 사용하는 경우 imutils라는 라이브러리에 rotate_bound라는 함수가 있는데 c++은 이러한 함수가 없나요?" << endl;
}

int main()
{
	// Menu UI
	cout << "===================================" << endl;
	cout << "             M E N U           " << endl;
	cout << "===================================" << endl;
	cout << "1. restore original image" << endl;
	cout << "2. Brightness" << endl;
	cout << "3. Gamma Correction" << endl;
	cout << "4. Edge Detection" << endl;
	cout << "5. Blur" << endl;
	cout << "6. Rotation" << endl;
	cout << "7. Rotate Color" << endl;
	cout << "8. comment" << endl;
	cout << "0. Exit" << endl;
	cout << "-----------------------------------" << endl;

	int opt; // option value
	Mat img = readImage();
	Mat restoreImg = readImage(); //restore mat for rotation
	if (img.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	imshow("Result", img);
	waitKey(33);
	while (1) {
		int check = 0; //check processing
		cout << "command? ";
		cin >> opt;

		if (opt == 0)
			break;
		switch (opt) {
		case 1:
			img = Original(img);
			check = 1;
			break;
		case 2:
			float b_value;
			cout << "correction value? ";
			cin >> b_value;
			if (b_value < -255 || b_value>255) {
				cout << "Invalid input. Please enter a number between -255 and 255." << endl;
				check = 0;
			}
			else {
				img = Brightness(img, b_value);
				check = 1;
			}
			break;
		case 3:
			float g_value;
			cout << "correction value? ";
			cin >> g_value;
			if (g_value<0.0 || g_value>2.0) {
				cout << "Invalid input. Please enter a number between 0 and 2.0." << endl;
				check = 0;
			}
			else {
				img = GammaCorrection(img, g_value);
				check = 1;
			}
			break;
		case 4:
			img = EdgeDetection(img);
			check = 1;
			break;
		case 5:
			int kernel;
			cout << "blur kernel size? ";
			cin >> kernel;
			if (kernel > img.rows || kernel > img.cols) {
				cout << "Invalid input. Size of kernel is larger than source image. " << endl;
				check = 0;
			}
			else if (kernel % 2 == 0) {
				cout << "Invalid input. Size of kernel is an odd. " << endl;
				check = 0;
			}
			else {
				img = Blur(img, kernel);
				check = 1;
			}
			break;
		case 6:
			float angle;
			cout << "Rotation angle? ";
			cin >> angle;
			img = Rotation(img, angle);
			check = 1;
			break;
		case 7:
			float hueAngle;
			cout << "Rotation in HUE? ";
			cin >> hueAngle;
			img = RotateColor(img, hueAngle);
			check = 1;
			break;
		case 8:
			Comment();
			break;
		default:
			cout << "Invalid input. Please enter a number between 0 and 8." << endl;
			break;
		}
		if (check)
			imshow("Result", img);
		waitKey(33);
	}
	return 0;
}

