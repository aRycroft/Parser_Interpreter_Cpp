#pragma once
#include "ProgInterface.h"
#include "Util.h"
class CommandFactory {
public:
	CommandFactory() {
		fillFunctionMap();
	}
	std::function<void(ProgInterface*)> getCommand(std::string token) {
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
		functionMap.insert(std::make_pair("PRINT", std::function<void(ProgInterface*)>{printCommand()}));
		functionMap.insert(std::make_pair("PRINTN", std::function<void(ProgInterface*)>{printNCommand()}));
		functionMap.insert(std::make_pair("ABORT", std::function<void(ProgInterface*)>{abortCommand()}));
		functionMap.insert(std::make_pair("FILE", std::function<void(ProgInterface*)>{fileCommand()}));
		functionMap.insert(std::make_pair("SET", std::function<void(ProgInterface*)>{setCommand()}));
	}

	struct fileCommand {
		void operator()(ProgInterface* p) {
			p->newProgram(removeQuotes(p->check(1)));
		};
	};

	struct setCommand {
		void operator()(ProgInterface* p) {
			p->setVar(p->check(0), p->check(2));
		};
	};

	struct int2StrCommand {
		void operator()(ProgInterface* p) {

		};
	};

	struct abortCommand {
		void operator()(ProgInterface* p) {
			exit(EXIT_SUCCESS);
		};
	};

	struct printCommand {
		void operator()(ProgInterface* p) {
			std::cout << removeQuotes(p->check(1)) << '\n';
		};
	};

	struct printNCommand {
		void operator()(ProgInterface* p) {
			std::cout << removeQuotes(p->check(1));
		};
	};
	std::unordered_map<std::string, std::function<void(ProgInterface*)>> functionMap;
};