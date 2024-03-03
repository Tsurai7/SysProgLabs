#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 200

void dirwalk(const char *dirPath, int showDirs, int showFiles, int showLinks) {

    DIR *dir = opendir(dirPath);

    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char fullPath[PATH_MAX];

        snprintf(fullPath, PATH_MAX, "%s/%s", dirPath, entry->d_name);

        if (entry->d_type == DT_DIR) {
            if (showDirs) {
                printf("%s\n", fullPath);
            }

            dirwalk(fullPath, showDirs, showFiles, showLinks);
        }

        else if (entry->d_type == DT_REG && showFiles) {
            printf("%s\n", fullPath);
        }

        else if (entry->d_type == DT_LNK && showLinks) {
            printf("%s\n", fullPath);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {

    const char *dirPath = argc > 1 ? argv[1] : ".";

    int showDirs = 1;
    int showFiles = 1;
    int showLinks = 1;

    int option;

    while ((option = getopt(argc, argv, "ldf")) != -1) {
        switch (option) {
            case 'l':
                showDirs = 0;
                break;
            case 'd':
                showDirs = 1;
                showFiles = 0;
                break;
            case 'f':
                showDirs = 0;
                showFiles = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [dir] [-l] [-d] [-f]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    dirwalk(dirPath, showDirs, showFiles, showLinks);

    return 0;
}