//calculate PI to the precision of 800 after the point

long a = 1000, b, c = 2000, d, e, f[2001], g;
int main()
{
	for(; b-c;) f[b++] = a/5; //a trick to implement counter
	for(; d==0, g=c*2; c-=14, printf("%.4d\n", e+d/a), e=d%a)
		for(b=c; d+=f[b]*a, f[b]=d%--g,d/=g--,--b;d*=b)
			;
	return 0;
}