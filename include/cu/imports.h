/* SPDX-License-Identifier: GPL-3.0-or-later */

#ifndef CT_IMPORTS_H
#define CT_IMPORTS_H

#include <stdbool.h>

void add_import_path(const char *dir);
const char *find_import(const char *file);
bool already_imported(const char *file);

#endif /* CT_IMPORTS_H */
