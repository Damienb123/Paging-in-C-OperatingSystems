#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 128
#define NUM_PAGES 32
#define NUM_FRAMES 8

unsigned long page_table[NUM_PAGES] = {
    2, 4, 1, 7, 3, 5, 6, 
};

void translate_addresses(const char *infile, const char *outfile) {
    FILE *input = fopen(infile, "rb");
    FILE *output = fopen(outfile, "wb");
    if (!input || !output) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    unsigned long logical_address, physical_address;
    while (fread(&logical_address, sizeof(unsigned long), 1, input) == 1) {
        unsigned long page_number = logical_address / PAGE_SIZE;
        unsigned long offset = logical_address % PAGE_SIZE;

        if (page_number >= NUM_PAGES) {
            fprintf(stderr, "Invalid logical address: %lu\n", logical_address);
            continue;
        }

        unsigned long frame_number = page_table[page_number];
        physical_address = frame_number * PAGE_SIZE + offset;

        fwrite(&physical_address, sizeof(unsigned long), 1, output);
    }

    fclose(input);
    fclose(output);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    translate_addresses(argv[1], argv[2]);
    return 0;
}

