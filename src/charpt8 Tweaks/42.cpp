#include <iostream>
#include <string>
#include <vector>
#include <chrono>

int main() {
    std::vector<std::string> vec1,vec2;

    // Test push_back
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        // vec2.push_back(std::to_string(i));
        vec2.push_back("FAN");

    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Push_back duration: " << elapsed_seconds.count() << " seconds\n";


    // Test emplace
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        // vec1.emplace_back(std::to_string(i));
        vec1.emplace_back("FAN");

    }
     end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Emplace duration: " << elapsed_seconds.count() << " seconds\n";

    //传入左值时,使用push_back效率更高
    //传入右值时,使用emplace_back效率更高

    return 0;
}
