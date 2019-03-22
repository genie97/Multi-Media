#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv;

int main()
{
	double alpha, beta, gamma = 0.0;

	Mat img, img_float, processing; // Mat변수 선언
	img = imread("seoul.png", IMREAD_GRAYSCALE); //일반 값으로 읽어오기

	if (img.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	cin >> gamma;
	
	namedWindow("img", WINDOW_AUTOSIZE); //윈도우 명
	imshow("img", img);


	img.convertTo(img, CV_32F, 1.0 / 255.0);

	pow(img, gamma,img_float);
	

	namedWindow("processing", WINDOW_AUTOSIZE); //윈도우 명
	imshow("processing", img_float);


	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}