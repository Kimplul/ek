/* SPDX-License-Identifier: GPL-3.0-or-later */

#ifndef EK_IMPORTS_H
#define EK_IMPORTS_H

#include <stdbool.h>

void add_import_path(const char *dir);
const char *find_import(const char *file);
bool already_imported(const char *file);

#endif /* EK_IMPORTS_H */
