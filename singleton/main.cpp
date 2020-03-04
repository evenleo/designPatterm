#include <iostream>
#include "singleton.h"

using namespace std;

int main() {
  singleton* p1 = singleton::Instance();
  p1 = singleton::Instance();

  system("pause");
  return 0;
}