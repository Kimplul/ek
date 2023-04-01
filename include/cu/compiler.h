/* SPDX-License-Identifier: GPL-3.0-or-later */

#ifndef CT_COMPILER_H
#define CT_COMPILER_H

#include <cu/scope.h>

int compile(const char *file);
int process_file(struct scope **parent, int public, const char *file);

#endif /* CT_COMPILER_H */
