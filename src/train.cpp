#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "train.h"
#include <iostream>

using namespace std;
using namespace cv;

void train(char* path_to_dataset, char* mode) {
    cout << "\x1B[32m-- START TRAINING --\033[0m" << endl;
    cout << "\x1B[33mDATASET FOLDER: \033[0m" << path_to_dataset << endl;
    cout << "\x1B[33mTYPE: \033[0m" << mode << endl;
};

