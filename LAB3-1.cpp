#include <opencv2/opencv.hpp>
#include <iostream>
#include<algorithm>

using namespace cv;
using namespace std;

float histo[256];  //���� �̹����� ������׷�
float e_histo[256];  // enhance ȿ�� �̹����� ������׷�
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

	Mat enhance = Mat(input.size(), input.type());  //�̹��� ó���� ��, ������ �̹��� ����� ���� Mat�����ؾ� ��

	/*���� �̹��� ������׷� �׸���*/
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

	/*enhancement �̹���*/
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

	/*enhance �̹��� ������׷� �׸���*/
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


	/* transform �Լ� �׸���*/
	Mat tf = Mat::zeros(256, 256, CV_8UC1);
	for (int i = 0; i < 256; i++) {
		if (i < 100)
			tf.at<unsigned char>(0.5 * i, i) = 255;
		else if(i>=100&&i<180)
			tf.at<unsigned char>(2*i-150, i) = 255;
		else
			tf.at<unsigned char>(0.6*i+102, i) = 255;
	}
	flip(tf, tf, 0);  //�� �Ʒ� ��ȯ
	imshow("transfer function", tf);

	waitKey(0); //Ű ��ǲ�� ���� ������ ��ٸ���.
}