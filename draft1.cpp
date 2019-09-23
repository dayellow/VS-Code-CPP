#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <stack>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main()
{ 
	int *x=(int*)malloc(sizeof(int));
	int *y=(int*)malloc(sizeof(int));
	int a=1;
	*x=1;
	*y=2;
	int t=*x;
	*x=*y;
	*y=t;
	cout<<*x<<*y;
    system("pause");
    return 0;
}