#ifndef LOGICFUNCTIONBASE_H
#define LOGICFUNCTIONBASE_H

#include "logicfunctioninterface.h"

/**
 * @brief Base class for logic functions.
 *
 * It includes functionality to store the function name and the number of inputs expected.
 */
class LogicFunctionBase : public LogicFunctionInterface
{
public:
	/**
	 * @brief Constructs a LogicFunctionBase object with the specified name and number of inputs.
	 *
	 * @param name The name of the logic function (must be unique).
	 * @param numinputs The number of input characters expected in a single row of the truth table.
	 */
	LogicFunctionBase(const std::string& name, int numinputs);
	~LogicFunctionBase() override;

	int getNumInputs() const override;
	std::string getName() const override;

protected:
	std::string m_name;
	int m_numinputs;
};

#endif // LOGICFUNCTIONBASE_H
