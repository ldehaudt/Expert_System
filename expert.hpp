#ifndef EXPERT_HPP
# define EXPERT_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <string>
# include <map>
# include "INode.hpp"

# define RED "\e[1;38;2;225;20;20m"
# define WHITE "\e[1;38;2;255;251;214m"
# define YELLO "\e[1;38;2;255;200;0m"
# define ORANGE "\e[1;38;2;255;120;10m"
# define GREEN "\e[1;38;2;0;175;117m"

typedef struct s_rule {
	std::string lhs;
	bool neg;
	char rhs;
}				rule;

typedef struct s_op op;

typedef struct s_node {
	op *o;
	bool neg;
	char c;
	char t;
}				node;

typedef struct s_op {
	node *lNode;
	op *lOp;
	node *rNode;
	op *rOp;
	char o;
}				op;

extern std::vector<rule> rules;
extern std::map<char, Leaf*> leaves;
extern std::string assersions;
extern std::string queries;
extern std::map<char, std::string> symbols;

std::string	cleanup(std::string str);
std::string	precedence(std::string line);
std::string deleteSpaces(std::string str);
std::string	resolveNegative(std::string r);
void		makeLeafs();
void		parse(std::string line);
char		solve(char c, std::string);
void		parse(std::string line);
void		graphRecursion(Op *top, std::string lhs);
bool		isAlpha(char c);
int			revMatch(std::string str, int pos);
int			match(std::string str, int pos);
void		output(char c);
void		makeGraph(rule r);
char		DFSLeaves(Op* o, std::string found);
void		compute();
void		resetBranch(Op* o);
bool		checkExist(std::string str);
void		restart(std::string line);
#endif
