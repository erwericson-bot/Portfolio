/*
 * Student Grade Calculator
 * A console-based C program that computes subject averages, letter grades,
 * and overall GPA for a student across multiple subjects.
 *
 * Compile: gcc GradeCalculator.c -o GradeCalculator
 * Run:     ./GradeCalculator
 */

#include <stdio.h>
#include <string.h>

#define MAX_SUBJECTS 10
#define NAME_LEN 50

typedef struct {
    char subject[NAME_LEN];
    float score;
    char letterGrade;
    float gradePoint;
} Subject;

char computeLetterGrade(float score) {
    if (score >= 90) return 'A';
    if (score >= 80) return 'B';
    if (score >= 70) return 'C';
    if (score >= 60) return 'D';
    return 'F';
}

float computeGradePoint(char letter) {
    switch (letter) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        default:  return 0.0;
    }
}

int main() {
    Subject subjects[MAX_SUBJECTS];
    int count;
    char studentName[NAME_LEN];

    printf("===== STUDENT GRADE CALCULATOR =====\n");

    printf("Enter student name: ");
    fgets(studentName, NAME_LEN, stdin);
    studentName[strcspn(studentName, "\n")] = '\0';

    printf("Enter number of subjects (max %d): ", MAX_SUBJECTS);
    scanf("%d", &count);
    getchar();

    if (count <= 0 || count > MAX_SUBJECTS) {
        printf("Invalid number of subjects.\n");
        return 1;
    }

    float total = 0;
    float totalGradePoints = 0;

    for (int i = 0; i < count; i++) {
        printf("\nSubject %d name: ", i + 1);
        fgets(subjects[i].subject, NAME_LEN, stdin);
        subjects[i].subject[strcspn(subjects[i].subject, "\n")] = '\0';

        printf("Score for %s (0-100): ", subjects[i].subject);
        scanf("%f", &subjects[i].score);
        getchar();

        if (subjects[i].score < 0) subjects[i].score = 0;
        if (subjects[i].score > 100) subjects[i].score = 100;

        subjects[i].letterGrade = computeLetterGrade(subjects[i].score);
        subjects[i].gradePoint = computeGradePoint(subjects[i].letterGrade);

        total += subjects[i].score;
        totalGradePoints += subjects[i].gradePoint;
    }

    float average = total / count;
    float gpa = totalGradePoints / count;

    printf("\n===== GRADE REPORT FOR %s =====\n", studentName);
    printf("%-20s | %-8s | %-6s | %-5s\n", "Subject", "Score", "Grade", "Point");
    printf("---------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-20s | %-8.2f | %-6c | %-5.1f\n",
               subjects[i].subject, subjects[i].score,
               subjects[i].letterGrade, subjects[i].gradePoint);
    }

    printf("---------------------------------------------\n");
    printf("Overall Average: %.2f\n", average);
    printf("Overall GPA:     %.2f\n", gpa);
    printf("Overall Grade:   %c\n", computeLetterGrade(average));

    return 0;
}
