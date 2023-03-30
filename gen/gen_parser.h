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
    SQUOTE = 262,                  /* "'"  */
    TO = 263,                      /* "="  */
    ELLIPSIS = 264,                /* "..."  */
    SEMICOLON = 265,               /* ";"  */
    COLON = 266,                   /* ":"  */
    BANG = 267,                    /* "!"  */
    TYPEOF = 268,                  /* "typeof"  */
    SIZEOF = 269,                  /* "sizeof"  */
    PASTE = 270,                   /* "##"  */
    STAR = 271,                    /* "*"  */
    DIV = 272,                     /* "/"  */
    REM = 273,                     /* "%"  */
    MINUS = 274,                   /* "-"  */
    PLUS = 275,                    /* "+"  */
    POW = 276,                     /* "^^"  */
    XOR = 277,                     /* "^"  */
    AND = 278,                     /* "&"  */
    OR = 279,                      /* "|"  */
    LAND = 280,                    /* "&&"  */
    LOR = 281,                     /* "||"  */
    TILDE = 282,                   /* "~"  */
    LT = 283,                      /* "<"  */
    GT = 284,                      /* ">"  */
    LE = 285,                      /* "<="  */
    GE = 286,                      /* ">="  */
    NE = 287,                      /* "!="  */
    EQ = 288,                      /* "=="  */
    LSHIFT = 289,                  /* "<<"  */
    RSHIFT = 290,                  /* ">>"  */
    PLUSSELF = 291,                /* "+="  */
    MINUSSELF = 292,               /* "-="  */
    STARSELF = 293,                /* "*="  */
    DIVSELF = 294,                 /* "/="  */
    REMSELF = 295,                 /* "%="  */
    XORSELF = 296,                 /* "^="  */
    POWSELF = 297,                 /* "^^="  */
    ANDSELF = 298,                 /* "&="  */
    ORSELF = 299,                  /* "|="  */
    LSHIFTSELF = 300,              /* "<<="  */
    RSHIFTSELF = 301,              /* ">>="  */
    AT = 302,                      /* "@"  */
    COMMA = 303,                   /* ","  */
    PUB = 304,                     /* "pub"  */
    STRUCT = 305,                  /* "struct"  */
    UNION = 306,                   /* "union"  */
    TYPEDEF = 307,                 /* "typedef"  */
    IMPORT = 308,                  /* "import"  */
    DEFER = 309,                   /* "defer"  */
    GOTO = 310,                    /* "goto"  */
    EMBED = 311,                   /* "embed"  */
    IF = 312,                      /* "if"  */
    ELSE = 313,                    /* "else"  */
    BREAK = 314,                   /* "break"  */
    CONTINUE = 315,                /* "continue"  */
    SWITCH = 316,                  /* "switch"  */
    CASE = 317,                    /* "case"  */
    FOR = 318,                     /* "for"  */
    WHILE = 319,                   /* "while"  */
    DO = 320,                      /* "do"  */
    MUT = 321,                     /* "mut"  */
    RETURN = 322,                  /* "return"  */
    CONST = 323,                   /* "const"  */
    EXTERN = 324,                  /* "extern"  */
    ENUM = 325,                    /* "enum"  */
    DEFINE = 326,                  /* "define"  */
    LPAREN = 327,                  /* "("  */
    RPAREN = 328,                  /* ")"  */
    LBRACE = 329,                  /* "{"  */
    RBRACE = 330,                  /* "}"  */
    LBRACKET = 331,                /* "["  */
    RBRACKET = 332,                /* "]"  */
    AS = 333,                      /* "as"  */
    DOT = 334,                     /* "."  */
    SCOPE = 335,                   /* "::"  */
    FATARROW = 336                 /* "=>"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "src/parser.y"

	struct ast_node *node;
	long long integer;
	double dbl;
	char *str;

#line 152 "gen/gen_parser.h"

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
