#pragma once

#include "logicfunctioninterface.h"

#include <vector>

/**
 * @brief Calculate output from logical function. Can be combined with other LogicProcessors
 */
class LogicProcessor
{
public:
	explicit LogicProcessor(LogicFunctionInterface* function);

	/**
	* @brief Set additional processor for combinatorial cases
	*/
	void setInput(int inputIndex, LogicProcessor* processor);
	/**
	* @brief Set currently processed input
	*/
	void setInput(int inputIndex, const char *source);
	/**
	* @brief Calculates logical output from currently set input function and processor
	*/
	char process() const;

private:
	std::vector<const char*> m_inputsources;
	std::vector<LogicProcessor*> m_inputfunctions;
	LogicFunctionInterface* m_logicfunction;
};
