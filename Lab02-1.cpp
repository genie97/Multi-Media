#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	double alpha, beta;

	Mat original, processing; // Mat변수 선언
	original = imread("seoul.png", IMREAD_GRAYSCALE); //일반 값으로 읽어오기
	if (original.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	cin >> alpha >> beta;

	namedWindow("original", WINDOW_AUTOSIZE); //윈도우 명
	imshow("original", original);

	processing = alpha * original + beta;
	namedWindow("processing", WINDOW_AUTOSIZE);
	imshow("processing", processing); //해당 이름을 가진 윈도우에 이미지 불러오기

	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}