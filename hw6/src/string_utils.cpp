#include <iostream>
#include <string>
#include "string_utils.h"

namespace string_utils {

/*
This function reads a desired string length,
copies characters manually into a C-style
character array, and prints the result.
*/

bool runStringOption() {
    int length;

    std::cout << "Enter string length:\n";
    std::cin >> length;

    if (length >= 20) {
        std::cout << "Error: length must be less than 20\n";
        return false;
    }

    std::cin.ignore();

    std::cout << "Enter string:\n";

    std::string input;
    std::getline(std::cin, input);

    char arr[20];

    for (int i = 0; i < length; ++i) {
        arr[i] = input[i];
    }

    arr[length] = '\0';

    std::cout << "C-style string: " << arr << "\n";

    return true;
}

}