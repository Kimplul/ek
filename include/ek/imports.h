/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef EK_IMPORTS_H
#define EK_IMPORTS_H

/**
 * @file imports.h
 *
 * File import handling.
 * Currently mostly unimplemented, but intended to keep track
 * of where to find files for import.
 */

#include <stdbool.h>

/**
 * Add import path to search for files in.
 *
 * @param dir Directory to search files in. Either absolute or relative.
 */
void add_import_path(const char *dir);

/**
 * Search for \p file in import path.
 * @todo implement.
 *
 * @param file File name to search for.
 * @return Full path to \p file if found, \c NULL otherwise.
 */
const char *find_import(const char *file);

#endif /* EK_IMPORTS_H */
