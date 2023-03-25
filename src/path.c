/* SPDX-License-Identifier: GPL-3.0-or-later */

#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include <cu/path.h>
#include <cu/debug.h>

char *cu_basename(const char *file)
{
	size_t l = strlen(file);
	size_t n = l - 1;
	while (--n) {
		if (file[n] == '/')
			break;
	}

	if (n == 0)
		return strdup(file);

	return strndup(file + n + 1, l - n);
}

char *cu_dirname(const char *file)
{
	size_t l = strlen(file);
	size_t n = l - 1;
	while (--n) {
		if (file[n] == '/')
			break;
	}

	return strndup(file, n);
}

char *cu_cwdname()
{
	size_t size;
	long path_max = pathconf(".", _PC_PATH_MAX);
	if (path_max == -1)
		size = 1024;
	else
		size = (size_t)path_max;

	char *buf = malloc(size);
	if (!buf)
		return NULL;

	if (!getcwd(buf, size)) {
		error("%s\n", strerror(errno));
		free(buf);
		return NULL;
	}

	return buf;
}
