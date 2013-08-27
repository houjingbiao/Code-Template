//1154 ��������
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
	cin >> N;
	vector<long long> pearl;
	for(int i = 0; i < N; i++){
		long long x;//hjb: define x
		cin >> x;
		pearl.push_back(x);
	}
	pearl.insert(pearl.end(), pearl.begin(), pearl.end());
	pearl.insert(pearl.end(), pearl.begin(), pearl.end());
	vector<vector<long long> > dp(2*N, vector<long long>(2*N, 0));
	for(int i = 0; i < 2*N - 2; i++)
		dp[i][i+1] = pearl[i]*pearl[i+1]*pearl[i+2];
	for(int len = 3; len <= N; len++){
		for(int i = 0; i < 2*N-len; i++){
			int j = i + len - 1;
			for(int k = i; k < j; k++)//hjb: warning the bound
				dp[i][j] = max(dp[i][j], pearl[i]*pearl[k+1]*pearl[j+1]+dp[i][k]+dp[k+1][j]);
		}
	}
	long long ret = 0;
	for(int i = 0; i < N; i++)//hjb: need find the largest
		ret = max(ret, dp[i][i+N-1]);
	cout << ret<<endl;
	return 0;
}


//1048 ʯ�ӹ鲢 
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
	int n;
	scanf("%d", &n);
	vector<int> arr;
	for(int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		arr.push_back(x);
	}
	vector<vector<int> > dp(n, vector<int>(n, 0x7FFFFFFF));//hjb: the initialized value, and the scope of maximum value
	vector<vector<int> > s(n, vector<int>(n, 0));
	for(int i = 0; i < n; i++){
		dp[i][i] = 0;
		s[i][i] = arr[i];
	}
	for(int len = 2; len <= n; len++){
		for(int i = 0; i <= n-len; i++){
			int j = i + len - 1;
			s[i][j] = s[i][i]+s[i+1][j];
			for(int k = i; k < j; k++){
				dp[i][j] = min(dp[i][j], dp[i][k]+dp[k+1][j]);
			}
			dp[i][j] += s[i][j];
		}
	}
	printf("%d", dp[0][n-1]);//hjb: colon
	return 0;
}


//1576 �߶θ��� 2
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
typedef struct seg{
	int a, b, c;
}segment;
bool compare(segment s1, segment s2){
	return s1.b < s2.b || s1.b == s2.b && s1.a < s2.a;
}
int main(){
	int n;
	scanf("%d", &n);
	vector<segment> segments;
	map<int, int> m;
	for(int i = 0; i < n; i++){
		segment seg;
		scanf("%d%d%d", &seg.a, &seg.b, &seg.c);
		segments.push_back(seg);
		m[seg.a]++;
		m[seg.b]++;
	}
	vector<int> points;
	map<int, int>::iterator ite = m.begin();
	for(; ite != m.end(); ite++){
		points.push_back(ite->first);
	}
	sort(points.begin(), points.end());
	m.clear();
	for(int i = 0; i < points.size(); i++){
		m[points[i]] = i;
	}

	for(int i = 0; i < segments.size(); i++){
		segments[i].a = m[segments[i].a];
		segments[i].b = m[segments[i].b];
	}
	sort(segments.begin(), segments.end(), compare);
	vector<int> dp(points.size(), -1);
	
	//dp
	for(int i = 0; i < segments[0].b; i++)
		dp[i] = 0;
	int ret = dp[0];
	int max_i = 0;
	dp[segments[0].b] = segments[0].c;
	for(int i = 1; i < segments.size(); i++){
		if(segments[i].a < segments[0].b)
			dp[segments[i].b] = max(dp[segments[i].b], segments[i].c);
		else{
			if(max_i < segments[i].a){
				for(int j = max_i; j <= segments[i].a; j++){
					if(ret < dp[j])
						ret = dp[j];
					else
						dp[j] = ret;
				}
				max_i = segments[i].a;
			}
			dp[segments[i].b] = max(dp[segments[i].b], dp[segments[i].a] + segments[i].c);
		}
	}
	
	for(int i = max_i; i < points.size(); i++)
		ret = max(ret, dp[i]);
	printf("%d\n", ret);
	return 0;
}

