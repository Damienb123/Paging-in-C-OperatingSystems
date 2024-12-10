#ifndef PAGETABLE_H
#define PAGETABLE_H

void initialize_pagetable();
unsigned long translate(unsigned long logical_address);
int get_page_fault_count();
void invalidate_page(int page_number);

#endif

