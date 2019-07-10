/**************************************************************************************************************************************************************
 * @file     file_updater.cpp
 * @author   Kuznetsov A.(RivandBlack).
 * @version  V 0.0.4
 * @date     07.10.2018
 * @brief    Class-singleton that updates file header if it is doxygen compatible.
 ************************************************************************************************************************************************************/
#include "file_updater.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
using ::std::ifstream;
using ::std::ofstream;
using ::std::ostringstream;
using ::std::pair;
using ::std::regex;
using ::std::setw;
using ::std::string;
using ::std::vector;
pair<bool, string> FileUpdater::UpdateFile(const std::string& in_file_name, const std::string& in_version_name) {
    pair<bool, std::string> answer{false, "Unknown state"};
    ifstream in_source_file(in_file_name, ifstream::in);
    if (!in_source_file.is_open()) {
        answer.second = "can't open file.";
        return answer;
    }
    // Get the last modified time of the file.
    auto last_write_file_time = std::filesystem::last_write_time(in_file_name);
    time_t tt = std::chrono::system_clock::to_time_t(last_write_file_time);
    tm tast_write_file_time_in_tm = *std::localtime(&tt);
    ostringstream oss_last_write_time;
    oss_last_write_time << std::setfill('0') << setw(2) << tast_write_file_time_in_tm.tm_mday << "." << setw(2) << tast_write_file_time_in_tm.tm_mon << "." << 1900 + tast_write_file_time_in_tm.tm_year << " " << setw(2) << tast_write_file_time_in_tm.tm_hour << ":" << setw(2) << tast_write_file_time_in_tm.tm_min << ":"
                        << setw(2) << tast_write_file_time_in_tm.tm_sec << std::flush << std::endl;
    string last_write_time_str_real{oss_last_write_time.str()};
    last_write_time_str_real.pop_back();  // Remove endl;

    // Read the file.
    vector<string> source_file_content;
    string str{};
    while (std::getline(in_source_file, str)) {
        source_file_content.push_back(std::move(str));
    }
    in_source_file.close();

    // Find the line with the date.
    string last_write_time_str_doxy{};
    for (auto& c : source_file_content) {
        std::smatch find_match;
        if (std::regex_search(c.cbegin(), c.cend(), find_match, regex(".*?@date[\\s\\t]+?\\d"))) {
            last_write_time_str_doxy = string(c.begin() + find_match.length() - 1, c.end());
            if (!last_write_time_str_doxy.compare(last_write_time_str_real)) {  // The dates and times are the same and you do not need to update the file.
                answer.second = "no file update required.";
                return answer;
            } else {  // Update the line with date and time.
                c = string(c.begin(), c.begin() + find_match.length() - 1);
                c.append(last_write_time_str_real);
            }
        };
    }
    if (!last_write_time_str_doxy.size()) {  // Are unable to find the row with the field "@data".
        answer.second = "could not find date field.";
        return answer;
    }
    // Find the line with the name of the version and replace it if necessary.
    for (auto& c : source_file_content) {
        std::smatch find_match;
        if (std::regex_search(c.cbegin(), c.cend(), find_match, regex(".*?@version[\\s\\t]+?[\\w]"))) {
            c = string(c.begin(), c.begin() + find_match.length() - 1);
            c.append(in_version_name);
        };
    }
    // Overwrite file.
    std::ofstream out_source_file(in_file_name);
    for (const auto& c : source_file_content) out_source_file << c << std::endl;
    out_source_file.close();

    // Set the time of the last file change is the same as now specified in the doxygen description.
    std::filesystem::last_write_time(in_file_name, last_write_file_time);

    answer.first = true;
    answer.second = "file has been updated.";
    return answer;
}