//1576 ��ϸ�����������
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
	vector<int> arr;
	for(int i = 0; i<N; i++){
		int x;
		scanf("%d", &x);
		arr.push_back(x);
	}
	vector<int> dp(N, 1);
	for(int i = 0; i < arr.size(); i++){
		for(int j = 0; j < i; j++){
			if(arr[j] < arr[i])
				dp[i] = max(dp[j]+1, dp[i]);
		}
	}
	int ret = dp[0];
	for(int i = 1; i < dp.size(); i++){
		ret = max(ret, dp[i]);
	}
	printf("%d", ret);
	return 0;
}

//1044 ���ص��� 
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
	vector<int> bombs;
	int x;
	while(scanf("%d", &x) != EOF && x){
		bombs.push_back(x);
	}
	//long descendents
	vector<int> dp2(bombs.size(), 1);
	for(int i = 1; i < bombs.size(); i++){
		for(int j = 0; j < i; j++){
			if(bombs[j] > bombs[i]) dp2[i] = max(dp2[i], dp2[j]+1);
		}
	}
	int maxb = dp2[0];
	for(int i = 1; i < dp2.size(); i++){
		if(maxb < dp2[i]) maxb = dp2[i];
	}

	//longest ascendents
	vector<int> dp(bombs.size(), 1);
	for(int i = 1; i < bombs.size(); i++){
		for(int j = 0; j < i; j++){
			if(bombs[j] < bombs[i]) dp[i] = max(dp[i], dp[j]+1);
		}
	}
	int las = dp[0];
	for(int i = 1; i < dp.size(); i++){
		if(las < dp[i]) las = dp[i];
	}

	printf("%d\n", maxb);
	printf("%d\n", las);
	return 0;
}


//1068 �ڹ���
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
	int N, M;
	scanf("%d%d", &N, &M);
	vector<int> board;
	for(int i = 0; i < N; i++){
		int x;
		scanf("%d", &x);
		board.push_back(x);
	}
	vector<int> cards(4, 0);
	for(int i = 0; i < M; i++){
		int x;
		scanf("%d", &x);
		cards[x-1]++;
	}
	vector<vector<vector<vector<int> > > > dp(cards[0]+1, 
		vector<vector<vector<int> > >(cards[1]+1, 
		vector<vector<int> >(cards[2]+1, 
		vector<int>(cards[3]+1, 0))));
	dp[0][0][0][0] = board[0];
	for(int i1 = 0; i1 <= cards[0]; i1++){
		for(int i2 = 0; i2 <= cards[1]; i2++){
			for(int i3 = 0; i3 <= cards[2]; i3++){
				for(int i4 = 0; i4 <= cards[3]; i4++){
					int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
					int step = i1+i2*2+i3*3+i4*4;
					if(i1 != 0)
						s1 = dp[i1-1][i2][i3][i4];
					if(i2 != 0)
						s2 = dp[i1][i2-1][i3][i4];
					if(i3 != 0)
						s3 = dp[i1][i2][i3-1][i4];
					if(i4 != 0)
						s4 = dp[i1][i2][i3][i4-1];
					dp[i1][i2][i3][i4] = max(s1, s2);
					dp[i1][i2][i3][i4] = max(s3, dp[i1][i2][i3][i4]);
					dp[i1][i2][i3][i4] = max(s4, dp[i1][i2][i3][i4]);
					dp[i1][i2][i3][i4] += board[step];
				}
			}
		}
	}
	printf("%d\n", dp[cards[0]][cards[1]][cards[2]][cards[3]]);
	return 0;
}

