#include "../inc/utils.hpp"

// CPP spliter
std::vector<std::string> split(const std::string &str, char delim)
{
	std::size_t i = 0;
	std::vector<std::string> list;

	std::size_t pos = str.find(delim);

	while (pos != std::string::npos)
	{
		list.push_back(str.substr(i, pos - i));
		i = ++pos;
		pos = str.find(delim, pos);
	}

	list.push_back(str.substr(i, str.length()));

	return list;
}

std::vector<std::string> split(const std::string &str, const char *set_delim)
{
	std::size_t i = 0;
	std::vector<std::string> list;

	std::size_t pos = str.find_first_of(set_delim);

	while (pos != std::string::npos)
	{
		if (pos == i)
		{
			i = ++pos;
		}
		else
		{
			list.push_back(str.substr(i, pos - i));
			i = ++pos;
		}
		pos = str.find_first_of(set_delim, pos);
	}

	if (i != str.length())
		list.push_back(str.substr(i, str.length()));

	return list;
}

std::string removeTrailingZeros(std::string number)
{
	if (number.find('.') == std::string::npos)
	{
		return number;
	}

	auto ret = number;
	for (auto c = ret.rbegin(); c != ret.rend(); ++c)
	{
		if (*c == '0' && *(c + 1) == '.')
		{
			ret.pop_back();
			ret.pop_back();
		}
		else if (*c == '0')
		{
			ret.pop_back();
		}
		else
		{
			break;
		}
	}
	return ret;
}

// trim from start (in place)
inline void ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
									{ return !std::isspace(ch); }));
}

// trim from end (in place)
inline void rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
						 { return !std::isspace(ch); })
				.base(),
			s.end());
}

// trim from both ends (in place)
void trim(std::string &s)
{
	rtrim(s);
	ltrim(s);
}

// trim from start (copying)
inline std::string ltrim_copy(std::string s)
{
	ltrim(s);
	return s;
}


// trim from end (copying)
inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
std::string trim_copy(std::string s) {
    trim(s);
    return s;
}