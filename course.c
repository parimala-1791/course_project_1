#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSES 100
#define MAX_NAME_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    char day[MAX_NAME_LEN];  
    char time[MAX_NAME_LEN]; 
    char room[MAX_NAME_LEN]; 
    char professor[MAX_NAME_LEN];
} Course;

Course courses[MAX_COURSES];
int courseCount = 0;

void addCourse() {
    if (courseCount >= MAX_COURSES) {
        printf("Maximum courses reached.\n");
        return;
    }
    printf("Enter course name: ");
    scanf(" %[^\n]", courses[courseCount].name);
    printf("Enter day: ");
    scanf(" %[^\n]", courses[courseCount].day);
    printf("Enter time: ");
    scanf(" %[^\n]", courses[courseCount].time);
    printf("Enter room: ");
    scanf(" %[^\n]", courses[courseCount].room);
    printf("Enter professor: ");
    scanf(" %[^\n]", courses[courseCount].professor);
    courseCount++;
    printf("Course added successfully.\n");
}

void displayTimetable() {
    char days[7][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int d = 0; d < 7; d++) {
        printf("\n%s:\n", days[d]);
        int found = 0;
        for (int i = 0; i < courseCount; i++) {
            if (strcmp(courses[i].day, days[d]) == 0) {
                printf("  %s - %s, Room: %s, Prof: %s\n", courses[i].time, courses[i].name, courses[i].room, courses[i].professor);
                found = 1;
            }
        }
        if (!found) printf("  No courses.\n");
    }
}

void saveToFile() {
    FILE *file = fopen("timetable.txt", "w");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%d\n", courseCount);
    for (int i = 0; i < courseCount; i++) {
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n", courses[i].name, courses[i].day, courses[i].time, courses[i].room, courses[i].professor);
    }
    fclose(file);
    printf("Timetable saved.\n");
}

void loadFromFile() {
    FILE *file = fopen("timetable.txt", "r");
    if (!file) {
        printf("No saved timetable found.\n");
        return;
    }
    fscanf(file, "%d\n", &courseCount);
    for (int i = 0; i < courseCount; i++) {
        fscanf(file, " %[^\n]\n", courses[i].name);
        fscanf(file, " %[^\n]\n", courses[i].day);
        fscanf(file, " %[^\n]\n", courses[i].time);
        fscanf(file, " %[^\n]\n", courses[i].room);
        fscanf(file, " %[^\n]\n", courses[i].professor);
    }
    fclose(file);
    printf("Timetable loaded.\n");
}

int main() {
    loadFromFile();
    int choice;
    while (1) {
        printf("\nUniversity Timetable Management\n");
        printf("1. Add Course\n");
        printf("2. Display Timetable\n");
        printf("3. Save Timetable\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addCourse(); break;
            case 2: displayTimetable(); break;
            case 3: saveToFile(); break;
            case 4: saveToFile(); exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}