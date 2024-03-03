#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define PATH_LEN 1024

struct options {
    int show_files;
    int show_dirs;
    int show_links;
    int sort;
};

void dirwalk(const char *dir_path, int depth, struct options opt) {

    DIR *dir = opendir(dir_path);
    struct dirent *entry;

    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            for (int i = 0; i < depth; i++) {
                printf("  ");
            }

            if (opt.show_dirs) {
                printf("[%s]\n", entry->d_name);
            }

            char path[PATH_LEN];
            snprintf(path, PATH_LEN, "%s/%s", dir_path, entry->d_name);

            dirwalk(path, depth + 1, opt);
        } else if (entry->d_type == DT_REG && opt.show_files) {
            for (int i = 0; i < depth; i++) {
                printf("  ");
            }
            printf("%s\n", entry->d_name);
        } else if (entry->d_type == DT_LNK && opt.show_links) {
            for (int i = 0; i < depth; i++) {
                printf("  ");
            }
            printf("%s\n", entry->d_name);
        }
    }

    if (closedir(dir) == -1) {
        perror("Error closing directory");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {

    /*struct options opts = {0, 0, 0, 0};

    int option;

    while ((option = getopt(argc, argv, "ldfs")) != -1) {
        switch (option) {
            case 'l':
                opts.show_links = 1;
                break;
            case 'd':
                opts.show_dirs = 1;
                break;
            case 'f':
                opts.show_files = 1;
                break;
            case 's':
                opts.sort = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l] [-d] [-f] [-s]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (argc != 0) {
        opts = (struct options){1, 1, 1, 1};
    } */

    dirwalk("./", 0, (struct options){1, 1, 1, 0});

    return 0;
}
