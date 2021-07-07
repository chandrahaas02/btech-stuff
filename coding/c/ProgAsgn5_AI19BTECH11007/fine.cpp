#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <semaphore.h>
#include <thread>

using namespace std;

sem_t *mutex;

int n_th, n_v;
int *colouring;
int **arr;

void colour(int a[])
{
    int v;
    bool available[n_v];
    for (int i = 0; i < n_v; i++)
        available[i] = true;
    for (int i = 0; i < n_v; i++)
    {
        if (a[i] == 1)
        {
            if (colouring[i] != -1)
            {
                available[colouring[i]] = false;
            }
        }
        else if (a[i] == -1)
        {
            v = i;
        }
    }

    int p;
    for (p = 0; p < n_v; p++)
    {
        if (available[p] == true)
        {
            break;
        }
    }
    colouring[v] = p;
}

void colour_part(vector<int> a)
{
    int k = a.size();
    bool interior[k];
    for (int l = 0; l < k; l++)
    {
        interior[l] = false;
    }

    vector<int> outers[k];

    for (int l = 0; l < k; l++)
    {
        //n_t gives number of neighbours and
        //n_in gives number of neighbours in the partition
        int n_t = 0, n_in = 0;
        for (int i = 0; i < n_v; i++)
        {
            if (arr[a[l]][i] == 1)
            {
                n_t++;
                int temp = n_in;
                for (int m = 0; m < k; m++)
                {
                    if (a[m] == i)
                        n_in++;
                }
                if (temp == n_in)
                    outers[l].push_back(i);
            }
        }
        if (n_t == n_in)
            interior[l] = true;
    }
    for (int l = 0; l < k; l++)
    {
        if (interior[l] == true)
            colour(arr[a[l]]);
    }
    for (int l = 0; l < k; l++)
    {
        if (interior[l] != true)
        {
            int temp_arr[outers[l].size() + 1];
            int k = 0;
            vector<int>::iterator i;
            for (i = outers[l].begin(); i != outers[l].end(); ++i)
            {
                temp_arr[k] = *i;
                k++;
            }
            temp_arr[k] = a[l];
            int y = k;
            while (y > 0 && temp_arr[y] < temp_arr[y - 1])
            {
                int temp = temp_arr[y - 1];
                temp_arr[y - 1] = temp_arr[y];
                temp_arr[y] = temp;
                y--;
            }

            for (int y = 0; y < k; y++)
                sem_wait(&mutex[temp_arr[y]]);
            colour(arr[a[l]]);
            for (int y = 0; y < k; y++)
                sem_post(&mutex[temp_arr[y]]);
        }
    }
}

int main()
{
    ifstream in_file("input_params.txt");
    ofstream out_file ("fine_out.txt");
    in_file >> n_th >> n_v;
    arr = new int *[n_v];
    for (int i = 0; i < n_v; i++)
        arr[i] = new int[n_v];

    for (int i = 0; i < n_v; i++)
    {
        for (int j = 0; j < n_v; j++)
        {
            in_file >> arr[i][j];
        }
    }

    mutex = new sem_t[n_v];
    for (int i = 0; i < n_v; i++)
        sem_init(&mutex[i], 0, 1);

    chrono::high_resolution_clock::time_point k1 = chrono::high_resolution_clock::now();
    colouring = new int[n_v];
    colouring[0] = 0;
    for (int i = 1; i < n_v; i++)
        colouring[i] = -1;

    vector<int> V[n_th]; // Assiging avector to assign vertices to thread
    srand(time(0));
    for (int i = 0; i < n_v; i++)
    {
        V[rand() % n_th].push_back(i);
    }
    thread t[n_th];
    for (int i = 0; i < n_th; i++)
    {
        t[i] = thread(colour_part, V[i]);
    }
    for (int i = 0; i < n_th; i++)
        t[i].join();
    chrono::high_resolution_clock::time_point k2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::micro> time_span = k2 - k1;
    float time_taken = time_span.count();

    out_file << "fine Lock:\n";
    int max = colouring[0];
    for (int i = 0; i < n_v; i++)
    {
        out_file << "v" << i + 1 << "-" << colouring[i] << " ";
        if (max < colouring[i])
            max = colouring[i];
    }
    out_file << "\nNo. of colours used: " << max + 1 << endl;
    out_file << "Time taken by the algorithm using: " << time_taken / 1000 << endl;
    in_file.close();
    out_file.close();
    return 0;
}