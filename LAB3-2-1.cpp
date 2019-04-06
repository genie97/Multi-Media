///////////////////////////////////////
/**********Convolution***********/
//////////////////////////////////////
/*#include <opencv2/opencv.hpp>
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
	Mat input,conInput;
	input = imread("city.jpg", IMREAD_GRAYSCALE);
	if (input.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", input);

	Mat blur = (Mat_<float>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);

	conInput = Mat(input.size(), input.type());
	input.convertTo(conInput, CV_32FC1, 1.0 / 255.0);

	Mat conv_result = Mat(conInput.size(), conInput.type());

	Convolution(conInput, blur, conv_result);
	namedWindow("convolution result", WINDOW_AUTOSIZE);
	imshow("convolution result", conv_result);

	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}*/