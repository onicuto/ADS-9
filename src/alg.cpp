// Copyright 2022 NNTU-CS
#include <vector>
#include "tree.h"

void collectPerms(Node* node, std::vector<char> current,
                  std::vector<std::vector<char>>& all) {
  if (node->value != 0) {
    current.push_back(node->value);
  }
  if (node->children.empty()) {
    if (!current.empty()) {
      all.push_back(current);
    }
    return;
  }
  for (auto child : node->children) {
    collectPerms(child, current, all);
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> all;
  collectPerms(tree.getRoot(), {}, all);
  return all;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  std::vector<std::vector<char>> all = getAllPerms(tree);
  if (num > 0 && num <= static_cast<int>(all.size())) {
    return all[num - 1];
  }
  return {};
}

long long factorial(int n) {
  long long res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  if (num <= 0) return {};

  Node* curr = tree.getRoot();
  std::vector<char> res;

  // Determine total elements N
  // The first level children count is N.
  int N = curr->children.size();
  if (N == 0) return {};

  long long total = factorial(N);
  if (num > total) return {};

  int current_depth = 0;
  while (!curr->children.empty()) {
    // Each child at depth current_depth+1 represents (N - (current_depth+1))! permutations
    long long sub_count = factorial(N - (current_depth + 1));
    int child_idx = (num - 1) / sub_count;
    if (child_idx >= static_cast<int>(curr->children.size())) return {};

    curr = curr->children[child_idx];
    res.push_back(curr->value);
    num -= child_idx * sub_count;
    current_depth++;
  }

  return res;
}
