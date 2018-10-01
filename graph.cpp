#include "expert.hpp"

char	endNode(INode **n, std::string str){
	int i = 0;
	char sign = 1;
	if (str[0] == '!')
	{
		sign = -1;
		i++;
	}
	*n = leaves[str[i]];
	return sign;
}

char	midNode(Op *n, std::string str, bool)
{
	int m;
	char c = 1;
	while (str[0] == '(' && str[(m = match(str, 0)) + 1] == '\0')
		str = str.substr(1, m - 1) + str.substr(m + 1);
	if (str[0] == '!' && str[1] == '(')
		c = -1;
	while (str[0] == '(' && str[(m = match(str, 0)) + 1] == '\0')
		str = str.substr(1, m - 1) + str.substr(m + 1);
	graphRecursion(n, str);
	return c;
}

void	graphRecursion(Op *top, std::string lhs){
	if (lhs.size() <= 2)
	{
		top->o = '-';
		top->lPos = endNode(&top->lNode, lhs);
		return ;
	}
	int opPos;
	if (lhs[0] == '(' &&  match(lhs, 0) == static_cast<int>(lhs.size()) - 1)
		lhs = lhs.substr(1, lhs.size() - 1);
	if (lhs[0] == '!' && lhs[1] == '(' && match(lhs, 1) == static_cast<int>(lhs.size()) - 1)
	{
		top->aPos = 0 - top->aPos;
		lhs = lhs.substr(2, lhs.size() - 3);
	}
	if (lhs[0] == '(')
		opPos = match(lhs, 0) + 1;
	else if (lhs[1] == '(' && lhs[0] == '!')
		opPos = match(lhs, 1) + 1;
	else
		opPos = (lhs[0] == '!' ? 2 : 1);
	top->o = lhs[opPos];
	top->t = 0;
	std::string left = lhs.substr(0, opPos);
	std::string right = lhs.substr(opPos + 1);
	if (left.size() <= 2)
		top->lPos = endNode(&top->lNode, left);
	else
	{
		top->lNode = new Op();
		top->lPos = midNode(dynamic_cast<Op*>(top->lNode), left, false);
	}
	if (right.size() <= 2)
		top->rPos = endNode(&top->rNode, right);
	else
	{
		top->rNode = new Op();
		top->rPos = midNode(dynamic_cast<Op*>(top->rNode), right, true);
	}
}

void	makeGraph(rule r){
	Leaf *top;
	top = leaves[r.rhs];
	top->o.push_back(new Op());
	top->o.back()->pPos = (r.neg ? -1 : 1);
	graphRecursion(top->o.back(), r.lhs);
}

char	DFSLeaves(Op* o, std::string found){
	char b;
	char b2;
	if (o->o == '-')
	{
		if ((b = solve(dynamic_cast<Leaf*>(o->lNode)->c, found) * o->lPos * o->aPos) > 0)
			return (b * o->pPos);
		else
			return 0;
	}
	if (o->lNode->type == 'e'){
		b = solve(dynamic_cast<Leaf*>(o->lNode)->c, found);
	}
	else{
		b = DFSLeaves(dynamic_cast<Op*>(o->lNode), found);
	}
	if (o->rNode->type == 'e')
		b2 = solve(dynamic_cast<Leaf*>(o->rNode)->c, found);
	else
		b2 = DFSLeaves(dynamic_cast<Op*>(o->rNode), found);
	if (o->o == '+')
		o->t = (b * o->lPos > b2 * o->rPos ? b2 * o->rPos : b * o->lPos) * o->aPos;
	if (o->o == '|')
		o->t = (b * o->lPos < b2 * o->rPos ? b2 * o->rPos : b * o->lPos) * o->aPos;
	if (o->o == '^')
	{
		if (b * o->lPos * b2 * o->rPos > 0)
			o->t = (0 - (abs(b) > abs(b2) ? abs(b2) : abs(b)));
		else
			o->t = (abs(b) > abs(b2) ? abs(b2) : abs(b));
	}
	if (o->t > 0)
		return (o->t * o->pPos);
	return 0;
}