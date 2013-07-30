//n个色子，每个色子m面，每一面的值分别是1-m。你将n个色子同时抛，落地后将所有朝上面的数字加起来，记为sum。
//给定一个数字x，如果sum>x，则你赢。给定n，m，x，求你赢的概率。1<=n<=100，1<=m<=10，m<=x<n*m。关注微信账
//号“待字闺中”，第一时间了解今日面试题及其分析

#define nMax 105
#define mMax 15
#define mnMax nMax*mMax+1
float getProbability(int n, int m, int x){

	int counts[mnMax];
	int counts_tmp[mnMax];
	memset(counts, 0, mnMax*sizeof(int));

	for(int i=1; i<=m; i++) counts[i] = 1;
	for(int i=2; i<=n; i++){
		memset(counts_tmp, 0, mnMax*sizeof(int));

		for(int j=1; j<=m; j++){//for each element
			for(int k = m*(i-1); k >= i-1; k--)
				counts_tmp[k+j] += counts[k];
		}
		for(int j = 0; j < m*n+1; j++) counts[j] = counts_tmp[j];
	}

	int count = 0;
	for(int i = m*n; i > x; i--)
		count += counts[i];

	int total_count = m;
	for(int i = 1; i < n; i++)
		total_count *= m;

	return float(count)/float(total_count);
}