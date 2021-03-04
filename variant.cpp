#include "lib.h"

#include <iostream>
#include <cstring>

template<typename VarT>
[[gnu::noinline]]
VarT run(const std::vector<uint64_t> &values)
{
    VarT s = 0u;

    for (std::size_t i = 0; i < 1000u; ++i) {
        const auto size = values.size();
        for (std::size_t i = 0; i < size; ++i) {
            s = add(s, get(s, i, values));
        }
    }
    return s;
}

void dump(Var0 v)
{
    std::cout << v << std::endl;
}

template<typename VarT>
void dump(VarT var)
{
    std::visit([](auto v) {
        std::cout << v << std::endl;
    }, var);
}

int main(int argc, char **argv)
{
    std::vector<uint64_t> values(131072, 0);

    if (argc < 2 || atoi(argv[1]) == 0) {
        dump(run<Var0>(values));
    } else if (atoi(argv[1]) == 1) {
        dump(run<Var1>(values));
    } else if (atoi(argv[1]) == 2) {
        dump(run<Var2>(values));
    }

    return 0;
}
