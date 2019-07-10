#include <opencv2/opencv.hpp>
#include<string>
#include<cstring>
#include<iostream>
#include<fstream>
using namespace std;
using namespace cv;
int freq[1000];
long double prob[1000];
pair<long double, long double> range[1000];
int main() {
	string str;
	getline(cin, str);
	for (int i = 0; i < str.length(); i++) {
		freq[str[i]]++;
	}
	for (int i = 0; i < 1000; i++) {
		prob[i] = (long double)freq[i] / (long double)str.length();
	}
	ofstream outFile("prob_table.txt");
	int visit[1000] = { 0, };
	for (int i = 0; i < str.length(); i++) {
		if (!visit[str[i]]) {
			outFile << str[i] << "\t" << setprecision(32) << prob[str[i]] << endl;
			visit[str[i]] = 1;
		}
	}
	outFile.close();
	ifstream inFile("prob_table.txt");
	char temp[1000];
	int check = 0, index = 0;
	long double start = 0.0;
	while (!inFile.eof()) {
		inFile.getline(temp, 100);
		char* tok = strtok(temp, "\t");
		while (tok != NULL) {
			if (check == 1) {
				range[index] = { start, start + stold(tok) };
				start += stold(tok);
				index++;
			}
			tok = strtok(NULL, "\t");
			check++;
		}
		check = 0;
	}
	long double low = 0.0, high = 1.0, interval = 1.0;
	for (int i = 0; i < index; i++) {
		low = low + interval*range[i].first;
		high = low + interval*range[i].second;
		interval = high - low;
	}
	inFile.close();
	ofstream outFile2("output.txt");
	long double ans = interval / 2.0;
	outFile2 << setprecision(32) << ans << endl;
	outFile2.close();
}