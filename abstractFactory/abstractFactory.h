#include "product.h"

class AbstractFactory {
public:
  virtual ~AbstractFactory() {}
  virtual AbstractProductA* CreateProductA() = 0;
  virtual AbstractProductB* CreateProductB() = 0;

protected:
  AbstractFactory() {}
};

class ConcreteFactory1 : public AbstractFactory {
public:
  ~ConcreteFactory1() {}
  ConcreteFactory1() {
    std::cout << "ConcreteFactory1" << std::endl;
  }
  AbstractProductA* CreateProductA() {
    return new ProductA1();
  }
  AbstractProductB* CreateProductB() {
    return new ProductB1();
  }
};

class ConcreteFactory2 : public AbstractFactory {
public:
  ~ConcreteFactory2() {}
  ConcreteFactory2() {
    std::cout << "ConcreteFactory2" << std::endl;
  }
  AbstractProductA* CreateProductA() {
    return new ProductA2();
  }
  AbstractProductB* CreateProductB() {
    return new ProductB2();
  }
};