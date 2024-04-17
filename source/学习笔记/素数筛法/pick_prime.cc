#include <bits/stdc++.h>
using namespace std;

vector<int> pick_primers(int n)
{
	vector<int> primers;
	vector<bool> not_primer(n+1);
	for(int i = 2; i <= n; i++)
	{
		if(!not_primer[i])
			primers.push_back(i);
		for(int pri : primers)
		{
			if(i * pri > n)
				break;
			not_primer[i * pri] = true;
			if(i % pri == 0)
			{
				// i 之前被pri筛选过了
				break;
			}
		}
	}
	return primers;
}

int main()
{
	auto primers = pick_primers(200);
	stringstream ss;
	for(auto p : primers)
		ss << p << ",";
	ss << endl;
	cout << ss.str();
	return 0;
}
