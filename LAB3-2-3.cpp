///////////////////////////////////////
/************Laplacian************/
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

	//Laplacian filter
	Mat lap = (Mat_<float>(3, 3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);
	Mat lap_result = Mat(conInput.size(), conInput.type());

	filter2D(conInput, lap_result, conInput.depth(), lap);
	namedWindow("Laplacian filter result", WINDOW_AUTOSIZE);
	imshow("Laplacian filter result", lap_result);


	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}