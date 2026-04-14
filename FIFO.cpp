#include <stdio.h>
#include <string>

// Replaces the oldest page in memory
int runFIFO(int frame_count, int page_table[], int page_count) {

    // 2D array to store frame contents at each step for display
    int table[frame_count][page_count];
    for (int i = 0; i < frame_count; i++) {
        for (int j = 0; j < page_count; j++) {
            table[i][j] = -1;
        }
    }

    int fault_count = 0;
    int next_to_replace = 0;

    // Track which steps were hits (for blank column requirement)
    bool hits[page_count];
    for (int i = 0; i < page_count; i++) {
        hits[i] = false;
    }

    // Contents of memory frames
    int frame[frame_count];
    for (int i = 0; i < frame_count; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < page_count; i++) {
        int page = page_table[i];
        bool hit = false;

        // Check for a hit: is the page already in a frame?
        for (int j = 0; j < frame_count; j++) {
            if (frame[j] == page) {
                hit = true;
                hits[i] = true; 
                break;
            }
        }

        // If it's a fault, we replace the oldest entry
        if (!hit) {
            fault_count++;
            
            // Place page in the next available/oldest slot
            frame[next_to_replace] = page;
            
            // Update pointer: move to next index or wrap around to 0
            next_to_replace = (next_to_replace + 1) % frame_count;
        }

        // Update the display table with the current state of frames
        for (int j = 0; j < frame_count; j++) {
            table[j][i] = frame[j];
        }
    }

    // Print the finished table [cite: 27, 28]
    for (int i = -2; i < frame_count + 1; i++) {
        for (int j = 0; j < page_count; j++) {
            if (i == -2) {
                // Row 1: page reference string
                printf(" %d ", page_table[j]);
            } else if (i == -1) {
                // Row 2: separator
                printf("---");
            } else if (i < frame_count) {
                // Rows 3 to (frame_count + 2): frame contents
                if (hits[j]) {
                    // Display blank column when no page fault occurs [cite: 27, 28]
                    printf("   ");
                } else {
                    printf(" %s ", table[i][j] == -1 ? " " : std::to_string(table[i][j]).c_str());
                }
            } else {
                // Last row: fault markers
                printf(" %s ", hits[j] ? " " : "/");
            }
        }
        printf("\n");
    }
    printf("Fault count: %d\n", fault_count);
    return 0;
}

#ifndef RUNNING_MAIN
    int main() {
        int frame_count = 4;
        int page_list[] = {2,3,2,1,5,2,4,5,3,2,5,2};
        int page_count = sizeof(page_list) / sizeof(page_list[0]);
        runFIFO(frame_count, page_list, page_count);
        return 0;
    }
#endif
