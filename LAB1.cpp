#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat origin_img, grey_img; // Mat변수 선언
	origin_img = imread("gachon.jpg", IMREAD_COLOR); //일반 값으로 읽어오기
	if (origin_img.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("win_color", WINDOW_AUTOSIZE); //윈도우 명
	imshow("win_color", origin_img);
	
	grey_img = imread("gachon.jpg", IMREAD_GRAYSCALE);
	namedWindow("win_grey", WINDOW_AUTOSIZE); 
	imshow("win_grey", grey_img); //해당 이름을 가진 윈도우에 이미지 불러오기

	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}