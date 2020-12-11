//
// Created by henry.wu on 10/1/20.
//

#ifndef PNSEI_META1_H
#define PNSEI_META1_H

namespace meta{
template <typename... Types>
struct PPack {};

struct A {static constexpr char name[] = "A";};
struct B {static constexpr char name[] = "B";};
struct C {static constexpr char name[] = "C";};

using All = PPack<A, B, C>;

template <typename Type, typename... Types>
void print_types_recur() {
  std::cout << Type::name << std::endl;
  if constexpr (sizeof...(Types) > 0) {
    (print_types_recur<Types>(), ...);
  }
}

template <typename... Types>
struct print_types;

template <typename... Types>
struct print_types<PPack<Types...>>
{
  void operator()() {
    (print_types_recur<Types>(), ...);
  }
};


}

#endif // PNSEI_META1_H
