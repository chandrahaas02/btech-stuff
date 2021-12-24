#include <iostream>
#include <chrono>
#include <atomic>
#include <fstream>
#include <unistd.h>
#include <bits/stdc++.h> 
#include <sys/types.h>
#include<semaphore.h>
#include<thread>

using namespace std;

int n,x;
float l,r,t;

int waitingtime=0;
int waiting=0;
int eating=0;
bool must_wait=false;

sem_t Mutex;
sem_t block;

string get_Sys_time()
{
    using namespace std::chrono;

    // get current time
    auto now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;

    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

float exp_rand(float n)
{
    float z=(float)rand()/RAND_MAX;
    float t= -log(1-z)/n;
    return min((int)t,10);
}

void hotel(int num,string a[])
{

    //entry section
    a[3*num] =get_Sys_time();
    chrono::high_resolution_clock::time_point k1 = chrono::high_resolution_clock::now();
    sem_wait(&Mutex);
    if(must_wait == true || eating + 1 > x)
    {
		waiting++;
		must_wait = true;
		sem_post(&Mutex);
		sem_wait(&block);
	}
	else
    {
		eating++;
		must_wait = (waiting>0 && eating == x);
		sem_post(&Mutex);
	}

    //critical section 
    chrono::high_resolution_clock::time_point k2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> time_span = k2 - k1;
    waitingtime+=time_span.count();
    a[3*num+1] =get_Sys_time();
    int time= exp_rand(t)*1000;
    this_thread::sleep_for(chrono::milliseconds(time));
    
    // exit section
    sem_wait(&Mutex);
	eating--;
	if(eating == 0)
    {
        int j =min(x,waiting);
		waiting-=j;
		eating+=j;
		must_wait = (waiting>0 && eating==x);
		for(int i=0;i<j;i++)
        {
			sem_post(&block);
		}
	}
    sem_post(&Mutex);
    a[3*num+2] =get_Sys_time();
}

int main()
{
    sem_init(&Mutex, 0, 1);
	sem_init(&block, 0, 0);

    ifstream in_file("input.txt");
    ofstream out_file("output-log.txt");
    in_file>>n >>x >>l >>r >>t;

    thread customer[n];
    string a[3*n];
    int n_cust=0;
    while(n_cust<n)
    {
        float s_time =exp_rand(l);
        int num=r*(rand()%(x));
        int k =min(num,(n-n_cust));
        for(int i=0;i<k;i++)
        {
            customer[n_cust] = thread(hotel,n_cust,&a[0]);
            n_cust++;
        }
        usleep(s_time);
    }
    for(int i=0;i<n;i++)
    {
        customer[i].join();
    }
    for(int i=0;i<n;i++)
    {
        out_file<<"the customer"<<i+1<<"arrived at"<<a[3*i]<<endl;
        out_file<<"the customer"<<i+1<<"got seat at"<<a[3*i+1]<<endl;
        out_file<<"the customer"<<i+1<<"exited at"<<a[3*i+2]<<endl;
    }
    cout<<"the average waiting time"<<(float)waitingtime/(n*1000)<<"sec"<<endl;
}