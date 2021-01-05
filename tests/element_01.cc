#include <iomanip>
#include <iostream>

#include <tpcc/element.h>

// Reference output
const unsigned int direction_index21[] = { 0, 0 };
const unsigned int direction_index22[] = { 0, 0 , 1, 1 };
const unsigned int* direction_index2[] = { 0, direction_index21, direction_index22 };
const unsigned int position21[] = { 1, 2, 1, 3 };
const unsigned int position22[] = { 2, 3, 3, 3, 2, 3, 2, 4 };
const unsigned int* position2[] = { 0, position21, position22 };
const unsigned int direction_index31[] = { 0, 0 };
const unsigned int direction_index32[] = { 0, 0, 2, 2 };
const unsigned int direction_index33[] = { 0, 0, 1, 1, 2, 2 };
const unsigned int* direction_index3[] = { 0, direction_index31, direction_index32, direction_index33 };
const unsigned int position31[] = { 1, 2, 3, 1, 3, 3 };
const unsigned int position32[] = { 2, 3, 5, 3, 3, 5, 2, 3, 5, 2, 3, 6 };
const unsigned int position33[] = { 3, 5, 8, 4, 5, 8, 3, 5, 8, 3, 6, 8, 3, 5, 8, 3, 5, 9 };
const unsigned int* position3[] = { 0, position31, position32, position33 };
const unsigned int direction_index52[] = { 0, 0, 3, 3 };
const unsigned int position52[] = { 2, 3, 5, 8, 13, 2, 4, 5, 8, 13, 2, 3, 5, 8, 13, 2, 3, 5, 8, 14 };
const unsigned int* direction_index5[] = { 0, 0, direction_index52 };
const unsigned int* position5[] = { 0, 0, position52 };
const unsigned int** direction_index[] = { 0, 0, direction_index2, direction_index3, 0, direction_index5 };
const unsigned int** position[] = { 0, 0, position2, position3, 0, position5 };

template <int n, int k, typename T1, typename T2>
void test(const TPCC::Element<n, k, T1, T2>& e)
{
    e.print_debug(std::cout);

    for (unsigned int i = 0; i < 2 * k; ++i)
    {
        std::cout << "\n   " << i << ": ";
        auto b = e.facet(i);
        b.print_debug(std::cout);

        if (b.direction_index() != direction_index[n][k][i])
            throw std::logic_error("Direction index differ!");
        for (unsigned int j = 0; j < n; ++j)
        {
            if (b[j] != position[n][k][i * n + j])
                throw std::logic_error("Position differ!");
        }
    }
    std::cout << std::endl;
}

constexpr unsigned int fibonacci(unsigned int i)
{
    if (i == 0 || i == 1)
        return i;

    unsigned int i0 = 1;
    unsigned int i1 = 1;
    for (unsigned int j = 1; j < i; ++j)
    {
        unsigned int in = i0 + i1;
        i0 = i1;
        i1 = in;
    }
    return i1;
}

template <int n, int k>
void test()
{
    TPCC::Combinations<n, k> combinations;
    std::array<unsigned int, n> positions{};
    for (unsigned int i = 0; i < n; ++i)
        positions[i] = fibonacci(k + i);

    TPCC::Element<n, k, unsigned int, unsigned short> e{ combinations[combinations.size() / 3],
                                                         positions };
    test(e);
}

int main()
{
//    test_2<0>(); // Invalid.
    test<2, 1>();
    test<2, 2>();

    test<3, 1>();
    test<3, 2>();
    test<3, 3>();

    test<5, 2>();

    return 0;
}
