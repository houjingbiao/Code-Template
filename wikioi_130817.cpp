//1098 均分纸牌
#include <stdio.h>
int main(){
	int N;
	scanf("%d", &N);
	int *A = new int[N];
	for(int i = 0; i < N; i++)
		scanf("%d", A+i);
	int sum = 0;
	for(int i = 0; i < N; i++)
		sum += A[i];
	int avg = sum/N;
	int move = 0;
	for(int i = 0; i < N; i++){
		move += 
	}
	
	
}


//3145 汉诺塔游戏 
#include <stdio.h>
int getStepNumber(int n){
	if(n == 0) return 0;
	int step = 1;
	for(int i = 2; i <= n; i++){
		step = step*2 + 1;
	}
	return step;
}
void hanoi(int n, char X, char Y, char Z){
	if(n == 0) return;
	if(n == 1){
		printf("%d from %c to %c\n", n, X, Y);
		return;
	}
	hanoi(n-1, X, Z, Y);
	printf("%d from %c to %c\n", n, X, Y);
	hanoi(n-1, Z, Y, X);
}

int main(){
	int n;
	scanf("%d", &n);
	printf("%d\n", getStepNumber(n));
	hanoi(n, 'A', 'C', 'B');
	return 0;
}

//3143 二叉树的序遍历 
#include <stdio.h>
typedef struct tree_node{
	int lc;
	int rc;
}node_t;

void preorder(node_t *tree, int i, int n){
	if(i == 0) return;
	printf("%d ", i);
	preorder(tree, tree[i].lc, n);
	preorder(tree, tree[i].rc, n);
}

void inorder(node_t *tree, int i, int n){
	if(i == 0) return;
	inorder(tree, tree[i].lc, n);
	printf("%d ", i);
	inorder(tree, tree[i].rc, n);
}

void postorder(node_t *tree, int i, int n){
	if(i == 0) return;
	postorder(tree, tree[i].lc, n);
	postorder(tree, tree[i].rc, n);
	printf("%d ", i);
}

int main(){
	int n;
	scanf("%d", &n);
	node_t *tree = new node_t[n+1];
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &tree[i].lc, &tree[i].rc);
	}
	preorder(tree, 1, n);
	printf("\n");
	inorder(tree, 1, n);
	printf("\n");
	postorder(tree, 1, n);
	return 0;
}

//1012 最大公约数和最小公倍数问题
#include <stdio.h>
int gcd(int m, int n){
	int a;
	while(m%n){
		a = m%n;
		m = n;
		n = a;
	}
	return n;
}
int main(){
	int x0, y0;
	scanf("%d %d", &x0, &y0);
	if(x0 > y0){
		printf("0");
		return 0;
	}
	if(x0 == y0){
		printf("1");
		return 0;
	}
	if(y0%x0 != 0){
		printf("0");
		return 0;
	}
	int x = y0/x0;
	int count = 2; //hjb: 1*20 = 20*1 = 20
	for(int i = 2; i <= x/2; i++){
		if(x%i == 0 && gcd(i, x/i) == 1)
			count++;
	}
	printf("%d", count);
	return 0;
}



//1474 十进制转m进制 
#include <stdio.h>
#include <string.h> //hjb: when should add it
char* conversToBase(int n, int m){
	char* ret = new char[100];
	memset(ret, 0, 100);
	int i = 0;
	while(n){
		int digit = n%m;
		if(digit < 10) ret[i] = digit + '0';
		else ret[i] = digit - 10 + 'A';
		i++;
		n /= m;
	}
	for(int a=0, b=i-1; a < b; a++, b--){
		char tmp = ret[a];
		ret[a] = ret[b];
		ret[b] = tmp;
	}
	return ret;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	printf("%s", conversToBase(n, m));
	return 0;
}


//1079 回家
#include <stdio.h>
#include <vector>
using namespace std;
typedef struct edge{
	char v1;
	char v2;
	int dist;
}edge_t;

void init_distToZ(int distToZ[], int n){
	for(int i = 0; i < n; i++){
		distToZ[i] = 999999;
	}
}

int charToIndex(char ch){ //hjb: miss the argument
	int idx = 0;
	if(ch >= 'a' && ch <= 'z')
		idx = ch - 'a';
	else //if(ch >= 'A' && ch <= 'Z')
		idx = 26 + ch - 'A';
	return idx;
}

char indexToChar(int idx){
	if(idx < 26)
		return 'a'+idx;
	else
		return 'A'+idx-26;
}

int get_distToZ(int distToZ[], char ch){
	int idx = charToIndex(ch);
	return distToZ[idx];
}

void set_distToZ(int distToZ[], char ch, int dist){
	int idx = charToIndex(ch);
	distToZ[idx] = dist;
}

void setTargetSet(long* isInTargetSet, char ch, bool connected){
	int idx = charToIndex(ch);
	long mask = (1 << idx);
	if(connected) (*isInTargetSet) |= mask;
	else (*isInTargetSet) &= (~mask);
}

bool getTargetSet(long* isInTargetSet, char ch){
	int idx = charToIndex(ch);
	long mask = (1 << idx);
	return (*isInTargetSet & mask); //hjb: pointer with "*" or without "*"
}

char getNearestNodeNotInTarget(long* isInTargetSet, int distToZ[]){
	int idx = 0;
	int min_dist = 999999;
	for(int i = 0; i < 52; i++){
		long mask = (1 << i);
		if(!(mask & (*isInTargetSet)) && min_dist > distToZ[i]){
			idx = i;
			min_dist = distToZ[i];
		}
	}
	return indexToChar(idx);
}

int main(){
	int p;
	scanf("%d", &p);
	vector<edge_t> edges;
	int i = 0;
	for(; i < p; i++){
		scanf("%s %s %d", &edge.v1, &edge.v2, &edge.dist);
		edges.push_back(edge);
	}
	//dist To Z
	int distToZ[52];
	init_distToZ(distToZ, 52);
	set_distToZ(distToZ, 'Z', 0);
	
	//target set
	long isInTargetSet = 0;
	setTargetSet(&isInTargetSet, 'Z', true);
	
	char target = 'Z';
	while(1){
		vector<edge_t>::iterator ite = edges.begin();
		while(ite != edges.end()){
			if(ite->v1 == target){
				int dist_v1 = get_distToZ(distToZ, ite->v1);
				int dist_v2 = get_distToZ(distToZ, ite->v2);
				if(dist_v2 > dist_v1 + ite->dist){
					set_distToZ(distToZ, ite->v2, dist_v1 + ite->dist);
				}
				ite = edges.erase(ite);
			}
			else if(ite->v2 == target){
				int dist_v1 = get_distToZ(distToZ, ite->v1);
				int dist_v2 = get_distToZ(distToZ, ite->v2);
				if(dist_v1 > dist_v2 + ite->dist){
					set_distToZ(distToZ, ite->v1, dist_v2 + ite->dist);
				}
				ite = edges.erase(ite);
			}
			else ite++;
		}
		char ch = getNearestNodeNotInTarget(&isInTargetSet, distToZ);
		if(ch >= 'A' && ch <= 'Y'){
			printf("%c %d", ch, get_distToZ(distToZ, ch));
			return 0;
		}
		else{
			setTargetSet(&isInTargetSet, ch, true);
			target = ch;
		}
	}	
	return 0;
}