#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	Mat img = imread("foreground.jpg", IMREAD_COLOR);
	if (img.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	Mat HSV, output;
	cvtColor(img, HSV, COLOR_BGR2HSV);
	output = Mat(HSV.size(), HSV.type());
	for (int i = 0; i < HSV.rows; i++) {
		for (int j = 0; j < HSV.cols; j++) {
			int H = HSV.at<Vec3b>(i,j)[0]; //0~360�� ����*0.5�� ���� ���� ���� ��
			int S = HSV.at<Vec3b>(i, j)[1];
			int V = HSV.at<Vec3b>(i, j)[2];
			if (50 <= H&&H <= 80 && V > 100) 
				H = S = V = 0;
			else
				H = S = V = 255;
			output.at<Vec3b>(i, j)[0] = H;
			output.at<Vec3b>(i, j)[1] = S;
			output.at<Vec3b>(i, j)[2] = V;
		}
	}
	namedWindow("origin", WINDOW_AUTOSIZE); //������ ��
	imshow("origin", output);

	waitKey(0); //Ű ��ǲ�� ���� ������ ��ٸ���.
}