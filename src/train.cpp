#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <iostream>
#include "train.h"

using namespace std;
using namespace cv;
using namespace filesystem;

void train(char* path_to_dataset, char* mode) {
    cout << "\x1B[32m-- START TRAINING --\033[0m" << endl;
    cout << "\x1B[33mDATA	SET FOLDER: \033[0m" << path_to_dataset << endl;
    cout << "\x1B[33mTYPE: \033[0m" << mode << endl;

	Mat img = imread("/home/teto/Documents/pbl_masked/datasets/GRAY/1TRAIN/CMFD/00001_Mask.jpg", IMREAD_GRAYSCALE);
	vector<uchar> v;
	for(int i=1; i<img.rows - 1; i++) {
    	for(int j=1; j<img.cols - 1; j++) {
			vector<int> bits;
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
			int decimalValue = 0;
			for (int i = 0; i < bits.size(); i++) {
				decimalValue = decimalValue + bits[i] * (1<<(bits.size()-i-1));
			}
			v.push_back(decimalValue);
		}
	}
	
	Mat my_mat(img.rows - 2,img.cols - 2,CV_8UC1,v.data());
	imshow("Display window", my_mat);
    int k = waitKey(0); // Wait for a keystroke in the window
};
