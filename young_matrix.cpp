#define MAXV 0x7FFFFFFF
#define MAX_M 100
#define MAX_N 10

int Y[MAX_M][MAX_N];

void init(){
	for(int i = 0; i < MAX_M; i++)
		for(int j = 0; j < MAX_N; j++)
			Y[i][j] = MAXV;
}

void init(int A[], int n){
	sort(A, A+n);
	int k = 0;
	for(int i = 0; i < MAX_M; i++)
		for(int j = 0; j < MAX_N; j++)
			Y[i][j] = A[k++];
}

bool isEmpty(){
	return Y[0][0] == MAXV;
}

bool isFull(){
	return Y[MAX_M-1][MAX_N-1] != MAXV;
}

void print(){
	for(int i = 0; i < MAX_M; i++){
		for(int j = 0; j < MAX_N; j++){
			if(Y[i][j] < MAXV)
				printf("%d", Y[i][j]);
			else
				printf("%c", '#');
		}
	}
}

int extractMin(){
	if(!isEmpty()){
		int ret = Y[0][0];
		int i = 0, j = 0;
		while(i < MAX_M-1 && j < MAX_N-1){
			if(Y[i][j+1] <= Y[i+1][j]){
				Y[i][j] = Y[i][j+1];
				j++;
			}
			else{
				Y[i][j] = Y[i+1][j];
				i++;
			}
		}
	}
	return -1;
}

void insert(int val){
	
}



int find(int val){
	return -1;
}

int extractMin(){
	return -1;
}

int extractMin(){
	return -1;
}

void sort(){
}