#include <stdint.h>

#include <algorithm>
#include <array>
#include <expected>
#include <iostream>
#include <optional>
#include <ranges>
#include <set>
#include <string_view>
#include <vector>

using namespace std;

int main() {
  constexpr char b[] = u8"µÜ\n";
  std::cout << b;
  for (const auto i : b) {
    std::cout << static_cast<unsigned>(i) << " ";
  }
  return 0;
}