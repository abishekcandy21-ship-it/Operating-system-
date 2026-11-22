/* Exp 34: Sequential file allocation - records are stored one after another
   and a record can be reached only by reading all the previous records */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int  recordNumber;
    char data[50];
};

int main()
{
    FILE *fp;
    struct Record rec;
    int n, i, req;
    char more;

    fp = fopen("sequential.dat", "wb");
    printf("Enter the number of records to store: ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        rec.recordNumber = i;
        printf("Enter data for record %d: ", i);
        scanf("%s", rec.data);
        fwrite(&rec, sizeof(rec), 1, fp);        /* written one after another */
    }
    fclose(fp);

    do {
        printf("\nEnter the record number to access: ");
        scanf("%d", &req);
        if (req < 1 || req > n) {
            printf("Record %d does not exist.\n", req);
        } else {
            fp = fopen("sequential.dat", "rb");
            printf("Reading sequentially from the beginning of the file:\n");
            while (fread(&rec, sizeof(rec), 1, fp) == 1) {
                printf("  Read record %d : %s\n", rec.recordNumber, rec.data);
                if (rec.recordNumber == req) break;      /* requested record reached */
            }
            printf("Record %d accessed after reading %d record(s).\n", req, req);
            fclose(fp);
        }
        printf("Access another record (y/n)? ");
        scanf(" %c", &more);
    } while (more == 'y' || more == 'Y');
    return 0;
}
