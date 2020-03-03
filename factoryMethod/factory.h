#include "product.h"

class Factory {
public:
  virtual ~Factory() = 0;
  virtual Product* CreateProduct() = 0;
protected:
  Factory() {}
};

Factory::~Factory() {}

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