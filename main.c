#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include "flag_parser.h"


int main(int argc, char *argv[]) {

    int16_t threads;
    int16_t optional_int;
    int16_t array_size;

    const char *Usage = "Usage: program_name [OPTIONS]\n\n"
                        "Description:\n"
                        "  This program demonstrates flag parsing using the flag_parser library.\n\n"
                        "Options:\n"
                        "--threads NUM                         Number of threads to use (required, range: -32,768 to 32,767)\n"
                        "--optional_int [NUM]                  Optional integer value (default: 0, range: -32,768 to 32,767)\n"
                        "--array_size NUM                      Size of the array (required, range: -32,768 to 32,767)\n"
                        "--help                                Display this help message and exit\n\n"
                        "Usage Examples:\n"
                        "  program_name -t 4 -a 100            # Run with 4 threads and array size 100\n"
                        "  program_name --optional_int 42      # Run with optional integer set to 42\n"
                        "  program_name -t 8 -a 256 -o 123     # Run with 8 threads, array size 256, and optional int 123\n";



    // Define the flags
    struct Flag flags[] = {
            {"threads",      required_argument, 't', &threads,      INT16_T, "Number of threads"},
            {"optional-int", optional_argument, 'o', &optional_int, INT16_T, "Optional int"},
            {"array-size",   required_argument, 'a', &array_size,   INT16_T, "Size of the array"},
    };


    // Parse flags
    parse_flags(argc, argv, flags, sizeof(flags) / sizeof(flags[0]), Usage);

    // Print the flags
    printf("threads = %d\n", threads);
    printf("optional-int = %d\n", optional_int);
    printf("array-size = %d\n", array_size);

    return 0;
}
