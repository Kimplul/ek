#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <cu/debug.h>
#include <cu/imports.h>
#include <cu/compiler.h>

static const char *cmdline_usage =
"Copper compiler usage:\n"
" cu [-I <dir>...] [-D <var>...] infile...\n"
"	-h       Show usage (this)\n"
"	-I <dir> Add directory to import path\n"
"	-D <var> Add predefined variable\n"
"	-o       Name of output\n"
"	infile   Top file(s) to compile\n"
;

static void usage()
{
	fprintf(stderr, cmdline_usage);
}

int main(int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "hI:D:o:")) != -1) {
		switch (opt) {
		case 'o':
			error("not yet implemented");
			break;

		case 'I':
			add_import_path(optarg);
			break;

		case 'D':
			/* TODO */
			error("not yet implemented");
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
		error("no input files");
		usage();
		exit(EXIT_FAILURE);
	}

	for (int i = optind; i < argc; ++i) {
		debug("starting compilation of '%s'", argv[i]);
		if (compile(argv[i]))
			return -1;
	}

	return 0;
}
