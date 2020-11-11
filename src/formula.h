#ifndef FORMULA_H
#define FORMULA_H
using namespace std;

double sad(int v1[256], int v2[256]);
double intersect(int v1[256], int v2[256]);
double correlation(int v1[256], int v2[256]);
double chisquare(int v1[256], int v2[256]);
double chisquare(int v1[3][256], int v2[3][256]);
double bhattacharyya(int v1[256], int v2[256]);
double bhattacharyya(int v1[3][256], int v2[3][256]);
#endif