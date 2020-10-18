#ifndef UTILS_H
#define UTILS_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

std::vector<int> gray2Hist(cv::Mat img);

#endif