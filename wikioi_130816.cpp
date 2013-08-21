//3115 高精度练习之减法 
#include <stdio.h>
int main(){
	char A[502];
	char B[502];
	memset(A, 0, 502);
	memset(B, 0, 502);
	scanf("%s %s", &A, &B);
	lA = strlen(A);
	lB = strlen(B);
	int diff = lA - lB;
	int carry = 0;
	char C[502];
	for(int i = lB - 1, j = i + diff; i >= 0 && j >= 0; i++){
		C[i]
		;
	}
	return 0;
}

//1214 线段覆盖
//dp version: from chuanying
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <bitset>
#include <stack>
#include <set>
#include <algorithm>
#include <math.h>
#include <string.h>

using namespace std;

const int INT_MAX = 1 << 30;
const int DOUBLE_MAX = 1e37;

bool inter(pair<int, int> a, pair<int, int> b) {
    if (a.first >= b.second || b.first >= a.second) {
    	return false;
    } 
    return true;
}

int main()
{
    int n;
    cin >> n;
    if (n <= 0) {
    	cout << n; 
        return 0;
    }
    vector<pair<int, int> > vec(n);
    for (int i = 0; i < n; ++i) {
    	cin >> vec[i].first >> vec[i].second;
        if (vec[i].first > vec[i].second) {
        	swap(vec[i].first, vec[i].second);
        }
    }
    sort(vec.begin(), vec.end());
    vector<int> dp(n, 0);
    dp[0] = 1;
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (!inter(vec[i], vec[j])) {
            	dp[i] = max(dp[i], dp[j] + 1);
            } else {
            	dp[i] = max(dp[i], 1);
            }
        }
        ans = max(ans, dp[i]);
    }
	cout << ans;
    return 0;
}

//version2: sort the segments by the start point, then ...
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <bitset>
#include <stack>
#include <set>
#include <algorithm>
#include <math.h>
#include <string.h>

using namespace std;

const int INT_MAX = 1 << 30;
const int DOUBLE_MAX = 1e37;

int main()
{
    int n, x, y;
    cin >> n;
    vector<pair<int, int> > vec;
    for (int i = 0; i < n; ++i) {
    	cin >> x >> y;
        if (x > y) {
        	swap(x, y);
        }
        vec.push_back(pair<int, int>(x, y));
    }
    sort(vec.begin(), vec.end());
    vector<pair<int, int> > ans(1, vec[0]);
    for (int i = 1; i < vec.size(); ++i) {
        if (vec[i].first < ans.back().second) {//hjb: worthing notice
            if (vec[i].second < ans.back().second) {
            	ans.back() = vec[i];
            }
        } else {
        	ans.push_back(vec[i]);
        }
    }
    cout << ans.size();
    return 0;
}


//version 3: sort the segments by the end point.
#include <stdio.h>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX_N = 1000;
int main(){
	int n;
	scanf("%d", &n);
	//vector<pair<int, int>> itvls;
	pair<int, int> itvls[MAX_N];
	for(int i = 0; i < n; i++){
		scanf("%d %d", &itvls[i].first, &itvls[i].second);
		if(itvls[i].first < itvls[i].second)
			swap(itvls[i].first, itvls[i].second);
	}
	sort(itvls, itvls+n);
	
	int count = 0;
	int t = -1000;
	for(int i = 0; i < n; i++){
		if(t <= itvls[i].second){
			count++;
			t = itvls[i].first;
		}
	}
	printf("%d", count);
	return 0;
}

// version: using the self defined structure and cmp function
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct interval{
	int b;
	int e;
}interval_t;

bool cmp(interval_t ite1, interval_t ite2){
	return ite1.e <= ite2.e;
}

int main(){
	int n;
	scanf("%d", &n);
	vector<interval_t> itvls;
	for(int i = 0; i < n; i++){
		interval_t itvl;
		scanf("%d %d", &itvl.b, &itvl.e);
		if(itvl.b > itvl.e){
			int tmp = itvl.b;
			itvl.b = itvl.e;
			itvl.e = tmp;
		}
		itvls.push_back(itvl);
	}
	sort(itvls.begin(), itvls.end(), cmp);
	
	int count = 0;
	int t = -1000;
	for(int i = 0; i < itvls.size(); i++){
		if(t <= itvls[i].b){
			count++;
			t = itvls[i].e;
		}
	}
	printf("%d", count);
	return 0;
}

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
	sum = 0;
	int move = 0;
	for(int i = 0; i < N; i++){
		sum += A[i];
		if(sum != avg*(i+1))
			move++;
	}
	printf("%d", move);
	return 0;
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

