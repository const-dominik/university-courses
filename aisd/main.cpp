//Dominik Kiełbowicz
//329595
//PRZ

#include <iostream>

using namespace std;

int findFirst(int x) {
  int y =((int)x/2023 + 1)*2023;
  return y;
}

int main() {
  int a, b;
  cin >> a >> b;
  int first = a % 2023 ? findFirst(a) : a;
  for (int i = first; i <= b; i += 2023) {
    cout << i << " ";
  }
}