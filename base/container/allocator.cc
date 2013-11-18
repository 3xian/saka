#include "allocator.h"

namespace base {

void DiskAllocator::Load(int fd, bool need_init, int file_size) {
  file_size_ = file_size;

  if (need_init) {
  } else {
  }
}

bool DiskAllocator::Alloc(size_t size, char* head, size_t* offset) {
}

void DiskAllocator::Free(size_t size, char* head) {
}

bool DiskAllocator::GetByOffset(size_t offset, char* head) {
}

}  // namespace base
