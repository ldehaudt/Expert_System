#include "INode.hpp"

Op::Op(){
	type = 'o';
	t = 0;
	pPos = 1;
	lPos = 1;
	rPos = 1;
	aPos = 1;
}

Op::~Op(){}

Leaf::Leaf(){
	type = 'e';
	ran = false;
	t = 0;
	branch = -1;
}

Leaf::~Leaf(){}
