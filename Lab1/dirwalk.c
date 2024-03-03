#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 200

void walk_directory(const char *dir_path, int show_dirs, int show_files, int show_links) {
    DIR *dir = opendir(dir_path);

    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[PATH_MAX];
        snprintf(full_path, PATH_MAX, "%s/%s", dir_path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            if (show_dirs) {
                printf("%s\n", full_path);
            }
            walk_directory(full_path, show_dirs, show_files, show_links);
        } else if (entry->d_type == DT_REG && show_files) {
            printf("%s\n", full_path);
        } else if (entry->d_type == DT_LNK && show_links) {
            printf("%s\n", full_path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *dir_path = argc > 1 ? argv[1] : ".";

    int show_dirs = 1;
    int show_files = 1;
    int show_links = 1;

    int option;

    while ((option = getopt(argc, argv, "ldf")) != -1) {
        switch (option) {
            case 'l':
                show_links = 0;
                break;
            case 'd':
                show_dirs = 1;
                show_files = 0;
                break;
            case 'f':
                show_dirs = 0;
                show_files = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [dir] [-l] [-d] [-f]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    walk_directory(dir_path, show_dirs, show_files, show_links);

    return 0;
}