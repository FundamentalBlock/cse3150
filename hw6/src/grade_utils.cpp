#include <iostream>
#include "grade_utils.h"

namespace grade_utils {

bool calculateGrade(double &grade) {
    char type;

    std::cout << "Enter student type (U for undergrad, G for grad):\n";
    std::cin >> type;

    std::cout << "Enter numeric grade:\n";
    std::cin >> grade;

    if (grade < 0 || grade > 100) {
        std::cout << "Invalid grade\n";
        return false;
    }

    bool pass = false;

    if (type == 'U' || type == 'u') {
        pass = (grade >= 60);
    } else if (type == 'G' || type == 'g') {
        pass = (grade >= 70);
    }

    if (pass)
        std::cout << "Status: Pass\n";
    else
        std::cout << "Status: Fail\n";

    return true;
}

}