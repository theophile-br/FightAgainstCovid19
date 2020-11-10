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
#include <ctime>

using namespace std;
using namespace cv;
using namespace filesystem;

void predict(char* path_to_dataset, char* mode){
    cout << "\x1B[32m-- START PREDICTION --\033[0m" << endl;
    cout << "\x1B[33mDATASET FOLDER: \033[0m" << path_to_dataset << endl;
    cout << "\x1B[33mTYPE: \033[0m" << mode << endl;
    if(strcmp(mode,"gray") == 0 ) {
        grayPredict(path_to_dataset);
    } else {
        colorPredict(path_to_dataset);
    }
};

void colorPredict(char* path_to_dataset){
    // ITERATE DATASET1 AND DATASET2
    for(int datasetNumber = 1; datasetNumber <= 2; datasetNumber++){
        time_t start = time(0);
        double success = 0;
        string pathToTestingSet = "";
        string pathToDescriptorFile = current_path().string() + "/" + string(path_to_dataset) + "/" + LBP::COLOR + "/" + to_string(datasetNumber) + LBP::TRAIN + "/descriptor.txt";
        ifstream descriptorFile(pathToDescriptorFile);
        std::string line;
        if(!descriptorFile) {
            cout << "Cant Open" << endl;
        }
        double result = 0;
        double numberOfImageProcess = 0;
        cout << "START TRAIN/TEST " << datasetNumber << endl;
        // ITERATE BETWEEN CMFD / IMFD
        for(int maskedTypeId = 0; maskedTypeId <= 1; maskedTypeId++ ) {
            string maskedType = "";
            if(maskedTypeId ==  0) {
                maskedType = LBP::CMFD;
            } else {
                maskedType = LBP::IMFD;
            };
            string pathToTestingSet = current_path().string() + "/" + string(path_to_dataset) + "/" + LBP::COLOR + "/" + to_string(datasetNumber) + LBP::TRAIN + "/" + maskedType;
            // ITERATE FOLDER
            for(auto& p: directory_iterator(pathToTestingSet)) {
                string bestCandidatType = "";
                double minError = 1.79769e+308;
                Mat currentImg =  imread(p.path(), IMREAD_COLOR);
                vector<vector<int>> testDescriptorVector = color2Hist(currentImg);
                while (getline(descriptorFile, line)) {
                    vector<vector<int>> trainDescriptorVector = colorDescriptor2Vector(line);
                    result = chisquare(trainDescriptorVector, testDescriptorVector);
                    if(minError > result ) {
                            minError = result;
                            bestCandidatType = descriptorGetType(line);
                    }
                }
                numberOfImageProcess++;
                if(bestCandidatType == maskedType ) {
                    success += 1;
                }
                descriptorFile.clear();
                descriptorFile.seekg(0, ios::beg);
                cout <<  "DATASETS NUM "<< datasetNumber << " " << maskedType << " : " << numberOfImageProcess << " images processed >> " <<  numberOfImageProcess / 10000 * 100 << "%" << endl;
                cout << "Chisquare " << " --- Predict : " <<  bestCandidatType << " --- MinError : " <<  minError <<  " --- Rate : " << success / numberOfImageProcess * 100 << " %" << endl;
                cout << "---" << endl;
            }
        }
        // SAVE FILE RESULT
        ofstream outfile;
        stringstream dataStreamString;
	    dataStreamString.str(string());
        time_t now = time(0);
        tm *ltm = localtime(&now);
        if(!exists(current_path().string() + "/results")) {
            create_directories(current_path().string() + "/results");
        }
        outfile.open(current_path().string() + "/results/" + to_string(ltm->tm_year) + "-" + to_string(ltm->tm_mon) + "-" + to_string(ltm->tm_mday) + "_" + to_string(ltm->tm_hour) + "h" + to_string(ltm->tm_min) + "m" + to_string(ltm->tm_sec) + "s-" + "COLOR_DATASET_" + to_string(datasetNumber)+ "-" + "result.txt");
        time_t end = time(0);
        double ltmDif = difftime(end,start);
        dataStreamString << "--------" << endl;
        dataStreamString << "TRAIN/TEST " << datasetNumber << " RESULT" << endl;
        dataStreamString << "TYPE : COLOR " << endl;
        dataStreamString << "Number Of Element : " << numberOfImageProcess << endl;
        dataStreamString << "Performance: " << to_string(ltmDif) << "sec" << endl;
        success = success / numberOfImageProcess * 100;
        dataStreamString << "Chisquare" << " sucess : \t\t" << success << "%" << endl;
        dataStreamString << "--------" << endl;
        outfile << dataStreamString.str();
        outfile.close();
    }
}


