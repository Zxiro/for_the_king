#ifndef STRING_UTIL_H
#define STRING_UTIL_H
#include <sstream>
#include <iomanip>
#include <string>


class StringUtil
{
public:
	static std::string toStringFixed(double value, int precision)
	{
		std::ostringstream out;
		out << std::fixed << std::setprecision(precision) << value;
		return out.str();
	}
};

#endif