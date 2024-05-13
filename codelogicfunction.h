#pragma once

#include "logicfunctionbase.h"
#include <functional>

/**
 * @brief Implements logical functions as given by a truth table.
 */

class CodeLogicFunction : public LogicFunctionBase
{
public:
	using FunctionType =  std::function<char (const std::vector<char> &)>;
	/**
	 *	@param[in] customfunction	Function handling truth table logic
									Inputs/output are char: 't','f','x'
	 */
	CodeLogicFunction(const std::string& name, int numinputs, FunctionType customfunction);
	~CodeLogicFunction() override = default;

	/**
	 * @brief Calculates output based on inputs and m_function
	 */
	char calculate(const std::vector<char> &inputs) const override;

private:
	FunctionType m_function;
};


