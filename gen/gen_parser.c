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
#line 1 "src/parser.y"


/* TODO: clean up this mess and I guess fix location tracking, it works for the
 * parser but each ast node should also get some location data
 * I'm trying something over in ast.c, but I'm not sure about it
 */

#include <stdio.h>
#include <stdlib.h>
#include <cu/parser.h>
#include <cu/ast.h>


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
  YYSYMBOL_SQUOTE = 7,                     /* "'"  */
  YYSYMBOL_TO = 8,                         /* "="  */
  YYSYMBOL_ELLIPSIS = 9,                   /* "..."  */
  YYSYMBOL_SEMICOLON = 10,                 /* ";"  */
  YYSYMBOL_COLON = 11,                     /* ":"  */
  YYSYMBOL_BANG = 12,                      /* "!"  */
  YYSYMBOL_TYPEOF = 13,                    /* "typeof"  */
  YYSYMBOL_SIZEOF = 14,                    /* "sizeof"  */
  YYSYMBOL_PASTE = 15,                     /* "##"  */
  YYSYMBOL_STAR = 16,                      /* "*"  */
  YYSYMBOL_DIV = 17,                       /* "/"  */
  YYSYMBOL_REM = 18,                       /* "%"  */
  YYSYMBOL_MINUS = 19,                     /* "-"  */
  YYSYMBOL_PLUS = 20,                      /* "+"  */
  YYSYMBOL_POW = 21,                       /* "^^"  */
  YYSYMBOL_XOR = 22,                       /* "^"  */
  YYSYMBOL_AND = 23,                       /* "&"  */
  YYSYMBOL_OR = 24,                        /* "|"  */
  YYSYMBOL_LAND = 25,                      /* "&&"  */
  YYSYMBOL_LOR = 26,                       /* "||"  */
  YYSYMBOL_TILDE = 27,                     /* "~"  */
  YYSYMBOL_LT = 28,                        /* "<"  */
  YYSYMBOL_GT = 29,                        /* ">"  */
  YYSYMBOL_LE = 30,                        /* "<="  */
  YYSYMBOL_GE = 31,                        /* ">="  */
  YYSYMBOL_NE = 32,                        /* "!="  */
  YYSYMBOL_EQ = 33,                        /* "=="  */
  YYSYMBOL_LSHIFT = 34,                    /* "<<"  */
  YYSYMBOL_RSHIFT = 35,                    /* ">>"  */
  YYSYMBOL_PLUSSELF = 36,                  /* "+="  */
  YYSYMBOL_MINUSSELF = 37,                 /* "-="  */
  YYSYMBOL_STARSELF = 38,                  /* "*="  */
  YYSYMBOL_DIVSELF = 39,                   /* "/="  */
  YYSYMBOL_REMSELF = 40,                   /* "%="  */
  YYSYMBOL_XORSELF = 41,                   /* "^="  */
  YYSYMBOL_POWSELF = 42,                   /* "^^="  */
  YYSYMBOL_ANDSELF = 43,                   /* "&="  */
  YYSYMBOL_ORSELF = 44,                    /* "|="  */
  YYSYMBOL_LSHIFTSELF = 45,                /* "<<="  */
  YYSYMBOL_RSHIFTSELF = 46,                /* ">>="  */
  YYSYMBOL_AT = 47,                        /* "@"  */
  YYSYMBOL_COMMA = 48,                     /* ","  */
  YYSYMBOL_PUB = 49,                       /* "pub"  */
  YYSYMBOL_STRUCT = 50,                    /* "struct"  */
  YYSYMBOL_UNION = 51,                     /* "union"  */
  YYSYMBOL_TYPEDEF = 52,                   /* "typedef"  */
  YYSYMBOL_IMPORT = 53,                    /* "import"  */
  YYSYMBOL_DEFER = 54,                     /* "defer"  */
  YYSYMBOL_GOTO = 55,                      /* "goto"  */
  YYSYMBOL_EMBED = 56,                     /* "embed"  */
  YYSYMBOL_IF = 57,                        /* "if"  */
  YYSYMBOL_ELSE = 58,                      /* "else"  */
  YYSYMBOL_BREAK = 59,                     /* "break"  */
  YYSYMBOL_CONTINUE = 60,                  /* "continue"  */
  YYSYMBOL_SWITCH = 61,                    /* "switch"  */
  YYSYMBOL_CASE = 62,                      /* "case"  */
  YYSYMBOL_FOR = 63,                       /* "for"  */
  YYSYMBOL_WHILE = 64,                     /* "while"  */
  YYSYMBOL_DO = 65,                        /* "do"  */
  YYSYMBOL_MUT = 66,                       /* "mut"  */
  YYSYMBOL_RETURN = 67,                    /* "return"  */
  YYSYMBOL_CONST = 68,                     /* "const"  */
  YYSYMBOL_EXTERN = 69,                    /* "extern"  */
  YYSYMBOL_ENUM = 70,                      /* "enum"  */
  YYSYMBOL_DEFINE = 71,                    /* "define"  */
  YYSYMBOL_LPAREN = 72,                    /* "("  */
  YYSYMBOL_RPAREN = 73,                    /* ")"  */
  YYSYMBOL_LBRACE = 74,                    /* "{"  */
  YYSYMBOL_RBRACE = 75,                    /* "}"  */
  YYSYMBOL_LBRACKET = 76,                  /* "["  */
  YYSYMBOL_RBRACKET = 77,                  /* "]"  */
  YYSYMBOL_AS = 78,                        /* "as"  */
  YYSYMBOL_DOT = 79,                       /* "."  */
  YYSYMBOL_SCOPE = 80,                     /* "::"  */
  YYSYMBOL_FATARROW = 81,                  /* "=>"  */
  YYSYMBOL_YYACCEPT = 82,                  /* $accept  */
  YYSYMBOL_id = 83,                        /* id  */
  YYSYMBOL_var = 84,                       /* var  */
  YYSYMBOL_embed = 85,                     /* embed  */
  YYSYMBOL_import = 86,                    /* import  */
  YYSYMBOL_assign = 87,                    /* assign  */
  YYSYMBOL_binary_op = 88,                 /* binary_op  */
  YYSYMBOL_unary_op = 89,                  /* unary_op  */
  YYSYMBOL_arg = 90,                       /* arg  */
  YYSYMBOL_arg_list = 91,                  /* arg_list  */
  YYSYMBOL_param_decl = 92,                /* param_decl  */
  YYSYMBOL_decl_list = 93,                 /* decl_list  */
  YYSYMBOL_call = 94,                      /* call  */
  YYSYMBOL_defer = 95,                     /* defer  */
  YYSYMBOL_expr = 96,                      /* expr  */
  YYSYMBOL_while = 97,                     /* while  */
  YYSYMBOL_do_while = 98,                  /* do_while  */
  YYSYMBOL_goto = 99,                      /* goto  */
  YYSYMBOL_statement = 100,                /* statement  */
  YYSYMBOL_statement_list = 101,           /* statement_list  */
  YYSYMBOL_body = 102,                     /* body  */
  YYSYMBOL_macro_list = 103,               /* macro_list  */
  YYSYMBOL_macro = 104,                    /* macro  */
  YYSYMBOL_expr_list = 105,                /* expr_list  */
  YYSYMBOL_struct_init = 106,              /* struct_init  */
  YYSYMBOL_struct_inits = 107,             /* struct_inits  */
  YYSYMBOL_struct_construct = 108,         /* struct_construct  */
  YYSYMBOL_init_expr = 109,                /* init_expr  */
  YYSYMBOL_cond = 110,                     /* cond  */
  YYSYMBOL_expr_if = 111,                  /* expr_if  */
  YYSYMBOL_if = 112,                       /* if  */
  YYSYMBOL_for = 113,                      /* for  */
  YYSYMBOL_case = 114,                     /* case  */
  YYSYMBOL_case_list = 115,                /* case_list  */
  YYSYMBOL_switch = 116,                   /* switch  */
  YYSYMBOL_const_for = 117,                /* const_for  */
  YYSYMBOL_const_if = 118,                 /* const_if  */
  YYSYMBOL_const = 119,                    /* const  */
  YYSYMBOL_func_sign = 120,                /* func_sign  */
  YYSYMBOL_variadic_sign = 121,            /* variadic_sign  */
  YYSYMBOL_type = 122,                     /* type  */
  YYSYMBOL_var_decl = 123,                 /* var_decl  */
  YYSYMBOL_var_init = 124,                 /* var_init  */
  YYSYMBOL_proc = 125,                     /* proc  */
  YYSYMBOL_lambda = 126,                   /* lambda  */
  YYSYMBOL_struct_elem = 127,              /* struct_elem  */
  YYSYMBOL_struct_list = 128,              /* struct_list  */
  YYSYMBOL_union = 129,                    /* union  */
  YYSYMBOL_generic = 130,                  /* generic  */
  YYSYMBOL_generic_list = 131,             /* generic_list  */
  YYSYMBOL_struct = 132,                   /* struct  */
  YYSYMBOL_template_elem = 133,            /* template_elem  */
  YYSYMBOL_template_list = 134,            /* template_list  */
  YYSYMBOL_type_list = 135,                /* type_list  */
  YYSYMBOL_type_alias = 136,               /* type_alias  */
  YYSYMBOL_type_template = 137,            /* type_template  */
  YYSYMBOL_enum_val = 138,                 /* enum_val  */
  YYSYMBOL_enum_list = 139,                /* enum_list  */
  YYSYMBOL_enum = 140,                     /* enum  */
  YYSYMBOL_top_if = 141,                   /* top_if  */
  YYSYMBOL_top = 142,                      /* top  */
  YYSYMBOL_unit = 143,                     /* unit  */
  YYSYMBOL_input = 144                     /* input  */
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
#define YYFINAL  61
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2064

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  219
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  438

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   336


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
      75,    76,    77,    78,    79,    80,    81
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   151,   151,   157,   158,   161,   164,   167,   168,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   195,   198,   199,   200,   201,   202,   203,   206,   207,
     208,   209,   210,   213,   214,   215,   218,   219,   222,   224,
     225,   226,   227,   231,   232,   235,   239,   240,   241,   242,
     243,   244,   245,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   264,   267,   273,   275,
     276,   277,   278,   279,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   314,   315,   318,   319,   322,   323,   326,   330,
     337,   343,   344,   347,   348,   354,   355,   358,   361,   362,
     363,   364,   367,   368,   372,   373,   376,   377,   378,   381,
     384,   387,   388,   391,   394,   401,   405,   410,   418,   420,
     424,   427,   429,   431,   433,   437,   438,   445,   446,   450,
     453,   457,   461,   465,   468,   473,   477,   478,   481,   482,
     486,   492,   496,   502,   505,   508,   509,   512,   515,   520,
     521,   522,   525,   528,   535,   536,   537,   538,   541,   542,
     545,   546,   549,   554,   557,   563,   564,   567,   568,   569,
     572,   573,   579,   583,   587,   595,   596,   597,   598,   599,
     600,   601,   602,   603,   604,   605,   606,   607,   608,   609,
     610,   611,   612,   613,   614,   615,   630,   631,   634,   635
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
  "STRING", "ID", "\"'\"", "\"=\"", "\"...\"", "\";\"", "\":\"", "\"!\"",
  "\"typeof\"", "\"sizeof\"", "\"##\"", "\"*\"", "\"/\"", "\"%\"", "\"-\"",
  "\"+\"", "\"^^\"", "\"^\"", "\"&\"", "\"|\"", "\"&&\"", "\"||\"",
  "\"~\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\"!=\"", "\"==\"",
  "\"<<\"", "\">>\"", "\"+=\"", "\"-=\"", "\"*=\"", "\"/=\"", "\"%=\"",
  "\"^=\"", "\"^^=\"", "\"&=\"", "\"|=\"", "\"<<=\"", "\">>=\"", "\"@\"",
  "\",\"", "\"pub\"", "\"struct\"", "\"union\"", "\"typedef\"",
  "\"import\"", "\"defer\"", "\"goto\"", "\"embed\"", "\"if\"", "\"else\"",
  "\"break\"", "\"continue\"", "\"switch\"", "\"case\"", "\"for\"",
  "\"while\"", "\"do\"", "\"mut\"", "\"return\"", "\"const\"",
  "\"extern\"", "\"enum\"", "\"define\"", "\"(\"", "\")\"", "\"{\"",
  "\"}\"", "\"[\"", "\"]\"", "\"as\"", "\".\"", "\"::\"", "\"=>\"",
  "$accept", "id", "var", "embed", "import", "assign", "binary_op",
  "unary_op", "arg", "arg_list", "param_decl", "decl_list", "call",
  "defer", "expr", "while", "do_while", "goto", "statement",
  "statement_list", "body", "macro_list", "macro", "expr_list",
  "struct_init", "struct_inits", "struct_construct", "init_expr", "cond",
  "expr_if", "if", "for", "case", "case_list", "switch", "const_for",
  "const_if", "const", "func_sign", "variadic_sign", "type", "var_decl",
  "var_init", "proc", "lambda", "struct_elem", "struct_list", "union",
  "generic", "generic_list", "struct", "template_elem", "template_list",
  "type_list", "type_alias", "type_template", "enum_val", "enum_list",
  "enum", "top_if", "top", "unit", "input", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-225)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-220)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     653,  -225,  -225,  -225,   429,    27,    27,    27,    42,     3,
      27,    27,    27,   246,    60,    64,  -225,   100,  -225,  -225,
    -225,  -225,    79,  -225,  -225,   214,  -225,   113,   124,   134,
    -225,  -225,  -225,  -225,   144,  -225,  -225,    99,   112,   149,
    -225,  1187,  -225,   107,    71,   126,    49,  1187,    46,    65,
      30,   524,   -38,  -225,   122,  -225,  -225,  -225,  1053,  -225,
    -225,  -225,  -225,  -225,  -225,    27,    27,    27,    27,    51,
    -225,  -225,  -225,  -225,  1187,    27,  1187,  1187,  1187,  1187,
    1187,  -225,   127,   130,  1187,    27,    38,    92,  -225,  -225,
    -225,  -225,  -225,  -225,  1280,  -225,    30,  -225,    38,    27,
      22,  -225,  -225,   137,  1053,  -225,  1053,  -225,  -225,    38,
      25,   165,    31,  -225,   173,    38,  1344,    38,    38,   823,
    -225,  1217,   604,  1985,   140,  -225,  -225,    38,   181,   157,
     194,  -225,   221,   159,   164,   182,  -225,   170,   233,  -225,
      29,   186,   137,  -225,   137,   137,   314,  1449,   137,  1187,
     263,    81,  1408,   100,   196,   224,   197,  -225,   975,    38,
    1131,  1187,  1187,  1187,  1187,  1187,  1187,  1187,  1187,  1187,
    1187,  1187,  1187,  1187,  1187,  1187,  1187,  1187,  1187,  1187,
    1187,  1187,  1187,  1187,  1187,  1187,  1187,  1187,  1187,  1187,
     334,    38,    27,    97,   202,   269,   230,   204,   122,    55,
    -225,  -225,   207,    38,    38,    38,    27,  -225,   168,    38,
    -225,    38,   239,   208,  -225,  -225,  -225,    27,  1217,   280,
     283,  1187,  1085,  1187,   122,  1007,   103,  -225,    70,   284,
     288,  1472,  -225,  -225,   289,   747,   226,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,   293,  -225,  -225,  1161,  1985,   122,
      27,   256,   231,  -225,    38,  -225,    27,   234,    27,  -225,
     235,  -225,  -225,   295,  -225,  -225,  -225,  1536,   237,  -225,
    -225,    27,   107,  1187,  -225,   220,   268,   238,  -225,  -225,
    -225,  1985,  -225,   110,   110,   110,   314,   314,   712,   556,
    1449,  1441,  1377,  1313,   913,   913,   913,   913,   837,   837,
     332,   332,  1985,  1985,  1985,  1985,  1985,  1985,  1985,  1985,
    1985,  1985,   244,  -225,  -225,    27,  1187,    27,  -225,  -225,
      27,   122,  -225,  -225,   240,  -225,   250,  -225,  -225,    38,
    -225,  -225,   122,  -225,  -225,  1600,   315,  1664,   260,  -225,
     316,  1187,    27,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,   254,   275,   328,   604,  -225,  -225,  -225,
      27,  -225,    27,  -225,  -225,  -225,  -225,   122,  -225,  1085,
    -225,   281,   266,  1985,  -225,   270,  -225,    38,  -225,  -225,
     296,   291,  1187,  -225,  1187,  -225,  1664,   335,  -225,   -16,
    1053,  -225,   282,   297,  -225,  -225,    33,  -225,   122,   272,
      74,  1187,   291,   298,  1729,  1793,   300,  1187,  -225,  -225,
    -225,  -225,  -225,   334,  -225,  -225,  -225,  -225,  -225,  1857,
    -225,  -225,  1187,  -225,    95,  1921,   122,   299,   899,  1664,
    -225,  -225,  1187,  -225,  -225,  -225,  -225,  -225
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   215,     2,   195,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   200,     3,     4,   197,
     199,   198,     0,   204,   196,     0,   218,     0,     0,     0,
     209,   208,   207,   206,     0,   212,   205,     0,     0,     0,
       6,     0,   201,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   147,   145,     0,   157,   213,   202,     0,   203,
     217,     1,   214,   210,   211,     0,     0,     0,     0,     0,
     182,    60,    61,    62,     0,     0,     0,     0,     0,     0,
       0,    59,     0,     0,     0,     0,     0,    56,    74,    64,
      67,    68,    65,    66,     0,    75,     0,   162,     0,     0,
       0,   148,   150,   153,     0,   155,     0,   156,   144,     0,
     147,    52,     0,    48,    51,     0,     0,     0,     0,     0,
     161,     0,     0,   118,   120,   158,   119,     0,   171,     0,
       0,   164,     0,     0,     0,     0,   184,     0,     0,   177,
     179,     0,    41,    58,    39,    70,    38,    40,    42,     0,
       0,    56,     0,     0,     0,   107,     0,    73,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   185,   189,     0,     0,     0,
     159,   160,     0,     0,     0,     0,     0,   141,     0,     0,
     151,     0,   181,     0,   154,   101,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,    56,     0,
       0,     0,    91,    92,     0,     0,     0,    99,    94,    86,
      89,    93,    90,    95,     0,    97,    98,     0,   122,     0,
       0,   116,     0,   113,     0,   169,     0,     0,   166,   172,
       0,   167,   174,     0,   176,   178,   183,     0,     0,    63,
      69,     0,     0,     0,    54,    56,    47,     0,    45,    44,
      72,     7,     8,    11,    12,    13,    10,     9,    15,    14,
      16,    18,    17,    19,    32,    33,    34,    35,    36,    37,
      20,    21,    22,    23,    24,    25,    26,    29,    27,    28,
      30,    31,     0,    71,    57,     0,     0,   188,   191,   110,
       0,     0,   143,    50,     0,   142,     0,    49,   152,     0,
     149,    78,     0,    82,    83,     0,     0,     0,     0,    81,
       0,     0,     0,   139,   138,    88,    85,    84,    79,    87,
     102,   104,    96,     0,     0,     0,     0,   117,   121,   170,
       0,   165,     0,   175,    55,     5,   106,     0,    43,     0,
      53,   192,     0,   186,   187,     0,   108,     0,   140,   180,
     126,     0,     0,    76,     0,    80,     0,     0,   123,     0,
       0,   115,     0,     0,   163,    46,     0,   190,     0,     0,
       0,     0,   132,     0,     0,     0,   135,     0,   124,   125,
     114,   173,   168,     0,   194,   109,   146,   127,   128,     0,
     131,   133,     0,    77,     0,   112,     0,     0,     0,     0,
     136,   137,     0,   134,   193,   130,   129,   111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,     0,    -3,  -225,     4,  -225,  -225,  -225,   133,     6,
    -225,   -66,  -225,  -225,   287,  -225,  -225,  -225,  -225,  -216,
     -30,   -84,     5,   -56,  -225,    24,   218,   -43,   161,  -224,
     -19,  -225,  -225,   -20,  -225,  -225,   -36,  -225,   -17,  -225,
     439,   427,   -62,   385,  -225,  -225,   -65,    23,  -225,   -46,
      10,  -225,   251,    66,    13,    14,  -225,  -120,    16,     1,
    -225,   -23,  -225
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    87,    14,    88,    15,    89,    90,    91,   276,   277,
     111,   112,    92,    93,   123,   232,   233,   234,   235,   236,
     237,   156,    16,   426,   251,   252,   124,   278,   249,   126,
     239,   240,   402,   403,   241,   343,   344,   242,    53,    54,
      55,    17,    18,    19,    95,   132,   133,    20,   128,   129,
      21,   140,   141,   213,    22,    23,   196,   197,    24,    42,
      25,    26,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    28,    60,   135,    13,    37,    38,    39,    29,    30,
      43,    44,    45,    52,    33,   125,   199,    34,    35,   350,
      36,   134,   154,   353,   120,    13,    97,    32,     2,   101,
     193,     2,    46,     2,   117,     2,     2,    46,    47,    52,
     206,   121,   118,    47,     2,    46,    52,    40,    52,    52,
     110,    47,     2,    46,   104,     2,    46,     2,   119,    47,
      41,   200,    47,   201,   320,   127,   130,   127,   130,   137,
      56,     2,    46,   106,    57,   143,     2,    46,    47,   253,
       6,   345,    98,    47,   151,   155,    52,     2,    46,    59,
      41,   203,   139,   204,    47,   198,   110,   117,    52,   195,
     155,    51,     6,   108,   207,   118,    51,   413,    58,    52,
      52,   109,   208,    61,    51,    52,   229,    52,    52,   228,
     263,    96,    51,   230,   238,    51,   136,    52,   321,   243,
      52,   218,   244,   245,    62,   246,    48,    52,    49,   323,
     137,    51,   158,   327,    63,    99,    51,    48,   119,    49,
     159,    52,   341,   158,    64,     2,    46,    51,   275,    52,
     341,   159,    47,   139,   158,   409,   342,   312,   319,   119,
     207,    65,   159,    66,     2,    46,     2,    46,   208,    96,
     262,    47,   340,    47,    67,   154,    68,   366,   191,   192,
      13,    52,   314,   361,   338,   372,   119,   374,   100,   149,
       2,    46,   150,    52,    52,   110,   324,    47,    52,   110,
     359,    52,   435,   205,  -216,     1,   192,   331,   254,   354,
       2,   209,   275,    69,     3,    51,     2,    46,    52,   256,
     257,   258,   229,    47,   259,   228,   203,   260,   204,   230,
     238,   325,    96,   264,    51,   243,    51,   151,   244,   245,
     355,   246,     2,    46,    52,   367,   127,   261,   130,    47,
     203,   266,   204,     4,     5,     6,     7,     8,   268,   270,
      51,   155,   271,   275,   272,    52,   315,   316,   317,   318,
     322,   330,     9,    10,    11,    12,   203,   329,   204,  -216,
     333,   376,   158,   334,   346,   392,    51,   393,   347,   349,
     159,   351,   380,   352,   356,   363,   357,   383,   360,   362,
     365,   370,    48,   253,    49,   195,   369,   195,    50,   371,
     375,   377,    51,   378,   384,   382,   385,   388,    94,    52,
     161,   162,   163,   389,   103,     1,   390,   394,   116,   396,
       2,   397,   387,   398,     3,   416,   407,   410,   161,   162,
     163,   164,   165,   401,   400,   336,   406,   411,   424,   408,
     130,   142,   130,   144,   145,   146,   147,   148,   415,   275,
     417,   152,   412,   421,   434,   395,   437,    52,   282,   332,
     391,   418,   420,     4,     5,     6,     7,     8,   431,    31,
     427,   265,   191,   192,   430,   379,   433,   414,     0,   436,
       0,     0,     9,    10,    11,    12,   231,     0,   248,     0,
     191,   192,     0,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   229,     0,     0,   228,     0,
       0,     0,   230,   238,     0,     2,   267,     0,   243,     0,
       0,   244,   245,     0,   246,     0,     0,   281,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   114,    70,     5,
       6,     7,     8,     0,     0,   102,     0,   105,   107,   113,
       0,     0,     0,   131,     0,   131,   138,     0,    10,    11,
      12,     0,     0,     0,     0,   248,     0,     0,   335,     0,
     337,   153,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   231,   114,     0,   157,     0,    71,    72,    73,
       2,    74,     0,    75,   152,   113,    76,   194,    77,     0,
       0,     0,     0,    78,     0,     0,     0,    79,   202,     0,
       0,    80,     0,     0,   210,     0,   212,   214,     0,     0,
     147,     0,     0,     0,     0,     0,   255,   138,     0,     0,
       0,    81,   161,   162,   163,   164,   165,     0,    82,   168,
      83,     0,     0,     0,     0,   279,     0,     0,     0,     0,
     178,   179,     0,     0,     0,     0,    84,     0,   280,     0,
      85,   115,    86,   373,     0,     0,     0,    71,    72,    73,
       2,    74,     0,    75,     0,     0,    76,     0,    77,     0,
       0,     0,     0,    78,     0,     0,     0,    79,   386,     0,
     313,    80,   114,     0,   191,   192,   114,     0,     0,     0,
       0,     0,   105,   107,   113,     0,     0,   326,   113,   279,
     328,    81,     0,  -219,     1,     0,     0,     0,    82,     2,
      83,   121,     0,     3,     0,     0,     0,     0,     0,   404,
       0,   405,     0,     0,   153,     0,    84,     0,   122,     0,
      85,     0,    86,   250,     0,   131,     0,     0,   419,     0,
       0,     0,     0,   358,   425,     0,     0,     0,     0,     0,
     368,     0,     4,     5,     6,     7,     8,     0,     0,   429,
       0,     0,     0,     0,     0,   231,     0,     0,     0,   425,
       0,     9,    10,    11,    12,     0,     0,     0,   161,   162,
     163,   164,   165,     0,   167,   168,   169,   170,   171,     0,
     172,   173,   174,   175,   176,   177,   178,   179,   215,     0,
      71,    72,    73,     2,    74,     0,    75,   216,     0,    76,
       0,    77,     0,     0,     0,     0,    78,     0,   212,     0,
      79,     0,     0,     0,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   131,     0,   131,
     191,   192,     0,     0,    81,     0,   279,     5,     0,     7,
       8,    82,   217,    83,   218,     0,   219,   220,   221,  -103,
     222,   223,   224,     0,   225,   226,   399,    11,    12,    84,
       0,   119,  -103,    85,   215,    86,    71,    72,    73,     2,
      74,     0,    75,   216,     0,    76,     0,    77,     0,     0,
       0,     0,    78,     0,     0,     0,    79,     0,     0,     0,
      80,     0,     0,   161,   162,   163,   164,   165,     0,   167,
     168,   169,     0,     0,     0,   172,   173,   174,   175,     0,
      81,   178,   179,     5,     0,     7,     8,    82,   217,    83,
     218,     0,   219,   220,   221,     0,   222,   223,   224,     0,
     225,   226,     0,    11,    12,    84,     0,   119,   227,    85,
     215,    86,    71,    72,    73,     2,    74,     0,    75,   216,
       0,    76,     0,    77,     0,   191,   192,     0,    78,     0,
       0,     0,    79,     0,     0,     0,    80,     0,     0,   161,
     162,   163,   164,   165,     0,   167,   168,   169,     0,     0,
       0,     0,     0,     0,     0,     0,    81,   178,   179,     5,
       0,     7,     8,    82,   217,    83,   218,     0,   219,   220,
     221,     0,   222,   223,   224,     0,   225,   226,     0,    11,
      12,    84,     0,   119,     0,    85,     0,    86,    71,    72,
      73,     2,    74,     0,    75,     0,     0,    76,     0,    77,
       0,   191,   192,     0,    78,     0,     0,     0,   273,     0,
       0,     0,    80,     0,     0,     0,     0,     0,     0,     0,
      71,    72,    73,     2,    74,     0,    75,   339,     0,    76,
       0,    77,    81,     0,     0,     0,    78,     0,     0,    82,
      79,    83,   121,     0,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    84,   274,   122,
       0,    85,     0,    86,    81,     0,    71,    72,    73,     2,
      74,    82,    75,    83,   121,    76,     0,    77,     0,     0,
       0,     0,    78,     0,     0,     0,    79,     0,     0,    84,
      80,   122,     0,    85,     0,    86,     0,     0,    71,    72,
      73,     2,    74,     0,    75,     0,     0,    76,     0,    77,
      81,     0,     0,     0,    78,     0,     0,    82,   273,    83,
     121,     0,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    84,     0,   122,     0,    85,
       0,    86,    81,     0,    71,    72,    73,     2,    74,    82,
      75,    83,   121,    76,     0,    77,     0,     0,     0,     0,
      78,     0,     0,     0,    79,     0,     0,    84,    80,   122,
       0,    85,     0,    86,    71,    72,    73,     2,    74,     0,
      75,     0,     0,    76,     0,    77,     0,     0,    81,     0,
      78,     0,     0,     0,    79,    82,     0,    83,    80,     0,
      71,    72,    73,     2,    74,     0,    75,     0,     0,    76,
       0,    77,     0,    84,     0,   122,    78,    85,    81,    86,
      79,     0,     0,     0,    80,    82,     0,    83,   121,     0,
      71,    72,    73,     2,    74,     0,    75,     0,     0,    76,
       0,    77,     0,    84,    81,     0,    78,    85,     0,    86,
      79,    82,     0,    83,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,    85,    81,    86,     0,     0,     0,     0,
       0,    82,     0,    83,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   160,   247,
       0,     0,     0,    85,     0,    86,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,     0,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,     0,   186,   187,   188,   189,     0,     0,   161,
     162,   163,   164,   165,     0,   167,   168,   169,   170,     0,
       0,   172,   173,   174,   175,   176,   177,   178,   179,     0,
       0,     0,   160,     0,   190,     0,     0,     0,   191,   192,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,     0,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,     0,   186,   187,   188,
     189,   191,   192,   161,   162,   163,   164,   165,     0,   167,
     168,   169,     0,     0,     0,   172,   173,   174,   175,   176,
     177,   178,   179,     0,     0,     0,   160,     0,     0,     0,
       0,   211,   191,   192,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,     0,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       0,   186,   187,   188,   189,   191,   192,   161,   162,   163,
     164,   165,     0,   167,   168,   161,   162,   163,   164,   165,
       0,     0,     0,     0,     0,   178,   179,     0,     0,     0,
     160,   269,   348,   178,   179,     0,   191,   192,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,     0,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,     0,   186,   187,   188,   189,   191,
     192,     0,     0,     0,     0,     0,     0,   191,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   160,     0,     0,     0,     0,     0,
     191,   192,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,     0,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,     0,   186,
     187,   188,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   160,   364,
       0,     0,     0,     0,   191,   192,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,     0,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,     0,   186,   187,   188,   189,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   160,     0,   381,     0,     0,     0,   191,   192,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,     0,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,     0,   186,   187,   188,
     189,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   160,   119,   422,
       0,     0,   191,   192,     0,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,     0,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,     0,   186,   187,   188,   189,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   160,     0,   423,     0,     0,     0,   191,   192,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
       0,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,     0,   186,   187,   188,   189,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   160,     0,     0,   428,     0,
       0,   191,   192,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,     0,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,     0,
     186,   187,   188,   189,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   160,
       0,     0,     0,     0,     0,   191,   192,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,     0,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,     0,   186,   187,   188,   189,     0,   432,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   160,     0,     0,     0,     0,     0,   191,
     192,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,     0,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,     0,   186,   187,
     188,   189,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   191,   192
};

