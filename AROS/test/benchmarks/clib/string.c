/*
    Copyright � 2008, The AROS Development Team. All rights reserved.
    $Id$
*/

#include "benchmark.h"
#include <string.h>

int main() 
{
    #define BUFSIZE 1000000UL
    char src[BUFSIZE];
    char dst[BUFSIZE];
    
    #define BENCHMARK(z, n, c) memcpy(dst, src, BUFSIZE);
    BENCHMARK_BUFFER(memcpy,1000, BUFSIZE);
    #undef BENCHMARK
    
    #define BENCHMARK(z, n, c) memmove(dst, src, BUFSIZE);
    BENCHMARK_BUFFER(memmove,1000, BUFSIZE);
    #undef BENCHMARK
    
    #define BENCHMARK(z, n, c) int res ## n = memcmp(dst, src, BUFSIZE); res ## n = 0;
    memset(src, 'a', BUFSIZE);
    memset(dst, 'a', BUFSIZE);
    BENCHMARK_BUFFER(memcmp,1000, BUFSIZE);
    #undef BENCHMARK
    
    #define BENCHMARK(z, n, c) char *res ## n = memchr(dst, 'b', BUFSIZE); res ## n = NULL;
    memset(src, 'a', BUFSIZE);
    BENCHMARK_BUFFER(memchr,1000, BUFSIZE);
    #undef BENCHMARK
    
    #define BENCHMARK(z, n, c) memset(dst, 'b', BUFSIZE);
    BENCHMARK_BUFFER(memset,1000, BUFSIZE);
    #undef BENCHMARK
    
    #define BENCHMARK(z, n, c) int res ## n = strlen(dst); res ## n = 0;
    memset(dst, 'a', BUFSIZE);
    dst[BUFSIZE - 1] = '\0';
    BENCHMARK_BUFFER(strlen,1000, BUFSIZE);
    #undef BENCHMARK
    
    #define BENCHMARK(z, n, c) strncpy(dst, src, BUFSIZE);
    memset(src, 'a', BUFSIZE);
    memset(dst, 'a', BUFSIZE);
    BENCHMARK_BUFFER(strncpy,1000, BUFSIZE);
    #undef BENCHMARK
    
    #define BENCHMARK(z, n, c) int res ## n = strncmp(dst, src, BUFSIZE); res ## n = 0;
    memset(src, 'a', BUFSIZE);
    memset(dst, 'a', BUFSIZE);
    BENCHMARK_BUFFER(strncmp,1000, BUFSIZE);
    #undef BENCHMARK
    
    #define BENCHMARK(z, n, c) int res ## n = strncasecmp(dst, src, BUFSIZE); res ## n = 0;
    memset(src, 'a', BUFSIZE);
    memset(dst, 'A', BUFSIZE);
    BENCHMARK_BUFFER(strncasecmp,1000, BUFSIZE);
    #undef BENCHMARK
    
    return 1;
}
