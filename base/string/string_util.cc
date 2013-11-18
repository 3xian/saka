#include <cctype>
#include "string_util.h"

namespace base {

std::string trim_front(const std::string& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        if (!isspace(str[i])) {
            return str.substr(i);
        }
    }
    return "";
}

std::string trim_back(const std::string& str) {
    for (int i = static_cast<int>(str.size()) - 1; i >= 0; --i) {
        if (!isspace(str[i])) {
            return str.substr(0, i + 1);
        }
    }
    return "";
}

std::string trim(const std::string& str) {
    return trim_back(trim_front(str));
}

bool utf8_to_uint32(const std::string& in, std::vector<uint32_t>* out) {
    out->clear();
    uint32_t key = 0;
    for (size_t i = 0; i < in.size(); ) {
        const char& ch = in[i];

        if ((ch & 0x80) == 0) {
            key = ch;
            ++i;
        } else if ((ch & 0xE0) == 0xC0) {
            if (i + 1 >= in.size()) {
                return false;
            }
            key = ((uint32_t)in[i] << 8 & 0xFF00) | ((uint32_t)in[i + 1] & 0xFF);
            i += 2;
        } else if ((ch & 0xF0) == 0xE0) {
            if (i + 2 >= in.size()) {
                return false;
            }
            key = ((uint32_t)in[i] << 16 & 0xFF0000) | ((uint32_t)in[i + 1] << 8 & 0xFF00) | ((uint32_t)in[i + 2] & 0xFF);
            i += 3;
        } else if ((ch & 0xF8) == 0xF0) {
            if (i + 3 >= in.size()) {
                return false;
            }
            key = ((uint32_t)in[i] << 24 & 0xFF000000) | ((uint32_t)in[i + 1] << 16 & 0xFF0000)
                | ((uint32_t)in[i + 2] << 8 & 0xFF00) | ((uint32_t)in[i + 3] & 0xFF);
            i += 4;
        } else {
            return false;
        }

        out->push_back(key);
    }
    return true;
}

}  // namespace base
