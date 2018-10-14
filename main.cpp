/**************************************************************************************************************************************************************
 * @file     main.cpp
 * @author   Kuznetsov A.(RivandBlack).
 * @version  V 0.0.2
 * @date     29.09.2018
 * @brief    SdHeaderUpdater - An application that automatically updates the version and time in doxygen headers of all source files.
 ************************************************************************************************************************************************************/
#include <iostream>
#include <string>
#include "file_list_reader.h"
#include "file_updater.h"
using ::std::cout;
using ::std::endl;
using ::std::flush;
using ::std::ifstream;
using ::std::string;

int main(const int argc, char* argv[]) {
    if (argc == 1) {
        // The application was started without arguments.
        cout << "SdHeaderUpdater application, type --help for help." << flush << endl;
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        string current_command(argv[i]);
        if (!current_command.compare("update")) {
            string version_name{};
            if (i < argc - 1) {
                for (int j = i + 1; j < argc; j++) version_name.append(std::string(argv[j]) + " ");
                i = argc;
            } else {
                cout << "You must give the version number, for example 'v 0.2.1'" << flush << endl;
                return 0;
            }
            auto [flag, list_of_source_files] = FileListReader::ParseFileWithListOfSourceFiles("CMakeLists.txt");
            if (!flag) {
                cout << "Could not process the file with the list of source files." << flush << endl;
                return 0;
            }
            for (auto& c : list_of_source_files) {
                auto [status_b, status_s] = FileUpdater::UpdateFile(c, version_name);
                cout << c << " - " << status_s << flush << endl;
            }
            cout << "All files have been processed." << flush << endl;
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
