#include "vector.hpp"

#include <iostream>

#include <vector>

int main() {
  sjtu::vector<long long> v;
  for (long long i = 0; i < 1LL << 20; ++i) {
    v.push_back(i);
  }
  std::cout << v.back() << " " << v.front() << std::endl;
  for (long long i = 0; i < 1LL << 11; ++i) {
    v.insert(v.begin(), i);
    // std::cout << v.front() << std::endl;
  }
  std::cout << v.size();
  for (long long i = 0; i < 1LL << 11; ++i) {
    // std::cout << v[i] << "*" << std::endl;
  }
  for (size_t i = 0; i < 1LL << 10; ++i) {
    std::cout << v.front() << std::endl;
    v.erase(v.begin());
  }
  return 0;
}