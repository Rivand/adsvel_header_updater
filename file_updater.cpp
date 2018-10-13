/**************************************************************************************************************************************************************
 * @file     file_updater.cpp
 * @author   Kuznetsov A.(RivandBlack).
 * @version  V 0.0.4
 * @date     07.10.2018
 * @brief    Class-singleton that updates file header if it is doxygen compatible.
 ************************************************************************************************************************************************************/
#include "file_updater.h"
#include <fstream>
#include <iostream>
using ::std::pair;
using ::std::string;
using ::std::ifstream;
pair<bool, string> FileUpdater::UpdateFile(const std::string& in_file_name, const std::string& in_version_name) {
    pair<bool, std::string> answer{false, "Unknown state"};
    ifstream source_file(in_file_name, ifstream::in);
    if (!source_file.is_open()){
        answer.second = "can't open file.";
        return answer;
    }
    return answer;
}
