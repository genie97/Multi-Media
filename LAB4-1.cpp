#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int gdx[4] = { 1,-1,0,0 }, gdy[4] = { 0,0,1,-1 };
int rbdx[4] = { -1,-1,1,1 }, rbdy[4] = { -1,1,-1,1 };
int ogx[2] = { 1,-1 }, ogy[2] = { 0,0 };
int egx[2] = { 0,0 }, egy[2] = { 1,-1 };
int main()
{

	Mat sensor_img = imread("sensor_data.jpg", IMREAD_GRAYSCALE);

	if (sensor_img.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	Mat bayer_img = Mat::zeros(sensor_img.size(), CV_8UC3);
	Mat color_img = Mat::zeros(sensor_img.size(), CV_8UC3);

	//bayer img
	for (int r = 0; r < sensor_img.rows; r += 2) {
		// R
		for (int c = 0; c < sensor_img.cols; c += 2)
			bayer_img.at<Vec3b>(r, c)[2] = sensor_img.at<unsigned char>(r, c);
		// G
		for (int c = 1; c < sensor_img.cols; c += 2)
			bayer_img.at<Vec3b>(r, c)[1] = sensor_img.at<unsigned char>(r, c);
	}
	for (int r = 1; r < sensor_img.rows; r += 2) {
		// G
		for (int c = 0; c < sensor_img.cols; c += 2)
			bayer_img.at<Vec3b>(r, c)[1] = sensor_img.at<unsigned char>(r, c);

		// B
		for (int c = 1; c < sensor_img.cols; c += 2)
			bayer_img.at<Vec3b>(r, c)[0] = sensor_img.at<unsigned char>(r, c);
	}

	namedWindow("origin", WINDOW_AUTOSIZE); //윈도우 명
	imshow("origin", bayer_img);

	//color img
	for (int r = 0; r < bayer_img.rows; r += 2) {
		for (int c = 0; c < bayer_img.cols; c += 2) {
			int g_cnt = 0, b_cnt = 0;
			double gsum = 0.0, bsum = 0.0;
			for (int i = 0; i < 4; i++) {
				int nx = r + gdx[i];
				int ny = c + gdy[i];
				int cx = r + rbdx[i];
				int cy = c + rbdy[i];
				if (nx < 0 || nx >= bayer_img.rows || ny < 0 || ny >= bayer_img.cols) {
					g_cnt++;
					continue;
				}
				if (cx < 0 || cx >= bayer_img.rows || cy < 0 || cy >= bayer_img.cols) {
					b_cnt++;
					continue;
				}
				gsum += (double)bayer_img.at<Vec3b>(nx, ny)[1];
				bsum += (double)bayer_img.at<Vec3b>(cx, cy)[0];
			}
			color_img.at<Vec3b>(r, c)[1] = (uchar)(gsum / (4 - g_cnt));
			color_img.at<Vec3b>(r, c)[0] = (uchar)(bsum / (4 - b_cnt));
		} //R에 G,B 넣기

		for (int c = 1; c < bayer_img.cols; c += 2) {
			int b_cnt = 0.0, r_cnt = 0.0;
			double rsum = 0, bsum = 0;
			for (int i = 0; i < 2; i++) {
				int nbx = r + ogx[i];
				int nby = c + ogy[i];
				int nrx = r + egx[i];
				int nry = c + egy[i];
				if (nbx < 0 || nbx >= bayer_img.rows || nby < 0 || nby >= bayer_img.cols) {
					b_cnt++;
					continue;
				}
				if (nrx < 0 || nrx >= bayer_img.rows || nry < 0 || nry >= bayer_img.cols) {
					r_cnt++;
					continue;
				}
				rsum += (double)bayer_img.at<Vec3b>(nrx, nry)[2];
				bsum += (double)bayer_img.at<Vec3b>(nbx, nby)[0];
			}
			//printf("%d %d\n", rsum, bsum);
			color_img.at<Vec3b>(r, c)[2] = rsum / (2 - r_cnt);
			color_img.at<Vec3b>(r, c)[0] = bsum / (2 - b_cnt);

		} //G에 R,B 넣기
	} //홀

	for (int r = 1; r < bayer_img.rows; r += 2) {
		for (int c = 0; c < bayer_img.cols; c += 2) {
			int b_cnt = 0.0, r_cnt = 0.0;
			double rsum = 0, bsum = 0;
			for (int i = 0; i < 2; i++) {
				int nbx = r + egx[i];
				int nby = c + egy[i];
				int nrx = r + ogx[i];
				int nry = c + ogy[i];
				if (nbx < 0 || nbx >= bayer_img.rows || nby < 0 || nby >= bayer_img.cols) {
					b_cnt++;
					continue;
				}
				if (nrx < 0 || nrx >= bayer_img.rows || nry < 0 || nry >= bayer_img.cols) {
					r_cnt++;
					continue;
				}
				rsum += (double)bayer_img.at<Vec3b>(nrx, nry)[2];
				bsum += (double)bayer_img.at<Vec3b>(nbx, nby)[0];
			}
			color_img.at<Vec3b>(r, c)[2] = rsum / (2 - r_cnt);
			color_img.at<Vec3b>(r, c)[0] = bsum / (2 - b_cnt);
		} //G
		for (int c = 1; c < bayer_img.cols; c += 2) {
			int g_cnt = 0.0, r_cnt = 0.0;
			double gsum = 0, rsum = 0;
			for (int i = 0; i < 4; i++) {
				int nx = r + gdx[i];
				int ny = c + gdx[i];
				int cx = r + rbdx[i];
				int cy = c + rbdy[i];

				if (nx < 0 || nx >= bayer_img.rows || ny < 0 || ny >= bayer_img.cols) {
					g_cnt++;
					continue;
				}
				if (cx < 0 || cx >= bayer_img.rows || cy < 0 || cy >= bayer_img.cols) {
					r_cnt++;
					continue;
				}
				gsum += (double)bayer_img.at<Vec3b>(nx, ny)[1];
				rsum += (double)bayer_img.at<Vec3b>(cx, cy)[2];
			}
			color_img.at<Vec3b>(r, c)[1] = gsum / (4 - g_cnt);
			color_img.at<Vec3b>(r, c)[2] = (rsum / 4 - r_cnt);
		} //B에 G,R넣기

	} //짝

	namedWindow("color", WINDOW_AUTOSIZE); //윈도우 명
	imshow("color", color_img);

	waitKey(0); //키 인풋이 들어올 때까지 기다린다.
}