//1014 װ������ 
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
	int v, n;
	scanf("%d", &v);
	scanf("%d", &n);
	vector<vector<int> > dp(n+1, vector<int>(v+1, 0));
	for(int i = 0; i < dp[0].size(); i++){
		dp[n][i] = 0;
	}	
	vector<int> objects;
	for(int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		objects.push_back(x);
	}
	for(int i = n-1; i >= 0; i--){
		for(int j = 0; j < dp[0].size(); j++){
			if(j >= objects[i] && dp[i+1][j-objects[i]]+objects[i] <= v)
				dp[i][j] = max(dp[i+1][j], dp[i+1][j-objects[i]]+objects[i]);
			else dp[i][j] = dp[i+1][j];
		}
	}
	printf("%d\n", v-dp[0][v]);
	return 0;
}

//3115 �߾�����ϰ֮���� 
//3116 �߾�����ϰ֮�ӷ� 
//3116 �߾�����ϰ֮�˷� 
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
#define MAXN 1005
class unsignedHP;
class HP;

class unsignedHP{
public:
	friend ostream& operator << (ostream& cout, const unsignedHP& a);
	unsignedHP():len(1){
		memset(s, 0, MAXN*sizeof(int));
	}
	unsignedHP(const char* str):len(0){
		if(str == NULL){
			len = 0;
			return;
		}
		memset(s, 0, MAXN*sizeof(int));
		len = strlen(str);
		for(int i = 0; i < len; i++){
			s[i] = str[len - 1 - i] - '0';
		}
	}
	unsignedHP(const unsignedHP& b){
		len = b.len;
		for(int i = 0; i < len; i++)
			s[i] = b.s[i];
	}

	unsignedHP& operator = (const unsignedHP &b){
		len = b.len;
		memcpy(s, b.s, len*sizeof(int));
		return *this;
	}

	~unsignedHP(){
	}

	bool isZero() const {
		if(len == 0 || len == 1 && s[0] == 0)
			return true;
		return false;
	}

	bool operator <= (const unsignedHP &b){
		if(len == b.len){
			int i = len - 1;
			while(i >= 0 && s[i] == b.s[i]){
				i--;
			}
			if(i < 0) return true;
			else return s[i] <= b.s[i];
		}
		return len < b.len;
	}

	bool operator > (const unsignedHP &b){
		return !(*this <= b);
	}
	unsignedHP operator +(const unsignedHP &b){
		int i = 0; 
		int jie = 0;
		unsignedHP ret;
		int maxlen = len > b.len? len : b.len;
		for(; i < maxlen; i++){
			ret.s[i] = s[i] + jie;
			ret.s[i] += b.s[i];
			if(ret.s[i] >= 10){
				ret.s[i] -= 10;
				jie = 1;
			}
			else
				jie = 0;
		}
		if(jie){
			ret.s[i] = 1;
			ret.len = i+1;
		}
		else
			ret.len = i;
		return ret;
	}
	unsignedHP operator -(unsignedHP &b){
		int i = 0; 
		int jie = 0;
		unsignedHP ret;
		for(; i < len; i++){
			ret.s[i] = s[i] - jie;
			ret.s[i] -= b.s[i];
			if(ret.s[i] < 0){
				ret.s[i] += 10;
				jie = 1;
			}
			else
				jie = 0;
		}
		i = len - 1;
		while(i >= 0 && ret.s[i] == 0)
			i--;
		ret.len = i+1;
		return ret;
	}
	unsignedHP operator*(const unsignedHP &b){
		unsignedHP c;
		int j = 0;
		for(int i = 0; i < len; i++){
			unsignedHP c1;
			int carry = 0;//hjb: the scope of every variable
			for(j = 0; j < b.len; j++){
				int t1 = s[i]*b.s[j] + carry;
				c1.s[i+j] = t1%10;
				carry = t1/10;
			}
			if(carry > 0){
				c1.len = i + j + 1;
				c1.s[i+j] = carry;
			}
			else{
				c1.len = i + j;
			}
			c = c+c1;
		}
		return c;
	}
	
public:
	int s[MAXN];
	int len;
};


