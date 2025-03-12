# 终端版C++贪吃蛇实现解析

## 项目概述
这是一个用C++11实现的命令行贪吃蛇游戏，具有以下核心特性：

- **多线程输入处理**：独立线程实时响应键盘操作
- **跨平台支持**：兼容Linux/macOS终端环境
- **安全退出机制**：支持Ctrl+C安全中断游戏
- **自适应终端**：实时刷新的游戏界面

## 游戏控制
```bash
  w - 向上移动
  a - 向左移动  
  s - 向下移动
  d - 向右移动
  q - 退出游戏
```

## 关键技术实现

### 1. 异步输入处理
```cpp
// 独立输入线程实现
std::thread input_thread(keyboard_input, std::ref(snake));
input_thread.detach();

// 非阻塞式字符读取
char getch() {
  struct termios old = {0};
  tcgetattr(0, &old);
  old.c_lflag &= ~(ICANON|ECHO);
  tcsetattr(0, TCSANOW, &old);
  // ...
}
```

### 2. 信号中断处理
```cpp
void signal_handler(int signal) {
  if (signal == SIGINT && g_snake != nullptr) {
    std::cout << "\n安全退出中...\n";
    g_snake->stop(); // 优雅终止游戏循环
    exit(0);
  }
}
```

### 3. 游戏主循环
```cpp
void Snake::run() {
  while (running_) {
    update();    // 游戏状态更新
    render();    // 界面渲染
    usleep(100000); // 控制游戏速度
  }
}
```

## 编译运行
```bash
# 编译项目
make

# 启动游戏
./snake_game
```

## 项目结构
```
├── main.cpp        # 程序入口/控制逻辑
├── snake.hpp       # 蛇类声明
├── snake.cpp       # 移动/碰撞检测实现  
├── map.hpp         # 游戏地图接口
├── map.cpp         # 终端渲染实现
└── Makefile        # 构建配置
```

## 扩展方向
1. map设计成独立的前端接口，支持五子棋/井字棋等游戏实现
2. 实现难度等级
3. 支持网络对战
4. src/include分离，接口和实现分离

> 项目源码已托管在[GitHub](https://github.com/zyulai/snake)，欢迎贡献代码！
