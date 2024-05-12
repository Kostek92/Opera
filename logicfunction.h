#ifndef LOGICFUNCTION_H
#define LOGICFUNCTION_H

#include <string>
#include <vector>
#include <functional>

/**
 * @brief Interface class for logic functions that calculates logic output based on input
 */
class LogicFunctionInterface
{
public:
	virtual ~LogicFunctionInterface() {}
	virtual char calculate(const std::vector<char> &inputs) const = 0;
	virtual int getNumInputs() const = 0;
	virtual std::string getName() const = 0;
};

/**
 * @brief Implements logical functions as given by a truth table.
 */
class TableLogicFunction : public LogicFunctionInterface
{
public:
	/**
	 *	@param[in] table		Truth table of given function containing numinputs inputs + resulting output.
								Inputs/output are char: 't','f','x'
		@param[in] numinputs	How many inputs chars are expected in single row of truth table
	 */
	TableLogicFunction(const std::string& name, int numinputs, const char **table);
	~TableLogicFunction() override;

	/**
	 * @brief Returns output from m_table if given input is found in m_table
	 */
	char calculate(const std::vector<char> &inputs) const override;
	int getNumInputs() const override;
	std::string getName() const override;

private:
	std::string m_name;
	int m_numinputs;
	const char **m_table;
};

/**
 * @brief Implements logical functions as given by a truth table.
 */
class CodeLogicFunction : public LogicFunctionInterface
{
public:
	using FunctionType =  std::function<char (const std::vector<char> &)>;
	CodeLogicFunction(const std::string& name, int numinputs, FunctionType customfunction);

	~CodeLogicFunction() override;

	/**
	 * @brief Calculates output bases on input and m_function
	 */
	char calculate(const std::vector<char> &inputs) const override;
	int getNumInputs() const override;
	std::string getName() const override;


private:
	std::string m_name;
	int m_numinputs;
	FunctionType m_function;
};

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
	void setInput(int inputIndex, char* source);
	/**
	* @brief Calculates logical output from currently set input function and processor
	*/
	char process() const;

private:
	std::vector<char*> m_inputsources;
	std::vector<LogicProcessor*> m_inputfunctions;
	LogicFunctionInterface* m_logicfunction;
};

#endif // LOGICFUNCTION_H
