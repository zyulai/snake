#include <atomic>

#include "map.hpp"

namespace snake {
class Snake {
 private:
  static Visual map;
  static std::atomic<char> direct;
  static std::atomic<bool> running;

 public:
  Snake() = default;
  ~Snake() = default;
  void init(int length, char direct);
  void update();
  void visual();
  void run();
  void set_direct(char direct);
  void stop();
};
}  // namespace snake
