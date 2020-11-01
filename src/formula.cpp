#include "utils.h"

using namespace std;

int sad(vector<int> v1, vector<int> v2) {
    int sumOfDifference = 0;
    for(int i = 0; i < v1.size(); i++) {
        sumOfDifference += abs(v1[i] - v2[i]);
    }
    return sumOfDifference;
}
int intersect(vector<int> v1, vector<int> v2) {
    // Not Implemented
    return 42;
}
int corelation(vector<int> v1, vector<int> v2) {
    // Not Implemented
    return 42;
}
int chisquare(vector<int> v1, vector<int> v2) {
    float sumChiSquare = 0;
    for(int i = 0; i < v1.size(); i++) {
        if(v2[i] == 0) {
            continue;
        }
        sumChiSquare += ((v1[i] - v2[i]) * (v1[i] - v2[i])) / v2[i];
    }
    return (int) sumChiSquare;
}
int bhattacharyya(vector<int> v1, vector<int> v2) {
    float coefBhattacharyyaSum = 0;
        for(int i = 0; i < v1.size(); i++) {
        coefBhattacharyyaSum += sqrt(v1[i] * v2[i]);
    }
    return -log(coefBhattacharyyaSum);
}

int mse(vector<int> v1, vector<int> v2) {
    float coefBhattacharyyaSum = 0;
        for(int i = 0; i < v1.size(); i++) {
        coefBhattacharyyaSum += sqrt(v1[i] * v2[i]);
    }
    return -log(coefBhattacharyyaSum);
}