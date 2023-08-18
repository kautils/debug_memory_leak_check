
#ifndef DEBUG_MEMORY_LEAK_MEMORY_LEAK_HPP
#define DEBUG_MEMORY_LEAK_MEMORY_LEAK_HPP

#ifdef KAUTIL_MEMORY_LEAK_CHECK

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static auto kMemcheckDirName="kautil_memory_leak_check";

#define generate_file_path(varname)\
char varname[KAUTIL_MEMORY_LEAK_CHECK_MAX_PATH]={};\
buffer[sprintf(varname,"%s/%lld",kMemcheckDirName,reinterpret_cast<unsigned long long int>(ptr))]=0;
void kautil_debug_memory_leak_check_configure_directory(const char * dir){
    kMemcheckDirName = dir;
}

bool kautil_debug_memory_leak_check_once(){
    struct stat st;
    if(stat(kMemcheckDirName,&st)){
        fprintf(stderr,"no such directory : \"%s\"",kMemcheckDirName);
        exit(1);
    } 
    return true;
}

void * kautil_debug_memory_leak_check_inc(void * ptr,const char * file, int line){
    generate_file_path(buffer);
    static auto kCheckDir = kautil_debug_memory_leak_check_once();  
    auto fd = fopen(buffer,"w+b");
    fprintf(fd,"%s(%d)",file,line);
    fclose(fd);
    return ptr;
}

void * kautil_debug_memory_leak_check_dec(void * ptr){
    generate_file_path(buffer);
    remove(buffer);
    return ptr;
}


#define __memory_leak_setdir(dir)  kautil_debug_memory_leak_check_configure_directory(dir);
#define __new(type,...) reinterpret_cast<type*>(kautil_debug_memory_leak_check_inc(new type(__VA_ARGS__),__FILE__,__LINE__))
#define __delete(ptr) kautil_debug_memory_leak_check_dec(ptr)

#else 

#define __memory_leak_setdir(dir) 
#define __new(type,...) new type(__VA_ARGS__)
#define __delete(ptr) delete ptr

#endif

#endif