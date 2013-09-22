�Ǹ������Ƽ�����Ŀ������д��java����ģ����ֶ��Ǹ��˽�̫���ˣ�����ֻ������������˼·�ˣ�

1.��һ��mapreduce��
	map����ÿ��<fromId, toId>, ת��Ϊ���
			<fromId, "1"��toId�� "-1"��null> 
			<toId,   "1"��null "-1"��fromId>
			����"1"���Ϊkey����ע�ģ�"-1"���Ϊ��עkey��
	reduce���ϲ�key��ͬ�ģ��õ�<key, list1, list2>��list1�����б�key��ע�ģ�list2�����й�עkey��
2.�ڶ���mapreduce
	map����ÿ��<key, list1, list2>, ת��Ϊ��
			for each1 in list1:
				output: <key, list1, null> //list1�����б�key��ע�ģ�null�ǿ���key����ע���˹�ע�ģ���2�ȹ�עĿ��
				for each2 in list2:
					output: <each2, null, each1> //null�����б�each1��ע�ģ�each2�ǿ���each1����ע���˹�ע�ģ���2�ȹ�עĿ��
	reduce1���ϲ�key��ͬ�ģ��õ�<key, list1, list3>��list1������key��ע��list3�ǿ���list1����ע���˹�ע�ģ���2�ȹ�עĿ��
	reduce2����ÿ��<key, list1, list3>��ȥ��list2�а�����list1�е�id���õ�newlist3�����<key, newlist3>



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
          
        job.setJarByClass(MyWordCount.class); //��������jar�е�class����  
          
        job.setMapperClass(WordCountMapper.class);//����mapreduce�е�mapper reducer combiner��  
        job.setReducerClass(WordCountReducer.class);  
                job.setCombinerClass(WordCountReducer.class);   
          
        job.setOutputKeyClass(Text.class); //������������ֵ������  
                job.setOutputValueClass(IntWritable.class);  
          
        FileInputFormat.addInputPath(job,new Path(args[0]));//����mapreduce��������ļ�·��  
        FileOutputFormat.setOutputPath(job,new Path(args[1]));  
          
        System.exit(job.waitForCompletion(true) ? 0:1);  
    }  
      
}  