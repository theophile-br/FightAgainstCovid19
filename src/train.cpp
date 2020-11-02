#include "train.h"
#include "utils.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>

#include <fstream>

using namespace std;
using namespace cv;
using namespace filesystem;

void executeTrain(string path, string maskedType, int trainNumber, bool emptyDescriptor)
{
	cout << "\x1B[32m-- EXECUTING TRAINING " << trainNumber << " --\033[0m" << endl;
	cout << "\x1B[32m--      TYPE: " << maskedType << "      --\033[0m" << endl;
	string descriptorPath = path + "/descriptor.txt";
	ofstream outfile;
	string result;
	if (emptyDescriptor)
	{
		outfile.open(descriptorPath, ofstream::trunc);
	}
	else
	{
		outfile.open(descriptorPath, ios_base::app);
	}
	stringstream data;
	data.str(string());
	int count = 0;
	for (auto &p : directory_iterator(path + "/" + maskedType))
	{
		if (count <= 5000)
		{
			count++;
		}
		cout << "\r"
			 << "process: "
			 << " : " << (float)count / 5000.f * 100 << "%";
		Mat img = imread(p.path(), IMREAD_GRAYSCALE);
		vector<int> pblHist;
		pblHist.empty();
		data.clear();
		data.str(std::string());
		pblHist = gray2Hist(img);

		for (int i = pblHist.size() - 1; i >= 0; i--)
		{
			data << pblHist[i];
			if (i > 0)
			{
				data << ",";
			}
		}
		if (maskedType == LBP::CMFD)
		{
			result = "1";
		}
		else
		{
			result = "0";
		}
		outfile << data.str() << ":" + result << endl;
	}
	cout << "" << endl;
	cout << "\x1B[33m DONE \033[0m" << endl;
	outfile.close();
}

void train(char *path_to_dataset, char *mode)
{

	cout << "\x1B[32m-- START TRAINING --\033[0m" << endl;
	cout << "\x1B[33mDATA	SET FOLDER: \033[0m" << path_to_dataset << endl;
	cout << "\x1B[33mTYPE: \033[0m" << mode << endl;

	// Train 1 - Correct(CMFD)
	executeTrain("datasets/GRAY/1TRAIN", "CMFD", 1, true);
	// Train 1 - Incorrect(IMFD)
	executeTrain("datasets/GRAY/1TRAIN", "IMFD", 1, false);
	// Train 2 - Correct(CMFD)
	executeTrain("datasets/GRAY/2TRAIN", "CMFD", 2, true);
	// Train 2 - Incorrect(IMFD)
	executeTrain("datasets/GRAY/2TRAIN", "IMFD", 2, false);
};
