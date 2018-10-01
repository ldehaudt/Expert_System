#include "expert.hpp"

int match(std::string str, int pos)
{
	int d = 1;
	int i = pos + 1;

	while (d && str[i])
	{
		if (str[i] == '(')
			d++;
		if (str[i] == ')')
		{
			d--;
			if (d == 0)
				return i;
		}
		i++;
	}
	throw (std::exception());
	return -1;
}

int revMatch(std::string str, int pos)
{
	int d = 1;
	int i = pos - 1;

	while (d && i >= 0)
	{
		if (str[i] == ')')
			d++;
		if (str[i] == '(')
		{
			d--;
			if (d == 0)
				return i;
		}
		i--;
	}
	throw (std::exception());
	return -1;
}

bool isAlpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

std::string deleteSpaces(std::string str)
{
	std::string ret;

	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			ret += str[i];
		i++;
	}
	return ret;
}

std::string	resolveNegative(std::string r)
{
	r = r.substr(1, r.size() - 1);
	int c = 1;
	int total = match(r, 0);
	while(c < total){
		if (r[c] == '|')
			r[c] = '+';
		else if (r[c] == '+')
			r[c] = '|';
		else if (isAlpha(r[c]))
		{
			r = r.substr(0, c) + '!' + r.substr(c, r.size() - c);
			c++;
			total++;
		}
		else if (r[c] == '(')
		{
			r = r.substr(0, c) + '!' + r.substr(c, r.size() - c);
			int t = match(r,c) - c;
			c += t;
			total += 1;
		}
		c++;
	}
	for (unsigned int i = 0; i < r.size() - 1; i++)
		if (r[i] == '!' && r[i + 1] == '!')
			r = r.substr(0, i) + r.substr(i + 2, r.size() - i - 2);
	return r;
}
