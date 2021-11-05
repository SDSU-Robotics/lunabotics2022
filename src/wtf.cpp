#include <iostream>
#include <thread>
#include <future>

int main()
{
    using namespace std::literals;

    auto f = std::async(std::launch::async,[] {
        auto s = ""s;
        if (std::cin >> s) return s;
    });

    while(f.wait_for(2s) != std::future_status::ready) {
        std::cout << "still waiting..." << std::endl;
    }

    std::cout << "input was: " << f.get() << std::endl;
}