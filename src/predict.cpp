#include "predict.h"
#include <iostream>
using namespace std;

void predict(char* path_to_dataset, char* mode) {
    cout << "\x1B[32m-- START PREDICTION --\033[0m" << endl;
    cout << "\x1B[33mDATASET FOLDER: \033[0m" << path_to_dataset << endl;
    cout << "\x1B[33mTYPE: \033[0m" << mode << endl;
};