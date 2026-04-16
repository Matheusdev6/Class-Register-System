#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Student{
    char name[100];
    float gpa;              // defines the 'class' student, and what it must have.
    bool isAproved;
} Student;
typedef struct Class{
    char classLetter;
    int numberOfStudents;       // defines the 'class' class, and what it must have
    bool isEmpty;
    Student *students;
} Class;

// register class function, recieves the class counter, and and array of classes -> similar to a school
void RegisterClass(int *class_counter, Class *classes){ 
    Class newClass;
    char classLetter;
    int numberOfStudents;
    Student *students = malloc(sizeof(Student) * 10);
    printf("\tREGISTER CLASS\n");
    printf("Type the letter of the Class:\n");
    scanf(" %c", &classLetter);
    printf("Type the number of students:\n");
    scanf("%d", &numberOfStudents);
    newClass.classLetter = classLetter;
    newClass.numberOfStudents = numberOfStudents;
    newClass.isEmpty = true;
    newClass.students = malloc(sizeof(Student) * numberOfStudents);
    if (students == NULL){
        printf("Error. Could not allocate memory.");
        exit(1);
    }
    (*class_counter)++;
    classes[*class_counter] = newClass;
}
// register student function, recieves which class you´re going to register students in
void RegisterStudent(Class *class){
    if (class->isEmpty){
        printf("\tREGISTER STUDENT\n");
        for (int i = 0; i <= class->numberOfStudents; i++){
            printf("Type the name of the student:\n");
            fgets(class->students[i].name, 100, stdin);
            class->students[i].name[strcspn(class->students[i].name, "\n")] = 0;
            printf("Type the GPA of the student:\n");
            scanf("%f", &class->students[i].gpa);
            if (class->students[i].gpa >= 5.0){
                class->students[i].isAproved = true;
            }
        }
        class->isEmpty = false;
    } 
    else {
        printf("The class you want to register students is full!\n");
    }
}

// select class function, returns which class we are going to visualize, or add students.
Class SelectClass(char *classLetter, Class *classes, int *class_counter){
    for(int i = 0; i <= *class_counter; i++){
        if (classes[i].classLetter == *classLetter){
            return classes[i];
        }
    }
}

// visualize class function, iterates over the class students and show their attributes
void VisualizeClass(Class *class){
    for(int i = 0; i < class->numberOfStudents; i++){
        printf("Name: %s\n", class->students[i].name);
        printf("GPA: %f\n", class->students[i].gpa);
        printf("Is Aproved: %d\n", class->students[i].isAproved);
    }
    printf("\n");
}
int main(void){
    int menu_choice = 23;
    int class_counter = 0;
    char classChoice;
    Class selectedClass;
    Class *classes = malloc(sizeof(Class) * 10);
    printf("Classes and students register system!\n");
    printf("\tMENU\n");
    do{
        printf("Type the following values to navigate:\n\t(1) Register class\n\t(2) Register student\n\t(3) Visualize class\n\t(0) Exit\n");
        scanf("%d", &menu_choice);
        switch(menu_choice){
            case 1:
                RegisterClass(&class_counter,classes);
                system("cls");
                break;
            case 2:
                printf("Type the letter of the class you want to register students:\n");
                scanf(" %c", &classChoice);
                selectedClass = SelectClass(&classChoice, classes, &class_counter);
                RegisterStudent(&selectedClass);
                system("cls");
                break;
            case 3:
                printf("Type the letter of the class you want to visualize:\n");
                scanf(" %c", &classChoice);
                selectedClass = SelectClass(&classChoice, classes, &class_counter);
                VisualizeClass(&selectedClass);
                system("cls");
                break;
            case 0:
                for(int i = 0; i <= class_counter; i++){
                    free(classes[i].students);
                }
                free(classes);
                printf("Exiting the system...\n");
                break;
        }
    } while(menu_choice != 0);
    return 0;
}