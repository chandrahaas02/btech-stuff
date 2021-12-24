#include <iostream>
#include <chrono>
#include <atomic>
#include <fstream>
#include <unistd.h>
#include <bits/stdc++.h> 
#include <sys/types.h>
#include<thread>


using namespace std;

bool * wait;
atomic<int> lock_t; 

int n,k,l1,l2,wait_time=0;
int worst=0;

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


void testCS(int id)
{
    for(int i=0;i<k;i++)
    {
        float x=(float)rand()/RAND_MAX;
        int t1= (int)-log(1-x)/l1;
        int t2= (int)-log(1-x)/l2;

        //entry section
        auto req_time=get_Sys_time();
        chrono::high_resolution_clock::time_point k1 = chrono::high_resolution_clock::now();
        
        int a = 0, b = 1, key = 1;
		
		wait[id] = true;
		while(wait[id] && key == 1) 
        {
			key = lock_t;
			bool temp = lock_t.compare_exchange_strong(a, b);
			a = 0;
		}
        wait[id] = false;

        // critical section 
        auto entry_time=get_Sys_time();
        chrono::high_resolution_clock::time_point k2 = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> time_span = k2 - k1;
        if(time_span.count()>worst) worst=time_span.count();
        wait_time=wait_time+time_span.count();
        this_thread::sleep_for(chrono::milliseconds(t1));
        cout << i+1 << "th CS Request at" << req_time << "by thread" << id <<endl ;
        cout << i+1 << "th CS entry at" << entry_time << "by thread" << id <<endl ;
        auto exit_time = get_Sys_time();
        cout << i+1 << "th CS exit at" << exit_time << "by thread" << id <<endl ;


        // preparing to exit
        int next = (id+1) % n;
		while ((next != id) && !wait[next])
        {
             next = (next + 1) % n;
        }
		if (next == id) 
        {
            lock_t = 0;
        }
		else  wait[next] = false;

        // exited
        this_thread::sleep_for(chrono::milliseconds(t2));
    }


}


int main()
{
    ifstream in_file("inp-parms.txt");
    in_file>> n >>k >>l1 >>l2 ;

    thread t[n];

    wait = new bool[n];	
	for(int y = 0; y < n; y++) wait[y] = false;

    for(int i=0;i<n;i++)
    {
        t[i] = thread(testCS, i);
    }

    for(int i=0;i<n;i++)
    {
        t[i].join();
    }
    double avg= (double)wait_time/(n*k);

    cout<<"the average waiting time of a process is"<< avg<<endl;
    cout<<"the worst waiting time of a process is"<<worst<<endl;
}
