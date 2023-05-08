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

int types_match(struct ast_node *a, struct ast_node *b);

/* these three might be better off in some ast_utils.c or something */
void replace_type(struct ast_node *type,
                  struct ast_node *from, struct ast_node *to);

void replace_param_types(struct ast_node *param,
                         struct ast_node *param_type,
                         struct ast_node *arg_type);

void init_template_type(struct ast_node *type, struct ast_node *param_type,
                        struct ast_node *arg_type);
void init_template_types(struct ast_node *param, struct ast_node *param_type,
                         struct ast_node *arg_type);

struct ast_node *extract_template(struct ast_node *type);
struct ast_node *extract_typeof(struct ast_node *type);

int analyze_root(struct scope *scope, struct ast_node *tree);
int actualize_main(struct scope *scope);
int actualize_temp_type(struct scope *scope, struct ast_node *type);
struct ast_node *actual_type(struct ast_node *type);

#endif /* ANALYZE_H */
