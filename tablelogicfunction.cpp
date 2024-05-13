#include "tablelogicfunction.h"

TableLogicFunction::TableLogicFunction(const std::string& name, int numinputs, const char **table)
	: LogicFunctionBase(name, numinputs)
	, m_table(table)
{

}

char TableLogicFunction::calculate(const std::vector<char>& inputs) const
{
	for (const char **t=m_table; *t ; t++)
	{
		int i;
		for (i=0; (*t)[i] == 'x' || inputs[i] == (*t)[i] ; )
		{
			if (++i == m_numinputs )
				return (*t)[i];
		}
	}
	return 'x';
}
