#include "stdio.h"
typedef struct Node{
	int parent;
} PSnode;

int getParent(int p, PSnode* ps){
	if(ps[p].parent != p)	ps[p].parent = getParent(ps[p].parent, ps);
	return ps[p].parent;
}

void doUnion(int p1, int p2, PSnode* ps){
	int parent = getParent(ps[p2].parent, ps);
	ps[parent].parent = p1;
}

int main(){
	int t = 0;
	int n, m;
	while(scanf("%d %d", &n, &m) && (n||m))
	{
		t++;
		n++;
		PSnode* ps = new PSnode[n];
		for(int i = 1; i < n; i++)
		{
			ps[i].parent = i;
		}

		int union_count = n-1;
		for(int i = 0; i < m; i++)
		{
			int p1, p2;
			scanf("%d %d", &p1, &p2);
			if(getParent(p1, ps) == getParent(p2, ps)) continue;

			union_count--;
			doUnion(p1, p2, ps);
		}
		printf("Case %d: %d\n", t, union_count);
		delete[] ps;
	}
	return 0;
}
