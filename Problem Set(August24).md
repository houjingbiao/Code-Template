## 1. driver and busman ##
在公共汽车上，为了保证乘客的安全，司机和售票员应该协调工作：停车后才能开门，关车门后才能行车。用PV操作来实现他们之间的协调。
<pre>
semaphore s1 = 0;//是否允许driver启动汽车
semephore s2 = 0;//是否允许busman开门
driver(){
	while(true){
		P(s1);
			start the bus;
			running;
			stop the bus;//停车之后并不一定要V(s1)
		V(s2);
	}
}
busman(){
	while(true){
		close door;//循环的开始，反正是循环，从哪里开始呢？
		 	   //循环从close door开始的好处是信号量可以去任意的初值
		V(s1);
			sell tickets;
		P(s2);
			Open Door;
			passenger transfer;
	}
}
</pre>

## 2.（Google面试题） ##
有四个线程1、2、3、4。线程1的功能就是输出1，线程2的功能就是输出2，以此类推.........现在有四个文件ABCD。初始都为空。现要让四个文件呈如下格式：  
A：1 2 3 4 1 2....  
B：2 3 4 1 2 3....  
C：3 4 1 2 3 4....  
D：4 1 2 3 4 1....  
请设计程序。  
提示：使用16个信号量，是16次输出形成一个闭环。主线程打开一个环，然后开始在环内循环。
<pre>
semaphore s1 = 1;//for thread1
semaphore s2 = 0;//for thread2
semaphore s3 = 0;//for thread3
semaphore s4 = 0;//for thread4
fileID_1 = 0;
fileID_2 = 1;
fileID_3 = 2;
fileID_4 = 3;
thread_1(){
	P(s1)
	switch(fileID_1){
		case 0: write(A); break;
		case 1: write(B); break;
		case 2: write(C); break;
		case 3: write(D); break;
	}
	fileID = (fileID_1+1)%4;
	V(s2);
}
thread_2(){
	P(s2)
	switch(fileID_2){
		case 0: write(A); break;
		case 1: write(B); break;
		case 2: write(C); break;
		case 3: write(D); break;
	}
	fileID = (fileID_2+1)%4;
	V(s3);
}
thread_3(){
	P(s3)
	switch(fileID_3){
		case 0: write(A); break;
		case 1: write(B); break;
		case 2: write(C); break;
		case 3: write(D); break;
	}
	fileID = (fileID_3+1)%4;
	V(s4);
}
thread_4(){
	P(s1)
	switch(fileID_4){
		case 0: write(A); break;
		case 1: write(B); break;
		case 2: write(C); break;
		case 3: write(D); break;
	}
	fileID = (fileID_4+1)%4;
	V(s1);
}
</pre>


## 3. poj 3040： Allowance ##
地址：[http://poj.org/problem?id=3040](http://poj.org/problem?id=3040)

## 4. poj 3040： Stripies ##
地址：[http://poj.org/problem?id=1862](http://poj.org/problem?id=1862)

## 5. Protecting the Flower ##
地址：[http://poj.org/problem?id=3262](http://poj.org/problem?id=3262)