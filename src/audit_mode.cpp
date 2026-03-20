#include "audit_mode.h"
#include "validation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

char get_delimiter(const std::string& filename) {
    if (filename.size() >= 4 &&
        filename.substr(filename.size() - 4) == ".csv") {
        return ',';
    }
    return '\t';
}

void process_file(std::string input, std::string output) {
    std::ifstream infile(input);
    if (!infile.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    std::ofstream outfile(output, std::ios::app);
    if (!outfile.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    char in_delim = get_delimiter(input);
    char out_delim = get_delimiter(output);

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);
        std::string username, email, password;

        std::getline(ss, username, in_delim);
        std::getline(ss, email, in_delim);
        std::getline(ss, password);

        if (!is_valid_password(password)) {
            outfile << username << out_delim << email << out_delim << password << "\n";
        }
    }
}

void run_menu() {
    int choice;
    while (true) {
        std::cout << "1. Check a single password" << std::endl;
        std::cout << "2. Process a TSV/CSV file" << std::endl;
        std::cout << "3. Quit" << std::endl;

        std::cin >> choice;

        if (choice == 1) {
            std::string password;
            std::cin.ignore();
            std::getline(std::cin, password);
            if (is_valid_password(password)) {
                std::cout << "Valid" << std::endl;
            } else {
                std::cout << "Invalid" << std::endl;
            }
        } else if (choice == 2) {
            std::string inpath, outpath;
            std::cin >> inpath >> outpath;
            process_file(inpath, outpath);
        } else if (choice == 3) {
            break;
        }
    }
}
