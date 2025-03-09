#include "snake.hpp"
#include <iostream>
#include <thread>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <csignal>

snake::Snake* g_snake = nullptr;

void signal_handler(int signal) {
    if (signal == SIGINT && g_snake != nullptr) {
        std::cout << "\n游戏被中断。退出中...\n";
        g_snake->stop();
        exit(0);
    }
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

void keyboard_input(snake::Snake& snake) {
    while (true) {
        char c = getch();
        if (c == 'w' || c == 'a' || c == 's' || c == 'd') {
            snake.set_direct(c);
        } else if (c == 'q') {
            std::cout << "\n游戏退出...\n";
            snake.stop();
            exit(0); // 按 'q' 退出游戏
        }
    }
}

int main() {
  srand(time(NULL));

  snake::Snake snake;
  g_snake = &snake;
  signal(SIGINT, signal_handler);

  snake.init(5, 'd');
  
  std::cout << "贪吃蛇游戏\n";
  std::cout << "控制：\n";
  std::cout << "  w - 向上移动\n";
  std::cout << "  a - 向左移动\n";
  std::cout << "  s - 向下移动\n";
  std::cout << "  d - 向右移动\n";
  std::cout << "  q - 退出游戏\n";
  std::cout << "按任意控制键开始...\n";
  
  std::thread input_thread(keyboard_input, std::ref(snake));
  input_thread.detach(); 
  snake.run();
  
  std::cout << "游戏结束！\n";
  return 0;
}