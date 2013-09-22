那个二度推荐的题目，本想写个java程序的，发现对那个了解太少了，所以只好用文字描述思路了：

1.第一趟mapreduce：
	map：对每个<fromId, toId>, 转化为两项：
			<fromId, "1"，toId， "-1"，null> 
			<toId,   "1"，null "-1"，fromId>
			其中"1"后的为key所关注的，"-1"后的为关注key的
	reduce：合并key相同的，得到<key, list1, list2>，list1是所有被key关注的，list2是所有关注key的
2.第二趟mapreduce
	map：对每个<key, list1, list2>, 转化为：
			for each1 in list1:
				output: <key, list1, null> //list1是所有被key关注的，null是可以key所关注的人关注的，即2度关注目标
				for each2 in list2:
					output: <each2, null, each1> //null是所有被each1关注的，each2是可以each1所关注的人关注的，即2度关注目标
	reduce1：合并key相同的，得到<key, list1, list3>，list1是所有key关注，list3是可以list1所关注的人关注的，即2度关注目标
	reduce2：对每个<key, list1, list3>，去除list2中包含在list1中的id，得到newlist3，输出<key, newlist3>



import java.io.IOException;  
import java.util.Iterator;  
import java.util.StringTokenizer;  
  
import org.apache.hadoop.conf.Configuration;  
import org.apache.hadoop.fs.Path;  
import org.apache.hadoop.io.IntWritable;  
import org.apache.hadoop.io.Text;  
import org.apache.hadoop.mapreduce.Job;  
import org.apache.hadoop.mapreduce.Mapper;  
import org.apache.hadoop.mapreduce.Reducer;  
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;  
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;  
import org.apache.hadoop.util.GenericOptionsParser;  
  
public class MyWordCount {  
  
    public static class Get1Follow extends Mapper<Object,Text,Text,IntWritable> {  
          
        private static final IntWritable one_degree =  new IntWritable(1);  
		private static final IntWritable minusone_degree =  new IntWritable(-1);
         
		private Text relation = new Text();
        private Text fromId = new Text();  
		private Text toId = new Text();
  
        protected void map(Object key, Text value, Context context)  
                throws IOException, InterruptedException {  
            String relations = value.toString();  
			StringTokenizer relationTok = new StringTokenizer(relations, "\n");
            while(relationTok.hasMoreTokens()) {
				relation.set(relationTok.nextToken());
				StringTokenizer idTok = new StringTokenizer(relation, "\n");
				fromId.set(idTok.nextToken());
				toId.set(idTok.nextToken());
				
                context.write(fromId, one_degree, toId, minusone_degree, null);
				context.write(toId, one_degree, null, minusone_degree, one_degree);
            }  
        }  
    }  
      
    public static class Bridge1andMinus1 extends Reducer<Text,IntWritable,Text,IntWritable> {  
  
        private Text onedegree = new Text();
        private Text minusOnedegree = new Text();  
          
        @Override  
        protected void reduce(Text key, Iterable<IntWritable> values,Context context)  
                throws IOException, InterruptedException {  
           int sum = 0;  
           Iterator<IntWritable> it = values.iterator();  
                while(it.hasNext()) {
					if(it.next().get() == -1){
						sum = 1;
						continue;
					}
					else if(it.next().get() == -1){
						sum = -1;
						continue;
					}
					if(sum == 1)
						onedegree.add(it.next().get())
					else
						minusOnedegree.add(it.next().get())
                }  
                totalNum.set(sum);  
                context.write(key,totalNum);   
        }  
    }  
      
    public static void main(String[] args) throws Exception{  
        Configuration conf = new Configuration();             
  
        Job job = new Job(conf,"MyWordCount");  
          
        job.setJarByClass(MyWordCount.class); //设置运行jar中的class名称  
          
        job.setMapperClass(WordCountMapper.class);//设置mapreduce中的mapper reducer combiner类  
        job.setReducerClass(WordCountReducer.class);  
                job.setCombinerClass(WordCountReducer.class);   
          
        job.setOutputKeyClass(Text.class); //设置输出结果键值对类型  
                job.setOutputValueClass(IntWritable.class);  
          
        FileInputFormat.addInputPath(job,new Path(args[0]));//设置mapreduce输入输出文件路径  
        FileOutputFormat.setOutputPath(job,new Path(args[1]));  
          
        System.exit(job.waitForCompletion(true) ? 0:1);  
    }  
      
}  