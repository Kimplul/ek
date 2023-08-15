/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GEN_GEN_PARSER_H_INCLUDED
# define YY_YY_GEN_GEN_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    FLOAT = 259,                   /* FLOAT  */
    STRING = 260,                  /* STRING  */
    ID = 261,                      /* ID  */
    APPLY = 262,                   /* APPLY  */
    QUESTION = 263,                /* "?"  */
    SQUOTE = 264,                  /* "'"  */
    TO = 265,                      /* "="  */
    ELLIPSIS = 266,                /* "..."  */
    SEMICOLON = 267,               /* ";"  */
    COLON = 268,                   /* ":"  */
    BANG = 269,                    /* "!"  */
    TYPEOF = 270,                  /* "typeof"  */
    SIZEOF = 271,                  /* "sizeof"  */
    PASTE = 272,                   /* "##"  */
    STAR = 273,                    /* "*"  */
    DIV = 274,                     /* "/"  */
    REM = 275,                     /* "%"  */
    MINUS = 276,                   /* "-"  */
    PLUS = 277,                    /* "+"  */
    POW = 278,                     /* "^^"  */
    XOR = 279,                     /* "^"  */
    AND = 280,                     /* "&"  */
    OR = 281,                      /* "|"  */
    LAND = 282,                    /* "&&"  */
    LOR = 283,                     /* "||"  */
    TILDE = 284,                   /* "~"  */
    LT = 285,                      /* "<"  */
    GT = 286,                      /* ">"  */
    LE = 287,                      /* "<="  */
    GE = 288,                      /* ">="  */
    NE = 289,                      /* "!="  */
    EQ = 290,                      /* "=="  */
    LSHIFT = 291,                  /* "<<"  */
    RSHIFT = 292,                  /* ">>"  */
    PLUSSELF = 293,                /* "+="  */
    MINUSSELF = 294,               /* "-="  */
    STARSELF = 295,                /* "*="  */
    DIVSELF = 296,                 /* "/="  */
    REMSELF = 297,                 /* "%="  */
    XORSELF = 298,                 /* "^="  */
    POWSELF = 299,                 /* "^^="  */
    ANDSELF = 300,                 /* "&="  */
    ORSELF = 301,                  /* "|="  */
    LSHIFTSELF = 302,              /* "<<="  */
    RSHIFTSELF = 303,              /* ">>="  */
    AT = 304,                      /* "@"  */
    COMMA = 305,                   /* ","  */
    PUB = 306,                     /* "pub"  */
    STRUCT = 307,                  /* "struct"  */
    UNION = 308,                   /* "union"  */
    TYPEDEF = 309,                 /* "typedef"  */
    IMPORT = 310,                  /* "import"  */
    DEFER = 311,                   /* "defer"  */
    GOTO = 312,                    /* "goto"  */
    EMBED = 313,                   /* "embed"  */
    IF = 314,                      /* "if"  */
    ELSE = 315,                    /* "else"  */
    BREAK = 316,                   /* "break"  */
    CONTINUE = 317,                /* "continue"  */
    DEFAULT = 318,                 /* "default"  */
    SWITCH = 319,                  /* "switch"  */
    CASE = 320,                    /* "case"  */
    FOR = 321,                     /* "for"  */
    WHILE = 322,                   /* "while"  */
    DO = 323,                      /* "do"  */
    MUT = 324,                     /* "mut"  */
    RETURN = 325,                  /* "return"  */
    CONST = 326,                   /* "const"  */
    EXTERN = 327,                  /* "extern"  */
    ENUM = 328,                    /* "enum"  */
    DEFINE = 329,                  /* "define"  */
    LPAREN = 330,                  /* "("  */
    RPAREN = 331,                  /* ")"  */
    LBRACE = 332,                  /* "{"  */
    RBRACE = 333,                  /* "}"  */
    LBRACKET = 334,                /* "["  */
    RBRACKET = 335,                /* "]"  */
    AS = 336,                      /* "as"  */
    DOT = 337,                     /* "."  */
    SCOPE = 338,                   /* "::"  */
    FATARROW = 339                 /* "=>"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "src/parser.y"

	struct ast_node *node;
	long long integer;
	double dbl;
	char *str;

#line 155 "gen/gen_parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (void *scanner, struct parser* parser);


#endif /* !YY_YY_GEN_GEN_PARSER_H_INCLUDED  */
