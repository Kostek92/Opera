#include "codelogicfunction.h"

CodeLogicFunction::CodeLogicFunction(const std::string &name, int numinputs, FunctionType customfunction)
	: LogicFunctionBase(name, numinputs)
	, m_function(customfunction)
{

}

char CodeLogicFunction::calculate(const std::vector<char> &inputs) const
{
	return m_function(inputs);
}

