#include "expert.hpp"

void	compute()
{
	try
	{
		for (std::map<char,Leaf*>::iterator it=leaves.begin(); it!=leaves.end(); ++it)
           	solve(it->second->c, "");
	}
	catch (const char *str)
	{
		std::cout << RED << str;
		exit(1);
	}
	for (unsigned int i = 0; i < queries.size(); i++)
		output(queries[i]);
}

void resetBranch(Op* o)
{
	o->t = 0;
	if(o->lNode && o->lNode->type == 'o')
		resetBranch(dynamic_cast<Op*>(o->lNode));
	if(o->rNode && o->rNode->type == 'o')
		resetBranch(dynamic_cast<Op*>(o->rNode));
}

bool	checkExist(std::string str)
{
	for(unsigned int i = 0; i < str.size(); i++){
		if (leaves.find(str[i]) == leaves.end()){
			std::cout << ORANGE << "Entry does not exist >.< Try again...\n";
			return false;
		}
	}
	return true;
}

void	restart(std::string line)
{
	if (line[0] == 'q' || line[0] == 'n')
		exit(0);
	if (line[0] != '=' && line[0] != '?')
		return ;
	if (!checkExist(line.substr(1)))
			return ;
	if (line[0] == '?')
	{
		queries = line.substr(1);
		for (unsigned int i = 0; i < queries.size(); i++)
			output(queries[i]);
		return ;
	}
	if (line[0] == '=')
	{
		assersions = line.substr(1);
		for (unsigned int i = 0; i < rules.size(); i++)
			for (unsigned int j = 0; j < leaves[rules[i].rhs]->o.size(); j++)
				resetBranch(leaves[rules[i].rhs]->o[j]);
		for (std::map<char,Leaf*>::iterator it=leaves.begin(); it!=leaves.end(); ++it)
		{
				it->second->ran = 0;
				it->second->t = 0;
				it->second->branch = -1;
		}
		for (unsigned int i = 0; i < assersions.size(); i++){
			leaves[assersions[i]]->t = 2;
		}
		compute();
	}
}
