#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// blocking function
static std::string getAnswer()
{    
    std::string answer;
    std::cin >> answer;
    return answer;
}

int main()
{

    std::chrono::seconds timeout(5);
    std::cout << "Do you even lift?" << std::endl << std::flush;
    std::string answer = "maybe"; //default to maybe
    
    std::future<std::string> future = std::async(getAnswer);

    if (future.wait_for(timeout) == std::future_status::ready)
        answer = future.get();

    std::cout << "the answer was: " << answer << std::endl;
    exit(0);
}