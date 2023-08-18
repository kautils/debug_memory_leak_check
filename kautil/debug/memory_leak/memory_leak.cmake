
set(KAUTIL_MEMORY_CHECK_INFO true)
set(KAUTIL_MEMORY_LEAK_CHECK_MAX_PATH 1024)

set(__t kautil_memory_leak_check)
add_library(${__t} INTERFACE)
add_library(kautl::debug::memory_leak_check ALIAS ${__t})

unset(__include_dir)
set(__include_dir include)
if(${KAUTIL_MEMORY_CHECK_INFO})
    target_include_directories(${__t} INTERFACE include)
    target_compile_definitions(${__t} INTERFACE KAUTIL_MEMORY_LEAK_CHECK)
    target_compile_definitions(${__t} INTERFACE KAUTIL_MEMORY_LEAK_CHECK_MAX_PATH=${KAUTIL_MEMORY_LEAK_CHECK_MAX_PATH})
else()
    target_include_directories(${__t} INTERFACE ${__include_dir})
endif()

set(__t tmain_memory_leak_check)
add_executable(${__t})
target_sources(${__t} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/unit_test.cc)
target_link_libraries(${__t} PRIVATE kautl::debug::memory_leak_check)
target_compile_definitions(${__t} PRIVATE TMAIN_MEMORY_LEAK_CHECK)