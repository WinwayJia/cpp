#include <iostream>
#include <string>
#include <hash_map>

using namespace std;
using namespace __gnu_cxx;

int main(int argc, char** argv)
{
	hash_map<int, string> loUser;

	loUser.insert(make_pair(1, "one"));

	for (auto iter : loUser)
	{
		cout << iter.first << " ==>> " << iter.second << endl;
	}

	return 0;
}
