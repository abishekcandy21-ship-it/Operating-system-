/* Exp 16: Random access file for processing employee details
   (record number is derived from the employee id, accessed with fseek) */
#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int  empId;
    char empName[50];
    float empSalary;
};

int main()
{
    FILE *fp;
    struct Employee emp;
    int choice, id;

    fp = fopen("employee.dat", "wb+");           /* start with a fresh file */
    if (fp == NULL) { printf("Error creating the file.\n"); return 1; }

    do {
        printf("\nEmployee Database Menu:\n1. Add Employee\n2. Display Employee Details\n3. Update Employee Details\n4. List All Employees\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp.empId);
                printf("Enter Employee Name: ");
                scanf("%s", emp.empName);
                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);
                fseek(fp, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                fwrite(&emp, sizeof(struct Employee), 1, fp);
                printf("Employee details added successfully.\n");
                break;
            case 2:
                printf("Enter Employee ID to display: ");
                scanf("%d", &id);
                fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, fp) == 1 && emp.empId == id) {
                    printf("Employee ID    : %d\n", emp.empId);
                    printf("Employee Name  : %s\n", emp.empName);
                    printf("Employee Salary: %.2f\n", emp.empSalary);
                } else
                    printf("Employee %d not found.\n", id);
                break;
            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &id);
                fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, fp) == 1 && emp.empId == id) {
                    printf("Enter new Employee Name: ");
                    scanf("%s", emp.empName);
                    printf("Enter new Employee Salary: ");
                    scanf("%f", &emp.empSalary);
                    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
                    fwrite(&emp, sizeof(struct Employee), 1, fp);
                    printf("Employee details updated successfully.\n");
                } else
                    printf("Employee %d not found.\n", id);
                break;
            case 4:
                rewind(fp);
                printf("\nID\tName\t\tSalary\n");
                while (fread(&emp, sizeof(struct Employee), 1, fp) == 1)
                    if (emp.empId > 0)
                        printf("%d\t%-10s\t%.2f\n", emp.empId, emp.empName, emp.empSalary);
                break;
            case 5: break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    fclose(fp);
    return 0;
}
