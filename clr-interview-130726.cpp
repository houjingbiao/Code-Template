//一个小岛，表示为一个N×N的方格，从(0,0)到(N-1, N-1)，一个人站在位置(x,y)，可以上下左右走，一步一格子，选择上下左右的可能性是一样的。
//当他走出小岛，就意味着死亡。假设他要走n步，请问死亡的概率有多大？请写出代码。

#define NMAX 20

int diff[][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
float getDeathProb(int x, int y, int w, int h, int n){
	float p[10][NMAX][NMAX];
	
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			if(i == 0 || i == w-1){
				if(j == 0 || j == w-1)  p[0][i][j]=0.5;
				else p[0][i][j]=0.25;
			}
			else p[0][i][j] = 0.0;
		}
	}
	
	for(int step = 1; step < n; step++){
		for(int i = 0; i < h; i++){
			for(int j = 0; j < w; j++){
				p[step][i][j] = 0.0;
				for(int k = 0; k < 4; k++){
					int co_x = i+diff[k][0];
					int co_y = j+diff[k][1];
					p[step][i][j] += (co_x<0 || co_y<0 || co_x>=h || co_y>w)? 0.0f : p[step-1][co_x][co_y];
				}
				p[step][i][j] = p[step][i][j]*0.25;
			}
		}
	}
	return p[n-1][x][y];
}