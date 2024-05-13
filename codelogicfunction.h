#ifndef CODELOGICFUNCTION_H
#define CODELOGICFUNCTION_H

#include "logicfunctionbase.h"
#include <functional>

/**
 * @brief Represents logical functions implemented as custom functions.
 *
 * This class implements logical functions using custom functions provided by the user.
 */
class CodeLogicFunction : public LogicFunctionBase
{
public:
	using FunctionType = std::function<char(const std::vector<char>&)>;

	/**
	 * @brief Constructs a CodeLogicFunction object with the specified name, number of inputs, and custom function.
	 *
	 * @param customfunction The custom function responsible for handling the logic.
	 *        The function should accept a vector of characters representing inputs and return a character
	 *        representing the output ('t', 'f', or 'x').
	 */
	CodeLogicFunction(const std::string& name, int numinputs, FunctionType customfunction);
	~CodeLogicFunction() override = default;

	/**
	 * @brief Calculates the output based on the input values using the custom function.
	 *
	 * @param inputs Input data for the function.
	 * @return The result of the function.
	 */
	char calculate(const std::vector<char>& inputs) const override;

private:
	FunctionType m_function;
};

#endif // CODELOGICFUNCTION_H
