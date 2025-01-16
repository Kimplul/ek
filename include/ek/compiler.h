/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef EK_COMPILER_H
#define EK_COMPILER_H

/**
 * @file compiler.h
 *
 * Top level compiler.
 */

#include <ek/scope.h>

/**
 * Compile a root file.
 * A root file is a file given on the command line, and is assumed to
 * create a file tree that eventually results in a binary.
 *
 * @param file Root file to compile.
 * @return \c 0 if compilation was succesful, otherwise some non-zero value.
 */
int compile(const char *input);

/**
 * Process a file, i.e. lex, parse and generate raw AST.
 *
 * @param parent Parent scope of file from which \p file is imported.
 * \c NULL if root file.
 * @param public \c 1 if \p file should be publicly imported, \c 0 otherwise.
 * @param file File to process.
 * @return \c 0 if compilation was succesful, otherwise some non-zero value.
 */
struct scope *process_file(const char *file);

#endif /* EK_COMPILER_H */
