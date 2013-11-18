/**
 * @file string_utils.h
 * @brief 
 * @author daiwei
 * @version 1.0
 * @date 2012-11-27
 */

#pragma once

#include <string>
#include <vector>

namespace base {

std::string trim_front(const std::string& str);

std::string trim_back(const std::string& str);

std::string trim(const std::string& str);

bool utf8_to_uint32(const std::string& in, std::vector<uint32_t>* out);

}  // namespace base
