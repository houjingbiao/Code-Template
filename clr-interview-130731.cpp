int getMaxArea(int* arr, int nrows, int ncols){
	int* lengths = new int[nrows*ncols];
	memset(lengths, 0, nrows*ncols*sizeof(int));
	int ret = 0;
	int area = 0;
	for(int i = 0; i < nrows; i++){//the first colomn
		if(arr[i*ncols] > 0){
			lengths[i*ncols] =  1;
			area++;
		}
		else{
			ret = max(ret, area);
			area = 0;
		}
	}
	ret = max(ret, area);
	area = 0;
	for(int j = 1; j < ncols; j++){//the first row
		if(arr[j] > 0){
			lengths[j] =  1;
			area++;
		}
		else{
			ret = max(ret, area);
			area = 0;
		}
	}
	ret = max(ret, area);
	
	for(int j = 1; j < ncols; j++){
		for(int i = 1; i < nrows; i++){
			if(arr[i*ncols+j] > 0){
				lengths[i*ncols+j] = lengths[i*ncols+j-1]+1;
				int ii = i;
				int minlen = lengths[i*ncols+j];
				while(ii>=0){
					if(arr[ii*ncols+j] > 0){
						minlen = min(minlen, lengths[ii*ncols+j]);
						area = minlen*(i-ii+1);
						ret = max(area, ret);
					}
					else break;
					ii--;
				}
			}
		}
	}
	return ret;
}