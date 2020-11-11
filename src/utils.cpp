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

void gray2Hist(Mat &img, int lbpHist[256]){
	// vector<uchar> pblImg;
	for (int y = 1; y < img.rows - 1; y++)
	{
		for (int x = 1; x < img.cols - 1; x++)
		{
			uchar bits[8];
			int center_pixel = img.at<uchar>(y, x);

			bits[0] = (center_pixel >= img.at<uchar>(y-1, x-1))?1:0;
			bits[1] = (center_pixel >= img.at<uchar>(y-1, x))?1:0;
			bits[2] = (center_pixel >= img.at<uchar>(y-1, x+1))?1:0;
			bits[3] = (center_pixel >= img.at<uchar>(y, x+1))?1:0;
			bits[4] = (center_pixel >= img.at<uchar>(y+1, x+1))?1:0;
			bits[5] = (center_pixel >= img.at<uchar>(y+1, x))?1:0;
			bits[6] = (center_pixel >= img.at<uchar>(y+1, x-1))?1:0;
			bits[7] = (center_pixel >= img.at<uchar>(y, x-1))?1:0;

			int decimalValue = 0;
			for (int i = 0; i < 8; i++)
			{
				// cout << (int)bits[i];
				decimalValue += pow(2, i) * bits[i];
			}
			// pblImg.push_back(decimalValue);
			// cout << endl << (int)decimalValue << endl;
			lbpHist[decimalValue] = lbpHist[decimalValue] + 1;
		}
	}
	// Mat my_mat(img.rows - 2, img.cols - 2, CV_8UC1, pblImg.data());
	// imshow("Display window", my_mat);
	// waitKey(0);
}

void color2Hist(cv::Mat &img, int lbpHist[3][256]){
	Mat rbg[3];
	split(img,rbg);
	gray2Hist(rbg[0], lbpHist[0]);
	gray2Hist(rbg[1], lbpHist[1]);
	gray2Hist(rbg[2], lbpHist[2]);
}

void colorDescriptor2Vector(string descriptor, int v[3][256]){
	descriptor = descriptorGetHistogramPart(descriptor);
	string delimiter = ",";
	size_t pos = 0;
	string token;
	for (int i = 0; i < 3; i++){
		int count = 0;
		while ((pos = descriptor.find(delimiter)) != std::string::npos) {
    		token = descriptor.substr(0, pos);
			v[i][count] = atoi( token.c_str() );
            count++;
            descriptor.erase(0, pos + delimiter.length());
			if(count == 256){
				break;
			}
		}
	}
	token = descriptor.substr(0, pos);
	v[2][255] = atoi( token.c_str() );
	descriptor.erase(0, pos + delimiter.length());
}

void grayDescriptor2Vector(string descriptor, int v[256]) {
    descriptor = descriptorGetHistogramPart(descriptor);
	string delimiter = ",";
	size_t pos = 0;
	string token;
	int i = 0;
	while ((pos = descriptor.find(delimiter)) != std::string::npos) {
    	token = descriptor.substr(0, pos);
		v[i] = atoi( token.c_str() );
    	descriptor.erase(0, pos + delimiter.length());
		i++;
	}
	token = descriptor.substr(0, pos);
	v[255] = atoi( token.c_str() );
}

string descriptorGetType(string descriptor) {
	string delimiterType= ":";
	size_t pos = descriptor.find(delimiterType);
	string type = descriptor.erase(0, pos + delimiterType.length());
	if(type == "1") {
		return LBP::CMFD;
	} else {
		return LBP::IMFD;
	}
}

string descriptorGetHistogramPart(string descriptor) {
	string delimiterType= ":";
	size_t pos = descriptor.find(delimiterType);
	return descriptor.substr(0, pos);
}



