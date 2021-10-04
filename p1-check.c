/*
 * CS 261 PA1: Mini-ELF header verifier
 *
 * Name: Adrien Ponce
 */

#include <getopt.h>
#include "p1-check.h"
#include "elf.h"

#define BUF_SIZE 1024
#define ELF_HEAD_SIZE 16 // size of a complete header (16 bytes)

/**********************************************************************
 *                         REQUIRED FUNCTIONS
 *********************************************************************/

bool read_header (FILE *file, elf_hdr_t *hdr)
{
    // check that the file & header exists
    if (!file || !hdr) {
        return false;
    }

    // go to the front of the file
    rewind(file);
    if (fread(hdr, sizeof(elf_hdr_t), 1, file)  != 1) {
        return false;
    }

    // check for the magic number at the end of the header
    if (hdr->magic == 0x00464C45) {
        return true;
    }

    return false;
}

/**********************************************************************
 *                         OPTIONAL FUNCTIONS
 *********************************************************************/

void usage_p1 (char **argv)
{
    printf("Usage: %s <option(s)> mini-elf-file\n", argv[0]);
    printf(" Options are:\n");
    printf("  -h      Display usage\n");
    printf("  -H      Show the Mini-ELF header\n");
}

bool parse_command_line_p1 (int argc, char **argv, bool *print_header, char **filename)
{
    // check for valid command line arguments
    if (!argv || !print_header || !filename) {
        return false;
    }

    opterr = 0;
    char opt;
    *print_header = false;
    char* optstr = "Hh";
    *filename = NULL;
    // check the flags
    while ((opt = getopt(argc, argv, optstr)) != -1) {
        switch(opt) {
            case 'h': /// p usage
                usage_p1(argv);
                *print_header = false;
                return true;
            case 'H': // dump
                *print_header = true;
                break;
            default: // always print usage
                usage_p1(argv);
                *print_header = false;
                return false;
        }
    }
    // filename does not exist
    if (optind != argc - 1) {
        usage_p1(argv);
        return false;
    }
    // initialize filename
    *filename = argv[optind];
    return true;
}

void dump_header (elf_hdr_t hdr)
{
    int i = 0;
    // loop while size = 16
    while (i < sizeof(elf_hdr_t)) {
        for (int k = 0; k < 16 && i < sizeof(elf_hdr_t); k++) {
            // add space after if before
            if (k < 15) {
                printf("%02x ", ((uint8_t*)&hdr)[k]);
            } else {
                printf("%02x", ((uint8_t*)&hdr)[k]);
            }
            // middle of header, need space
            if (k == 7) {
                printf(" ");
            }
            i++;
        }
        // weird bug checking
        printf("\n");
    }

    printf("Mini-ELF version %d\n", hdr.e_version);
    printf("Entry point 0x%x\n", hdr.e_entry);
    printf("There are %d program headers, starting at offset %d (0x%x)\n", hdr.e_num_phdr,
           hdr.e_phdr_start, hdr.e_phdr_start);
    if (hdr.e_symtab != 0) {
        printf("There is a symbol table starting at offset %d (0x%x)\n", hdr.e_symtab, hdr.e_symtab);
    } else {
        printf("There is no symbol table present\n");
    }

    if (hdr.e_strtab) {
        printf("There is a string table starting at offset %d (0x%x)\n", hdr.e_strtab, hdr.e_strtab);
    } else {
        printf("There is no string table present\n");
    }


}

