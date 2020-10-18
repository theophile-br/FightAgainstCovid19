#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "utils.h"
	
using namespace std;
using namespace cv;

const string LBP::CMFD("CMFD");
const string LBP::IMFD("IMFD");
const string LBP::COLOR("COLOR");
const string LBP::GRAY("GRAY");
const string LBP::TRAIN("TRAIN");
const string LBP::TEST("TEST");

vector<int> gray2Hist(Mat img) {
	vector<uchar> pblImg;
	vector<int> pblHist(256,0);
	for(int i=1; i<img.rows - 1; i++) {
    	for(int j=1; j<img.cols - 1; j++) {
			vector<uchar> bits;
			int center_pixel = img.at<uchar>(i,j);
			for(int y = i+1; y >= i-1 ; y--) {
				for(int x = j+1; x >= j-1 ; x--) {
					if(x == j && y == i)
						continue;
					int curent_pixel = img.at<uchar>(y,x);
					if( center_pixel >= curent_pixel) {
						bits.push_back(1);
					} else {
						bits.push_back(0);
					}
				}
			}
			uchar decimalValue = 0;
			for (int i = bits.size() -1; i > 0; i--) {
				//cout << (int)bits[i];
				decimalValue = decimalValue * 2 + bits[i];
			}
			//cout << endl << "data : " << (int)decimalValue << endl;
			pblImg.push_back(decimalValue);
			pblHist[decimalValue]++;
		}
	}
	// UNCOMMENT TO SEE PBL PICTURE
	// Mat my_mat(img.rows - 2,img.cols - 2,CV_8UC1,pblImg.data());
	// imshow("Display window", my_mat);
    // int k = waitKey(0);
	return pblHist;
}