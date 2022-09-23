#include <iostream>
#include <fmt/format.h>

int main() {
    const char* s = "Kappa";
    std::cout << fmt::format("Hello, {}!", "Mom!") << std::endl;
    std::cout << fmt::format("I don't this is useable at all! {}", s) << std::endl;
    return 0;
}
