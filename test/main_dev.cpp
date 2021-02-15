//
//  main.cpp
//  test
//
//  Created by Ivan Welsh on 9/02/21.
//

#include <iostream>

#include <stdx/fixed_vector.hpp>
#include <vector>
#include <iterator>
#include <numeric>

int main(int argc, const char * argv[]) {
  stdx::fixed_vector<int64_t> test(-5,5);
  std::iota(test.begin(), test.end(), -5);
  std::cout << test[0] << " " << test.at(3) << '\n';
  test.resize(-3, 17);
  std::iota(test.begin(), test.end(), -3);
  std::cout << test[0] << " " << test.at(3) << " " << test[-2] << '\n';
  return 0;
}
