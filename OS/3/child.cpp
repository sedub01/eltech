#include <iostream>

const int N = 10;

using std::cout;
int main(){
    cout << "CHILD PROCESS STARTS\n";
    cout << "I'm a child process\n";

    double x[N]{0};
    for (int i = 0; i < N; i++)
        x[i] = (0.5 + i) / N;

    cout << "CHILD PROCESS ENDS\n";
}