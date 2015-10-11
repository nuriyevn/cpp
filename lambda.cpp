#include <algorithm>
#include <vector>

namespace {
	struct f{
		void operator()(int) {
			
		}
	};
}


void func(std::vector<int>& v)
{
	f f;
	std::for_each(v.begin(), v.end(), f);

}
