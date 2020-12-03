#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
 
#define FILE 8
#define DIRNO 4

typedef struct {
    int dir;
    int file;
} summary;

void print_summary ( summary *S ) {
    printf ("[Summary - Directories %d, Files: %d]\n", S->dir, S->file);
}

int walk( char path[], summary *S ) {

    struct dirent *pDirent;

    DIR *pDir;    
    pDir = opendir(path);
    char *cwd;

    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", path);
        return 1;
    }

    while ((pDirent = readdir(pDir)) != NULL) {

            // Skip . and ..
            if ( strcmp(pDirent->d_name, ".") == 0) {
                continue;
            }

            if ( strcmp(pDirent->d_name, "..") == 0) {
                continue;
            }
            
            cwd = (char*)malloc( sizeof(char) + strlen(pDirent->d_name) + strlen(path) + 1);

            strncpy(cwd, path, strlen(path) + 1);
            strcat(cwd, pDirent->d_name);
   
            if (pDirent->d_type == FILE) {
                printf ("[File Found: %s, type: %d, Path: %s]\n", pDirent->d_name, pDirent->d_type, cwd);
                S->file++;
            }

            if (pDirent->d_type == DIRNO) {

                strcat(cwd, "/");
                printf ("[Dir Found: %s, type: %d, Path: %s]\n", pDirent->d_name, pDirent->d_type, cwd);

                S->dir++;

                walk(cwd, S);
            }
    
            //printf ("!! Freeing memory for Path: %s]\n", cwd);
            free(cwd);
    }

    closedir (pDir);
    return 0;
}

int main(int argc, const char *argv[]) {

    summary S = { 0, 0 };
    summary *sum;
 
    char dir[] = "/";
    walk(dir, &S); 

    print_summary(&S);

    return 0;
}
