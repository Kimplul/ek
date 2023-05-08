/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef EK_PATH
#define EK_PATH

/**
 * @file path.h
 *
 * Path handling helpers.
 */

char *ek_basename(const char *file);
char *ek_dirname(const char *file);
char *ek_cwdname();

#endif /* EK_PATH */
