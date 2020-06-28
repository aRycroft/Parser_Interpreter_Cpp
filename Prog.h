#pragma once
#include <iostream>
#include <functional>
#include <fstream>
#include <regex>
#include <unordered_map>
#include "Util.h"
#define ON_FAIL(STR) {fprintf(stderr, "%s, ERROR OCCURED in %s, on line %d\n", STR, __FILE__, __LINE__); exit(EXIT_FAILURE);}

class Program {
public:
	Program(std::string fileName);
	void skip(int n);
	std::string check(int n);
private:
	void tokenise(std::string fileName);
	void prog();
	void instr();
	void instruct();
	class CommandFactory
	{
	public:
		CommandFactory() {
			fillFunctionMap();
		}

		std::function<void(Program*)> getCommand(std::string token) {
			if (strVar(token) || numVar(token)) {
				return functionMap.at("SET");
			}
			else if (functionMap.count(token)) {
				return functionMap.at(token);
			}
			else {
				return nullptr;
			}
		};
	private:
		void fillFunctionMap() {
			functionMap.insert(std::make_pair("PRINT", std::function<void(Program*)>{printCommand()}));
			functionMap.insert(std::make_pair("PRINTN", std::function<void(Program*)>{printNCommand()}));
			functionMap.insert(std::make_pair("ABORT", std::function<void(Program*)>{abortCommand()}));
			functionMap.insert(std::make_pair("FILE", std::function<void(Program*)>{fileCommand()}));
			functionMap.insert(std::make_pair("SET", std::function<void(Program*)>{setCommand()}));
		}
		struct fileCommand {
			void operator()(Program* p) {
				std::unique_ptr<Program> newProgram(new Program(removeQuotes(p->check(1))));
			};
		};

		struct setCommand {
			void operator()(Program* p) {
				p->vars.insert(std::make_pair(p->check(0), p->check(2)));
			};
		};

		struct int2StrCommand {
			void operator()(Program* p) {

			};
		};

		struct abortCommand {
			void operator()(Program* p) {
				exit(EXIT_SUCCESS);
			};
		};

		struct printCommand {
			void operator()(Program* p) {
				std::cout << removeQuotes(p->check(1)) << '\n';
			};
		};

		struct printNCommand {
			void operator()(Program* p) {
				std::cout << removeQuotes(p->check(1));
			};
		};
		std::unordered_map<std::string, std::function<void(Program*)>> functionMap;
	};
	unsigned currentWord;
	std::vector<std::string> tokens;
	std::unordered_map<std::string, std::string> vars;
	CommandFactory factory;
};


