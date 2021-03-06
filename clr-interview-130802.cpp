// 可怜的小老鼠：有11瓶酒，只有一瓶有毒。喝酒之后，三天会死，只有三天时间。请问至少需要多少只老鼠，
// 可以找出9瓶没有毒的酒。


// 假设用m只老鼠，n瓶酒，m<n, 且其中只有一瓶酒有毒，一次至少能鉴别出的多少瓶没毒的酒？

证明：容易知道，m只老鼠，可以将n瓶酒分为2^m个分组（这是一个划分），假设第i个分组有n(i)瓶酒, i = 0, 1, 2, ... ,(2^m-1)。一次鉴别后，有且只有一组中含有毒酒。
所以，假设第j组含有毒酒，此时我们得到的没毒的就的瓶数就是n - n(j)。这样问题就可以转化为最优化问题，就是：

max(min (n - n(j))) j = 0, 1, 2, ... ,(2^m-1)
s.t. n(0)+n(1)+...+n(2^m-1) = n；
n(j) >= 0； j = 0, 1, 2, ... ,(2^m-1)

目标函数可以转化为max( n - max( n(j) )) = n - min( max ( n(j) ))  j = 0, 1, 2, ... ,(2^m-1)

最终优化问题变味：min( max ( n(j) ))  j = 0, 1, 2, ... ,(2^m-1)
s.t. n(0)+n(1)+...+n(2^m-1) = n。
n(j) >= 0

求解可以得到：min( max ( n(j) )) = [n/m]+1

故：
对n = 11，
当m = 1, 一次至少能鉴别n - min( max ( n(j) )) = 11 - ([11/2]+1) = 5;
当m = 2, 一次至少能鉴别n - min( max ( n(j) )) = 11 - ([11/4]+1) = 8;
当m = 3, 一次至少能鉴别n - min( max ( n(j) )) = 11 - ([11/8]+1) = 9;
当m = 4, 一次至少能鉴别n - min( max ( n(j) )) = 11 - ([11/16]+1) = 10;



进一步扩展当含有k瓶毒酒的时候，
求解可以得到：min( max ( n(j) )) = ([n/m]+1)*k
