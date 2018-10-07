/**************************************************************************************************************************************************************
 * @file     file_updater.h
 * @author   Kuznetsov A.(RivandBlack).
 * @version  V 0.0.4
 * @date     07.10.2018
 * @brief    Class-singleton that updates file header if it is doxygen compatible.
 ************************************************************************************************************************************************************/
#pragma once
#include <string>
class FileUpdater {
public:
	static bool UpdateFile(const std::string& in_file_name, const std::string& in_version_name);
};
