#include <stdio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/param.h>
#include <unistd.h>

#define NAME_PROGRAM 0
#define PATH_ENVIRONMENT_FILE 1
#define NAME_BUTTON 2
#define INITIAL_SIZE 7
#define MAX_LEN_FILE_STR 255

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

int findChildPathEnvp(char **envp, const char *name_variable)
{
    size_t ind = 0;
    size_t len = strlen(name_variable);

    int flag_find = 0;

    while (envp[ind])
    {
        flag_find = 1;
        for (size_t i = 0; i < len; ++i)
        {
            if (envp[ind][i] != name_variable[i])
            {
                flag_find = 0;
                break;
            }
        }

        if (flag_find == 1)
            break;

        ind++;
    }

    if (flag_find == 0)
        return 0;

    size_t path_len = strlen(name_variable);
    size_t find_str_len = strlen(envp[ind]);

    for (size_t i = path_len + 1; i < find_str_len; ++i)
    {
        printf("%c", envp[ind][i]);
    }

    printf("\n");

    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    printf("NAME PROGRAM: %s\n", argv[NAME_PROGRAM]);
    printf("PID PROGRAM: %d\n", getpid());
    printf("PPID PROGRAM: %d\n", getppid());

    char **array_variables = (char **)calloc(INITIAL_SIZE, sizeof(char *));

    if (getVariables(argv[PATH_ENVIRONMENT_FILE], &array_variables))
    {
        if (strcmp(argv[NAME_BUTTON], "+") == 0)
        {
            for (size_t i = 0; i < INITIAL_SIZE; ++i)
                printf("%s\n", getenv(array_variables[i]));
        }

        else if (strcmp(argv[NAME_BUTTON], "*") == 0)
        {
            for (size_t i = 0; i < INITIAL_SIZE; ++i)
            {
                findChildPathEnvp(envp, array_variables[i]);
                printf("%s\n", getenv(array_variables[i]));
            }
        }

        else if (strcmp(argv[NAME_BUTTON], "&") == 0)
        {
            for (size_t i = 0; i < INITIAL_SIZE; ++i)
            {
                findChildPathEnvp(envp, array_variables[i]);
                printf("%s\n", getenv(array_variables[i]));
            }
        }
    }

    for (size_t i = 0; i < INITIAL_SIZE; ++i)
        free(array_variables[i]);

    free(array_variables);

    return 0;
}
