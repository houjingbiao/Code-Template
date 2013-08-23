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
int main(){
	return 0;
}

//删数问题，给定一个高精度的正整数N（不超过240位），去掉任意S个数字之后剩下的数字按照原左右次序组成一个新的正整数。编程对给定的N和S，寻找一种方案使得剩下的数字组成的新数最小
#include <stdio.h>
int main(){
	
}

//POJ 3040: Allowance
#include <stdio.h>
#include <algorithm>
typedef struct denomation{
	int val;
	int count;
}coin;
bool compare(coin c1, coin c2){
	return c1.val < c2.val;
}
int main(){
	int N, C;
	scanf("%d %d", &N, &C);
	coin* coins = new coin[N];
	int sum = 0;
	for(int i = 0; i < N; i++){
		scanf("%d %d", &coins[i].val, &coins[i].count);
		sum += coins[i].val*coins[i].count;
	}
	sort(coins, coins+N, compare);
	int count = 1;
	sum = sum < 1000000? sum:1000000;
	for(int i = sum; i >= C; i++){
		
	}
	if(coins[i] == 1)
	
	return 0;
}


//POJ 3262: Protecting the Flowers
//version 2:
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
#include <utility>
using namespace std;
bool compare(pair<int, int> p1, pair<int, int> p2){
	return !(p1.second*p2.first < p2.second*p1.first);
}
int main(){
	//freopen("in.txt", "r", stdin);
	int N;
	scanf("%d", &N);
	vector<pair<int, int>> cows(100005, pair<int, int>(0, 0));
	int sum = 0;
	for(int i=0; i<N; i++){
		scanf("%d %d", &cows[i].first, &cows[i].second);
		//cows[i].first <<= 1;
		sum += cows[i].second;
	}
	sort(cows.begin(), cows.begin()+N, compare);
	unsigned long long ans = 0;
	for(int i = 0; i < N; i++){
		sum -= cows[i].second;
		ans += sum*cows[i].first*2;
	}
	printf("%llu\n", ans);//hjb: the scope of the result
	return 0;
}

//version 1
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
#include <utility>
using namespace std;
int main(){
	freopen("in.txt", "r", stdin);
	int N;
	scanf("%d", &N);
	vector<pair<int, int>> cows(100005, pair<int, int>(0, 0));
	int sum = 0;
	for(int i=0; i<N; i++){
		scanf("%d %d", &cows[i].first, &cows[i].second);
		cows[i].first <<= 1;
		sum += cows[i].second;
	}
	int ans = 0;
	while(N > 0){
		int minCost = (sum - cows[0].second)*cows[0].first;
		int minIdx = 0;
		for(int i = 1; i < N; i++){
			int cost = (sum - cows[i].second)*cows[i].first;
			if(cost < minCost){
				minCost = cost;
				minIdx = i;
			}
		}
		ans += minCost;
		sum -= cows[minIdx].second;
		cows.erase(cows.begin()+minIdx);
		N--;
	}
	printf("%d", ans);
	return 0;
}


//POJ 1862: Stripies
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
int main(){
	int N;
	scanf("%d", &N);
	vector<double> vec;
	for(int i = 0; i < N; i++){
		int strip;
		scanf("%d", &strip);
		vec.push_back((double)strip);
	}
	sort(vec.begin(), vec.end());
	while(vec.size()>1){
		double newstrip = 2*sqrt(vec[vec.size()-2]*vec[vec.size()-1]);
		vec.erase(vec.begin()+vec.size()-1);
		vec.erase(vec.begin()+vec.size()-1);
		vec.push_back(newstrip);
	}
	printf("%.3lf", vec[0]);//hjb: format for the preciseness
	return 0;
}


//POJ 1017: Packets
//a more readable version
#include <stdio.h>
#include <string.h>
int main(){
	//freopen("out.txt", "w", stdout);
	int remain[7];
	int p[7];
	memset(p, 0, 7*sizeof(int));
	//freopen("in.txt", "r", stdin);
	while(scanf("%d %d %d %d %d %d", &p[1], &p[2], &p[3], &p[4], &p[5], &p[6])
		&& (p[6] || p[1] || p[2] || p[3] || p[4] || p[5])){
		memset(remain, 0, 7*sizeof(int));
		int ans = p[6]; //6*6
		
		ans += p[5]; //5*5
		remain[1] = 11*p[5];
		
		ans += p[4]; //4*4
		remain[2] = 5*p[4];
		
		ans += (p[3]+3)/4; //3*3
		int rem = p[3]%4;
		if(rem == 1){
			remain[2] += 5;
			remain[1] += 7;
		}
		else if(rem == 2){
			remain[2] += 3;
			remain[1] += 6;
		}
		else if(rem == 3){
			remain[2] += 1;
			remain[1] += 5;
		}
		
		if(p[2] < remain[2]){//hjb: missing parenthesis
			remain[1] += (remain[2] - p[2])*4;
		}
		else{
			ans += (p[2] - remain[2] + 8)/9;
			int rem2 = (p[2] - remain[2])%9;
			if(rem2 != 0)
				remain[1] += (9 - rem2)*4;
		}
		ans += p[1]-remain[1]>0 ? (p[1]-remain[1]+35)/36:0; //1*1
		printf("%d\n", ans);
	}
	return 0;
}

//my version
#include <stdio.h>
#include <string.h>
int main(){
	int p[7];
	memset(p, 0, 7*sizeof(int));
	//freopen("in.txt", "r", stdin);
	while(scanf("%d %d %d %d %d %d", &p[1], &p[2], &p[3], &p[4], &p[5], &p[6])
		&& (p[6] || p[1] || p[2] || p[3] || p[4] || p[5])){
		int ans = p[6]; //6*6
		
		ans += p[5]; //5*5
		p[1] = (p[1] > 11*p[5]) ? p[1] - 11*p[5] : 0;
		
		ans += p[4]; //4*4
		int b2 = p[2];
		p[2] = (p[2] > 5*p[4]) ? p[2] - 5*p[4] : 0;
		if(p[2] == 0){
			int remain = 20*p[4] - b2*4;
			p[1] = p[1] - remain > 0 ? p[1] - remain : 0;
		}
		
		ans += (p[3]+3)/4; //3*3
		int rem = p[3]%4;
		if(rem != 0){
			rem = 4 - rem;
		}
		b2 = p[2];
		p[2] = p[2] > (rem*3+rem-1)/2? p[2] - (rem*3+rem-1)/2:0;
		int b1 = rem*9 - (b2 - p[2])*4;
		p[1] = p[1] > b1 ? p[1] - b1 : 0;
		
		ans += (p[2]+8)/9; //2*2
		int rem2 = p[2]%9;
		if(rem2 != 0){
			rem2 = (9 - rem2)*4;
			p[1] = rem2 > p[1]? 0 : p[1] - rem2;
		}		
		
		ans += (p[1]+35)/36; //1*1
		printf("%d\n", ans);
	}
	return 0;
}

//POJ 2393: Yogurt factory
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