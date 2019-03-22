#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat origin_img, grey_img; // Mat���� ����
	origin_img = imread("gachon.jpg", IMREAD_COLOR); //�Ϲ� ������ �о����
	if (origin_img.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("win_color", WINDOW_AUTOSIZE); //������ ��
	imshow("win_color", origin_img);
	
	grey_img = imread("gachon.jpg", IMREAD_GRAYSCALE);
	namedWindow("win_grey", WINDOW_AUTOSIZE); 
	imshow("win_grey", grey_img); //�ش� �̸��� ���� �����쿡 �̹��� �ҷ�����

	waitKey(0); //Ű ��ǲ�� ���� ������ ��ٸ���.
}