class HP{
public:
	friend ostream& operator << (ostream& cout, const HP& a);
	HP():sign(1){
	}
	HP(const char* s){
		if(s[0] == '-')
			sign = -1;
		else
			sign = 1;
		if(s[0] == '-' || s[0] == '+')
			d = unsignedHP(s+1);
		else
			d = unsignedHP(s);
	}
	HP(const HP& b){
		sign = b.sign;
		d = b.d;
	}
	HP& operator = (const HP& b){
		sign = b.sign;
		d = b.d;
		return *this;
	}
	~HP(){
	}
	bool isZero() const{
		return d.isZero();
	}
	HP operator-(HP& b){
		HP c;
		if(sign == -1 && b.sign == 1){
			c.sign = -1;
			c.d = d + b.d;
		}
		else if(sign == -1 && b.sign == -1){
			if(d > b.d){
				c.sign = -1;
				c.d = d - b.d;
			}
			else{
				c.sign = 1;
				c.d = b.d - d;
			}
		}
		else if(sign == 1 && b.sign == -1){
			sign = 1;
			c.d = d + b.d;
		}
		else  if(sign == 1 && b.sign == 1){
			if(d > b.d){
				c.sign = 1;
				c.d = d - b.d;
			}
			else{
				c.sign = -1;
				c.d = b.d - d;
			}
		}
		if(c.isZero())
			c.sign = 1;
		return c;
	}
	HP operator+(HP &b){
		if(this->isZero()) return b;
		if(b.isZero()) return (*this);
		HP c;
		if(sign == -1 && b.sign == -1){
			c.sign = -1;
			c.d = d + b.d;
		}
		else if(sign == 1 && b.sign == 1){
			c.sign = 1;
			c.d = d + b.d;
		}
		else if(sign == 1 && b.sign == -1){
			if(b.d <= d){
				c.sign = 1;
				c.d = d - b.d;
			}
			else{
				c.sign = -1;
				c.d = b.d - d;
			}
		}
		else if(sign == -1 && b.sign == 1){
			if(d <= b.d){
				c.sign = 1;
				c.d = b.d - d;
			}
			else{
				c.sign = -1;
				c.d = d - b.d;
			}
		}
		return c;
	}
	HP operator*(const HP &b){
		if(isZero()) return *this;
		if(b.isZero()) return b;
		HP c;
		c.sign = sign*b.sign;
		c.d = d * b.d;
		return c;
	}
public:
	unsignedHP d;
	int sign;
};

ostream& operator << (ostream& cout, HP& a);
ostream& operator << (ostream& cout, unsignedHP& a);
ostream& operator << (ostream& cout, HP& a){
	if(a.sign == -1)
		cout << "-";
	cout << a.d;
	return cout;
}

ostream& operator << (ostream& cout, unsignedHP& a){
	if(a.isZero()){
		cout << 0;
	}
	else{
		for(int i = a.len-1; i >= 0; i--){
			cout << a.s[i];
		}
	}
	return cout;
}

int main(){
	char s1[MAXN];
	char s2[MAXN];
	memset(s1, 0, MAXN);
	memset(s2, 0, MAXN);
	while(scanf("%s %s",s1,s2)!= EOF){
		HP A = s1;
		HP B = s2;
		HP C = A * B;
		cout <<C << endl;
		memset(s1, 0, MAXN);
		memset(s2, 0, MAXN);
	}
	return 0;
}

//version from others
#include<stdio.h> 
#include<string.h> 
  
int compare(char *str_a,char *str_b) 
{ 
    int len_a, len_b; 
    len_a = strlen(str_a);          //�ֱ��ȡ������λ�����бȽ� 
    len_b = strlen(str_b); 
  
    if ( strcmp(str_a, str_b) == 0 )    //���رȽϽ�� 
        return 0; 
    if ( len_a > len_b ) 
        return 1; 
    else if( len_a == len_b ) 
        return strcmp(str_a, str_b); 
    else
        return -1; 
} 
  
