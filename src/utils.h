#ifndef UTILS_H
#define UTILS_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>

class LBP {
	public:
    	static const std::string CMFD;
		static const std::string IMFD;
		static const std::string COLOR;
		static const std::string GRAY;
    	static const std::string TRAIN;
    	static const std::string TEST;
};

void gray2Hist(cv::Mat &img, int lbpHist[256]);
void color2Hist(cv::Mat &img, int lbpHist[3][256]);
std::string descriptorGetType(std::string descriptor);
void grayDescriptor2Vector(std::string descriptor, int v[256]);
std::string descriptorGetHistogramPart(std::string descriptor);
void colorDescriptor2Vector(std::string descriptor, int v[3][256]);

#endif