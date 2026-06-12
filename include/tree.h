// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

struct Node {
  char value;
  std::vector<Node*> children;
};

class PMTree {
 private:
  Node* root;
  void build(Node* parent, std::vector<char> remaining) {
    if (remaining.empty()) return;
    std::sort(remaining.begin(), remaining.end());
    for (size_t i = 0; i < remaining.size(); ++i) {
      Node* child = new Node{remaining[i], {}};
      parent->children.push_back(child);
      std::vector<char> next_remaining = remaining;
      next_remaining.erase(next_remaining.begin() + i);
      build(child, next_remaining);
    }
  }

  void clear(Node* node) {
    for (auto child : node->children) {
      clear(child);
    }
    delete node;
  }

 public:
  explicit PMTree(std::vector<char> values) {
    root = new Node{0, {}};
    build(root, values);
  }

  ~PMTree() {
    clear(root);
  }

  Node* getRoot() const {
    return root;
  }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
