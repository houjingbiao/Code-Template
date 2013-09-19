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



void young_insert_rec(int val, int i, int j){
	/*if(val >= MAXV)	return;
	int i = 0, j = MAX_N - 1;
	while(j>=0 && i < MAX_M){
	if(val < Y[i][j])
	j--;
	else if(val > Y[i][j])
	i++;
	else
	return true;
	}*/

	while(i < MAX_M && j < MAX_N){
		if(val > Y[i][j]){
			i++, j++;
		}
		else if(val < Y[i-1][j]){
			int t = val;
			val = Y[i-1][j];
			Y[i-1][j] = t;
			return young_insert_rec(val, i-1, j-1);
		}
	}
	while(i == MAX_M && Y[i-1][j] < val){
		j++;
	}
	while(j == MAX_N && Y[i][j-1] < val){
		i++;
	}
	return;
}

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

//void young_min_heapify(int a[][11],int i,int j)
void young_min_heapify(int i,int j)
{
	int x,y;
	if (i>0 && Y[i][j] < Y[i-1][j])
	{
		x = i-1;
		y = j;
	}
	else { x = i; y = j;}
	if (j>0 && Y[x][y] < Y[i][j-1])
	{
		x = i;
		y = j-1;
	}
	if (x !=i || y !=j)
	{
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