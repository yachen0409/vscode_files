#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    int N,K;
    cin >> N >> K;
    vector<int> c(N);
    vector<int> p(N);
    for(int i=0;i<N;i++)
    {
        cin >> c[i] >> p[i];
    }
    double lower_bound = 0.0;
    double upper_bound = 1000000000.0;
    while(fabs(upper_bound-lower_bound) > 0.000001)
    {
    	double mid_score = (lower_bound+upper_bound)/2;
    	long long sum = 0;
    	for(int i=0;i<N;i++)
    	{
    		long long temp = (int)(c[i]/mid_score)-p[i];
    		if(temp<=0)
    			continue;
    		sum += temp;
		}
		if(K<=sum)
			lower_bound=mid_score;
		else
			upper_bound=mid_score;
	}
    
    cout << setprecision(10) << (lower_bound+upper_bound)/2;
    
    return 0;
}