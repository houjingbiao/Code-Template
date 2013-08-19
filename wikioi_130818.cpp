//1214 Ïß¶Î¸²¸Ç
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