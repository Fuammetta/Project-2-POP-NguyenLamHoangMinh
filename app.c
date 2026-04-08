#include <stdio.h>

#define MAX_STUDENTS 100

// Structure to store individual student data
struct Student
{
    int id;
    char name[100];
    float midterm;
    float final;
    float average;
    char grade[15];
};

// Global array and counter to manage student records
struct Student students[MAX_STUDENTS];
int student_count = 0;

/**
 * isDuplicate:
 * Checks if a specific ID already exists in the system to prevent 
 * multiple students having the same identifier.
 */
int isDuplicate(int id)
{
    for (int i = 0; i < student_count; i++)
    {
        if (students[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * showMenu:
 * Displays the main user interface options to the console.
 */
void showMenu()
{
    printf("\n========== STUDENT SYSTEM ==========\n");
    printf("1. Add student\n");
    printf("2. Display students\n");
    printf("3. Calculate average\n");
    printf("4. Search student\n");
    printf("5. Save to file\n");
    printf("6. Sort students by score\n");
    printf("7. View Statistical Analysis\n");
    printf("0. Exit\n");
}

/**
 * addStudent:
 * Handles user input for new student records. 
 * Includes validation for duplicate IDs and score ranges (0-10).
 */
void addStudent()
{
    if (student_count >= MAX_STUDENTS)
    {
        printf("Student list is full!\n");
        return;
    }

    struct Student s;
    s.average = 0;
    int tempId;

    printf("Enter student ID: ");
    if (scanf("%d", &tempId) != 1)
    {
        printf("Invalid ID format! Please enter a number.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    if (isDuplicate(tempId))
    {
        printf("Error: Student ID %d already exists.\n", tempId);
        return;
    }
    s.id = tempId;

    printf("Enter name: ");
    scanf(" %[^\n]", s.name);

    // Midterm score input validation loop
    do
    {
        printf("Enter midterm score (0-10): ");
        if (scanf("%f", &s.midterm) != 1)
        {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            s.midterm = -1;
            continue;
        }
        if (s.midterm < 0 || s.midterm > 10)
        {
            printf("Error: Score must be between 0 and 10.\n");
        }
    } while (s.midterm < 0 || s.midterm > 10);

    // Final score input validation loop
    do
    {
        printf("Enter final score (0-10): ");
        if (scanf("%f", &s.final) != 1)
        {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            s.final = -1;
            continue;
        }
        if (s.final < 0 || s.final > 10)
        {
            printf("Error: Score must be between 0 and 10.\n");
        }
    } while (s.final < 0 || s.final > 10);

    students[student_count++] = s;
    printf("Student added successfully!\n");
}

/**
 * displayStudents:
 * Prints a formatted table of all students currently in the array.
 */
void displayStudents()
{
    if (student_count == 0)
    {
        printf("No students in system.\n");
        return;
    }

    printf("\nID\tName\tMidterm\tFinal\tAverage\tGrade\n");
    for (int i = 0; i < student_count; i++)
    {
        printf("%d\t%s\t%.2f\t%.2f\t%.2f\t%s\n",
               students[i].id,
               students[i].name,
               students[i].midterm,
               students[i].final,
               students[i].average,
               students[i].grade);
    }
}

/**
 * calculateAverage:
 * Computes the weighted average (40% Midterm, 60% Final) 
 * and assigns a letter/descriptive grade to each student.
 */
void calculateAverage()
{
    if (student_count == 0)
    {
        printf("\nNo students to calculate.\n");
        return;
    }

    for (int i = 0; i < student_count; i++)
    {
        students[i].average = (students[i].midterm * 0.4) + (students[i].final * 0.6);
        if (students[i].average >= 8.5) sprintf(students[i].grade, "Excellent");
        else if (students[i].average >= 7.0) sprintf(students[i].grade, "Good");
        else if (students[i].average >= 5.0) sprintf(students[i].grade, "Average");
        else sprintf(students[i].grade, "Poor");
    }

    printf("\nAverages calculated successfully for %d students!\n", student_count);
}

/**
 * searchStudent:
 * Searches for a student record by ID and displays their name and average.
 */
void searchStudent()
{
    int searchId;
    if (student_count == 0)
    {
        printf("\nNo students recorded in the system yet.\n");
        return;
    }

    printf("Enter student ID to search: ");
    if (scanf("%d", &searchId) != 1)
    {
        printf("\nError: Invalid input!\n");
        while (getchar() != '\n');
        return;
    }

    for (int i = 0; i < student_count; i++)
    {
        if (students[i].id == searchId)
        {
            printf("\nStudent found:\nName: %s\nAverage: %.1f\n", students[i].name, students[i].average);
            return;
        }
    }
    printf("\nStudent with ID %d not found.\n", searchId);
}

/**
 * saveToFile:
 * Exports all student data into a formatted text file called "students.txt".
 */
void saveToFile()
{
    if (student_count == 0)
    {
        printf("No data to save.\n");
        return;
    }

    FILE *fptr = fopen("students.txt", "w");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fptr, "ID\tName\tMidterm\tFinal\tAverage\tgrade\n");
    fprintf(fptr, "--------------------------------------------\n");

    for (int i = 0; i < student_count; i++)
    {
        fprintf(fptr, "%d\t%s\t%.2f\t%.2f\t%.2f\t%s\n",
                students[i].id, students[i].name, students[i].midterm,
                students[i].final, students[i].average, students[i].grade);
    }

    fclose(fptr);
    printf("Data successfully saved to students.txt!\n");
}

/**
 * sortStudents:
 * Uses Bubble Sort to arrange students in descending order based on their averages.
 */
void sortStudents()
{
    if (student_count < 2)
    {
        printf("Not enough students to sort.\n");
        return;
    }

    struct Student temp;
    for (int i = 0; i < student_count - 1; i++)
    {
        for (int j = 0; j < student_count - i - 1; j++)
        {
            if (students[j].average < students[j + 1].average)
            {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("\nStudents sorted by average score (Highest to Lowest)!\n");
}

/**
 * displayStatistics:
 * Calculates and prints class-wide metrics such as high/low scores and pass rates.
 */
void displayStatistics()
{
    if (student_count == 0)
    {
        printf("\nNo student data available.\n");
        return;
    }

    float totalScore = 0;
    float highest = students[0].average;
    float lowest = students[0].average;
    int passedCount = 0;

    for (int i = 0; i < student_count; i++)
    {
        if (students[i].average > highest) highest = students[i].average;
        if (students[i].average < lowest) lowest = students[i].average;
        if (students[i].average >= 5.0) passedCount++;
        totalScore += students[i].average;
    }

    printf("\n========== STATISTICAL ANALYSIS ==========\n");
    printf("Highest Average Score: %.2f\n", highest);
    printf("Lowest Average Score:  %.2f\n", lowest);
    printf("Students Passed (>=5): %d / %d\n", passedCount, student_count);
    printf("Class Average Score:   %.2f\n", totalScore / student_count);
    printf("==========================================\n");
}

/**
 * main:
 * Entry point of the program. Controls the loop and menu selection.
 */
int main()
{
    int choice;
    while (1)
    {
        showMenu();
        printf("Choose: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a number (0-7).\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choice)
        {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: calculateAverage(); break;
            case 4: searchStudent(); break;
            case 5: saveToFile(); break;
            case 6: sortStudents(); displayStudents(); break;
            case 7: displayStatistics(); break;
            case 0: return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
