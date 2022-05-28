#pragma once

class Calculator {
public:
	static int evaluate(char* exp);
private:
	static bool isOperand(char c);
	static int value(char c);
};