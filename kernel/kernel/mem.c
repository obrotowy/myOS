#include <kernel/multiboot.h>
#include <kernel/tty.h>
#include <stdio.h>


void identity_map(uint32_t* page_table, uint32_t* page_directory, uint32_t from, int size) {
    for (; size > 0; from += 4096, size -= 4096, page_table++, page_directory++) {
        // Set the page directory entry
        *page_directory = (uint32_t) page_table | 3; // Present and RW
    }
}

void fill_page_tables(uint32_t* page_table) {
    for (int i = 0; i<1024; ++i) {
        // Set the page table entry
        page_table[i] = (i << 12) | 3; // Present and RW
    }
}
