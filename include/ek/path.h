/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef EK_PATH
#define EK_PATH

/**
 * @file path.h
 *
 * Path handling helpers.
 */

/**
 * Get basename of file path.
 * E.g. src/some/file.c -> file.c
 *
 * @param file File path to get basename from.
 * @return Basename of \p file.
 */
char *ek_basename(const char *file);

/**
 * Get directory name of path.
 * E.g. src/some/file.c -> src/some
 *
 * @param file File path to get dirname from.
 * @return Dirname of \p file.
 */
char *ek_dirname(const char *file);

/**
 * Get current working directory.
 *
 * @return Current working directory.
 */
char *ek_cwdname();

#endif /* EK_PATH */
