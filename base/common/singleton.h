#pragma once

#include "common/class.h"
#include "common/thread.h"

namespace base {

template<typename T>
class Singleton : NonCopyable {
public:
    static T& instance() {
        if (instance_ == NULL) {
            ScopedLock lock(&mutex_);
            if (instance_ == NULL) {  // double lock check
                instance_ = new T;
            }
        }
        return *instance_;
    }

private:
    Singleton();
    ~Singleton();

    static T* instance_;
    static Mutex mutex_;
};

template<typename T> T* Singleton<T>::instance_ = NULL;
template<typename T> Mutex Singleton<T>::mutex_;

}  // namespace base
