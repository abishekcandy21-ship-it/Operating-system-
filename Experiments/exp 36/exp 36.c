/* Exp 36: Linked file allocation - a file is a linked list of disk blocks;
   the directory holds the first and last block, each block points to the next */
#include <stdio.h>

#define DISK 50

int main()
{
    int next[DISK], used[DISK] = {0};
    int n, i, blk, prev, first, last;
    char more, name[30];

    for (i = 0; i < DISK; i++) next[i] = -1;

    do {
        printf("\nEnter the file name: ");
        scanf("%s", name);
        printf("Enter the number of blocks: ");
        scanf("%d", &n);
        printf("Enter the block numbers in order: ");
        prev = -1; first = -1; last = -1;
        for (i = 0; i < n; i++) {
            scanf("%d", &blk);
            if (blk < 0 || blk >= DISK || used[blk]) {
                printf("Block %d is not available, skipped.\n", blk);
                continue;
            }
            used[blk] = 1;
            if (first == -1) first = blk;
            if (prev != -1) next[prev] = blk;    /* link previous block to this one */
            prev = blk;
            last = blk;
        }
        printf("\nDirectory entry:\nFile\tStart\tEnd\n%s\t%d\t%d\n", name, first, last);
        printf("Chain: ");
        for (blk = first; blk != -1; blk = next[blk])
            printf("%d -> ", blk);
        printf("NULL\n");
        printf("Store another file (y/n)? ");
        scanf(" %c", &more);
    } while (more == 'y' || more == 'Y');
    return 0;
}
