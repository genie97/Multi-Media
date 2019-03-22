#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv;

int main()
{
	double alpha, beta, gamma = 0.0;

	Mat img, img_float, processing; // Mat���� ����
	img = imread("seoul.png", IMREAD_GRAYSCALE); //�Ϲ� ������ �о����

	if (img.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	cin >> gamma;
	
	namedWindow("img", WINDOW_AUTOSIZE); //������ ��
	imshow("img", img);


	img.convertTo(img, CV_32F, 1.0 / 255.0);

	pow(img, gamma,img_float);
	

	namedWindow("processing", WINDOW_AUTOSIZE); //������ ��
	imshow("processing", img_float);


	waitKey(0); //Ű ��ǲ�� ���� ������ ��ٸ���.
}