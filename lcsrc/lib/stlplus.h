// for some stl in c++23
#pragma once

#include <iterator>
#include <ranges>
#include <xutility>

namespace leetcode::lib {

template <class Container, std::ranges::input_range Rng, class... Types>
  requires(!std::ranges::view<Container>)
[[nodiscard]] constexpr Container to(Rng&& Range, Types&&... Args) {
  Container res(std::forward<Types>(Args)...);
  std::ranges::copy(Range, std::back_inserter(res));
  return res;
}

template <class Container>
struct ToClassFn {
  template <std::ranges::input_range Rng, class... Types>
  [[nodiscard]] constexpr auto operator()(Rng&& Range, Types&&... Args) const
    requires requires { to<Container>(_STD forward<Rng>(Range), _STD forward<Types>(Args)...); }
  {
    return to<Container>(std::forward<Rng>(Range), std::forward<Types>(Args)...);
  }
};

template <class Container, class... Types>
  requires(!std::ranges::view<Container>)
[[nodiscard]] constexpr auto to(Types&&... Args) {
  return std::ranges::_Range_closure<ToClassFn<Container>, std::decay_t<Types>...>{
      std::forward<Types>(Args)...};
}

}  // namespace leetcode::lib