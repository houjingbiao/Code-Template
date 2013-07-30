#define nMax 100
float getWater(float C, float L, int n)//C: capacity of each cup, L: the amount of water, n: the index of the cup whose water we want
{
	float W[nMax];
	memset(W, 0, sizeof(int)*nMax);

	if(n == 1)  return L-C > 0 ? C : L;
	W[1] = (L-C)/2.0;
	int line = 1;
	int last_line_begin = 1;
	int curr_line_begin = 1;
	while(1){
		last_line_begin = curr_line_begin;
		curr_line_begin = curr_line_begin + line;
		
		W[curr_line_begin] = W[last_line_begin];
		if(curr_line_begin == n) return W[curr_line_begin]>C? C : W[curr_line_begin];
		W[curr_line_begin] = W[curr_line_begin] > C? (W[curr_line_begin] - C)/2.0:0.0;
		int i = 1;
		line++;
		while(i < line-1)
		{
			W[curr_line_begin+i] = W[last_line_begin+i] + W[last_line_begin+i-1];
			if(curr_line_begin + i == n) return W[curr_line_begin+i]>C? C : W[curr_line_begin+i];
			W[curr_line_begin + i] = W[curr_line_begin + i] > C? (W[curr_line_begin + i] - C)/2.0:0.0;
			i++;
		}
		if(line - 1 != 0){
			W[curr_line_begin+i] = W[last_line_begin+i-1];
			if(curr_line_begin + i == n) return W[curr_line_begin+i]>C? C : W[curr_line_begin+i];
			W[curr_line_begin + i] = W[curr_line_begin + i] > C? (W[curr_line_begin + i] - C)/2.0:0.0;
		}
	}
}