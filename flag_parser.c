#include <string.h>
#include "flag_parser.h"


#define BYTE_SIZE 8


void save(Flag *flags, const char *usage, void *temp, const char *endptr, int j, int size);

void print_usage(const char *help) {
    printf("%s\n", help);
}


void parse_flags(int argc, char *argv[], Flag *flags, int size, const char *usage) {
    // create a list of options based on the flags

    struct option long_options[size + 2];
    for (int i = 0; i < size; i++) {
        flags[i].present = 0;
        long_options[i].name = flags[i].name;
        long_options[i].has_arg = flags[i].has_arg;
        long_options[i].flag = 0;
        long_options[i].val = flags[i].val;
    }


    long_options[size].name = "help";
    long_options[size].has_arg = 2;
    long_options[size].flag = 0;
    long_options[size++].val = 'h';

    long_options[size].name = 0;
    long_options[size].has_arg = 0;
    long_options[size].flag = 0;
    long_options[size].val = 0;


    int i = 0;
    int64_t temp_i;
    float temp_f;
    double temp_d;
    bool find;

    // parse the options
    int c;
    char *endptr;
    while ((c = getopt_long(argc, argv, "", long_options, 0)) != -1) {
        if (c == 'h') {
            print_usage(usage);
            exit(EXIT_SUCCESS);
        }

        for (int j = 0; j < size; j++) {
            find = false;
            if (c == flags[j].val) {
                find = true;
                switch (flags[j].type) {
                    case INT16_T:
                    case INT32_T:
                    case INT64_T:
                        temp_i = strtoll(optarg, &endptr, 10);
                        save(flags, usage, &temp_i, endptr, j, flags[j].type);

                        j = size;
                        break;
                    case FLOAT:
                        temp_f = strtof(optarg, &endptr);
                        save(flags, usage, &temp_f, endptr, j, sizeof(float));

                        j = size;
                        break;
                    case DOUBLE:
                        temp_d = strtod(optarg, &endptr);
                        save(flags, usage, &temp_d, endptr, j, sizeof(double));

                        j = size;
                        break;
                    case STRING:
                        *(char **) flags[j].save = optarg;
                        flags[j].present = 1;

                        j = size;
                        break;
                    case NO_VAL:
                        *(bool *) flags[j].save = true;
                        flags[j].present = 1;

                        j = size;
                        break;
                }
            }
        }
        if (!find) {
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }

    // check if all required flags are present
    for (int j = 0; j < size - 1; j++) {
        if (flags[j].has_arg == required_argument && flags[j].present == 0) {
            fprintf(stderr, "%s: missing required option '--%s'\n", argv[0], flags[j].name);
            exit(EXIT_FAILURE);

        }
    }
}

void save(Flag *flags, const char *usage, void *temp, const char *endptr, int j, int size) {
    if (endptr == optarg) {
        printf("Invalid Flag Format!");
        print_usage(usage);
        exit(EXIT_FAILURE);
    } else if (*endptr != '\0') {
        printf("Conversion stopped!");
        print_usage(usage);
        exit(EXIT_FAILURE);
    } else {
        memcpy(flags[j].save, temp, size / BYTE_SIZE);
    }
    flags[j].present = 1;
}
