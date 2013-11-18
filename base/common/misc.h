#pragma once

#include <sstream>

namespace base {

template<typename SrcType, typename DstType>
DstType basic_convert(const SrcType& src) {
    DstType dst;
    std::stringstream ss;
    ss << src;
    ss >> dst;
    return dst;
}

}  // namespace base
