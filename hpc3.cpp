#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <omp.h>
using namespace std;

int main()
{
    int n;
    cout << "Size: ";
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int sum = 0, mn = INT_MAX, mx = INT_MIN;

#pragma omp parallel for reduction(+ : sum) reduction(min : mn) reduction(max : mx)
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
    }

    cout << "Min: " << mn << "\nMax: " << mx;
    cout << "\nSum: " << sum << "\nAvg: " << (float)sum / n;
}