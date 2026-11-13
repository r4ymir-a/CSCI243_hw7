/**
 * @file dissect.c
 * @brief dissects messages from stream and extacts payload
 *
 * @author Raymir Aguero <rma8154@rit.edu>
 * @course CSCI-243 Homework 7
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * handles truncation and exits with code 1
*/
static void truncationError(void) {
    printf("error: truncated message\n");
    exit(1);
}

/**
 * Main function  for the dissect program.
 * Reads messages and extracts information from data
 * @return 0 on success, 1 on truncated message error
 */
int main(void) {
    int b0 = getchar();

    unsigned long msgCount  = 0;

    while (b0 != EOF) {
        // check
        int b1 = getchar();
        int b2 = getchar();
        int b3 = getchar();
        int b4 = getchar();
        int b5 = getchar();
        int b6 = getchar();

        if (b1 == EOF || b2 == EOF || b3 == EOF || b4 == EOF || b5 == EOF || b6 == EOF) {
            truncationError();
        }

        // get data
        unsigned int version = (b0 >> 4) & 0x0F;
        unsigned int type = b0 & 0x0F;
        unsigned int length = ((unsigned int)b1 << 8) | (unsigned int)b2;
        unsigned long timestamp = ((unsigned long)b3 << 24) |
                                  ((unsigned long)b4 << 16) |
                                  ((unsigned long)b5 << 8)  |
                                  (unsigned long)b6;

        printf("msg version=%u type=%u len=%u ts=%lu payload=\"",
               version, type, length, timestamp);

        for (unsigned int i = 0; i < length; i++) {
            int c = getchar();
            if (c == EOF) {
                printf("\"\n");
                truncationError();
            }
            if (c >= 32 && c < 127) {
                putchar(c);
            } else {
                putchar('.');
            }
        }

        printf("\"\n");
        msgCount++;

        b0 = getchar();
    }

    printf("count: %lu\n", msgCount);
    return 0;
}
