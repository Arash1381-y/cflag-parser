#ifndef CFLAG_PARSER_FLAG_PARSER_H
#define CFLAG_PARSER_FLAG_PARSER_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

// create an enum for field types (only number, string and double are supported)
typedef enum field_type {
    INT16_T = 16,
    INT32_T = 32,
    INT64_T = 64,
    FLOAT,
    DOUBLE,
    STRING,
    NO_VAL
} field_type_t;


typedef struct Flag {
    const char *name;               // option struct field
    int has_arg;                    // option struct field
    int val;                        // option struct field

    void *save;                     // pointer to the variable that will store the value
    field_type_t type;              // type of the flag

    const char *help;               // help message
    bool present;                   // whether the flag was used
} Flag;

void print_usage(const char *program_name);

void parse_flags(int argc, char *argv[], Flag *flags, int size, const char *usage);

#endif //CFLAG_PARSER_FLAG_PARSER_H
