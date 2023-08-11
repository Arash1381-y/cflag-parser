#ifndef CFLAG_PARSER_FLAG_PARSER_H
#define CFLAG_PARSER_FLAG_PARSER_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// create an enum for field types (only number, string and double are supported)
typedef enum field_type {
    NUMBER,
    STRING,
    DOUBLE
} field_type_t;


typedef struct Flag {
    const char *name; // name of the flag
    int has_arg; // required_argument, no_argument, or optional_argument
    void *save;
    field_type_t type; // type of the flag
    int val; // defined flag
    const char *help; // help message
    bool present; // whether the flag was used
} Flag;

void print_usage(const char *program_name, Flag *flags);

void parse_flags(int argc, char *argv[], Flag *flags, int size);

#endif //CFLAG_PARSER_FLAG_PARSER_H
