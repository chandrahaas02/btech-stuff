#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <queue>
using namespace std;
#define MAXPROCESS 1024  // to intilize the array

int Min(int deadline[],int remaing[]);
void EDF(int max);

int process_num=0;
int pid[MAXPROCESS],processing_time[MAXPROCESS],period[MAXPROCESS],num_times[MAXPROCESS];

int main()
{
  int a;
  ifstream in_file ( "inp-params.txt");
  in_file>> a;
  process_num =a;
  for(int i=0;i<process_num;i++)
  {
      in_file>> a;
      pid[i]=a;
      in_file>> a;
      processing_time[i]=a;
      in_file>> a;
      period[i]=a;
      in_file>> a;
      num_times[i]=a;
  }
  int max_dead[process_num];
  for(int i=0;i<process_num;i++)
  {
      max_dead[i]=period[i]*num_times[i];
  }
  int max=*max_element(max_dead, max_dead + process_num);
  EDF(max);
  in_file.close();
}

int Min(int deadline[],int remaing[])
{
    int min_time = 1000 ; // assuming no process is greater than 1000 secs
    int min_num=-1;
    for(int i=0;i<process_num;i++)
    {
        if(remaing[i]>0 && remaing[i]<deadline[i])
        {
            if(deadline[i]<min_time)
            {
                min_time=deadline[i];
                min_num=i;
            }
        }
    }
    return min_num;
}

void EDF(int max)
{
    ofstream edf_file ( "EDF-log.txt");
    ofstream edf_stats ( "EDF-stats.txt");
    int remain[process_num],k[process_num],dead_line[process_num],waiting[process_num];
    int prev=-1,count=0;
    for(int i=0;i<process_num;i++)
    {
        remain[i]=processing_time[i];
        k[i]=0;
        dead_line[i]=period[i];
        waiting[i]=0;
    }
    // finding next process every second and decreasing the remain time of that process
    for(int i=0; i<max;i++)
    {
        for(int j=0;j<process_num;j++)
        {
            if(i%period[j]==0 && k[j]<=num_times[j])
            {
                if(remain[j]>0 && k[j]>0)
                {
                    count+=1;
                }
                remain[j]=processing_time[j];
                k[j]+=1;
                dead_line[j]=period[j];
            }
            if(k[j]>num_times[j])
            {
                remain[j]=0;
            }
        }
        int next  = Min(dead_line,remain);
        remain[next]-=1;
        for(int j=0;j<process_num;j++)
        {
            dead_line[j]-=1;
            if(j!=next && remain[j]!=0)
            {
                waiting[j]+=1;
            }
        }
        if(prev!=next)
        {
            if(remain[prev]==0 && pid[prev]!=0)
            {
                edf_file<<"Process"<<pid[prev]<<"completed excuting at time"<<i<<"\n";
            }
            if(pid[prev]!=0 && pid[next]!=0 && remain[prev]!=0)
            {
                edf_file<<"Process"<<pid[prev]<<"is preemepted by process"<<pid[next]<<"at time"<<i<<"\n";
            }
            if(next!=-1)
            {
                edf_file<<"Process"<<pid[next]<<"Started excuting at time"<<i<<"\n";
            }
            if(next==-1)
            {
                edf_file<<"cpu is idle from"<<i<<"\n";
            }
            prev=next;
        }
    }
    int sum1=0,sum2=0;
    sum1 = accumulate(waiting, waiting+process_num, sum1);
    sum2 = accumulate(num_times, num_times+process_num, sum2);
    float average =(float)sum1/(float)sum2;

    edf_stats<<"num of prcoess came into the system :"<<sum2<<"\n";
    edf_stats<<"num of process that sucessfully completed :"<<sum2-count<<"\n";
    edf_stats<<"num of process that missed deadline :" <<count<<"\n";
    edf_stats<<"The avrage waiting time :"<<average<<"\n";
    edf_file.close();
    edf_stats.close();
}