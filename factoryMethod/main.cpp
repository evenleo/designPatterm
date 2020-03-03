#include <iostream>
#include "factory.h"

int main() {
    Factory* factory = new ConcreteFactory();
    Product* p = factory->CreateProduct();
    system("pause");
    return 0;
}