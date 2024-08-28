#pragma once

#include "storage/buffer_strategy.h"

namespace huadb {

struct Node {
  Node *next;
  Node *prev;
  size_t val = -1;
};
class LRUBufferStrategy : public BufferStrategy {
 public:
  void Access(size_t frame_no) override;
  size_t Evict() override;
  ~LRUBufferStrategy();
  
  private:
    Node *head = new Node();
};

}  // namespace huadb
