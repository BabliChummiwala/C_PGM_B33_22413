#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define TOTAL_DAYS 30

// Structure to store student data
struct Student {
    char name[50];
    int roll_no;
    int present_days;
    int absent_days;
};

// Union to store total or shortage days (memory efficient)
union AttendanceInfo { //either one to be used at a time, therefore shared memory will work better here.
    int total_days;
    int shortage_days;
};

// Function to input student data
void inputStudents(struct Student students[], int *num_students) {
    printf("Enter number of students (max %d): ", MAX_STUDENTS);
    scanf("%d", num_students);
    if (*num_students > MAX_STUDENTS) *num_students = MAX_STUDENTS;
    for (int i = 0; i < *num_students; i++) {
        printf("Enter roll number for student %d: ", i+1);
        scanf("%d", &students[i].roll_no);
        printf("Enter name for student %d: ", i+1);
        // Clear input buffer before fgets
        while (getchar() != '\n');
        fgets(students[i].name, sizeof(students[i].name), stdin); //fgets add newline due to which we need strcspn.
        // Remove newline from fgets
        students[i].name[strcspn(students[i].name, "\n")] = 0;
        students[i].present_days = 0;
        students[i].absent_days = 0;
    }
}

// Function to take daily attendance
void takeAttendance(struct Student students[], int num_students, int day) {
    char status;
    printf("\n--- Day %d Attendance ---\n", day);
    for (int i = 0; i < num_students; i++) {
        printf("%s (Roll %d) - Present(P)/Absent(A)? ", students[i].name, students[i].roll_no);
        scanf(" %c", &status);
        if (status == 'P' || status == 'p') {
            students[i].present_days++;
        } else if (status == 'A' || status == 'a') {
            students[i].absent_days++;
        } else {
            printf("Invalid input, marked Absent.\n");
            students[i].absent_days++;
        }
    }
}

// Function to calculate and display attendance report
void calculateShortage(struct Student students[], int num_students, int total_days) {
    union AttendanceInfo info;
    info.total_days = total_days;
    printf("\n--- Final Attendance Report ---\n");
    printf("Roll\tName\t\tPresent\tAbsent\tPercentage\tShortage\n");
    printf("----\t----\t\t-------\t------\t----------\t--------\n");
    for (int i = 0; i < num_students; i++) {
        float percentage = (float)students[i].present_days / total_days * 100;
        info.shortage_days = total_days - students[i].present_days;
        printf("%d\t%-12s\t%d\t%d\t%.1f%%\t\t%d\n", 
               students[i].roll_no, students[i].name, 
               students[i].present_days, students[i].absent_days,
               percentage, info.shortage_days);
    }
}

// Main function
int main() {
    struct Student students[MAX_STUDENTS];
    int num_students = 0;
    int total_days;
    inputStudents(students, &num_students);
    printf("Enter total working days: ");
    scanf("%d", &total_days);
    for (int day = 1; day <= total_days; day++) {
        takeAttendance(students, num_students, day);
    }
    calculateShortage(students, num_students, total_days);
    return 0;
}

