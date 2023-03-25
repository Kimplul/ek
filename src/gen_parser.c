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


#line 85 "src/gen_parser.c"

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
  YYSYMBOL_TYPEDEF = 52,                   /* "type"  */
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
  YYSYMBOL_FATARROW = 80,                  /* "=>"  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_id = 82,                        /* id  */
  YYSYMBOL_var = 83,                       /* var  */
  YYSYMBOL_embed = 84,                     /* embed  */
  YYSYMBOL_import = 85,                    /* import  */
  YYSYMBOL_assign = 86,                    /* assign  */
  YYSYMBOL_binary_op = 87,                 /* binary_op  */
  YYSYMBOL_unary_op = 88,                  /* unary_op  */
  YYSYMBOL_arg = 89,                       /* arg  */
  YYSYMBOL_arg_list = 90,                  /* arg_list  */
  YYSYMBOL_param_decl = 91,                /* param_decl  */
  YYSYMBOL_decl_list = 92,                 /* decl_list  */
  YYSYMBOL_call = 93,                      /* call  */
  YYSYMBOL_defer = 94,                     /* defer  */
  YYSYMBOL_expr = 95,                      /* expr  */
  YYSYMBOL_while = 96,                     /* while  */
  YYSYMBOL_do_while = 97,                  /* do_while  */
  YYSYMBOL_goto = 98,                      /* goto  */
  YYSYMBOL_statement = 99,                 /* statement  */
  YYSYMBOL_statement_list = 100,           /* statement_list  */
  YYSYMBOL_body = 101,                     /* body  */
  YYSYMBOL_macro_list = 102,               /* macro_list  */
  YYSYMBOL_macro = 103,                    /* macro  */
  YYSYMBOL_expr_list = 104,                /* expr_list  */
  YYSYMBOL_struct_init = 105,              /* struct_init  */
  YYSYMBOL_struct_inits = 106,             /* struct_inits  */
  YYSYMBOL_struct_construct = 107,         /* struct_construct  */
  YYSYMBOL_init_expr = 108,                /* init_expr  */
  YYSYMBOL_cond = 109,                     /* cond  */
  YYSYMBOL_expr_if = 110,                  /* expr_if  */
  YYSYMBOL_if = 111,                       /* if  */
  YYSYMBOL_for = 112,                      /* for  */
  YYSYMBOL_case = 113,                     /* case  */
  YYSYMBOL_case_list = 114,                /* case_list  */
  YYSYMBOL_switch = 115,                   /* switch  */
  YYSYMBOL_const_for = 116,                /* const_for  */
  YYSYMBOL_const_if = 117,                 /* const_if  */
  YYSYMBOL_const = 118,                    /* const  */
  YYSYMBOL_func_sign = 119,                /* func_sign  */
  YYSYMBOL_variadic_sign = 120,            /* variadic_sign  */
  YYSYMBOL_type = 121,                     /* type  */
  YYSYMBOL_var_decl = 122,                 /* var_decl  */
  YYSYMBOL_var_init = 123,                 /* var_init  */
  YYSYMBOL_proc = 124,                     /* proc  */
  YYSYMBOL_lambda = 125,                   /* lambda  */
  YYSYMBOL_struct_elem = 126,              /* struct_elem  */
  YYSYMBOL_struct_list = 127,              /* struct_list  */
  YYSYMBOL_union = 128,                    /* union  */
  YYSYMBOL_generic = 129,                  /* generic  */
  YYSYMBOL_generic_list = 130,             /* generic_list  */
  YYSYMBOL_struct = 131,                   /* struct  */
  YYSYMBOL_template_elem = 132,            /* template_elem  */
  YYSYMBOL_template_list = 133,            /* template_list  */
  YYSYMBOL_type_list = 134,                /* type_list  */
  YYSYMBOL_type_alias = 135,               /* type_alias  */
  YYSYMBOL_type_template = 136,            /* type_template  */
  YYSYMBOL_enum_val = 137,                 /* enum_val  */
  YYSYMBOL_enum_list = 138,                /* enum_list  */
  YYSYMBOL_enum = 139,                     /* enum  */
  YYSYMBOL_top_if = 140,                   /* top_if  */
  YYSYMBOL_top = 141,                      /* top  */
  YYSYMBOL_unit = 142,                     /* unit  */
  YYSYMBOL_input = 143                     /* input  */
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
#define YYFINAL  57
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1987

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  216
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  434

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


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
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   148,   148,   154,   155,   158,   161,   164,   165,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   192,   195,   196,   197,   198,   199,   200,   203,   204,
     205,   206,   207,   210,   211,   212,   215,   216,   219,   221,
     222,   223,   224,   228,   229,   232,   236,   237,   238,   239,
     240,   241,   242,   243,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   261,   264,   270,   272,
     273,   274,   275,   276,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   311,   312,   315,   316,   319,   320,   323,   327,
     334,   340,   341,   344,   345,   351,   352,   355,   358,   359,
     360,   361,   364,   365,   369,   370,   373,   374,   375,   378,
     381,   384,   385,   388,   391,   398,   402,   407,   415,   417,
     421,   424,   426,   428,   430,   434,   435,   442,   443,   447,
     450,   454,   458,   462,   467,   471,   472,   475,   476,   480,
     486,   490,   496,   499,   502,   503,   506,   509,   514,   515,
     516,   519,   522,   529,   530,   531,   532,   535,   536,   539,
     540,   543,   548,   551,   557,   558,   561,   562,   563,   566,
     567,   573,   577,   581,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   622,   623,   626,   627
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
  "\",\"", "\"pub\"", "\"struct\"", "\"union\"", "\"type\"", "\"import\"",
  "\"defer\"", "\"goto\"", "\"embed\"", "\"if\"", "\"else\"", "\"break\"",
  "\"continue\"", "\"switch\"", "\"case\"", "\"for\"", "\"while\"",
  "\"do\"", "\"mut\"", "\"return\"", "\"const\"", "\"extern\"", "\"enum\"",
  "\"define\"", "\"(\"", "\")\"", "\"{\"", "\"}\"", "\"[\"", "\"]\"",
  "\"as\"", "\".\"", "\"=>\"", "$accept", "id", "var", "embed", "import",
  "assign", "binary_op", "unary_op", "arg", "arg_list", "param_decl",
  "decl_list", "call", "defer", "expr", "while", "do_while", "goto",
  "statement", "statement_list", "body", "macro_list", "macro",
  "expr_list", "struct_init", "struct_inits", "struct_construct",
  "init_expr", "cond", "expr_if", "if", "for", "case", "case_list",
  "switch", "const_for", "const_if", "const", "func_sign", "variadic_sign",
  "type", "var_decl", "var_init", "proc", "lambda", "struct_elem",
  "struct_list", "union", "generic", "generic_list", "struct",
  "template_elem", "template_list", "type_list", "type_alias",
  "type_template", "enum_val", "enum_list", "enum", "top_if", "top",
  "unit", "input", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-255)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-217)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     210,  -255,  -255,  -255,   341,    44,    44,    24,     1,    44,
      44,    44,   411,    46,    54,  -255,    64,  -255,  -255,  -255,
      67,  -255,  -255,    95,  -255,    84,    76,    77,  -255,  -255,
    -255,    81,  -255,  -255,    -7,   172,  -255,  1110,  -255,    27,
      23,    36,    42,  1110,   181,   296,   100,   494,    47,  -255,
      59,  -255,  -255,  -255,   976,  -255,  -255,  -255,  -255,  -255,
    -255,    44,    44,    25,  -255,  -255,  -255,  -255,  1110,    44,
    1110,  1110,  1110,  1110,  1110,  -255,    66,    68,  1110,    44,
     305,    17,  -255,  -255,  -255,  -255,  -255,  -255,  1203,  -255,
     100,  -255,   305,    44,    15,  -255,  -255,    57,   976,  -255,
     976,  -255,  -255,   305,   615,    93,    51,  -255,    94,   305,
    1267,   305,   746,  -255,  1140,   573,  1908,    71,  -255,  -255,
     305,    98,    80,   527,  -255,   144,    82,    44,  -255,   332,
     145,  -255,    30,    83,    57,  -255,    57,    57,   207,  1492,
      57,  1110,   154,   522,  1331,    64,    89,   124,   113,  -255,
      44,   898,  1054,  1110,  1110,  1110,  1110,  1110,  1110,  1110,
    1110,  1110,  1110,  1110,  1110,  1110,  1110,  1110,  1110,  1110,
    1110,  1110,  1110,  1110,  1110,  1110,  1110,  1110,  1110,  1110,
    1110,  1110,   221,   305,    44,   -21,   103,   183,   157,   117,
      59,    29,  -255,  -255,   120,   305,   305,   305,    44,  -255,
     161,   305,  -255,   305,   159,   129,  -255,  -255,    44,  1140,
     199,   202,  1110,  1008,  1110,    59,   930,   -16,  -255,   320,
     204,   205,  1395,  -255,  -255,   208,   670,   153,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,   222,  -255,  -255,  1084,  1908,
      59,    44,   195,   169,  -255,   305,  -255,    44,   182,    44,
    -255,    -1,  -255,   255,  -255,  -255,  -255,  1459,   194,  -255,
    -255,    44,    27,  -255,  1110,  -255,   539,   220,   203,  -255,
    -255,  1908,  -255,    -4,    -4,    -4,   207,   207,  1236,  1436,
    1492,  1428,  1364,  1300,   836,   836,   836,   836,   760,   760,
     235,   235,  1908,  1908,  1908,  1908,  1908,  1908,  1908,  1908,
    1908,  1908,   197,  -255,  -255,    44,  1110,    44,  -255,  -255,
      44,    59,  -255,  -255,   214,  -255,   209,  -255,  -255,   305,
    -255,  -255,    59,  -255,  -255,  1523,   265,  1587,   219,  -255,
     277,  1110,    44,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,   223,   237,   289,   573,  -255,  -255,  -255,
      44,  -255,    44,    44,  -255,  -255,  -255,  -255,    59,  -255,
    1008,  -255,   240,   224,  1908,  -255,   227,  -255,   305,  -255,
    -255,   243,   244,  1110,  -255,  1110,  -255,  1587,   297,  -255,
     -35,   976,  -255,   242,   247,   246,  -255,  -255,   -31,  -255,
      59,   249,   -20,  1110,   244,   248,  1652,  1716,   257,  1110,
    -255,  -255,  -255,  -255,   251,  -255,   221,  -255,  -255,  -255,
    -255,  -255,  1780,  -255,  -255,  1110,  -255,   -17,  1844,    59,
      44,   253,   822,  1587,  -255,  -255,  1110,  -255,   254,  -255,
    -255,  -255,  -255,  -255
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   212,     2,   194,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   198,     3,     4,   196,   197,
       0,   202,   195,     0,   215,     0,     0,     0,   206,   205,
     204,     0,   209,   203,     0,     0,     6,     0,   199,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,   145,
       0,   156,   210,   200,     0,   201,   214,     1,   211,   207,
     208,     0,     0,     0,   181,    61,    62,    63,     0,     0,
       0,     0,     0,     0,     0,    60,     0,     0,     0,     0,
       0,    56,    74,    65,    68,    69,    66,    67,     0,    75,
       0,   161,     0,     0,     0,   148,   150,   153,     0,   154,
       0,   155,   144,     0,   147,    52,     0,    48,    51,     0,
       0,     0,     0,   160,     0,     0,   118,   120,   157,   119,
       0,   170,     0,     0,   163,     0,     0,     0,   183,     0,
       0,   176,   178,     0,    41,    59,    39,    71,    38,    40,
      42,     0,     0,    56,     0,     0,     0,   107,     0,    73,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   184,   188,     0,
       0,     0,   158,   159,     0,     0,     0,     0,     0,   141,
       0,     0,   151,     0,   180,     0,   101,   100,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,    56,
       0,     0,     0,    91,    92,     0,     0,     0,    99,    94,
      86,    89,    93,    90,    95,     0,    97,    98,     0,   122,
       0,     0,   116,     0,   113,     0,   168,     0,     0,   165,
     171,     0,   173,     0,   175,   177,   182,     0,     0,    64,
      70,     0,     0,    58,     0,    54,    56,    47,     0,    45,
      44,     7,     8,    11,    12,    13,    10,     9,    15,    14,
      16,    18,    17,    19,    32,    33,    34,    35,    36,    37,
      20,    21,    22,    23,    24,    25,    26,    29,    27,    28,
      30,    31,     0,    72,    57,     0,     0,   187,   190,   110,
       0,     0,   143,    50,     0,   142,     0,    49,   152,     0,
     149,    78,     0,    82,    83,     0,     0,     0,     0,    81,
       0,     0,     0,   139,   138,    88,    85,    84,    79,    87,
     102,   104,    96,     0,     0,     0,     0,   117,   121,   169,
       0,   164,     0,     0,   174,    55,     5,   106,     0,    43,
       0,    53,   191,     0,   185,   186,     0,   108,     0,   140,
     179,   126,     0,     0,    76,     0,    80,     0,     0,   123,
       0,     0,   115,     0,     0,     0,   162,    46,     0,   189,
       0,     0,     0,     0,   132,     0,     0,     0,   135,     0,
     124,   125,   114,   172,     0,   166,     0,   193,   109,   146,
     127,   128,     0,   131,   133,     0,    77,     0,   112,     0,
       0,     0,     0,     0,   136,   137,     0,   134,     0,   192,
     130,   129,   111,   167
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -255,     0,     3,  -255,     4,  -255,  -255,  -255,   121,   -23,
    -255,   -62,  -255,  -255,   293,  -255,  -255,  -255,  -255,  -223,
     -34,   -92,     9,   -85,  -255,    -2,   196,   -30,   140,  -219,
     -38,  -255,  -255,   -39,  -255,  -255,   -60,  -255,   -12,  -255,
     440,    20,   -63,   355,  -255,  -255,  -216,  -255,  -255,  -222,
      10,  -255,   230,    50,    13,    14,  -255,  -254,    16,   -14,
    -255,   -22,  -255
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    81,    13,    82,    14,    83,    84,    85,   267,   268,
     105,   106,    86,    87,   116,   223,   224,   225,   226,   227,
     228,   148,    15,   419,   242,   243,   117,   269,   240,   119,
     230,   231,   394,   395,   232,   333,   334,   233,    49,    50,
      51,    16,    17,    18,    89,   125,   126,   131,   121,   122,
      19,   132,   133,   205,    20,    21,   188,   189,    22,    38,
      23,    24,    25
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      12,    56,   191,   340,    12,    34,    35,    26,    27,    39,
      40,    41,    48,    28,    30,   146,   113,    31,    32,   343,
      33,     2,   114,    12,   118,   349,    37,    91,   185,    36,
      95,     2,   150,   351,    92,    48,     2,   209,   310,   112,
     331,   331,    48,   406,    48,    48,   104,   332,     2,    42,
       2,   363,   199,   365,   112,    43,    52,   112,    37,   200,
     198,   120,   123,   129,    53,    61,   108,    62,   192,   135,
     193,   352,    54,   353,   183,   184,   127,    55,   143,   147,
      48,   127,   124,   130,    57,   244,    58,    59,   190,   151,
     104,    60,    48,   187,   147,  -213,     1,    93,   145,    90,
     128,     2,   311,    48,    48,     3,     2,    42,    94,    48,
     108,    48,   219,    43,    90,   220,   221,   253,    47,   111,
      48,   229,   234,    48,   199,   235,   236,   251,   237,    48,
     384,   200,   129,   112,   383,   313,   184,   385,   141,   317,
     142,   197,   201,    48,     4,     5,   247,     6,     7,   245,
     263,   266,   130,   248,   249,   254,   309,   250,   256,   258,
     302,   401,   260,     8,     9,    10,    11,     2,    42,   357,
    -213,   270,   261,   102,    43,   146,    47,   305,     2,    42,
     103,   328,    12,    48,   304,    43,   330,     2,    42,    98,
     262,   306,   308,   312,    43,    48,    48,   104,   314,   430,
      48,   104,   320,    48,   428,   307,   344,   319,   321,   323,
    -216,     1,   324,   266,   336,   337,     2,   108,   339,    48,
       3,   108,     1,   153,   154,   155,   219,     2,   341,   220,
     221,     3,   342,   270,   315,   229,   234,    47,   143,   235,
     236,   345,   237,   346,   347,    48,    63,   120,    47,   123,
     358,   153,   154,   155,   156,   157,   350,    47,   145,     4,
       5,   147,     6,     7,   266,   354,    48,   356,   360,   124,
       4,     5,   362,     6,     7,   373,   361,   367,     8,     9,
      10,    11,   369,   375,   359,   183,   184,   376,   371,     8,
       9,    10,    11,   374,   368,   380,   379,   381,   388,   389,
     390,   392,     2,    42,   100,   187,   393,   187,   399,    43,
     366,     2,    42,   183,   184,   417,   244,   403,    43,    48,
     404,   405,   409,   414,   386,   420,     2,    42,   429,   433,
      88,   335,   378,    43,   326,   150,    97,   387,     2,    42,
     110,   432,   252,   398,   382,    43,   400,     2,   272,   322,
     123,   402,   120,   123,   411,   413,   408,   425,   410,    29,
     266,   134,   255,   136,   137,   138,   139,   140,    48,   370,
     124,   144,    47,   124,   407,     0,     0,     0,     0,     0,
     270,    47,     0,   424,   421,   427,    44,     0,    45,   431,
       0,     5,   151,     6,     7,     0,    47,     0,   195,     0,
     196,     0,     0,     0,    90,   222,    12,   239,    47,     0,
       9,    10,    11,     0,     0,     0,     0,     2,    42,     0,
     123,     0,   219,     0,    43,   220,   221,     0,     0,     0,
       0,   229,   234,     0,   257,   235,   236,     0,   237,     0,
     124,     0,     0,     0,     0,   271,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,    64,     0,    44,     0,    45,
       0,     0,    96,    46,    99,   101,   107,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
       2,    68,   239,    69,     0,   325,    70,   327,    71,     0,
       0,     0,     0,    72,     0,     0,     0,    73,     0,   222,
     149,    74,     0,     0,     0,     0,     0,     0,     2,    42,
     107,   144,   186,     2,    42,    43,     0,   150,     0,     0,
      43,    75,     0,   194,     0,     2,    42,     0,    76,   202,
      77,   204,    43,     0,   150,     0,     0,   139,     0,     0,
     246,     0,     0,     0,     0,     0,    78,     0,     0,     0,
      79,   109,    80,     0,     0,     0,    65,    66,    67,     2,
      68,     0,    69,     0,     0,    70,     0,    71,    44,     0,
      45,     0,    72,   195,   151,   196,    73,     0,    47,   364,
      74,     0,     0,    47,     0,   195,     0,   196,     0,     0,
       0,   151,     0,     0,     0,    47,     0,     0,     0,     0,
      75,     2,    42,   303,   377,     0,     0,    76,    43,    77,
     114,     0,     0,     0,     0,    99,   101,   107,     0,     0,
     316,   107,     0,   318,     0,    78,     0,   115,     0,    79,
       0,    80,   241,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   396,     0,   397,     0,
       0,   206,     0,    65,    66,    67,     2,    68,     0,    69,
     207,   195,    70,   196,    71,   348,   412,   111,     0,    72,
       0,    47,   418,    73,     0,     0,     0,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   423,     0,
       0,     0,     0,     0,     0,   222,     0,    75,     0,   418,
       5,     0,     6,     7,    76,   208,    77,   209,     0,   210,
     211,   212,  -103,   213,   214,   215,     0,   216,   217,     0,
      10,    11,    78,     0,   112,  -103,    79,   206,    80,    65,
      66,    67,     2,    68,     0,    69,   207,     0,    70,   204,
      71,     0,     0,     0,     0,    72,     0,     0,     0,    73,
       0,     0,     0,    74,     0,     0,   153,   154,   155,   156,
     157,     0,   159,   160,   161,     0,     0,     0,   164,   165,
     166,   167,     0,    75,   170,   171,     5,     0,     6,     7,
      76,   208,    77,   209,     0,   210,   211,   212,   391,   213,
     214,   215,     0,   216,   217,     0,    10,    11,    78,     0,
     112,   218,    79,   206,    80,    65,    66,    67,     2,    68,
       0,    69,   207,     0,    70,     0,    71,     0,   183,   184,
       0,    72,     0,     0,     0,    73,     0,     0,     0,    74,
       0,     0,   153,   154,   155,   156,   157,     0,   159,   160,
     161,     0,     0,     0,     0,     0,     0,     0,     0,    75,
     170,   171,     5,     0,     6,     7,    76,   208,    77,   209,
       0,   210,   211,   212,     0,   213,   214,   215,     0,   216,
     217,     0,    10,    11,    78,     0,   112,     0,    79,     0,
      80,    65,    66,    67,     2,    68,     0,    69,     0,     0,
      70,     0,    71,     0,   183,   184,     0,    72,     0,     0,
       0,   264,     0,     0,     0,    74,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,     2,    68,     0,    69,
     329,     0,    70,     0,    71,    75,     0,     0,     0,    72,
       0,     0,    76,    73,    77,   114,     0,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      78,   265,   115,     0,    79,     0,    80,    75,     0,    65,
      66,    67,     2,    68,    76,    69,    77,   114,    70,     0,
      71,     0,     0,     0,     0,    72,     0,     0,     0,    73,
       0,     0,    78,    74,   115,     0,    79,     0,    80,     0,
       0,    65,    66,    67,     2,    68,     0,    69,     0,     0,
      70,     0,    71,    75,     0,     0,     0,    72,     0,     0,
      76,   264,    77,   114,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    78,     0,
     115,     0,    79,     0,    80,    75,     0,    65,    66,    67,
       2,    68,    76,    69,    77,   114,    70,     0,    71,     0,
       0,     0,     0,    72,     0,     0,     0,    73,     0,     0,
      78,    74,   115,     0,    79,     0,    80,    65,    66,    67,
       2,    68,     0,    69,     0,     0,    70,     0,    71,     0,
       0,    75,     0,    72,     0,     0,     0,    73,    76,     0,
      77,    74,     0,    65,    66,    67,     2,    68,     0,    69,
       0,     0,    70,     0,    71,     0,    78,     0,   115,    72,
      79,    75,    80,    73,     0,     0,     0,    74,    76,     0,
      77,   114,     0,    65,    66,    67,     2,    68,     0,    69,
       0,     0,    70,     0,    71,     0,    78,    75,     0,    72,
      79,     0,    80,    73,    76,     0,    77,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    78,     0,     0,     0,    79,    75,    80,     0,
       0,     0,     0,     0,    76,     0,    77,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   152,   238,     0,     0,     0,    79,     0,    80,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
       0,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,     0,   178,   179,   180,   181,
       0,     0,   153,   154,   155,   156,   157,     0,   159,   160,
     161,   162,   163,     0,   164,   165,   166,   167,   168,   169,
     170,   171,     0,     0,     0,   152,     0,   182,     0,     0,
       0,   183,   184,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,     0,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,     0,
     178,   179,   180,   181,   183,   184,   153,   154,   155,   156,
     157,     0,   159,   160,   161,   162,     0,     0,   164,   165,
     166,   167,   168,   169,   170,   171,     0,     0,     0,   152,
       0,     0,     0,     0,   203,   183,   184,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,     0,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,     0,   178,   179,   180,   181,   183,   184,
     153,   154,   155,   156,   157,     0,   159,   160,   161,     0,
       0,     0,   164,   165,   166,   167,   168,   169,   170,   171,
       0,     0,     0,   152,   259,   338,     0,     0,     0,   183,
     184,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,     0,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,     0,   178,   179,
     180,   181,   183,   184,   153,   154,   155,   156,   157,     0,
     159,   160,   153,   154,   155,   156,   157,     0,     0,   160,
       0,     0,   170,   171,     0,     0,     0,   152,     0,     0,
     170,   171,     0,   183,   184,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,     0,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,     0,   178,   179,   180,   181,   183,   184,   153,   154,
     155,   156,   157,     0,   183,   184,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   170,   171,     0,     0,
       0,   152,   355,     0,     0,     0,     0,   183,   184,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
       0,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,     0,   178,   179,   180,   181,
     183,   184,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   152,     0,   372,     0,     0,
       0,   183,   184,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,     0,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,     0,
     178,   179,   180,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     152,   112,   415,     0,     0,   183,   184,     0,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,     0,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,     0,   178,   179,   180,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   152,     0,   416,     0,     0,     0,
     183,   184,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,     0,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,     0,   178,
     179,   180,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   152,     0,
       0,   422,     0,     0,   183,   184,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,     0,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,     0,   178,   179,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   152,     0,     0,     0,     0,     0,   183,   184,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,     0,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,     0,   178,   179,   180,
     181,     0,   426,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   152,     0,     0,     0,
       0,     0,   183,   184,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,     0,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
       0,   178,   179,   180,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   183,   184
};

