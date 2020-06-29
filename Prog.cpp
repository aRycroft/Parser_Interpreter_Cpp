#pragma once
#include "Prog.h"

Program::Program(std::string fileName) {
	currentWord = 0;
	tokenise(fileName);
	prog();
}

void Program::skip(int n) {
	currentWord += n;
}

std::string Program::check(int n) {
	return tokens[currentWord + n];
}

void Program::newProgram(std::string fileName)
{
	std::unique_ptr<Program> newProgram(new Program(fileName));
}

void Program::setVar(std::string name, std::string value)
{
	vars.insert(std::make_pair(name, value));
}

void Program::tokenise(std::string fileName) {
	std::string line;
	std::fstream file(fileName);
	if (file.is_open()) {
		while (getline(file, line)) {
			const std::regex anyToken("\".*\"|\\S+");
			std::smatch sm;
			while (std::regex_search(line, sm, anyToken)) {
				tokens.push_back(sm[0]);
				line = sm.suffix();
			}
		}
		file.close();
	}
	else {
		ON_FAIL("File does not exist");
	}
}

void Program::prog() {
	if ("{" != check(0)) {
		ON_FAIL("EXPECTED {");
	}
	skip(1);
	instr();
}

void Program::instr() {
	if ("}" == check(0)) {
		return;
	}
	instruct();
	skip(1);
	instr();
}

void Program::instruct() {
	std::function<void(Program*)> function;
	function = factory.getCommand(check(0));
	if (function != nullptr) {
		function(this);
	}
}



