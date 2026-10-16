#include <stdio.h>
#include <string.h>

#define NUMBER_OF_SUBJECTS  5
#define TOTAL_STUDENTS 100


struct Student {
    int roll_no;
    char name[50];
    float marks[NUMBER_OF_SUBJECTS];
    float total;
    float percentage;
    char result[10];
    // pass or fail garauni kura is a string.
};



// paxi tyo marks ko array garauney
// use definition to impress sir


// prototypes
void addStudent(struct Student s[], int *count);
// count garna call by refrence use garni coz otherwise it will be block scoped 
// array pointer is passed instead of the whole array

void displayStudents(struct Student s[], int count);
void searchStudent(struct Student s[], int count);
void calculateResult(struct Student s[], int count);
void updateStudent(struct Student s[], int count);
void findHighestMarks(struct Student s[], int count);

int main() {
    int total = 100;
    struct Student students[total];
    
    int choice, count=0;
    
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
            // invalid case handling
            printf("Invalid input! Please enter a number.\n");

            while(getchar() != '\n'); // clear buffer
            continue; 
            // kaam lagney keyword
        }

        
        switch (choice) {
            case 1:
                addStudent(students, &count);
                // yesma count pass gareko bhaye call by value hunthyo and the value only changes inside the funtion but hamilai ta globally scoped garaunu parxa..

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
return 0;
}



// actual definitions:



























void addStudent(struct Student s[], int *count) {
    if (*count >= TOTAL_STUDENTS) {
        printf("Database is full!\n");
        return;
    }

    int c = *count; // shortcut for current index
    printf("Enter Roll Number: ");
    scanf("%d", &s[c].roll_no);

    // Check duplicate roll number
    for (int i = 0; i < c; i++) {
        if (s[i].roll_no == s[c].roll_no) {
            printf("Roll number already exists!\n");
            return;
        }
    }

    printf("Enter Name: ");
   
    
 scanf("%s",&s[c].name);

    s[c].total = 0;
    int failed = 0;
    printf("Enter marks for %d subjects:\n", NUMBER_OF_SUBJECTS);

    for (int i = 0; i < NUMBER_OF_SUBJECTS; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &s[c].marks[i]);
        if (s[c].marks[i] < 0 || s[c].marks[i] > 100) {
            printf("Invalid marks! Enter between 0 and 100.\n");
            i--;
            continue;
        }
        s[c].total += s[c].marks[i];
        if (s[c].marks[i] < 40) {
            failed = 1;
        }
    }

    s[c].percentage = s[c].total / NUMBER_OF_SUBJECTS;
    strcpy(s[c].result, failed ? "Fail" : "Pass"); 

    (*count)++;
    printf("Student added successfully!\n");
}

void displayStudents(struct Student s[], int count) {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    printf("\nRoll No\tName\t\tTotal\tPercentage\tResult\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%.2f\t%.2f%%\t\t%s\n", 
               s[i].roll_no, s[i].name, s[i].total, s[i].percentage, s[i].result);
    }
}



void searchStudent(struct Student s[], int count) {
    if (count == 0) { printf("No records available.\n"); return; }
    
    int roll;
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (s[i].roll_no == roll) {
            printf("\nFound! Name: %s, Total: %.2f, Result: %s\n", 
                   s[i].name, s[i].total, s[i].result);
            return;
        }
    }
    printf("Student not found.\n");
}



void calculateResult(struct Student s[], int count) {
    for (int i = 0; i < count; i++) {
        s[i].total = 0;
        int failed = 0;
        for (int j = 0; j < NUMBER_OF_SUBJECTS; j++) {
            s[i].total += s[i].marks[j];
            if (s[i].marks[j] < 40) failed = 1;
        }
        s[i].percentage = s[i].total / NUMBER_OF_SUBJECTS;
        strcpy(s[i].result, failed ? "Fail" : "Pass");
    }
    printf("All results recalculated successfully!\n");
}



void updateStudent(struct Student s[], int count) {
    int roll;
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (s[i].roll_no == roll) {
            printf("Enter new Name: ");
            getchar();
            // fgets(s[i].name, sizeof(s[i].name), stdin);
            scanf("%s", s[i].name);
            // s[i].name[strcspn(s[i].name, "\n")] = 0;

            s[i].total = 0;
            int failed = 0;

            for (int j = 0; j < NUMBER_OF_SUBJECTS; j++) {
                printf("Subject %d: ", j + 1);
                scanf("%f", &s[i].marks[j]);
                s[i].total += s[i].marks[j];
                if (s[i].marks[j] < 40) {failed = 1;}
            }
            s[i].percentage = s[i].total / NUMBER_OF_SUBJECTS;

            strcpy(s[i].result, failed ? "Fail" : "Pass");
            
            printf("Student updated successfully!\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void findHighestMarks(struct Student s[], int count) {
    if (count == 0) { printf("No records available.\n"); return; }

    int top = 0;
    for (int i = 1; i < count; i++) {
        if (s[i].total > s[top].total) {
            top = i;
        }
    }

    printf("\nFirsst: %s (Roll: %d) with %.2f marks (%.2f%%)\n", 
           s[top].name, s[top].roll_no, s[top].total, s[top].percentage);
}