#include <opencv2/opencv.hpp>
#include <iostream>
#include<algorithm>

using namespace cv;
using namespace std;

float histo[256];  //기존 이미지의 히스토그램
float e_histo[256];  // enhance 효과 이미지의 히스토그램
int main()
{
	Mat input;
	input = imread("beach.png", IMREAD_GRAYSCALE);

	if (input.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("input", WINDOW_AUTOSIZE); 
	imshow("input", input);

	Mat enhance = Mat(input.size(), input.type());  //이미지 처리할 때, 기존의 이미지 사이즈를 가진 Mat선언해야 함

	/*원래 이미지 히스토그램 그리기*/
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			histo[(int)input.at<unsigned char>(i, j)]++;
		}
	}
	int maxV = *max_element(histo, histo + 256);

	Mat histogram = Mat::zeros(256, 256, CV_8UC1);
	for (int i = 0; i < 256; i++) {
		line(histogram, Point(i, 0), Point(i, histo[i] / maxV * 255), Scalar(255, 255, 255), 1, 8, 0);
	}
	flip(histogram, histogram, -1);
	flip(histogram, histogram, 1);
	imshow("input histogram", histogram);

	/*enhancement 이미지*/
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			if ((float)input.at<unsigned char>(i, j) < 100)
				enhance.at<unsigned char>(i, j) = (unsigned char)(0.5 * (float)input.at<unsigned char>(i, j));
			else if ((float)input.at<unsigned char>(i, j) >= 100 && (float)input.at<unsigned char>(i, j) < 180)
				enhance.at<unsigned char>(i, j) = (unsigned char)(2 * (float)input.at<unsigned char>(i, j) - 150);
			else
				enhance.at<unsigned char>(i, j) = (unsigned char)(0.6 * (float)input.at<unsigned char>(i, j) + 102);
		}
	}
	namedWindow("enhanced image", WINDOW_AUTOSIZE);
	imshow("enhanced image", enhance); 

	/*enhance 이미지 히스토그램 그리기*/
	for (int i = 0; i < enhance.rows; i++) {
		for (int j = 0; j < enhance.cols; j++) {
			e_histo[(int)enhance.at<unsigned char>(i, j)]++;
		}
	}
	maxV = *max_element(e_histo, e_histo + 256);

	Mat e_histogram = Mat::zeros(256, 256, CV_8UC1);
	for (int i = 0; i < 256; i++) {
		line(e_histogram, Point(i, 0), Point(i, e_histo[i] / maxV * 255), Scalar(255, 255, 255), 1, 8, 0);
	}
	flip(e_histogram, e_histogram, -1);
	flip(e_histogram, e_histogram, 1);
	imshow("enhance histogram", e_histogram);


	/* transform 함수 그리기*/
	Mat tf = Mat::zeros(256, 256, CV_8UC1);
	for (int i = 0; i < 256; i++) {
		if (i < 100)
			tf.at<unsigned char>(0.5 * i, i) = 255;
		else if(i>=100&&i<180)
			tf.at<unsigned char>(2*i-150, i) = 255;
		else
			tf.at<unsigned char>(0.6*i+102, i) = 255;
	}
	flip(tf, tf, 0);  //위 아래 변환
	imshow("transfer function", tf);

	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}