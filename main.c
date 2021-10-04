/*
 * CS 261: Main driver
 *
 * Name: Adrien Ponce
 */

#include "p1-check.h"
#include "elf.h"

int main (int argc, char **argv)
{
    char *fn;
    bool exists;
    struct elf hdr;

    if (!parse_command_line_p1(argc, argv, &exists, &fn)) {
        exit(EXIT_FAILURE);
    } else if (fn == NULL) {
        exit(EXIT_FAILURE);
    } else if (!exists && fn == NULL) {
        exit(EXIT_FAILURE);
    }

    // open file from command line
    FILE *fp = fopen(fn, "rb");

    if (!fp || !read_header(fp, &hdr)) {
        puts("Failed to read file");
        exit(EXIT_FAILURE);
    } else if (fp != NULL && exists) {
        dump_header(hdr);
        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}

