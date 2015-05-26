
#include "bm_io.h"

void enable_dcache() {
    unsigned cache_config;
    __asm__ volatile ("mrc p15, 0, %[config], c1, c0, 0":[config]"=r"(cache_config));
    // bit manipulation
    unsigned int C = (cache_config >> 2) & 0x1;// C bit, data cache info
    send_string("C bit: ");
    send_uint32(C);
    send_string("\r\n");
    // enable data cache
    send_string("enabling data cache\r\n");
    cache_config = cache_config | (0x1 << 2);
    __asm__ volatile("mcr p15, 0, %[config], c1, c0, 0"::[config]"r"(cache_config));
}

const char *size_map[] = {
    "0.5KB",
    "1KB",
    "2KB",
    "4KB",
    "8KB",
    "16KB",
    "32KB",
    "64KB",
    "128KB"
};

unsigned int cache_type() {
    unsigned cache_config;
    __asm__ volatile ("MRC P15, 0, %0, c0, c0, 0" : "=r"(cache_config));

    return cache_config;
}

void dcache_metrics(unsigned int config) {
    send_string("data cache metrics:\r\n");
    unsigned int dsize = (config >> 18) & 0xF;
    unsigned int assoc = (config >> 15) & 0x7;
    unsigned int block = (config >> 12) & 0x3;
    send_string("cache size: ");
    send_uint32(dsize);
    send_string("\r\n");
    send_string("associativity: ");
    send_uint32(assoc);
    send_string("\r\n");
    send_string("block size: ");
    send_uint32(block);
    send_string("\r\n");
}

void icache_metrics(unsigned int config) {
    send_string("instruction cache metrics:\r\n");
    unsigned int isize = (config >> 6) & 0xF;
    unsigned int assoc = (config >> 3) & 0x7;
    unsigned int block = (config >> 0) & 0x3;
    send_string("cache size: ");
    send_uint32(isize);
    send_string("\r\n");
    send_string("associativity: ");
    send_uint32(assoc);
    send_string("\r\n");
    send_string("block size: ");
    send_uint32(block);
    send_string("\r\n");
}

void entrance()
{
    enable_dcache();
    unsigned int cache_config = cache_type();
    send_string("--------------------\r\n");
    dcache_metrics(cache_config);
    send_string("--------------------\r\n");
    icache_metrics(cache_config);
}
