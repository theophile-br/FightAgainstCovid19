#include "utils.h"

using namespace std;

double sad(vector<int> v1, vector<int> v2) {
    double sumOfDifference = 0;
    for(int i = 0; i < v1.size(); i++) {
        sumOfDifference += abs((double)v1[i] - (double)v2[i]);
    }
    return sumOfDifference;
}

double intersect(vector<int> v1, vector<int> v2) {
    double intersectSum = 0;
    for(int i = 0; i < v1.size(); i++) {    
        if(v1[i] == v2[i]) {
            continue;
        }
        intersectSum += min(v1[i],v2[i]);
    }
    return intersectSum;
}

double correlation(vector<int> v1, vector<int> v2) {
    double mean_v1 = 0, mean_v2 = 0, dividend = 0, diviseur1 = 0, diviseur2 = 0;
        for(int i = 0; i < v1.size(); i++) {
            mean_v1 += v1[i];
            mean_v2 += v2[i];
        }
        mean_v1 = mean_v1 / v1.size();
        mean_v2 = mean_v2 / v2.size();
        for(int i = 0; i < v1.size(); i++) {
            dividend += (v1[i] - mean_v1)*(v2[i] - mean_v2);
            diviseur1 += (v1[i] - mean_v1)*(v1[i] - mean_v1);
            diviseur2 += (v2[i] - mean_v2)*(v2[i] - mean_v2);
        }
    return dividend / sqrt(diviseur1 * diviseur2);
}
double chisquare(vector<int> v1, vector<int> v2) {
    double sumChiSquare = 0;
    for(int i = 0; i < v1.size(); i++) {
        if(v2[i] == 0) {
            continue;
        }
        sumChiSquare += ((v1[i] - v2[i]) * (v1[i] - v2[i])) / v2[i];
    }
    return sumChiSquare;
}

double chisquare(vector<vector<int>> v1, vector<vector<int>> v2) {
    double sumForAvgChiSquare = 0;
    vector<int> sumChiSquare(3,0);
    for(int j = 0; j < v1.size(); j++) {
        for(int i = 0; i < v1[j].size(); i++) {
            if(v2[j][i] == 0) {
                continue;
            }
        sumChiSquare[j] += ((v1[j][i] - v2[j][i]) * (v1[j][i] - v2[j][i])) / v2[j][i];
        }
    }
    for(int i=0; i < sumChiSquare.size(); i++) {
        sumForAvgChiSquare += sumChiSquare[i];
    }
    return sumForAvgChiSquare / sumChiSquare.size();
}

double bhattacharyya(vector<int> v1, vector<int> v2) {
    double mean_v1 = 0, mean_v2 = 0, coefBhattacharyaSum = 0;
        for(int i = 0; i < v1.size(); i++) {
            mean_v1 += v1[i];
            mean_v2 += v2[i];
            coefBhattacharyaSum += sqrt(v1[i] * v2[i]);
        }
    mean_v1 = mean_v1 / v1.size();
    mean_v2 = mean_v2 / v2.size();
    return sqrt( 1 - 
                (1 / sqrt( mean_v1 * mean_v2 * v1.size() * v1.size()))
                * coefBhattacharyaSum);
}