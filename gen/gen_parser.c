/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "src/parser.y"


/* TODO: clean up this mess and I guess fix location tracking, it works for the
 * parser but each ast node should also get some location data
 * I'm trying something over in ast.c, but I'm not sure about it
 */

#include <stdio.h>
#include <stdlib.h>
#include <ek/parser.h>
#include <ek/ast.h>


#line 85 "gen/gen_parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "gen_parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_ID = 6,                         /* ID  */
  YYSYMBOL_APPLY = 7,                      /* APPLY  */
  YYSYMBOL_QUESTION = 8,                   /* "?"  */
  YYSYMBOL_SQUOTE = 9,                     /* "'"  */
  YYSYMBOL_TO = 10,                        /* "="  */
  YYSYMBOL_ELLIPSIS = 11,                  /* "..."  */
  YYSYMBOL_SEMICOLON = 12,                 /* ";"  */
  YYSYMBOL_COLON = 13,                     /* ":"  */
  YYSYMBOL_BANG = 14,                      /* "!"  */
  YYSYMBOL_TYPEOF = 15,                    /* "typeof"  */
  YYSYMBOL_SIZEOF = 16,                    /* "sizeof"  */
  YYSYMBOL_PASTE = 17,                     /* "##"  */
  YYSYMBOL_STAR = 18,                      /* "*"  */
  YYSYMBOL_DIV = 19,                       /* "/"  */
  YYSYMBOL_REM = 20,                       /* "%"  */
  YYSYMBOL_MINUS = 21,                     /* "-"  */
  YYSYMBOL_PLUS = 22,                      /* "+"  */
  YYSYMBOL_POW = 23,                       /* "^^"  */
  YYSYMBOL_XOR = 24,                       /* "^"  */
  YYSYMBOL_AND = 25,                       /* "&"  */
  YYSYMBOL_OR = 26,                        /* "|"  */
  YYSYMBOL_LAND = 27,                      /* "&&"  */
  YYSYMBOL_LOR = 28,                       /* "||"  */
  YYSYMBOL_TILDE = 29,                     /* "~"  */
  YYSYMBOL_LT = 30,                        /* "<"  */
  YYSYMBOL_GT = 31,                        /* ">"  */
  YYSYMBOL_LE = 32,                        /* "<="  */
  YYSYMBOL_GE = 33,                        /* ">="  */
  YYSYMBOL_NE = 34,                        /* "!="  */
  YYSYMBOL_EQ = 35,                        /* "=="  */
  YYSYMBOL_LSHIFT = 36,                    /* "<<"  */
  YYSYMBOL_RSHIFT = 37,                    /* ">>"  */
  YYSYMBOL_PLUSSELF = 38,                  /* "+="  */
  YYSYMBOL_MINUSSELF = 39,                 /* "-="  */
  YYSYMBOL_STARSELF = 40,                  /* "*="  */
  YYSYMBOL_DIVSELF = 41,                   /* "/="  */
  YYSYMBOL_REMSELF = 42,                   /* "%="  */
  YYSYMBOL_XORSELF = 43,                   /* "^="  */
  YYSYMBOL_POWSELF = 44,                   /* "^^="  */
  YYSYMBOL_ANDSELF = 45,                   /* "&="  */
  YYSYMBOL_ORSELF = 46,                    /* "|="  */
  YYSYMBOL_LSHIFTSELF = 47,                /* "<<="  */
  YYSYMBOL_RSHIFTSELF = 48,                /* ">>="  */
  YYSYMBOL_AT = 49,                        /* "@"  */
  YYSYMBOL_COMMA = 50,                     /* ","  */
  YYSYMBOL_PUB = 51,                       /* "pub"  */
  YYSYMBOL_STRUCT = 52,                    /* "struct"  */
  YYSYMBOL_UNION = 53,                     /* "union"  */
  YYSYMBOL_TYPEDEF = 54,                   /* "typedef"  */
  YYSYMBOL_IMPORT = 55,                    /* "import"  */
  YYSYMBOL_DEFER = 56,                     /* "defer"  */
  YYSYMBOL_GOTO = 57,                      /* "goto"  */
  YYSYMBOL_EMBED = 58,                     /* "embed"  */
  YYSYMBOL_IF = 59,                        /* "if"  */
  YYSYMBOL_ELSE = 60,                      /* "else"  */
  YYSYMBOL_BREAK = 61,                     /* "break"  */
  YYSYMBOL_CONTINUE = 62,                  /* "continue"  */
  YYSYMBOL_DEFAULT = 63,                   /* "default"  */
  YYSYMBOL_SWITCH = 64,                    /* "switch"  */
  YYSYMBOL_CASE = 65,                      /* "case"  */
  YYSYMBOL_FOR = 66,                       /* "for"  */
  YYSYMBOL_WHILE = 67,                     /* "while"  */
  YYSYMBOL_DO = 68,                        /* "do"  */
  YYSYMBOL_MUT = 69,                       /* "mut"  */
  YYSYMBOL_RETURN = 70,                    /* "return"  */
  YYSYMBOL_CONST = 71,                     /* "const"  */
  YYSYMBOL_EXTERN = 72,                    /* "extern"  */
  YYSYMBOL_ENUM = 73,                      /* "enum"  */
  YYSYMBOL_DEFINE = 74,                    /* "define"  */
  YYSYMBOL_LPAREN = 75,                    /* "("  */
  YYSYMBOL_RPAREN = 76,                    /* ")"  */
  YYSYMBOL_LBRACE = 77,                    /* "{"  */
  YYSYMBOL_RBRACE = 78,                    /* "}"  */
  YYSYMBOL_LBRACKET = 79,                  /* "["  */
  YYSYMBOL_RBRACKET = 80,                  /* "]"  */
  YYSYMBOL_AS = 81,                        /* "as"  */
  YYSYMBOL_DOT = 82,                       /* "."  */
  YYSYMBOL_SCOPE = 83,                     /* "::"  */
  YYSYMBOL_FATARROW = 84,                  /* "=>"  */
  YYSYMBOL_YYACCEPT = 85,                  /* $accept  */
  YYSYMBOL_id = 86,                        /* id  */
  YYSYMBOL_apply = 87,                     /* apply  */
  YYSYMBOL_var = 88,                       /* var  */
  YYSYMBOL_embed = 89,                     /* embed  */
  YYSYMBOL_import = 90,                    /* import  */
  YYSYMBOL_assign = 91,                    /* assign  */
  YYSYMBOL_binop = 92,                     /* binop  */
  YYSYMBOL_unop = 93,                      /* unop  */
  YYSYMBOL_arg = 94,                       /* arg  */
  YYSYMBOL_args = 95,                      /* args  */
  YYSYMBOL_param_decl = 96,                /* param_decl  */
  YYSYMBOL_decls = 97,                     /* decls  */
  YYSYMBOL_defer = 98,                     /* defer  */
  YYSYMBOL_const_binop = 99,               /* const_binop  */
  YYSYMBOL_const_unop = 100,               /* const_unop  */
  YYSYMBOL_const_expr = 101,               /* const_expr  */
  YYSYMBOL_expr = 102,                     /* expr  */
  YYSYMBOL_while = 103,                    /* while  */
  YYSYMBOL_do_while = 104,                 /* do_while  */
  YYSYMBOL_goto = 105,                     /* goto  */
  YYSYMBOL_statelet = 106,                 /* statelet  */
  YYSYMBOL_statement = 107,                /* statement  */
  YYSYMBOL_statements = 108,               /* statements  */
  YYSYMBOL_body = 109,                     /* body  */
  YYSYMBOL_references = 110,               /* references  */
  YYSYMBOL_macro = 111,                    /* macro  */
  YYSYMBOL_exprs = 112,                    /* exprs  */
  YYSYMBOL_construct_arg = 113,            /* construct_arg  */
  YYSYMBOL_construct_args = 114,           /* construct_args  */
  YYSYMBOL_construct = 115,                /* construct  */
  YYSYMBOL_if = 116,                       /* if  */
  YYSYMBOL_for = 117,                      /* for  */
  YYSYMBOL_case = 118,                     /* case  */
  YYSYMBOL_cases = 119,                    /* cases  */
  YYSYMBOL_switch = 120,                   /* switch  */
  YYSYMBOL_const_for = 121,                /* const_for  */
  YYSYMBOL_const_if = 122,                 /* const_if  */
  YYSYMBOL_const = 123,                    /* const  */
  YYSYMBOL_simple_sign = 124,              /* simple_sign  */
  YYSYMBOL_func_sign = 125,                /* func_sign  */
  YYSYMBOL_type = 126,                     /* type  */
  YYSYMBOL_var_decl = 127,                 /* var_decl  */
  YYSYMBOL_var_init = 128,                 /* var_init  */
  YYSYMBOL_proc = 129,                     /* proc  */
  YYSYMBOL_lambda = 130,                   /* lambda  */
  YYSYMBOL_struct_elem = 131,              /* struct_elem  */
  YYSYMBOL_members = 132,                  /* members  */
  YYSYMBOL_union = 133,                    /* union  */
  YYSYMBOL_generic = 134,                  /* generic  */
  YYSYMBOL_generics = 135,                 /* generics  */
  YYSYMBOL_struct = 136,                   /* struct  */
  YYSYMBOL_template_elem = 137,            /* template_elem  */
  YYSYMBOL_template_elems = 138,           /* template_elems  */
  YYSYMBOL_types = 139,                    /* types  */
  YYSYMBOL_alias = 140,                    /* alias  */
  YYSYMBOL_template = 141,                 /* template  */
  YYSYMBOL_enum_val = 142,                 /* enum_val  */
  YYSYMBOL_enums = 143,                    /* enums  */
  YYSYMBOL_enum = 144,                     /* enum  */
  YYSYMBOL_top_if = 145,                   /* top_if  */
  YYSYMBOL_top_var_decl = 146,             /* top_var_decl  */
  YYSYMBOL_top_var_init = 147,             /* top_var_init  */
  YYSYMBOL_top_var = 148,                  /* top_var  */
  YYSYMBOL_top = 149,                      /* top  */
  YYSYMBOL_unit = 150,                     /* unit  */
  YYSYMBOL_input = 151                     /* input  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  69
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2267

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  253
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  501

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   339


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   165,   165,   171,   177,   178,   181,   184,   187,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   214,   217,   218,   219,   220,   221,   222,   225,   226,
     227,   228,   229,   232,   233,   234,   237,   238,   241,   244,
     245,   246,   247,   250,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   274,   275,   276,   279,   280,   281,   282,
     283,   284,   288,   289,   290,   291,   292,   293,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   319,   322,
     328,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   368,   371,   372,   373,   376,   377,   380,
     381,   385,   389,   396,   402,   403,   406,   407,   413,   414,
     417,   420,   421,   422,   426,   429,   431,   436,   437,   440,
     444,   451,   455,   460,   468,   469,   472,   475,   476,   477,
     478,   481,   482,   489,   490,   494,   497,   501,   505,   508,
     513,   517,   518,   521,   522,   526,   532,   536,   542,   543,
     546,   549,   550,   553,   556,   561,   564,   565,   568,   571,
     578,   579,   580,   581,   584,   585,   588,   589,   592,   597,
     600,   606,   607,   610,   611,   612,   615,   616,   622,   626,
     630,   636,   640,   641,   644,   645,   646,   649,   650,   655,
     656,   657,   658,   659,   660,   661,   662,   663,   664,   665,
     666,   667,   668,   669,   670,   671,   672,   673,   677,   678,
     693,   694,   697,   698
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT",
  "STRING", "ID", "APPLY", "\"?\"", "\"'\"", "\"=\"", "\"...\"", "\";\"",
  "\":\"", "\"!\"", "\"typeof\"", "\"sizeof\"", "\"##\"", "\"*\"", "\"/\"",
  "\"%\"", "\"-\"", "\"+\"", "\"^^\"", "\"^\"", "\"&\"", "\"|\"", "\"&&\"",
  "\"||\"", "\"~\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\"!=\"",
  "\"==\"", "\"<<\"", "\">>\"", "\"+=\"", "\"-=\"", "\"*=\"", "\"/=\"",
  "\"%=\"", "\"^=\"", "\"^^=\"", "\"&=\"", "\"|=\"", "\"<<=\"", "\">>=\"",
  "\"@\"", "\",\"", "\"pub\"", "\"struct\"", "\"union\"", "\"typedef\"",
  "\"import\"", "\"defer\"", "\"goto\"", "\"embed\"", "\"if\"", "\"else\"",
  "\"break\"", "\"continue\"", "\"default\"", "\"switch\"", "\"case\"",
  "\"for\"", "\"while\"", "\"do\"", "\"mut\"", "\"return\"", "\"const\"",
  "\"extern\"", "\"enum\"", "\"define\"", "\"(\"", "\")\"", "\"{\"",
  "\"}\"", "\"[\"", "\"]\"", "\"as\"", "\".\"", "\"::\"", "\"=>\"",
  "$accept", "id", "apply", "var", "embed", "import", "assign", "binop",
  "unop", "arg", "args", "param_decl", "decls", "defer", "const_binop",
  "const_unop", "const_expr", "expr", "while", "do_while", "goto",
  "statelet", "statement", "statements", "body", "references", "macro",
  "exprs", "construct_arg", "construct_args", "construct", "if", "for",
  "case", "cases", "switch", "const_for", "const_if", "const",
  "simple_sign", "func_sign", "type", "var_decl", "var_init", "proc",
  "lambda", "struct_elem", "members", "union", "generic", "generics",
  "struct", "template_elem", "template_elems", "types", "alias",
  "template", "enum_val", "enums", "enum", "top_if", "top_var_decl",
  "top_var_init", "top_var", "top", "unit", "input", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-284)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-254)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     614,  -284,  -284,  -284,   137,    27,    27,    27,    19,   533,
      27,    27,    27,   775,  -284,  -284,  -284,  -284,  -284,  -284,
    -284,  -284,  -284,    29,  -284,  -284,   523,  -284,    53,  -284,
    -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,    33,    54,
     350,  -284,  -284,  -284,   533,   533,   533,   533,  -284,  -284,
    -284,  2068,   -48,    42,   -21,  -284,    28,  1352,   -48,   400,
     574,   121,   -17,   -10,  -284,     1,  -284,   533,  -284,  -284,
      27,    27,    27,    27,    56,  -284,  -284,    45,  -284,  1940,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   815,
     121,  -284,   326,    27,    36,   533,  -284,  -284,  -284,  -284,
    1352,    27,  1157,  1352,  1352,  1352,  1352,    39,  1352,  1352,
    1184,    27,   693,    -4,    57,  -284,  -284,  -284,  -284,  2003,
    -284,  -284,  -284,  -284,  -284,   533,  -284,   533,  -284,  -284,
     326,   331,    89,    41,  -284,    95,   771,   326,   999,  -284,
    2150,   326,    99,    62,   822,  -284,   138,    78,    84,    85,
    -284,   665,   156,  -284,    23,    96,  -284,  -284,  -284,  -284,
      45,    45,  2170,  1293,  1399,   330,  2210,  2190,  1204,  1204,
    1204,  1204,  2230,  2230,   180,   180,    97,   -46,   100,   168,
     129,   106,     1,   143,    37,  1011,    -7,  -284,   801,    -7,
      -7,   232,   615,    -7,   182,  1443,  1509,   372,  1575,   118,
     194,   130,   132,  -284,   693,  1246,  1352,  1352,  1352,  1352,
    1352,  1352,  1352,  1352,  1352,  1352,  1352,  1352,  1352,  1352,
    1352,  1352,  1352,  1352,  1352,  1352,  1352,  1352,  1352,  1352,
    1352,  1352,  1352,  1352,  1352,  1352,  1273,  1352,   693,    27,
    2150,  2150,   160,   326,   326,  -284,   326,    27,  -284,   503,
     326,  -284,   163,   157,  -284,  -284,  1352,    27,  -284,  -284,
    1379,  1352,     1,  1352,    67,  -284,   259,  -284,  -284,  -284,
    1906,  -284,  -284,  -284,   226,   914,   161,  -284,  -284,  -284,
    -284,   194,  -284,  -284,  -284,  -284,  -284,  -284,    27,   165,
      27,  -284,   166,  -284,  -284,   228,  -284,  -284,  -284,   187,
      27,  1352,    27,  -284,  -284,    27,    27,     1,   771,    27,
    1906,   205,   183,   188,   198,    79,   612,   649,  -284,  -284,
    1352,  -284,    80,  -284,  1352,  -284,   389,   213,   193,  1906,
    -284,  1972,   -24,   -24,   -24,   232,   232,  1478,  2037,   615,
    1875,  1611,  1544,  1743,  1743,  1743,  1743,  1677,  1677,   878,
     878,  1972,  1972,  1972,  1972,  1972,  1972,  1972,  1972,  1972,
    1972,  -284,   199,  1642,  -284,  -284,  -284,  -284,  -284,  -284,
     195,  -284,   201,  -284,   326,  -284,  1906,  -284,   272,  1443,
     219,  1906,   533,    27,  -284,  -284,  -284,  -284,  -284,  -284,
    -284,    27,  -284,    27,  -284,   -36,   209,  1906,  -284,  -284,
     212,  -284,  -284,   280,   801,  -284,  -284,   -28,   278,   533,
      79,   214,  1352,  1352,  1906,  -284,     1,  -284,  1379,  -284,
    -284,  -284,   326,  -284,  -284,  1352,  -284,  1352,  2102,   282,
     223,   227,   815,  -284,  -284,     1,  1352,  -284,  -284,  -284,
    1078,  2128,  -284,  -284,  1906,  1906,  -284,  -284,   221,  1708,
    1774,   244,  1352,  -284,  -284,   231,  -284,  1906,  -284,  1078,
    -284,  1352,  -284,   -27,  1840,     1,  -284,  -284,  1443,  -284,
    -284,  1352,  -284,  -284,  -284,   109,  1352,   234,   416,  1352,
     237,   326,   533,  1906,   533,    -7,   693,  1090,  1809,   326,
     693
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   249,     2,   248,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   236,   233,   230,   232,   231,   237,
     238,   229,   234,   227,   228,   235,     0,   252,     0,   244,
     243,   242,   241,   240,   245,   246,   239,   247,     0,     0,
       0,     7,    78,    79,     0,     0,     0,     0,    77,    80,
      81,     0,     0,     0,     0,     3,     0,     0,     0,     0,
       0,     0,   173,     0,   171,     0,   223,     0,   251,     1,
       0,     0,     0,     0,     0,   208,    74,    73,    75,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   187,     0,     0,     0,     0,   176,    85,    86,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,     0,   102,    89,    95,    96,   178,
     106,   104,   105,   103,   174,     0,   221,     0,   222,   170,
       0,   173,    52,     0,    48,    51,     0,     0,     0,   186,
     224,     0,   197,     0,     0,   190,     0,     0,     0,     0,
     210,     0,     0,   203,   205,     0,    76,    56,    57,    58,
      55,    54,    60,    59,    61,    63,    62,    64,    67,    68,
      69,    70,    71,    72,    65,    66,     0,     0,     0,   211,
     215,     0,     0,   140,     0,     0,    41,    84,     0,    39,
      98,    38,    40,    42,     0,     0,     0,    82,     0,     0,
       0,     0,     0,   101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     225,   226,     0,     0,     0,   182,     0,     0,   167,     0,
       0,   179,   207,     0,   132,   131,     0,     0,   114,   115,
       0,     0,     0,   113,     0,   138,    82,   117,   116,   128,
     111,   122,   123,   118,   136,     0,     0,   130,   124,   120,
     121,     4,     5,   125,   126,   127,   129,   195,     0,     0,
     192,   198,     0,   193,   200,     0,   202,   204,   209,   218,
       0,     0,   214,   217,   143,     0,     0,     0,     0,     0,
     146,   149,     0,     0,   151,     0,     0,     0,    88,   107,
       0,    97,     0,   100,     0,    94,    82,    47,     0,    45,
      44,     8,    11,    12,    13,    10,     9,    15,    14,    16,
      18,    17,    19,    32,    33,    34,    35,    36,    37,    20,
      21,    22,    23,    24,    25,    26,    29,    27,    28,    30,
      31,    91,     0,     0,    99,    83,   169,   180,   181,    50,
       0,   168,     0,    49,     0,   175,    53,   110,     0,     0,
       0,   112,     0,     0,   165,   164,   119,   133,   134,   137,
     196,     0,   191,     0,   201,     0,     0,   212,   213,   139,
       0,   141,   177,     0,     0,   150,     6,     0,     0,     0,
     158,     0,     0,     0,   183,   189,     0,    43,     0,    93,
      90,    92,     0,   166,   206,     0,   108,     0,     0,     0,
       0,     0,     0,   220,   216,     0,     0,   148,   152,   153,
       0,     0,   157,   159,   184,   185,   188,    46,     0,     0,
       0,   161,     0,   199,   194,     0,   142,   147,   156,     0,
     172,     0,   109,     0,   145,     0,   219,   155,     0,   162,
     163,     0,   160,   154,   144,     0,     0,   173,     0,     0,
     173,     0,     0,   178,     0,   178,     0,     0,     0,     0,
       0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -284,     0,   222,  -284,  -284,     4,  -284,  -284,  -284,    51,
    -243,  -284,   -84,  -284,  -284,  -284,   136,   528,  -284,  -284,
    -284,  -284,  -284,  -283,    88,  -120,    11,  -170,  -284,   -91,
    -284,   -92,  -284,  -284,   -89,  -284,  -284,  -144,  -284,   -38,
    -284,   357,   445,   233,   335,  -284,  -284,   -56,    32,  -284,
     -53,    14,  -284,   179,   -26,    17,    18,  -284,  -139,    21,
     -44,  -284,  -284,   360,  -284,     2,  -284
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   123,   124,   277,   125,    14,   126,   127,   128,   337,
     338,   142,   143,   279,    49,    50,    51,   280,   281,   282,
     283,   284,   285,   286,   287,   194,    15,   475,   321,   322,
     130,   131,   289,   420,   421,   132,   394,   395,   290,    64,
      65,   255,   155,   292,    16,   133,   156,   157,    17,   152,
     153,    18,   164,   165,   263,    19,    20,   190,   191,    21,
      22,    23,    24,    25,    26,    27,    28
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,   212,   398,   372,    13,    38,    39,    40,    29,    48,
      52,    53,    54,    62,   101,    30,   187,   159,    33,   158,
     134,    34,    35,     9,    41,    36,    13,   100,    68,     2,
     258,   118,   392,     2,     2,    55,    32,    56,   259,    67,
     487,   442,     2,    57,    48,    48,    48,    48,   316,   148,
     148,   246,   257,    69,   104,   102,    62,   248,   249,    62,
      62,   141,     2,    80,    81,    82,   146,    48,   246,   147,
     151,   154,   151,   154,   161,   249,     6,    58,   148,   214,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    13,
     141,   186,   487,   189,   193,    48,   163,   105,    70,     6,
      71,   197,   192,   317,   204,     2,    55,   258,   485,   103,
     207,   193,   490,   305,   486,   259,   392,     2,    55,    72,
     485,    73,   215,   393,   160,    48,   486,    48,   299,   256,
     487,   487,   418,     2,   419,   260,    62,   487,   276,   298,
     300,   487,   278,   149,   487,   100,   301,   148,    58,   288,
     302,   487,   293,   303,   161,   294,   295,   468,   306,   296,
      58,   406,   379,   408,   308,   309,   383,   310,   311,   312,
      76,    77,    78,    79,   313,   457,   477,   323,   492,     5,
       6,     7,     8,   315,   329,   409,   163,   139,    80,    81,
      82,    83,    84,   150,   330,   140,   331,    62,   209,    10,
      11,    12,   332,   384,   490,   336,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,    63,   376,   385,   397,   399,
     404,   195,   401,   403,   402,   400,   336,   405,   490,   375,
     217,   218,   219,   487,   487,   414,   141,   380,   417,   487,
     141,   415,    63,   428,   416,     2,    55,   387,    56,   429,
     336,   250,   396,   251,    57,   430,    62,   433,    63,   432,
     314,    63,    63,    63,   435,   276,   437,   444,   445,   278,
     446,   450,   453,   324,   426,   462,   288,   470,   151,   293,
     154,   463,   294,   295,   473,   464,   296,   246,    58,   476,
     189,   484,   189,   248,   249,   193,   410,   491,    62,   413,
     496,   388,    63,   447,    63,   449,    62,    62,   326,   480,
     327,   452,     2,    55,   336,   485,   487,     2,    55,    31,
     485,   486,   214,   307,    63,   440,   486,   441,    80,    81,
      82,    83,    84,   211,    86,    87,     2,    55,   434,   485,
     390,   443,    63,    63,    37,   486,    97,    98,    63,    63,
      66,     0,     0,    63,     0,    58,    63,     0,     2,    55,
      58,    56,     0,    63,   487,     0,     0,    57,     0,     0,
       0,     0,    48,   439,     0,     2,    55,    75,   485,    58,
     253,   154,   254,   154,   486,   411,     2,    55,     0,    56,
     135,     0,     0,   106,   491,    57,   136,   138,   144,    48,
     425,    58,     2,    55,     0,   488,     0,    74,   336,    63,
       0,   489,   487,     0,     0,     0,    63,     0,    58,     0,
       0,   326,    13,   327,   465,     0,     0,     0,     0,    58,
     276,     0,     0,     0,   278,   214,     0,   144,   253,   188,
     254,   288,     0,     0,   293,    58,     0,   294,   295,   276,
      63,   296,   214,   278,     0,    63,    63,   436,    63,   213,
     288,    63,    63,   293,     0,   487,   294,   295,   490,     0,
     296,   487,    48,     0,    48,   494,   490,   252,    63,   487,
     490,     0,     0,   261,   262,   448,   145,     0,   297,     2,
      55,     0,   485,     0,   456,     0,     0,     0,   486,   162,
       0,     0,     0,  -250,     1,     0,   461,     0,   438,     2,
       0,     0,     0,   466,     0,     3,    42,    43,     0,     2,
      63,     0,     0,     0,     0,   145,     0,    44,    63,    63,
       0,     0,    58,     0,    45,   451,     0,     0,    63,     0,
       0,   479,    46,   482,     0,   210,   483,     0,     0,     0,
       0,   333,     0,     0,     4,     5,     6,     7,     8,   381,
       2,    55,     9,    56,   137,   129,     0,     0,     0,    57,
       0,     0,     0,   291,     0,    10,    11,    12,     0,     0,
       0,  -250,     0,     0,     0,   374,    63,     0,    47,   162,
     377,   378,     0,   144,  -253,     1,   382,   144,     2,    55,
       2,    56,   422,    58,     0,     0,     3,    57,   497,     0,
     498,     0,     0,   217,   218,   219,   220,   221,   196,     0,
     199,   200,   201,   202,   203,     0,   205,   206,   208,     0,
       0,   234,   235,     0,    63,     2,    55,     0,    56,   423,
     340,    58,     0,     0,    57,     4,     5,     6,     7,     8,
       0,     2,    55,     9,   485,   412,     0,   304,     0,     0,
     486,     0,     0,   377,   378,     0,    10,    11,    12,     0,
     246,   340,     0,     0,     0,     0,   248,   249,    58,     2,
      55,   145,   488,     0,     0,   145,     0,    63,   489,     0,
      63,     0,     0,    63,    58,   340,     0,     0,    63,     0,
       0,    63,    63,     0,     0,     0,   320,     0,     0,     0,
     291,     0,     0,     0,   253,     0,   254,     0,     0,     0,
     100,   262,    58,   339,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   339,   373,     0,     2,    55,   427,
      56,     2,    55,     0,    56,     0,    57,     0,     0,   458,
      57,     0,     0,     0,   386,     0,     0,     0,   339,   389,
       0,   391,     0,     0,   107,   108,   109,     2,    55,     0,
     110,     0,   111,     0,     0,   112,     1,   113,     0,     0,
      58,     2,   114,     0,    58,     0,   115,     3,     2,    55,
     116,   485,     0,     0,     0,     0,     0,   486,     0,   407,
       0,     0,   106,     0,    59,   106,    60,     0,   261,     0,
      61,     0,     0,   261,     0,     0,   412,   412,   424,   117,
     118,     0,   202,     0,     0,   119,     4,     5,     6,     7,
       8,    58,     0,   340,     9,     0,   120,     0,     0,     0,
     121,     0,   122,   319,     0,     0,     0,    10,    11,    12,
       0,   253,     0,   254,     0,   291,   217,   218,   219,   220,
     221,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   291,   264,     0,   107,   108,   109,
       2,    55,     0,   110,     0,   111,   265,     0,   112,     0,
     113,     0,     0,     0,     0,   114,     0,     0,     0,   115,
       0,     0,   320,   116,     0,     0,     0,     0,     0,     0,
     454,   455,     0,   246,     0,     0,   339,     0,     0,   248,
     249,     0,     0,   459,     0,   460,     5,     0,     7,     8,
     266,   267,   117,   118,   467,   268,   269,  -135,   119,  -135,
     270,   271,   272,     0,   273,   274,     0,    11,    12,   120,
     474,   148,  -135,   121,     0,   122,     0,     0,     0,   478,
     264,     0,   107,   108,   109,     2,    55,     0,   110,   474,
     111,   265,     0,   112,   493,   113,     0,   495,     0,     0,
     114,     0,     0,     0,   115,     0,     0,     0,   116,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
       0,    91,    92,    93,    94,    95,    96,    97,    98,     0,
       0,     5,     0,     7,     8,   266,   267,   117,   118,     0,
     268,   269,     0,   119,     0,   270,   271,   272,     0,   273,
     274,     0,    11,    12,   120,     0,   148,   275,   121,   264,
     122,   107,   108,   109,     2,    55,     0,   110,     0,   111,
     265,   318,   112,     0,   113,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,   116,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     0,
      91,    92,    93,    94,    95,    96,    97,    98,     0,     0,
       5,     0,     7,     8,   266,   267,   117,   118,     0,   268,
     269,     0,   119,     0,   270,   271,   272,     0,   273,   274,
       0,    11,    12,   120,     0,   148,     0,   121,     0,   122,
     107,   108,   109,     2,    55,     0,   110,     0,   111,     0,
     499,   112,     0,   113,     0,     0,     0,     0,   114,     0,
       0,     0,   115,     0,     0,     0,   116,   107,   108,   109,
       2,    55,     0,   110,     0,   111,     0,     0,   112,     0,
     113,     0,     0,     0,     0,   114,     0,     0,     0,   115,
       0,     0,     0,   116,     0,   117,   118,     0,     0,     0,
       0,   119,    80,    81,    82,    83,    84,     0,    86,    87,
      88,     0,   120,     0,   198,     0,   121,     0,   122,     0,
      97,    98,   117,   118,     0,     0,     0,     0,   119,   107,
     108,   109,     2,    55,     0,   110,     0,   111,     0,   120,
     112,   148,   113,   121,     0,   122,     0,   114,     0,     0,
       0,   334,     0,     0,     0,   116,   107,   108,   109,     2,
      55,     0,   110,     0,   111,     0,     0,   112,     0,   113,
       0,     0,     0,     0,   114,     0,     0,     0,   334,     0,
       0,     0,   116,     0,   117,   118,     0,     0,     0,     0,
     119,    80,    81,    82,    83,    84,     0,     0,    87,     0,
       0,   120,   335,     0,     0,   121,     0,   122,     0,    97,
      98,   117,   118,     0,     0,     0,     0,   119,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   120,   371,
       0,     0,   121,     0,   122,   107,   108,   109,     2,    55,
       0,   110,     0,   111,     0,     0,   112,     0,   113,     0,
       0,     0,     0,   114,     0,     0,     0,   115,     0,     0,
       0,   116,   107,   108,   109,     2,    55,     0,   110,     0,
     111,     0,     0,   112,     0,   113,     0,     0,     0,     0,
     114,     0,     0,     0,   334,     0,     0,     0,   116,     0,
     117,   118,     0,     0,     0,     0,   119,    80,    81,    82,
      83,    84,     0,     0,     0,     0,     0,   120,     0,     0,
       0,   121,     0,   122,     0,    97,    98,   117,   118,     0,
       0,     0,     0,   119,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   216,   120,     0,     0,     0,   121,     0,
     122,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,     0,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,     0,   242,   243,
     244,   245,     0,     0,     0,     0,   217,   218,   219,   220,
     221,     0,   223,   224,   225,   226,   227,     0,   228,   229,
     230,   231,   232,   233,   234,   235,     0,     0,   246,   216,
     148,     0,   247,     0,   248,   249,     0,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,     0,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   246,   242,   243,   244,   245,     0,   248,
     249,     0,   217,   218,   219,   220,   221,     0,   223,   224,
     225,   226,     0,     0,   228,   229,   230,   231,   232,   233,
     234,   235,     0,     0,   246,   216,   325,     0,   247,     0,
     248,   249,     0,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,     0,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   246,
     242,   243,   244,   245,     0,   248,   249,     0,     0,   217,
     218,   219,   220,   221,     0,   223,   224,   225,     0,     0,
       0,   228,   229,   230,   231,   232,   233,   234,   235,     0,
     246,   328,   216,     0,   247,     0,   248,   249,     0,     0,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,     0,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   246,   242,   243,   244,
     245,     0,   248,   249,     0,   217,   218,   219,   220,   221,
       0,   223,   224,   225,     0,     0,     0,   228,   229,   230,
     231,     0,     0,   234,   235,     0,     0,   246,   216,     0,
     471,   247,   431,   248,   249,     0,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,     0,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   246,   242,   243,   244,   245,     0,   248,   249,
       0,   217,   218,   219,   220,   221,     0,   223,   224,   225,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   234,
     235,     0,     0,   246,   216,     0,   472,   247,     0,   248,
     249,     0,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,     0,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   246,   242,
     243,   244,   245,     0,   248,   249,     0,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,     0,    91,
      92,    93,    94,    95,    96,    97,    98,     0,     0,   246,
     216,     0,     0,   247,     0,   248,   249,     0,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,     0,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,     0,   242,   243,   244,   245,   500,
     481,     0,     0,   217,   218,   219,   220,   221,     0,   223,
     224,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   234,   235,     0,     0,   246,   216,     0,     0,   247,
       0,   248,   249,     0,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,     0,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     246,   242,   243,   244,   245,     0,   248,   249,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     0,
      91,    92,    93,    94,    95,    96,    97,    98,     0,     0,
       0,   246,   216,     0,     0,   247,     0,   248,   249,     0,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,     0,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   166,   242,   243,   244,
     245,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,     0,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   246,   242,   243,
     244,   245,     0,   248,   249,   217,   218,   219,   220,   221,
       0,     0,   224,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   235,     0,     0,     0,   246,     0,
       0,     0,   247,     0,   248,   249,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,     0,    91,    92,
      93,    94,    95,    96,    97,    98,     0,     0,     0,     0,
       0,     0,   246,     0,     0,     0,     0,     0,   248,   249,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,    91,    92,    93,    94,    95,    96,    97,    98,
       0,   469,     0,     0,     0,    99,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,     0,    91,    92,
      93,    94,    95,    96,    97,    98,     0,     0,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,   148,
      91,    92,    93,    94,    95,    96,    97,    98,    80,    81,
      82,    83,    84,     0,    86,    87,    88,    89,    90,     0,
      91,    92,    93,    94,    95,    96,    97,    98,    80,    81,
      82,    83,    84,     0,    86,    87,    88,    89,     0,     0,
      91,    92,    93,    94,    95,    96,    97,    98,    80,    81,
      82,    83,    84,     0,    86,    87,    88,     0,     0,     0,
      91,    92,    93,    94,    95,    96,    97,    98,    80,    81,
      82,    83,    84,     0,    86,    87,    88,     0,     0,     0,
      91,    92,    93,    94,     0,     0,    97,    98
};

static const yytype_int16 yycheck[] =
{
       0,   121,   285,   246,     4,     5,     6,     7,     4,     9,
      10,    11,    12,    13,    52,     4,   100,    73,     4,    72,
      58,     4,     4,    59,     5,     4,    26,    75,    26,     6,
      76,    59,    59,     6,     6,     7,     4,     9,    84,    10,
      40,    77,     6,    15,    44,    45,    46,    47,    11,    77,
      77,    75,    11,     0,    75,    13,    56,    81,    82,    59,
      60,    61,     6,    18,    19,    20,    83,    67,    75,    79,
      70,    71,    72,    73,    74,    82,    53,    49,    77,    83,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,    99,   102,   103,   104,   105,    74,    79,    75,    53,
      77,   111,    76,    76,    75,     6,     7,    76,     9,    77,
     120,   121,   122,   161,    15,    84,    59,     6,     7,    75,
       9,    77,    75,    66,    78,   135,    15,   137,    76,    50,
     140,   141,    63,     6,    65,    50,   146,   147,   148,    50,
      12,   151,   148,    65,   154,    75,    78,    77,    49,   148,
      76,   161,   148,    78,   164,   148,   148,   450,    12,   148,
      49,   310,   256,   312,    78,    78,   260,    77,    10,    50,
      44,    45,    46,    47,    78,   428,   469,     5,    79,    52,
      53,    54,    55,    50,    76,   315,   164,    76,    18,    19,
      20,    21,    22,    67,    10,    84,    76,   207,   120,    72,
      73,    74,    80,    50,   214,   215,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    13,    76,    80,    12,    78,
      12,   105,    77,    77,   300,   298,   246,    60,   248,   249,
      18,    19,    20,   253,   254,    50,   256,   257,    60,   259,
     260,    78,    40,    50,    76,     6,     7,   267,     9,    76,
     270,   135,    13,   137,    15,    76,   276,    76,    56,    84,
     192,    59,    60,    61,    12,   285,    67,    78,    76,   285,
      10,    13,    78,   205,   332,    13,   285,    76,   298,   285,
     300,    78,   285,   285,    60,    78,   285,    75,    49,    78,
     310,   481,   312,    81,    82,   315,   316,    83,   318,   319,
      83,   270,   100,   414,   102,   417,   326,   327,    69,   473,
      71,   420,     6,     7,   334,     9,   336,     6,     7,     4,
       9,    15,    83,   164,   122,   401,    15,   403,    18,    19,
      20,    21,    22,   120,    24,    25,     6,     7,   384,     9,
     272,   405,   140,   141,     4,    15,    36,    37,   146,   147,
      13,    -1,    -1,   151,    -1,    49,   154,    -1,     6,     7,
      49,     9,    -1,   161,   384,    -1,    -1,    15,    -1,    -1,
      -1,    -1,   392,   393,    -1,     6,     7,    40,     9,    49,
      69,   401,    71,   403,    15,   317,     6,     7,    -1,     9,
      10,    -1,    -1,    56,    83,    15,    59,    60,    61,   419,
     332,    49,     6,     7,    -1,     9,    -1,    77,   428,   207,
      -1,    15,   432,    -1,    -1,    -1,   214,    -1,    49,    -1,
      -1,    69,   442,    71,   442,    -1,    -1,    -1,    -1,    49,
     450,    -1,    -1,    -1,   450,    83,    -1,   100,    69,   102,
      71,   450,    -1,    -1,   450,    49,    -1,   450,   450,   469,
     248,   450,    83,   469,    -1,   253,   254,   389,   256,   122,
     469,   259,   260,   469,    -1,   485,   469,   469,   488,    -1,
     469,   491,   492,    -1,   494,    79,   496,   140,   276,   499,
     500,    -1,    -1,   146,   147,   417,    61,    -1,   151,     6,
       7,    -1,     9,    -1,   426,    -1,    -1,    -1,    15,    74,
      -1,    -1,    -1,     0,     1,    -1,   438,    -1,   392,     6,
      -1,    -1,    -1,   445,    -1,    12,     3,     4,    -1,     6,
     318,    -1,    -1,    -1,    -1,   100,    -1,    14,   326,   327,
      -1,    -1,    49,    -1,    21,   419,    -1,    -1,   336,    -1,
      -1,   473,    29,   475,    -1,   120,   478,    -1,    -1,    -1,
      -1,   214,    -1,    -1,    51,    52,    53,    54,    55,    76,
       6,     7,    59,     9,    10,    57,    -1,    -1,    -1,    15,
      -1,    -1,    -1,   148,    -1,    72,    73,    74,    -1,    -1,
      -1,    78,    -1,    -1,    -1,   248,   384,    -1,    75,   164,
     253,   254,    -1,   256,     0,     1,   259,   260,     6,     7,
       6,     9,    10,    49,    -1,    -1,    12,    15,   492,    -1,
     494,    -1,    -1,    18,    19,    20,    21,    22,   110,    -1,
     112,   113,   114,   115,   116,    -1,   118,   119,   120,    -1,
      -1,    36,    37,    -1,   432,     6,     7,    -1,     9,    10,
     215,    49,    -1,    -1,    15,    51,    52,    53,    54,    55,
      -1,     6,     7,    59,     9,   318,    -1,    12,    -1,    -1,
      15,    -1,    -1,   326,   327,    -1,    72,    73,    74,    -1,
      75,   246,    -1,    -1,    -1,    -1,    81,    82,    49,     6,
       7,   256,     9,    -1,    -1,   260,    -1,   485,    15,    -1,
     488,    -1,    -1,   491,    49,   270,    -1,    -1,   496,    -1,
      -1,   499,   500,    -1,    -1,    -1,   198,    -1,    -1,    -1,
     285,    -1,    -1,    -1,    69,    -1,    71,    -1,    -1,    -1,
      75,   384,    49,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,    -1,     6,     7,   334,
       9,     6,     7,    -1,     9,    -1,    15,    -1,    -1,   432,
      15,    -1,    -1,    -1,   266,    -1,    -1,    -1,   270,   271,
      -1,   273,    -1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    -1,    11,    -1,    -1,    14,     1,    16,    -1,    -1,
      49,     6,    21,    -1,    49,    -1,    25,    12,     6,     7,
      29,     9,    -1,    -1,    -1,    -1,    -1,    15,    -1,   311,
      -1,    -1,   485,    -1,    69,   488,    71,    -1,   491,    -1,
      75,    -1,    -1,   496,    -1,    -1,   499,   500,   330,    58,
      59,    -1,   334,    -1,    -1,    64,    51,    52,    53,    54,
      55,    49,    -1,   428,    59,    -1,    75,    -1,    -1,    -1,
      79,    -1,    81,    82,    -1,    -1,    -1,    72,    73,    74,
      -1,    69,    -1,    71,    -1,   450,    18,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   469,     1,    -1,     3,     4,     5,
       6,     7,    -1,     9,    -1,    11,    12,    -1,    14,    -1,
      16,    -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    25,
      -1,    -1,   414,    29,    -1,    -1,    -1,    -1,    -1,    -1,
     422,   423,    -1,    75,    -1,    -1,   428,    -1,    -1,    81,
      82,    -1,    -1,   435,    -1,   437,    52,    -1,    54,    55,
      56,    57,    58,    59,   446,    61,    62,    63,    64,    65,
      66,    67,    68,    -1,    70,    71,    -1,    73,    74,    75,
     462,    77,    78,    79,    -1,    81,    -1,    -1,    -1,   471,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,   481,
      11,    12,    -1,    14,   486,    16,    -1,   489,    -1,    -1,
      21,    -1,    -1,    -1,    25,    -1,    -1,    -1,    29,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    52,    -1,    54,    55,    56,    57,    58,    59,    -1,
      61,    62,    -1,    64,    -1,    66,    67,    68,    -1,    70,
      71,    -1,    73,    74,    75,    -1,    77,    78,    79,     1,
      81,     3,     4,     5,     6,     7,    -1,     9,    -1,    11,
      12,    80,    14,    -1,    16,    -1,    -1,    -1,    -1,    21,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    29,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      52,    -1,    54,    55,    56,    57,    58,    59,    -1,    61,
      62,    -1,    64,    -1,    66,    67,    68,    -1,    70,    71,
      -1,    73,    74,    75,    -1,    77,    -1,    79,    -1,    81,
       3,     4,     5,     6,     7,    -1,     9,    -1,    11,    -1,
      80,    14,    -1,    16,    -1,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    29,     3,     4,     5,
       6,     7,    -1,     9,    -1,    11,    -1,    -1,    14,    -1,
      16,    -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    29,    -1,    58,    59,    -1,    -1,    -1,
      -1,    64,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    75,    -1,    77,    -1,    79,    -1,    81,    -1,
      36,    37,    58,    59,    -1,    -1,    -1,    -1,    64,     3,
       4,     5,     6,     7,    -1,     9,    -1,    11,    -1,    75,
      14,    77,    16,    79,    -1,    81,    -1,    21,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    29,     3,     4,     5,     6,
       7,    -1,     9,    -1,    11,    -1,    -1,    14,    -1,    16,
      -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    29,    -1,    58,    59,    -1,    -1,    -1,    -1,
      64,    18,    19,    20,    21,    22,    -1,    -1,    25,    -1,
      -1,    75,    76,    -1,    -1,    79,    -1,    81,    -1,    36,
      37,    58,    59,    -1,    -1,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      -1,    -1,    79,    -1,    81,     3,     4,     5,     6,     7,
      -1,     9,    -1,    11,    -1,    -1,    14,    -1,    16,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    29,     3,     4,     5,     6,     7,    -1,     9,    -1,
      11,    -1,    -1,    14,    -1,    16,    -1,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    25,    -1,    -1,    -1,    29,    -1,
      58,    59,    -1,    -1,    -1,    -1,    64,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,
      -1,    79,    -1,    81,    -1,    36,    37,    58,    59,    -1,
      -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    10,    75,    -1,    -1,    -1,    79,    -1,
      81,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    48,    -1,    -1,    -1,    -1,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    75,    10,
      77,    -1,    79,    -1,    81,    82,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    75,    45,    46,    47,    48,    -1,    81,
      82,    -1,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    75,    10,    77,    -1,    79,    -1,
      81,    82,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    75,
      45,    46,    47,    48,    -1,    81,    82,    -1,    -1,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      75,    76,    10,    -1,    79,    -1,    81,    82,    -1,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    75,    45,    46,    47,
      48,    -1,    81,    82,    -1,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    36,    37,    -1,    -1,    75,    10,    -1,
      12,    79,    80,    81,    82,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    75,    45,    46,    47,    48,    -1,    81,    82,
      -1,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    75,    10,    -1,    12,    79,    -1,    81,
      82,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    75,    45,
      46,    47,    48,    -1,    81,    82,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    75,
      10,    -1,    -1,    79,    -1,    81,    82,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    45,    46,    47,    48,    80,
      50,    -1,    -1,    18,    19,    20,    21,    22,    -1,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    -1,    -1,    75,    10,    -1,    -1,    79,
      -1,    81,    82,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      75,    45,    46,    47,    48,    -1,    81,    82,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    75,    10,    -1,    -1,    79,    -1,    81,    82,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    76,    45,    46,    47,
      48,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    75,    45,    46,
      47,    48,    -1,    81,    82,    18,    19,    20,    21,    22,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    79,    -1,    81,    82,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    81,    82,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    13,    -1,    -1,    -1,    77,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    77,
      30,    31,    32,    33,    34,    35,    36,    37,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    12,    51,    52,    53,    54,    55,    59,
      72,    73,    74,    86,    90,   111,   129,   133,   136,   140,
     141,   144,   145,   146,   147,   148,   149,   150,   151,    90,
     111,   129,   133,   136,   140,   141,   144,   148,    86,    86,
      86,     5,     3,     4,    14,    21,    29,    75,    86,    99,
     100,   101,    86,    86,    86,     7,     9,    15,    49,    69,
      71,    75,    86,    87,   124,   125,   126,    10,   150,     0,
      75,    77,    75,    77,    77,   126,   101,   101,   101,   101,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    30,    31,    32,    33,    34,    35,    36,    37,    77,
      75,   124,    13,    77,    75,    79,   126,     3,     4,     5,
       9,    11,    14,    16,    21,    25,    29,    58,    59,    64,
      75,    79,    81,    86,    87,    89,    91,    92,    93,   102,
     115,   116,   120,   130,   124,    10,   126,    10,   126,    76,
      84,    86,    96,    97,   126,   127,    83,    79,    77,   109,
     101,    86,   134,   135,    86,   127,   131,   132,   135,   132,
      78,    86,   127,   133,   137,   138,    76,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   150,    97,   126,    86,
     142,   143,    76,    86,   110,   101,   102,    86,    77,   102,
     102,   102,   102,   102,    75,   102,   102,    86,   102,   109,
     127,   128,   110,   126,    83,    75,    10,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    45,    46,    47,    48,    75,    79,    81,    82,
     101,   101,   126,    69,    71,   126,    50,    11,    76,    84,
      50,   126,   126,   139,     1,    12,    56,    57,    61,    62,
      66,    67,    68,    70,    71,    78,    86,    88,    90,    98,
     102,   103,   104,   105,   106,   107,   108,   109,   111,   117,
     123,   127,   128,   136,   140,   141,   144,   126,    50,    76,
      12,    78,    76,    78,    12,   124,    12,   138,    78,    78,
      77,    10,    50,    78,   109,    50,    11,    76,    80,    82,
     102,   113,   114,     5,   109,    77,    69,    71,    76,    76,
      10,    76,    80,   126,    25,    76,    86,    94,    95,   102,
     127,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,    76,    95,   102,   126,    86,    76,   126,   126,    97,
      86,    76,   126,    97,    50,    80,   102,    86,    94,   102,
     109,   102,    59,    66,   121,   122,    13,    12,   108,    78,
     135,    77,   132,    77,    12,    60,   143,   102,   143,   110,
      86,   109,   126,    86,    50,    78,    76,    60,    63,    65,
     118,   119,    10,    10,   102,   109,   124,   127,    50,    76,
      76,    80,    84,    76,   139,    12,   109,    67,   101,    86,
     132,   132,    77,   145,    78,    76,    10,   114,   109,   116,
      13,   101,   119,    78,   102,   102,   109,    95,   126,   102,
     102,   109,    13,    78,    78,   150,   109,   102,   108,    13,
      76,    12,    12,    60,   102,   112,    78,   108,   102,   109,
     122,    50,   109,   109,   112,     9,    15,    86,     9,    15,
      86,    83,    79,   102,    79,   102,    83,   101,   101,    80,
      80
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    88,    88,    89,    90,    91,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    93,    93,
      93,    93,    93,    94,    94,    94,    95,    95,    96,    97,
      97,    97,    97,    98,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,   100,   100,   100,   101,   101,   101,   101,
     101,   101,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   103,   104,
     105,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   107,   108,   108,   108,   109,   109,   110,
     110,   111,   111,   111,   112,   112,   113,   113,   114,   114,
     115,   116,   116,   116,   117,   118,   118,   119,   119,   120,
     121,   122,   122,   122,   123,   123,   124,   124,   124,   124,
     124,   125,   125,   126,   126,   126,   126,   126,   126,   126,
     127,   127,   127,   128,   128,   128,   129,   129,   130,   130,
     131,   132,   132,   133,   133,   134,   135,   135,   136,   136,
     137,   137,   137,   137,   138,   138,   139,   139,   140,   141,
     141,   142,   142,   143,   143,   143,   144,   144,   145,   145,
     145,   146,   146,   146,   147,   147,   147,   148,   148,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     150,   150,   151,   151
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     4,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     2,     1,     1,     3,     1,     1,     3,
       3,     1,     1,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     3,     2,     1,     1,     1,     3,     1,
       4,     3,     4,     4,     3,     1,     1,     3,     2,     3,
       3,     2,     1,     1,     1,     1,     1,     3,     3,     5,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     3,     2,     3,
       1,     6,     8,     5,     3,     1,     1,     4,     3,     1,
       4,     3,     5,     5,     7,     4,     3,     2,     1,     5,
       5,     3,     5,     5,     2,     2,     5,     3,     4,     4,
       2,     1,     7,     1,     2,     4,     2,     5,     2,     3,
       3,     3,     2,     3,     4,     4,     3,     3,     5,     4,
       1,     3,     2,     5,     8,     2,     3,     1,     5,     8,
       2,     3,     2,     1,     2,     1,     3,     1,     3,     5,
       4,     1,     3,     3,     2,     1,     7,     5,     5,     9,
       7,     3,     3,     2,     3,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     2,     1,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, scanner, parser, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner, parser); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct parser* parser)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (parser);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct parser* parser)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner, parser);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, void *scanner, struct parser* parser)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner, parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, parser); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void *scanner, struct parser* parser)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (parser);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_INT: /* INT  */
