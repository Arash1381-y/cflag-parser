#include "flag_parser.h"


void print_usage(const char *help, const struct Flag *flags) {
    printf("%s\n", help);
    printf("Options:\n");
    for (int i = 0; flags[i].name != NULL; i++) {
        printf("--%s : ", flags[i].name);
        if (flags[i].has_arg == required_argument) {
            printf("required argument");
        } else if (flags[i].has_arg == optional_argument) {
            printf("optional argument");
        } else {
            printf("no argument");
        }
        printf("\n");

    }
}


void parse_flags(int argc, char *argv[], const struct Flag *flags, int size) {
    // create a list of options based on the flags


    struct option long_options[size];
    int i = 0;
    for (int j = 0; flags[j].name != NULL; j++) {
        long_options[i].name = flags[j].name;
        long_options[i].has_arg = flags[j].has_arg;
        long_options[i].flag = 0;
        long_options[i].val = flags[j].val;
        i++;
        //printf("flags[%d].name = %s\n", j, flags[j].name);

    }

    // parse the options and check if required flags are present
    int c;
    int option_index = 0;
    while ((c = getopt_long(argc, argv, "", long_options, &option_index)) != -1) {
        for (int j = 0; flags[j].name != NULL; j++) {
            if (c == flags[j].val) {
                switch (flags[j].type) {
                    case NUMBER:
                        *(int *) flags[j].save = atoi(optarg);
                        break;
                    case STRING:
                        *(char **) flags[j].save = optarg;
                        break;
                    case DOUBLE:
                        *(double *) flags[j].save = atof(optarg);
                        break;
                }
            }
        }
    }

    // check if all required flags are present
    for (int j = 0; flags[j].name != NULL; j++) {
        if (flags[j].has_arg == required_argument && *(int *) flags[j].save == 0) {
            printf("Missing required flag: --%s\n", flags[j].name);
            print_usage(flags->help, flags);
            exit(1);
        }
    }
}