////////////////////////////////////////
/*************Gaussian************/
//////////////////////////////////////
#include <opencv2/opencv.hpp>
#include <iostream>
#include<math.h>
#include<algorithm>

using namespace cv;
using namespace std;
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

	//Gaussian blur
	Mat gau_result = Mat(conInput.size(), conInput.type());

	//Gaussian blur 5 by 5
	GaussianBlur(conInput, gau_result, Size(5, 5), 0, 0, 4);
	namedWindow("Gaussian filter result_5", WINDOW_AUTOSIZE);
	imshow("Gaussian filter result_5", gau_result);

	//Gaussian blur 11 by 11
	GaussianBlur(conInput, gau_result, Size(11, 11), 0, 0, 4);
	namedWindow("Gaussian filter result_11", WINDOW_AUTOSIZE);
	imshow("Gaussian filter result_11", gau_result);

	//Gaussian blur horizontally
	GaussianBlur(conInput, gau_result, Size(21, 1), 0, 0, 4);
	namedWindow("Gaussian filter result_horizontally", WINDOW_AUTOSIZE);
	imshow("Gaussian filter result_horizontally", gau_result);

	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}