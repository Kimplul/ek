/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

/**
 * @file main.c
 *
 * Compiler main file, controls compilation and command line
 * handling.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <ek/debug.h>
#include <ek/imports.h>
#include <ek/compiler.h>

/**
 * String describing compiler usage.
 * @todo I suspect backends might want more flags, come up with
 * some way to make flag handling more generic
 */
static const char *cmdline_usage =
	"ek compiler usage:\n"
	" ek [-I <dir>...] [-o <outfile>] infile\n"
	"	-h            Show usage (this)\n"
	"	-I <dir>      Add directory to import path\n"
	"	infile        Top file(s) to compile\n"
	"	-o <outfile>  Name of output assembly file\n"
	"	              (infile minus file extension if not given)\n"
;

/** Print usage of compiler. */
static void usage()
{
	fprintf(stderr, cmdline_usage);
}

/**
 * Main entry to compiler.
 * Checks command line parameters and drives the rest of the compiler.
 * Feels kind of weird documenting main, but doxygen warns about not
 * doing it so whatever.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int main(int argc, char *argv[])
{
	int opt;
	const char *output = "e.out";
	while ((opt = getopt(argc, argv, "hI:o:")) != -1) {
		switch (opt) {
		case 'o':
			output = optarg;
			break;

		case 'I':
			add_import_path(optarg);
			break;

		case 'h':
			usage();
			exit(EXIT_SUCCESS);

		default:
			usage();
			exit(EXIT_FAILURE);
		}
	}

	if (optind >= argc) {
		error("no input file");
		usage();
		exit(EXIT_FAILURE);
	}

	if (optind != argc - 1) {
		error("too many arguments");
		usage();
		exit(EXIT_FAILURE);
	}

	const char *input = argv[optind];
	return compile(input, output);
}
