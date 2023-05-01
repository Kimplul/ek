/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef EK_COMPILER_H
#define EK_COMPILER_H

#include <ek/scope.h>

int compile(const char *file);
int process_file(struct scope **parent, int public, const char *file);

#endif /* EK_COMPILER_H */
