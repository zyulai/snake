#include "map.hpp"

#include <cassert>
#include <iostream>
#include <utility>

using namespace snake;  // NOLINT

void Visual::visual(const char direct) {
  system("clear");
  std::cout << "+";
  for (int j = 0; j < width; j++) {
    std::cout << "--+";
  }
  std::cout << std::endl;

  for (int i = 0; i < height; i++) {
    std::cout << "|";
    for (int j = 0; j < width; j++) {
      std::pair<int, int> current_pos = {i, j};
      if (i == nodes.front().first && j == nodes.front().second) {
        std::cout << " " << direct_symbol.at(direct) << "|";
      } else if (i == food.first && j == food.second) {
        std::cout << " @|";
      } else if (map_status.count({i, j})) {
        std::cout << " O|";
      } else {
        std::cout << "  |";
      }
    }
    std::cout << std::endl;

    std::cout << "+";
    for (int j = 0; j < width; j++) {
      std::cout << "--+";
    }
    std::cout << std::endl;
  }
}

void Visual::init(int length, const char direct) {
  assert(direct == 'a' || direct == 's' || direct == 'd' || direct == 'w');
  assert(!(direct == 'a' || direct == 'd') || length < height);
  assert(!(direct == 'w' || direct == 's') || length < width);

  if (direct == 'a') {
    for (int i = width - length; i < width; ++i) {
      map_status.insert({height / 2, i});
      nodes.push_back({height / 2, i});
    }
  } else if (direct == 'd') {
    for (int i = 0; i < length; ++i) {
      map_status.insert({height / 2, i});
      nodes.push_front({height / 2, i});
    }
  } else if (direct == 'w') {
    for (int i = height - length; i < height; ++i) {
      map_status.insert({i, width / 2});
      nodes.push_back({i, width / 2});
    }
  } else {
    for (int i = 0; i < length; ++i) {
      map_status.insert({i, width / 2});
      nodes.push_front({i, width / 2});
    }
  }

  set_food();
}

std::pair<int, int> Visual::update_node_with_direct(const std::pair<int, int> &node, const char direct) {
  assert(direct == 'a' || direct == 's' || direct == 'd' || direct == 'w');
  if (direct == 'a')
    return {node.first, node.second - 1};
  else if (direct == 'd')
    return {node.first, node.second + 1};
  else if (direct == 'w')
    return {node.first - 1, node.second};
  else  // direct == 's'
    return {node.first + 1, node.second};
}

bool Visual::is_valid_position(const Node &node) {
  if (node.first < 0 || node.first >= height || node.second < 0 || node.second >= width) {
    return false;
  }

  for (size_t i = 0; i < nodes.size() - 1; ++i) {
    if (nodes[i] == node) {
      return false;
    }
  }

  return true;
}

void Visual::update_snake_body(const char &direct) {
  std::pair<int, int> new_head = update_node_with_direct(nodes.front(), direct);
  nodes.push_front(new_head);
  map_status.insert(new_head);

  std::pair<int, int> tail = nodes.back();
  map_status.erase(tail);
  nodes.pop_back();
}

bool Visual::update(const char &direct) {
  Node new_head = update_node_with_direct(nodes.front(), direct);

  if (!is_valid_position(new_head)) {
    return false;
  }

  nodes.push_front(new_head);
  map_status.insert(new_head);

  if (new_head.first == food.first && new_head.second == food.second) {
    set_food();
  } else {
    Node tail = nodes.back();
    nodes.pop_back();
    map_status.erase(tail);
  }

  return true;
}

void Visual::set_food() {
  int x = rand() % height;
  int y = rand() % width;
  while (map_status.count({x, y})) {
    x = rand() % height;
    y = rand() % width;
  }
  food = {x, y};
  map_status.insert(food);
}
