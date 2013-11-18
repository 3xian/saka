/**
 * @file thread.h
 * @brief 线程安全相关
 * @author daiwei
 * @version 1.0
 * @date 2012-11-26
 */

#pragma once

#include <pthread.h>
#include "common/class.h"

namespace base {

class Mutex : NonCopyable {
public:
    Mutex() { pthread_mutex_init(&mutex_, NULL); }
    ~Mutex() { pthread_mutex_destroy(&mutex_); }

    void lock() { pthread_mutex_lock(&mutex_); }
    void unlock() { pthread_mutex_unlock(&mutex_); }

private:
    pthread_mutex_t mutex_;

    friend class Cond;
};

class Cond : NonCopyable {
public:
    Cond() { pthread_cond_init(&cond_, NULL); }
    ~Cond() { pthread_cond_destroy(&cond_); }

    void wait(Mutex* mutex) { pthread_cond_wait(&cond_, &mutex->mutex_); }
    void signal() { pthread_cond_signal(&cond_); }

private:
    pthread_cond_t cond_;
};

class ScopedLock : NonCopyable {
public:
    explicit ScopedLock(Mutex* mutex) : mutex_(mutex) { mutex_->lock(); }
    ~ScopedLock() { mutex_->unlock(); }

private:
    Mutex* const mutex_;
};

class ReadWriteLock {
public:
    ReadWriteLock() { pthread_rwlock_init(&rwlock_, NULL); }
    ~ReadWriteLock() { pthread_rwlock_destroy(&rwlock_); }

    void read_lock() { pthread_rwlock_rdlock(&rwlock_); }
    void read_unlock() { pthread_rwlock_unlock(&rwlock_); }

    void write_lock() { pthread_rwlock_wrlock(&rwlock_); }
    void write_unlock() { pthread_rwlock_unlock(&rwlock_); }

private:
    pthread_rwlock_t rwlock_;
};

class ScopedReadLock : NonCopyable {
public:
    explicit ScopedReadLock(ReadWriteLock* rwlock) : rwlock_(rwlock) {
        rwlock_->read_lock();
    }
    ~ScopedReadLock() { rwlock_->read_unlock(); }

private:
    ReadWriteLock* const rwlock_;
};

class ScopedWriteLock : NonCopyable {
public:
    explicit ScopedWriteLock(ReadWriteLock* rwlock) : rwlock_(rwlock) {
        rwlock_->write_lock();
    }
    ~ScopedWriteLock() { rwlock_->write_unlock(); }

private:
    ReadWriteLock* const rwlock_;
};

}  // namespace base