//3038 3n+1问题 
#include <stdio.h>
int getStepsNumber(int n){
	int step = 0;
	int back_n = n;
	while(n != 1){  //hjb: treat the condition sentence carefully
		if(n&0x01)
			n = 3*n+1;
		else n /= 2;
		if(n == back_n) return -1;
		step++;
	}
	return step;
}

int main(){
	int t;
	scanf("%d", &t);
	for(int t1 = 0; t1 < t; t1++){
		int n;
		scanf("%d", &n);
		printf("%d\n",getStepsNumber(n)); //hjb：recheck the outline of programm when finish it
	}
	return 0;
}



//1842 递归第一次 
#include <stdio.h>
int recusive_f(int n){
	if(n >= 0) return 5;
	return recusive_f(n+1)+recusive_f(n+2)+1;
}

int main(){
	int n;
	scanf("%d", &n);
	printf("%d", recusive_f(n));
	return 0;
}

//1501 二叉树最大宽度和高度
//hjb：make sure to understand the problem and concept fully
#include <stdio.h>
#include <queue>
using namespace std;
typedef struct tree_node{
	int lc;
	int rc;
} node_t;

int getHeight(int idx, node_t* tree, int n){
	if(tree[idx].lc == 0 && tree[idx].lc == 0)
		return 1;
	int lh = 0;
	if(tree[idx].lc != 0) lh = getHeight(tree[idx].lc, tree, n);
	int rh = 0;
	if(tree[idx].rc != 0) rh = getHeight(tree[idx].rc, tree, n);
	return 1 + (lh > rh?lh:rh); //hjb: opertors
}

int getWidth(int idx, node_t* tree, int n){
	if(tree[idx].lc == 0 && tree[idx].lc == 0)
		return 1;
	int maxw = 1;
	queue<int> q;
	q.push(idx);
	while(!q.empty()){
		queue<int> q_nextlevel;
		while(!q.empty()){
			int idx = q.front();//hjb: how to use the queue
			q.pop();
			if(tree[idx].lc != 0) q_nextlevel.push(tree[idx].lc);
			if(tree[idx].rc != 0) q_nextlevel.push(tree[idx].rc);
		}
		maxw = maxw < q_nextlevel.size()?q_nextlevel.size():maxw;
		q = q_nextlevel;
	}
	return maxw;
}

int main(){
	int n;
	scanf("%d", &n);
	if(n == 0) {
		printf("0 0");
		return 0;
	}
	n++;
	node_t *tree = new node_t[n];
	for(int i = 1; i < n; i++){
		scanf("%d %d", &tree[i].lc, &tree[i].rc);
	}
	int h = getHeight(1, tree, n);
	int w = getWidth(1, tree, n);
	printf("%d %d", w, h);
	delete[] tree;
	return 0;
}



