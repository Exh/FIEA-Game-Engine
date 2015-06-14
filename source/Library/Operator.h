#pragma once
#include <string>
#include <map>

namespace Library
{
	class Operator final
	{
	public:
		static bool IsOperator(const std::string& oper);
		static bool IsNumber(const std::string& value);
		static bool IsFunction(const std::string& name);
		static bool IsFloat(const std::string& value);

		static Datum Evaluate(const std::string& postfixString, Datum::DatumType type=Datum::DatumType::Float);

		static std::string ToPostfix(const std::string& infixString);
		static float ToFloat(const std::string& value);
		static int ToInt(const std::string& value);

		static std::map<std::string, int> PrecedenceMap;
		static std::map<std::string, int> OperandsCountMap;
	private:
		static float Operation(const std::string& oper, float operand1, float operand2 = 0.0f);
	};
}