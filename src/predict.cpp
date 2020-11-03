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
    string pathToTestingSet = current_path().string() + "/" + string(path_to_dataset) + "/" + LBP::GRAY + "/1" + LBP::TRAIN + "/" + LBP::IMFD;
    ifstream descriptorFile(pathToDescriptorFile);
    std::string line;
    if(!descriptorFile) {
        cout << "Cant Open" << endl;
    }
    for(auto& p: directory_iterator(pathToTestingSet)) {
        vector<string> bestCandidatType(5, "");
        vector<double> minError(5, -1);
        vector<double> result(5, 0);
        vector<double> performance(5, NAN);
        Mat currentImg =  imread(p.path(), IMREAD_GRAYSCALE);
        vector<int> testDescriptorVector = gray2Hist(currentImg);
        cout << p.path() << endl;
        while (getline(descriptorFile, line)) {
            vector<int> trainDescriptorVector = grayDescriptor2Vector(line);
            // for(int i = 0; i < trainDescriptorVector.size(); i++) {
            //     cout << trainDescriptorVector[i] << ","; 
            // }
            // cout << endl;
            for(int i = 0; i < trainDescriptorVector.size(); i++) {
                cout << testDescriptorVector[i] << ","; 
            }
            cout << endl;

            result[0] = sad(testDescriptorVector, trainDescriptorVector);
            result[1] = intersect(testDescriptorVector, trainDescriptorVector);
            result[2] = correlation(testDescriptorVector, trainDescriptorVector);
            result[3] = chisquare(testDescriptorVector, trainDescriptorVector);
            result[4] = bhattacharyya(testDescriptorVector, trainDescriptorVector);
            for(int i = 0; i < minError.size(); i++) {
                if(minError[i] == -1 || minError[i] > result[i] ) {
                    minError[i] = result[i];
                    bestCandidatType[i] = grayDescriptorGetType(line);
                }
            }
        } 
        for(int i = 0; i < minError.size(); i++) {
            cout << "--------" << endl;
            cout << "Erreur Min : " << minError[i] << endl;
            cout << "Deduction : " << bestCandidatType[i] << endl;
            cout << "--------" << endl;
        }
        descriptorFile.clear();
        descriptorFile.seekg(0);
    }


};