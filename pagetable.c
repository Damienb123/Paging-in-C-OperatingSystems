#include "pagetable.h"
#include "phypages.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_PAGES 32
#define PAGE_SIZE 128

typedef struct {
    int frame_number;
    int valid;
} PageTableEntry;

static PageTableEntry page_table[NUM_PAGES];
static int page_fault_count = 0;

void initialize_pagetable() {
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i].frame_number = -1;
        page_table[i].valid = 0;
    }
}

unsigned long translate(unsigned long logical_address) {
    unsigned long page_number = logical_address / PAGE_SIZE;
    unsigned long offset = logical_address % PAGE_SIZE;

    if (page_number >= NUM_PAGES) {
        fprintf(stderr, "Invalid logical address: %lu\n", logical_address);
        exit(EXIT_FAILURE);
    }

    if (page_table[page_number].valid) {
        update_frame_usage(page_table[page_number].frame_number);
        return page_table[page_number].frame_number * PAGE_SIZE + offset;
    }

    page_fault_count++;
    int frame_number = allocate_frame(page_number);
    page_table[page_number].frame_number = frame_number;
    page_table[page_number].valid = 1;

    return frame_number * PAGE_SIZE + offset;
}

int get_page_fault_count() {
    return page_fault_count;
}

void invalidate_page(int page_number) {
    if (page_number >= 0 && page_number < NUM_PAGES) {
        page_table[page_number].valid = 0;
    }
}

