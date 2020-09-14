#include <iostream>

using namespace std;
const int N = 40;
inline int sum(int *p, int n, int d[]){for(int i = 0; i < n; ++i){ *p = *p + d[i];}};
    
int main()
{
    int accum = 0;
    int data[N];
    for(int i = 0; i < N; ++i){
        data[i] = i;
    }
    
    sum(&accum, N, data);
    cout << "Accum is: \n" << accum;
    
    return 0;
}
