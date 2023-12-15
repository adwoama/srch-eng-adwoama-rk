/*
 * Rebecca Kuhlman
 * 4/6/2021
 * CS 2341
 * main to the Search Engine program that receives command prompts and calls methods as needed
 */
//#define CATCH_CONFIG_RUNNER
//#include "catchTDD.hpp"
#include <iostream>
#include "UserInterface.h"

using namespace std;

void runCatchTests();

int main(int argc, char** argv) {
    if(argc == 1) {
        runCatchTests();
        return 0;
    }
    else if(argc != 2){
        throw std::out_of_range("Enter 0 or 1 arguments");
    }
    string path = argv[1];
    UserInterface program(path);
    program.receiveQueries();
    return 0;
}

void runCatchTests(){
   // Catch::Session().run();
}
