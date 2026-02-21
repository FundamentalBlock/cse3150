#include <iostream>
#include "do_while_count_utils.h"

namespace do_while_count_utils {

void runDoWhileCount() {
    int num;

    do {
        std::cout << "Enter a number between 1 and 5:\n";
        std::cin >> num;
    } while (num < 1 || num > 5);

    int arr[5] = {1,2,3,4,5};

    for (int value : arr) {
        std::cout << "Value: " << value << "\n";
        if (value == num)
            break;
    }
}

}