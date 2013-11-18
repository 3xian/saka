#include "string/encoding_converter.h"

namespace base {

void Iconv::set_encoding(const char* tocode, const char* fromcode) {
    ScopedLock l(&mutex_);

    if (is_iconv_opened_) {
        iconv_close(iconv_);
        iconv_ = iconv_open(tocode, fromcode);
    } else {
        iconv_ = iconv_open(tocode, fromcode);
        is_iconv_opened_ = true;
    }
}

std::string Iconv::convert(const std::basic_string<TWCHAR>& source) {
    char* src = (char*)(source.c_str());
    size_t srclen = (source.size() + 1) * sizeof(TWCHAR);

    ScopedLock l(&mutex_);
    if (buffer_size_ <= srclen) {
        delete [] buffer_;
        buffer_size_ = srclen + 1;
        buffer_ = new char[buffer_size_];
    }

    char* dst = buffer_;
    size_t dstlen = buffer_size_ - 1;

    iconv(iconv_, &src, &srclen, &dst, &dstlen);

    return std::string(buffer_, dst);
}

Iconv::Iconv() : is_iconv_opened_(false) {
    buffer_size_ = 512;
    buffer_ = new char[buffer_size_];
}

Iconv::~Iconv() {
    if (is_iconv_opened_) {
        iconv_close(iconv_);
    }
    delete [] buffer_;
}

}  // namespace base
