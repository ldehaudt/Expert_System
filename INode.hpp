#ifndef INODE_HPP
# define INODE_HPP

# include <iostream>
# include <vector>

class INode {
	public:
		char type;
		char t;
		virtual ~INode() {}
};

class Op : public INode {
	public:
		INode *lNode;
		INode *rNode;
		char o;
		char pPos;
		char aPos;
		char lPos;
		char rPos;
		Op();
		~Op();
};

class Leaf : public INode {
	public:
		bool ran;
		int branch;
		std::vector<Op*>o;
		char c;
		Leaf();
		~Leaf();
};

#endif
