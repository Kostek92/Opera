#ifndef LOGICFUNCTIONINTERFACE_H
#define LOGICFUNCTIONINTERFACE_H

#include <string>
#include <vector>

/**
 * @brief Interface class for logic functions.
 *
 * This class defines an interface for logic functions that calculate logic output based on input.
 * Implementations of this interface should provide the calculation logic via the calculate() method,
 * along with methods to retrieve the number of inputs and the name of the function.
 */
class LogicFunctionInterface
{
public:
	virtual ~LogicFunctionInterface() {}

	/**
	 * @brief Calculates the logic output based on the input values.
	 *
	 * @param inputs A vector of characters representing the input values.
	 * @return The calculated logic output.
	 */
	virtual char calculate(const std::vector<char> &inputs) const = 0;

	virtual int getNumInputs() const = 0;
	virtual std::string getName() const = 0;
};

#endif // LOGICFUNCTIONINTERFACE_H
