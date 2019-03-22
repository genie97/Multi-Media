#include<opencv2\opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main() {
	Mat a(4, 4, CV_32FC1);
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			a.at<float>(r, c) = (float)r + c;
		}
	}
	cout << a << endl;

	Mat b;
	a.copyTo(b);
	cout << b << endl;
	b = a.clone();
	cout << b << endl;

	Mat c = Mat(b, Rect(0, 0, 2, 2));
	cout << c << endl;

	Mat row = a.row(0).clone();
	cout << row << endl;

	Mat col = a.col(0).clone();
	cout << col << endl;

	cout << a.size() << endl;
	cout << a.rows << " and " << a.cols << endl;

	Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
	cout << "M = " << endl << " " << M << endl << endl;


	Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0,-1,0);
	cout << "C= " << endl << " " << C << endl << endl;

	Scalar s1;
	s1 = Scalar(0);

	Scalar s2;
	s1 = Scalar(2, 3);

	Scalar s3;
	s3.val[0] = 1;
	s3.val[1] = 2;
	s3.val[2] = 3;
	s3.val[3] = 4;

	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	cout << "s3: " << s3 << endl;

	Point2f p1(10.1, 20.2);
	Point3i p2(4, 5, 6);
	cout << p1 << endl;
	cout << p2 << endl;

	cout << p1.x << " " << p1.y << endl;
	p2.z = 8;
	cout << p2 << endl;
	
	// Today's mission: Calculate below equation using Mat 
	Mat A = (Mat_<double>(2, 3) << 5, -2, 1, 4, -1, 2);
	Mat B = (Mat_<double>(2, 3) << 1, 3, 4, 6, -1, 2);
	Mat C;
	C = A.t()*B - B.t()*A;
	cout << "C= " << C << endl;

}