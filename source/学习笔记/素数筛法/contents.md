# 筛选素数

如何筛选2~N之间的素数？
线性筛法（或者欧拉筛法），时间复杂度O(n)

```C++
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

```
