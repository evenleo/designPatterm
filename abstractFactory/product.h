#include <iostream>

class AbstractProductA {
public:
  virtual ~AbstractProductA() {}
protected:
  AbstractProductA() {}  // 屏蔽构造函数
};

class AbstractProductB {
public:
  virtual ~AbstractProductB() {}
protected:
  AbstractProductB() {}  // 屏蔽构造函数
};

class ProductA1 : public AbstractProductA {
public:
  virtual ~ProductA1() {}
  ProductA1() {
    std::cout << "ProductA1" << std::endl;
  }  
};

class ProductA2 : public AbstractProductA {
public:
  virtual ~ProductA2() {}
  ProductA2() {
    std::cout << "ProductA2" << std::endl;
  }  
};

class ProductB1 : public AbstractProductB {
public:
  virtual ~ProductB1() {}
  ProductB1() {
    std::cout << "ProductB1" << std::endl;
  }  
};

class ProductB2 : public AbstractProductB {
public:
  virtual ~ProductB2() {}
  ProductB2() {
    std::cout << "ProductB2" << std::endl;
  }  
};