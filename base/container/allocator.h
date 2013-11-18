#include <cstddef>

namespace base {

class DiskAllocator {
 public:
  static const size_t kDefaultFileSize = (size_t)64 * 1024 * 1024 * 1024;  // Default 64GB
  static const size_t kMinBlockSize = 32;
  static const size_t kMaxBlockSize = 1073741824;

  void Load(int fd, bool need_init, int file_size = kDefaultFileSize);

  bool Alloc(size_t size, char* head, size_t* offset);
  void Free(size_t size, char* head);

  bool GetByOffset(size_t offset, char* head);

 private:
  size_t file_size_;
};

}  // namespace base
