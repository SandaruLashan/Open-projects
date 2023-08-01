//This code is totally free to modify and republish
//My Name is Sandaru Lashan Herman who made this code as a coursework
//Thank you

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

#define COLOR_RED     12
#define COLOR_GREEN   10
#define COLOR_YELLOW  14
#define COLOR_BLUE    9
#define COLOR_MAGENTA 13
#define COLOR_CYAN    11

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void option() {
     setConsoleColor(COLOR_CYAN);
     printf("\n  Available operations\n-----------------------------\n1. Create a folder\n2. Create a text file\n3. Write to a text file\n4. List the current directory\n5. Read a text file\n6. Delete a file\n7. Delete a folder\n8. Rename a file\n9. List folder contents\n10. Change the directory\n11. Show the current directory\n12. Show option\n13. Exit\n-----------------------------\n");
     setConsoleColor(15);
}
void banner(){
     setConsoleColor(COLOR_BLUE);
     printf("\t\t\t\t\t\t+----------------------------+\n\t\t\t\t\t\t|    File management system  |\n\t\t\t\t\t\t|\t\t\t     |\n\t\t\t\t\t\t|\t\t\t     |\n\t\t\t\t\t\t|\t version 1.0\t     |\n\t\t\t\t\t\t|By CT/2020/012 - Herman PSL |\n\t\t\t\t\t\t+----------------------------+\n\n\n\n"); // lebel
     setConsoleColor(15);
}
void createFolder(const char *folderName) {
    int result = mkdir(folderName);
    if (result == 0) {
        setConsoleColor(COLOR_GREEN);
        printf("\nFolder created successfully: %s\n", folderName);
        setConsoleColor(15);
    } else {
        setConsoleColor(COLOR_RED);
        printf("\nUnable to create folder: %s\n", folderName);
        setConsoleColor(15);
    }
}

void createTextFile(const char *fileName) {
FILE *file;
if (access(fileName, F_OK) == 0) {
    // File already exists
    setConsoleColor(COLOR_RED);
    printf("\nError: Text file '%s' already exists.\n", fileName);
    setConsoleColor(15);
} else {
    // File doesn't exist, create it
    file = fopen(fileName, "w");
    if (file) {
        setConsoleColor(COLOR_GREEN);
        printf("\nText file created successfully: %s\n", fileName);
        setConsoleColor(15);
        fclose(file);
    } else {
        setConsoleColor(COLOR_RED);
        printf("\nUnable to create text file: %s\n", fileName);
        setConsoleColor(15);
    }
}
}

void writeToFile(const char *fileName) {
    FILE *file = fopen(fileName, "a");
    if (file) {
        char text[1000];
        printf("Enter the text to write to the file (Ctrl+Z to stop):\n");
        while (fgets(text, sizeof(text), stdin) != NULL) {
            fprintf(file, "%s", text);
        }
        setConsoleColor(COLOR_GREEN);
        printf("\nText written to the file successfully.\n");
        setConsoleColor(15);
        fclose(file);
    } else {
        setConsoleColor(COLOR_RED);
        printf("\nUnable to open the file for writing.\n");
        setConsoleColor(15);
    }
}

void listDirectory() {
    DIR *directory = opendir(".");
    if (directory) {
        struct dirent *dirEntry;
        setConsoleColor(COLOR_RED);
        printf("Current directory\n");
        setConsoleColor(15);
        while ((dirEntry = readdir(directory)) != NULL) {
            setConsoleColor(COLOR_GREEN);
            printf("\t\t\t%s\n", dirEntry->d_name);
        }
        setConsoleColor(15);
        closedir(directory);
    } else {
        setConsoleColor(COLOR_RED);
        printf("Error opening the current directory.\n");
        setConsoleColor(15);

    }
}

void readFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file) {
        setConsoleColor(COLOR_RED);
        printf("\nContent of the file:\n");
        setConsoleColor(15);
        char ch;

        while ((ch = fgetc(file)) != EOF) {
            setConsoleColor(COLOR_GREEN);
            putchar(ch);

        }
        setConsoleColor(15);

        fclose(file);
    } else {
        printf("Unable to open the file for reading.\n");
    }
}

void deleteFile(const char *fileName) {
    int result = remove(fileName);
    if (result == 0) {
        setConsoleColor(COLOR_GREEN);
        printf("File deleted successfully: %s\n", fileName);
        setConsoleColor(15);
    } else {
        setConsoleColor(COLOR_RED);
        printf("Unable to delete file: %s\n", fileName);
        setConsoleColor(15);
    }
}

void deleteFolder(const char *folderName) {
    int result = rmdir(folderName);
    if (result == 0) {
        setConsoleColor(COLOR_GREEN);
        printf("Folder deleted successfully: %s\n", folderName);
        setConsoleColor(15);
    } else {
        setConsoleColor(COLOR_RED);
        printf("Unable to delete folder: %s\n", folderName);
        setConsoleColor(15);
    }
}

void renameFile(const char *oldName, const char *newName) {
    int result = rename(oldName, newName);
    if (result == 0) {
        printf("File renamed successfully: %s -> %s\n", oldName, newName);
    } else {
        printf("Unable to rename file: %s -> %s\n", oldName, newName);
    }
}

