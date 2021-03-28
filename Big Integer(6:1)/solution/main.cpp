#include <iostream>
#include <string>
#include "BigInteger.hpp"
#define _CRT_DISABLE_PERFCRIT_LOCKS

int main(int argc, char const *argv[]) {
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    std::string val;
    BigInteger a, b;
    char op;
    while (std::cin >> a >> b >> op) {
        try {
            if (op == '+')
                std::cout << (a += b) << '\n';
            else if (op == '-')
                std::cout << (a -= b) << '\n';
            else if (op == '*')
                std::cout << (a *= b) << '\n';
            else if (op == '/')
                std::cout << (a /= b) << '\n';
            else if (op == '^')
                std::cout << (a ^= b) << '\n';
            else if (op == '>')
                std::cout << (a > b ? "true" : "false") << '\n';
            else if (op == '<')
                std::cout << (a < b ? "true" : "false") << '\n';
            else if (op == '=')
                std::cout << (a == b ? "true" : "false") << '\n';
        } catch(char const* e) {
            std::cout << e << '\n';
        }
    }
}
