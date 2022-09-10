#include <iostream>
#include "utils.hpp"

int main(){
  using std::cout;
  using std::endl;
  using std::cin;

  cout << "Hello world!" << endl;

  int x, y;
  cout << "x = ? ";
  cin >> x;
  cout << "y = ? ";
  cin >> y;
  cout << x << " + " << y << " = " << x + y << endl;
  cout << x << " - " << y << " = " << x - y << endl;
  cout << x << " * " << y << " = " << x * y << endl;
  cout << x << " / " << y << " = " << x / y << endl;
  cout << x << " % " << y << " = " << x % y << endl;
  cout << x << " | " << y << " = " << (x | y) << endl;
  cout << x << " & " << y << " = " << (x & y) << endl;
  cout << x << " ^ " << y << " = " << (x ^ y) << endl;
  cout << x << " << " << y << " = " << (x << y) << endl;
  cout << x << " >> " << y << " = " << (x >> y) << endl;
  cout << "Plus(" << x << ", " << y << ") = " << Plus(x,y) << endl;

  return 0;

}