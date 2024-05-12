/* Logical function */

#include <stdio.h>
#include <string.h>

#include "logicfunction.h"

class LogicFunctionList {
private:

	struct LogicFunctionElm {
		LogicFunctionInterface *m_function;
		struct LogicFunctionElm *m_next;
	};

	static struct LogicFunctionElm *head;

public:
	static void insert(LogicFunctionInterface *function);
	static void remove(LogicFunctionInterface *function);
	static LogicFunctionInterface *find(const std::string& name);
};

LogicFunctionList::LogicFunctionElm *LogicFunctionList::head;

void LogicFunctionList::insert(LogicFunctionInterface *function)
{
	struct LogicFunctionElm *oldhead=head;
	head = new struct LogicFunctionElm;
	head->m_function = function;
	head->m_next = oldhead;
}

void LogicFunctionList::remove(LogicFunctionInterface *function)
{
	auto **elm=&head;
	while((*elm) != nullptr)
	{
		if ( (*elm)->m_function == function)
		{
			auto *next = (*elm)->m_next;
			delete (*elm);
			(*elm) = next;
		}
		else
		{
			(*elm) = (*elm)->m_next;
		}
	}
}

LogicFunctionInterface *LogicFunctionList::find(const std::string& name)
{
	for (const auto *elm=head; elm; elm=elm->m_next)
	{
		if (elm->m_function->getName() == name )
		{
			return elm->m_function;
		}
	}
	return nullptr;
}

TableLogicFunction::TableLogicFunction(const std::string& name, int numinputs, const char **table)
	: m_name(name),
	m_numinputs(numinputs),
	m_table(table)
{
	if (auto lf = LogicFunctionList::find(name))
	{
		fprintf(stderr, "Warning: Duplicate definition of LogicFunction \"%s\"\n", name.c_str());
		delete lf;
	}
	LogicFunctionList::insert(this);
}

TableLogicFunction::~TableLogicFunction()
{
	LogicFunctionList::remove(this);
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

int TableLogicFunction::getNumInputs() const
{
	return m_numinputs;
}

std::string TableLogicFunction::getName() const
{
	return m_name;
}

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

void LogicProcessor::setInput(int inputIndex, char* source)
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

CodeLogicFunction::CodeLogicFunction(const std::string &name, int numinputs, FunctionType customfunction)
	: m_name(name)
	, m_numinputs(numinputs)
	, m_function(customfunction)
{
	if (auto lf = LogicFunctionList::find(name))
	{
		fprintf(stderr, "Warning: Duplicate definition of LogicFunction \"%s\"\n", name.c_str());
		delete lf;
	}
	LogicFunctionList::insert(this);
}

CodeLogicFunction::~CodeLogicFunction()
{
	LogicFunctionList::remove(this);
}

char CodeLogicFunction::calculate(const std::vector<char> &inputs) const
{
	return m_function(inputs);
}

int CodeLogicFunction::getNumInputs() const
{
	return m_numinputs;
}

std::string CodeLogicFunction::getName() const
{
	return m_name;
}

