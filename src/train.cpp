#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include "train.h"
#include "utils.h"
#include <fstream>

using namespace std;
using namespace cv;
using namespace filesystem;

void train(char* path_to_dataset, char* mode) {
	string maskedType = "CMFD";
	ofstream outfile("descriptor.txt");
	outfile << "";
	outfile.close();
    cout << "\x1B[32m-- START TRAINING --\033[0m" << endl;
    cout << "\x1B[33mDATA	SET FOLDER: \033[0m" << path_to_dataset << endl;
    cout << "\x1B[33mTYPE: \033[0m" << mode << endl;
    cout << "\x1B[33mTYPE: \033[0m" << maskedType << endl;
	outfile.open("descriptor.txt", ios_base::app);
	
	Mat img = imread("/home/teto/Documents/pbl_masked/datasets/GRAY/1TRAIN/CMFD/00000_Mask.jpg", IMREAD_GRAYSCALE);
	vector<int> pblHist = gray2Hist(img);
	stringstream data;
	data.str(string());
	for (int i = pblHist.size() -1; i >= 0; i--) {
		data << pblHist[i];
		if(i > 0) {
		 	data << ",";
		}
	}
	if(maskedType == "CMFD") {
		data << 1;
	} else {
		data << 0;
	}
	outfile << ":" << data.str() << endl;
	outfile.close();
	cout << LBP::CMFD;
};
