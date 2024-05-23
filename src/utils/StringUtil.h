#ifndef STRING_UTIL_H
#define STRING_UTIL_H
#include <sstream>
#include <iomanip>
#include <string>
#include <typeindex>


class StringUtil
{
public:
	static std::string toStringFixed(double value, int precision)
	{
		std::ostringstream out;
		out << std::fixed << std::setprecision(precision) << value;
		return out.str();
	}

	static std::string getName(std::type_index type)
	{
		std::string name = type.name();
		size_t pos = name.find("class ");

		if (pos != std::string::npos) {
			name = name.substr(pos + 6);
		}


		return name;
	}
};

#endif