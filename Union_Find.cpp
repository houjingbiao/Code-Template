#include "stdio.h"
typedef struct Node{
	int parent;
} Union_Find_node;

int getParent(int p, Union_Find_node* ps){
	if(ps[p].parent != p)	ps[p].parent = getParent(ps[p].parent, ps);
	return ps[p].parent;
}

void doUnion(int p1, int p2, Union_Find_node* ps){
	int parent = getParent(ps[p2].parent, ps);
	ps[parent].parent = p1;
}