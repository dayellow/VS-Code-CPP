#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <sstream>

#include <string>
#include <vector>
#include <map>

#define maxt 100010
#define operate 100

typedef long long LL;

using namespace std;

map<string, vector<int> > road;

bool is_road(int x)
{
	int left1, left2, right1, right2;
	left1 = ((double)x) / sqrt(2.0);
	right1 = ((double)x+1) / sqrt(2.0);
	left2 = ((double)x) / (2.0 + sqrt(2.0));
	right2 = ((double)x+1) / (2.0 + sqrt(2.0));
	if ((right1 - left1)!=0 || (right2 - left2)!=0) return true;
	else return false;
}

int main(int argc, char * argv[])
{
	int city, year;
	cin >> city >> year;
	int value[maxt] = {0};
	for (int i = 0; i < city; ++i)
	{
		cin >> value[i + 1];
	}
	getchar();

	for (int i = 1; i <= year; ++i)
	{
		int t = 1;
		string s;
		getline(cin, s);
		stringstream ss(s);
		string info[operate];
		string l;
		while (ss >> l)
		{
			info[t++] = l;
		}
		if (info[1] == "1")
		{
			int n, m, l;
			string x;
			stringstream s1;
			s1<<info[2];
			s1 >> n;
			stringstream s2;
			s2<<info[3];
			s2 >> m;
			stringstream s3;
			s3<<info[4];
			s3 >> l;
			if (n > m) x = info[3] + info[2];
			x = info[2] + info[3];
			road[x].push_back(l);
		}
	if (info[1] == "2")
		{
			int m, n;
			stringstream s4;
			s4<<info[2];
			s4 >> m;
			stringstream s5;
			s5<<info[3];
			s5 >> n;
			value[m] += n;
		}
	if (info[1] == "3")
		{
			int e;
			int r=0;
			for (int i = 1; i <= city; ++i)
			{
				string x;
				stringstream s4;
				s4 << i;
				s4 >> x;
				stringstream s5;
				s5<<info[2];
				s5 >> e;
				if(e==i) continue;
				string p;
				if (e > i) p = x + info[2];
				else p = info[2] + x;
				if (!road.count(p)) continue;
				else
				{
					for (int j = 0; j < (int)road[p].size(); ++j)
					{
						if (is_road(road[p][j]))
						{
							r+=value[i];
						}

					}
				}
			}
			cout << r <<endl;
		}
	}


  return 0;
}