//version 1: 
void rightMove(vector<int> &vec, int n)
{
	if(vec.size() == 0) return;
	n = n%vec.size();
	if(n == 0) return;
	
	reverse(vec.begin(), vec.begin()+vec.size() - n);
	reverse(vec.begin()+vec.size()-n, vec.end());
	reverse(vec.begin(), vec.end());
}

//version 2:
void rightMove2(vector<int> &vec, int n)
{
	if(vec.size() == 0) return;
	n = n%vec.size();
	if(n == 0) return;

	int a = vec.size();
	int b = n;
	int g = a%b;
	while(g != 0){
		a = b;
		b = g;
		g = a%b;
	}

	for(int i = 0; i < b; i++)
	{
		int tmp = vec[i];
		int x = i;
		do
		{
			int y = x-n>0? x-n : x-n+vec.size();
			vec[x] = vec[y];
			x = y;
		}while(x-n != i);
		vec[x] = tmp;
	}
}

//version 2.1: change rightMove into left move which avoid the judgement whether x-n < 0? comparing to the version 2
void rightMove(vector<int> &vec, int n)
{
	if(vec.size() == 0) return;
	n = n%vec.size();
	if(n == 0) return;

	int a = vec.size();
	int b = n;
	int g = a%b;
	while(g != 0){
		a = b;
		b = g;
		g = a%b;
	}
	n = vec.size()-n;
	for(int i = 0; i < b; i++)
	{
		int tmp = vec[i];
		int x = i;
		int y = (x+n)%vec.size();
		while(y!=i)
		{
			vec[x] = vec[y];
			y = (x+n)%vec.size();
		}
		vec[x] = tmp;
	}
}

//version 3: from hefeng cui, in this version another method is used to change right shift to left shift
int gcd(int a, int b){
	if(a < b)
		return gcd(b, a);
	while(b!=0)
	{
		int r = a%b;
		a = b;
		b = r;
	}
	return a;
}
void rightShift(vector<int> &vec, int k)
{
	if(vec.size()<=1) return;
	int n = vec.size();

	k = k%n;
	if(k == 0)
		return;
	int m = gcd(n,k);
	for(int i = m; i < n; i++)
	{
		int x=vec[i];
		int j, t = i;
		for(j = (i+k)%n; j!=i; j = (j+k)%n){
			vec[t] = vec[j];
			t = j;
		}
		vec[t] = x;
	}
}