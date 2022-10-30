#include <iostream>
#include <vector>
#include "boxInfo.hpp"

int main()
{
  std::vector<double> x = {0.0855298042e+00,1.4513241053e+00,1.3237277269e+00,1.0128350258e+00,1.4122089148e+00,6.5826654434e-01,2.0795986652e+00,1.0230206251e+00,1.4231411219e+00,1.1091691256e+00,1.7714337111e+00,1.3986129761e+00,1.0640757084e+00,1.4216910601e+00,1.2402026653e+00};
  auto res = BoxInfo(x, 2);
  std::cout << std::get<0>(res) << ' ' << std::get<1>(res) << ' ' << std::get<2>(res) << std::endl;
}