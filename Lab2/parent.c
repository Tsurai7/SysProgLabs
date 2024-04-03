#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define INITIAL_SIZE 7
#define MAX_LEN_FILE_STR 255
#define ENVIRONMENT_VALUE_CHILD "CHILD_PATH"
#define NAME_BUTTON 2
#define NAME_PROGRAM 0
#define PATH_ENVIRONMENT_FILE 1

int compare(const void *a, const void *b)
{
    return strcoll((const char *)a, (const char *)b);
}

int getVariables(const char *path, char ***buffer)
{
    FILE *file = NULL;

    if ((file = fopen(path, "r")) != NULL)
    {

        size_t ind = 0;
        size_t cnt = INITIAL_SIZE;

        while (cnt--)
        {
            (*buffer)[ind] = (char *)realloc((*buffer)[ind], (MAX_LEN_FILE_STR + 1) * sizeof(char));
            fscanf(file, "%s", (*buffer)[ind++]);
        }

        fclose(file);

        return 1;
    }

    perror("File error");

    return 0;
}

int findChildPathEnvp(char **envp, char **path_child)
{
    size_t ind = 0;
    size_t len = strlen(ENVIRONMENT_VALUE_CHILD);

    int flag_find = 0;

    while (envp[ind])
    {
        flag_find = 1;
        for (size_t i = 0; i < len; ++i)
        {
            if (envp[ind][i] != ENVIRONMENT_VALUE_CHILD[i])
            {
                flag_find = 1;
                break;
            }
        }
        if (flag_find == 1)
            break;
        ind++;
    }

    if (flag_find == 0)
        return 0;

    printf("%s\n", envp[ind]);

    size_t path_len = strlen(ENVIRONMENT_VALUE_CHILD);
    size_t find_str_len = strlen(envp[ind]);

    *path_child = (char *)malloc(find_str_len - (path_len + 1) + 1);

    size_t j = 0;

    for (size_t i = path_len + 1; i < find_str_len; ++i)
    {
        (*path_child)[j++] = envp[ind][i];
    }

    path_child[ind] = '\0';
    return 1;
}

void incrementChild(char **file_name)
{
    if ((*file_name)[7] == '9')
    {
        (*file_name)[7] = '0';
        (*file_name)[6]++;

        return;
    }

    (*file_name)[7]++;
}

int main(int argc, char *argv[], char *envp[])
{
    setlocale(LC_COLLATE, "C");

    char *path = argv[PATH_ENVIRONMENT_FILE];
    char **array_variables = (char **)calloc(INITIAL_SIZE, sizeof(char *));
    int flag_alloc_memory = 0;

    if (getVariables(path, &array_variables))
    {
        flag_alloc_memory = 1;

        qsort(array_variables, INITIAL_SIZE, sizeof(char *), compare);

        for (size_t i = 0; i < INITIAL_SIZE; ++i)
            printf("%s\n", array_variables[i]);

        char *child_name = (char *)malloc(9);
        strcpy(child_name, "child_00");
        char *newargv[] = {child_name, path, NULL, NULL};

        do
        {
            int ch = getchar();

            switch (ch)
            {
            case '+':
            {
                pid_t pid = fork();
                newargv[NAME_BUTTON] = "+";

                if (pid == 0)
                {
                    const char *path_child = getenv(ENVIRONMENT_VALUE_CHILD);
                    execve("./child", newargv, envp);
                }
                else
                    incrementChild(&child_name);

                break;
            }

            case '*':
            {
                pid_t pid = fork();
                newargv[NAME_BUTTON] = "*";

                if (pid == 0)
                {
                    const char *path_child = getenv(ENVIRONMENT_VALUE_CHILD);
                    execve("./child", newargv, envp);
                }
                else
                    incrementChild(&child_name);

                break;
            }

            case '&':
            {
                pid_t pid = fork();
                newargv[NAME_BUTTON] = "&";

                if (pid == 0)
                {
                    const char *path_child = getenv(ENVIRONMENT_VALUE_CHILD);
                    execve("./child", newargv, envp);
                }
                else
                    incrementChild(&child_name);

                break;
            }

            case 'q':
            {
                return 0;
            }

            default:
            {
                printf("Unknown command\n");
                break;
            }
            }
        } while (1);

        free(child_name);
    }

    if (flag_alloc_memory)
    {
        for (size_t i = 0; i < INITIAL_SIZE; ++i)
            free(array_variables[i]);
    }

    free(array_variables);

    return 0;
}
