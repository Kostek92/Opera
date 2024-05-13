#include "logicprocessor.h"

LogicProcessor::LogicProcessor(LogicFunctionInterface* function)
	: m_logicfunction(function)
{
	m_inputsources.resize(m_logicfunction->getNumInputs(), 0);
	m_inputfunctions.resize(m_logicfunction->getNumInputs(), nullptr);
}

void LogicProcessor::setInput(int inputIndex, LogicProcessor* processor)
{
	if(inputIndex < 0 || inputIndex >= m_inputfunctions.size())
	{
		fprintf(stderr, "Warning: Invalid input index for processor \"%i\"\n", inputIndex);
		return;
	}
	m_inputfunctions[inputIndex] = processor;
}

void LogicProcessor::setInput(int inputIndex, const char* source)
{
	if(inputIndex < 0 || inputIndex >= m_inputsources.size())
	{
		fprintf(stderr, "Warning: Invalid input index for sources \"%i\"\n", inputIndex);
		return;
	}
	m_inputsources[inputIndex] = source;
}

char LogicProcessor::process() const
{
	std::vector<char> inputs(m_logicfunction->getNumInputs());

	for (size_t i = 0; i < m_logicfunction->getNumInputs(); ++i)
	{
		inputs[i] =  m_inputsources[i] ? *m_inputsources[i] :
						m_inputfunctions[i] ? m_inputfunctions[i]->process() : 0;
	}

	char output = m_logicfunction->calculate(inputs);
	return output;
}
