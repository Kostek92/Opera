#pragma once

#include <string>
#include <vector>

/**
 * @brief Interface class for logic functions that calculates logic output based on input
 */
class LogicFunctionInterface
{
public:
	virtual ~LogicFunctionInterface() {}
	virtual char calculate(const std::vector<char> &inputs) const = 0;
	virtual int getNumInputs() const = 0;
	virtual std::string getName() const = 0;
};
