#include <iostream>
#include "predict.h"
#include "train.h"
#include <filesystem>

using namespace std;
using namespace filesystem;

void printUsage(char** argv);
int parseCmdArgs(int argc, char** argv);

int main(int argc, char* argv[])
{
    int retval = parseCmdArgs(argc, argv);
    if (retval) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
void printUsage()
{
    cout <<
         "Accept only three argument.\n"
         "Argument:\n"
         "  --type <train|predict>    -t\n"
         "      train the model by producing a descriptor or predict the training set with different distance formula\n"
         "  --mode <color|gray>         -m\n"
         "      specify the nature of the images\n"
         "Example :\n"
         "FightAgainstCovid19 -t train -m gray <path_to_dataset>\n"
         << endl;
}

int parseCmdArgs(int argc, char** argv)
{
    char *mode = (char *)"gray";
    char *type = (char *)"train";
    char *path = (char *)"datasets";
    if (argc == 1) {
        printUsage();
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "--help" || string(argv[i]) == "-h") {
            printUsage();
            return EXIT_FAILURE;
        } else if (string(argv[i]) == "--mode" || string(argv[i]) == "-m") {
            mode = argv[i+1];
            if(string(mode) == "gray" && string(mode) == "color") {
                cout << "Wrong mode argument " << mode << endl;
                printUsage();
                return EXIT_FAILURE;
            }
            i++;
        } else if (string(argv[i]) == "--type" || string(argv[i]) == "-t")  {
            type = argv[i+1];
            if(string(type) == "train" && string(type) == "predict") {
                cout << "Wrong type argument " << type << endl;
                printUsage();
                return EXIT_FAILURE;
            }
            i++;
        } else {
            path = argv[i];
			if(!is_directory( current_path().string() + "/" + path)) {
				cout << current_path().string() + "/" + path << " isn't a directory" << endl;
				printUsage();
				return EXIT_FAILURE;
			}
        }
    }
    if(type == string("predict")){
        predict(path, mode);
    } else {
        train(path, mode);
    }
    return EXIT_SUCCESS;
}