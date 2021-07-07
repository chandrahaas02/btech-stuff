#include <iostream>
#include <sys/time.h>
#include <time.h>
#include <fstream>

using namespace std;

int **arr;

void graph_generator(int n_v)
{
    arr = new int *[n_v];
    for (int i = 0; i < n_v; i++)
        arr[i] = new int[n_v];
    srand(time(0));
    for (int i = 0; i < n_v; i++)
    {
        arr[i][i] = -1;
        for (int j = 0; j < i; j++)
        {
            int k = rand() % 1000;
            if (k > 500)
                arr[i][j] = 1;
            else
                arr[i][j] = 0;
        }
    }
    for (int i = 0; i < n_v; i++)
    {
        for (int j = i + 1; j < n_v; j++)
            arr[i][j] = arr[j][i];
    }
}

int main()
{
    int v, t;
    ofstream out_file("input_params.txt");
    cout << "number of vertices" << endl;
    cin >> v;
    cout << "number of Threads" << endl;
    cin >> t;
    out_file << t<<"\t";
    out_file << v <<endl;
    graph_generator(v);
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
            out_file << arr[i][j]<<"\t";
        out_file << endl;
    }
    out_file.close();
}
