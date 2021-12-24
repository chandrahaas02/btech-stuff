#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<time.h>

int n,p,part=0;
FILE*fclo;
void merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 
	int L[n1], R[n2]; 

	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2) 
	{ 
		if (L[i] <= R[j]) 
		{ 
			arr[k] = L[i]; 
			i++; 
		} 
		else
		{ 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	/* Copy the remaining elements of L[], if there 
	are any */
	while (i < n1) 
	{ 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 

	/* Copy the remaining elements of R[], if there 
	are any */
	while (j < n2) 
	{ 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

/* l is for left index and r is right index of the 
sub-array of arr to be sorted */
void mergeSort(int a[],int l, int r) 
{ 
	if (l < r) 
	{ 
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l+(r-l)/2; 

		// Sort first and second halves 
		mergeSort(a,l,m); 
		mergeSort(a,m+1,r); 

		merge(a, l, m, r); 
	} 
} 

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		fprintf(fclo,"%d ", A[i]); 
	fprintf(fclo,"\n"); 
}

int power(int n)
{
	int p=1;
	for(int i=0;i<n;i++)
	{
		p=p*2;
	}
	return p;
}

void* merge_sort(void* arr) 
{ 
	int*a=(int*)arr;
    // which part out of 4 parts 
    int thread_part = part++; 
  
    // calculating low and high 
    int low = thread_part * (n/p); 
    int high = (thread_part + 1) * (n/p) - 1; 
  
    // evaluating mid point 
    int mid = low + (high - low) / 2; 
    if (low < high) { 
        mergeSort(a,low, mid); 
        mergeSort(a,mid + 1, high); 
        merge(a,low, mid, high); 
    } 
} 

int main() 
{ 
	FILE*fptr;
	fptr=fopen("/home/chandrahaas/input.txt","r+");
	fclo=fopen("output.txt","w");
	fscanf(fptr,"%d,%d",&n,&p);
	n=power(n);
	p=power(p);
	int a[n];
	clock_t t1,t2;
	srand(time(0));
	pthread_t threads[p];
	for(int i=0;i<n;i++)
	{
		a[i]=rand();
	}
	printArray(a,n);
	t1=clock();
	for(int i=0;i<p;i++)
	{
		pthread_create(&threads[i],NULL,merge_sort,(void*)a);
	}
	for (int i = 0; i < p; i++)
	{
        pthread_join(threads[i], NULL); 
	}
    // merging the final all parts
	for(int i=1;i<p;i++)
	{
		merge(a,0,((i*n/p)-1),((i+1)*n/p)-1);
	}
    t2 = clock(); 
	printArray(a,n);
	fprintf(fclo,"\n time taken :%ld microseconds",t2-t1);
	fclose(fptr);
	fclose(fclo);
} 
