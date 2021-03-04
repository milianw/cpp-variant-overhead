#pragma once

#include <vector>
#include <cstdint>
#include <variant>

using Var0 = uint64_t;
using Var1 = std::variant<uint64_t>;
using Var2 = std::variant<uint64_t, uint32_t>;

Var0 add(Var0 lhs, Var0 rhs);
Var0 get(Var0 v, std::size_t i, const std::vector<uint64_t> &values);

Var1 add(Var1 lhs, Var1 rhs);
Var1 get(Var1 v, std::size_t i, const std::vector<uint64_t> &values);

Var2 add(Var2 lhs, Var2 rhs);
Var2 get(Var2 v, std::size_t i, const std::vector<uint64_t> &values);
