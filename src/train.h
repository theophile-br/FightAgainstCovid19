#ifndef TRAIN_H
#define TRAIN_H
#include <string>

void train(char *path_to_dataset, char *mode);
void executeGrayTrain(std::string path, std::string maskedType, int trainNumber, bool emptyDescriptor);
void executeColorTrain(std::string path, std::string maskedType, int trainNumber, bool emptyDescriptor);
#endif