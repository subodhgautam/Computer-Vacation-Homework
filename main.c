#include <stdio.h>
#include <string.h>


struct Student {
    int roll_no;
    char name[50];
    float marks;
    float total;
    float percentage;
    char result[10];
};



// paxi tyo marks ko array garauney
// use definition to impress sir


int main() {
    struct Student students[100];

    int choice;
    
    do {
        printf("\n=========================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM         \n");
        printf("=========================================\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Student Records\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Calculate Student Result\n");
        printf("5. Update Student Information\n");
        printf("6. Find Student with Highest Marks\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        
    
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while(getchar() != '\n'); // clear buffer
            continue;
        }

        
        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                calculateResult(students, count);
                break;
            case 5:
                updateStudent(students, count);
                break;
            case 6:
                findHighestMarks(students, count);
                break;
            case 7:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Please choose between 1 and 7.\n");
        }
    } while (choice != 7);
