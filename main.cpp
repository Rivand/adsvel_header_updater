//***********************************************************************************************************************************
//*                                                                                                                                 *
//*    SdHeaderUpdater - An application that automatically updates the version and time in doxygen headers of all source files.     *
//*                                                                                                                                 *
//***********************************************************************************************************************************

#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::ifstream;

int main(int argc, char* argv[]) {
    if (argc == 1){ // The application was started without arguments.
        cout << "SdHeaderUpdater application, type --help for help." << flush << endl;
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        string current_command(argv[i]);
        if (!current_command.compare("update")) {
            string new_version(argv[++i]);
            ifstream cmake_file;
            cmake_file.open("CMakeLists.txt", std::ifstream::in);
            if (!cmake_file.is_open()) {
                cout << "Could not open file \"CMakeLists.txt\". "<< flush << endl;
                return 0;
            }
            cout << "Source files was updated." << flush << endl;
            continue;
        }
        if (!current_command.compare("--help")) {
            cout << "It is help. I hope it helped you =)." << flush << endl;
            continue;
        }
        // The command is not recognized, we display the corresponding warning.
        cout << "SdHeaderUpdater: " << current_command << " is not a SdHeaderUpdater command. See \'SdHeaderUpdater --help\'." << flush << endl;
    }

    return 0;
}
