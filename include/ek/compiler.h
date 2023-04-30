/* SPDX-License-Identifier: GPL-3.0-or-later */

#ifndef EK_COMPILER_H
#define EK_COMPILER_H

#include <ek/scope.h>

int compile(const char *file);
int process_file(struct scope **parent, int public, const char *file);

#endif /* EK_COMPILER_H */
