/*
NAME: Lana Mahmoud Ali Musaffer
Dr. Radi Jarrar
SECTION: 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#define MAX 900

//STUDENT INFORMATION BLOCK
struct student{
    int studentID;
    char studentName[MAX];
    char city[MAX];
    char currentClassID[MAX];
    char enrollmentDate[MAX];
};

typedef struct student* STD;

//TREE BLOCK
struct stdNode{
    STD student;
    struct stdNode* left;
    struct stdNode* right;
};

typedef struct stdNode* SNode;

//CREATE THE STUDENT INFO NODE
STD createStudent(int stdID, char stdName[], char city[], char date[], char classID[]){
    STD node = (STD) malloc(sizeof(struct student));
    node->studentID = stdID;
    for(int i=0; i<MAX; i++){
        node->city[i] = city[i];
        node->studentName[i] = stdName[i];
        node->enrollmentDate[i] = date[i];
        node->currentClassID[i] = classID[i];
    }
    return node;
}

//INSERT A STUDENT INTO THE SYSTEM
SNode insertStudent(SNode* studentRoot, STD student){
    if(*studentRoot == NULL){
        *studentRoot = (SNode) malloc(sizeof(struct stdNode));
        if(*studentRoot == NULL)
            printf("OUT OF SPACE");
        else{
            (*studentRoot)->student = student;
            (*studentRoot)->left = (*studentRoot)->right = NULL;
        }
    }
    else if(student->studentID < (*studentRoot)->student->studentID)
        insertStudent(&((*studentRoot)->left), student);
    else if(student->studentID > (*studentRoot)->student->studentID)
        insertStudent(&((*studentRoot)->right), student);
    return *studentRoot;
}

//FIND A STUDENT BY HER/HIS ID
SNode findStudent(SNode studentRoot, int studentID){
    if(studentRoot == NULL)
        return NULL;
    else if(studentID < studentRoot->student->studentID)
        return findStudent(studentRoot->left, studentID);
    else if(studentID > studentRoot->student->studentID)
        return findStudent(studentRoot->right, studentID);
    else
        return studentRoot;
}

//METHOD THAT PRINTS A MENU TO CHANGE STUDENT'S INFORMATION
SNode update(SNode studentRoot) {
    char stdName[MAX], city[MAX], date[MAX], classID[MAX];
    int option;
    int exitMenu = 0;  // Flag variable to control loop condition

    while (!exitMenu) {
        printf("ENTER WHAT YOU WANT TO UPDATE:\n");
        printf("1. Change student name.\n");
        printf("2. Change student city.\n");
        printf("3. Change current class ID.\n");
        printf("4. Change enrollment date.\n");
        printf("5. Exit.\n");

        scanf("%d", &option);  // OPTION FROM USER

        switch (option) {
            case 1:
                printf("Enter student name: ");
                scanf("%s", studentRoot->student->studentName);
                break;

            case 2:
                printf("Enter student city: ");
                scanf("%s", studentRoot->student->city);
                break;

            case 3:
                printf("Enter current class ID: ");
                scanf("%s", studentRoot->student->currentClassID);
                break;

            case 4:
                printf("Enter enrollment date: ");
                scanf("%s", studentRoot->student->enrollmentDate);
                break;

            case 5:
                exitMenu = 1;  //FLAG TO EXIT THE MENU
                break;

            default:
                printf("INVALID OPTION! PLEASE TRY AGAIN\n");
                printf("____________________\n");
                break;
        }
    }

    return studentRoot;
}

//HELPING METHOD (FOR DELETION) THAT FINDS THE MINIMUM NODE
SNode findMin(SNode t){
    if(t == NULL)
        return NULL;
    else if(t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

//METHOD TO DELETE THE STUDENT BY HER/HIS STUDENT ID
SNode deleteStudent(int studentID, SNode studentRoot) {
    if (studentRoot == NULL) {
        printf("STUDENT NOT FOUND!\n");
        return studentRoot;
    }

    if (studentID < studentRoot->student->studentID)
        studentRoot->left = deleteStudent(studentID, studentRoot->left);
    else if (studentID > studentRoot->student->studentID)
        studentRoot->right = deleteStudent(studentID, studentRoot->right);
    else {
        if (studentRoot->left && studentRoot->right) { // TWO CHILDREN
            SNode tempCell = findMin(studentRoot->right);
            studentRoot->student->studentID = tempCell->student->studentID;
            studentRoot->right = deleteStudent(tempCell->student->studentID, studentRoot->right);
        } else { //ONE OR ZERO CHILDREN
            SNode tempCell = studentRoot;
            if (studentRoot->left == NULL)
                studentRoot = studentRoot->right;
            else if (studentRoot->right == NULL)
                studentRoot = studentRoot->left;
            free(tempCell);
        }
    }

    return studentRoot;
}

//PRINT ALL STUDENTS INORDER TRAVERSAL
void listStudents(SNode studentRoot) {
    if(studentRoot != NULL){
        listStudents(studentRoot->left);
        printf("\nSTUDENT NAME: %s\n", studentRoot->student->studentName);
        printf("STUDENT ID: %d\n", studentRoot->student->studentID);
        printf("STUDENT CITY: %s\n", studentRoot->student->city);
        printf("CURRENT CLASS ID: %s\n", studentRoot->student->currentClassID);
        printf("ENROLLMENT DATE: %s\n", studentRoot->student->enrollmentDate);
        listStudents(studentRoot->right);
    }
}

////////////////////////////////////////////CASE 4///////////////////////////////////////////////////////
//FIND A STUDENT BY HER/HIS CITY
SNode findCity(SNode studentRoot, const char* city) {
    if (studentRoot == NULL)
        return NULL;

    int comparisonResult = strcasecmp(city, studentRoot->student->city);

    if (comparisonResult < 0)
        return findCity(studentRoot->left, city);
    else if (comparisonResult > 0)
        return findCity(studentRoot->right, city);
    else
        return studentRoot;
}

//METHOD THAT FINDS THE STUDENTS WITH THE SAME CITY AND LIST THEIR INFO
void listStudentsCity(SNode studentRoot, const char* city) {
    if (studentRoot == NULL)
        return;

    listStudentsCity(studentRoot->left, city);
    if (strcasecmp(studentRoot->student->city, city) == 0) {
        printf("\nSTUDENT NAME: %s\n", studentRoot->student->studentName);
        printf("STUDENT ID: %d\n", studentRoot->student->studentID);
        printf("STUDENT CITY: %s\n", studentRoot->student->city);
        printf("ENROLLMENT DATE: %s\n", studentRoot->student->enrollmentDate);
        printf("CURRENT CLASS ID: %s\n", studentRoot->student->currentClassID);
    }
    listStudentsCity(studentRoot->right, city);
}
////////////////////////////////////////////////SAVE TO FILE/////////////////////////////////////////////////
//SAVE THE TREE IN studentsData.txt FILE
void saveInFile(SNode studentRoot) {
    FILE* file = fopen("studentsData.txt", "w");
    if (file == NULL) {
        printf("FILE NOT FOUND!\n");
        return;
    }
    saveStudentsInfo(studentRoot, file);
    fclose(file);
}

//METHOD TO TRAVERSE THE TREE INORDER AND PRINT IN THE FILE
void saveStudentsInfo(SNode studentRoot, FILE* file) {
    if (studentRoot != NULL) {
        saveStudentsInfo(studentRoot->left, file);
        fprintf(file, "%d %s %s %s %s \n", studentRoot->student->studentID,
                 studentRoot->student->studentName,
                 studentRoot->student->city,
                 studentRoot->student->enrollmentDate,
                 studentRoot->student->currentClassID);
        saveStudentsInfo(studentRoot->right, file);
    }
}
////////////////////////////////////////////SORT//////////////////////////////////////////////////
SNode merge(SNode left, SNode right) {

    //RETURN THE SUBTREE IF THE OTHER ONE IS NULL
    if (left == NULL)
        return right;
    if (right == NULL)
        return left;

    SNode result = NULL; //CREATE A NEW SUBTREE

    //COMPARES THE STUDENT NAMES IN LEFT AND RIGHT
    if (strcmp(left->student->studentName, right->student->studentName) <= 0) {
        result = left;
        result->right = merge(left->right, right);
    } else {
        result = right;
        result->right = merge(left, right->right);
    }
    return result;  //RETURN THE SUBTREE WITH THE MERGED RESULTS
}

//A METHOD FOR SPLITTING THE TREE INTO TWO SUBTREES
void split(SNode source, SNode* front, SNode* back) {
    SNode fast, slow;
    slow = source;
    fast = source->right;

    while (fast != NULL) {
        fast = fast->right;
        if (fast != NULL) {
            slow = slow->right;
            fast = fast->right;
        }
    }

    *front = source;
    *back = slow->right;
    slow->right = NULL;
}

//A METHOD FOR SORTING THE TREE RECURSIVELY
void mergeSort(SNode* studentRoot) {
    SNode head = *studentRoot;
    SNode front, back;

    //BASE CASE: IF THERE IS NO STUDENTS OR JUST ONE
    if (head == NULL || head->right == NULL)
        return;

    split(head, &front, &back);

    mergeSort(&front);
    mergeSort(&back);

    *studentRoot = merge(front, back);
}
////////////////////////////////////////////////////CASE 5: CLASSES///////////////////////////////////////////
//METHOD TO TRAVERSE THE TREE AND SAVE THE CLASSID IN ARRAY
void saveClass(SNode root, char* classes[], int* index) {
    if (root != NULL) {
        saveClass(root->left, classes, index);
        classes[*index] = strdup(root->student->currentClassID);  //SAVE STUDENTS ID'S IN THE ARRAY
        (*index)++;
        saveClass(root->right, classes, index);
    }
}

//METHOD TO DELETE DUPLICATED ID CLASSES
void duplicates(char** classes, int* count) {
    for (int i = 0; i < (*count); i++) {
        if (classes[i] == NULL)   //IF THE STUDENT IS DELETED, SKIP IT
            continue;
        for (int j = i + 1; j < (*count); j++) {
            if (classes[j] == NULL)  //IF THE STUDENT IS DELETED, SKIP IT
                continue;
            if (strcmp(classes[i], classes[j]) == 0) {  //IF TWO STUDENTS HAVE THE SAME CLASSID, THEY ARE DUPLICATED
                free(classes[j]);   //DELETE THE DUPLICATED CLASSID
                classes[j] = NULL;
            }
        }
    }

    int index = 0;
     //KEEP TRAKING OF THE UNIQUE IDS AND UPDATE THE COUNT
    for (int i = 0; i < (*count); i++) {
        if (classes[i] != NULL) {
            classes[index++] = classes[i];
        }
    }
    (*count) = index;
}

//METHOD THAT FINDS THE STUDENTS WITH THE SAME CLASSID AND LIST THEIR INFO
void findClass(SNode studentRoot, char* classes) {
    if (studentRoot == NULL)
        return;

    findClass(studentRoot->left, classes);
    if (strcmp(studentRoot->student->currentClassID, classes) == 0) {
        printf("\nSTUDENT NAME: %s\n", studentRoot->student->studentName);
        printf("STUDENT ID: %d\n", studentRoot->student->studentID);
        printf("STUDENT CITY: %s\n", studentRoot->student->city);
        printf("ENROLLMENT DATE: %s\n", studentRoot->student->enrollmentDate);
    }
    findClass(studentRoot->right, classes);
}

//METHOD FOR PRINTING ID'S CLASSES
void listStudentsClasses(SNode root, char* classes[], int counter) {
    printf("CLASSES AVAILABLE:\n");
    for (int i = 0; i < counter; i++) {
        printf("\n%s:", classes[i]);
        findClass(root, classes[i]);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
//METHOD TO PRINT THE MENU
void menu(){
    printf("\nWELCOME TO MY STUDENT APPLICATION! PLEASE SELECT AN OPERATION: \n");
    printf("1. Insert a student with all its associated data.\n");
    printf("2. Find a student by his/her student ID\n");
    printf("3. List all students in lexicographic order of their names.\n");
    printf("4. Search for a city and list all students from that city in lexicographic order of their names.\n");
    printf("5. List all students by their class in lexicographic order of their names.\n");
    printf("6. Delete a student given his/her student ID.\n");
    printf("7. Save all students in file students.data.\n");
    printf("8. Exit\n");
}

//METHOD THAT CHECKS THE STUDENT ID
int checkID(SNode r, int id){
    if(r == NULL)
        return 0;

    if(r->student->studentID == id)
        return 1;

    else if(r->student->studentID > id)
        return checkID(r->left, id);

    else
        return checkID(r->right, id);
}

//READ THE FILE AND CONSTRUCT THE TREE
SNode loadStudents(SNode root, char file[]) {
    FILE* fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("ERROR IN OPENING THE FILE: %s\n", file);
        return root;  // Return the original root if file cannot be opened
    }

    int stdID;
    char stdName[MAX], city[MAX], date[MAX], classID[MAX];

    STD std;

    while (fscanf(fptr, "%d %499s %499s %499s %499s", &stdID, stdName, city, date, &classID) == 5) {
        std = createStudent(stdID, stdName, city, date, classID);
        root = insertStudent(&root, std);

        SNode node = findStudent(root, stdID);
        if (node != NULL) {
            strcpy(node->student->studentName, stdName);
            strcpy(node->student->city, city);
            strcpy(node->student->enrollmentDate, date);
            strcpy(node->student->currentClassID, classID);
        }
    }

    fclose(fptr);
    printf("\nDATA HAVE BEEN LOADED SUCCESSFULLY!\n");
    return root;
}
////////////////////////////////////////////////////////////////////////////////////////

int main(){
    SNode* root = NULL; //CREATING THE TREE

    int stdID;
    char stdName[MAX], city[MAX], date[MAX], classID[MAX];
    char file[40] = "studentsData.txt";
    root = loadStudents(root, file); //READ THE FILE AND CONSTRUCT THE TREE
    listStudents(root); //PRINT THE TREE

    int classCount = 0; //INITIALE VALUE FOR KEEP TRAKING THE NUMBER OF CURRENT CLASSES

    int select, updateSTD;

    while (1) {
        menu();
        scanf("%d", &select);  // OPTION FROM USER

        switch (select) {

            // INSERT A STUDENT
            case 1:
                printf("ENTER STUDENT ID: ");
                scanf("%d", &stdID);
                if (checkID(root, stdID) == 1) {
                    printf("STUDENT ALREADY EXISTS!");
                    break;
                }

                printf("ENTER STUDENT NAME: ");
                scanf("%s", stdName);

                printf("ENTER STUDENT CITY: ");
                scanf("%s", city);

                printf("ENTER STUDENT ENROLLMENT DATE: ");
                scanf("%s", date);

                printf("ENTER CURRENT CLASS ID: ");
                scanf("%s", classID);

                //INSERT STUDENT NODE WITH HER/HIS INFORMATION FROM THE USER
                STD newStudent = createStudent(stdID, stdName, city, date, classID);
                root = insertStudent(&root, newStudent);
                printf("\nSTUDENT ADDED SUCCESSFULLY!\n");

                printf("______________________________________\n");
                break;

            //FIND A STUDENT
            case 2:
                printf("ENTER STUDENT ID: ");
                scanf("%d", &stdID);
                SNode searchFound = findStudent(root, stdID);
                if(searchFound != NULL){
                    printf("STUDENT IS FOUND!\n");
                    printf("______________________________________\n");
                    printf("DO YOU WANT TO UPDATE THE STUDENT INFORMATION? IF NO, PRESS 0!\n");
                    scanf("%d", &updateSTD);
                    if(updateSTD != 0){  //IF THE STUDENT IS FOUND, UPDATE HER/HIS INFORMATION
                        SNode UPDATE = update(root);
                        printf("STUDENT INFORMATION HAS BEEN UPDATED!\n");
                        printf("______________________________________\n");
                        break;
                    }
                    else
                        break;
                }
                else{
                    printf("STUDENT IS NOT FOUND!\n");
                    printf("______________________________________\n");
                    break;
                }

                printf("______________________________________\n");
                break;

            //LIST ALL STUDENTS BY LEXICOGRAPHIC ORDER OF THEIR NAMES
            case 3:

                mergeSort(&root); //Sort the students' names using merge sort
                printf("STUDENTS BY LEXICOGRAPHIC ORDER OF THEIR NAMES:\n");
                listStudents(root);  //Traverse the tree in inorder and print their info
                printf("______________________________________\n");
                break;

            //SEARCH FOR A CITY
            case 4:
                printf("ENTER CITY TO SEARCH: ");
                scanf("%s",city);
                SNode findStdCity = findCity(root,city);
                if(findStdCity != NULL){
                    mergeSort(&root); //SORT STUDENTS' NAMES USING MERGE SORT
                    printf("STUDENTS BY LEXICOGRAPHIC ORDER OF THEIR NAMES FROM %s CITY:\n", city);
                    listStudentsCity(root,city);
                    break;
                }
                else{
                    printf("THERE IS NO STUDENTS FROM THIS CITY!\n");
                    break;
                }

                printf("______________________________________\n");
                break;

            //LIST ALL STUDENTS BY THEIR CLASS IN LEXICOGRAPHIC ORDER OF THEIR NAMES
            case 5:
                saveClass(root, classID, &classCount);
                duplicates(classID, &classCount);
                mergeSort(&root); //SORT STUDENTS' NAMES USING MERGE SORT
                listStudentsClasses(root, classID,classCount);
                break;

            //DELETE A STUDENT GIVEN HER/HIS STUDENT ID
            case 6:
                printf("ENTER STUDENT ID TO DELETE: ");
                scanf("%d", &stdID);
                if (checkID(root, stdID) == 0) {
                    printf("STUDENT IS NOT EXIST!\n");
                    printf("_______________________________\n");
                    break;
                }
                root = deleteStudent(stdID, root);
                printf("STUDENT HAD BEEN DELETED!\n");
                printf("_______________________________\n");
                break;

            //SAVE ALL STUDENTS IN studentsData.txt file
            case 7:
                saveInFile(root);
                printf("Students Information have been saved to studentsData.txt!\n");
                printf("__________________________\n");
                break;

            //EXIT
            case 8:
                printf("THANKS FOR USING MY PROGRAM!");
                exit(0);

            default:
                printf("INVALID OPTION! PLEASE TRY AGAIN\n");
                printf("______\n");
                break;
        }
    }

    return 0;
}