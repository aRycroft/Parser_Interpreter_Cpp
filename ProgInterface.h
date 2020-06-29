#pragma once
class ProgInterface {
public:
	virtual void skip(int n) = 0;
	virtual std::string check(int n) = 0;
	virtual void newProgram(std::string fileName) = 0;
	virtual void setVar(std::string name, std::string value) = 0;
};