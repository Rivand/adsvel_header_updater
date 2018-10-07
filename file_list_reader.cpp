/**************************************************************************************************************************************************************
 * @file     file_list_reader.cpp
 * @author   Kuznetsov A.(RivandBlack).
 * @version  V 0.0.4
 * @date     07.10.2018
 * @brief    Class-singleton that reads files with a list of source code files, parses it and returns the corresponding list.
 ************************************************************************************************************************************************************/
#include "file_list_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
using ::std::ifstream;
using ::std::list;
using ::std::pair;
using ::std::string;
using ::std::smatch;
using ::std::regex_replace;
using ::std::regex_search;

pair<bool, list<string>> FileListReader::ParseFileWithListOfSourceFiles(const string& in_file_name) {
    pair<bool, list<string>> answer{false, {}};
    // The file that you want to parse is CMakeLists.txt.
    if (!in_file_name.compare("CMakeLists.txt")) {
        ifstream cmake_file("CMakeLists.txt", ifstream::in);
        if (!cmake_file.is_open()) return answer; // Could not open file.
		std::stringstream ss;
		ss << cmake_file.rdbuf();
	    string cmake_file_content{ ss.str() };
		cmake_file_content = regex_replace(cmake_file_content,std::regex("\n")," "); // Remove all \n.
		cmake_file_content = regex_replace(cmake_file_content, std::regex("[ ]+"), " "); // Remove all unnecessary spaces.
		smatch sm_tmp;
        regex_search(cmake_file_content.cbegin(), cmake_file_content.cend(),sm_tmp, std::regex("add_executable.*?\\(.+\\)")); // Find the list of source files. 
		string file_list_s{sm_tmp.str()};
		file_list_s = regex_replace(file_list_s, std::regex("\\$\\{.+?\\}|add_executable|\\(|\\)|\""), ""); // Remove all variables,add_executable,"(", ")" and """.
		auto begin = file_list_s.cbegin();
		auto& file_list = answer.second;
        while (regex_search(begin, file_list_s.cend(), sm_tmp, std::regex("\\S+"))) {
			file_list.push_back(sm_tmp.str());
			begin += sm_tmp.position() + sm_tmp.length();
        };
        answer.first = true;
        return answer;
    }
    return answer;
}
