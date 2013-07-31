//问题：
/*有一座金字塔，从上到下，第一层有一个杯子、第二层有两个杯子，依次类推。对杯子进行编号，有如下的形状：
   1
 2   3
4   5   6

每个杯子的容量为C升，从塔顶倒下L升水，当1号杯子满了之后，会等量溢出到2号和3号杯子。当2号和3号满了，
2号溢出到4号和5号，3号溢出到5号和6号，注意5号接受来自两个杯子的水。依次类推。给定C和L，请问，第n杯里
有多少水。
*/
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




//version 2: from http://blog.csdn.net/liql2007/article/details/9639315
//pay attention to the use of hashmap, 
double getFlow(int C, int leveli, int index, unordered_map<int, double> &hashMap){  
    if(index < 0 || index > leveli)  
        return 0;  
    int n = (leveli + 1) * leveli / 2 + index;//总的索引   
    auto p = hashMap.find(n);  // auto variables 的使用
    if(p != hashMap.end())   
        return p->second;  
    double leftFlow = getFlow(C, leveli - 1, index -1, hashMap);  
    double rightFlow = getFlow(C, leveli - 1, index, hashMap);  
    return hashMap[n] = (leftFlow >= C ? (leftFlow - C) / 2 : 0)   
        + (rightFlow >= C ? (rightFlow - C) / 2 : 0);  
}  
  
int main() {  
    int L = 10;  
    int C = 5;   
    int n = 1;//n值从0开始，表示总的索引   
    int leveli = 0, sum = 0;  
    while(sum + (leveli + 1) < n + 1) //初始化所在层次：leveli   
        sum += leveli++ + 1;  
    int index = n - (leveli + 1) * leveli / 2; //计算所在行的索引   
    unordered_map<int, double> hashMap;  
    hashMap[0] = L;//初始化Map   
  
    double flow = getFlow(C, leveli, index, hashMap);  
    cout << (flow > C ? C : flow) << endl;  
}  
