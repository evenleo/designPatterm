#include <mutex>
#include <atomic>

class Singleton {
public:
  static Singleton *Instance() {
    if (instance_ == nullptr) {
      std::lock_guard<std::mutex> lock(mutex_);
      if (instance_ == nullptr) {
        instance_ = new Singleton();
      }
    }
    return instance_;
  }

private:
  Singleton() {}
  static Singleton *instance_;
  static std::mutex mutex_;
};

Singleton *Singleton::instance_ = nullptr;
std::mutex Singleton::mutex_;
