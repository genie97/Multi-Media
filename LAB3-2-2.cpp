///////////////////////////////////////
/**************Sobel**************/
//////////////////////////////////////
#include <opencv2/opencv.hpp>
#include <iostream>
#include<math.h>
#include<algorithm>

using namespace cv;
using namespace std;
void Convolution(Mat input, Mat kernel, Mat& result) {
	float sum = 0;
	for (int i = 1; i < input.rows - 1; i++) {
		for (int j = 1; j < input.cols - 1; j++) {
			for (int k = -1; k <= 1; k++) {
				for (int l = -1; l <= 1; l++) {
					int nx = i + k;
					int ny = j + k;
					sum += input.at<float>(nx, ny) * kernel.at<float>(k + 1, l + 1);
				}
			}
			sum /= (3 * 3);
			result.at<float>(i, j) = sum;
		}
	}
}

int main()
{
	Mat input, conInput;
	input = imread("city.jpg", IMREAD_GRAYSCALE);
	if (input.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", input);

	conInput = Mat(input.size(), input.type());
	input.convertTo(conInput, CV_32FC1, 1.0 / 255.0);

	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", input);

	Mat sobel_h = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
	Mat sobel_v = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	Mat edge_result = Mat(conInput.size(), conInput.type());
	Mat edge_result1 = Mat(conInput.size(), conInput.type());
	Mat edge_result2 = Mat(conInput.size(), conInput.type());
	Mat tmp1 = Mat(conInput.size(), conInput.type());
	Mat tmp2 = Mat(conInput.size(), conInput.type());

	Convolution(conInput, sobel_h, edge_result1);
	Convolution(conInput, sobel_v, edge_result2);

	//sobel_v
	namedWindow("edge_v detection result", WINDOW_AUTOSIZE);
	imshow("edge_v detection result", edge_result2);

	//sobel_h
	namedWindow("edge_h detection result", WINDOW_AUTOSIZE);
	imshow("edge_h detection result", edge_result1);

	pow(edge_result1, 2.0, tmp1);
	pow(edge_result2, 2.0, tmp2);
	sqrt(tmp1 + tmp2, edge_result);

	//sobel
	namedWindow("edge detection result", WINDOW_AUTOSIZE);
	imshow("edge detection result", edge_result);

	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}