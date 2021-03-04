#include "lib.h"

Var0 add(Var0 lhs, Var0 rhs)
{
    return lhs + rhs;
}

Var0 get(Var0, std::size_t i, const std::vector<uint64_t> &values)
{
    return values[i];
}

Var1 add(Var1 lhs, Var1 rhs)
{
    return std::visit([](auto lhs, auto rhs) -> Var1 {
        return lhs + rhs;
    }, lhs, rhs);
}

Var1 get(Var1 , std::size_t i, const std::vector<uint64_t> &values)
{
    return values[i];
}

Var2 add(Var2 lhs, Var2 rhs)
{
    return std::visit([](auto lhs, auto rhs) -> Var2 {
        return lhs + rhs;
    }, lhs, rhs);
}

Var2 get(Var2, std::size_t i, const std::vector<uint64_t> &values)
{
    return values[i];
}
