#include <mutex>
#include <atomic>

using namespace std;

class Singleton {
public:
  static Singleton *Instance() {
    if (inst_ptr_ == nullptr) {
      lock_guard<mutex> lock(mutex_);
      if (inst_ptr_ == nullptr) {
        inst_ptr_ = new Singleton();
      }
    }
    return inst_ptr_;
  }

private:
  Singleton() {}
  static Singleton *inst_ptr_;
  static mutex mutex_;
};

Singleton *Singleton::inst_ptr_ = nullptr;
mutex Singleton::mutex_;

/*
* 这个代码的目的是消除大部分执行路径上的加锁开销。原本的意图是：如果 inst_ptr_ 没有被初始化，
* 执行才会进入加锁的路径，防止单件被构造多次；如果 inst_ptr_ 已经被初始化，那它就会被直接返回，
* 不会产生额外的开销。虽然看上去很美，但它一样有着上面提到的问题。Scott Meyers 和 Andrei 
* Alexandrecu 详尽地分析了这个用法 [4]，然后得出结论：即使花上再大的力气，这个用法仍然有着非常
* 多的难以填补的漏洞。本质上还是上面说的，优化编译器会努力击败你试图想防止优化的努力，而多处理器
* 会以令人意外的方式让代码走到错误的执行路径上去。他们分析得非常详细，建议你可以花时间学习一下。
*/

/*
* 为了从根本上消除这些漏洞，C++11 里引入了适合多线程的内存模型。我们可以在参考资料 [5] 里了解更多
* 的细节。跟我们开发密切相关的是：现在我们有了原子对象（atomic）和使用原子对象的获得（acquire）、
* 释放（release）语义，可以真正精确地控制内存访问的顺序性，保证我们需要的内存序。
*/

class singleton {
public:
  static singleton *Instance() {
    singleton* ptr = inst_ptr_.load(memory_order_acquire);
    if (ptr == nullptr) {
      lock_guard<mutex> lock(mutex_);
      ptr = inst_ptr_.load(memory_order_relaxed);
      if (ptr == nullptr) {
        ptr = new singleton();
        inst_ptr_.store(ptr, memory_order_release);
      }
    }
    return ptr;
  }

private:
  singleton() {}
  static atomic<singleton*> inst_ptr_;
  static mutex mutex_;
};

atomic<singleton*> singleton::inst_ptr_;
mutex singleton::mutex_;

/*
* <atomic> 头文件中还定义了内存序，分别是：
* memory_order_relaxed：松散内存序，只用来保证对原子对象的操作是原子的
* memory_order_consume：目前不鼓励使用，我就不说明了
* memory_order_acquire：获得操作，在读取某原子对象时，当前线程的任何后面的读写操作都不允许重排到这个操作的前面去，
*   并且其他线程在对同一个原子对象释放之前的所有内存写入都在当前线程可见
* memory_order_release：释放操作，在写入某原子对象时，当前线程的任何前面的读写操作都不允许重排到这个操作的后面去，
*   并且当前线程的所有内存写入都在对同一个原子对象进行获取的其他线程可见
* memory_order_acq_rel：获得释放操作，一个读‐修改‐写操作同时具有获得语义和释放语义，即它前后的任何读写操作都不允许
*   重排，并且其他线程在对同一个原子对象释放之前的所有内存写入都在当前线程可见，当前线程的所有内存写入都在对同一个原
*   子对象进行获取的其他线程可见
* memory_order_seq_cst：顺序一致性语义，对于读操作相当于获取，对于写操作相当于释放，对于读‐修改‐写操作相当于获得释
*   放，是所有原子操作的默认内存序
*/