#pragma once

#include "logicfunctionbase.h"

/**
 * @brief Implements logical functions as given by a truth table.
 */
class TableLogicFunction : public LogicFunctionBase
{
public:
	/**
	 *	@param[in] table		Truth table of given function containing numinputs inputs + resulting output.
								Inputs/output are char: 't','f','x'
	 */
	TableLogicFunction(const std::string& name, int numinputs, const char **table);
	~TableLogicFunction() override = default;

	/**
	 * @brief Returns output from m_table if given input is found in m_table
	 */
	char calculate(const std::vector<char> &inputs) const override;

private:
	const char **m_table;
};

