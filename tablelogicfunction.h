#ifndef TABLELOGICFUNCTION_H
#define TABLELOGICFUNCTION_H

#include "logicfunctionbase.h"

/**
 * @brief Represents logical functions implemented using a truth table.
 *
 * The TableLogicFunction class implements logical functions using a truth table.
 * Each row of the truth table represents a combination of inputs and the corresponding output.
 */
class TableLogicFunction : public LogicFunctionBase
{
public:
	/**
	 * @brief Constructs a TableLogicFunction object with the specified name, number of inputs, and truth table.
	 * @param table The truth table of the function, containing the inputs and the resulting output.
	 *        Inputs/output are characters: 't', 'f', or 'x'.
	 */
	TableLogicFunction(const std::string& name, int numinputs, const char **table);
	~TableLogicFunction() override = default;

	/**
	 * @brief Calculates the output based on the input values using the truth table.
	 *
	 * @param inputs One row of the truth table to calculate results.
	 * @return The output from the truth table if the matching input is found.
	 */
	char calculate(const std::vector<char>& inputs) const override;

private:
	const char **m_table;
};

#endif // TABLELOGICFUNCTION_H
