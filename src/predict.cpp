#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "utils.h"
#include "formula.h"
#include "predict.h"
#include <iostream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
using namespace cv;
using namespace filesystem;

void predict(char* path_to_dataset, char* mode) {
    cout << "\x1B[32m-- START PREDICTION --\033[0m" << endl;
    cout << "\x1B[33mDATASET FOLDER: \033[0m" << path_to_dataset << endl;
    cout << "\x1B[33mTYPE: \033[0m" << mode << endl;
    string pathToDescriptorFile = current_path().string() + "/" + string(path_to_dataset) + "/" + LBP::GRAY + "/1" + LBP::TRAIN + "/descriptor.txt";
    string pathToDescriptorTestSet = current_path().string() + "/" + string(path_to_dataset) + "/" + LBP::GRAY + "/1" + LBP::TEST + "/" + LBP::CMFD;
    ifstream descriptorFile(pathToDescriptorFile);
    std::string line;
    string bestCandidatType;
    double minError = NULL;

    if(!descriptorFile) {
        cout << "Cant Open" << endl;
    }
    for(auto& p: directory_iterator(pathToDescriptorTestSet)) {
        Mat currentImg =  imread(p.path(), IMREAD_GRAYSCALE);
        vector<int> testDescriptorVector = gray2Hist(currentImg);
        cout << p.path() << endl;
        while (getline(descriptorFile, line)) {
            vector<int> trainDescriptorVector = grayDescriptor2Vector(line);
            double result = sad(testDescriptorVector, trainDescriptorVector);
            if(minError == NULL | minError > result ) {
                minError = result;
                // bestCandidatType = get
            }
            cout << result << endl;
        } 
        descriptorFile.clear();
        descriptorFile.seekg(0);
    }


};