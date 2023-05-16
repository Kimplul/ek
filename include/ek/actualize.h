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
 * template expansion.
 *
 * @param a Type to compare against \p b.
 * @param b Type to compare against \p a.
 * @return \c 1 if types match, \c 0 otherwise.
 */
int types_match(struct ast_node *a, struct ast_node *b);

/**
 * Replace type in \p type that matches with \p from
 * with \p to.
 *
 * @param type Whole type to replace part in.
 * @param from Part of type to replace.
 * @param to Type to replace \p from with.
 */
void replace_type(struct ast_node *type,
                  struct ast_node *from, struct ast_node *to);

/**
 * Loop over parameters and replace types that match with \p param_type
 * with \p arg_type.
 *
 * @param param Parameters to replace types for.
 * @param param_type Type to replace with \p arg_type.
 * @param arg_type Type to replace \p param_type with.
 */
void replace_param_types(struct ast_node *param,
                         struct ast_node *param_type,
                         struct ast_node *arg_type);

/**
 * Replace templated type with actual type.
 *
 * @param type Templated type.
 * Keep in mind that a templated struct retains all template parameters, so
 * pass the struct itself.
 * @param param_type Template parameter type to replace.
 * @param arg_type Type to replace \p param_type with.
 */
void init_template_type(struct ast_node *type, struct ast_node *param_type,
                        struct ast_node *arg_type);

/**
 * Replace templated parameter types.
 *
 * @param param List of parameters to replace templated types for.
 * @param param_type Types that match this are replaced with \p arg_type.
 * @param arg_type Type to replace \p param_type with.
 */
void init_template_types(struct ast_node *param, struct ast_node *param_type,
                         struct ast_node *arg_type);

/**
 * Extract template type, that is strip pointer/expression/alias stuff
 * and get the template itself from the type.
 *
 * @param type Type to extract template from.
 * @return Pointer to template node when found, \c NULL otherwise.
 */
struct ast_node *extract_template(struct ast_node *type);

/**
 * Extract typeof expression.
 *
 * @param type Type to extract typeof from.
 * @return Pointer to typeof expression node when found, \c NULL otherwise.
 */
struct ast_node *extract_typeof(struct ast_node *type);

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
int analyze_root(struct scope *scope, struct ast_node *tree);

/**
 * Start actual compilation by trying to actualize main.
 *
 * @param scope Scope \c main() should be visible to, likely root scope.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int actualize_main(struct scope *scope);

/**
 * Create temporary actualization context and actualizes \p type within it.
 *
 * @param scope Scope to actualize \p type in.
 * @param type Type to actualize.
 * @return \c 0 when succesful, non-zero otherwise.
 */
int actualize_temp_type(struct scope *scope, struct ast_node *type);

/**
 * Expand templates, typeofs, aliases and try to get the most
 * basic representation.
 *
 * @param type Type to extract actual type from.
 * @return AST node of actual type.
 */
struct ast_node *actual_type(struct ast_node *type);

#endif /* ANALYZE_H */
