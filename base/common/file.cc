#include <cstdio>
#include "common/file.h"

namespace base {

bool read_file_to_string(const std::string& filename, std::string* data) {
    FILE* fp = fopen(filename.c_str(), "rb");
    if (fp == NULL) {
        return false;
    }

    data->clear();
    while (!feof(fp)) {
        char buf[4096];
        size_t ret = fread(buf, 1, 4096, fp);
        if (ret == 0 && ferror(fp)) {
            fclose(fp);
            return false;
        }
        data->append(std::string(buf, ret));
    }

    fclose(fp);
    return true;
}

bool write_string_to_file(const std::string& str, const std::string& filename) {
    FILE* fp = fopen(filename.c_str(), "wb");
    if (fp == NULL) {
        return false;
    }

    int ret = fwrite(str.data(), str.size(), 1, fp);
    if (ret != 1) {
        fclose(fp);
        return false;
    }

    fclose(fp);
    return true;
}

FileAppender::FileAppender() {
    file_ = NULL;
}

FileAppender::~FileAppender() {
    close();
}

bool FileAppender::open(const std::string& path) {
    close();
    file_ = fopen(path.c_str(), "a");
    if (file_ != NULL) {
        path_ = path;
        return true;
    } else {
        return false;
    }
}

void FileAppender::close() {
    if (file_ != NULL) {
        fclose(file_);
        file_ = NULL;
    }
    path_ = "";
}

void FileAppender::write(const std::string& content) {
    fwrite(content.c_str() , 1 , content.size(), file_);
}

void FileAppender::flush() {
    fflush(file_);
}

const char* FileAppender::path() const {
    return path_.c_str();
}

}  // namespace base
