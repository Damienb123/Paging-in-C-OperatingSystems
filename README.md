# Paging-in-C-OperatingSystems
This project implements a simulator for OS-level memory management, focusing on address translation and virtual memory. Although typical OSs handle multiple processes, this simulator is designed to manage a single process.

## System Properties
- **Physical Memory**: 1 KB  
- **Virtual Memory**: 4 KB  
- **Page/Frame Size**: 128 bytes  

### Key Metrics
- **Maximum pages per process**: 32  
- **Total frames**: 8  
- **Page table entries**: 32  

## Implementation Details

### Part 1: Address Translation and I/O 
- Simulates address translation using a predefined page table.  
- **Input**: Sequence file (`infile`) containing logical addresses in binary format.  
- **Output**: Physical addresses written to `outfile` in binary format.  

#### How it Works
1. Hardcodes the page-to-frame mapping.
2. Reads logical addresses, translates them using the page table, and writes the physical addresses to the output file.  
3. Includes verification via provided test sequences and checksum (`md5sum`) validation.

---

### Part 2: Virtual Memory Management 
- Extends the simulation with physical memory management and dynamic page table handling.  

#### Features
- Allocates frames sequentially, starting from frame 1.
- Implements **Least Recently Used (LRU)** page replacement when frames are full.
- Manages page table updates, including invalidation and reverse mappings.
- Records the number of page faults during translation.

#### Output
- Translated physical addresses.
- Computes a checksum (`md5sum`) for validation.

---

### Part 3: Adaptive Design
- Generalizes the simulator to handle any configuration of memory properties and input parameters.

#### Parameters
- `BytesPerPage`, `SizeOfVirtualMemory`, `SizeOfPhysicalMemory`
- Input file (`SequenceFile`) and output file (`OutputFile`)

#### Verification
Compares results with Part 2 outputs to ensure correctness.

---

## File Structure
- **Source Files**:
  - `part1.c`: Implements address translation for Part 1.
  - `phypages.c`, `pagetable.c`, `part2.c`: Implements physical memory and page table management for Part 2.
  - `part3.c`: Implements the generalized adaptive design for Part 3.
- **Test Data**:
  - Input: `part1testsequence`, `part2sequence`
  - Output: `part1-output`, `part2-output`
- **Report**:
  - `REPORT.txt`: Includes checksum results, number of page faults (Part 2), and implementation notes (Part 3).

---