#line 159 "src/parser.y"
            {}
#line 2031 "gen/gen_parser.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 159 "src/parser.y"
            {}
#line 2037 "gen/gen_parser.c"
        break;

    case YYSYMBOL_STRING: /* STRING  */
#line 159 "src/parser.y"
            {}
#line 2043 "gen/gen_parser.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 159 "src/parser.y"
            {}
#line 2049 "gen/gen_parser.c"
        break;

    case YYSYMBOL_APPLY: /* APPLY  */
#line 159 "src/parser.y"
            {}
#line 2055 "gen/gen_parser.c"
        break;

    case YYSYMBOL_id: /* id  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2061 "gen/gen_parser.c"
        break;

    case YYSYMBOL_apply: /* apply  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2067 "gen/gen_parser.c"
        break;

    case YYSYMBOL_var: /* var  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2073 "gen/gen_parser.c"
        break;

    case YYSYMBOL_embed: /* embed  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2079 "gen/gen_parser.c"
        break;

    case YYSYMBOL_import: /* import  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2085 "gen/gen_parser.c"
        break;

    case YYSYMBOL_assign: /* assign  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2091 "gen/gen_parser.c"
        break;

    case YYSYMBOL_binop: /* binop  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2097 "gen/gen_parser.c"
        break;

    case YYSYMBOL_unop: /* unop  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2103 "gen/gen_parser.c"
        break;

    case YYSYMBOL_arg: /* arg  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2109 "gen/gen_parser.c"
        break;

    case YYSYMBOL_args: /* args  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2115 "gen/gen_parser.c"
        break;

    case YYSYMBOL_param_decl: /* param_decl  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2121 "gen/gen_parser.c"
        break;

    case YYSYMBOL_decls: /* decls  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2127 "gen/gen_parser.c"
        break;

    case YYSYMBOL_defer: /* defer  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2133 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_binop: /* const_binop  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2139 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_unop: /* const_unop  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2145 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_expr: /* const_expr  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2151 "gen/gen_parser.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2157 "gen/gen_parser.c"
        break;

    case YYSYMBOL_while: /* while  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2163 "gen/gen_parser.c"
        break;

    case YYSYMBOL_do_while: /* do_while  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2169 "gen/gen_parser.c"
        break;

    case YYSYMBOL_goto: /* goto  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2175 "gen/gen_parser.c"
        break;

    case YYSYMBOL_statelet: /* statelet  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2181 "gen/gen_parser.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2187 "gen/gen_parser.c"
        break;

    case YYSYMBOL_statements: /* statements  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2193 "gen/gen_parser.c"
        break;

    case YYSYMBOL_body: /* body  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2199 "gen/gen_parser.c"
        break;

    case YYSYMBOL_references: /* references  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2205 "gen/gen_parser.c"
        break;

    case YYSYMBOL_macro: /* macro  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2211 "gen/gen_parser.c"
        break;

    case YYSYMBOL_exprs: /* exprs  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2217 "gen/gen_parser.c"
        break;

    case YYSYMBOL_construct_arg: /* construct_arg  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2223 "gen/gen_parser.c"
        break;

    case YYSYMBOL_construct_args: /* construct_args  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2229 "gen/gen_parser.c"
        break;

    case YYSYMBOL_construct: /* construct  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2235 "gen/gen_parser.c"
        break;

    case YYSYMBOL_if: /* if  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2241 "gen/gen_parser.c"
        break;

    case YYSYMBOL_for: /* for  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2247 "gen/gen_parser.c"
        break;

    case YYSYMBOL_case: /* case  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2253 "gen/gen_parser.c"
        break;

    case YYSYMBOL_cases: /* cases  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2259 "gen/gen_parser.c"
        break;

    case YYSYMBOL_switch: /* switch  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2265 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_for: /* const_for  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2271 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_if: /* const_if  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2277 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const: /* const  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2283 "gen/gen_parser.c"
        break;

    case YYSYMBOL_simple_sign: /* simple_sign  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2289 "gen/gen_parser.c"
        break;

    case YYSYMBOL_func_sign: /* func_sign  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2295 "gen/gen_parser.c"
        break;

    case YYSYMBOL_type: /* type  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2301 "gen/gen_parser.c"
        break;

    case YYSYMBOL_var_decl: /* var_decl  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2307 "gen/gen_parser.c"
        break;

    case YYSYMBOL_var_init: /* var_init  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2313 "gen/gen_parser.c"
        break;

    case YYSYMBOL_proc: /* proc  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2319 "gen/gen_parser.c"
        break;

    case YYSYMBOL_lambda: /* lambda  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2325 "gen/gen_parser.c"
        break;

    case YYSYMBOL_struct_elem: /* struct_elem  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2331 "gen/gen_parser.c"
        break;

    case YYSYMBOL_members: /* members  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2337 "gen/gen_parser.c"
        break;

    case YYSYMBOL_union: /* union  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2343 "gen/gen_parser.c"
        break;

    case YYSYMBOL_generic: /* generic  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2349 "gen/gen_parser.c"
        break;

    case YYSYMBOL_generics: /* generics  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2355 "gen/gen_parser.c"
        break;

    case YYSYMBOL_struct: /* struct  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2361 "gen/gen_parser.c"
        break;

    case YYSYMBOL_template_elem: /* template_elem  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2367 "gen/gen_parser.c"
        break;

    case YYSYMBOL_template_elems: /* template_elems  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2373 "gen/gen_parser.c"
        break;

    case YYSYMBOL_types: /* types  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2379 "gen/gen_parser.c"
        break;

    case YYSYMBOL_alias: /* alias  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2385 "gen/gen_parser.c"
        break;

    case YYSYMBOL_template: /* template  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2391 "gen/gen_parser.c"
        break;

    case YYSYMBOL_enum_val: /* enum_val  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2397 "gen/gen_parser.c"
        break;

    case YYSYMBOL_enums: /* enums  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2403 "gen/gen_parser.c"
        break;

    case YYSYMBOL_enum: /* enum  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2409 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top_if: /* top_if  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2415 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top_var_decl: /* top_var_decl  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2421 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top_var_init: /* top_var_init  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2427 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top_var: /* top_var  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2433 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top: /* top  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2439 "gen/gen_parser.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2445 "gen/gen_parser.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner, struct parser* parser)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner, parser);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* id: ID  */