static const yytype_int16 yycheck[] =
{
       0,    23,    94,   226,     4,     5,     6,     4,     4,     9,
      10,    11,    12,     4,     4,    78,    50,     4,     4,   238,
       4,     6,    57,    23,    54,   247,    57,    39,    90,     5,
      42,     6,    15,   249,    11,    35,     6,    57,     9,    74,
      57,    57,    42,    74,    44,    45,    46,    63,     6,     7,
       6,   305,    73,   307,    74,    13,    10,    74,    57,    80,
       9,    61,    62,    63,    10,    72,    46,    74,    98,    69,
     100,    72,     8,    74,    78,    79,    51,    10,    78,    79,
      80,    51,    62,    63,     0,   115,    10,    10,    73,    72,
      90,    10,    92,    93,    94,     0,     1,    74,    78,    72,
      75,     6,    73,   103,   104,    10,     6,     7,    72,   109,
      90,   111,   112,    13,    72,   112,   112,   129,    76,    72,
     120,   112,   112,   123,    73,   112,   112,   127,   112,   129,
     352,    80,   132,    74,   350,   197,    79,   353,    72,   201,
      72,    48,    48,   143,    49,    50,    48,    52,    53,    78,
     150,   151,   132,    73,    10,    10,   190,    75,    75,     5,
     182,   380,    73,    68,    69,    70,    71,     6,     7,   261,
      75,   151,    48,    73,    13,   238,    76,    74,     6,     7,
      80,   215,   182,   183,   184,    13,   216,     6,     7,     8,
      77,     8,    75,    73,    13,   195,   196,   197,   198,   422,
     200,   201,    73,   203,   420,    48,   240,    48,   208,    10,
       0,     1,    10,   213,    10,    10,     6,   197,    10,   219,
      10,   201,     1,    16,    17,    18,   226,     6,    75,   226,
     226,    10,    10,   213,    73,   226,   226,    76,   238,   226,
     226,   241,   226,    48,    75,   245,    74,   247,    76,   249,
     262,    16,    17,    18,    19,    20,    74,    76,   238,    49,
      50,   261,    52,    53,   264,    10,   266,    73,    48,   249,
      49,    50,    75,    52,    53,    10,    73,   311,    68,    69,
      70,    71,    73,    64,   264,    78,    79,    10,   322,    68,
      69,    70,    71,   327,    80,    58,    73,     8,    58,    75,
      73,    58,     6,     7,     8,   305,    62,   307,    11,    13,
     310,     6,     7,    78,    79,    58,   346,    75,    13,   319,
      73,    75,    73,    75,   358,    74,     6,     7,    75,    75,
      37,    11,   332,    13,   213,    15,    43,   360,     6,     7,
      47,   426,    10,   377,   346,    13,   380,     6,   152,   209,
     350,   381,   352,   353,   392,   394,   390,   417,   392,     4,
     360,    68,   132,    70,    71,    72,    73,    74,   368,   319,
     350,    78,    76,   353,   388,    -1,    -1,    -1,    -1,    -1,
     360,    76,    -1,   417,   406,   419,    66,    -1,    68,   423,
      -1,    50,    72,    52,    53,    -1,    76,    -1,    66,    -1,
      68,    -1,    -1,    -1,    72,   112,   406,   114,    76,    -1,
      69,    70,    71,    -1,    -1,    -1,    -1,     6,     7,    -1,
     420,    -1,   422,    -1,    13,   422,   422,    -1,    -1,    -1,
      -1,   422,   422,    -1,   141,   422,   422,    -1,   422,    -1,
     420,    -1,    -1,    -1,    -1,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,    35,    -1,    66,    -1,    68,
      -1,    -1,    42,    72,    44,    45,    46,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,   209,     9,    -1,   212,    12,   214,    14,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    23,    -1,   226,
      80,    27,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
      90,   238,    92,     6,     7,    13,    -1,    15,    -1,    -1,
      13,    47,    -1,   103,    -1,     6,     7,    -1,    54,   109,
      56,   111,    13,    -1,    15,    -1,    -1,   264,    -1,    -1,
     120,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,
      76,    77,    78,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    -1,    -1,    12,    -1,    14,    66,    -1,
      68,    -1,    19,    66,    72,    68,    23,    -1,    76,   306,
      27,    -1,    -1,    76,    -1,    66,    -1,    68,    -1,    -1,
      -1,    72,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,
      47,     6,     7,   183,   331,    -1,    -1,    54,    13,    56,
      57,    -1,    -1,    -1,    -1,   195,   196,   197,    -1,    -1,
     200,   201,    -1,   203,    -1,    72,    -1,    74,    -1,    76,
      -1,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   373,    -1,   375,    -1,
      -1,     1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    66,    12,    68,    14,   245,   393,    72,    -1,    19,
      -1,    76,   399,    23,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   415,    -1,
      -1,    -1,    -1,    -1,    -1,   422,    -1,    47,    -1,   426,
      50,    -1,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    63,    64,    65,    -1,    67,    68,    -1,
      70,    71,    72,    -1,    74,    75,    76,     1,    78,     3,
       4,     5,     6,     7,    -1,     9,    10,    -1,    12,   319,
      14,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    27,    -1,    -1,    16,    17,    18,    19,
      20,    -1,    22,    23,    24,    -1,    -1,    -1,    28,    29,
      30,    31,    -1,    47,    34,    35,    50,    -1,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,   368,    63,
      64,    65,    -1,    67,    68,    -1,    70,    71,    72,    -1,
      74,    75,    76,     1,    78,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    12,    -1,    14,    -1,    78,    79,
      -1,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    27,
      -1,    -1,    16,    17,    18,    19,    20,    -1,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      34,    35,    50,    -1,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    -1,    63,    64,    65,    -1,    67,
      68,    -1,    70,    71,    72,    -1,    74,    -1,    76,    -1,
      78,     3,     4,     5,     6,     7,    -1,     9,    -1,    -1,
      12,    -1,    14,    -1,    78,    79,    -1,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    -1,    12,    -1,    14,    47,    -1,    -1,    -1,    19,
      -1,    -1,    54,    23,    56,    57,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    -1,    76,    -1,    78,    47,    -1,     3,
       4,     5,     6,     7,    54,     9,    56,    57,    12,    -1,
      14,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    23,
      -1,    -1,    72,    27,    74,    -1,    76,    -1,    78,    -1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    -1,    -1,
      12,    -1,    14,    47,    -1,    -1,    -1,    19,    -1,    -1,
      54,    23,    56,    57,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,
      74,    -1,    76,    -1,    78,    47,    -1,     3,     4,     5,
       6,     7,    54,     9,    56,    57,    12,    -1,    14,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,
      72,    27,    74,    -1,    76,    -1,    78,     3,     4,     5,
       6,     7,    -1,     9,    -1,    -1,    12,    -1,    14,    -1,
      -1,    47,    -1,    19,    -1,    -1,    -1,    23,    54,    -1,
      56,    27,    -1,     3,     4,     5,     6,     7,    -1,     9,
      -1,    -1,    12,    -1,    14,    -1,    72,    -1,    74,    19,
      76,    47,    78,    23,    -1,    -1,    -1,    27,    54,    -1,
      56,    57,    -1,     3,     4,     5,     6,     7,    -1,     9,
      -1,    -1,    12,    -1,    14,    -1,    72,    47,    -1,    19,
      76,    -1,    78,    23,    54,    -1,    56,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    -1,    76,    47,    78,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     8,    72,    -1,    -1,    -1,    76,    -1,    78,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    43,    44,    45,    46,
      -1,    -1,    16,    17,    18,    19,    20,    -1,    22,    23,
      24,    25,    26,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,     8,    -1,    74,    -1,    -1,
      -1,    78,    79,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      43,    44,    45,    46,    78,    79,    16,    17,    18,    19,
      20,    -1,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    77,    78,    79,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    43,    44,    45,    46,    78,    79,
      16,    17,    18,    19,    20,    -1,    22,    23,    24,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,     8,    73,    10,    -1,    -1,    -1,    78,
      79,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    43,    44,
      45,    46,    78,    79,    16,    17,    18,    19,    20,    -1,
      22,    23,    16,    17,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    34,    35,    -1,    -1,    -1,     8,    -1,    -1,
      34,    35,    -1,    78,    79,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    43,    44,    45,    46,    78,    79,    16,    17,
      18,    19,    20,    -1,    78,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,    -1,
      -1,     8,    73,    -1,    -1,    -1,    -1,    78,    79,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    43,    44,    45,    46,
      78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    74,    -1,    -1,
      -1,    78,    79,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       8,    74,    10,    -1,    -1,    78,    79,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    10,    -1,    -1,    -1,
      78,    79,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,
      -1,    11,    -1,    -1,    78,    79,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,    78,    79,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    -1,    78,    79,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    10,    49,    50,    52,    53,    68,    69,
      70,    71,    82,    83,    85,   103,   122,   123,   124,   131,
     135,   136,   139,   141,   142,   143,    83,    85,   103,   124,
     131,   135,   136,   139,    82,    82,     5,    57,   140,    82,
      82,    82,     7,    13,    66,    68,    72,    76,    82,   119,
     120,   121,    10,    10,     8,    10,   142,     0,    10,    10,
      10,    72,    74,    74,   121,     3,     4,     5,     7,     9,
      12,    14,    19,    23,    27,    47,    54,    56,    72,    76,
      78,    82,    84,    86,    87,    88,    93,    94,    95,   125,
      72,   119,    11,    74,    72,   119,   121,    95,     8,   121,
       8,   121,    73,    80,    82,    91,    92,   121,   122,    77,
      95,    72,    74,   101,    57,    74,    95,   107,   108,   110,
      82,   129,   130,    82,   122,   126,   127,    51,    75,    82,
     122,   128,   132,   133,    95,    82,    95,    95,    95,    95,
      95,    72,    72,    82,    95,   122,   123,    82,   102,   121,
      15,    72,     8,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    43,    44,
      45,    46,    74,    78,    79,    92,   121,    82,   137,   138,
      73,   102,   108,   108,   121,    66,    68,    48,     9,    73,
      80,    48,   121,    77,   121,   134,     1,    10,    55,    57,
      59,    60,    61,    63,    64,    65,    67,    68,    75,    82,
      83,    85,    95,    96,    97,    98,    99,   100,   101,   103,
     111,   112,   115,   118,   131,   135,   136,   139,    72,    95,
     109,    79,   105,   106,   108,    78,   121,    48,    73,    10,
      75,    82,    10,   119,    10,   133,    75,    95,     5,    73,
      73,    48,    77,    82,    23,    73,    82,    89,    90,   108,
     122,    95,   107,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,   142,   121,    82,    74,     8,    48,    75,   101,
       9,    73,    73,    92,    82,    73,   121,    92,   121,    48,
      73,    82,   109,    10,    10,    95,    89,    95,   101,    10,
     108,    57,    63,   116,   117,    11,    10,    10,    10,    10,
     100,    75,    10,   110,   101,    82,    48,    75,   121,   130,
      74,   127,    72,    74,    10,    73,    73,   102,   119,   122,
      48,    73,    75,   138,    95,   138,    82,   101,    80,    73,
     134,   101,    74,    10,   101,    64,    10,    95,    82,    73,
      58,     8,   106,   127,   130,   127,   101,    90,    58,    75,
      73,   121,    58,    62,   113,   114,    95,    95,   101,    11,
     101,   110,   108,    75,    73,    75,    74,   140,   101,    73,
     101,   111,    95,   114,    75,    10,    10,    58,    95,   104,
      74,   142,    11,    95,   101,   117,    48,   101,   127,    75,
     100,   101,   104,    75
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    85,    86,    86,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    88,    89,    89,    89,    90,    90,    91,    92,
      92,    92,    92,    93,    93,    94,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    96,    97,    98,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   101,   101,   102,   102,   103,   103,
     103,   104,   104,   105,   105,   106,   106,   107,   108,   108,
     108,   108,   109,   109,   110,   110,   111,   111,   111,   112,
     113,   114,   114,   115,   116,   117,   117,   117,   118,   118,
     119,   119,   119,   119,   119,   120,   120,   121,   121,   121,
     121,   121,   121,   121,   122,   122,   122,   123,   123,   123,
     124,   124,   125,   126,   127,   127,   128,   128,   129,   130,
     130,   131,   131,   132,   132,   132,   132,   133,   133,   134,
     134,   135,   136,   136,   137,   137,   138,   138,   138,   139,
     139,   140,   140,   140,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   142,   142,   143,   143
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     4,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     2,     1,     1,     3,     1,     1,     3,
       3,     1,     1,     4,     3,     4,     1,     3,     3,     2,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       3,     2,     3,     2,     1,     1,     3,     5,     2,     2,
       3,     2,     2,     2,     2,     2,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     2,     1,     3,     2,     3,     1,     6,     8,
       5,     3,     1,     1,     4,     3,     1,     3,     1,     1,
       1,     3,     1,     3,     5,     5,     3,     5,     5,     7,
       4,     2,     1,     5,     5,     3,     5,     5,     2,     2,
       5,     3,     4,     4,     2,     1,     7,     1,     2,     4,
       2,     3,     4,     2,     3,     3,     2,     3,     4,     4,
       3,     3,     5,     1,     3,     2,     5,     8,     2,     3,
       1,     5,     8,     2,     3,     2,     1,     2,     1,     3,
       1,     3,     5,     4,     1,     3,     3,     2,     1,     7,
       5,     5,     9,     7,     1,     1,     1,     1,     1,     2,
       2,     2,     1,     2,     2,     2,     2,     3,     3,     2,
       2,     3,     1,     1,     2,     1,     0
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
#line 143 "src/parser.y"
            {}
#line 1934 "src/gen_parser.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 143 "src/parser.y"
            {}
#line 1940 "src/gen_parser.c"
        break;

    case YYSYMBOL_STRING: /* STRING  */
#line 143 "src/parser.y"
            {}
#line 1946 "src/gen_parser.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 143 "src/parser.y"
            {}
#line 1952 "src/gen_parser.c"
        break;

    case YYSYMBOL_id: /* id  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1958 "src/gen_parser.c"
        break;

    case YYSYMBOL_var: /* var  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1964 "src/gen_parser.c"
        break;

    case YYSYMBOL_embed: /* embed  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1970 "src/gen_parser.c"
        break;

    case YYSYMBOL_import: /* import  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1976 "src/gen_parser.c"
        break;

    case YYSYMBOL_assign: /* assign  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1982 "src/gen_parser.c"
        break;

    case YYSYMBOL_binary_op: /* binary_op  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1988 "src/gen_parser.c"
        break;

    case YYSYMBOL_unary_op: /* unary_op  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1994 "src/gen_parser.c"
        break;

    case YYSYMBOL_arg: /* arg  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2000 "src/gen_parser.c"
        break;

    case YYSYMBOL_arg_list: /* arg_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2006 "src/gen_parser.c"
        break;

    case YYSYMBOL_param_decl: /* param_decl  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2012 "src/gen_parser.c"
        break;

    case YYSYMBOL_decl_list: /* decl_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2018 "src/gen_parser.c"
        break;

    case YYSYMBOL_call: /* call  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2024 "src/gen_parser.c"
        break;

    case YYSYMBOL_defer: /* defer  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2030 "src/gen_parser.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2036 "src/gen_parser.c"
        break;

    case YYSYMBOL_while: /* while  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2042 "src/gen_parser.c"
        break;

    case YYSYMBOL_do_while: /* do_while  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2048 "src/gen_parser.c"
        break;

    case YYSYMBOL_goto: /* goto  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2054 "src/gen_parser.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2060 "src/gen_parser.c"
        break;

    case YYSYMBOL_statement_list: /* statement_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2066 "src/gen_parser.c"
        break;

    case YYSYMBOL_body: /* body  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2072 "src/gen_parser.c"
        break;

    case YYSYMBOL_macro_list: /* macro_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2078 "src/gen_parser.c"
        break;

    case YYSYMBOL_macro: /* macro  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2084 "src/gen_parser.c"
        break;

    case YYSYMBOL_expr_list: /* expr_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2090 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct_init: /* struct_init  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2096 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct_inits: /* struct_inits  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2102 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct_construct: /* struct_construct  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2108 "src/gen_parser.c"
        break;

    case YYSYMBOL_init_expr: /* init_expr  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2114 "src/gen_parser.c"
        break;

    case YYSYMBOL_cond: /* cond  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2120 "src/gen_parser.c"
        break;

    case YYSYMBOL_expr_if: /* expr_if  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2126 "src/gen_parser.c"
        break;

    case YYSYMBOL_if: /* if  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2132 "src/gen_parser.c"
        break;

    case YYSYMBOL_for: /* for  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2138 "src/gen_parser.c"
        break;

    case YYSYMBOL_case: /* case  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2144 "src/gen_parser.c"
        break;

    case YYSYMBOL_case_list: /* case_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2150 "src/gen_parser.c"
        break;

    case YYSYMBOL_switch: /* switch  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2156 "src/gen_parser.c"
        break;

    case YYSYMBOL_const_for: /* const_for  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2162 "src/gen_parser.c"
        break;

    case YYSYMBOL_const_if: /* const_if  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2168 "src/gen_parser.c"
        break;

    case YYSYMBOL_const: /* const  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2174 "src/gen_parser.c"
        break;

    case YYSYMBOL_func_sign: /* func_sign  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2180 "src/gen_parser.c"
        break;

    case YYSYMBOL_variadic_sign: /* variadic_sign  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2186 "src/gen_parser.c"
        break;

    case YYSYMBOL_type: /* type  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2192 "src/gen_parser.c"
        break;

    case YYSYMBOL_var_decl: /* var_decl  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2198 "src/gen_parser.c"
        break;

    case YYSYMBOL_var_init: /* var_init  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2204 "src/gen_parser.c"
        break;

    case YYSYMBOL_proc: /* proc  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2210 "src/gen_parser.c"
        break;

    case YYSYMBOL_lambda: /* lambda  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2216 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct_elem: /* struct_elem  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2222 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct_list: /* struct_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2228 "src/gen_parser.c"
        break;

    case YYSYMBOL_union: /* union  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2234 "src/gen_parser.c"
        break;

    case YYSYMBOL_generic: /* generic  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2240 "src/gen_parser.c"
        break;

    case YYSYMBOL_generic_list: /* generic_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2246 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct: /* struct  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2252 "src/gen_parser.c"
        break;

    case YYSYMBOL_template_elem: /* template_elem  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2258 "src/gen_parser.c"
        break;

    case YYSYMBOL_template_list: /* template_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2264 "src/gen_parser.c"
        break;

    case YYSYMBOL_type_list: /* type_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2270 "src/gen_parser.c"
        break;

    case YYSYMBOL_type_alias: /* type_alias  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2276 "src/gen_parser.c"
        break;

    case YYSYMBOL_type_template: /* type_template  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2282 "src/gen_parser.c"
        break;

    case YYSYMBOL_enum_val: /* enum_val  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2288 "src/gen_parser.c"
        break;

    case YYSYMBOL_enum_list: /* enum_list  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2294 "src/gen_parser.c"
        break;

    case YYSYMBOL_enum: /* enum  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2300 "src/gen_parser.c"
        break;

    case YYSYMBOL_top_if: /* top_if  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2306 "src/gen_parser.c"
        break;

    case YYSYMBOL_top: /* top  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2312 "src/gen_parser.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 144 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2318 "src/gen_parser.c"
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
#line 148 "src/parser.y"
       {
		(yyval.node) = gen_id(strdup((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 2627 "src/gen_parser.c"
    break;

  case 3: /* var: var_decl  */
#line 154 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2633 "src/gen_parser.c"
    break;

  case 4: /* var: var_init  */
#line 155 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2639 "src/gen_parser.c"
    break;

  case 5: /* embed: "embed" "(" STRING ")"  */
#line 158 "src/parser.y"
                              { (yyval.node) = gen_embed(clone_string((yyvsp[-1].str)));  }
#line 2645 "src/gen_parser.c"
    break;

  case 6: /* import: "import" STRING  */
#line 161 "src/parser.y"
                        { (yyval.node) = gen_import(clone_string((yyvsp[0].str)));  }
#line 2651 "src/gen_parser.c"
    break;

  case 7: /* assign: expr "=" expr  */
#line 164 "src/parser.y"
                      { (yyval.node) = gen_assign((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2657 "src/gen_parser.c"
    break;

  case 8: /* assign: expr "=" struct_construct  */
#line 165 "src/parser.y"
                                    { (yyval.node) = gen_assign((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2663 "src/gen_parser.c"
    break;

  case 9: /* binary_op: expr "+" expr  */
#line 168 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2669 "src/gen_parser.c"
    break;

  case 10: /* binary_op: expr "-" expr  */
#line 169 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2675 "src/gen_parser.c"
    break;

  case 11: /* binary_op: expr "*" expr  */
#line 170 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2681 "src/gen_parser.c"
    break;

  case 12: /* binary_op: expr "/" expr  */
#line 171 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2687 "src/gen_parser.c"
    break;

  case 13: /* binary_op: expr "%" expr  */
#line 172 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2693 "src/gen_parser.c"
    break;

  case 14: /* binary_op: expr "^" expr  */
#line 173 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2699 "src/gen_parser.c"
    break;

  case 15: /* binary_op: expr "^^" expr  */
#line 174 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_POW, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2705 "src/gen_parser.c"
    break;

  case 16: /* binary_op: expr "&" expr  */
#line 175 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2711 "src/gen_parser.c"
    break;

  case 17: /* binary_op: expr "&&" expr  */
#line 176 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LAND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2717 "src/gen_parser.c"
    break;

  case 18: /* binary_op: expr "|" expr  */
#line 177 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2723 "src/gen_parser.c"
    break;

  case 19: /* binary_op: expr "||" expr  */
#line 178 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2729 "src/gen_parser.c"
    break;

  case 20: /* binary_op: expr "<<" expr  */
#line 179 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2735 "src/gen_parser.c"
    break;

  case 21: /* binary_op: expr ">>" expr  */
#line 180 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2741 "src/gen_parser.c"
    break;

  case 22: /* binary_op: expr "+=" expr  */
#line 181 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2747 "src/gen_parser.c"
    break;

  case 23: /* binary_op: expr "-=" expr  */
#line 182 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2753 "src/gen_parser.c"
    break;

  case 24: /* binary_op: expr "*=" expr  */
#line 183 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2759 "src/gen_parser.c"
    break;

  case 25: /* binary_op: expr "/=" expr  */
#line 184 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2765 "src/gen_parser.c"
    break;

  case 26: /* binary_op: expr "%=" expr  */
#line 185 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2771 "src/gen_parser.c"
    break;

  case 27: /* binary_op: expr "&=" expr  */
#line 186 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2777 "src/gen_parser.c"
    break;

  case 28: /* binary_op: expr "|=" expr  */
#line 187 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2783 "src/gen_parser.c"
    break;

  case 29: /* binary_op: expr "^=" expr  */
#line 188 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2789 "src/gen_parser.c"
    break;

  case 30: /* binary_op: expr "<<=" expr  */
#line 189 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2797 "src/gen_parser.c"
    break;

  case 31: /* binary_op: expr ">>=" expr  */
#line 192 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2805 "src/gen_parser.c"
    break;

  case 32: /* binary_op: expr "<" expr  */
#line 195 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_LT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2811 "src/gen_parser.c"
    break;

  case 33: /* binary_op: expr ">" expr  */
#line 196 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_GT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2817 "src/gen_parser.c"
    break;

  case 34: /* binary_op: expr "<=" expr  */
#line 197 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2823 "src/gen_parser.c"
    break;

  case 35: /* binary_op: expr ">=" expr  */
#line 198 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_GE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2829 "src/gen_parser.c"
    break;

  case 36: /* binary_op: expr "!=" expr  */
#line 199 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_NE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2835 "src/gen_parser.c"
    break;

  case 37: /* binary_op: expr "==" expr  */
#line 200 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_EQ, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2841 "src/gen_parser.c"
    break;

  case 38: /* unary_op: "-" expr  */
#line 203 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NEG, (yyvsp[0].node));  }
#line 2847 "src/gen_parser.c"
    break;

  case 39: /* unary_op: "!" expr  */
#line 204 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_LNOT, (yyvsp[0].node));  }
#line 2853 "src/gen_parser.c"
    break;

  case 40: /* unary_op: "&" expr  */
#line 205 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 2859 "src/gen_parser.c"
    break;

  case 41: /* unary_op: "'" expr  */
#line 206 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_DEREF, (yyvsp[0].node));  }
#line 2865 "src/gen_parser.c"
    break;

  case 42: /* unary_op: "~" expr  */
#line 207 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NOT, (yyvsp[0].node));  }
#line 2871 "src/gen_parser.c"
    break;

  case 43: /* arg: "&" var_decl  */
#line 210 "src/parser.y"
                  { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 2877 "src/gen_parser.c"
    break;

  case 44: /* arg: var_decl  */
#line 211 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2883 "src/gen_parser.c"
    break;

  case 45: /* arg: init_expr  */
#line 212 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2889 "src/gen_parser.c"
    break;

  case 46: /* arg_list: arg "," arg_list  */
#line 215 "src/parser.y"
                           { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2895 "src/gen_parser.c"
    break;

  case 47: /* arg_list: arg  */
#line 216 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2901 "src/gen_parser.c"
    break;

  case 48: /* param_decl: type  */
#line 219 "src/parser.y"
                 { (yyval.node) = gen_var(NULL, (yyvsp[0].node), NULL);  }
#line 2907 "src/gen_parser.c"
    break;

  case 49: /* decl_list: var_decl "," decl_list  */
#line 221 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2913 "src/gen_parser.c"
    break;

  case 50: /* decl_list: param_decl "," decl_list  */
#line 222 "src/parser.y"
                                   { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2919 "src/gen_parser.c"
    break;

  case 51: /* decl_list: var_decl  */
#line 223 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2925 "src/gen_parser.c"
    break;

  case 52: /* decl_list: param_decl  */
#line 224 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2931 "src/gen_parser.c"
    break;

  case 53: /* call: id "(" arg_list ")"  */
#line 228 "src/parser.y"
                          { (yyval.node) = gen_call((yyvsp[-3].node), (yyvsp[-1].node));  }
#line 2937 "src/gen_parser.c"
    break;

  case 54: /* call: id "(" ")"  */
#line 229 "src/parser.y"
                     { (yyval.node) = gen_call((yyvsp[-2].node), NULL);  }
#line 2943 "src/gen_parser.c"
    break;

  case 55: /* defer: "defer" "(" expr ")"  */
#line 232 "src/parser.y"
                            { (yyval.node) = gen_defer((yyvsp[-1].node));  }
#line 2949 "src/gen_parser.c"
    break;

  case 56: /* expr: id  */
#line 236 "src/parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 2955 "src/gen_parser.c"
    break;

  case 57: /* expr: expr "." id  */
#line 237 "src/parser.y"
                      { (yyval.node) = gen_dot((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2961 "src/gen_parser.c"
    break;

  case 58: /* expr: id "##" id  */
#line 238 "src/parser.y"
                     { (yyval.node) = gen_paste((yyvsp[-2].node), (yyvsp[0].node));  }
#line 2967 "src/gen_parser.c"
    break;

  case 59: /* expr: "..." id  */
#line 239 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2973 "src/gen_parser.c"
    break;

  case 60: /* expr: "@"  */
#line 240 "src/parser.y"
              { (yyval.node) = gen_last();  }
#line 2979 "src/gen_parser.c"
    break;

  case 61: /* expr: INT  */
#line 241 "src/parser.y"
              { (yyval.node) = gen_int((yyvsp[0].integer)); (yyval.node)->loc = to_src_loc(&yylloc); }
#line 2985 "src/gen_parser.c"
    break;

  case 62: /* expr: FLOAT  */
#line 242 "src/parser.y"
                { (yyval.node) = gen_float((yyvsp[0].dbl)); (yyval.node)->loc = to_src_loc(&yylloc);  }
#line 2991 "src/gen_parser.c"
    break;

  case 63: /* expr: STRING  */
#line 243 "src/parser.y"
                 {
		(yyval.node) = gen_string(clone_string((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 3000 "src/gen_parser.c"
    break;

  case 64: /* expr: "(" expr ")"  */
#line 247 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3006 "src/gen_parser.c"
    break;

  case 65: /* expr: assign  */
#line 248 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3012 "src/gen_parser.c"
    break;

  case 66: /* expr: call  */
#line 249 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3018 "src/gen_parser.c"
    break;

  case 67: /* expr: defer  */
#line 250 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3024 "src/gen_parser.c"
    break;

  case 68: /* expr: binary_op  */
#line 251 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3030 "src/gen_parser.c"
    break;

  case 69: /* expr: unary_op  */
#line 252 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3036 "src/gen_parser.c"
    break;

  case 70: /* expr: "(" var_init ")"  */
#line 253 "src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 3042 "src/gen_parser.c"
    break;

  case 71: /* expr: "sizeof" expr  */
#line 254 "src/parser.y"
                        { (yyval.node) = gen_sizeof((yyvsp[0].node)); }
#line 3048 "src/gen_parser.c"
    break;

  case 72: /* expr: expr "as" type  */
#line 255 "src/parser.y"
                         { (yyval.node) = gen_cast((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3054 "src/gen_parser.c"
    break;

  case 73: /* expr: "as" type  */
#line 256 "src/parser.y"
                    { (yyval.node) = gen_as((yyvsp[0].node)); }
#line 3060 "src/gen_parser.c"
    break;

  case 74: /* expr: embed  */
#line 257 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3066 "src/gen_parser.c"
    break;

  case 75: /* expr: lambda  */
#line 258 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3072 "src/gen_parser.c"
    break;

  case 76: /* while: "while" expr body  */
#line 261 "src/parser.y"
                         { (yyval.node) = gen_while((yyvsp[-1].node), (yyvsp[0].node));  }
#line 3078 "src/gen_parser.c"
    break;

  case 77: /* do_while: "do" body "while" expr ";"  */
#line 264 "src/parser.y"
                                     {
		(yyval.node) = gen_while((yyvsp[-3].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_DELAYED);
	}
#line 3087 "src/gen_parser.c"
    break;

  case 78: /* goto: "goto" id  */
#line 270 "src/parser.y"
                { (yyval.node) = gen_goto(gen_label((yyvsp[0].node)));  }
#line 3093 "src/gen_parser.c"
    break;

  case 79: /* statement: expr ";"  */
#line 272 "src/parser.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 3099 "src/gen_parser.c"
    break;

  case 80: /* statement: "return" init_expr ";"  */
#line 273 "src/parser.y"
                                 { (yyval.node) = gen_return((yyvsp[-1].node));  }
#line 3105 "src/gen_parser.c"
    break;

  case 81: /* statement: "return" ";"  */
#line 274 "src/parser.y"
                       { (yyval.node) = gen_return(NULL); }
#line 3111 "src/gen_parser.c"
    break;

  case 82: /* statement: "break" ";"  */
#line 275 "src/parser.y"
                      { (yyval.node) = gen_ctrl(AST_CTRL_BREAK, to_src_loc(&yylloc)); }
#line 3117 "src/gen_parser.c"
    break;

  case 83: /* statement: "continue" ";"  */
#line 276 "src/parser.y"
                         { (yyval.node) = gen_ctrl(AST_CTRL_CONTINUE,
	to_src_loc(&yylloc));  }
#line 3124 "src/gen_parser.c"
    break;

  case 84: /* statement: import ";"  */
#line 278 "src/parser.y"
                     { (yyval.node) = (yyvsp[-1].node); }
#line 3130 "src/gen_parser.c"
    break;

  case 85: /* statement: var ";"  */
#line 279 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3136 "src/gen_parser.c"
    break;

  case 86: /* statement: if  */
#line 280 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3142 "src/gen_parser.c"
    break;

  case 87: /* statement: goto ";"  */
#line 281 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3148 "src/gen_parser.c"
    break;

  case 88: /* statement: id ":"  */
#line 282 "src/parser.y"
                 { (yyval.node) = gen_label((yyvsp[-1].node));  }
#line 3154 "src/gen_parser.c"
    break;

  case 89: /* statement: for  */
#line 283 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3160 "src/gen_parser.c"
    break;

  case 90: /* statement: const  */
#line 284 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3166 "src/gen_parser.c"
    break;

  case 91: /* statement: while  */
#line 285 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3172 "src/gen_parser.c"
    break;

  case 92: /* statement: do_while  */
#line 286 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3178 "src/gen_parser.c"
    break;

  case 93: /* statement: switch  */
#line 287 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3184 "src/gen_parser.c"
    break;

  case 94: /* statement: macro  */
#line 288 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3190 "src/gen_parser.c"
    break;

  case 95: /* statement: struct  */
#line 289 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3196 "src/gen_parser.c"
    break;

  case 96: /* statement: type_alias ";"  */
#line 290 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3202 "src/gen_parser.c"
    break;

  case 97: /* statement: type_template  */
#line 291 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3208 "src/gen_parser.c"
    break;

  case 98: /* statement: enum  */
#line 292 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3214 "src/gen_parser.c"
    break;

  case 99: /* statement: body  */
#line 293 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3220 "src/gen_parser.c"
    break;

  case 100: /* statement: ";"  */
#line 294 "src/parser.y"
              { (yyval.node) = gen_empty();  }
#line 3226 "src/gen_parser.c"
    break;

  case 101: /* statement: error  */
#line 295 "src/parser.y"
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
#line 3245 "src/gen_parser.c"
    break;

  case 102: /* statement_list: statement statement_list  */
#line 311 "src/parser.y"
                                         { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3251 "src/gen_parser.c"
    break;

  case 103: /* statement_list: statement  */
#line 312 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3257 "src/gen_parser.c"
    break;

  case 104: /* body: "{" statement_list "}"  */
#line 315 "src/parser.y"
                             { (yyval.node) = gen_block((yyvsp[-1].node));  }
#line 3263 "src/gen_parser.c"
    break;

  case 105: /* body: "{" "}"  */
#line 316 "src/parser.y"
                  { (yyval.node) = gen_block(gen_empty());  }
#line 3269 "src/gen_parser.c"
    break;

  case 106: /* macro_list: id "," macro_list  */
#line 319 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 3275 "src/gen_parser.c"
    break;

  case 107: /* macro_list: id  */
#line 320 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3281 "src/gen_parser.c"
    break;

  case 108: /* macro: "define" id "(" macro_list ")" body  */
#line 323 "src/parser.y"
                                           {
		(yyval.node) = gen_macro((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3290 "src/gen_parser.c"
    break;

  case 109: /* macro: "define" id "(" macro_list "..." id ")" body  */
#line 327 "src/parser.y"
                                                       {
		/* TODO: the location data of the variadic ID is way off */
		ast_append((yyvsp[-4].node), (yyvsp[-2].node));
		(yyval.node) = gen_macro((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3302 "src/gen_parser.c"
    break;

  case 110: /* macro: "define" id "(" ")" body  */
#line 334 "src/parser.y"
                                   {
		(yyval.node) = gen_macro((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3311 "src/gen_parser.c"
    break;

  case 111: /* expr_list: expr "," expr_list  */
#line 340 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3317 "src/gen_parser.c"
    break;

  case 112: /* expr_list: expr  */
#line 341 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3323 "src/gen_parser.c"
    break;

  case 113: /* struct_init: init_expr  */
#line 344 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 3329 "src/gen_parser.c"
    break;

  case 114: /* struct_init: "." id "=" init_expr  */
#line 345 "src/parser.y"
                               {
		(yyval.node) = gen_var((yyvsp[-2].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_MEMBER);
	}
#line 3338 "src/gen_parser.c"
    break;

  case 115: /* struct_inits: struct_init "," struct_inits  */
#line 351 "src/parser.y"
                                           { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3344 "src/gen_parser.c"
    break;

  case 116: /* struct_inits: struct_init  */
#line 352 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3350 "src/gen_parser.c"
    break;

  case 117: /* struct_construct: "{" struct_inits "}"  */
#line 355 "src/parser.y"
                                       { (yyval.node) = gen_init((yyvsp[-1].node)); }
#line 3356 "src/gen_parser.c"
    break;

  case 118: /* init_expr: expr  */
#line 358 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3362 "src/gen_parser.c"
    break;

  case 119: /* init_expr: expr_if  */
#line 359 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 3368 "src/gen_parser.c"
    break;

  case 120: /* init_expr: struct_construct  */
#line 360 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 3374 "src/gen_parser.c"
    break;

  case 121: /* init_expr: struct_construct "as" type  */
#line 361 "src/parser.y"
                                     { (yyval.node) = gen_cast((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3380 "src/gen_parser.c"
    break;

  case 122: /* cond: expr  */
#line 364 "src/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 3386 "src/gen_parser.c"
    break;

  case 123: /* cond: "(" expr_if ")"  */
#line 365 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 3392 "src/gen_parser.c"
    break;

  case 124: /* expr_if: "if" cond body "else" body  */
#line 369 "src/parser.y"
                                    { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3398 "src/gen_parser.c"
    break;

  case 125: /* expr_if: "if" cond body "else" expr_if  */
#line 370 "src/parser.y"
                                        { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3404 "src/gen_parser.c"
    break;

  case 126: /* if: "if" cond body  */
#line 373 "src/parser.y"
                   { (yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3410 "src/gen_parser.c"
    break;

  case 127: /* if: "if" cond body "else" body  */
#line 374 "src/parser.y"
                                     { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3416 "src/gen_parser.c"
    break;

  case 128: /* if: "if" cond body "else" if  */
#line 375 "src/parser.y"
                                   { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3422 "src/gen_parser.c"
    break;

  case 129: /* for: "for" arg ";" expr ";" expr body  */
#line 378 "src/parser.y"
                                      { (yyval.node) = gen_for((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3428 "src/gen_parser.c"
    break;

  case 130: /* case: "case" expr ":" statement_list  */
#line 381 "src/parser.y"
                                     { (yyval.node) = gen_case((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3434 "src/gen_parser.c"
    break;

  case 131: /* case_list: case case_list  */
#line 384 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3440 "src/gen_parser.c"
    break;

  case 132: /* case_list: case  */
#line 385 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3446 "src/gen_parser.c"
    break;

  case 133: /* switch: "switch" expr "{" case_list "}"  */
#line 388 "src/parser.y"
                                        { (yyval.node) = gen_switch((yyvsp[-3].node), (yyvsp[-1].node));  }
#line 3452 "src/gen_parser.c"
    break;

  case 134: /* const_for: "for" id ":" expr_list body  */
#line 391 "src/parser.y"
                                       {
		/* TODO: should id be a separate rule? */
		(yyval.node) = gen_for((yyvsp[-3].node), NULL, (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3462 "src/gen_parser.c"
    break;

  case 135: /* const_if: "if" expr body  */
#line 398 "src/parser.y"
                         {
		(yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3471 "src/gen_parser.c"
    break;

  case 136: /* const_if: "if" expr body "else" body  */
#line 402 "src/parser.y"
                                     {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3481 "src/gen_parser.c"
    break;

  case 137: /* const_if: "if" expr body "else" const_if  */
#line 407 "src/parser.y"
                                         {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
	}
#line 3490 "src/gen_parser.c"
    break;

  case 138: /* const: "const" const_if  */
#line 415 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST);
      }
#line 3497 "src/gen_parser.c"
    break;

  case 139: /* const: "const" const_for  */
#line 417 "src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST);
	 }
#line 3504 "src/gen_parser.c"
    break;

  case 140: /* func_sign: "(" decl_list "=>" type ")"  */
#line 421 "src/parser.y"
                                       {
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 3512 "src/gen_parser.c"
    break;

  case 141: /* func_sign: "(" decl_list ")"  */
#line 424 "src/parser.y"
                            { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-1].node), NULL);
	 }
#line 3519 "src/gen_parser.c"
    break;

  case 142: /* func_sign: "(" decl_list "=>" ")"  */
#line 426 "src/parser.y"
                                 { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-2].node), NULL);
	 }
#line 3526 "src/gen_parser.c"
    break;

  case 143: /* func_sign: "(" "=>" type ")"  */
#line 428 "src/parser.y"
                            { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, (yyvsp[-1].node));
	 }
#line 3533 "src/gen_parser.c"
    break;

  case 144: /* func_sign: "(" ")"  */
#line 430 "src/parser.y"
                  { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, NULL);
	 }
#line 3540 "src/gen_parser.c"
    break;

  case 145: /* variadic_sign: func_sign  */
#line 434 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3546 "src/gen_parser.c"
    break;

  case 146: /* variadic_sign: "(" decl_list "..." id "=>" type ")"  */
#line 435 "src/parser.y"
                                               {
		ast_append((yyvsp[-5].node), (yyvsp[-3].node));
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
	}
#line 3556 "src/gen_parser.c"
    break;

  case 147: /* type: id  */
#line 442 "src/parser.y"
         { (yyval.node) = gen_type(AST_TYPE_ID, (yyvsp[0].node), NULL, NULL); }
#line 3562 "src/gen_parser.c"
    break;

  case 148: /* type: "'" func_sign  */
#line 443 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->next = (yyvsp[0].node);
	}
#line 3571 "src/gen_parser.c"
    break;

  case 149: /* type: id "(" type_list ")"  */
#line 447 "src/parser.y"
                               {
		(yyval.node) = gen_type(AST_TYPE_STRUCT, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
	}
#line 3579 "src/gen_parser.c"
    break;

  case 150: /* type: "'" type  */
#line 450 "src/parser.y"
                   {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3588 "src/gen_parser.c"
    break;

  case 151: /* type: "[" "]" type  */
#line 454 "src/parser.y"
                       {
		(yyval.node) = gen_type(AST_TYPE_ARR, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3597 "src/gen_parser.c"
    break;

  case 152: /* type: "[" expr "]" type  */
#line 458 "src/parser.y"
                            {
		(yyval.node) = gen_type(AST_TYPE_ARR, NULL, (yyvsp[-2].node), NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3606 "src/gen_parser.c"
    break;

  case 153: /* type: "typeof" expr  */
#line 462 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_TYPEOF, NULL, (yyvsp[0].node), NULL);
	}
#line 3614 "src/gen_parser.c"
    break;

  case 154: /* var_decl: id "mut" type  */
#line 467 "src/parser.y"
                        {
		(yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_MUTABLE);
	}
#line 3623 "src/gen_parser.c"
    break;

  case 155: /* var_decl: id "const" type  */
#line 471 "src/parser.y"
                          { (yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);  }
#line 3629 "src/gen_parser.c"
    break;

  case 156: /* var_decl: id type  */
#line 472 "src/parser.y"
                  { (yyval.node) = gen_var((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3635 "src/gen_parser.c"
    break;

  case 157: /* var_init: var_decl "=" init_expr  */
#line 475 "src/parser.y"
                                 { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->_var.init = (yyvsp[0].node); }
#line 3641 "src/gen_parser.c"
    break;

  case 158: /* var_init: id "mut" "=" init_expr  */
#line 476 "src/parser.y"
                                 {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED | AST_FLAG_MUTABLE);
	}
#line 3650 "src/gen_parser.c"
    break;

  case 159: /* var_init: id "const" "=" init_expr  */
#line 480 "src/parser.y"
                                   {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 3659 "src/gen_parser.c"
    break;

  case 160: /* proc: id variadic_sign body  */
#line 486 "src/parser.y"
                            {
		(yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), (yyvsp[-1].node)->flags);
	}
#line 3668 "src/gen_parser.c"
    break;

  case 161: /* proc: "extern" id func_sign  */
#line 490 "src/parser.y"
                                {
		(yyval.node) = gen_proc((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_EXTERN);
	}
#line 3677 "src/gen_parser.c"
    break;

  case 162: /* lambda: "[" macro_list "]" func_sign body  */
#line 496 "src/parser.y"
                                          { (yyval.node) = gen_lambda((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3683 "src/gen_parser.c"
    break;

  case 163: /* struct_elem: var_decl  */
#line 499 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3689 "src/gen_parser.c"
    break;

  case 164: /* struct_list: struct_elem ";" struct_list  */
#line 502 "src/parser.y"
                                         { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3695 "src/gen_parser.c"
    break;

  case 165: /* struct_list: struct_elem ";"  */
#line 503 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 3701 "src/gen_parser.c"
    break;

  case 166: /* union: "union" id "{" struct_list "}"  */
#line 506 "src/parser.y"
                                      {
		(yyval.node) = gen_union((yyvsp[-3].node), NULL, (yyvsp[-1].node));
	}
#line 3709 "src/gen_parser.c"
    break;

  case 167: /* union: "union" id "(" generic_list ")" "{" struct_list "}"  */
#line 509 "src/parser.y"
                                                              {
		(yyval.node) = gen_union((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
	}
#line 3717 "src/gen_parser.c"
    break;

  case 168: /* generic: id type  */
#line 514 "src/parser.y"
                 { (yyval.node) = gen_alias((yyvsp[-1].node), (yyvsp[0].node)); }
#line 3723 "src/gen_parser.c"
    break;

  case 169: /* generic_list: generic "," generic_list  */
#line 515 "src/parser.y"
                                       { (yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 3729 "src/gen_parser.c"
    break;

  case 170: /* generic_list: generic  */
#line 516 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 3735 "src/gen_parser.c"
    break;

  case 171: /* struct: "struct" id "{" struct_list "}"  */
#line 519 "src/parser.y"
                                        {
		(yyval.node) = gen_struct((yyvsp[-3].node), NULL, (yyvsp[-1].node));
	}
#line 3743 "src/gen_parser.c"
    break;

  case 172: /* struct: "struct" id "(" generic_list ")" "{" struct_list "}"  */
#line 522 "src/parser.y"
                                                               {
		(yyval.node) = gen_struct((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
	}
#line 3751 "src/gen_parser.c"
    break;

  case 173: /* template_elem: id ";"  */
#line 529 "src/parser.y"
                      { (yyval.node) = (yyvsp[-1].node); }
#line 3757 "src/gen_parser.c"
    break;

  case 174: /* template_elem: id func_sign ";"  */
#line 530 "src/parser.y"
                           { (yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), NULL);  }
#line 3763 "src/gen_parser.c"
    break;

  case 175: /* template_elem: var_decl ";"  */
#line 531 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3769 "src/gen_parser.c"
    break;

  case 176: /* template_elem: union  */
#line 532 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3775 "src/gen_parser.c"
    break;

  case 177: /* template_list: template_elem template_list  */
#line 535 "src/parser.y"
                                           { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3781 "src/gen_parser.c"
    break;

  case 178: /* template_list: template_elem  */
#line 536 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3787 "src/gen_parser.c"
    break;

  case 179: /* type_list: type "," type_list  */
#line 539 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3793 "src/gen_parser.c"
    break;

  case 180: /* type_list: type  */
#line 540 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3799 "src/gen_parser.c"
    break;

  case 181: /* type_alias: "type" id type  */
#line 543 "src/parser.y"
                           { (yyval.node) = gen_alias((yyvsp[-1].node), (yyvsp[0].node));  }
#line 3805 "src/gen_parser.c"
    break;

  case 182: /* type_template: "type" id "{" template_list "}"  */
#line 548 "src/parser.y"
                                               {
		(yyval.node) = gen_template((yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 3813 "src/gen_parser.c"
    break;

  case 183: /* type_template: "type" id "{" "}"  */
#line 551 "src/parser.y"
                            {
		/* should match anything, but doesn't implement anything */
		(yyval.node) = gen_template((yyvsp[-2].node), NULL);
	}
#line 3822 "src/gen_parser.c"
    break;

  case 184: /* enum_val: id  */
#line 557 "src/parser.y"
             { (yyval.node) = gen_val((yyvsp[0].node), gen_int(0));  }
#line 3828 "src/gen_parser.c"
    break;

  case 185: /* enum_val: id "=" expr  */
#line 558 "src/parser.y"
                      { (yyval.node) = gen_val((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3834 "src/gen_parser.c"
    break;

  case 186: /* enum_list: enum_val "," enum_list  */
#line 561 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3840 "src/gen_parser.c"
    break;

  case 187: /* enum_list: enum_val ","  */
#line 562 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3846 "src/gen_parser.c"
    break;

  case 188: /* enum_list: enum_val  */
#line 563 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3852 "src/gen_parser.c"
    break;

  case 189: /* enum: "enum" id ":" type "{" enum_list "}"  */
#line 566 "src/parser.y"
                                           { (yyval.node) = gen_enum((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3858 "src/gen_parser.c"
    break;

  case 190: /* enum: "enum" id "{" enum_list "}"  */
#line 567 "src/parser.y"
                                      {
		(yyval.node) = gen_enum((yyvsp[-3].node), NULL, (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 3867 "src/gen_parser.c"
    break;

  case 191: /* top_if: "if" expr "{" unit "}"  */
#line 573 "src/parser.y"
                               {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-1].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3876 "src/gen_parser.c"
    break;

  case 192: /* top_if: "if" expr "{" unit "}" "else" "{" unit "}"  */
#line 577 "src/parser.y"
                                                     {
		(yyval.node) = gen_if((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3885 "src/gen_parser.c"
    break;

  case 193: /* top_if: "if" expr "{" unit "}" "else" top_if  */
#line 581 "src/parser.y"
                                               {
		(yyval.node) = gen_if((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3894 "src/gen_parser.c"
    break;

  case 194: /* top: ";"  */
#line 589 "src/parser.y"
         { (yyval.node) = gen_empty(); }
#line 3900 "src/gen_parser.c"
    break;

  case 195: /* top: enum  */
#line 590 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3906 "src/gen_parser.c"
    break;

  case 196: /* top: proc  */
#line 591 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3912 "src/gen_parser.c"
    break;

  case 197: /* top: struct  */
#line 592 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3918 "src/gen_parser.c"
    break;

  case 198: /* top: macro  */
#line 593 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3924 "src/gen_parser.c"
    break;

  case 199: /* top: "const" top_if  */
#line 594 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 3930 "src/gen_parser.c"
    break;

  case 200: /* top: import ";"  */
#line 595 "src/parser.y"
                     { (yyval.node) = (yyvsp[-1].node); }
#line 3936 "src/gen_parser.c"
    break;

  case 201: /* top: type_alias ";"  */
#line 596 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3942 "src/gen_parser.c"
    break;

  case 202: /* top: type_template  */
#line 597 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3948 "src/gen_parser.c"
    break;

  case 203: /* top: "pub" enum  */
#line 598 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3954 "src/gen_parser.c"
    break;

  case 204: /* top: "pub" struct  */
#line 599 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3960 "src/gen_parser.c"
    break;

  case 205: /* top: "pub" proc  */
#line 600 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3966 "src/gen_parser.c"
    break;

  case 206: /* top: "pub" macro  */
#line 601 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3972 "src/gen_parser.c"
    break;

  case 207: /* top: "pub" import ";"  */
#line 602 "src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 3978 "src/gen_parser.c"
    break;

  case 208: /* top: "pub" type_alias ";"  */
#line 603 "src/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 3984 "src/gen_parser.c"
    break;

  case 209: /* top: "pub" type_template  */
#line 604 "src/parser.y"
                              { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3990 "src/gen_parser.c"
    break;

  case 210: /* top: var ";"  */
#line 605 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3996 "src/gen_parser.c"
    break;

  case 211: /* top: "pub" var ";"  */
#line 606 "src/parser.y"
                        { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 4002 "src/gen_parser.c"
    break;

  case 212: /* top: error  */
#line 607 "src/parser.y"
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
#line 4020 "src/gen_parser.c"
    break;

  case 213: /* unit: top  */
#line 622 "src/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 4026 "src/gen_parser.c"
    break;

  case 214: /* unit: top unit  */
#line 623 "src/parser.y"
                   { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 4032 "src/gen_parser.c"
    break;

  case 215: /* input: unit  */
#line 626 "src/parser.y"
            { parser->tree = (yyvsp[0].node); }
#line 4038 "src/gen_parser.c"
    break;


#line 4042 "src/gen_parser.c"

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

#line 629 "src/parser.y"