int main() 
{ 
    int f, n; 
    int i, k, len_a, len_b; 
    char str_a[1000], str_b[1000]; 
    int num_a[1000] = {0};          //��ʼ���������飬��λȫ��0 
    int num_b[1000] = {0}; 
    int num_c[1000]; 
  
    while (scanf("%s%s",str_a,str_b)!= EOF) //�ɽ��ж������ 
    { 
        len_a = strlen(str_a);         //�ֱ�������������λ�� 
        len_b = strlen(str_b); 
  
        k = len_a > len_b? len_a:len_b;                    //�������λ�� 
        num_c[0] = 0; 
        f = 0; 
        n = compare(str_a,str_b); 
  
        for (i=0;i<len_a;i++)                   //�ߵ��洢 
            num_a[i] = str_a[len_a-i-1] - '0'; 
        for (i=0;i<len_b;i++) 
            num_b[i] = str_b[len_b-i-1] - '0'; 
  
        for (i=0;i<k;i++)         //��λ���м��� 
        { 
            if (n>=0) 
            { 
                if (num_a[i] >= num_b[i]) 
                    num_c[i] = num_a[i] - num_b[i]; 
                else
                { 
                    num_c[i] = num_a[i] - num_b[i] + 10; 
                    num_a[i+1]--; 
                } 
            } 
            else
            { 
                if ( num_b[i] >= num_a[i]) 
                    num_c[i] = num_b[i] - num_a[i]; 
                else
                { 
                    num_c[i] = num_b[i] - num_a[i] + 10; 
                    num_b[i+1]--; 
                } 
            } 
  
        } 
  
        if (n<0)            //��Ҫ���ӡ 
            printf("-"); 
        for (i=k-1; i>=0; i--) 
        { 
            if (num_c[i]) 
                f = 1; 
            if (f || i == 0 ) 
                printf("%d",num_c[i]); 
        } 
        printf("\n"); 
        for (i=0;i<k;i++)               //��0. ������һ�β��� 
        { 
            num_a[i] = 0; 
            num_b[i] = 0; 
        } 
    } 
  
    return 0; 
  
}

//1214 �߶θ���
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

//1098 ����ֽ��
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


//3145 ��ŵ����Ϸ 
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

//3143 ������������� 
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

//1012 ���Լ������С����������
#include <stdio.h>
int gcd(int m, int n){
	while(m%n){
		int a = m%n;
		m = n;
		n = a;
	}
	return n;
}

int gcd_rec(int m, int n){
	if(m%n) return gcd_rec(n, m%n);
	else return n;
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
		//if(x%i == 0 && gcd(i, x/i) == 1)
		if(x%i == 0 && gcd_rec(i, x/i) == 1)
			count++;
	}
	printf("%d", count);
	return 0;
}


//1474 ʮ����תm���� 
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


//1079 �ؼ�
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

//3038 3n+1���� 
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
		printf("%d\n",getStepsNumber(n)); //hjb��recheck the outline of programm when finish it
	}
	return 0;
}

//1842 �ݹ��һ�� 
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

//1501 ����������Ⱥ͸߶�
//hjb��make sure to understand the problem and concept fully
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

//1160 ���ξ���
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


//1083 Cantor�� 
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



//version 1: iteration
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


//1978 Fibonacci���� 3 
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

// 1011 ���ļ��� 
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

//1076 ���� 
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


//1075 ����������� 
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


//2235 ��Ʊ���� 
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

//1206 ������λС�� 
#include <stdio.h>
int main(){
	double f;
	scanf("%lf", &f); //how to input double precised number
	printf("%.2lf", f);
	return 0;
}

//1205 ���ʷ�ת
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

//1204 Ѱ���Ӵ�λ�� 
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

//1203 �жϸ������Ƿ���� 
#include <stdio.h>
int main(){
	float f1, f2;
	scanf("%f %f", &f1, &f2);
	if(f1 - f2 < 1e-8 && f1 - f2 > -1e-8) //also ok for: if(f1 - f2 < 1e-8 && f2 - f1 < 1e-8)
		printf("yes");
	else printf("no");
	return 0;
}

//1202 ��� 
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

// 1201 ��С��������� 
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

// 1475 m����תʮ����
#include <stdio.h>
#include <string.h>
int main(){
	char s[100];
	memset(s, 100, 0);
	int base;
	if(scanf("%s%d", &s, &base)){
		long num = 0;
		int len = strlen(s);
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
		printf("%ld", num);
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