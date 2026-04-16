//Evan Sanders

#include <stdio.h>
#include <string>


int runLRU(int frame_count, int page_list[], int page_count) {
    // 2D Array to store the pages in the frame
    int table[frame_count][page_count];
    // Initialize the table with -1
    for (int i = 0; i < frame_count; i++) {
        for (int j = 0; j < page_count; j++) {
            table[i][j] = -1;
        }
    }
    int fault_count = 0;
    // Array to store the faults
    bool faults[page_count];
    for (int i = 0; i < page_count; i++) {
        faults[i] = false;
    }
    // Array to store the frames
    int frame[frame_count];
    // Initialize the frame with -1
    for (int i = 0; i < frame_count; i++) {
        frame[i] = -1;
    }

    
    // Main loop over length of page list
    for (int i = 0; i < page_count; i++) {
        // Get current page
        int page = page_list[i];

        // Assume fault until proven otherwise
        bool fault = true;
        // Check if page is already present
        for (int j = 0; j < frame_count; j++) {
            if (frame[j] == page) {
                // Track the fault
                fault     = false;
                faults[i] = true;
                break;
            }
        }
        // If fault: read a new page
        if (fault) {
            fault_count++;
            bool done = false;
            // Check if there is an empty frame
            for (int j = 0; j < frame_count; j++) {
                // Found a slot, place page:
                if (frame[j] == -1) {
                    frame[j] = page;
                    done = true;
                    break;
                }
            }
            // If there is no empty frame, we need to replace a page
            if (!done) {
                // create and setup and array to track old pages
                int new_pages[frame_count]; 
                for (int l = 0; l < frame_count; l++) {
                    new_pages[l] = -1;
                }
                // Array to track the new pages
                int new_page_count = 0;
                int to_replace = -1;
                // Get the previous frame_count pages
                for (int k = i-1; k > 0; k--) {
                    for (int l = 0; l < frame_count; l++) {
                        // Page already in the new pages array
                        if (page_list[k] == new_pages[l]) {
                            break;
                        }
                        // Found a new page, place page:
                        if (new_pages[l] == -1) {
                            new_pages[l] = page_list[k];
                            new_page_count++;
                            break;
                        }
                    }
                }
                // This is the oldest page in the new pages array
                to_replace = new_pages[frame_count-1]; // Replace the last page in the new pages array

                // Debug for oldest page finder
                // printf("New pages %d: ", page);
                // for (int l = 0; l < new_page_count; l++) {
                //     printf("%d ", new_pages[l]);
                // }
                // printf("\n");
                // printf("To replace: %d\n", to_replace);
                
                // Replace the oldest page with the new page
                for (int l = 0; l < frame_count; l++) {
                    // Find and replace page
                    if (frame[l] == to_replace) {
                        frame[l] = page;
                        break;
                    }
                }

            }


            
            
        }

        // Update the table with the frame set
        for (int j = 0; j < frame_count; j++) {
            table[j][i] = frame[j];
        }
        
        // Debug for frame set
        // for (int j = 0; j < frame_count; j++) {
        //     printf("%d ", frame[j]);
        // }
        // printf("%s\n", faults[i] ? "R" : "F");
    }



    // printf("Table:\n");
    // Print the finished table
    // Main printing loop
    for (int i = -2; i < frame_count + 1; i++) {
        for (int j = 0; j < page_count; j++) {
            if (i == -2) {
                // Print the page list
                printf(" %d ", page_list[j]);
            } else if (i == -1) {
                // Print the separator
                printf("---");
            } else if (i < frame_count) {
                // Print the frame set
                if (faults[j]) {
                    printf("   ");
                } else {
                    printf(" %s ", table[i][j] == -1 ? " " : std::to_string(table[i][j]).c_str());
                }
            } else {
                // Print the faults
                printf(" %s ", faults[j] ? " " : "/");
            }
            // printf("%s ", faults[j] ? "F" : "R");
        }
        printf("\n");
    }
    printf("Fault count: %d\n", fault_count);
    return 0;
}

// Standalone test driver only when compiling lru.cpp alone (not when included from main.cpp).
#ifndef RUNNING_MAIN
    int main() {
        int frame_count = 4;
        int page_list[] = {2,3,2,1,5,2,4,5,3,2,5,2};
        int page_count = sizeof(page_list) / sizeof(page_list[0]);
        // Test IT!
        runLRU(frame_count, page_list, page_count);
        return 0;
    }
#endif