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
void heapAdjust(int arr[], int n, int i){
	int left = 2*i+1;
	int right = 2*i+2;
	if(left < n){
		if(right < n){
			if(arr[left] > arr[right]){
				if(arr[i] < arr[left]){
					int tmp = arr[i];
					arr[i] = arr[left];
					arr[left] = tmp;
					heapAdjust(arr, n, left);
				}
			}
			else{
				if(arr[i] < arr[right]){
					int tmp = arr[i];
					arr[i] = arr[right];
					arr[right] = tmp;
					heapAdjust(arr, n, right);
				}
			}
		}
		else{
			if(arr[i] < arr[left]){
				int tmp = arr[i];
				arr[i] = arr[left];
				arr[left] = tmp;
			}
		}
	}
}
int main(){
	int n;
	scanf("%d", &n);
	int* arr = new int[n];
	int i = 0;
	while(i <n && scanf("%d", (arr+i))) i++;
	
	for(i = n/2-1; i >= 0; i--)
		heapAdjust(arr, n, i);
	
	int curr_n = n;
	while(curr_n > 3){
		int tmp = arr[curr_n - 1];
		arr[curr_n - 1] = arr[0];
		arr[0] = tmp;
		curr_n--;
		for(i = curr_n/2-1; i >= 0; i--)
			heapAdjust(arr, curr_n, 0);
	}
	i = 0;
	while(i < n) printf("%d", arr[i++]);
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