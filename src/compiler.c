#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

#include <ct/compiler.h>
#include <ct/string.h>
#include <ct/debug.h>
#include <ct/path.h>
#include <ct/res.h>

static int read_element(FILE *f, struct string *element)
{
	if (feof(f))
		return -1;

	str_clear(element);

	char c = fgetc(f);
	str_append(element, c);
	if (!isalnum(c))
		return 0;

	while ((c = fgetc(f))) {
		if (isalnum(c)) {
			str_append(element, c);
		} else {
			ungetc(c, f);
			break;
		}
	}

	return 0;
}

static struct string *read_block(FILE *f, size_t *lines)
{
	size_t depth = 0;
	bool maybe_statement = true;
	struct string *block = new_string(NULL);
	if (!block)
		return NULL;

	struct string *elem = new_string(NULL);
	if (!elem) {
		destroy_string(block);
		return NULL;
	}

	size_t newlines = 0;
	while (1) {
		if (read_element(f, elem)) {
			destroy_string(elem);
			destroy_string(block);
			return NULL;
		}

		if (maybe_statement && str_compare(elem, ";")) {
			str_add(block, elem);
			break;
		}

		if (str_compare(elem, "{")) {
			maybe_statement = false;
			depth += 1;
		}

		if (str_compare(elem, "}"))
			depth -= 1;

		str_add(block, elem);

		if (str_compare(elem, "\n"))
			newlines++;

		if (!maybe_statement && depth == 0)
			break;
	}

	if (lines)
		*lines += newlines;

	destroy_string(elem);
	return block;
}

static int process(struct res *r, const char *file)
{
	FILE *f = fopen(file, "r");
	if (!f) {
		error("failed opening %s: %s\n", file, strerror(errno));
		return -1;
	}

	size_t lines = 1, prev_lines = 1;
	struct string *block;
	while ((block = read_block(f, &lines))) {
		debug("block: (%zu - %zu, %zu)\n%s\n", prev_lines, lines,
				lines - prev_lines, block->buf);
		prev_lines = lines + 1;

		/* with each block,
		 * A) Detect if it is an import block and what kind,
		 * in which case process the file that it refers to.
		 *
		 * B) Detect if it is a macro block and what kind, in which case
		 * parse it and add it to the macro subsystem.
		 *
		 * C) Run the preprocessor on the block.
		 *
		 * D) Actually lex/parse/generate AST for the block.
		 *
		 * E) Run semantic checks on the block.
		 *
		 * With all of these parts checked, I'm pretty sure we can
		 * directly generate code for each block. Possibly something
		 * like one C file per CT file, will have to look into what
		 * might be easiest. Also, some internal duplicate checking, so
		 * that we don't accidentally generate the same generic function
		 * in two different files or something like that.
		 *
		 * Same duplicate checking could be useful for the interpreted
		 * approach.
		 *
		 * Step D) could potentially be done on request, maybe fitting
		 * for the interpreted approach, I guess it depends on how fast the
		 * lexing/parsing/AST generation for each block is. Semantic
		 * checking is what I suspect will be the slowest part.
		 *
		 * Oh yeah, need some way to push result of some lower file
		 * processing upwards. And probably detecting a main block as
		 * well?
		 */
		destroy_string(block);
	}

	fclose(f);
	return 0;
}

void compile(const char *file) {
	struct res *r = res_create();
	res_add(r, (void *)(file = strdup(file)));

	const char *base = ct_basename(file);
	res_add(r, (void *)base);
	if (!base)
		goto out;

	const char *dir = ct_dirname(file);
	res_add(r, (void *)dir);
	if (!dir)
		goto out;

	const char *cwd = ct_cwdname();
	res_add(r, (void *)cwd);
	if (!cwd)
		goto out;

	debug("(cwd:%s)(dir:%s)(base:%s)\n", cwd, dir, base);

	if (chdir(dir)) {
		error("couldn't change to directory %s: %s\n", dir, strerror(errno));
		goto out;
	}

	if (process(r, base))
		goto out;

	if (chdir(cwd)) {
		error("couldn't change back to directory %s: %s\n", cwd, strerror(errno));
		goto out;
	}


out:
	res_destroy(r);
}
