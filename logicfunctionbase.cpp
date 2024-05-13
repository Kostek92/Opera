#include "logicfunctionbase.h"

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
			elm = &((*elm)->m_next);
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

LogicFunctionBase::LogicFunctionBase(const std::string &name, int numinputs)
	: m_name(name)
	, m_numinputs(numinputs)
{
	if (auto lf = LogicFunctionList::find(name))
	{
		fprintf(stderr, "Warning: Duplicate definition of LogicFunction \"%s\"\n", name.c_str());
		delete lf;
	}
	LogicFunctionList::insert(this);
}

LogicFunctionBase::~LogicFunctionBase()
{
	LogicFunctionList::remove(this);
}

int LogicFunctionBase::getNumInputs() const
{
	return m_numinputs;
}

std::string LogicFunctionBase::getName() const
{
	return m_name;
}
