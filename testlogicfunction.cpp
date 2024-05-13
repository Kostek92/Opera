/*
 * Test software
 */

#include <cassert>
#include <stdio.h>
#include <algorithm>

#include "logicprocessor.h"
#include "tablelogicfunction.h"
#include "codelogicfunction.h"
#include "testcases.h"

const char *or2_table [] =
{
"txt",
"xtt",
"fff",
0
};

const char *or3_table [] =
{
"txxt",
"xtxt",
"xxtt",
"ffff",
0
};

const char *and2_table [] =
{
"ttt",
"fxf",
"xff",
0
};

const char *and3_table [] =
{
"tttt",
"fxxf",
"xfxf",
"xxff",
0
};

const char *xor2_table  [] =
{
"tft",
"ftt",
"fff",
"ttf",
0
};

const char *xor3_table  [] =
{
"fftt",
"ftft",
"tfft",
"tttt",
"ffff",
"fttf",
"ttff",
"tftf",
0
};

const char *impl_table [] =
{
"xtt",
"fxt",
"tff",
0
};

const char *not_table [] =
{
"tf",
"ft",
0
};

const char *incl_table [] =
{
"txxt",
0
};

bool isSymmetrical(const std::vector<char> &input)
{
	for (int i = 0; i < input.size() / 2; ++i)
	{
		if (input[i] != input[input.size() - i - 1])
		{
			return false;
		}
	}
	return true;
}

auto gridHorizontalSymmetryFunction = [](const std::vector<char> &inputs)
{
	assert(gridSize == inputs.size());
	for (int i = 0; i < inputs.size(); i+=gridLength )
	{
		auto horizontalLine = std::vector<char>(inputs.begin() + i, inputs.begin() + i + gridLength);
		if(!isSymmetrical(horizontalLine))
		{
			return false;
		}
	}
	return true;
};

auto gridVerticalSymmetryFunction = [](const std::vector<char> &inputs)
{
	assert(gridSize == inputs.size());
	for (int column = 0; column < gridLength; ++column )
	{
		std::vector<char> verticalLine(gridLength);
		for (int row = 0; row < gridLength; ++row)
		{
			verticalLine[row] = inputs[row * gridLength + column];
		}
		if(!isSymmetrical(verticalLine))
		{
			return false;
		}
	}
	return true;
};

auto gridRotationalSymmetryFunction = [](const std::vector<char> &inputs)
{
	return gridHorizontalSymmetryFunction(inputs) && gridVerticalSymmetryFunction(inputs);
};

void processor_test(LogicProcessor *proc, int n, char *inp)
{
	int i;
	for (i=0;i<n;i++)
	{
		inp[i] = 'f';
	}

	bool done=false;
	do {
		for (i=0 ; i<n; i++)
			printf("%c ", inp[i]);
		printf(" -> %c\n", proc->process());

		for (i=0 ; i<n; i++)
		{
			if (inp[i] == 'f')
			{
				inp[i] = 't';
				break;
			}
			else
			{
				inp[i] = 'f';
			}
		}
		done = i==n;
	} while (!done);

}

void function_test(LogicFunctionInterface *func)
{
	char *inp;
	char n=func->getNumInputs();
	LogicProcessor proc(func);

	printf("Testing function: %s\n", func->getName().c_str());
	inp = new char [n];
	for (int i=0; i<n; i++)
	{
		proc.setInputData(i, inp+i);
	}

	processor_test(&proc, n, inp);

	delete [] inp;
}

void grid_symmetry_test(LogicProcessor *proc, int numinputs, const std::vector<bool>& expectedSymmetry)
{
	const bool debugOnlyFail = false;
	assert(expectedSymmetry.size() == testCasesCount);
	for(int testCaseIndex = 0; testCaseIndex < testCasesCount; ++testCaseIndex)
	{
		for (int i=0; i<numinputs; i++)
		{
			proc->setInputData(i, testcases[testCaseIndex]+i);
		}
		const bool isSymmetrical= proc->process();
		const bool testCasePassed = isSymmetrical == expectedSymmetry.at(testCaseIndex);
		if(!debugOnlyFail || !testCasePassed)
		{
			printf("Test case %d %s\n", testCaseIndex+1, testCasePassed ? "PASS" : "FAIL");
		}
	}
}

