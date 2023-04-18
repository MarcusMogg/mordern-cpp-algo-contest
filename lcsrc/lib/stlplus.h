// for some stl in c++23
#pragma once

#include <algorithm>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <ranges>
#include <set>
#include <string>
#include <vector>

#include "leetcode_struct.h"
#include "segtree.h"

namespace leetcode::lib {

// https://en.cppreference.com/w/cpp/ranges/to

template <class Container, class Rng, class... Types>
concept ConvertsCommonConstructible = requires {
  requires std::ranges::common_range<Rng>;
  requires std::derived_from<
      typename std::iterator_traits<std::ranges::iterator_t<Rng>>::iterator_category,
      std::input_iterator_tag>;
  requires std::constructible_from<
      Container,
      std::ranges::iterator_t<Rng>,
      std::ranges::sentinel_t<Rng>,
      Types...>;
};

template <class Container, class Reference>
concept CanPushBack = requires(Container& Cont) { Cont.push_back(std::declval<Reference>()); };

template <class Reference, class Container>
constexpr auto ContainerInserter(Container& Con) {
  if constexpr (CanPushBack<Container, Reference>) {
    return std::back_insert_iterator{Con};
  } else {
    return std::insert_iterator{Con, Con.end()};
  }
}

template <class Container, std::ranges::input_range Rng, class... Types>
  requires(!std::ranges::view<Container>)
[[nodiscard]] constexpr Container to(Rng&& Range, Types&&... Args) {
  if constexpr (ConvertsCommonConstructible<Container, Rng, Types...>) {
    return Container(
        std::ranges::begin(Range), std::ranges::end(Range), std::forward<Types>(Args)...);
  }
  Container res(std::forward<Types>(Args)...);
  std::ranges::copy(Range, ContainerInserter<std::ranges::range_reference_t<Rng>>(res));
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