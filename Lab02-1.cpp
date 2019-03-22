#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	double alpha, beta;

	Mat original, processing; // Mat���� ����
	original = imread("seoul.png", IMREAD_GRAYSCALE); //�Ϲ� ������ �о����
	if (original.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	cin >> alpha >> beta;

	namedWindow("original", WINDOW_AUTOSIZE); //������ ��
	imshow("original", original);

	processing = alpha * original + beta;
	namedWindow("processing", WINDOW_AUTOSIZE);
	imshow("processing", processing); //�ش� �̸��� ���� �����쿡 �̹��� �ҷ�����

	waitKey(0); //Ű ��ǲ�� ���� ������ ��ٸ���.
}