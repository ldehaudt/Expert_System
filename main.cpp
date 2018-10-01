#include "expert.hpp"

std::vector<rule> rules;
std::map<char, Leaf*> leaves;
std::string assersions;
std::string queries;
std::map<char, std::string> symbols =
{
	{'+', "∧"},
	{'|', "∨"},
	{'^', "⊕"},
	{'!', "¬"}
};

char solve(char c, std::string found)
{
	if (leaves[c]->ran){
		return (leaves[c]->t);
	}
	if (found.find(c) != std::string::npos){
		return leaves[c]->t;
	}
	found = found + c;
	if (leaves[c]->o.size() == 0)
	{
		if (abs(leaves[c]->t) == 0)
			leaves[c]->t = -1;
		leaves[c]->ran = true;
		return leaves[c]->t;
	}
	char b = 0;
	for (unsigned int i = 0; i < leaves[c]->o.size(); i++)
	{
		b = DFSLeaves(leaves[c]->o[i], found);
		if (abs(leaves[c]->t) < abs(b)){
			leaves[c]->t = b;
			leaves[c]->branch = i;
		}
		if (abs(leaves[c]->t) == 2 && leaves[c]->t == -b)
			throw "There is a Contradiction in the rules, go fix it fast!\n";
	}
	leaves[c]->ran = true;
	return leaves[c]->t;
}

int print_usage()
{
	std::cout << ORANGE
	<< "Usage: Please feed the expert with a file formatted as below:\n\n"
	<<"[INSERT RULES HERE], e.g.\n" << YELLO
	<< "A => B\n(!(C | !A) ^ D) + !B => !(E | F)\n"
	<< ORANGE << "=[INSERT FACTS HERE], e.g.\n" << YELLO
	<< "t=ACDB\n"
	<< ORANGE << "=[INSERT QUERIES HERE], e.g.\n" << YELLO
	<< "?EF\n";
	return 0;
}

void print_prompt()
{
	std::cout << WHITE << "To change assersions or queries, "
	<< "type '=' or '?' followed by your new entries. q to exit\n";
}

int	main(int ac, char **av)
{
	std::string line;
	if (ac != 2)
		return (print_usage());
	std::ifstream file;
	file.open(av[1]);
	if (file.fail())
	{
		std::cout << RED << "Input file does not exist\n";
		return 0;
	}
	try {
		while (std::getline(file, line) && line[0] && line[0] != '=')
		{
			std::cout << WHITE << "Input: " << line << std::endl;
			line = cleanup(line);
			std::cout << WHITE << "Formatted: \n";
			parse(line);
		}
		while (!line[0] && std::getline(file, line))
			;
		line = deleteSpaces(line);
		if (line[0] != '=')
			throw (std::exception());
		assersions = line.substr(1);
		while (std::getline(file, line) && !line[0])
			;
		line = deleteSpaces(line);
		if (line[0] != '?')
			throw (std::exception());
		queries = line.substr(1);
		makeLeafs();
		for (unsigned int i = 0; i < rules.size(); i++)
			makeGraph(rules[i]);
	}
	catch (std::exception&)
	{
		std::cout << RED << "Input format error\n";
		file.close();
		exit(1);
	}
	file.close();
	compute();
	print_prompt();
	while (std::getline(std::cin, line))
	{
		restart(line);
		print_prompt();
	}
	return 0;
}
