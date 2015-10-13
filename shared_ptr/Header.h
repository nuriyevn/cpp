#include <memory>

using namespace std;

class B;
class A
{
public:
	A() {};
	~A()
	{
		int j = 0;
	}
	//shared_ptr<B> m_spToB;
	B* m_spToB;
};

class B
{
public:
	B(){};
	~B()
	{
		int k = 0;
	}
	A* m_spToA;
};

