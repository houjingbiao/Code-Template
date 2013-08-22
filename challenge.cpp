#include <stdio.h>
#include <vector>
#include <utility>
using namespace std;
int main(){
	int N, S;
	scanf("%d %d", &N, &S);
	if(N <= 0) return 0;
	vector<pair<int, int>> weeks;
	for(int i = 0; i < N; i++){
		pair<int, int> week;
		scanf("%d %d", &week.first, &week.second);//hjb: second
		weeks.push_back(week);
	}
	int minP = weeks[0].first;
	unsigned long long total = minP * weeks[0].second;//hjb: unsigned long long
	for(int i = 1; i < weeks.size(); i++){
		minP = min(minP+S, weeks[i].first);
		total += minP * weeks[i].second;//hjb: i => 0 and +
	}
	printf("%llu\n", total);//hjb: "%llu"
	return 0;
}


//POJ 2190: Stall Reservations
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;
void heap_sift_down(vector<int>& heap, vector<int>& stalls){
	heap[0] = heap[1];
	int k = 1;
	int i = 2;
	while(i < heap.size()){
		if(i+1 < heap.size() && stalls[heap[i+1]] < stalls[heap[i]])
			i++;
		if(stalls[heap[i]] >= stalls[heap[0]]) break;////hjb: plural and compare with stalls[heap[0]]
		else{
			heap[k] = heap[i];
			k = i;
			i *= 2;
		}
	}
	heap[k] = heap[0];//hjb: colon
}

void heap_sift_up(vector<int>& heap, vector<int>& stalls){
	heap[0] = heap[heap.size() - 1];
	int k = heap.size() - 1;
	int i = k/2;
	while(i >= 1){ //hjb: >= not >
		if(stalls[heap[i]] > stalls[heap[0]]){ //hjb: plural and compare with stalls[heap[0]]
			heap[k] = heap[i];
			k = i;
			i = k/2;
		}
		else break;
	}
	heap[k] = heap[0];
}

typedef struct thecow{
	int idx;
	pair<int, int> intv;
}milkcow;

bool compare(milkcow c1, milkcow c2){
	return c1.intv.first < c2.intv.first;
}

int main(){
	int N;
	if(scanf("%d", &N) && N){
		vector<milkcow> cows;
		for(int i = 0; i < N; i++){
			milkcow cow;
			scanf("%d %d", &cow.intv.first, &cow.intv.second);
			cow.idx = i;
			cows.push_back(cow);
		}
		sort(cows.begin(), cows.end(), compare);
		int* stallToCow = new int[cows.size()];
		memset(stallToCow, 0, cows.size()*sizeof(int));//hjb: sizeof(int)
		vector<int> heap(1, 0);
		vector<int> stalls;
		stalls.push_back(cows[0].intv.second);
		heap.push_back(stalls.size()-1);
		stallToCow[cows[0].idx] = stalls.size()-1;
		for(int i = 1; i < N; i++){
			if(stalls[heap[1]] < cows[i].intv.first){
				stalls[heap[1]] = cows[i].intv.second;
				stallToCow[cows[i].idx] = heap[1];
				heap_sift_down(heap, stalls);
			}
			else{
				stalls.push_back(cows[i].intv.second);
				heap.push_back(stalls.size()-1);
				stallToCow[cows[i].idx] = stalls.size()-1;
				heap_sift_up(heap, stalls);
			}
		}
		printf("%d\n", stalls.size());
		for(int i = 0; i < N; i++)
			printf("%d\n", stallToCow[i]+1);
		delete stallToCow;
	}
	return 0;
}





//POJ 1328: Radar Installation
#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
using namespace std;
int main(){
	//freopen("in.txt", "r", stdin);
	int n;
	int r;
	int t = 0;
	while(scanf("%d %d", &n, &r) && n){
		t++;
		vector<pair<double, double>> islands;
		bool haveSolution = true;
		for(int i = 0; i<n; i++){
			double d1, d2;
			scanf("%lf %lf", &d1, &d2);
			if(haveSolution && d2 <= r){
				double dist = sqrt(double((r + d2)*(r - d2)));
				pair<double, double> island;
				island.first = d1 - dist;
				island.second = d1 + dist;
				islands.push_back(island);
			}
			else 
				haveSolution = false;
		}
		if(haveSolution == false){
			printf("Case %d: -1\n", t);
			continue;
		}
		sort(islands.begin(), islands.end());
		double maxX = islands[0].second;
		int count = 1;
		for(int i = 1; i < n; i++){
			if(islands[i].first > maxX){
				count++;
				maxX = islands[i].second;
			}
			else{
				maxX = min(islands[i].second, maxX);
			}
		}
		printf("Case %d: %d\n", t, count);
	}
	return 0;
}




//POJ 2376: Cleaning Shifts
#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
int main(){
	int N, T;
	scanf("%d %d", &N, &T);
	vector<pair<int, int>> cows;
	for(int i = 0; i < N; i++){
		pair<int, int> cow;
		scanf("%d %d", &cow.first, &cow.second);
		cows.push_back(cow);
	}
	sort(cows.begin(), cows.end());
	if(cows[0].first != 1){
		printf("-1\n");
		return 0;
	}
	int count = 1;
	int curT = 1;
	int maxT = 0;
	for(int i = 0; i < N; i++){
		if(cows[i].first <= curT){
			maxT = max(cows[i].second, maxT);
			if(maxT >= T)	break;
		}
		else if(cows[i].first > maxT+1){
			break;
		}
		else{
			count++;
			curT = maxT+1;
			maxT = max(cows[i].second, maxT);
		}
	}
	if(maxT < T)  printf("-1\n");
	else printf("%d\n", count);
	return 0;
}