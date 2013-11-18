#pragma once

#include <string>
#include <iconv.h>
#include "common/class.h"
#include "common/singleton.h"
#include "common/thread.h"

namespace base {

typedef unsigned int TWCHAR;

class Iconv : NonCopyable {
public:
    void set_encoding(const char* tocode, const char* fromcode);

    std::string convert(const std::basic_string<TWCHAR>& source);

private:
    Iconv();
    ~Iconv();

    bool is_iconv_opened_;
    iconv_t iconv_;
    char* buffer_;
    size_t buffer_size_;
    Mutex mutex_;

    template<typename> friend class Singleton;
};

typedef Singleton<Iconv> EncodingConverter;

}  // namespace base
