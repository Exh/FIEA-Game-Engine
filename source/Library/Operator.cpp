#include "pch.h"
#include "Operator.h"

namespace Library
{
	bool Operator::IsOperator(const std::string& oper)
	{
		return (oper == "+" || oper == "-" || oper == "*" || oper == "/" || oper == "%" || oper == "=");
	}

	bool Operator::IsNumber(const std::string& value)
	{
		try
		{
			if (IsFloat(value))
			{
				ToFloat(value);
			}
			else
			{
				ToInt(value);
			}

			return true;
		}
		catch (std::exception)
		{
			return false;
		}
	}

	bool Operator::IsFloat(const std::string& value)
	{
		if (value[value.length() - 1] == 'f')
		{
			return true;
		}

		return false;
	}

	bool Operator::IsFunction(const std::string& name)
	{
		return true;
	}

	Datum Operator::Evaluate(const std::string& postfixString, Datum::DatumType type)
	{
		std::stringstream sstream(postfixString);
		std::string extract;
		Stack<float> valuesStack;

		while (std::getline(sstream, extract, ' '))
		{
			//if it is a number push it on to stack
			if (IsNumber(extract))
			{
				valuesStack.Push(ToFloat(extract));
			}
			//if it is an operator, evaluate and push it back to stack
			else if (IsOperator(extract) || IsFunction(extract))
			{
				std::uint32_t argsCount = OperandsCountMap[extract];

				if (valuesStack.Size() < argsCount)
				{
					throw std::exception("Incorrect postfix expression");
				}
				else
				{
					float* values = new float[2]();

					for (int i = argsCount - 1; i >= 0; i--)
					{
						values[i] = valuesStack.Pop();
					}

					float result = Operation(extract, values[0], values[1]);

					valuesStack.Push(result);

					delete values;
				}
			}
		}

		if (valuesStack.Size() == 1)
		{
			return Datum(); //TODO make a new datum with the result
		}
		else
		{
			throw std::exception("Incorrect postfix expression");
		}
	}

	float Operator::Operation(const std::string& oper, float operand1, float operand2)
	{
		return 0.0f; //TODO evaluate the expression as operand1 operator operand2 or function(operand1, operand2)
	}

	float Operator::ToFloat(const std::string& value)
	{
		if (IsFloat(value))
		{
			return std::stof(value.substr(0, value.length() - 1));
		}
		
		return std::stof(value);
	}

	int Operator::ToInt(const std::string& value)
	{
		return std::stoi(value);
	}

	//using map for initialisation line
	std::map<std::string, int> Operator::PrecedenceMap = {
			{ "(", 2 },
			{ ")", 2 },
			{ ".", 2 },
			{ "*", 5 },
			{ "/", 5 },
			{ "%", 5 },
			{ "+", 6 },
			{ "-", 6 },
			{ "=", 16 } };

	std::map<std::string, int> Operator::OperandsCountMap = {
			{ "*", 2 },
			{ "/", 2 },
			{ "%", 2 },
			{ "+", 2 },
			{ "-", 2 },
			{ "=", 2 } };

	//shunting yard algorithm - comments from wiki
	std::string Operator::ToPostfix(const std::string& infixString)
	{
		Vector<std::string> outputQueue;
		Stack<std::string> operatorStack;

		std::stringstream sstream(infixString);
		std::string extract;

		//Read a token.
		while (std::getline(sstream, extract, ' '))
		{
			if (Operator::IsNumber(extract))
			{
				//If the token is a number, then add it to the output queue.
				outputQueue.PushBack(extract);
			}
			else if (Operator::IsFunction(extract))
			{
				//If the token is a function token, then push it onto the stack.
				operatorStack.Push(extract);
			}
			else if (extract == ",")
			{
				//If the token is a function argument separator(e.g., a comma) :
				//Until the token at the top of the stack is a left parenthesis, pop operators off the stack onto the output queue. 
				//If no left parentheses are encountered, either the separator was misplaced or parentheses were mismatched.
				while (operatorStack.Top() == "(")
				{
					if (operatorStack.IsEmpty())
					{
						throw std::exception("Parenthesis mismatch in expression");
					}

					outputQueue.PushBack(operatorStack.Pop());
				}
			}
			else if (Operator::IsOperator(extract))
			{
				//If the token is an operator, o1, then:
				if (!operatorStack.IsEmpty())
				{
					/*while there is an operator token, o2, at the top of the operator stack, and either

					o1 is left-associative and its precedence is less than or equal to that of o2, or
					o1 is right associative, and has precedence less than that of o2,

					then pop o2 off the operator stack, onto the output queue;

					push o1 onto the operator stack.*/

					int stackTopPrecedence = PrecedenceMap[operatorStack.Top()];
					int currentOperatorPrecedence = PrecedenceMap[extract];

					while (currentOperatorPrecedence >= stackTopPrecedence)
					{
						if (operatorStack.IsEmpty())
						{
							break;
						}

						outputQueue.PushBack(operatorStack.Pop());
						stackTopPrecedence = PrecedenceMap[operatorStack.Top()];
					}
				}
				operatorStack.Push(extract);
			}
			else if (extract == "(")
			{
				//If the token is a left parenthesis, then push it onto the stack.
				operatorStack.Push(extract);
			}
			else if (extract == ")")
			{
				/*If the token is a right parenthesis :

				Until the token at the top of the stack is a left parenthesis, pop operators off the stack onto the output queue.
				Pop the left parenthesis from the stack, but not onto the output queue.
				If the token at the top of the stack is a function token, pop it onto the output queue.
				If the stack runs out without finding a left parenthesis, then there are mismatched parentheses.*/

				while (operatorStack.Top() != "(")
				{
					if (operatorStack.IsEmpty())
					{
						throw std::exception("Parenthesis mismatch");
					}

					outputQueue.PushBack(operatorStack.Pop());
				}

				operatorStack.Pop(); //pop (
			}
		}

		while (!operatorStack.IsEmpty())
		{
			/*If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses.
			Pop the operator onto the output queue.*/

			if (operatorStack.Top() == "(" || operatorStack.Top() == ")")
			{
				throw std::exception("Parenthesis mismatch in expression");
			}

			outputQueue.PushBack(operatorStack.Pop());
		}

		std::string output = "";

		//convert vector to string
		for (std::uint32_t i = 0; i < outputQueue.Size(); i++)
		{
			output.append(outputQueue[i]);

			if (i != outputQueue.Size() - 1)
			{
				output.append(" ");
			}
		}

		return output;
	}
}