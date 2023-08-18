#ifdef TMAIN_MEMORY_LEAK_CHECK

#include "kautil/debug/memory_leak/memory_leak.h"
#include <filesystem>
#include <string>

int main(){
    namespace fs = std::filesystem;
    auto dir = "memory_leak_check";
    fs::remove_all(dir);
    fs::create_directories(dir);
    __memory_leak_setdir(dir);
    __new(std::string,"leak");
    __delete(__new(int,0));
    return 0;
}

#endif