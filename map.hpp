#pragma once
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <utility>

// Add hash support for std::pair<int, int>
namespace std {
template <>
struct hash<pair<int, int>> {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};
}

namespace snake {
using Node = std::pair<int, int>;
class Visual {
 private:
  int width;
  int height;
  Node food;
  std::deque<Node> nodes;
  std::unordered_set<Node> map_status;
  const std::unordered_map<char, char> direct_symbol = {{'a', '<'}, {'d', '>'}, {'s', 'v'}, {'w', '^'}};
  Node update_node_with_direct(const Node &node, const char direct);
  void update_snake_body(const char &direct);
  void set_food();
  bool is_valid_position(const Node &node);

 public:
  Visual(int height, int width)
      : height(height),
        width(width) {};
  ~Visual() = default;
  void visual(const char direct);
  void init(int length, const char direct);
  bool update(const char &direct);
};
}  // namespace snake
