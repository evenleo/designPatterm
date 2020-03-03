#include <iostream>

class Product {
public:
  virtual ~Product() = 0;
protected:
  Product() {}  // 屏蔽构造函数
};

Product::~Product() {}

class ConcreteProduct: public Product {
public:
  ~ConcreteProduct() {}
  ConcreteProduct() {
    std::cout << "ConcreteProduct" << std::endl;
  }

};

