#include "utils.h"

using namespace std;

double sad(int v1[256], int v2[256]) {
    double sumOfDifference = 0;
    for(int i = 0; i < 256; i++) {
        sumOfDifference += abs((double)v1[i] - (double)v2[i]);
    }
    return sumOfDifference;
}

double intersect(int v1[256], int v2[256]) {
    double intersectSum = 0;
    for(int i = 0; i < 256; i++) {    
        if(v1[i] == v2[i]) {
            continue;
        }
        intersectSum += min(v1[i],v2[i]);
    }
    return intersectSum;
}

double correlation(int v1[256], int v2[256]) {
    double mean_v1 = 0, mean_v2 = 0, dividend = 0, diviseur1 = 0, diviseur2 = 0;
        for(int i = 0; i < 256; i++) {
            mean_v1 += v1[i];
            mean_v2 += v2[i];
        }
        mean_v1 = mean_v1 / 256;
        mean_v2 = mean_v2 / 256;
        for(int i = 0; i < 256; i++) {
            dividend += (v1[i] - mean_v1)*(v2[i] - mean_v2);
            diviseur1 += (v1[i] - mean_v1)*(v1[i] - mean_v1);
            diviseur2 += (v2[i] - mean_v2)*(v2[i] - mean_v2);
        }
    return dividend / sqrt(diviseur1 * diviseur2);
}
double chisquare(int v1[256], int v2[256]) {
    double sumChiSquare = 0;
    for(int i = 0; i < 256; i++) {
        if(v2[i] == 0) {
            continue;
        }
        sumChiSquare += ((v1[i] - v2[i]) * (v1[i] - v2[i])) / v2[i];
    }
    return sumChiSquare;
}

double chisquare(int v1[3][256], int v2[3][256]) {
    double sumForAvgChiSquare = 0;
    vector<int> sumChiSquare(3,0);
    // cout << v1[2].size() << endl;
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < 256; i++) {
            if(v2[j][i] == 0) {
                continue;
            }
        sumChiSquare[j] += ((v1[j][i] - v2[j][i]) * (v1[j][i] - v2[j][i])) / v2[j][i];
        }
    }
    for(int i=0; i < 3; i++) {
        sumForAvgChiSquare += sumChiSquare[i];
    }
    return sumForAvgChiSquare / 3.0;
}

double bhattacharyya(int v1[256], int v2[256]) {
    double mean_v1 = 0, mean_v2 = 0, coefBhattacharyaSum = 0;
        for(int i = 0; i < 256; i++) {
            mean_v1 += v1[i];
            mean_v2 += v2[i];
            coefBhattacharyaSum += sqrt(v1[i] * v2[i]);
        }
    mean_v1 = mean_v1 / 256;
    mean_v2 = mean_v2 / 256;
    return sqrt( 1 - 
                (1 / sqrt( mean_v1 * mean_v2 * 256 * 256))
                * coefBhattacharyaSum);
}

double bhattacharyya(int v1[3][256], int v2[3][256]) {
    double bhattacharyaAggr = 0;
    for(int j = 0; j < 3; j++) {
        double mean_v1 = 0, mean_v2 = 0, coefBhattacharyaSum = 0;
        for (int i = 0; i < 256; i++) {
            mean_v1 += v1[j][i];
            mean_v2 += v2[j][i];
            coefBhattacharyaSum += sqrt(v1[j][i] * v2[j][i]);
        }
        mean_v1 = mean_v1 / 256;
        mean_v2 = mean_v2 / 256;
        bhattacharyaAggr = sqrt(1 -
                                (1 / sqrt(mean_v1 * mean_v2 * 256 * 256))
                                * coefBhattacharyaSum);
    }
    return bhattacharyaAggr;
}