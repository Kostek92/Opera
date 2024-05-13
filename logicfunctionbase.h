#pragma once

#include "logicfunctioninterface.h"

class LogicFunctionBase : public LogicFunctionInterface
{
public:
	/**
	 *	@param[in] name			Function name. Must be unique
	 *	@param[in] numinputs	How many inputs chars are expected in single row of truth table
	 */
	LogicFunctionBase(const std::string& name, int numinputs);
	~LogicFunctionBase() override;

	int getNumInputs() const override;
	std::string getName() const override;

protected:
	std::string m_name;
	int m_numinputs;
};