void listFolderContents(const char *folderName) {
    DIR *directory = opendir(folderName);
    if (directory) {
        setConsoleColor(COLOR_RED);
        printf("\nListing contents of folder '%s':\n", folderName);
        setConsoleColor(15);
        struct dirent *dirEntry;
        while ((dirEntry = readdir(directory)) != NULL) {
            if (strcmp(dirEntry->d_name, ".") != 0 && strcmp(dirEntry->d_name, "..") != 0) {
                setConsoleColor(COLOR_GREEN);
                printf("\t\t\t %s\n", dirEntry->d_name);
            }
        }
        setConsoleColor(15);
        closedir(directory);
    } else {
        printf("Unable to open the folder: %s\n", folderName);
    }
}
void changeDirectory() {
    char newDir[1024];
    printf("Enter the directory path to change to: ");
    fgets(newDir, sizeof(newDir), stdin);
    newDir[strcspn(newDir, "\n")] = '\0'; // Remove the trailing newline

    if (chdir(newDir) == 0) {
        setConsoleColor(COLOR_GREEN);
        printf("Successfully changed the current working directory to: %s\n", newDir);
        setConsoleColor(15);
    } else {
        setConsoleColor(COLOR_RED);
        perror("\nchdir() error\n");
        setConsoleColor(15);
        return 1;
    }

}
void ShowworkingDirectory(){
         char cwd[1024];
         if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    setConsoleColor(COLOR_YELLOW);
                    printf("Current working directory: %s\n", cwd);
                    setConsoleColor(15);
        } else {
                    setConsoleColor(COLOR_RED);
                    perror("getcwd() error");
                    setConsoleColor(15);
                    return 1;
        }
}
int main() {
    char input[100];
    int choice;
    banner();
    option();

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        setConsoleColor(COLOR_YELLOW);
        printf("\nCurrent working directory: %s\n", cwd);
        setConsoleColor(15);
    } else {
        setConsoleColor(COLOR_RED);
        perror("getcwd() error");
        setConsoleColor(15);
        return 1;
    }

    while (1) {
        printf("\nEnter your choice (1/2/.../11): ");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &choice) != 1) {
            setConsoleColor(COLOR_RED);
            printf("Invalid input. Please enter a number.\n");
            setConsoleColor(15);
            continue;
        }

        switch (choice) {
            case 1: {
                char folderName[100];
                printf("Enter the name of the folder to create: ");
                fgets(folderName, sizeof(folderName), stdin);
                folderName[strcspn(folderName, "\n")] = '\0';
                createFolder(folderName);
                break;
            }
            case 2: {
                char fileName[100];
                printf("Enter the name of the text file to create: ");
                fgets(fileName, sizeof(fileName), stdin);
                fileName[strcspn(fileName, "\n")] = '\0';
                createTextFile(fileName);
                break;
            }
            case 3: {
                char fileName[100];
                printf("Enter the name of the text file to write: ");
                fgets(fileName, sizeof(fileName), stdin);
                fileName[strcspn(fileName, "\n")] = '\0';
                writeToFile(fileName);
                break;
            }
            case 4:
                listDirectory();
                break;
            case 5: {
                char fileName[100];
                printf("Enter the name of the text file to read: ");
                fgets(fileName, sizeof(fileName), stdin);
                fileName[strcspn(fileName, "\n")] = '\0';
                readFile(fileName);
                break;
            }
            case 6: {
                char fileName[100];
                printf("Enter the name of the file to delete: ");
                fgets(fileName, sizeof(fileName), stdin);
                fileName[strcspn(fileName, "\n")] = '\0';
                deleteFile(fileName);
                break;
            }
            case 7: {
                char folderName[100];
                printf("Enter the name of the folder to delete: ");
                fgets(folderName, sizeof(folderName), stdin);
                folderName[strcspn(folderName, "\n")] = '\0';
                deleteFolder(folderName);
                break;
            }
            case 8: {
                char oldName[100], newName[100];
                printf("Enter the name of the file to rename: ");
                fgets(oldName, sizeof(oldName), stdin);
                oldName[strcspn(oldName, "\n")] = '\0';
                printf("Enter the new name for the file: ");
                fgets(newName, sizeof(newName), stdin);
                newName[strcspn(newName, "\n")] = '\0';
                renameFile(oldName, newName);
                break;
            }
            case 9: {
                char folderName[100];
                printf("Enter the name of the folder to show its contents: ");
                fgets(folderName, sizeof(folderName), stdin);
                folderName[strcspn(folderName, "\n")] = '\0';
                listFolderContents(folderName);
                break;
            }
            case 10:
                changeDirectory();
                break;
            case 11:
                ShowworkingDirectory();
                break;
            case 12:
                option();
                break;
            case 13:
                setConsoleColor(COLOR_BLUE);
                printf("Exiting the File Management System.\n");
                setConsoleColor(15);
                exit(0);
                break;
            default:
                setConsoleColor(COLOR_RED);
                printf("Invalid choice. Please select a valid option.\n");
                setConsoleColor(15);
                break;
        }
    }

    return 0;
}