//1160 蛇形矩阵
// version simulation
#include <stdio.h>
#include <vector>
using namespace std; //hjb: namespace
int dir[][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
int main(){
	int n;
	scanf("%d", &n);
	vector<vector<int> > matrix(n, vector<int>(n, 0));
	matrix[n/2][n/2] = 1;
	int num = 2;
	int i = n/2, j = n/2;
	int d = 3;
	while(num <= n*n){
		int new_d = (d+1)%4;
		int new_i = i + dir[new_d][0];
		int new_j = j + dir[new_d][1];
		if(new_i >= 0 && new_i < n && new_i >= 0 && new_i < n && matrix[new_i][new_j] == 0){
			matrix[new_i][new_j] = num++;
			i = new_i;
			j = new_j;
			d = new_d;
		}
		else{
			i = i + dir[d][0];
			j = j + dir[d][1];
			matrix[i][j] = num++;
		}
	}
	for(int i = 0; i < n; i++){
		if(i != 0) printf("\n");
		for(int j = 0; j < n; j++){
			printf("%d ", matrix[i][j]);
		}
	}
	int sum = 0;
	for(int i = 0; i < n; i++){
		sum += matrix[i][i];
		sum += matrix[i][n - 1 - i];
	}
	sum -= 1;
	printf("\n%d", sum);
	return 0;
}

//version 2: draw each edges:
//hjb: anti-clockwise
#include <stdio.h>
#include <vector>
using namespace std; //hjb: namespace
int main(){
	int n;
	scanf("%d", &n);
	vector<vector<int> > matrix(n, vector<int>(n, 0));
	matrix[n/2][n/2] = 1;
	int num = 2;
	for(int round = 1; round <= n/2; round++){
		//line right: part1
		int row = n/2 + round - 1;
		int col = n/2 + round;  //hjb: redeclaration
		for(int i = 0; i < 2*round; i++) matrix[row - i][col] = num++;
		
		//line up
		row = n/2 - round;
		col = n/2 + round - 1;
		for(int i = 0; i < 2*round; i++) matrix[row][col-i] = num++;
		
		//line left
		row = n/2 - round + 1;
		col = n/2 - round;
		for(int i = 0; i < 2*round; i++) matrix[row + i][col] = num++;
	
		//line bottom:
		row = n/2 + round;
		col = n/2 - round + 1;
		for(int i = 0; i < 2*round; i++) matrix[row][col+i] = num++;
	}
	for(int i = 0; i < n; i++){
		if(i != 0) printf("\n");
		for(int j = 0; j < n; j++){
			printf("%d ", matrix[i][j]);
		}
	}
	int sum = 0;
	for(int i = 0; i < n; i++){
		sum += matrix[i][i];
		sum += matrix[i][n - 1 - i];
	}
	sum -= 1;
	printf("\n%d", sum);
	return 0;
}


//1083 Cantor表 
//version 2: simulate
#include <stdio.h>
int main(){
	int dir[][2] = {{-1, 1}, {1, -1}};
	int i = 1, j = 1;
	int n;
	scanf("%d", &n);
	int d = 0;
	while(n-- > 1){
		int new_i = i + dir[d][0];
		int new_j = j + dir[d][1];
		if(new_i <= 0){
			j++;
			d = (d+1)%2;
		}
		else if(new_j <= 0){
			i++;
			d = (d+1)%2;
		}
		else{
			i = new_i;
			j = new_j;
		}
	}
	printf("%d/%d", i, j);
	return 0;
}



//version 1: iterate
#include <stdio.h>
int main(){
	int n;
	scanf("%d", &n);
	if(n == 1){
		printf("1/1");
		return 0;
	}
	int sum = 1;
	int line = 2;
	while(sum + line < n){
		sum += line;
		line++;
	}
	int p = n - sum;
	int q = line + 1 - p;
	if(line & 0x01)
		printf("%d/%d", q, p);
	else
		printf("%d/%d", p, q);
	return 0;
}


//1978 Fibonacci数列 3 
#include <stdio.h>
int main(){
	int n;
	scanf("%d", &n);
	if(n == 1 && n == 2) 
		printf("1");
	else{
		int f1 = 1;
		int f2 = 1;
		for(int i = 3; i <= n; i++){
			int tmp = f1+f2;
			f1 = f2;
			f2 = tmp;
		}
		printf("%d", f2);
	}
	return 0;
}



// 1011 数的计算 
#include <stdio.h>
#include <queue>
using namespace std;  //hjb
int main(){
	int n;
	scanf("%d", &n);
	queue<int> q;
	q.push(n);
	int count = 0;
	while(!q.empty()){
		count++;
		int num = q.front();
		q.pop();
		for(int i = 1; 2*i <= num; i++) //hjb
			q.push(i);
	}
	printf("%d", count);
	return 0;
}



//1076 排序 
#include <stdio.h>
typedef int ElemType;//hjb: the order
void AdjustDown(ElemType A[], int k, int len){
	A[0] = A[k];
	for(int i = 2*k; i <= len; i *= 2){
		if(i < len && A[i] < A[i+1])
			i++;
		if(A[0] > A[i]) break;
		else{
			A[k] = A[i];
			k = i;
		}
	}
	A[k] = A[0];
}

void BuildMaxHeap(ElemType A[], int len){
	for(int i = len/2; i > 0; i--)
		AdjustDown(A, i, len);
}

void HeapSort(ElemType A[], int len){
	BuildMaxHeap(A, len);
	for(int i = len; i > 1; i--){
		A[0] = A[i];
		A[i] = A[1];
		A[1] = A[0];
		AdjustDown(A, 1, i-1);//hjb: i - 1
	}
}

int main(){
	int n;
	scanf("%d", &n);
	int *arr = new int[n+1];
	for(int i = 1; i <= n; i++){
		scanf("%d", arr+i);
	}
	HeapSort(arr, n);
	int i = 1;
	while(i <= n) printf("%d ", arr[i++]);
	delete[] arr;
	return 0;
}


//1075 明明的随机数 
#include <stdio.h>
int main(){
	int n;
	scanf("%d", &n);
	int *arr = new int[n];
	int i = 0;
	while(i <n && scanf("%d", (arr+i))) i++;  //an alternative form: &arr[i]
	i = 0; 
	while(i < n){
		int min_idx = i;
		for(int j = i; j < n; j++){
			if(arr[min_idx] > arr[j])
				min_idx = j;
		}
		if(i > 0 && arr[min_idx] == arr[i-1]){
			arr[min_idx] = arr[n-1];
			n--;
		}
		else{
			if(min_idx != i){
				int tmp = arr[min_idx];
				arr[min_idx] = arr[i];
				arr[i] = tmp;
			}
			i++;
		}
	}
	printf("%d\n", n);
	for(i = 0; i < n; i++)
		printf("%d ", arr[i]);
	delete[] arr;
	return 0;
}


//2235 机票打折 
#include <stdio.h>
int main(){
	int price;
	float discount;
	scanf("%d %f", &price, &discount);
	int rp = price * discount / 10.0;
	rp = rp - rp%10 + (rp%10 >= 5 ? 10 : 0);
	printf("%d", rp);
	return 0;
}

//1206 保留两位小数 
#include <stdio.h>
int main(){
	double f;
	scanf("%lf", &f); //how to input double precised number
	printf("%.2lf", f);
	return 0;
}

//1205 单词翻转
#include <stdio.h>
#include <string.h>
void reverse(char* b, char* e){
	e--;
	while(b < e){
		char tmp = *b;
		*b = *e;
		*e = tmp;
		b++;
		e--;
	}
}
int main(){
	char s[100];
	memset(s, 0, 100);
	//scanf("%99[^n]", s);
	gets(s);
	char* p = s;
	while(*p == ' ') p++;
	char* word_b = p;
	char* word_e = NULL;
	while(*p){
		if(*p == ' '){
			word_e = p;
			reverse(word_b, word_e);
			do{
				p++;
			}while(*p == ' ');
			if(*p == 0) break;
			word_b = p;
		}
		p++;
	}
	word_e = p;
	reverse(word_b, word_e);
	reverse(s, p);
	printf("%s", s);
	return 0;
}

//1204 寻找子串位置 
#include <stdio.h>
#include <string.h>
int main(){
	char s1[100];
	char s2[100];
	memset(s1, 0, 100);
	memset(s2, 0, 100);
	scanf("%s%s", &s1, &s2);
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	for(int i = 0; i < len1-len2+1; i++){
		int j = 0;
		for(; j < len2; j++){
			if(s1[i+j] != s2[j]) 
				break;
		}
		if(j == len2){
			printf("%d", i+1);
			return 0;
		}
	}
	return 0;
}

//1203 判断浮点数是否相等 
#include <stdio.h>
int main(){
	float f1, f2;
	scanf("%f %f", &f1, &f2);
	if(f1 - f2 < 1e-8 && f1 - f2 > -1e-8) //also ok for: if(f1 - f2 < 1e-8 && f2 - f1 < 1e-8)
		printf("yes");
	else printf("no");
	return 0;
}

//1202 求和 
#include <stdio.h>
int main(){
	int n;
	scanf("%d", &n);
	int sum = 0;
	for(int i = 0; i < n; i++){
		int num;
		scanf("%d", &num);
		sum += num;
	}
	printf("%d", sum);
	return 0;
}

// 1201 最小数和最大数 
#include <stdio.h>
int main(){
	int maxn = 0x80000000;
	int minn = 0x7FFFFFFF;
	int count;
	if(scanf("%d", &count) && count){
		for(int i = 0; i < count; i++){
			int n;
			scanf("%d", &n);
			maxn = maxn < n ? n :maxn;
			minn = minn > n ? n :minn;
		}
		printf("%d %d", minn, maxn);
	}
	return 0;
}

// 1475 m进制转十进制
#include <stdio.h>
#include <string.h>
int main(){
	char s[100];
	memset(s, 100, 0);
	int base;
	if(scanf("%s%d", &s, &base)){
		long num = 0;
		int len = strlen(s);
		if(base > 9){
			for(int i = 0; i < len; i++){
				int digit;
				switch(s[i]){
					case 'F':
						digit = 15;
						break;
					case 'E':
						digit = 14;
						break;
					case 'D':
						digit = 13;
						break;
					case 'C':
						digit = 12;
						break;
					case 'B':
						digit = 11;
						break;
					case 'A':
						digit = 10;
						break;
					default:
						digit = s[i] - '0';
						break;
				}
				num = num*base + digit;
			}
		}
		else{
			for(int i = 0; i < len; i++){
				num = num*base + s[i] - '0';
			}
		}
		printf("%d", num);
	}
	return 0;
}


#include<stdio.h>
#include<string.h>
char xx(char w)
{
    if (w>64) return (w-55);
        return (w-48);
}
long cf(long j,long k)
{
    long p=1;
    while(k>0)
    {
        p=p*j;
        k--;
        
    }
    return p;
}
main()
{
    char y[300];
    long q,a,b,c,d;
    scanf("%s%d",&y,&q);
    a=0;c=0;
    b=strlen(y)-1;
    while(b>=0)
    {
        y[a]=xx(y[a]);
        c=(cf(q,b))*y[a]+c;
        a++;
        b--;
        
    }
    printf("%d",c);
}