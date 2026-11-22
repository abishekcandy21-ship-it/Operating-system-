/* Exp 35: Indexed file allocation - an index block holds pointers to all
   the blocks of a file (i-th entry points to the i-th block of the file) */
#include <stdio.h>

int main()
{
    int used[100] = {0}, index[20], n, i, blk, ch, start;
    char more;

    do {
        printf("\nEnter the index block number: ");
        scanf("%d", &start);
        if (used[start]) {
            printf("Block %d is already allocated.\n", start);
            goto next;
        }
        printf("Enter the number of blocks needed by the file: ");
        scanf("%d", &n);
        printf("Enter the block numbers: ");
        ch = 1;
        for (i = 0; i < n; i++) {
            scanf("%d", &blk);
            index[i] = blk;
            if (used[blk]) ch = 0;
        }
        if (!ch) {
            printf("One of the blocks is already allocated. File cannot be stored.\n");
            goto next;
        }
        used[start] = 1;
        for (i = 0; i < n; i++) used[index[i]] = 1;

        printf("File indexed successfully.\nIndex block %d -> ", start);
        for (i = 0; i < n; i++)
            printf("[%d]=%d ", i, index[i]);
        printf("\n");
next:
        printf("Do you want to store another file (y/n)? ");
        scanf(" %c", &more);
    } while (more == 'y' || more == 'Y');
    return 0;
}
