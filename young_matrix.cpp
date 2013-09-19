//young矩阵可以认为是以为排序数组的推广，并且与堆（heap）有很大的相似。
//增删查改：
//在一位排序数组里面，任意两个相邻的元素之间的大小关系是确定的。而在young矩阵里面，任意一个2*2的子矩阵[A(i,j), A(i,j+1); A(i+1,j), A(i+1,j+1)]都满足：A(i,j) < A(i,j+1), A(i+1,j) < A(i+1,j+1)。在堆里面，是把数组中的元素组织成了一个完全二叉树，且满足A[i] < A[2*i], A[i] < A[2*i+1]。
//另外，从递归的角度看的话，三者都是递归的结构。
//增：从右下角开始
//删：1.删除左上角的最小元素， 2.删除任意元素
//查：查找的过程其实是相当于一个剪枝的过程，具体地，比较查找值与中间节点，比较结果来确定下一步的查找范围。观察young矩阵可以知道每一个7型都是一个
//改：
#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include "windows.h"
using namespace std;
#define MAXV 0x7FFFFFFF
#define MAX_M 10
#define MAX_N 10
int Y[MAX_M][MAX_N];
void young_reset(){
	for(int i = 0; i < MAX_M; i++)
		for(int j = 0; j < MAX_N; j++)
			Y[i][j] = MAXV;
}

void young_init(int A[], int n){
	sort(A, A+n);
	int k = 0;
	for(int i = 0; i < MAX_M; i++){
		for(int j = 0; j < MAX_N; j++){
			if(k == n) return;//hjb: should be excuted first then assignment
			Y[i][j] = A[k++];
		}
	}
}

bool young_isEmpty(){
	return Y[0][0] == MAXV;
}

bool young_isFull(){
	return Y[MAX_M-1][MAX_N-1] != MAXV;
}

void young_print(){
	for(int i = 0; i < MAX_M; i++){
		for(int j = 0; j < MAX_N; j++){
			if(Y[i][j] < MAXV)
				printf("%2d ", Y[i][j]);
			else
				printf("%s ", "##");
		}
		printf("\n");
	}
}

int young_extractMin(){
	if(!young_isEmpty()){
		int ret = Y[0][0];
		int i = 0, j = 0;
		while(i < MAX_M - 1&& j < MAX_N - 1 && Y[i][j] < MAXV){
			if(Y[i][j+1] <= Y[i+1][j]){
				Y[i][j] = Y[i][j+1];
				j++;
			}
			else{
				Y[i][j] = Y[i+1][j];
				i++;
			}
		}
		while(i == MAX_M - 1 && j < MAX_N-1){
			Y[i][j] = Y[i][j+1];
			j++;
		}
		while(j == MAX_N - 1 && i < MAX_M-1){
			Y[i][j] = Y[i+1][j];
			i++;
		}
		Y[i][j] = MAXV;
	}
	return -1;
}

bool young_find(int val){
	if(val >= MAXV)
		return false;
	int i = 0, j = MAX_N - 1;
	while(j>=0 && i < MAX_M){
		if(val < Y[i][j])
			j--;
		else if(val > Y[i][j])
			i++;
		else
			return true;
	}
	return false;
}

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void young_min_heapify(int i,int j)
{
	int x = i， y = j;
	if (i>0 && Y[i][j] < Y[i-1][j]){
		x = i-1;
		y = j;
	}
	
	if (j>0 && Y[x][y] < Y[i][j-1]){
		x = i;
		y = j-1;
	}
	
	if (x !=i || y !=j)	{
		swap(Y[i][j],Y[x][y]);
		printf("\n%d %d:\n", x, y);
		young_print();
		young_min_heapify(x, y);
	}
}

bool young_insert(int val){
	Y[MAX_M-1][MAX_N-1] = val;
	young_min_heapify(MAX_M-1, MAX_N-1);
	return true;
}

void young_sort(){
}

int main(){
	young_reset();
	young_print();
	int A[MAX_M*MAX_N];
	for(int i = 0; i < MAX_M*MAX_N; i++){
		A[i] = rand()%100;
		young_insert(A[i]);
		printf("\nthe %d:\n", i);
		young_print();
	}
	//young_init(A, 100);
	young_print();
	int j = 0;
	/*while(1){
	printf("\nthe %d:\n", j);
	young_extractMin();
	young_print();
	}*/
	young_extractMin();
	int ret = young_find(MAXV);
	return -1;
}