#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <locale.h>


struct options {
    int show_files;
    int show_dirs;
    int show_links;
    int sort;
};


struct option long_options[] = {
    {"show_links", no_argument, 0, 'l'},
    {"show_dirs", no_argument, 0, 'd'},
    {"show_files", no_argument, 0, 'f'},
    {"sort", no_argument, 0, 's'},
    {0, 0, 0, 0}
};


int comparer(const struct dirent** first, const struct dirent** second) {
    return strcoll((*first)->d_name, (*second)->d_name);
}


void dirwalk(char *dir_path,  struct options *opts) {
    struct dirent** entries;

    int res = scandir(dir_path, &entries, NULL, opts->sort ? &comparer : NULL);

    if (res == -1) {
        printf("Error opening directory %s\n", dir_path);
        return;
    }

    for (int i = 0; i < res; ++i) {
        struct dirent *entry = entries[i];

        if (entry->d_type == DT_DIR &&
            (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0))
                continue;

        char* new_path = calloc(strlen(dir_path) + strlen(entry->d_name) + 2,sizeof(char));
        strcpy(new_path, dir_path);
        strcat(new_path, "/");
        strcat(new_path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            dirwalk(new_path, opts);
        }

        if (opts->show_files == 1 && entry->d_type == DT_REG) {
            printf("File: %s\n", entry->d_name);
        }

        else if(opts->show_dirs == 1 && entry->d_type == DT_DIR) {
            printf("[%s]\n", entry->d_name);
        }

        else if(opts->show_links && entry->d_type == DT_LNK) {
            printf("Link: %s\n", entry->d_name);
        }

        free(entry);
        free(new_path);
    }

    free(entries);
}


int main(int argc, char *argv[]) {
    setlocale(LC_COLLATE, "");
    struct options opts = {0, 0, 0, 0};
    int option_index;
    int option;

    while ((option = getopt_long(argc, argv, "ldfs", long_options, &option_index)) != -1) {
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
                printf("Usage: path [-l] [-d] [-f] [-s]\n");
                break;
        }
    }

    if (argc < 3) {
        opts = (struct options){1, 1, 1, 1};
        dirwalk("./", &opts);
        return 0;
    }

    dirwalk(argv[optind], &opts);

    return 0;
}