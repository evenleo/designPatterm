#include <iostream>
#include "singleton.h"

using namespace std;

int main() {
  Singleton* p1 = Singleton::Instance();
  p1 = Singleton::Instance();

  system("pause");
  return 0;
}