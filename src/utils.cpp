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

vector<int> gray2Hist(Mat img){
	vector<uchar> pblImg;
	vector<int> pblHist(256, 0);
	for (int y = 1; y < img.rows - 1; y++)
	{
		for (int x = 1; x < img.cols - 1; x++)
		{
			vector<uchar> bits;
			int center_pixel = img.at<uchar>(y, x);

			bits.push_back((center_pixel >= img.at<uchar>(y-1, x-1))?1:0);
			bits.push_back((center_pixel >= img.at<uchar>(y-1, x))?1:0);
			bits.push_back((center_pixel >= img.at<uchar>(y-1, x+1))?1:0);
			bits.push_back((center_pixel >= img.at<uchar>(y, x+1))?1:0);
			bits.push_back((center_pixel >= img.at<uchar>(y+1, x+1))?1:0);
			bits.push_back((center_pixel >= img.at<uchar>(y+1, x))?1:0);
			bits.push_back((center_pixel >= img.at<uchar>(y+1, x-1))?1:0);
			bits.push_back((center_pixel >= img.at<uchar>(y, x-1))?1:0);

			int decimalValue = 0;
			for (int i = 0; i < bits.size(); i++)
			{
				// cout << (int)bits[i];
				decimalValue += pow(2, i) * bits[i];
			}
			// pblImg.push_back(decimalValue);
			// cout << endl << (int)decimalValue << endl;
			pblHist[decimalValue]++;
		}
	}
	// Mat my_mat(img.rows - 2, img.cols - 2, CV_8UC1, pblImg.data());
	// imshow("Display window", my_mat);
	// waitKey(0);
	return pblHist;
}

vector<vector<int>> color2Hist(cv::Mat img){
	Mat rbg[3];
	split(img,rbg);
	vector<vector<int>> pblHist(3);
	pblHist[0] = gray2Hist(rbg[0]);
	pblHist[1] = gray2Hist(rbg[1]);
	pblHist[2] = gray2Hist(rbg[2]);
	return pblHist;
}

vector<vector<int>> colorDescriptor2Vector(string descriptor){
	vector<vector<int>> v(3,vector<int>());
	descriptor = descriptorGetHistogramPart(descriptor);
	string delimiter = ",";
	size_t pos = 0;
	string token;
	for (int i = 0; i < 3; i++){
		int count = 0;
		while ((pos = descriptor.find(delimiter)) != std::string::npos) {
			count++;
    		token = descriptor.substr(0, pos);
			v[i].push_back(atoi( token.c_str() ));
    		descriptor.erase(0, pos + delimiter.length());
			if(count == 255){
				break;
			}
		}
		if((pos = descriptor.find(delimiter)) != std::string::npos) {
			token = descriptor.substr(0, pos);
			v[i].push_back(atoi( token.c_str() ));
			descriptor.erase(0, pos + delimiter.length());
		}
	}
	return  v;
}

vector<int> grayDescriptor2Vector(string descriptor) {
	vector<int> v;
    descriptor = descriptorGetHistogramPart(descriptor);
	string delimiter = ",";
	size_t pos = 0;
	string token;
	while ((pos = descriptor.find(delimiter)) != std::string::npos) {
    	token = descriptor.substr(0, pos);
		v.push_back(atoi( token.c_str() ));
    	descriptor.erase(0, pos + delimiter.length());
	}
	token = descriptor.substr(0, pos);
	v.push_back(atoi( token.c_str() ));
	return  v;
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



