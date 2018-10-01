#include "expert.hpp"

std::string precedence(std::string line)
{
	char arr[3] = {'+','|','^'};
	
	for (int c = 0; c < 3; c++)
		for (unsigned int i = 1; i < line.size(); i++)
			if (line[i] == arr[c])
			{
				int p1 = i - 1;
				int p2 = i + 1;
				if (p2 != static_cast<int>(line.size() - 1) && line[p2] == '!')
					p2++;
				if (line[p1] == ')')
					p1 = revMatch(line, p1);
				if (line[p2] == '(')
					p2 = match(line, p2);
				if (p1 != 0 && line[p1 - 1] == '!')
					p1--;
				if ((p1 == 0 && p2 == static_cast<int>(line.size() - 1)) ||
					(line[p1 - 1] == '(' && match(line, p1 - 1) == p2 + 1))
					continue ;
				line = line.substr(0, p1) + '(' +
				line.substr(p1, p2 + 1 - p1) + ')' + line.substr(p2 + 1);
				i++;
			}
	return line;
}

bool	recurse(std::string l, std::string r)
{
	if ((isAlpha(r[0]) && r.size() == 1) ||
		(r[0] == '!' && isAlpha(r[1]) && r[2] == '\0'))
		return true;
	std::string rhs1;
	std::string rhs2;
	int opPos = 0;
	char op;
	if (r[0] == '!' && r[1] == '(')
		r = resolveNegative(r);
	if (r[0] == '(')
	{
		opPos = match(r, 0);
		if (r[opPos + 1] == '\0')
		{
			parse(l + "=>" + r.substr(1, opPos - 1));
			return false;
		}
		opPos++;
	}
	else
	{
		if (r[0] == '!')
			opPos++;
		if (isAlpha(r[opPos]))
			opPos++;
		else
			throw (std::exception());
	}
	rhs1 = r.substr(0, opPos);
	rhs2 = r.substr(opPos + 1, r.size() - opPos - 1);
	op = r[opPos];
	if (op == '|')
	{
		parse("(" + l + ")+!" + rhs1 + "=>" + rhs2);
		parse("(" + l + ")+!" + rhs2 + "=>" + rhs1);
	}
	else if (op == '+')
	{
		parse(l + "=>" + rhs2);
		parse(l + "=>" + rhs1);
	}
	else if (op == '^')
	{
		parse("(" + l + ")+" + rhs1 + "=>!" + rhs2);
		parse("(" + l + ")+" + rhs2 + "=>!" + rhs1);
		parse("(" + l + ")+!" + rhs1 + "=>" + rhs2);
		parse("(" + l + ")+!" + rhs2 + "=>" + rhs1);
	}
	return false;
}

void	parse(std::string line)
{
	rule r;
	int i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (!line[i + 1] || line[i + 1] != '>')
		throw (std::exception());
	if (i >= 1 && line[i - 1] == '<')
	{
		std::string rev;
		rev = line.substr(i + 2, line.size() - i - 1);
		rev += "=>";
		rev += line.substr(0, i - 1);
		parse(rev);
		r.lhs = line.substr(0, i - 1);
	}
	else 
		r.lhs = line.substr(0, i);
	line = line.substr(i + 2, line.size() - i - 2);
	if (recurse(r.lhs, line))
	{
		int pos;
		while((pos = r.lhs.find("!!")) != static_cast<int>(std::string::npos))
			r.lhs = r.lhs.substr(0, pos) + r.lhs.substr(pos + 2);
		r.lhs = precedence(r.lhs);
		r.neg = 0;
		if (line[0] == '!')
		{
			r.neg = 1;
			r.rhs = line[1];
		}
		else
			r.rhs = line[0];
		rules.push_back(r);
		std::string left;
		for (unsigned int i = 0; i < r.lhs.size(); i++)
			if (symbols[r.lhs[i]].size() != 0)
				left += symbols[r.lhs[i]];
			else
				left += r.lhs[i];
		std::cout << YELLO << left << "=>" << (r.neg ? "¬" : "") << r.rhs << std::endl;
	}
}

void    checkValid(std::string str)
{
    for(unsigned int i = 0; i < str.size(); i++)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
        	|| str[i] == '|' || str[i] == '+' || str[i] == '=' || str[i] == '>' || str[i] == '<'
        	|| str[i] == '(' || str[i] == ')' || str[i] == '^' || str[i] == '!'))
            throw std::exception();
    }
}

std::string	cleanup(std::string str)
{
	int m;
	str = deleteSpaces(str);
	checkValid(str);
	for (int i = 0; i < (int)str.size() - 2; i++)
	{
		if (str[i] == '(' && str[i + 2] == ')')
		{
			str = str.substr(0, i) + str[i + 1] + str.substr(i + 3);
			i -= 2;
		}
		else if (str[i] == '(' && str[i+1] == '!' && str[i + 3] == ')')
		{
			str = str.substr(0, i) + "!" + str[i + 2] + str.substr(i + 4);
			i -= 2;
		}
		if (i < -1)
			i = -1;
	}
	for (unsigned int i = 0; i < str.size() - 2; i++){
		if (str[i] == '(')
		{
			m = match(str, i);
			if (str[i + 1] == '(' && m - 1 == match(str, i + 1))
				str = str.substr(0, i) + str.substr(i + 1, m) + str.substr(m +1);
			else if (str[i + 1] == '!' && str[i + 2] == '(' && m - 1 == match(str, i + 2))
				str = str.substr(0, i) + str.substr(i + 1, m - i - 1) + str.substr(m +1);
		}
	}
	unsigned int pos;
	while (str.find("!!") != std::string::npos)
	{
		pos = str.find("!!");
		str = str.substr(0, pos) + str.substr(pos + 2);
	}
	return str;
}

void	makeLeafs()
{
	char c;

	for (unsigned int i = 0; i < rules.size(); i++)
	{	
		for (unsigned int j = 0; j < rules[i].lhs.size(); j++)
		{
			if (isAlpha(rules[i].lhs[j]))
			{
				c = rules[i].lhs[j];
				if (leaves.find(c) == leaves.end())
				{
					Leaf *tmp = new Leaf;
					tmp->t = 0;
					tmp->c = c;
					leaves.emplace(c, tmp);
				}
			}
		}
		if (leaves.find(c = rules[i].rhs) == leaves.end())
		{
			Leaf *tmp = new Leaf;
			tmp->t = 0;
			tmp->c = c;
			leaves.emplace(c, tmp);
		}
	}
	for (unsigned int i = 0; i < assersions.size(); i++)
	{
		if (leaves.find(assersions[i]) == leaves.end())
		{
			Leaf *tmp = new Leaf;
			tmp->c = assersions[i];
			leaves.emplace(assersions[i], tmp);
		}
		leaves[assersions[i]]->t = 2;
	}
	for (unsigned int i = 0; i < queries.size(); i++)
	{
		if (leaves.find(queries[i]) == leaves.end())
		{
			Leaf *tmp = new Leaf;
			tmp->c = queries[i];
			leaves.emplace(queries[i], tmp);
			leaves[queries[i]]->t = 0;
		}
	}
}

