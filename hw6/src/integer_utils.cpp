#include <iostream>
#include "integer_utils.h"

namespace integer_utils {

void runIntegerOption() {
    int a, b;

    std::cout << "Enter first integer:\n";
    std::cin >> a;

    std::cout << "Enter second integer:\n";
    std::cin >> b;

    if (b == 0) {
        std::cout << "Error: division by zero\n";
        return;
    }

    int result = a / b;
    std::cout << "Result: " << result << "\n";

    // increment operations
    std::cout << "After post-increment: " << a++ << "\n";
    std::cout << "After pre-increment: " << ++a << "\n";
}

}