#include <iostream>
#include "while_count_utils.h"

namespace while_count_utils {

void runWhileCount() {
    int num;

    std::cout << "Enter a number to count to:\n";
    std::cin >> num;

    while (num > 10) {
        std::cout << "I'm programmed to only count up to 10!\n";
        std::cout << "Enter a number to count to:\n";
        std::cin >> num;
    }

    int i = 1;
    while (i <= num) {
        if (i == 5) {
            i++;
            continue;
        }

        std::cout << i << "\n";
        i++;
    }
}

}