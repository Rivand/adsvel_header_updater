/**************************************************************************************************************************************************************
 * @file     file_list_reader.cpp
 * @author   Kuznetsov A.(RivandBlack).
 * @version  V 0.0.2
 * @date     29.09.2018
 * @brief    Class-singleton that reads files with a list of source code files, parses it and returns the corresponding list.
 ************************************************************************************************************************************************************/
#include "file_list_reader.h"
#include <fstream>
using ::std::ifstream;
using ::std::list;
using ::std::pair;
using ::std::string;

pair<bool, list<string>> FileListReader::ParseFileWithListOfSourceFiles(const string& in_file_name) {
    pair<bool, list<string>> answer{false, {}};
    // The file that you want to parse is CMakeLists.txt.
    if (in_file_name.compare("CMakeLists.txt")) {
        ifstream cmake_file;
        cmake_file.open("CMakeLists.txt", ifstream::in);
        if (!cmake_file.is_open()) return answer; // Could not open file.

        answer.first = true;
        return answer;
    }
    return answer;
}
