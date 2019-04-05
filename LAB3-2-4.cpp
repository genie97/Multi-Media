///////////////////////////////////////
/*************Median*************/
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
	input= imread("city_noise.jpg", IMREAD_GRAYSCALE);
	if (input.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", input);

	conInput = Mat(input.size(), input.type());
	input.convertTo(conInput, CV_32FC1, 1.0 / 255.0);

	//Median filter
	Mat med_result = Mat(conInput.size(), conInput.type());
	input.convertTo(conInput, CV_32FC1, 1.0 / 255.0);

	medianBlur(conInput, med_result, 3);
	namedWindow("Median filter result_3", WINDOW_AUTOSIZE);
	imshow("Median filter result_3", med_result);

	medianBlur(conInput, med_result, 5);
	namedWindow("Median filter result_5", WINDOW_AUTOSIZE);
	imshow("Median filter result_5", med_result);

	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}