#include <stdio.h>
#include <stdlib.h>
#include "phypages.h"
#include "pagetable.h"

void translate_addresses(const char *infile, const char *outfile) {
    FILE *input = fopen(infile, "rb");
    FILE *output = fopen(outfile, "wb");
    if (!input || !output) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    unsigned long logical_address, physical_address;
    while (fread(&logical_address, sizeof(unsigned long), 1, input) == 1) {
        physical_address = translate(logical_address);
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

    initialize_phypages();
    initialize_pagetable();

    translate_addresses(argv[1], argv[2]);

    printf("Page faults: %d\n", get_page_fault_count());
    return 0;
}

