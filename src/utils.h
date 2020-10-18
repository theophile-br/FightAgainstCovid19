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

std::vector<int> gray2Hist(cv::Mat img);

#endif