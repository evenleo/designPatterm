#include <iostream>
#include "abstractFactory.h"

int main() {
    AbstractFactory* af1 = new ConcreteFactory1();
    af1->CreateProductA();
    af1->CreateProductB();

    AbstractFactory* af2 = new ConcreteFactory2();
    af2->CreateProductA();
    af2->CreateProductB();

    system("pause");
    return 0;
}