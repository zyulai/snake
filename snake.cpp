#include "snake.hpp"

#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>

namespace snake {
// Change these definitions to properly define the static members
Visual Snake::map(20, 20);
std::atomic<char> Snake::direct;
std::atomic<bool> Snake::running(true);

void Snake::init(int length, char direct) {
  map.init(length, direct);
  this->direct = direct;  // 初始化方向变量
  running = true;
}

void Snake::update() {
  bool alive = map.update(direct);
  if (!alive) {
    running = false;
  }
}

void Snake::visual() { map.visual(direct); }

void Snake::set_direct(char direct) { this->direct = direct; }

void Snake::run() {
  while (running) {
    visual();
    update();  // 更新蛇的位置

    if (!running) {
      std::cout << "\n游戏结束！按任意键退出...\n";
      break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));  // 适当的游戏速度
  }
}

void Snake::stop() { running = false; }
}  // namespace snake
