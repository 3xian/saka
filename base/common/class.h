/**
 * @file class.h
 * @brief 
 * @author daiwei
 * @version 1.0
 * @date 2012-11-26
 */

#pragma once

namespace base {

class NonCopyable {
protected:
    NonCopyable() { }
    ~NonCopyable() { }

private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator =(const NonCopyable&);
};

template<typename T>
class ScopedSweeper {
public:
    ScopedSweeper(T* p) : p_(p) { }
    ~ScopedSweeper() { delete p_; }

protected:
    T* p_;
};

}  // namespace base
