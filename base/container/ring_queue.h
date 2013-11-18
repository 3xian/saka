/**
 * @file ring_queue.h
 * @brief 可O(1)下标访问的双端循环队列
 * @author daiwei
 * @version 1.0
 * @date 2012-12-18
 */

#pragma once

namespace base {

template<typename T>
class RingQueue {
public:
    RingQueue(size_t cap = 0) {
        init(cap);
    }

    RingQueue(const RingQueue& other) {
        init(other.capacity());
        for (size_t i = 0; i < other.size(); ++i) {
            push_back(other.at(i));
        }
    }

    RingQueue& operator =(const RingQueue& other) {
        reset(other.capacity());
        for (size_t i = 0; i < other.size(); ++i) {
            push_back(other.at(i));
        }
        return *this;
    }

    ~RingQueue() {
        destroy();
    }

    size_t capacity() const {
        return capacity_;
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    bool full() const {
        return size_ == capacity_;
    }

    void reset(size_t new_capacity) {
        destroy();
        init(new_capacity);
    }

    bool push_back(const T& item) {
        if (size_ == capacity_) {
            return false;
        }
        buffer_[end_offset_] = item;
        end_offset_ = next(end_offset_);
        ++size_;
        return true;
    }

    bool pop_front(T* item = NULL) {
        if (size_ == 0) {
            return false;
        }
        if (item != NULL) {
            *item = buffer_[begin_offset_];
        }
        begin_offset_ = next(begin_offset_);
        --size_;
        return true;
    }

    const T& front() const {
        return buffer_[begin_offset_];
    }

    const T& back() const {
        if (end_offset_ > 0) {
            return buffer_[end_offset_ - 1];
        } else {
            return buffer_[capacity_ - 1];
        }
    }

    const T& at(int index) const {
        return buffer_[(begin_offset_ + index) % capacity_];
    }

    T& at(int index) {
        return buffer_[(begin_offset_ + index) % capacity_];
    }

private:
    size_t next(int index) const {
        return (index + 1) % capacity_;
    }

    void destroy() {
        if (capacity_ > 0) {
            delete [] buffer_;
        }
    }

    void init(size_t cap = 0) {
        size_ = 0;
        begin_offset_ = 0;
        end_offset_ = 0;
        capacity_ = cap;
        if (capacity_ > 0) {
            buffer_ = new T[capacity_];
        } else {
            buffer_ = NULL;
        }
    }

    size_t size_;
    size_t begin_offset_;
    size_t end_offset_;
    size_t capacity_;
    T* buffer_;
};

}  // namespace base
