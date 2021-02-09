//
//  main.cpp
//  test
//
//  Created by Ivan Welsh on 9/02/21.
//

#include <iostream>

#include <stdx/string.hpp>

int main(int argc, const char * argv[]) {
  stdx::string test("hello test");
  stdx::string test_sub = test.substr(0, 5);
  std::cout << test << " " << test_sub << '\n';
  
  test = test_sub;
  
  std::cout << test << '\n';
  test = "   Temp try at reassign\n   ";
  std::cout << test << stdx::string::alphanumeric() << '\n';
  test_sub = test.strip();
  std::cout << test_sub << stdx::string::alphanumeric() << '\n';
  
  stdx::string test2 = "   123456   ";
  std::cout << test2 << '1' << '\n';
  std::cout << test2.strip() << '1' << '\n';
  test2.strip_inplace();
  std::cout << test2 << "1\n";
  return 0;
}
