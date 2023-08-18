### kautil_memory_leak_check
* header only.
* thread safe.
* find out what line of which file caused the memory leak.

### cmake variables
``````
# enable/disable memory check functions
set(KAUTIL_MEMORY_CHECK_INFO true)

# maximum size of path which is used by this module
set(KAUTIL_MEMORY_LEAK_CHECK_MAX_PATH 1024)

``````

### example 
```c++

#include "kautil/debug/memory_leak/memory_leak.h"
#include <filesystem>
#include <string>

int main(){
    namespace fs = std::filesystem;
    auto dir = "memory_leak_check";
    fs::remove_all(dir);
    fs::create_directories(dir);
    __memory_leak_setdir(dir);
    __new(std::string,"leak"); // will be logged into "memory_leak_check".  
    __delete(__new(int,0)); 
    return 0;
}

```


### summary
* assumed to be used when smart pointer is not used for some reason.
