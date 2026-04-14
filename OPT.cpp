#include <stdio.h>
#include <string>

// Replaces page that will not be used for the longest time in the future
int runOPT(int frame_count, int page_table[], int page_count) {

    // 2D array to store frame contents at each step for display
    int table[frame_count][page_count];
    for (int i = 0; i < frame_count; i++) {
        for (int j = 0; j < page_count; j++) {
            table[i][j] = -1;
        }
    }

    int fault_count = 0;

    // Track which steps were hits
    bool faults[page_count];
    for (int i = 0; i < page_count; i++) {
        faults[i] = false;
    }

    // Contents of memory frames
    int frame[frame_count];
    for (int i = 0; i < frame_count; i++) {
        frame[i] = -1;
    }

    int filled = 0;


    for (int i = 0; i < page_count; i++) {
        int page = page_table[i];

        // Push a fault until we find the page already in a frame
        bool fault = true;
        for (int j = 0; j < frame_count; j++) {
            if (frame[j] == page) {
                fault = false;
                faults[i] = true; // Marks hit for display
                break;
            }
        }

        // If fault we need to read a new page
        if (fault) {
            fault_count++;
            bool done = false;

            // Checks for empty frame
            for (int j = 0; j < frame_count; j++) {
                if (frame[j] == -1) {
                    frame[j] = page;
                    done = true;
                    filled++;
                    break;
                }
            }

            // No empty frame, need to replace a page
            if (!done) {
                int replaceIndex = 0;
                int farthest = -1;

                // For each page in the frame, look ahead to see when it is next used
                for (int j = 0; j < frame_count; j++) {
                    int nextUse = -1;

                    // Look ahead in the page table for the next use of frame[j]
                    for (int k = i + 1; k < page_count; k++) {
                        if (page_table[k] == frame[j]) {
                            nextUse = k;
                            break;
                        }
                    }

                    // If a page is not used again, we can replace it immediately
                    if (nextUse == -1) {
                        replaceIndex = j;
                        break;
                    }

                    // Track the page with the farthest next use
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }

                frame[replaceIndex] = page;
            }
        }

        // Update the table with the frame set
        for (int j = 0; j < frame_count; j++) {
            table[j][i] = frame[j];
        }
    }

    // Print the finished table
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
                if (faults[j]) {
                    printf("   ");
                } else {
                    printf(" %s ", table[i][j] == -1 ? " " : std::to_string(table[i][j]).c_str());
                }
            } else {
                // Last row: faults
                printf(" %s ", faults[j] ? " " : "/");
            }
        }
        printf("\n");
    }
    printf("Fault count: %d\n", fault_count);
    return 0;
}

// Test main function for OPT algorithm
#ifndef RUNNING_MAIN
    int main() {
        int frame_count = 3;
        int page_list[] = {1,2,1,3,1,4,1,5,1,6,1,7,1,8};
        int page_count = sizeof(page_list) / sizeof(page_list[0]);
        runOPT(frame_count, page_list, page_count);
        return 0;
    }
#endif