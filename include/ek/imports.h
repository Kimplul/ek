/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef EK_IMPORTS_H
#define EK_IMPORTS_H

/**
 * @file imports.h
 *
 * File import handling.
 * Currently mostly unimplemented, but intended to keep track
 * of which files have been imported.
 */

#include <stdbool.h>

void add_import_path(const char *dir);
const char *find_import(const char *file);
bool already_imported(const char *file);

#endif /* EK_IMPORTS_H */
