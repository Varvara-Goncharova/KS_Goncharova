#include"data_base.h"
#include"parser.h"
#include"solver.h"

#include<string>
#include<iostream>

int main() {
    std::string input_address;
    std::string output_address;
    std::cout << "Insert input file: ";
    std::cin >> input_address;
    std::cout << "Insert output file: ";
    std::cin >> output_address;
    DataBase db;
    if(!db.parse(input_address)) {
        std::cout << "Incorrect input file!";
        return 1;
    }
    Answer answer = GenerationsAlgorithm(db);
    Parser parser;
    if(!parser.Print(output_address, answer)) {
        std::cout << "Incorrect output file!";
        return 1;
    }
}