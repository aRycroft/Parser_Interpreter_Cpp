#pragma once
#include <iostream>
#include <functional>
#include <fstream>
#include <regex>
#include <unordered_map>
#include "ProgInterface.h"
#include "CommandFactory.h"
#include "Util.h"
#define ON_FAIL(STR) {fprintf(stderr, "%s, ERROR OCCURED in %s, on line %d\n", STR, __FILE__, __LINE__); exit(EXIT_FAILURE);}

class Program : public ProgInterface {
public:
Program(std::string fileName);
void skip(int n);
std::string check(int n);
void newProgram(std::string fileName);
void setVar(std::string name, std::string value);
private:
void tokenise(std::string fileName);
void prog();
void instr();
void instruct();
private:
unsigned currentWord;
std::vector<std::string> tokens;
std::unordered_map<std::string, std::string> vars;
CommandFactory factory;
};


