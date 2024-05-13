Opera Programming Test

For this test you are given responsibility of a couple of classes that
implement logical functions as given by a truth table.
The interface and implementation of these classes are found in files
logicalfunction.h and logicalfunction.cpp respectively.
In addition, there is a small program that tests the basic usage of the
classes, and a file testcases.h intended for use in the last task.

However, as of now these classes have a number of shortcomings, and it is your
task to correct these. First, take a look through the code and make a
quick estimate of how much time you think you will spend on each of the tasks
given below. Then, as you do the programming, record how much time
you actually spend.

TASKS:

1) The class interfaces do not follow good object-oriented design principles,
   which make them bug-prone and hard to extend/subclass properly.

   Improve the object-oriented design of the classes.

2) The class interfaces are almost completely undocumented.

   Include proper interface documentation in the .h-file.

3) There seems to be a bug somewhere, as the test program seems to end with a
   SEGV.

   Find the bug, explain what is wrong, and make a working fix.

4) The class LogicalFunction only supports functions defined by a table.
   For some logical functions, especially with many inputs, the truth tables may
   be inconveniently large. As an example, a 10-input XOR would need 1024 rows,
   whereas you could implement it by a couple of lines of C++ code.

   Make modifications that makes it possible for the calling program to define
   the behaviour of a LogicalFunction by providing C++ code.

5) Using your modified classes, define LogicalProcessors that are able to
   inspect an 8x8 monochrome pixel grid, represented by 64 inputs, and report
   whether this grid has horizontal, vertical or rotational symmetry.

   Verify your LogicalProcessors by using the grids given in testcases.h as
   input


We hope that you have fun!

------------------------------------------------------

Quick estimate vs real time spend
1) 1h		  3h
2) 0.5h           1h
3) 1h		  45min
4) 1.5h		  0.5h
5) 1.5h		  2h

I decided to start with point 3. Passing tests are really helpfull base for any refactors
3) In method void LogicFunctionList::remove(LogicFunction *f) we were skipping 2 nodes of list if elm to delete was found instead of one:
elm=&((*elm)->m_next
(*elm) = next. 
In for loop we first check if *elm is nullptr, then we update elm with (*elm) = next; in for loop body and then we try to update elm=&((*elm)->m_next) again.
During second update of elm, we use (*elm)->m_next, but *elm can be already nullptr which is Undefined Behaviour.
Fix was to use while loop instead which updates *elm only once. 

1) Improvements done
Use interface for logic function
Extract classess to separate files
Use vector for easier memory managment
Make class members private
Mark methods as const when possible
Use std::string instead of const char* for name
Remove unused method findFunction
return nullptr instead of 0
Use full name in arguments intead of one letters shortcuts
Rename setInput into setInputProcessor and setInputData

Improvements not done:
I kept arguments name in all lower case since it is consistent in whole project
I didn't use smart pointers in interfaces of classes because all data that comes into classes are local variables in tests
Some valid unit test framework should be used in tests, but it is beyond the scope of task

2) Doxygen style documentation added. Obvious methods or parameters where not documented

4) Coded xor example added in testlogicfunction.cpp

5) Horizontal, vertical or rotational symmetry logic processors are validated again testcases.h
