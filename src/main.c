#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <ct/ctpp.h>
#include <ct/debug.h>
#include <ct/imports.h>
#include <ct/compiler.h>

static const char *cmdline_usage =
"C with traits compiler usage:\n"
" ct [-I <dir>...] [-D <var>...] infile...\n"
"	-h       Show usage (this)\n"
"	-I <dir> Add directory to import path\n"
"	-D <var> Add predefined variable\n"
"	infile   Top file to compile\n"
;

static void usage()
{
	fprintf(stderr, cmdline_usage);
}

int main(int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "hI:D:")) != -1) {
		switch (opt) {
		case 'I':
			add_import_path(optarg);
			break;

		case 'D':
			add_predefined_variable(optarg);
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
		error("no input files\n");
		exit(EXIT_FAILURE);
	}

	for (int i = optind; i < argc; ++i) {
		debug("starting compilation of '%s'\n", argv[i]);
		compile(argv[i]);
	}

	return 0;
}
