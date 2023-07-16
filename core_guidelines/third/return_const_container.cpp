#include <iostream>

class Container
{
public:
    Container() { }
    ~Container() { }
    void begin() {
        std::cout << "Non-const begin" << std::endl;
    }
    void begin() const {
        std::cout << "const begin" << std::endl;
    }
};

Container c;
const Container getter()
{
    return c;
}

int main()
{
    getter().begin();
    return 0;
}
