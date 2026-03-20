#include <iostream>
#include "integer_utils.h"
#include "string_utils.h"
#include "grade_utils.h"
#include "while_count_utils.h"
#include "do_while_count_utils.h"

int main() {
    int choice;

    while (true) {
        std::cout << "1. Integer operations\n";
        std::cout << "2. Character arrays and C-style strings\n";
        std::cout << "3. Grade evaluation\n";
        std::cout << "4. While-loop counting\n";
        std::cout << "5. Do-while and range-based for counting\n";
        std::cout << "6. Quit\n";

        std::cin >> choice;

        switch (choice) {
            case 1:
                integer_utils::runIntegerOption();
                break;

            case 2:
                if (!string_utils::runStringOption())
                    return 1;
                break;

            case 3: {
                double grade;
                if (!grade_utils::calculateGrade(grade))
                    return 1;
                break;
            }

            case 4:
                while_count_utils::runWhileCount();
                break;

            case 5:
                do_while_count_utils::runDoWhileCount();
                break;

            case 6:
                std::cout << "Goodbye!\n";
                return 0;

            default:
                break;
        }
    }

    return 0;
}