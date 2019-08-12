#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig.h>

void print_usage(char *prg)
{
    fprintf(stderr, "\nUsage: %s <file> <path> <type>\n", prg);
    fprintf(stderr, "file - Libconfig syntax compatybile file.\n");
    fprintf(stderr, "path - Path to the exact setting.\n");
    fprintf(stderr, "type - Type of setting [int|int64|float|bool|string].\n");
    fprintf(stderr, "Examples:\n");
    fprintf(stderr, "%s sample.cfg users.[0].surnme string (matches 'surname' of first user in 'users' group)\n", prg);
    fprintf(stderr, "\n");
}

int main(int argc, char **argv)
{
    config_t cfg;
    config_setting_t *setting;
    const char *str;
    char *file_name;
    char *setting_path;
    char *setting_type;

    if (4 != argc) {
        print_usage("lcfglookup");
        exit(0);
    }

    file_name = argv[1];
    setting_path = argv[2];
    setting_type = argv[3];

    config_init(&cfg);

    /* Read the file. If there is an error, report it and exit. */
    if(! config_read_file(&cfg, file_name))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return(EXIT_FAILURE);
    }

    /* Chech if setting exist */
    if (config_lookup(&cfg, setting_path) == NULL)
    {
        fprintf(stderr, "No '%s' setting in configuration file.\n", setting_path);
        return(EXIT_FAILURE);
    }

    if (strcmp(setting_type, "int") == 0)
    {
        int value;
        if (config_lookup_int(&cfg, setting_path, &value)) {
            printf("%d", value);
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Setiing '%s' is not %s.\n", setting_path, setting_type);
            return EXIT_FAILURE;
        }
    }
    else if (strcmp(setting_type, "int64") == 0)
    {
        long long value;
        if (config_lookup_int64(&cfg, setting_path, &value)) {
            printf("%lld", value);
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Setiing '%s' is not %s.\n", setting_path, setting_type);
            return EXIT_FAILURE;
        }
    }
    else if (strcmp(setting_type, "float") == 0)
    {
        double value;
        if (config_lookup_float(&cfg, setting_path, &value)) {
            printf("%f", value);
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Setiing '%s' is not %s.\n", setting_path, setting_type);
            return EXIT_FAILURE;
        }
    }
    else if (strcmp(setting_type, "bool") == 0)
    {
        int value;
        if (config_lookup_bool(&cfg, setting_path, &value)) {
            value ? printf("true") :  printf("false");
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Setiing '%s' is not %s.\n", setting_path, setting_type);
            return EXIT_FAILURE;
        }
    }
    else if (strcmp(setting_type, "string") == 0)
    {
        const char *str;
        if (config_lookup_string(&cfg, setting_path, &str)) {
            printf("%s", str);
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Setiing '%s' is not %s.\n", setting_path, setting_type);
            return EXIT_FAILURE;
        }
    }

    fprintf(stderr, "Not supported type '%s'.\n", setting_type);
    return EXIT_FAILURE;
}
