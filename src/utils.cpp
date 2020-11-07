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
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			vector<uchar> bits;
			int center_pixel = img.at<uchar>(i, j);
			for (int y = i + 1; y >= i - 1; y--)
			{
				for (int x = j + 1; x >= j - 1; x--)
				{
					if (x == j && y == i)
						continue;
					int curent_pixel = img.at<uchar>(y, x);
					if (center_pixel >= curent_pixel)
					{
						bits.push_back(1);
					}
					else
					{
						bits.push_back(0);
					}
				}
			}
			uchar decimalValue = 0;
			for (int i = bits.size() - 1; i > 0; i--)
			{
				decimalValue = decimalValue * 2 + bits[i];
			}
			pblHist[decimalValue]++;
		}
	}
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
	for (int i = 0; i < 3; i++){
		size_t pos = 0;
		string token;
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
		v[i].push_back(atoi( token.c_str() ));
		descriptor.erase(0, pos + delimiter.length());
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



