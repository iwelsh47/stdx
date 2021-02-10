//
//  main.cpp
//  test
//
//  Created by Ivan Welsh on 9/02/21.
//

#include <iostream>

#include <stdx/string.hpp>
#include <vector>
#include <iterator>

int main(int argc, const char * argv[]) {
  stdx::string test("hello test a b c d e f    g  ");
  std::vector<stdx::string> substrs;
  
  test.split(std::back_inserter(substrs), ' ', false);
  
  for (stdx::string& s : substrs) {
    std::cout << s << "|\n";
  }
  
  return 0;
}
