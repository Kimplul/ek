/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

#ifndef ANALYZE_H
#define ANALYZE_H

/**
 * @file actualize.h
 *
 * Actualization stuff  needed for turning raw AST
 * into processed AST that can be passed to a backend to generate code.
 */

#include <assert.h>

#include "ast.h"
#include "scope.h"

/**
 * Check if two types match.
 * A match is considered as identical types after alias, expression and
 * trait expansion.
 *
 * @param a Type to compare against \p b.
 * @param b Type to compare against \p a.
 * @return \c 1 if types match, \c 0 otherwise.
 */
int types_match(struct type *a, struct type *b);

int type_lists_match(struct type *a, struct type *b);

/**
 * Analyze raw AST, assumed to be file scope.
 * The analysis phase collects top level objects, types, procedures, etc.
 * Constructs visibilities and builds resolution trees.
 * Also detects some duplicates.
 *
 * @param scope File scope of raw AST.
 * @param tree Raw AST to analyze.
 * @return \c 0 when successful, non-zero otherwise.
 */
int analyze_root(struct scope *scope, struct ast *tree);

#endif /* ANALYZE_H */
