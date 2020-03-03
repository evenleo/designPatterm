#include "product.h"

class Factory {
public:
  virtual ~Factory() {}
  virtual Product* CreateProduct() = 0;
protected:
  Factory() {}
};

class ConcreteFactory : public Factory {
public:
  ~ConcreteFactory() {}
  ConcreteFactory() {
    std::cout << "ConcreteFactory" << std::endl;
  }
  Product* CreateProduct() {
    return new ConcreteProduct();
  }
};