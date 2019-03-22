#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv;

int main()
{
	double alpha, beta, gamma=0.0;

	Mat img1, img2, dst; // Mat변수 선언
	img1 = imread("seoul.png", IMREAD_GRAYSCALE); //일반 값으로 읽어오기
	img2 = imread("bird.png", IMREAD_GRAYSCALE); //일반 값으로 읽어오기

	if (img1.empty() || img2.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	cin >> alpha;
	beta = 1 - alpha;

	addWeighted(img1, alpha, img2, beta, gamma, dst);

	namedWindow("img1", WINDOW_AUTOSIZE); //윈도우 명
	imshow("img1", img1);

	namedWindow("img2", WINDOW_AUTOSIZE); //윈도우 명
	imshow("img2", img2);

	namedWindow("blending", WINDOW_AUTOSIZE); //윈도우 명
	imshow("blending", dst);

	
	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}