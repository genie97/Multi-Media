#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	VideoCapture cap;
	cap.open("horse.avi");
	//매칭할때는 GRAY로 읽을 것
	Mat src = imread("horse_template.jpg",IMREAD_GRAYSCALE); 
	while (1) {
		Mat dst;
		double minVal;
		Point minLoc;
		Mat result;
		Mat img;

		cap >> img;
		if (img.empty())
			break;
		if (waitKey(33) > 0)
			break;
		cvtColor(img, dst, COLOR_BGR2GRAY);
		matchTemplate(dst, src, result, TM_SQDIFF);
		minMaxLoc(result, &minVal, NULL, &minLoc, NULL);
		rectangle(img, minLoc, Point(minLoc.x + src.cols, minLoc.y + src.rows), Scalar(255, 0, 0), 2);
		namedWindow("window", WINDOW_AUTOSIZE); //윈도우 명
		imshow("window",img);
	}
}