static const yytype_int16 yycheck[] =
{
       0,     4,    25,    68,     4,     5,     6,     7,     4,     4,
      10,    11,    12,    13,     4,    58,   100,     4,     4,   235,
       4,    67,    84,   247,    54,    25,    43,     4,     6,    46,
      96,     6,     7,     6,    72,     6,     6,     7,    13,    39,
       9,    57,    80,    13,     6,     7,    46,     5,    48,    49,
      50,    13,     6,     7,     8,     6,     7,     6,    74,    13,
      57,   104,    13,   106,     9,    65,    66,    67,    68,    69,
      10,     6,     7,     8,    10,    75,     6,     7,    13,   122,
      51,    11,    11,    13,    84,    85,    86,     6,     7,    10,
      57,    66,    69,    68,    13,    73,    96,    72,    98,    99,
     100,    76,    51,    73,    73,    80,    76,    74,     8,   109,
     110,    81,    81,     0,    76,   115,   119,   117,   118,   119,
     137,    72,    76,   119,   119,    76,    75,   127,    73,   119,
     130,    57,   119,   119,    10,   119,    66,   137,    68,   205,
     140,    76,    72,   209,    10,    74,    76,    66,    74,    68,
      80,   151,    57,    72,    10,     6,     7,    76,   158,   159,
      57,    80,    13,   140,    72,   389,    63,   190,   198,    74,
      73,    72,    80,    74,     6,     7,     6,     7,    81,    72,
      10,    13,   225,    13,    72,   247,    74,   271,    78,    79,
     190,   191,   192,   258,   224,   315,    74,   317,    72,    72,
       6,     7,    72,   203,   204,   205,   206,    13,   208,   209,
     256,   211,   428,    48,     0,     1,    79,   217,    78,   249,
       6,    48,   222,    74,    10,    76,     6,     7,   228,    48,
      73,    10,   235,    13,    75,   235,    66,    73,    68,   235,
     235,    73,    72,    10,    76,   235,    76,   247,   235,   235,
     250,   235,     6,     7,   254,   272,   256,    75,   258,    13,
      66,    75,    68,    49,    50,    51,    52,    53,     5,    73,
      76,   271,    48,   273,    77,   275,    74,     8,    48,    75,
      73,    73,    68,    69,    70,    71,    66,    48,    68,    75,
      10,   321,    72,    10,    10,   360,    76,   362,    10,    10,
      80,    75,   332,    10,    48,    10,    75,   337,    74,    74,
      73,    73,    66,   356,    68,   315,    48,   317,    72,    75,
     320,    81,    76,    73,    64,    10,    10,    73,    41,   329,
      16,    17,    18,    58,    47,     1,     8,   367,    51,    58,
       6,    75,   342,    73,    10,    73,    11,   390,    16,    17,
      18,    19,    20,    62,    58,   222,   386,    75,    58,   389,
     360,    74,   362,    76,    77,    78,    79,    80,   398,   369,
     400,    84,    75,    75,    75,   369,   432,   377,   160,   218,
     356,   400,   402,    49,    50,    51,    52,    53,   424,     4,
     413,   140,    78,    79,   424,   329,   426,   396,    -1,   429,
      -1,    -1,    68,    69,    70,    71,   119,    -1,   121,    -1,
      78,    79,    -1,   413,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   428,    -1,    -1,   428,    -1,
      -1,    -1,   428,   428,    -1,     6,   149,    -1,   428,    -1,
      -1,   428,   428,    -1,   428,    -1,    -1,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,    50,    39,    50,
      51,    52,    53,    -1,    -1,    46,    -1,    48,    49,    50,
      -1,    -1,    -1,    66,    -1,    68,    69,    -1,    69,    70,
      71,    -1,    -1,    -1,    -1,   218,    -1,    -1,   221,    -1,
     223,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   235,    96,    -1,    86,    -1,     3,     4,     5,
       6,     7,    -1,     9,   247,    96,    12,    98,    14,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    23,   109,    -1,
      -1,    27,    -1,    -1,   115,    -1,   117,   118,    -1,    -1,
     273,    -1,    -1,    -1,    -1,    -1,   127,   140,    -1,    -1,
      -1,    47,    16,    17,    18,    19,    20,    -1,    54,    23,
      56,    -1,    -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,
      34,    35,    -1,    -1,    -1,    -1,    72,    -1,   159,    -1,
      76,    77,    78,   316,    -1,    -1,    -1,     3,     4,     5,
       6,     7,    -1,     9,    -1,    -1,    12,    -1,    14,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    23,   341,    -1,
     191,    27,   205,    -1,    78,    79,   209,    -1,    -1,    -1,
      -1,    -1,   203,   204,   205,    -1,    -1,   208,   209,   222,
     211,    47,    -1,     0,     1,    -1,    -1,    -1,    54,     6,
      56,    57,    -1,    10,    -1,    -1,    -1,    -1,    -1,   382,
      -1,   384,    -1,    -1,   247,    -1,    72,    -1,    74,    -1,
      76,    -1,    78,    79,    -1,   258,    -1,    -1,   401,    -1,
      -1,    -1,    -1,   254,   407,    -1,    -1,    -1,    -1,    -1,
     273,    -1,    49,    50,    51,    52,    53,    -1,    -1,   422,
      -1,    -1,    -1,    -1,    -1,   428,    -1,    -1,    -1,   432,
      -1,    68,    69,    70,    71,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    -1,    22,    23,    24,    25,    26,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,     1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,    -1,    12,
      -1,    14,    -1,    -1,    -1,    -1,    19,    -1,   329,    -1,
      23,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   360,    -1,   362,
      78,    79,    -1,    -1,    47,    -1,   369,    50,    -1,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      63,    64,    65,    -1,    67,    68,   377,    70,    71,    72,
      -1,    74,    75,    76,     1,    78,     3,     4,     5,     6,
       7,    -1,     9,    10,    -1,    12,    -1,    14,    -1,    -1,
      -1,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      27,    -1,    -1,    16,    17,    18,    19,    20,    -1,    22,
      23,    24,    -1,    -1,    -1,    28,    29,    30,    31,    -1,
      47,    34,    35,    50,    -1,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    -1,    63,    64,    65,    -1,
      67,    68,    -1,    70,    71,    72,    -1,    74,    75,    76,
       1,    78,     3,     4,     5,     6,     7,    -1,     9,    10,
      -1,    12,    -1,    14,    -1,    78,    79,    -1,    19,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    27,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    34,    35,    50,
      -1,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      61,    -1,    63,    64,    65,    -1,    67,    68,    -1,    70,
      71,    72,    -1,    74,    -1,    76,    -1,    78,     3,     4,
       5,     6,     7,    -1,     9,    -1,    -1,    12,    -1,    14,
      -1,    78,    79,    -1,    19,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,    -1,    12,
      -1,    14,    47,    -1,    -1,    -1,    19,    -1,    -1,    54,
      23,    56,    57,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      -1,    76,    -1,    78,    47,    -1,     3,     4,     5,     6,
       7,    54,     9,    56,    57,    12,    -1,    14,    -1,    -1,
      -1,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,    72,
      27,    74,    -1,    76,    -1,    78,    -1,    -1,     3,     4,
       5,     6,     7,    -1,     9,    -1,    -1,    12,    -1,    14,
      47,    -1,    -1,    -1,    19,    -1,    -1,    54,    23,    56,
      57,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    74,    -1,    76,
      -1,    78,    47,    -1,     3,     4,     5,     6,     7,    54,
       9,    56,    57,    12,    -1,    14,    -1,    -1,    -1,    -1,
      19,    -1,    -1,    -1,    23,    -1,    -1,    72,    27,    74,
      -1,    76,    -1,    78,     3,     4,     5,     6,     7,    -1,
       9,    -1,    -1,    12,    -1,    14,    -1,    -1,    47,    -1,
      19,    -1,    -1,    -1,    23,    54,    -1,    56,    27,    -1,
       3,     4,     5,     6,     7,    -1,     9,    -1,    -1,    12,
      -1,    14,    -1,    72,    -1,    74,    19,    76,    47,    78,
      23,    -1,    -1,    -1,    27,    54,    -1,    56,    57,    -1,
       3,     4,     5,     6,     7,    -1,     9,    -1,    -1,    12,
      -1,    14,    -1,    72,    47,    -1,    19,    76,    -1,    78,
      23,    54,    -1,    56,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    -1,    76,    47,    78,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    72,
      -1,    -1,    -1,    76,    -1,    78,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    45,    46,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,     8,    -1,    74,    -1,    -1,    -1,    78,    79,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    43,    44,    45,
      46,    78,    79,    16,    17,    18,    19,    20,    -1,    22,
      23,    24,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    77,    78,    79,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    46,    78,    79,    16,    17,    18,
      19,    20,    -1,    22,    23,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    -1,    34,    35,    -1,    -1,    -1,
       8,    73,    10,    34,    35,    -1,    78,    79,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    43,    44,    45,    46,    78,
      79,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,
      78,    79,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    73,
      -1,    -1,    -1,    -1,    78,    79,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,    -1,    74,    -1,    -1,    -1,    78,    79,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    74,    10,
      -1,    -1,    78,    79,    -1,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     8,    -1,    10,    -1,    -1,    -1,    78,    79,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    11,    -1,
      -1,    78,    79,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    -1,    78,    79,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    43,    44,    45,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,    78,
      79,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    10,    49,    50,    51,    52,    53,    68,
      69,    70,    71,    83,    84,    86,   104,   123,   124,   125,
     129,   132,   136,   137,   140,   142,   143,   144,    84,    86,
     104,   125,   129,   132,   136,   137,   140,    83,    83,    83,
       5,    57,   141,    83,    83,    83,     7,    13,    66,    68,
      72,    76,    83,   120,   121,   122,    10,    10,     8,    10,
     143,     0,    10,    10,    10,    72,    74,    72,    74,    74,
     122,     3,     4,     5,     7,     9,    12,    14,    19,    23,
      27,    47,    54,    56,    72,    76,    78,    83,    85,    87,
      88,    89,    94,    95,    96,   126,    72,   120,    11,    74,
      72,   120,   122,    96,     8,   122,     8,   122,    73,    81,
      83,    92,    93,   122,   123,    77,    96,    72,    80,    74,
     102,    57,    74,    96,   108,   109,   111,    83,   130,   131,
      83,   123,   127,   128,   131,   128,    75,    83,   123,   129,
     133,   134,    96,    83,    96,    96,    96,    96,    96,    72,
      72,    83,    96,   123,   124,    83,   103,   122,    72,    80,
       8,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    43,    44,    45,    46,
      74,    78,    79,    93,   122,    83,   138,   139,    73,   103,
     109,   109,   122,    66,    68,    48,     9,    73,    81,    48,
     122,    77,   122,   135,   122,     1,    10,    55,    57,    59,
      60,    61,    63,    64,    65,    67,    68,    75,    83,    84,
      86,    96,    97,    98,    99,   100,   101,   102,   104,   112,
     113,   116,   119,   132,   136,   137,   140,    72,    96,   110,
      79,   106,   107,   109,    78,   122,    48,    73,    10,    75,
      73,    75,    10,   120,    10,   134,    75,    96,     5,    73,
      73,    48,    77,    23,    73,    83,    90,    91,   109,   123,
     122,    96,   108,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,   143,   122,    83,    74,     8,    48,    75,   102,
       9,    73,    73,    93,    83,    73,   122,    93,   122,    48,
      73,    83,   110,    10,    10,    96,    90,    96,   102,    10,
     109,    57,    63,   117,   118,    11,    10,    10,    10,    10,
     101,    75,    10,   111,   102,    83,    48,    75,   122,   131,
      74,   128,    74,    10,    73,    73,   103,   120,   123,    48,
      73,    75,   139,    96,   139,    83,   102,    81,    73,   135,
     102,    74,    10,   102,    64,    10,    96,    83,    73,    58,
       8,   107,   128,   128,   102,    91,    58,    75,    73,   122,
      58,    62,   114,   115,    96,    96,   102,    11,   102,   111,
     109,    75,    75,    74,   141,   102,    73,   102,   112,    96,
     115,    75,    10,    10,    58,    96,   105,   143,    11,    96,
     102,   118,    48,   102,    75,   101,   102,   105
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    85,    86,    87,    87,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    89,    89,
      89,    89,    89,    90,    90,    90,    91,    91,    92,    93,
      93,    93,    93,    94,    94,    95,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    98,    99,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   102,   102,   103,   103,   104,   104,
     104,   105,   105,   106,   106,   107,   107,   108,   109,   109,
     109,   109,   110,   110,   111,   111,   112,   112,   112,   113,
     114,   115,   115,   116,   117,   118,   118,   118,   119,   119,
     120,   120,   120,   120,   120,   121,   121,   122,   122,   122,
     122,   122,   122,   122,   122,   123,   123,   123,   124,   124,
     124,   125,   125,   126,   127,   128,   128,   129,   129,   130,
     131,   131,   132,   132,   133,   133,   133,   133,   134,   134,
     135,   135,   136,   137,   137,   138,   138,   139,   139,   139,
     140,   140,   141,   141,   141,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   143,   143,   144,   144
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     4,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     2,     1,     1,     3,     1,     1,     3,
       3,     1,     1,     4,     3,     4,     1,     3,     2,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       2,     3,     3,     2,     1,     1,     3,     5,     2,     2,
       3,     2,     2,     2,     2,     2,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     2,     1,     3,     2,     3,     1,     6,     8,
       5,     3,     1,     1,     4,     3,     1,     3,     1,     1,
       1,     3,     1,     3,     5,     5,     3,     5,     5,     7,
       4,     2,     1,     5,     5,     3,     5,     5,     2,     2,
       5,     3,     4,     4,     2,     1,     7,     1,     2,     4,
       2,     3,     4,     2,     3,     3,     3,     2,     3,     4,
       4,     3,     3,     5,     1,     3,     2,     5,     8,     2,
       3,     1,     5,     8,     2,     3,     2,     1,     2,     1,
       3,     1,     3,     5,     4,     1,     3,     3,     2,     1,
       7,     5,     5,     9,     7,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     1,     2,     2,     2,     2,     2,
       3,     3,     2,     2,     3,     1,     1,     2,     1,     0
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
#line 146 "src/parser.y"
            {}
#line 1951 "gen/gen_parser.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 146 "src/parser.y"
            {}
#line 1957 "gen/gen_parser.c"
        break;

    case YYSYMBOL_STRING: /* STRING  */
#line 146 "src/parser.y"
            {}
#line 1963 "gen/gen_parser.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 146 "src/parser.y"
            {}
#line 1969 "gen/gen_parser.c"
        break;

    case YYSYMBOL_id: /* id  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1975 "gen/gen_parser.c"
        break;

    case YYSYMBOL_var: /* var  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1981 "gen/gen_parser.c"
        break;

    case YYSYMBOL_embed: /* embed  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1987 "gen/gen_parser.c"
        break;

    case YYSYMBOL_import: /* import  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1993 "gen/gen_parser.c"
        break;

    case YYSYMBOL_assign: /* assign  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1999 "gen/gen_parser.c"
        break;

    case YYSYMBOL_binary_op: /* binary_op  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2005 "gen/gen_parser.c"
        break;

    case YYSYMBOL_unary_op: /* unary_op  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2011 "gen/gen_parser.c"
        break;

    case YYSYMBOL_arg: /* arg  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2017 "gen/gen_parser.c"
        break;

    case YYSYMBOL_arg_list: /* arg_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2023 "gen/gen_parser.c"
        break;

    case YYSYMBOL_param_decl: /* param_decl  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2029 "gen/gen_parser.c"
        break;

    case YYSYMBOL_decl_list: /* decl_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2035 "gen/gen_parser.c"
        break;

    case YYSYMBOL_call: /* call  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2041 "gen/gen_parser.c"
        break;

    case YYSYMBOL_defer: /* defer  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2047 "gen/gen_parser.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2053 "gen/gen_parser.c"
        break;

    case YYSYMBOL_while: /* while  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2059 "gen/gen_parser.c"
        break;

    case YYSYMBOL_do_while: /* do_while  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2065 "gen/gen_parser.c"
        break;

    case YYSYMBOL_goto: /* goto  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2071 "gen/gen_parser.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2077 "gen/gen_parser.c"
        break;

    case YYSYMBOL_statement_list: /* statement_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2083 "gen/gen_parser.c"
        break;

    case YYSYMBOL_body: /* body  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2089 "gen/gen_parser.c"
        break;

    case YYSYMBOL_macro_list: /* macro_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2095 "gen/gen_parser.c"
        break;

    case YYSYMBOL_macro: /* macro  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2101 "gen/gen_parser.c"
        break;

    case YYSYMBOL_expr_list: /* expr_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2107 "gen/gen_parser.c"
        break;

    case YYSYMBOL_struct_init: /* struct_init  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2113 "gen/gen_parser.c"
        break;

    case YYSYMBOL_struct_inits: /* struct_inits  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2119 "gen/gen_parser.c"
        break;

    case YYSYMBOL_struct_construct: /* struct_construct  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2125 "gen/gen_parser.c"
        break;

    case YYSYMBOL_init_expr: /* init_expr  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2131 "gen/gen_parser.c"
        break;

    case YYSYMBOL_cond: /* cond  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2137 "gen/gen_parser.c"
        break;

    case YYSYMBOL_expr_if: /* expr_if  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2143 "gen/gen_parser.c"
        break;

    case YYSYMBOL_if: /* if  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2149 "gen/gen_parser.c"
        break;

    case YYSYMBOL_for: /* for  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2155 "gen/gen_parser.c"
        break;

    case YYSYMBOL_case: /* case  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2161 "gen/gen_parser.c"
        break;

    case YYSYMBOL_case_list: /* case_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2167 "gen/gen_parser.c"
        break;

    case YYSYMBOL_switch: /* switch  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2173 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_for: /* const_for  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2179 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_if: /* const_if  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2185 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const: /* const  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2191 "gen/gen_parser.c"
        break;

    case YYSYMBOL_func_sign: /* func_sign  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2197 "gen/gen_parser.c"
        break;

    case YYSYMBOL_variadic_sign: /* variadic_sign  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2203 "gen/gen_parser.c"
        break;

    case YYSYMBOL_type: /* type  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2209 "gen/gen_parser.c"
        break;

    case YYSYMBOL_var_decl: /* var_decl  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2215 "gen/gen_parser.c"
        break;

    case YYSYMBOL_var_init: /* var_init  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2221 "gen/gen_parser.c"
        break;

    case YYSYMBOL_proc: /* proc  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2227 "gen/gen_parser.c"
        break;

    case YYSYMBOL_lambda: /* lambda  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2233 "gen/gen_parser.c"
        break;

    case YYSYMBOL_struct_elem: /* struct_elem  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2239 "gen/gen_parser.c"
        break;

    case YYSYMBOL_struct_list: /* struct_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2245 "gen/gen_parser.c"
        break;

    case YYSYMBOL_union: /* union  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2251 "gen/gen_parser.c"
        break;

    case YYSYMBOL_generic: /* generic  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2257 "gen/gen_parser.c"
        break;

    case YYSYMBOL_generic_list: /* generic_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2263 "gen/gen_parser.c"
        break;

    case YYSYMBOL_struct: /* struct  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2269 "gen/gen_parser.c"
        break;

    case YYSYMBOL_template_elem: /* template_elem  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2275 "gen/gen_parser.c"
        break;

    case YYSYMBOL_template_list: /* template_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2281 "gen/gen_parser.c"
        break;

    case YYSYMBOL_type_list: /* type_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2287 "gen/gen_parser.c"
        break;

    case YYSYMBOL_type_alias: /* type_alias  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2293 "gen/gen_parser.c"
        break;

    case YYSYMBOL_type_template: /* type_template  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2299 "gen/gen_parser.c"
        break;

    case YYSYMBOL_enum_val: /* enum_val  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2305 "gen/gen_parser.c"
        break;

    case YYSYMBOL_enum_list: /* enum_list  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2311 "gen/gen_parser.c"
        break;

    case YYSYMBOL_enum: /* enum  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2317 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top_if: /* top_if  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2323 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top: /* top  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2329 "gen/gen_parser.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 147 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2335 "gen/gen_parser.c"
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
#line 151 "src/parser.y"
       {
		(yyval.node) = gen_id(strdup((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 2644 "gen/gen_parser.c"
    break;

  case 3: /* var: var_decl  */
#line 157 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2650 "gen/gen_parser.c"
    break;

  case 4: /* var: var_init  */
#line 158 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2656 "gen/gen_parser.c"
    break;

  case 5: /* embed: "embed" "(" STRING ")"  */
#line 161 "src/parser.y"
                              { (yyval.node) = gen_embed(clone_string((yyvsp[-1].str)));  }
#line 2662 "gen/gen_parser.c"
    break;

  case 6: /* import: "import" STRING  */
#line 164 "src/parser.y"
                        { (yyval.node) = gen_import(clone_string((yyvsp[0].str)));  }
#line 2668 "gen/gen_parser.c"
    break;

  case 7: /* assign: expr "=" expr  */
#line 167 "src/parser.y"
                      { (yyval.node) = gen_assign((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2674 "gen/gen_parser.c"
    break;

  case 8: /* assign: expr "=" struct_construct  */
#line 168 "src/parser.y"
                                    { (yyval.node) = gen_assign((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2680 "gen/gen_parser.c"
    break;

  case 9: /* binary_op: expr "+" expr  */
#line 171 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2686 "gen/gen_parser.c"
    break;

  case 10: /* binary_op: expr "-" expr  */
#line 172 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2692 "gen/gen_parser.c"
    break;

  case 11: /* binary_op: expr "*" expr  */
#line 173 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2698 "gen/gen_parser.c"
    break;

  case 12: /* binary_op: expr "/" expr  */
#line 174 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2704 "gen/gen_parser.c"
    break;

  case 13: /* binary_op: expr "%" expr  */
#line 175 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2710 "gen/gen_parser.c"
    break;

  case 14: /* binary_op: expr "^" expr  */
#line 176 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2716 "gen/gen_parser.c"
    break;

  case 15: /* binary_op: expr "^^" expr  */
#line 177 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_POW, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2722 "gen/gen_parser.c"
    break;

  case 16: /* binary_op: expr "&" expr  */
#line 178 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2728 "gen/gen_parser.c"
    break;

  case 17: /* binary_op: expr "&&" expr  */
#line 179 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LAND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2734 "gen/gen_parser.c"
    break;

  case 18: /* binary_op: expr "|" expr  */
#line 180 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2740 "gen/gen_parser.c"
    break;

  case 19: /* binary_op: expr "||" expr  */
#line 181 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2746 "gen/gen_parser.c"
    break;

  case 20: /* binary_op: expr "<<" expr  */
#line 182 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2752 "gen/gen_parser.c"
    break;

  case 21: /* binary_op: expr ">>" expr  */
#line 183 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2758 "gen/gen_parser.c"
    break;

  case 22: /* binary_op: expr "+=" expr  */
#line 184 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2764 "gen/gen_parser.c"
    break;

  case 23: /* binary_op: expr "-=" expr  */
#line 185 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2770 "gen/gen_parser.c"
    break;

  case 24: /* binary_op: expr "*=" expr  */
#line 186 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2776 "gen/gen_parser.c"
    break;

  case 25: /* binary_op: expr "/=" expr  */
#line 187 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2782 "gen/gen_parser.c"
    break;

  case 26: /* binary_op: expr "%=" expr  */
#line 188 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2788 "gen/gen_parser.c"
    break;

  case 27: /* binary_op: expr "&=" expr  */
#line 189 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2794 "gen/gen_parser.c"
    break;

  case 28: /* binary_op: expr "|=" expr  */
#line 190 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2800 "gen/gen_parser.c"
    break;

  case 29: /* binary_op: expr "^=" expr  */
#line 191 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2806 "gen/gen_parser.c"
    break;

  case 30: /* binary_op: expr "<<=" expr  */
#line 192 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2814 "gen/gen_parser.c"
    break;

  case 31: /* binary_op: expr ">>=" expr  */
#line 195 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2822 "gen/gen_parser.c"
    break;

  case 32: /* binary_op: expr "<" expr  */
#line 198 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_LT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2828 "gen/gen_parser.c"
    break;

  case 33: /* binary_op: expr ">" expr  */
#line 199 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_GT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2834 "gen/gen_parser.c"
    break;

  case 34: /* binary_op: expr "<=" expr  */
#line 200 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2840 "gen/gen_parser.c"
    break;

  case 35: /* binary_op: expr ">=" expr  */
#line 201 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_GE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2846 "gen/gen_parser.c"
    break;

  case 36: /* binary_op: expr "!=" expr  */
#line 202 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_NE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2852 "gen/gen_parser.c"
    break;

  case 37: /* binary_op: expr "==" expr  */
#line 203 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_EQ, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2858 "gen/gen_parser.c"
    break;

  case 38: /* unary_op: "-" expr  */
#line 206 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NEG, (yyvsp[0].node));  }
#line 2864 "gen/gen_parser.c"
    break;

  case 39: /* unary_op: "!" expr  */
#line 207 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_LNOT, (yyvsp[0].node));  }
#line 2870 "gen/gen_parser.c"
    break;

  case 40: /* unary_op: "&" expr  */
#line 208 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 2876 "gen/gen_parser.c"
    break;

  case 41: /* unary_op: "'" expr  */
#line 209 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_DEREF, (yyvsp[0].node));  }
#line 2882 "gen/gen_parser.c"
    break;

  case 42: /* unary_op: "~" expr  */
#line 210 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NOT, (yyvsp[0].node));  }
#line 2888 "gen/gen_parser.c"
    break;

  case 43: /* arg: "&" var_decl  */
#line 213 "src/parser.y"
                  { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 2894 "gen/gen_parser.c"
    break;

  case 44: /* arg: var_decl  */
#line 214 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2900 "gen/gen_parser.c"
    break;

  case 45: /* arg: init_expr  */
#line 215 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2906 "gen/gen_parser.c"
    break;

  case 46: /* arg_list: arg "," arg_list  */
#line 218 "src/parser.y"
                           { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2912 "gen/gen_parser.c"
    break;

  case 47: /* arg_list: arg  */
#line 219 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2918 "gen/gen_parser.c"
    break;

  case 48: /* param_decl: type  */
#line 222 "src/parser.y"
                 { (yyval.node) = gen_var(NULL, (yyvsp[0].node), NULL);  }
#line 2924 "gen/gen_parser.c"
    break;

  case 49: /* decl_list: var_decl "," decl_list  */
#line 224 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2930 "gen/gen_parser.c"
    break;

  case 50: /* decl_list: param_decl "," decl_list  */
#line 225 "src/parser.y"
                                   { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2936 "gen/gen_parser.c"
    break;

  case 51: /* decl_list: var_decl  */
#line 226 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2942 "gen/gen_parser.c"
    break;

  case 52: /* decl_list: param_decl  */
#line 227 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2948 "gen/gen_parser.c"
    break;

  case 53: /* call: id "(" arg_list ")"  */
#line 231 "src/parser.y"
                          { (yyval.node) = gen_call((yyvsp[-3].node), (yyvsp[-1].node));  }
#line 2954 "gen/gen_parser.c"
    break;

  case 54: /* call: id "(" ")"  */
#line 232 "src/parser.y"
                     { (yyval.node) = gen_call((yyvsp[-2].node), NULL);  }
#line 2960 "gen/gen_parser.c"
    break;

  case 55: /* defer: "defer" "(" expr ")"  */
#line 235 "src/parser.y"
                            { (yyval.node) = gen_defer((yyvsp[-1].node));  }
#line 2966 "gen/gen_parser.c"
    break;

  case 56: /* expr: id  */
#line 239 "src/parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 2972 "gen/gen_parser.c"
    break;

  case 57: /* expr: expr "." id  */
#line 240 "src/parser.y"
                      { (yyval.node) = gen_dot((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2978 "gen/gen_parser.c"
    break;

  case 58: /* expr: "..." id  */
#line 241 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2984 "gen/gen_parser.c"
    break;

  case 59: /* expr: "@"  */
#line 242 "src/parser.y"
              { (yyval.node) = gen_last();  }
#line 2990 "gen/gen_parser.c"
    break;

  case 60: /* expr: INT  */
#line 243 "src/parser.y"
              { (yyval.node) = gen_int((yyvsp[0].integer)); (yyval.node)->loc = to_src_loc(&yylloc); }
#line 2996 "gen/gen_parser.c"
    break;

  case 61: /* expr: FLOAT  */
#line 244 "src/parser.y"
                { (yyval.node) = gen_float((yyvsp[0].dbl)); (yyval.node)->loc = to_src_loc(&yylloc);  }
#line 3002 "gen/gen_parser.c"
    break;

  case 62: /* expr: STRING  */
#line 245 "src/parser.y"
                 {
		(yyval.node) = gen_string(clone_string((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 3011 "gen/gen_parser.c"
    break;

  case 63: /* expr: "(" expr ")"  */
#line 249 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3017 "gen/gen_parser.c"
    break;

  case 64: /* expr: assign  */
#line 250 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3023 "gen/gen_parser.c"
    break;

  case 65: /* expr: call  */
#line 251 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3029 "gen/gen_parser.c"
    break;

  case 66: /* expr: defer  */
#line 252 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3035 "gen/gen_parser.c"
    break;

  case 67: /* expr: binary_op  */
#line 253 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3041 "gen/gen_parser.c"
    break;

  case 68: /* expr: unary_op  */
#line 254 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3047 "gen/gen_parser.c"
    break;

  case 69: /* expr: "(" var_init ")"  */
#line 255 "src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 3053 "gen/gen_parser.c"
    break;

  case 70: /* expr: "sizeof" expr  */
#line 256 "src/parser.y"
                        { (yyval.node) = gen_sizeof((yyvsp[0].node)); }
#line 3059 "gen/gen_parser.c"
    break;

  case 71: /* expr: expr "as" type  */
#line 257 "src/parser.y"
                         { (yyval.node) = gen_cast((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3065 "gen/gen_parser.c"
    break;

  case 72: /* expr: id "::" type  */
#line 258 "src/parser.y"
                       { (yyval.node) = gen_fetch((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3071 "gen/gen_parser.c"
    break;

  case 73: /* expr: "as" type  */
#line 259 "src/parser.y"
                    { (yyval.node) = gen_as((yyvsp[0].node)); }
#line 3077 "gen/gen_parser.c"
    break;

  case 74: /* expr: embed  */
#line 260 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3083 "gen/gen_parser.c"
    break;

  case 75: /* expr: lambda  */
#line 261 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3089 "gen/gen_parser.c"
    break;

  case 76: /* while: "while" expr body  */
#line 264 "src/parser.y"
                         { (yyval.node) = gen_while((yyvsp[-1].node), (yyvsp[0].node));  }
#line 3095 "gen/gen_parser.c"
    break;

  case 77: /* do_while: "do" body "while" expr ";"  */
#line 267 "src/parser.y"
                                     {
		(yyval.node) = gen_while((yyvsp[-3].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_DELAYED);
	}
#line 3104 "gen/gen_parser.c"
    break;

  case 78: /* goto: "goto" id  */
#line 273 "src/parser.y"
                { (yyval.node) = gen_goto(gen_label((yyvsp[0].node)));  }
#line 3110 "gen/gen_parser.c"
    break;

  case 79: /* statement: expr ";"  */
#line 275 "src/parser.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 3116 "gen/gen_parser.c"
    break;

  case 80: /* statement: "return" init_expr ";"  */
#line 276 "src/parser.y"
                                 { (yyval.node) = gen_return((yyvsp[-1].node));  }
#line 3122 "gen/gen_parser.c"
    break;

  case 81: /* statement: "return" ";"  */
#line 277 "src/parser.y"
                       { (yyval.node) = gen_return(NULL); }
#line 3128 "gen/gen_parser.c"
    break;

  case 82: /* statement: "break" ";"  */
#line 278 "src/parser.y"
                      { (yyval.node) = gen_ctrl(AST_CTRL_BREAK, to_src_loc(&yylloc)); }
#line 3134 "gen/gen_parser.c"
    break;

  case 83: /* statement: "continue" ";"  */
#line 279 "src/parser.y"
                         { (yyval.node) = gen_ctrl(AST_CTRL_CONTINUE,
	to_src_loc(&yylloc));  }
#line 3141 "gen/gen_parser.c"
    break;

  case 84: /* statement: import ";"  */
#line 281 "src/parser.y"
                     { (yyval.node) = (yyvsp[-1].node); }
#line 3147 "gen/gen_parser.c"
    break;

  case 85: /* statement: var ";"  */
#line 282 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3153 "gen/gen_parser.c"
    break;

  case 86: /* statement: if  */
#line 283 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3159 "gen/gen_parser.c"
    break;

  case 87: /* statement: goto ";"  */
#line 284 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3165 "gen/gen_parser.c"
    break;

  case 88: /* statement: id ":"  */
#line 285 "src/parser.y"
                 { (yyval.node) = gen_label((yyvsp[-1].node));  }
#line 3171 "gen/gen_parser.c"
    break;

  case 89: /* statement: for  */
#line 286 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3177 "gen/gen_parser.c"
    break;

  case 90: /* statement: const  */
#line 287 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3183 "gen/gen_parser.c"
    break;

  case 91: /* statement: while  */
#line 288 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3189 "gen/gen_parser.c"
    break;

  case 92: /* statement: do_while  */
#line 289 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3195 "gen/gen_parser.c"
    break;

  case 93: /* statement: switch  */
#line 290 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3201 "gen/gen_parser.c"
    break;

  case 94: /* statement: macro  */
#line 291 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3207 "gen/gen_parser.c"
    break;

  case 95: /* statement: struct  */
#line 292 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3213 "gen/gen_parser.c"
    break;

  case 96: /* statement: type_alias ";"  */
#line 293 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3219 "gen/gen_parser.c"
    break;

  case 97: /* statement: type_template  */
#line 294 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3225 "gen/gen_parser.c"
    break;

  case 98: /* statement: enum  */
#line 295 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3231 "gen/gen_parser.c"
    break;

  case 99: /* statement: body  */
#line 296 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3237 "gen/gen_parser.c"
    break;

  case 100: /* statement: ";"  */
#line 297 "src/parser.y"
              { (yyval.node) = gen_empty();  }
#line 3243 "gen/gen_parser.c"
    break;

  case 101: /* statement: error  */
#line 298 "src/parser.y"
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
#line 3262 "gen/gen_parser.c"
    break;

  case 102: /* statement_list: statement statement_list  */
#line 314 "src/parser.y"
                                         { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3268 "gen/gen_parser.c"
    break;

  case 103: /* statement_list: statement  */
#line 315 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3274 "gen/gen_parser.c"
    break;

  case 104: /* body: "{" statement_list "}"  */
#line 318 "src/parser.y"
                             { (yyval.node) = gen_block((yyvsp[-1].node));  }
#line 3280 "gen/gen_parser.c"
    break;

  case 105: /* body: "{" "}"  */
#line 319 "src/parser.y"
                  { (yyval.node) = gen_block(gen_empty());  }
#line 3286 "gen/gen_parser.c"
    break;

  case 106: /* macro_list: id "," macro_list  */
#line 322 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 3292 "gen/gen_parser.c"
    break;

  case 107: /* macro_list: id  */
#line 323 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3298 "gen/gen_parser.c"
    break;

  case 108: /* macro: "define" id "(" macro_list ")" body  */
#line 326 "src/parser.y"
                                           {
		(yyval.node) = gen_macro((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3307 "gen/gen_parser.c"
    break;

  case 109: /* macro: "define" id "(" macro_list "..." id ")" body  */
#line 330 "src/parser.y"
                                                       {
		/* TODO: the location data of the variadic ID is way off */
		ast_append((yyvsp[-4].node), (yyvsp[-2].node));
		(yyval.node) = gen_macro((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3319 "gen/gen_parser.c"
    break;

  case 110: /* macro: "define" id "(" ")" body  */
#line 337 "src/parser.y"
                                   {
		(yyval.node) = gen_macro((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3328 "gen/gen_parser.c"
    break;

  case 111: /* expr_list: expr "," expr_list  */
#line 343 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3334 "gen/gen_parser.c"
    break;

  case 112: /* expr_list: expr  */
#line 344 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3340 "gen/gen_parser.c"
    break;

  case 113: /* struct_init: init_expr  */
#line 347 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 3346 "gen/gen_parser.c"
    break;

  case 114: /* struct_init: "." id "=" init_expr  */
#line 348 "src/parser.y"
                               {
		(yyval.node) = gen_var((yyvsp[-2].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_MEMBER);
	}
#line 3355 "gen/gen_parser.c"
    break;

  case 115: /* struct_inits: struct_init "," struct_inits  */
#line 354 "src/parser.y"
                                           { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3361 "gen/gen_parser.c"
    break;

  case 116: /* struct_inits: struct_init  */
#line 355 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3367 "gen/gen_parser.c"
    break;

  case 117: /* struct_construct: "{" struct_inits "}"  */
#line 358 "src/parser.y"
                                       { (yyval.node) = gen_init((yyvsp[-1].node)); }
#line 3373 "gen/gen_parser.c"
    break;

  case 118: /* init_expr: expr  */
#line 361 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3379 "gen/gen_parser.c"
    break;

  case 119: /* init_expr: expr_if  */
#line 362 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 3385 "gen/gen_parser.c"
    break;

  case 120: /* init_expr: struct_construct  */
#line 363 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 3391 "gen/gen_parser.c"
    break;

  case 121: /* init_expr: struct_construct "as" type  */
#line 364 "src/parser.y"
                                     { (yyval.node) = gen_cast((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3397 "gen/gen_parser.c"
    break;

  case 122: /* cond: expr  */
#line 367 "src/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 3403 "gen/gen_parser.c"
    break;

  case 123: /* cond: "(" expr_if ")"  */
#line 368 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 3409 "gen/gen_parser.c"
    break;

  case 124: /* expr_if: "if" cond body "else" body  */
#line 372 "src/parser.y"
                                    { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3415 "gen/gen_parser.c"
    break;

  case 125: /* expr_if: "if" cond body "else" expr_if  */
#line 373 "src/parser.y"
                                        { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3421 "gen/gen_parser.c"
    break;

  case 126: /* if: "if" cond body  */
#line 376 "src/parser.y"
                   { (yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3427 "gen/gen_parser.c"
    break;

  case 127: /* if: "if" cond body "else" body  */
#line 377 "src/parser.y"
                                     { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3433 "gen/gen_parser.c"
    break;

  case 128: /* if: "if" cond body "else" if  */
#line 378 "src/parser.y"
                                   { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3439 "gen/gen_parser.c"
    break;

  case 129: /* for: "for" arg ";" expr ";" expr body  */
#line 381 "src/parser.y"
                                      { (yyval.node) = gen_for((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3445 "gen/gen_parser.c"
    break;

  case 130: /* case: "case" expr ":" statement_list  */
#line 384 "src/parser.y"
                                     { (yyval.node) = gen_case((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3451 "gen/gen_parser.c"
    break;

  case 131: /* case_list: case case_list  */
#line 387 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3457 "gen/gen_parser.c"
    break;

  case 132: /* case_list: case  */
#line 388 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3463 "gen/gen_parser.c"
    break;

  case 133: /* switch: "switch" expr "{" case_list "}"  */
#line 391 "src/parser.y"
                                        { (yyval.node) = gen_switch((yyvsp[-3].node), (yyvsp[-1].node));  }
#line 3469 "gen/gen_parser.c"
    break;

  case 134: /* const_for: "for" id ":" expr_list body  */
#line 394 "src/parser.y"
                                       {
		/* TODO: should id be a separate rule? */
		(yyval.node) = gen_for((yyvsp[-3].node), NULL, (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3479 "gen/gen_parser.c"
    break;

  case 135: /* const_if: "if" expr body  */
#line 401 "src/parser.y"
                         {
		(yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3488 "gen/gen_parser.c"
    break;

  case 136: /* const_if: "if" expr body "else" body  */
#line 405 "src/parser.y"
                                     {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3498 "gen/gen_parser.c"
    break;

  case 137: /* const_if: "if" expr body "else" const_if  */
#line 410 "src/parser.y"
                                         {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
	}
#line 3507 "gen/gen_parser.c"
    break;

  case 138: /* const: "const" const_if  */
#line 418 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST);
      }
#line 3514 "gen/gen_parser.c"
    break;

  case 139: /* const: "const" const_for  */
#line 420 "src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST);
	 }
#line 3521 "gen/gen_parser.c"
    break;

  case 140: /* func_sign: "(" decl_list "=>" type ")"  */
#line 424 "src/parser.y"
                                       {
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 3529 "gen/gen_parser.c"
    break;

  case 141: /* func_sign: "(" decl_list ")"  */
#line 427 "src/parser.y"
                            { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-1].node), NULL);
	 }
#line 3536 "gen/gen_parser.c"
    break;

  case 142: /* func_sign: "(" decl_list "=>" ")"  */
#line 429 "src/parser.y"
                                 { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-2].node), NULL);
	 }
#line 3543 "gen/gen_parser.c"
    break;

  case 143: /* func_sign: "(" "=>" type ")"  */
#line 431 "src/parser.y"
                            { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, (yyvsp[-1].node));
	 }
#line 3550 "gen/gen_parser.c"
    break;

  case 144: /* func_sign: "(" ")"  */
#line 433 "src/parser.y"
                  { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, NULL);
	 }
#line 3557 "gen/gen_parser.c"
    break;

  case 145: /* variadic_sign: func_sign  */
#line 437 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3563 "gen/gen_parser.c"
    break;

  case 146: /* variadic_sign: "(" decl_list "..." id "=>" type ")"  */
#line 438 "src/parser.y"
                                               {
		ast_append((yyvsp[-5].node), (yyvsp[-3].node));
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
	}
#line 3573 "gen/gen_parser.c"
    break;

  case 147: /* type: id  */
#line 445 "src/parser.y"
         { (yyval.node) = gen_type(AST_TYPE_ID, (yyvsp[0].node), NULL, NULL); }
#line 3579 "gen/gen_parser.c"
    break;

  case 148: /* type: "'" func_sign  */
#line 446 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3588 "gen/gen_parser.c"
    break;

  case 149: /* type: id "(" type_list ")"  */
#line 450 "src/parser.y"
                               {
		(yyval.node) = gen_type(AST_TYPE_GENERIC, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
	}
#line 3596 "gen/gen_parser.c"
    break;

  case 150: /* type: "'" type  */
#line 453 "src/parser.y"
                   {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3605 "gen/gen_parser.c"
    break;

  case 151: /* type: "[" "]" type  */
#line 457 "src/parser.y"
                       {
		(yyval.node) = gen_type(AST_TYPE_ARR, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3614 "gen/gen_parser.c"
    break;

  case 152: /* type: "[" expr "]" type  */
#line 461 "src/parser.y"
                            {
		(yyval.node) = gen_type(AST_TYPE_ARR, NULL, (yyvsp[-2].node), NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3623 "gen/gen_parser.c"
    break;

  case 153: /* type: "typeof" expr  */
#line 465 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_TYPEOF, NULL, (yyvsp[0].node), NULL);
	}
#line 3631 "gen/gen_parser.c"
    break;

  case 154: /* type: id "::" type  */
#line 468 "src/parser.y"
                       {
		(yyval.node) = gen_type(AST_TYPE_MEMBER, (yyvsp[-2].node), (yyvsp[0].node), NULL);
	}
#line 3639 "gen/gen_parser.c"
    break;

  case 155: /* var_decl: id "mut" type  */
#line 473 "src/parser.y"
                        {
		(yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_MUTABLE);
	}
#line 3648 "gen/gen_parser.c"
    break;

  case 156: /* var_decl: id "const" type  */
#line 477 "src/parser.y"
                          { (yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);  }
#line 3654 "gen/gen_parser.c"
    break;

  case 157: /* var_decl: id type  */
#line 478 "src/parser.y"
                  { (yyval.node) = gen_var((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3660 "gen/gen_parser.c"
    break;

  case 158: /* var_init: var_decl "=" init_expr  */
#line 481 "src/parser.y"
                                 { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->_var.init = (yyvsp[0].node); }
#line 3666 "gen/gen_parser.c"
    break;

  case 159: /* var_init: id "mut" "=" init_expr  */
#line 482 "src/parser.y"
                                 {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED | AST_FLAG_MUTABLE);
	}
#line 3675 "gen/gen_parser.c"
    break;

  case 160: /* var_init: id "const" "=" init_expr  */
#line 486 "src/parser.y"
                                   {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 3684 "gen/gen_parser.c"
    break;

  case 161: /* proc: id variadic_sign body  */
#line 492 "src/parser.y"
                            {
		(yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), (yyvsp[-1].node)->flags);
	}
#line 3693 "gen/gen_parser.c"
    break;

  case 162: /* proc: "extern" id func_sign  */
#line 496 "src/parser.y"
                                {
		(yyval.node) = gen_proc((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_EXTERN);
	}
#line 3702 "gen/gen_parser.c"
    break;

  case 163: /* lambda: "[" macro_list "]" func_sign body  */
#line 502 "src/parser.y"
                                          { (yyval.node) = gen_lambda((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3708 "gen/gen_parser.c"
    break;

  case 164: /* struct_elem: var_decl  */
#line 505 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3714 "gen/gen_parser.c"
    break;

  case 165: /* struct_list: struct_elem ";" struct_list  */
#line 508 "src/parser.y"
                                         { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3720 "gen/gen_parser.c"
    break;

  case 166: /* struct_list: struct_elem ";"  */
#line 509 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 3726 "gen/gen_parser.c"
    break;

  case 167: /* union: "union" id "{" struct_list "}"  */
#line 512 "src/parser.y"
                                      {
		(yyval.node) = gen_union((yyvsp[-3].node), NULL, (yyvsp[-1].node));
	}
#line 3734 "gen/gen_parser.c"
    break;

  case 168: /* union: "union" id "(" generic_list ")" "{" struct_list "}"  */
#line 515 "src/parser.y"
                                                              {
		(yyval.node) = gen_union((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
	}
#line 3742 "gen/gen_parser.c"
    break;

  case 169: /* generic: id type  */
#line 520 "src/parser.y"
                 { (yyval.node) = gen_alias((yyvsp[-1].node), (yyvsp[0].node)); }
#line 3748 "gen/gen_parser.c"
    break;

  case 170: /* generic_list: generic "," generic_list  */
#line 521 "src/parser.y"
                                       { (yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 3754 "gen/gen_parser.c"
    break;

  case 171: /* generic_list: generic  */
#line 522 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 3760 "gen/gen_parser.c"
    break;

  case 172: /* struct: "struct" id "{" struct_list "}"  */
#line 525 "src/parser.y"
                                        {
		(yyval.node) = gen_struct((yyvsp[-3].node), NULL, (yyvsp[-1].node));
	}
#line 3768 "gen/gen_parser.c"
    break;

  case 173: /* struct: "struct" id "(" generic_list ")" "{" struct_list "}"  */
#line 528 "src/parser.y"
                                                               {
		(yyval.node) = gen_struct((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
	}
#line 3776 "gen/gen_parser.c"
    break;

  case 174: /* template_elem: id ";"  */
#line 535 "src/parser.y"
                      { (yyval.node) = (yyvsp[-1].node); }
#line 3782 "gen/gen_parser.c"
    break;

  case 175: /* template_elem: id func_sign ";"  */
#line 536 "src/parser.y"
                           { (yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), NULL);  }
#line 3788 "gen/gen_parser.c"
    break;

  case 176: /* template_elem: var_decl ";"  */
#line 537 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3794 "gen/gen_parser.c"
    break;

  case 177: /* template_elem: union  */
#line 538 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3800 "gen/gen_parser.c"
    break;

  case 178: /* template_list: template_elem template_list  */
#line 541 "src/parser.y"
                                           { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3806 "gen/gen_parser.c"
    break;

  case 179: /* template_list: template_elem  */
#line 542 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3812 "gen/gen_parser.c"
    break;

  case 180: /* type_list: type "," type_list  */
#line 545 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3818 "gen/gen_parser.c"
    break;

  case 181: /* type_list: type  */
#line 546 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3824 "gen/gen_parser.c"
    break;

  case 182: /* type_alias: "typedef" id type  */
#line 549 "src/parser.y"
                              { (yyval.node) = gen_alias((yyvsp[-1].node), (yyvsp[0].node));  }
#line 3830 "gen/gen_parser.c"
    break;

  case 183: /* type_template: "typedef" id "{" template_list "}"  */
#line 554 "src/parser.y"
                                                  {
		(yyval.node) = gen_template((yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 3838 "gen/gen_parser.c"
    break;

  case 184: /* type_template: "typedef" id "{" "}"  */
#line 557 "src/parser.y"
                               {
		/* should match anything, but doesn't implement anything */
		(yyval.node) = gen_template((yyvsp[-2].node), NULL);
	}
#line 3847 "gen/gen_parser.c"
    break;

  case 185: /* enum_val: id  */
#line 563 "src/parser.y"
             { (yyval.node) = gen_val((yyvsp[0].node), NULL);  }
#line 3853 "gen/gen_parser.c"
    break;

  case 186: /* enum_val: id "=" expr  */
#line 564 "src/parser.y"
                      { (yyval.node) = gen_val((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3859 "gen/gen_parser.c"
    break;

  case 187: /* enum_list: enum_val "," enum_list  */
#line 567 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3865 "gen/gen_parser.c"
    break;

  case 188: /* enum_list: enum_val ","  */
#line 568 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3871 "gen/gen_parser.c"
    break;

  case 189: /* enum_list: enum_val  */
#line 569 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3877 "gen/gen_parser.c"
    break;

  case 190: /* enum: "enum" id ":" type "{" enum_list "}"  */
#line 572 "src/parser.y"
                                           { (yyval.node) = gen_enum((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3883 "gen/gen_parser.c"
    break;

  case 191: /* enum: "enum" id "{" enum_list "}"  */
#line 573 "src/parser.y"
                                      {
		(yyval.node) = gen_enum((yyvsp[-3].node), NULL, (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 3892 "gen/gen_parser.c"
    break;

  case 192: /* top_if: "if" expr "{" unit "}"  */
#line 579 "src/parser.y"
                               {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-1].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3901 "gen/gen_parser.c"
    break;

  case 193: /* top_if: "if" expr "{" unit "}" "else" "{" unit "}"  */
#line 583 "src/parser.y"
                                                     {
		(yyval.node) = gen_if((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3910 "gen/gen_parser.c"
    break;

  case 194: /* top_if: "if" expr "{" unit "}" "else" top_if  */
#line 587 "src/parser.y"
                                               {
		(yyval.node) = gen_if((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3919 "gen/gen_parser.c"
    break;

  case 195: /* top: ";"  */
#line 595 "src/parser.y"
         { (yyval.node) = gen_empty(); }
#line 3925 "gen/gen_parser.c"
    break;

  case 196: /* top: enum  */
#line 596 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3931 "gen/gen_parser.c"
    break;

  case 197: /* top: proc  */
#line 597 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3937 "gen/gen_parser.c"
    break;

  case 198: /* top: struct  */
#line 598 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3943 "gen/gen_parser.c"
    break;

  case 199: /* top: union  */
#line 599 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3949 "gen/gen_parser.c"
    break;

  case 200: /* top: macro  */
#line 600 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3955 "gen/gen_parser.c"
    break;

  case 201: /* top: "const" top_if  */
#line 601 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 3961 "gen/gen_parser.c"
    break;

  case 202: /* top: import ";"  */
#line 602 "src/parser.y"
                     { (yyval.node) = (yyvsp[-1].node); }
#line 3967 "gen/gen_parser.c"
    break;

  case 203: /* top: type_alias ";"  */
#line 603 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3973 "gen/gen_parser.c"
    break;

  case 204: /* top: type_template  */
#line 604 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3979 "gen/gen_parser.c"
    break;

  case 205: /* top: "pub" enum  */
#line 605 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3985 "gen/gen_parser.c"
    break;

  case 206: /* top: "pub" struct  */
#line 606 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3991 "gen/gen_parser.c"
    break;

  case 207: /* top: "pub" union  */
#line 607 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3997 "gen/gen_parser.c"
    break;

  case 208: /* top: "pub" proc  */
#line 608 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4003 "gen/gen_parser.c"
    break;

  case 209: /* top: "pub" macro  */
#line 609 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4009 "gen/gen_parser.c"
    break;

  case 210: /* top: "pub" import ";"  */
#line 610 "src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 4015 "gen/gen_parser.c"
    break;

  case 211: /* top: "pub" type_alias ";"  */
#line 611 "src/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 4021 "gen/gen_parser.c"
    break;

  case 212: /* top: "pub" type_template  */
#line 612 "src/parser.y"
                              { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4027 "gen/gen_parser.c"
    break;

  case 213: /* top: var ";"  */
#line 613 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 4033 "gen/gen_parser.c"
    break;

  case 214: /* top: "pub" var ";"  */
#line 614 "src/parser.y"
                        { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 4039 "gen/gen_parser.c"
    break;

  case 215: /* top: error  */
#line 615 "src/parser.y"
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
#line 4057 "gen/gen_parser.c"
    break;

  case 216: /* unit: top  */
#line 630 "src/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 4063 "gen/gen_parser.c"
    break;

  case 217: /* unit: top unit  */
#line 631 "src/parser.y"
                   { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 4069 "gen/gen_parser.c"
    break;

  case 218: /* input: unit  */
#line 634 "src/parser.y"
            { parser->tree = (yyvsp[0].node); }
#line 4075 "gen/gen_parser.c"
    break;


#line 4079 "gen/gen_parser.c"

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

#line 637 "src/parser.y"