void horizontal_symmetry_test()
{
	CodeLogicFunction f_horizontalSymmetry("horizontal_symmetry", gridSize, gridHorizontalSymmetryFunction);
	LogicProcessor proc (&f_horizontalSymmetry);

	std::vector<bool> expectedSymmetry(testCasesCount, false);
	std::fill(expectedSymmetry.begin(), expectedSymmetry.begin() + 16, true);

	printf("Testing function: %s\n", f_horizontalSymmetry.getName().c_str());

	grid_symmetry_test(&proc, f_horizontalSymmetry.getNumInputs(), expectedSymmetry);
}

void vertical_symmetry_test()
{
	CodeLogicFunction f_verticalSymmetry("vertical_symmetry", gridSize, gridVerticalSymmetryFunction);
	LogicProcessor proc (&f_verticalSymmetry);

	std::vector<bool> expectedSymmetry(testCasesCount, false);
	std::fill(expectedSymmetry.begin(), expectedSymmetry.begin() + 8, true);
	std::fill(expectedSymmetry.begin() + 16, expectedSymmetry.begin() + 24, true);

	printf("Testing function: %s\n", f_verticalSymmetry.getName().c_str());

	grid_symmetry_test(&proc, f_verticalSymmetry.getNumInputs(), expectedSymmetry);
}

void rotational_symmetry_test()
{
	CodeLogicFunction f_rotationalSymmetry("rotational_symmetry", gridSize, gridRotationalSymmetryFunction);
	LogicProcessor proc (&f_rotationalSymmetry);

	std::vector<bool> expectedSymmetry(testCasesCount, false);
	std::fill(expectedSymmetry.begin(), expectedSymmetry.begin() + 8, true);

	printf("Testing function: %s\n", f_rotationalSymmetry.getName().c_str());

	grid_symmetry_test(&proc, f_rotationalSymmetry.getNumInputs(), expectedSymmetry);
}

int main()
{
	TableLogicFunction
		f_not("not",1,not_table),
		f_and2("and2",2,and2_table),
		f_and3("and3",3,and3_table),
		f_or2("or2",2,or2_table),
		f_or3("or3",3,or3_table),
		f_xor2("xor2",2,xor2_table),
		f_xor3("xor3",3,xor3_table),
		f_implies("implies", 2, impl_table);

	TableLogicFunction
		f_incomplete("incomplete",3, incl_table);

// Basic table tests
	function_test(&f_not);
	function_test(&f_and2);
	function_test(&f_and3);
	function_test(&f_or2);
	function_test(&f_or3);
	function_test(&f_xor2);
	function_test(&f_xor3);
	function_test(&f_implies);

	function_test(&f_incomplete);

// Combinatorial tests

	{
		printf("Testing combinatorial not (P and Q)\n");
		char inputs[2];
		LogicProcessor p_not(&f_not),  p_and(&f_and2);
		p_and.setInputData(0,inputs);
		p_and.setInputData(1,inputs + 1);
		p_not.setInputProcessor(0,&p_and);

		processor_test(&p_not, 2, inputs);
	}

	{
		printf("Testing combinatorial P and not (Q or not R)\n");
		//  A && !(B || !C)
		char inputs[3];
		LogicProcessor p_not0(&f_not), p_not1(&f_not), p_or(&f_or2), p_and(&f_and2);
		p_not0.setInputData(0,inputs+2);
		p_or.setInputData(0,inputs+1);
		p_or.setInputProcessor(1,&p_not0);
		p_not1.setInputProcessor(0,&p_or);
		p_and.setInputData(0,inputs);
		p_and.setInputProcessor(1, &p_not1);

		processor_test(&p_and, 3, inputs);
	}

//Code table test
	{
		auto xorFunction = [](const std::vector<char> &inputs)
		{
			const auto trueCount = std::count_if(inputs.begin(), inputs.end(), [](auto element) { return element == 't'; });
			return trueCount % 2 == 1 ? 't' : 'f';
		};
		CodeLogicFunction f_codeXor3("xor3_code", 3, xorFunction);
		function_test(&f_codeXor3);
	}

//Grid tests
	{
		horizontal_symmetry_test();
		vertical_symmetry_test();
		rotational_symmetry_test();
	}
	return 0;
}
