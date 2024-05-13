#ifndef LOGICPROCESSOR_H
#define LOGICPROCESSOR_H

#include "logicfunctioninterface.h"


#include <vector>
/**
 * @brief Calculates output from a logical function and can be combined with other LogicProcessors.
 */
class LogicProcessor
{
public:
	/**
	 * @brief Constructs a LogicProcessor object with the specified logical function.
	 *
	 * @param function Pointer to the logical function interface.
	 */
	explicit LogicProcessor(LogicFunctionInterface* function);

	/**
	 * @brief Sets an additional processor for combinatorial cases.
	 *
	 * @param inputIndex The index of the input for which the processor is being set.
	 * @param processor Pointer to the LogicProcessor object to be set as an input processor.
	 */
	void setInputProcessor(int inputIndex, LogicProcessor* processor);

	/**
	 * @brief Sets the currently processed input from a source.
	 *
	 * @param inputIndex The index of the input being set.
	 * @param source Pointer to the source data for the input.
	 */
	void setInputData(int inputIndex, const char *source);

	/**
	 * @brief Calculates the logical output from the currently set inputs and processor.
	 *
	 * @return The calculated logical output.
	 */
	char process() const;

private:
	std::vector<const char*> m_inputsources;
	std::vector<LogicProcessor*> m_inputfunctions;
	LogicFunctionInterface* m_logicfunction;
};
#endif // LOGICPROCESSOR_H
