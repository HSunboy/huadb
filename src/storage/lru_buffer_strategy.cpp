#include "storage/lru_buffer_strategy.h"
#include <iostream>
namespace huadb {

LRUBufferStrategy::~LRUBufferStrategy() {
  std::cout << "destory" << std::endl;
  Node *cur = head;
  while (cur != nullptr) {
    auto next = cur->next;
    delete cur;
    cur = next;
  }
  return;
}

void LRUBufferStrategy::Access(size_t frame_no) {
  // 缓存页面访问
  // LAB 1 BEGIN
  /**
   * 如果 frame_no 不存在于链表中，将其插入到链表头部
   */
  Node *cur = head;
  /**
   * 先查找是否在链表中
   */

  while (cur != nullptr) {
    if (cur->val == frame_no) {
      break;
    }
    cur = cur->next;
  }
  if (cur != nullptr) {
    /**
     * 存在，放到首部
     */
    auto prev = cur->prev;
    auto next = cur->next;
    prev->next = next;
    if (next != nullptr) {
      next->prev = prev;
    }
    cur->next = head->next;
    cur->prev = head;
    if (head->next != nullptr) {
      head->next->prev = cur;
    }
    head->next = cur;
  } else {
    /**
     * 不存在，插入到首部
     */
    auto new_node = new Node();
    new_node->val = frame_no;

    new_node->next = head->next;
    new_node->prev = head;
    if (head->next != nullptr) {
      head->next->prev = new_node;
    }
    head->next = new_node;
  }
  return;
};

size_t LRUBufferStrategy::Evict() {
  // 缓存页面淘汰，返回淘汰的页面在 buffer pool 中的下标
  // LAB 1 BEGIN
  Node *cur = head;
  while (cur->next != nullptr) {
    cur = cur->next;
  }
  if (cur == head) {
    return 0;
  }
  size_t res = cur->val;
  cur->prev->next = nullptr;
   delete cur;
  return res;
}

}  // namespace huadb
