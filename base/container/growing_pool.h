#pragma once

#include <vector>
#include "common/macro.h"

namespace base {

template<typename ElementType, size_t BlockSize>
class GrowingPool {
public:
    GrowingPool() : last_block_used(BlockSize) { }
    ~GrowingPool() { clear(); }

    void clear() {
        FOR_EACH (head_iter, heads_) { delete [] *head_iter; }
        heads_.clear();
        last_block_used = BlockSize;
    }

    ElementType* new_element() {
        if (last_block_used >= BlockSize) {
            heads_.push_back(new ElementType[BlockSize]);
            last_block_used = 0;
        }
        return heads_.back() + last_block_used++;
    }

    size_t blocks_count() const {
        return heads_.size();
    }

private:
    std::vector<ElementType*> heads_;
    size_t last_block_used;
};

}  // namespace base