void grayPredict(char* path_to_dataset){
        vector<string> labelFormula = { "SumOfAbsDif", "Intersect", "Chisquare", "Bhattacharyya", "Correlation"};
    // ITERATE DATASET1 AND DATASET2
    for(int datasetNumber = 1; datasetNumber <= 2; datasetNumber++){
        time_t start = time(0);
        vector<double> success(5, 0);
        string pathToTestingSet = "";
        string pathToDescriptorFile = current_path().string() + "/" + string(path_to_dataset) + "/" + LBP::GRAY + "/" + to_string(datasetNumber) + LBP::TRAIN + "/descriptor.txt";
        ifstream descriptorFile(pathToDescriptorFile);
        std::string line;
        if(!descriptorFile) {
            cout << "Cant Open" << endl;
        }
        vector<double> result(5, 0);
        double numberOfImageProcess = 0;
        cout << "START TRAIN/TEST " << datasetNumber << endl;
        // ITERATE BETWEEN CMFD / IMFD
        for(int maskedTypeId = 0; maskedTypeId <= 1; maskedTypeId++ ) {
            string maskedType = "";
            if(maskedTypeId ==  0) {
                maskedType = LBP::CMFD;
            } else {
                maskedType = LBP::IMFD;
            };
            string pathToTestingSet = current_path().string() + "/" + string(path_to_dataset) + "/" + LBP::GRAY + "/" + to_string(datasetNumber) + LBP::TEST + "/" + maskedType;
            // ITERATE FOLDER
            for(auto& p: directory_iterator(pathToTestingSet)) {
                vector<string> bestCandidatType(5, "");
                vector<double> minError(5, 1.79769e+308);
                minError[4] = -1.0;
                Mat currentImg =  imread(p.path(), IMREAD_GRAYSCALE);
                vector<int> testDescriptorVector = gray2Hist(currentImg);
                while (getline(descriptorFile, line)) {
                    vector<int> trainDescriptorVector = grayDescriptor2Vector(line);
                    result[0] = sad(trainDescriptorVector, testDescriptorVector);
                    result[1] = intersect(trainDescriptorVector, testDescriptorVector);
                    result[2] = chisquare(trainDescriptorVector, testDescriptorVector);
                    result[3] = bhattacharyya(trainDescriptorVector, testDescriptorVector);
                    for(int i = 0; i < 4; i++) {
                        if(minError[i] > result[i] ) {
                            minError[i] = result[i];
                            bestCandidatType[i] = descriptorGetType(line);
                        }
                    }
                    // CORELATION SPECIAL LOGIC
                    result[4] = correlation(trainDescriptorVector, testDescriptorVector);
                    if(minError[4] < result[4] ) {
                        minError[4] = result[4];
                        bestCandidatType[4] = descriptorGetType(line);
                    }
                }
                numberOfImageProcess++;
                cout << " ----- " << endl;
                cout <<  "DATASETS NUM "<< datasetNumber << " " << maskedType << " : " << numberOfImageProcess << " images processed >> " <<  numberOfImageProcess / 10000 * 100 << "%" << endl;
                for(int i = 0; i < bestCandidatType.size(); i++) {
                    if(bestCandidatType[i] == maskedType ) {
                        success[i] += 1;
                    }
                    cout << labelFormula[i] << " --- Predict : " <<  bestCandidatType[i] << " --- MinError : " <<  minError[i] << " --- Rate : " << success[i] / numberOfImageProcess * 100 << " %" << endl;
                }
                descriptorFile.clear();

                descriptorFile.seekg(0, ios::beg);
            }
        }
        // SAVE FILE RESULT
        ofstream outfile;
        stringstream dataStreamString;
	    dataStreamString.str(string());
        time_t now = time(0);
        tm *ltm = localtime(&now);
        if(!exists(current_path().string() + "/results")) {
            create_directories(current_path().string() + "/results");
        }
        outfile.open(current_path().string() + "/results/" + to_string(ltm->tm_year) + "-" + to_string(ltm->tm_mon) + "-" + to_string(ltm->tm_mday) + "_" + to_string(ltm->tm_hour) + "h" + to_string(ltm->tm_min) + "m" + to_string(ltm->tm_sec) + "s-" + "GRAY_DATASET_" + to_string(datasetNumber)+ "-" + "result.txt");
        time_t end = time(0);
        double ltmDif = difftime(end,start);
        dataStreamString << "--------" << endl;
        dataStreamString << "TRAIN/TEST " << datasetNumber << " RESULT" << endl;
        dataStreamString << "Number Of Element : " << numberOfImageProcess << endl;
        dataStreamString << "TYPE : GRAY " << endl;
        dataStreamString << "Performance: " << to_string(ltmDif) << "sec" << endl;
        for(int i = 0; i < success.size(); i++){
            success[i] = (success[i] / numberOfImageProcess) * 100;
        }
        for(int i = 0; i < success.size(); i++) {
            dataStreamString << labelFormula[i] << " sucess : \t\t" << success[i] << "%" << endl;
        }
        dataStreamString << "--------" << endl;
        outfile << dataStreamString.str();
        outfile.close();
    }
}