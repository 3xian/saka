#pragma once

#include <fstream>
#include <string>
#include "common/class.h"

namespace base {

bool read_file_to_string(const std::string& filename, std::string* data);

bool write_string_to_file(const std::string& str, const std::string& filename);

class FileAppender : NonCopyable {
public:
    FileAppender();
    virtual ~FileAppender();
    bool open(const std::string& path);
    void close();
    void write(const std::string& content);
    void flush();
    const char* path() const;

private:
    FILE* file_;
    std::string path_;
};
//
}  // namespace base