#line 165 "src/parser.y"
             {
		(yyval.node) = gen_id(strdup((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 2754 "gen/gen_parser.c"
    break;

  case 3: /* apply: APPLY  */
#line 171 "src/parser.y"
                {
		(yyval.node) = gen_id(strdup((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 2763 "gen/gen_parser.c"
    break;

  case 4: /* var: var_decl  */
#line 177 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2769 "gen/gen_parser.c"
    break;

  case 5: /* var: var_init  */
#line 178 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2775 "gen/gen_parser.c"
    break;

  case 6: /* embed: "embed" "(" STRING ")"  */
#line 181 "src/parser.y"
                                 { (yyval.node) = gen_embed(clone_string((yyvsp[-1].str)));  }
#line 2781 "gen/gen_parser.c"
    break;

  case 7: /* import: "import" STRING  */
#line 184 "src/parser.y"
                          { (yyval.node) = gen_import(clone_string((yyvsp[0].str)));  }
#line 2787 "gen/gen_parser.c"
    break;

  case 8: /* assign: expr "=" expr  */
#line 187 "src/parser.y"
                        { (yyval.node) = gen_assign((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2793 "gen/gen_parser.c"
    break;

  case 9: /* binop: expr "+" expr  */
#line 190 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2799 "gen/gen_parser.c"
    break;

  case 10: /* binop: expr "-" expr  */
#line 191 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2805 "gen/gen_parser.c"
    break;

  case 11: /* binop: expr "*" expr  */
#line 192 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2811 "gen/gen_parser.c"
    break;

  case 12: /* binop: expr "/" expr  */
#line 193 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2817 "gen/gen_parser.c"
    break;

  case 13: /* binop: expr "%" expr  */
#line 194 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2823 "gen/gen_parser.c"
    break;

  case 14: /* binop: expr "^" expr  */
#line 195 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2829 "gen/gen_parser.c"
    break;

  case 15: /* binop: expr "^^" expr  */
#line 196 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_POW, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2835 "gen/gen_parser.c"
    break;

  case 16: /* binop: expr "&" expr  */
#line 197 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2841 "gen/gen_parser.c"
    break;

  case 17: /* binop: expr "&&" expr  */
#line 198 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LAND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2847 "gen/gen_parser.c"
    break;

  case 18: /* binop: expr "|" expr  */
#line 199 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2853 "gen/gen_parser.c"
    break;

  case 19: /* binop: expr "||" expr  */
#line 200 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2859 "gen/gen_parser.c"
    break;

  case 20: /* binop: expr "<<" expr  */
#line 201 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2865 "gen/gen_parser.c"
    break;

  case 21: /* binop: expr ">>" expr  */
#line 202 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2871 "gen/gen_parser.c"
    break;

  case 22: /* binop: expr "+=" expr  */
#line 203 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2877 "gen/gen_parser.c"
    break;

  case 23: /* binop: expr "-=" expr  */
#line 204 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2883 "gen/gen_parser.c"
    break;

  case 24: /* binop: expr "*=" expr  */
#line 205 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2889 "gen/gen_parser.c"
    break;

  case 25: /* binop: expr "/=" expr  */
#line 206 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2895 "gen/gen_parser.c"
    break;

  case 26: /* binop: expr "%=" expr  */
#line 207 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2901 "gen/gen_parser.c"
    break;

  case 27: /* binop: expr "&=" expr  */
#line 208 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2907 "gen/gen_parser.c"
    break;

  case 28: /* binop: expr "|=" expr  */
#line 209 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2913 "gen/gen_parser.c"
    break;

  case 29: /* binop: expr "^=" expr  */
#line 210 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2919 "gen/gen_parser.c"
    break;

  case 30: /* binop: expr "<<=" expr  */
#line 211 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2927 "gen/gen_parser.c"
    break;

  case 31: /* binop: expr ">>=" expr  */
#line 214 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2935 "gen/gen_parser.c"
    break;

  case 32: /* binop: expr "<" expr  */
#line 217 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_LT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2941 "gen/gen_parser.c"
    break;

  case 33: /* binop: expr ">" expr  */
#line 218 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_GT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2947 "gen/gen_parser.c"
    break;

  case 34: /* binop: expr "<=" expr  */
#line 219 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2953 "gen/gen_parser.c"
    break;

  case 35: /* binop: expr ">=" expr  */
#line 220 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_GE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2959 "gen/gen_parser.c"
    break;

  case 36: /* binop: expr "!=" expr  */
#line 221 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_NE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2965 "gen/gen_parser.c"
    break;

  case 37: /* binop: expr "==" expr  */
#line 222 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_EQ, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2971 "gen/gen_parser.c"
    break;

  case 38: /* unop: "-" expr  */
#line 225 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NEG, (yyvsp[0].node));  }
#line 2977 "gen/gen_parser.c"
    break;

  case 39: /* unop: "!" expr  */
#line 226 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_LNOT, (yyvsp[0].node));  }
#line 2983 "gen/gen_parser.c"
    break;

  case 40: /* unop: "&" expr  */
#line 227 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 2989 "gen/gen_parser.c"
    break;

  case 41: /* unop: "'" expr  */
#line 228 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_DEREF, (yyvsp[0].node));  }
#line 2995 "gen/gen_parser.c"
    break;

  case 42: /* unop: "~" expr  */
#line 229 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NOT, (yyvsp[0].node));  }
#line 3001 "gen/gen_parser.c"
    break;

  case 43: /* arg: "&" var_decl  */
#line 232 "src/parser.y"
                       { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 3007 "gen/gen_parser.c"
    break;

  case 44: /* arg: var_decl  */
#line 233 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3013 "gen/gen_parser.c"
    break;

  case 45: /* arg: expr  */
#line 234 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3019 "gen/gen_parser.c"
    break;

  case 46: /* args: arg "," args  */
#line 237 "src/parser.y"
                       { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3025 "gen/gen_parser.c"
    break;

  case 47: /* args: arg  */
#line 238 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3031 "gen/gen_parser.c"
    break;

  case 48: /* param_decl: type  */
#line 241 "src/parser.y"
               { (yyval.node) = gen_var(NULL, (yyvsp[0].node), NULL);  }
#line 3037 "gen/gen_parser.c"
    break;

  case 49: /* decls: var_decl "," decls  */
#line 244 "src/parser.y"
                             { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3043 "gen/gen_parser.c"
    break;

  case 50: /* decls: param_decl "," decls  */
#line 245 "src/parser.y"
                               { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3049 "gen/gen_parser.c"
    break;

  case 51: /* decls: var_decl  */
#line 246 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3055 "gen/gen_parser.c"
    break;

  case 52: /* decls: param_decl  */
#line 247 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 3061 "gen/gen_parser.c"
    break;

  case 53: /* defer: "defer" expr  */
#line 250 "src/parser.y"
                       { (yyval.node) = gen_defer((yyvsp[0].node));  }
#line 3067 "gen/gen_parser.c"
    break;

  case 54: /* const_binop: const_expr "+" const_expr  */
#line 253 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3073 "gen/gen_parser.c"
    break;

  case 55: /* const_binop: const_expr "-" const_expr  */
#line 254 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3079 "gen/gen_parser.c"
    break;

  case 56: /* const_binop: const_expr "*" const_expr  */
#line 255 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3085 "gen/gen_parser.c"
    break;

  case 57: /* const_binop: const_expr "/" const_expr  */
#line 256 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3091 "gen/gen_parser.c"
    break;

  case 58: /* const_binop: const_expr "%" const_expr  */
#line 257 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3097 "gen/gen_parser.c"
    break;

  case 59: /* const_binop: const_expr "^" const_expr  */
#line 258 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3103 "gen/gen_parser.c"
    break;

  case 60: /* const_binop: const_expr "^^" const_expr  */
#line 259 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_POW, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3109 "gen/gen_parser.c"
    break;

  case 61: /* const_binop: const_expr "&" const_expr  */
#line 260 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3115 "gen/gen_parser.c"
    break;

  case 62: /* const_binop: const_expr "&&" const_expr  */
#line 261 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_LAND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3121 "gen/gen_parser.c"
    break;

  case 63: /* const_binop: const_expr "|" const_expr  */
#line 262 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3127 "gen/gen_parser.c"
    break;

  case 64: /* const_binop: const_expr "||" const_expr  */
#line 263 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_LOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3133 "gen/gen_parser.c"
    break;

  case 65: /* const_binop: const_expr "<<" const_expr  */
#line 264 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3139 "gen/gen_parser.c"
    break;

  case 66: /* const_binop: const_expr ">>" const_expr  */
#line 265 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3145 "gen/gen_parser.c"
    break;

  case 67: /* const_binop: const_expr "<" const_expr  */
#line 266 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_LT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3151 "gen/gen_parser.c"
    break;

  case 68: /* const_binop: const_expr ">" const_expr  */
#line 267 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_GT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3157 "gen/gen_parser.c"
    break;

  case 69: /* const_binop: const_expr "<=" const_expr  */
#line 268 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_LE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3163 "gen/gen_parser.c"
    break;

  case 70: /* const_binop: const_expr ">=" const_expr  */
#line 269 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_GE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3169 "gen/gen_parser.c"
    break;

  case 71: /* const_binop: const_expr "!=" const_expr  */
#line 270 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_NE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3175 "gen/gen_parser.c"
    break;

  case 72: /* const_binop: const_expr "==" const_expr  */
#line 271 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_EQ, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3181 "gen/gen_parser.c"
    break;

  case 73: /* const_unop: "-" const_expr  */
#line 274 "src/parser.y"
                         { (yyval.node) = gen_unop(AST_NEG, (yyvsp[0].node));  }
#line 3187 "gen/gen_parser.c"
    break;

  case 74: /* const_unop: "!" const_expr  */
#line 275 "src/parser.y"
                         { (yyval.node) = gen_unop(AST_LNOT, (yyvsp[0].node));  }
#line 3193 "gen/gen_parser.c"
    break;

  case 75: /* const_unop: "~" const_expr  */
#line 276 "src/parser.y"
                         { (yyval.node) = gen_unop(AST_NOT, (yyvsp[0].node));  }
#line 3199 "gen/gen_parser.c"
    break;

  case 76: /* const_expr: "(" const_expr ")"  */
#line 279 "src/parser.y"
                             { (yyval.node) = (yyvsp[-1].node); }
#line 3205 "gen/gen_parser.c"
    break;

  case 77: /* const_expr: id  */
#line 280 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3211 "gen/gen_parser.c"
    break;

  case 78: /* const_expr: INT  */
#line 281 "src/parser.y"
              { (yyval.node) = gen_int((yyvsp[0].integer)); }
#line 3217 "gen/gen_parser.c"
    break;

  case 79: /* const_expr: FLOAT  */
#line 282 "src/parser.y"
                { (yyval.node) = gen_float((yyvsp[0].dbl)); }
#line 3223 "gen/gen_parser.c"
    break;

  case 80: /* const_expr: const_binop  */
#line 283 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3229 "gen/gen_parser.c"
    break;

  case 81: /* const_expr: const_unop  */
#line 284 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 3235 "gen/gen_parser.c"
    break;

  case 82: /* expr: id  */
#line 288 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3241 "gen/gen_parser.c"
    break;

  case 83: /* expr: expr "." id  */
#line 289 "src/parser.y"
                      { (yyval.node) = gen_dot((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3247 "gen/gen_parser.c"
    break;

  case 84: /* expr: "..." id  */
#line 290 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3253 "gen/gen_parser.c"
    break;

  case 85: /* expr: INT  */
#line 291 "src/parser.y"
              { (yyval.node) = gen_int((yyvsp[0].integer)); (yyval.node)->loc = to_src_loc(&yylloc); }
#line 3259 "gen/gen_parser.c"
    break;

  case 86: /* expr: FLOAT  */
#line 292 "src/parser.y"
                { (yyval.node) = gen_float((yyvsp[0].dbl)); (yyval.node)->loc = to_src_loc(&yylloc);  }
#line 3265 "gen/gen_parser.c"
    break;

  case 87: /* expr: STRING  */
#line 293 "src/parser.y"
                 {
		(yyval.node) = gen_string(clone_string((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 3274 "gen/gen_parser.c"
    break;

  case 88: /* expr: "(" expr ")"  */
#line 297 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3280 "gen/gen_parser.c"
    break;

  case 89: /* expr: assign  */
#line 298 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3286 "gen/gen_parser.c"
    break;

  case 90: /* expr: expr "(" args ")"  */
#line 299 "src/parser.y"
                            { (yyval.node) = gen_call((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3292 "gen/gen_parser.c"
    break;

  case 91: /* expr: expr "(" ")"  */
#line 300 "src/parser.y"
                       { (yyval.node) = gen_call((yyvsp[-2].node), NULL); }
#line 3298 "gen/gen_parser.c"
    break;

  case 92: /* expr: expr "[" expr "]"  */
#line 301 "src/parser.y"
                            { (yyval.node) = gen_call((yyvsp[-3].node), (yyvsp[-1].node)); /** @todo add arr access */}
#line 3304 "gen/gen_parser.c"
    break;

  case 93: /* expr: apply "(" args ")"  */
#line 302 "src/parser.y"
                             { (yyval.node) = gen_call((yyvsp[-3].node), (yyvsp[-1].node)); /* macro call */}
#line 3310 "gen/gen_parser.c"
    break;

  case 94: /* expr: apply "(" ")"  */
#line 303 "src/parser.y"
                        { (yyval.node) = gen_call((yyvsp[-2].node), NULL); /* macro call */}
#line 3316 "gen/gen_parser.c"
    break;

  case 95: /* expr: binop  */
#line 304 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3322 "gen/gen_parser.c"
    break;

  case 96: /* expr: unop  */
#line 305 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3328 "gen/gen_parser.c"
    break;

  case 97: /* expr: "(" var_init ")"  */
#line 306 "src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 3334 "gen/gen_parser.c"
    break;

  case 98: /* expr: "sizeof" expr  */
#line 307 "src/parser.y"
                        { (yyval.node) = gen_sizeof((yyvsp[0].node)); }
#line 3340 "gen/gen_parser.c"
    break;

  case 99: /* expr: expr "as" type  */
#line 308 "src/parser.y"
                         { (yyval.node) = gen_cast((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3346 "gen/gen_parser.c"
    break;

  case 100: /* expr: id "::" type  */
#line 309 "src/parser.y"
                       { (yyval.node) = gen_fetch((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3352 "gen/gen_parser.c"
    break;

  case 101: /* expr: "as" type  */
#line 310 "src/parser.y"
                    { (yyval.node) = gen_as((yyvsp[0].node)); }
#line 3358 "gen/gen_parser.c"
    break;

  case 102: /* expr: embed  */
#line 311 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3364 "gen/gen_parser.c"
    break;

  case 103: /* expr: lambda  */
#line 312 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3370 "gen/gen_parser.c"
    break;

  case 104: /* expr: if  */
#line 313 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3376 "gen/gen_parser.c"
    break;

  case 105: /* expr: switch  */
#line 314 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3382 "gen/gen_parser.c"
    break;

  case 106: /* expr: construct  */
#line 315 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3388 "gen/gen_parser.c"
    break;

  case 107: /* expr: "(" body ")"  */
#line 316 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3394 "gen/gen_parser.c"
    break;

  case 108: /* while: "while" expr body  */
#line 319 "src/parser.y"
                            { (yyval.node) = gen_while((yyvsp[-1].node), (yyvsp[0].node));  }
#line 3400 "gen/gen_parser.c"
    break;

  case 109: /* do_while: "do" body "while" expr ";"  */
#line 322 "src/parser.y"
                                     {
		(yyval.node) = gen_while((yyvsp[-3].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_DELAYED);
	}
#line 3409 "gen/gen_parser.c"
    break;

  case 110: /* goto: "goto" id  */
#line 328 "src/parser.y"
                    { (yyval.node) = gen_goto(gen_label((yyvsp[0].node)));  }
#line 3415 "gen/gen_parser.c"
    break;

  case 111: /* statelet: expr  */
#line 331 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3421 "gen/gen_parser.c"
    break;

  case 112: /* statelet: "return" expr  */
#line 332 "src/parser.y"
                        { (yyval.node) = gen_return((yyvsp[0].node));  }
#line 3427 "gen/gen_parser.c"
    break;

  case 113: /* statelet: "return"  */
#line 333 "src/parser.y"
                   { (yyval.node) = gen_return(NULL); }
#line 3433 "gen/gen_parser.c"
    break;

  case 114: /* statelet: "break"  */
#line 334 "src/parser.y"
                  { (yyval.node) = gen_ctrl(AST_CTRL_BREAK, to_src_loc(&yylloc)); }
#line 3439 "gen/gen_parser.c"
    break;

  case 115: /* statelet: "continue"  */
#line 335 "src/parser.y"
                     { (yyval.node) = gen_ctrl(AST_CTRL_CONTINUE, to_src_loc(&yylloc)); }
#line 3445 "gen/gen_parser.c"
    break;

  case 116: /* statelet: import  */
#line 336 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3451 "gen/gen_parser.c"
    break;

  case 117: /* statelet: var  */
#line 337 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3457 "gen/gen_parser.c"
    break;

  case 118: /* statelet: goto  */
#line 338 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3463 "gen/gen_parser.c"
    break;

  case 119: /* statelet: id ":"  */
#line 339 "src/parser.y"
                 { (yyval.node) = gen_label((yyvsp[-1].node));  }
#line 3469 "gen/gen_parser.c"
    break;

  case 120: /* statelet: for  */
#line 340 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3475 "gen/gen_parser.c"
    break;

  case 121: /* statelet: const  */
#line 341 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3481 "gen/gen_parser.c"
    break;

  case 122: /* statelet: while  */
#line 342 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3487 "gen/gen_parser.c"
    break;

  case 123: /* statelet: do_while  */
#line 343 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3493 "gen/gen_parser.c"
    break;

  case 124: /* statelet: macro  */
#line 344 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3499 "gen/gen_parser.c"
    break;

  case 125: /* statelet: struct  */
#line 345 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3505 "gen/gen_parser.c"
    break;

  case 126: /* statelet: alias  */
#line 346 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3511 "gen/gen_parser.c"
    break;

  case 127: /* statelet: template  */
#line 347 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3517 "gen/gen_parser.c"
    break;

  case 128: /* statelet: defer  */
#line 348 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3523 "gen/gen_parser.c"
    break;

  case 129: /* statelet: enum  */
#line 349 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3529 "gen/gen_parser.c"
    break;

  case 130: /* statelet: body  */
#line 350 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3535 "gen/gen_parser.c"
    break;

  case 131: /* statelet: ";"  */
#line 351 "src/parser.y"
              { (yyval.node) = gen_empty();  }
#line 3541 "gen/gen_parser.c"
    break;

  case 132: /* statelet: error  */
#line 352 "src/parser.y"
                {
	    /* TODO: figure out how to destroy any and all possible ast nodes we
	     * may have generated up until the error */
	    (yyval.node) = gen_empty();
	    parser->failed = true;
	    /* If we're failing to parse a statement in a block, continue by trying to
	     * parse the next statement in the block */
	    if (next_interesting_feature(&yylval, &yylloc, scanner, parser)) {
		destroy_ast_node((yyval.node));
		YYABORT;
	    }
	    yyclearin;
	    yyerrok;
	    }
#line 3560 "gen/gen_parser.c"
    break;

  case 133: /* statement: statelet ";"  */
#line 368 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3566 "gen/gen_parser.c"
    break;

  case 134: /* statements: statement statements  */
#line 371 "src/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3572 "gen/gen_parser.c"
    break;

  case 135: /* statements: statement  */
#line 372 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3578 "gen/gen_parser.c"
    break;

  case 136: /* statements: statelet  */
#line 373 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3584 "gen/gen_parser.c"
    break;

  case 137: /* body: "{" statements "}"  */
#line 376 "src/parser.y"
                             { (yyval.node) = gen_block((yyvsp[-1].node));  }
#line 3590 "gen/gen_parser.c"
    break;

  case 138: /* body: "{" "}"  */
#line 377 "src/parser.y"
                  { (yyval.node) = gen_block(gen_empty());  }
#line 3596 "gen/gen_parser.c"
    break;

  case 139: /* references: id "," references  */
#line 380 "src/parser.y"
                            { (yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 3602 "gen/gen_parser.c"
    break;

  case 140: /* references: id  */
#line 381 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3608 "gen/gen_parser.c"
    break;

  case 141: /* macro: "define" id "(" references ")" body  */
#line 385 "src/parser.y"
                                              {
		(yyval.node) = gen_macro((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3617 "gen/gen_parser.c"
    break;

  case 142: /* macro: "define" id "(" references "..." id ")" body  */
#line 389 "src/parser.y"
                                                       {
		/* TODO: the location data of the variadic ID is way off */
		ast_append((yyvsp[-4].node), (yyvsp[-2].node));
		(yyval.node) = gen_macro((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3629 "gen/gen_parser.c"
    break;

  case 143: /* macro: "define" id "(" ")" body  */
#line 396 "src/parser.y"
                                   {
		(yyval.node) = gen_macro((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3638 "gen/gen_parser.c"
    break;

  case 144: /* exprs: expr "," exprs  */
#line 402 "src/parser.y"
                         { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3644 "gen/gen_parser.c"
    break;

  case 145: /* exprs: expr  */
#line 403 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3650 "gen/gen_parser.c"
    break;

  case 146: /* construct_arg: expr  */
#line 406 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3656 "gen/gen_parser.c"
    break;

  case 147: /* construct_arg: "." id "=" expr  */
#line 407 "src/parser.y"
                          {
		(yyval.node) = gen_var((yyvsp[-2].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_MEMBER);
	}
#line 3665 "gen/gen_parser.c"
    break;

  case 148: /* construct_args: construct_arg "," construct_args  */
#line 413 "src/parser.y"
                                           { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3671 "gen/gen_parser.c"
    break;

  case 149: /* construct_args: construct_arg  */
#line 414 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3677 "gen/gen_parser.c"
    break;

  case 150: /* construct: "!" "{" construct_args "}"  */
#line 417 "src/parser.y"
                                     { (yyval.node) = gen_init((yyvsp[-1].node)); }
#line 3683 "gen/gen_parser.c"
    break;

  case 151: /* if: "if" expr body  */
#line 420 "src/parser.y"
                         { (yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3689 "gen/gen_parser.c"
    break;

  case 152: /* if: "if" expr body "else" body  */
#line 421 "src/parser.y"
                                     { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3695 "gen/gen_parser.c"
    break;

  case 153: /* if: "if" expr body "else" if  */
#line 422 "src/parser.y"
                                   { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3701 "gen/gen_parser.c"
    break;

  case 154: /* for: "for" arg ";" expr ";" expr body  */
#line 426 "src/parser.y"
                                           { (yyval.node) = gen_for((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3707 "gen/gen_parser.c"
    break;

  case 155: /* case: "case" const_expr ":" statements  */
#line 429 "src/parser.y"
                                           {
		(yyval.node) = gen_case((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3714 "gen/gen_parser.c"
    break;

  case 156: /* case: "default" ":" statements  */
#line 431 "src/parser.y"
                                   {
		(yyval.node) = gen_case(NULL, (yyvsp[0].node));
	}
#line 3722 "gen/gen_parser.c"
    break;

  case 157: /* cases: case cases  */
#line 436 "src/parser.y"
                     { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3728 "gen/gen_parser.c"
    break;

  case 158: /* cases: case  */
#line 437 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3734 "gen/gen_parser.c"
    break;

  case 159: /* switch: "switch" expr "{" cases "}"  */
#line 440 "src/parser.y"
                                      { (yyval.node) = gen_switch((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3740 "gen/gen_parser.c"
    break;

  case 160: /* const_for: "for" id ":" exprs body  */
#line 444 "src/parser.y"
                                  {
		/* TODO: should id be a separate rule? */
		(yyval.node) = gen_for((yyvsp[-3].node), NULL, (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3750 "gen/gen_parser.c"
    break;

  case 161: /* const_if: "if" const_expr body  */
#line 451 "src/parser.y"
                               {
		(yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3759 "gen/gen_parser.c"
    break;

  case 162: /* const_if: "if" const_expr body "else" body  */
#line 455 "src/parser.y"
                                           {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3769 "gen/gen_parser.c"
    break;

  case 163: /* const_if: "if" const_expr body "else" const_if  */
#line 460 "src/parser.y"
                                               {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
	}
#line 3778 "gen/gen_parser.c"
    break;

  case 164: /* const: "const" const_if  */
#line 468 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 3784 "gen/gen_parser.c"
    break;

  case 165: /* const: "const" const_for  */
#line 469 "src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 3790 "gen/gen_parser.c"
    break;

  case 166: /* simple_sign: "(" decls "=>" type ")"  */
#line 472 "src/parser.y"
                                  {
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 3798 "gen/gen_parser.c"
    break;

  case 167: /* simple_sign: "(" decls ")"  */
#line 475 "src/parser.y"
                        { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-1].node), NULL); }
#line 3804 "gen/gen_parser.c"
    break;

  case 168: /* simple_sign: "(" decls "=>" ")"  */
#line 476 "src/parser.y"
                             { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-2].node), NULL); }
#line 3810 "gen/gen_parser.c"
    break;

  case 169: /* simple_sign: "(" "=>" type ")"  */
#line 477 "src/parser.y"
                            { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, (yyvsp[-1].node)); }
#line 3816 "gen/gen_parser.c"
    break;

  case 170: /* simple_sign: "(" ")"  */
#line 478 "src/parser.y"
                  { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, NULL); }
#line 3822 "gen/gen_parser.c"
    break;

  case 171: /* func_sign: simple_sign  */
#line 481 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3828 "gen/gen_parser.c"
    break;

  case 172: /* func_sign: "(" decls "..." id "=>" type ")"  */
#line 482 "src/parser.y"
                                           {
		ast_append((yyvsp[-5].node), (yyvsp[-3].node));
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
	}
#line 3838 "gen/gen_parser.c"
    break;

  case 173: /* type: id  */
#line 489 "src/parser.y"
             { (yyval.node) = gen_type(AST_TYPE_ID, (yyvsp[0].node), NULL, NULL); }
#line 3844 "gen/gen_parser.c"
    break;

  case 174: /* type: "@" simple_sign  */
#line 490 "src/parser.y"
                          {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3853 "gen/gen_parser.c"
    break;

  case 175: /* type: apply "[" types "]"  */
#line 494 "src/parser.y"
                              {
		(yyval.node) = gen_type(AST_TYPE_GENERIC, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
	}
#line 3861 "gen/gen_parser.c"
    break;

  case 176: /* type: "'" type  */
#line 497 "src/parser.y"
                   {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3870 "gen/gen_parser.c"
    break;

  case 177: /* type: "'" "[" const_expr "]" type  */
#line 501 "src/parser.y"
                                      {
		(yyval.node) = gen_type(AST_TYPE_ARR, NULL, (yyvsp[-2].node), NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3879 "gen/gen_parser.c"
    break;

  case 178: /* type: "typeof" expr  */
#line 505 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_TYPEOF, NULL, (yyvsp[0].node), NULL);
	}
#line 3887 "gen/gen_parser.c"
    break;

  case 179: /* type: id "::" type  */
#line 508 "src/parser.y"
                       {
		(yyval.node) = gen_type(AST_TYPE_MEMBER, (yyvsp[-2].node), (yyvsp[0].node), NULL);
	}
#line 3895 "gen/gen_parser.c"
    break;

  case 180: /* var_decl: id "mut" type  */
#line 513 "src/parser.y"
                        {
		(yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_MUTABLE);
	}
#line 3904 "gen/gen_parser.c"
    break;

  case 181: /* var_decl: id "const" type  */
#line 517 "src/parser.y"
                          { (yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);  }
#line 3910 "gen/gen_parser.c"
    break;

  case 182: /* var_decl: id type  */
#line 518 "src/parser.y"
                  { (yyval.node) = gen_var((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3916 "gen/gen_parser.c"
    break;

  case 183: /* var_init: var_decl "=" expr  */
#line 521 "src/parser.y"
                            { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->_var.init = (yyvsp[0].node); }
#line 3922 "gen/gen_parser.c"
    break;

  case 184: /* var_init: id "mut" "=" expr  */
#line 522 "src/parser.y"
                            {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED | AST_FLAG_MUTABLE);
	}
#line 3931 "gen/gen_parser.c"
    break;

  case 185: /* var_init: id "const" "=" expr  */
#line 526 "src/parser.y"
                              {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 3940 "gen/gen_parser.c"
    break;

  case 186: /* proc: id func_sign body  */
#line 532 "src/parser.y"
                            {
		(yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), (yyvsp[-1].node)->flags);
	}
#line 3949 "gen/gen_parser.c"
    break;

  case 187: /* proc: "extern" id simple_sign  */
#line 536 "src/parser.y"
                                  {
		(yyval.node) = gen_proc((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_EXTERN);
	}
#line 3958 "gen/gen_parser.c"
    break;

  case 188: /* lambda: "[" references "]" simple_sign body  */
#line 542 "src/parser.y"
                                              { (yyval.node) = gen_lambda((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3964 "gen/gen_parser.c"
    break;

  case 189: /* lambda: "[" references "]" body  */
#line 543 "src/parser.y"
                                  { (yyval.node) = gen_lambda((yyvsp[-2].node), NULL, (yyvsp[0].node)); }
#line 3970 "gen/gen_parser.c"
    break;

  case 190: /* struct_elem: var_decl  */
#line 546 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3976 "gen/gen_parser.c"
    break;

  case 191: /* members: struct_elem ";" members  */
#line 549 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3982 "gen/gen_parser.c"
    break;

  case 192: /* members: struct_elem ";"  */
#line 550 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 3988 "gen/gen_parser.c"
    break;

  case 193: /* union: "union" id "{" members "}"  */
#line 553 "src/parser.y"
                                     {
		(yyval.node) = gen_union((yyvsp[-3].node), NULL, (yyvsp[-1].node));
	}
#line 3996 "gen/gen_parser.c"
    break;

  case 194: /* union: "union" id "(" generics ")" "{" members "}"  */
#line 556 "src/parser.y"
                                                      {
		(yyval.node) = gen_union((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
	}
#line 4004 "gen/gen_parser.c"
    break;

  case 195: /* generic: id type  */
#line 561 "src/parser.y"
                  { (yyval.node) = gen_alias((yyvsp[-1].node), (yyvsp[0].node)); }
#line 4010 "gen/gen_parser.c"
    break;

  case 196: /* generics: generic "," generics  */
#line 564 "src/parser.y"
                               { (yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 4016 "gen/gen_parser.c"
    break;

  case 197: /* generics: generic  */
#line 565 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 4022 "gen/gen_parser.c"
    break;

  case 198: /* struct: "struct" id "{" members "}"  */
#line 568 "src/parser.y"
                                      {
		(yyval.node) = gen_struct((yyvsp[-3].node), NULL, (yyvsp[-1].node));
	}
#line 4030 "gen/gen_parser.c"
    break;

  case 199: /* struct: "struct" id "(" generics ")" "{" members "}"  */
#line 571 "src/parser.y"
                                                       {
		(yyval.node) = gen_struct((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
	}
#line 4038 "gen/gen_parser.c"
    break;

  case 200: /* template_elem: id ";"  */
#line 578 "src/parser.y"
                 { (yyval.node) = (yyvsp[-1].node); }
#line 4044 "gen/gen_parser.c"
    break;

  case 201: /* template_elem: id simple_sign ";"  */
#line 579 "src/parser.y"
                             { (yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), NULL);  }
#line 4050 "gen/gen_parser.c"
    break;

  case 202: /* template_elem: var_decl ";"  */
#line 580 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 4056 "gen/gen_parser.c"
    break;

  case 203: /* template_elem: union  */
#line 581 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 4062 "gen/gen_parser.c"
    break;

  case 204: /* template_elems: template_elem template_elems  */
#line 584 "src/parser.y"
                                       { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 4068 "gen/gen_parser.c"
    break;

  case 205: /* template_elems: template_elem  */
#line 585 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 4074 "gen/gen_parser.c"
    break;

  case 206: /* types: type "," types  */
#line 588 "src/parser.y"
                         { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 4080 "gen/gen_parser.c"
    break;

  case 207: /* types: type  */
#line 589 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 4086 "gen/gen_parser.c"
    break;

  case 208: /* alias: "typedef" id type  */
#line 592 "src/parser.y"
                            { (yyval.node) = gen_alias((yyvsp[-1].node), (yyvsp[0].node));  }
#line 4092 "gen/gen_parser.c"
    break;

  case 209: /* template: "typedef" id "{" template_elems "}"  */
#line 597 "src/parser.y"
                                              {
		(yyval.node) = gen_template((yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 4100 "gen/gen_parser.c"
    break;

  case 210: /* template: "typedef" id "{" "}"  */
#line 600 "src/parser.y"
                               {
		/* should match anything, but doesn't implement anything */
		(yyval.node) = gen_template((yyvsp[-2].node), NULL);
	}
#line 4109 "gen/gen_parser.c"
    break;

  case 211: /* enum_val: id  */
#line 606 "src/parser.y"
             { (yyval.node) = gen_val((yyvsp[0].node), NULL);  }
#line 4115 "gen/gen_parser.c"
    break;

  case 212: /* enum_val: id "=" expr  */
#line 607 "src/parser.y"
                      { (yyval.node) = gen_val((yyvsp[-2].node), (yyvsp[0].node));  }
#line 4121 "gen/gen_parser.c"
    break;

  case 213: /* enums: enum_val "," enums  */
#line 610 "src/parser.y"
                             { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 4127 "gen/gen_parser.c"
    break;

  case 214: /* enums: enum_val ","  */
#line 611 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 4133 "gen/gen_parser.c"
    break;

  case 215: /* enums: enum_val  */
#line 612 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 4139 "gen/gen_parser.c"
    break;

  case 216: /* enum: "enum" id ":" type "{" enums "}"  */
#line 615 "src/parser.y"
                                           { (yyval.node) = gen_enum((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 4145 "gen/gen_parser.c"
    break;

  case 217: /* enum: "enum" id "{" enums "}"  */
#line 616 "src/parser.y"
                                  {
		(yyval.node) = gen_enum((yyvsp[-3].node), NULL, (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 4154 "gen/gen_parser.c"
    break;

  case 218: /* top_if: "if" const_expr "{" unit "}"  */
#line 622 "src/parser.y"
                                       {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-1].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 4163 "gen/gen_parser.c"
    break;

  case 219: /* top_if: "if" const_expr "{" unit "}" "else" "{" unit "}"  */
#line 626 "src/parser.y"
                                                           {
		(yyval.node) = gen_if((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 4172 "gen/gen_parser.c"
    break;

  case 220: /* top_if: "if" const_expr "{" unit "}" "else" top_if  */
#line 630 "src/parser.y"
                                                     {
		(yyval.node) = gen_if((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 4181 "gen/gen_parser.c"
    break;

  case 221: /* top_var_decl: id "mut" type  */
#line 636 "src/parser.y"
                        {
		(yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_MUTABLE);
	}
#line 4190 "gen/gen_parser.c"
    break;

  case 222: /* top_var_decl: id "const" type  */
#line 640 "src/parser.y"
                          { (yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 4196 "gen/gen_parser.c"
    break;

  case 223: /* top_var_decl: id type  */
#line 641 "src/parser.y"
                  { (yyval.node) = gen_var((yyvsp[-1].node), (yyvsp[0].node), NULL); }
#line 4202 "gen/gen_parser.c"
    break;

  case 224: /* top_var_init: top_var_decl "=" const_expr  */
#line 644 "src/parser.y"
                                      { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->_var.init = (yyvsp[0].node); }
#line 4208 "gen/gen_parser.c"
    break;

  case 225: /* top_var_init: id "mut" "=" const_expr  */
#line 645 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-3].node); (yyvsp[-3].node)->_var.init = (yyvsp[0].node); }
#line 4214 "gen/gen_parser.c"
    break;

  case 226: /* top_var_init: id "const" "=" const_expr  */
#line 646 "src/parser.y"
                                    { (yyval.node) = (yyvsp[-3].node); (yyvsp[-3].node)->_var.init = (yyvsp[0].node); }
#line 4220 "gen/gen_parser.c"
    break;

  case 227: /* top_var: top_var_decl  */
#line 649 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 4226 "gen/gen_parser.c"
    break;

  case 228: /* top_var: top_var_init  */
#line 650 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 4232 "gen/gen_parser.c"
    break;

  case 229: /* top: enum  */
#line 655 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 4238 "gen/gen_parser.c"
    break;

  case 230: /* top: proc  */
#line 656 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 4244 "gen/gen_parser.c"
    break;

  case 231: /* top: struct  */
#line 657 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 4250 "gen/gen_parser.c"
    break;

  case 232: /* top: union  */
#line 658 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 4256 "gen/gen_parser.c"
    break;

  case 233: /* top: macro  */
#line 659 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 4262 "gen/gen_parser.c"
    break;

  case 234: /* top: top_if  */
#line 660 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 4268 "gen/gen_parser.c"
    break;

  case 235: /* top: top_var  */
#line 661 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 4274 "gen/gen_parser.c"
    break;

  case 236: /* top: import  */
#line 662 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 4280 "gen/gen_parser.c"
    break;

  case 237: /* top: alias  */
#line 663 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 4286 "gen/gen_parser.c"
    break;

  case 238: /* top: template  */
#line 664 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 4292 "gen/gen_parser.c"
    break;

  case 239: /* top: "pub" enum  */
#line 665 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4298 "gen/gen_parser.c"
    break;

  case 240: /* top: "pub" struct  */
#line 666 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4304 "gen/gen_parser.c"
    break;

  case 241: /* top: "pub" union  */
#line 667 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4310 "gen/gen_parser.c"
    break;

  case 242: /* top: "pub" proc  */
#line 668 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4316 "gen/gen_parser.c"
    break;

  case 243: /* top: "pub" macro  */
#line 669 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4322 "gen/gen_parser.c"
    break;

  case 244: /* top: "pub" import  */
#line 670 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4328 "gen/gen_parser.c"
    break;

  case 245: /* top: "pub" alias  */
#line 671 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4334 "gen/gen_parser.c"
    break;

  case 246: /* top: "pub" template  */
#line 672 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4340 "gen/gen_parser.c"
    break;

  case 247: /* top: "pub" top_var  */
#line 673 "src/parser.y"
                        {
		(yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC);
		ast_set_flags((yyval.node), AST_FLAG_CONST);
	}
#line 4349 "gen/gen_parser.c"
    break;

  case 248: /* top: ";"  */
#line 677 "src/parser.y"
              { (yyval.node) = gen_empty(); }
#line 4355 "gen/gen_parser.c"
    break;

  case 249: /* top: error  */
#line 678 "src/parser.y"
                {
	    (yyval.node) = gen_empty();
	    parser->failed = true;
	    /* ignore any content inside a top level thing and just move onto
	     * the next one */
	    if (next_interesting_feature(&yylval, &yylloc, scanner, parser)) {
		/* remove previously allocated node if we're out of input */
		destroy_ast_node((yyval.node));
		YYABORT;
	    }
	    yyclearin;
	    yyerrok;
	}
#line 4373 "gen/gen_parser.c"
    break;

  case 250: /* unit: top  */
#line 693 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 4379 "gen/gen_parser.c"
    break;

  case 251: /* unit: top unit  */
#line 694 "src/parser.y"
                   { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 4385 "gen/gen_parser.c"
    break;

  case 252: /* input: unit  */
#line 697 "src/parser.y"
               { parser->tree = (yyvsp[0].node); }
#line 4391 "gen/gen_parser.c"
    break;


#line 4395 "gen/gen_parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, scanner, parser, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, scanner, parser);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, parser, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, parser);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner, parser);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 700 "src/parser.y"

