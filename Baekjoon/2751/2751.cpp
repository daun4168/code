#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    
    vector<int> v;
    int num, N;

    cin >> N;
    for(int i = 0;i<N;i++){
        cin >> num;
        v.push_back(num);
        push_heap(v.begin(), v.end());
    }
    
    std::sort_heap (v.begin(),v.end());

    for(int i = 0;i<N;i++){
        cout << v[i] << '\n';
    }

    return 0;
}
