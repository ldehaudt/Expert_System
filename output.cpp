#include "expert.hpp"

void output_recurse(Op *o, bool st)
{
	if (st && o->aPos == -1)
		std::cout << WHITE << "¬";
	if (!st && o->aPos * o->pPos == -1)
		std::cout << WHITE << "¬";
	st = 0;
	if (o->o != '-')
		std::cout << WHITE << "(";
	if (o->lPos == -1)
		std::cout << WHITE << "¬";
	if (o->lNode->type == 'e')
	{
		if (assersions.find(dynamic_cast<Leaf*>(o->lNode)->c) != std::string::npos)
			std::cout << GREEN << dynamic_cast<Leaf*>(o->lNode)->c;
		else if (dynamic_cast<Leaf*>(o->lNode)->t == 0 || dynamic_cast<Leaf*>(o->lNode)->t == -1)
			std::cout << ORANGE << dynamic_cast<Leaf*>(o->lNode)->c << " [default]";
		else
			output_recurse(dynamic_cast<Leaf*>(o->lNode)->o
				[dynamic_cast<Leaf*>(o->lNode)->branch], st);
	}
	else
		output_recurse(dynamic_cast<Op*>(o->lNode), st);
	if (o->o != '-')
		std::cout << WHITE << " " << symbols[o->o] << " ";
	else
		return ;
	if (o->rPos == -1)
		std::cout << WHITE << "¬";
	if (o->rNode->type == 'e')
	{
		if (assersions.find(dynamic_cast<Leaf*>(o->rNode)->c) != std::string::npos)
			std::cout << GREEN << dynamic_cast<Leaf*>(o->rNode)->c;
		else if (dynamic_cast<Leaf*>(o->rNode)->t == 0 || dynamic_cast<Leaf*>(o->rNode)->t == -1)
			std::cout << ORANGE << dynamic_cast<Leaf*>(o->rNode)->c << " [default]";
		else
			output_recurse(dynamic_cast<Leaf*>(o->rNode)->o
				[dynamic_cast<Leaf*>(o->rNode)->branch], st);
	}
	else
		output_recurse(dynamic_cast<Op*>(o->rNode), st);

	std::cout << WHITE << ")";
}

void output(char c)
{
	std::cout << WHITE << "NOW DOING...................." << c << "!!!\n";
	if (assersions.find(c) != std::string::npos)
		std::cout << GREEN << c << WHITE << " => " << c << std::endl;
	else if (leaves[c]->t == -1 || leaves[c]->t == 0)
		std::cout << ORANGE << "¬" << c << " [default]" << WHITE << " => " << "¬" << c << std::endl;
	else
	{
		output_recurse(leaves[c]->o[leaves[c]->branch], true);
		if (leaves[c]->o[leaves[c]->branch]->pPos == -1)
			std::cout << WHITE << " => !" <<  c << std::endl;
		else
			std::cout << WHITE << " => " <<  c << std::endl;
	}
	std::cout << WHITE << "Answer: ";
	if (leaves[c]->t == 2)
		std::cout << GREEN << c << " is surely TRUE! I promise! =)\n";
	else if (leaves[c]->t == 1)
		std::cout << GREEN << c << " is TRUE assuming the default variable is false\n";
	else if (leaves[c]->t == 0 || leaves[c]->t == -1)
		std::cout << RED << c << " is FALSE assuming the default variable is false\n";
	else
		std::cout << RED << c << " is surely FALSE! Not much can be done about it =(\n";
	std::cout << std::endl;
}
