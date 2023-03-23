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
  YYSYMBOL_binary_op = 86,                 /* binary_op  */
  YYSYMBOL_unary_op = 87,                  /* unary_op  */
  YYSYMBOL_arg = 88,                       /* arg  */
  YYSYMBOL_arg_list = 89,                  /* arg_list  */
  YYSYMBOL_param_decl = 90,                /* param_decl  */
  YYSYMBOL_decl_list = 91,                 /* decl_list  */
  YYSYMBOL_call = 92,                      /* call  */
  YYSYMBOL_defer = 93,                     /* defer  */
  YYSYMBOL_expr = 94,                      /* expr  */
  YYSYMBOL_while = 95,                     /* while  */
  YYSYMBOL_do_while = 96,                  /* do_while  */
  YYSYMBOL_goto = 97,                      /* goto  */
  YYSYMBOL_statement = 98,                 /* statement  */
  YYSYMBOL_statement_list = 99,            /* statement_list  */
  YYSYMBOL_body = 100,                     /* body  */
  YYSYMBOL_macro_list = 101,               /* macro_list  */
  YYSYMBOL_macro = 102,                    /* macro  */
  YYSYMBOL_expr_list = 103,                /* expr_list  */
  YYSYMBOL_init_expr = 104,                /* init_expr  */
  YYSYMBOL_expr_if = 105,                  /* expr_if  */
  YYSYMBOL_if = 106,                       /* if  */
  YYSYMBOL_for = 107,                      /* for  */
  YYSYMBOL_case = 108,                     /* case  */
  YYSYMBOL_case_list = 109,                /* case_list  */
  YYSYMBOL_switch = 110,                   /* switch  */
  YYSYMBOL_const_for = 111,                /* const_for  */
  YYSYMBOL_const_if = 112,                 /* const_if  */
  YYSYMBOL_const = 113,                    /* const  */
  YYSYMBOL_func_sign = 114,                /* func_sign  */
  YYSYMBOL_variadic_sign = 115,            /* variadic_sign  */
  YYSYMBOL_impl = 116,                     /* impl  */
  YYSYMBOL_impl_list = 117,                /* impl_list  */
  YYSYMBOL_type = 118,                     /* type  */
  YYSYMBOL_var_decl = 119,                 /* var_decl  */
  YYSYMBOL_var_init = 120,                 /* var_init  */
  YYSYMBOL_proc = 121,                     /* proc  */
  YYSYMBOL_lambda = 122,                   /* lambda  */
  YYSYMBOL_union_elem = 123,               /* union_elem  */
  YYSYMBOL_union_list = 124,               /* union_list  */
  YYSYMBOL_union = 125,                    /* union  */
  YYSYMBOL_struct_list = 126,              /* struct_list  */
  YYSYMBOL_struct = 127,                   /* struct  */
  YYSYMBOL_template_elem = 128,            /* template_elem  */
  YYSYMBOL_template_list = 129,            /* template_list  */
  YYSYMBOL_type_list = 130,                /* type_list  */
  YYSYMBOL_type_alias = 131,               /* type_alias  */
  YYSYMBOL_type_template = 132,            /* type_template  */
  YYSYMBOL_enum_val = 133,                 /* enum_val  */
  YYSYMBOL_enum_list = 134,                /* enum_list  */
  YYSYMBOL_enum = 135,                     /* enum  */
  YYSYMBOL_top_if = 136,                   /* top_if  */
  YYSYMBOL_top = 137,                      /* top  */
  YYSYMBOL_unit = 138,                     /* unit  */
  YYSYMBOL_input = 139                     /* input  */
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
#define YYLAST   1950

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  210
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  418

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
       0,   146,   146,   152,   153,   156,   159,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     187,   190,   191,   192,   193,   194,   195,   198,   199,   200,
     201,   202,   205,   206,   207,   210,   211,   214,   216,   217,
     218,   219,   223,   224,   227,   231,   232,   233,   234,   235,
     236,   237,   238,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   255,   258,   264,   266,   267,   268,
     269,   270,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     305,   306,   309,   310,   313,   314,   317,   321,   328,   334,
     335,   338,   339,   340,   341,   344,   345,   348,   349,   350,
     353,   357,   360,   361,   364,   367,   374,   378,   383,   391,
     393,   397,   400,   402,   404,   406,   410,   411,   418,   420,
     423,   424,   427,   428,   432,   435,   439,   443,   447,   452,
     456,   457,   460,   461,   465,   471,   475,   481,   485,   486,
     489,   490,   493,   496,   501,   504,   507,   512,   513,   514,
     515,   518,   519,   522,   523,   526,   531,   534,   540,   541,
     544,   545,   546,   549,   550,   556,   560,   564,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     584,   585,   586,   587,   588,   589,   590,   605,   606,   609,
     610
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
  "binary_op", "unary_op", "arg", "arg_list", "param_decl", "decl_list",
  "call", "defer", "expr", "while", "do_while", "goto", "statement",
  "statement_list", "body", "macro_list", "macro", "expr_list",
  "init_expr", "expr_if", "if", "for", "case", "case_list", "switch",
  "const_for", "const_if", "const", "func_sign", "variadic_sign", "impl",
  "impl_list", "type", "var_decl", "var_init", "proc", "lambda",
  "union_elem", "union_list", "union", "struct_list", "struct",
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

#define YYPACT_NINF (-225)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-211)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     482,  -225,  -225,  -225,   246,    42,    42,    50,   -30,    42,
      42,    42,   408,    61,    62,  -225,    74,  -225,  -225,  -225,
      75,  -225,  -225,  1028,  -225,   107,   120,   128,  -225,  -225,
    -225,   131,  -225,  -225,    65,    30,  -225,  1039,  -225,    77,
      27,    83,   141,  1039,   227,   284,    70,   153,    97,  -225,
      68,  -225,  -225,  -225,   915,  -225,  -225,  -225,  -225,  -225,
    -225,   127,    33,    23,  -225,  -225,  -225,  -225,  1039,    42,
    1039,  1039,  1039,  1039,  1039,  -225,    98,    99,  1039,    42,
     127,    53,  -225,  -225,  -225,  -225,  -225,  1102,  -225,    70,
    -225,   127,    42,    22,  -225,  -225,  1871,   915,  -225,   915,
    -225,  -225,   127,   429,   118,     8,  -225,   125,   127,  1166,
      42,   731,  -225,  1039,   915,   280,  1871,  -225,  -225,    74,
    -225,   126,   102,    12,    51,  -225,   167,  -225,  -225,   103,
    -225,   438,   169,   172,  -225,    33,   114,   111,  -225,   111,
    1871,   176,  1327,   111,  1039,   186,  1230,   122,   158,   135,
    -225,    42,   883,  1039,  1039,  1039,  1039,  1039,  1039,  1039,
    1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,
    1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,
    1039,  1039,  1039,   567,   127,    42,   -40,   134,   208,   170,
     144,    68,    56,  -225,  -225,   147,   127,   127,   127,    42,
    -225,   253,   127,  -225,   127,   148,   175,   151,  -225,  -225,
      42,   915,   217,   222,  1039,   961,  1039,    68,   993,   -16,
    -225,   256,   226,   231,  1294,  -225,  -225,   240,   649,   181,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,   241,  -225,  -225,
    -225,    68,   127,   190,    33,   191,    33,  -225,   127,   258,
    -225,  -225,  -225,  -225,  1358,   197,  -225,  -225,    42,    77,
    -225,  1039,  -225,   224,   201,  -225,    74,  1871,   -19,   -19,
     -19,   176,   176,  1135,  1071,  1327,   745,  1263,  1199,   562,
     562,   562,   562,   821,   821,   437,   437,  1871,  1871,  1871,
    1871,  1871,  1871,  1871,  1871,  1871,  1871,   200,  -225,  -225,
      42,  1039,    42,  -225,  -225,    42,    68,  -225,  -225,   196,
    -225,   204,  -225,  -225,    42,  -225,  -225,    68,  -225,  -225,
    1422,   269,  1486,   225,  -225,  1551,  1039,    42,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,   236,  -225,
      33,   232,    33,  -225,   233,  -225,  -225,  -225,  -225,    68,
      74,   961,  -225,   243,   234,  1871,  -225,   237,  -225,   127,
    -225,  -225,   248,   250,  1039,  -225,  1039,  -225,  1486,   302,
     -25,   244,  -225,   245,  -225,  -225,  -225,   -23,  -225,    68,
     252,    13,  1039,   250,   255,  1615,  1679,   260,  1039,  -225,
    -225,  -225,  -225,   567,  -225,  -225,  -225,  -225,  -225,  1743,
    -225,  -225,  1039,  -225,    79,  1807,    68,   259,   807,  1486,
    -225,  -225,  1039,  -225,  -225,  -225,  -225,  -225
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   206,     2,   188,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   192,     3,     4,   190,   191,
       0,   196,   189,     0,   209,     0,     0,     0,   200,   199,
     198,     0,   203,   197,     0,     0,     6,     0,   193,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   142,   136,
       0,   151,   204,   194,     0,   195,   208,     1,   205,   201,
     202,     0,     0,     0,   175,    60,    61,    62,     0,     0,
       0,     0,     0,     0,     0,    59,     0,     0,     0,     0,
       0,    55,    72,    66,    67,    64,    65,     0,    73,     0,
     156,     0,     0,     0,   143,   145,   148,     0,   149,     0,
     150,   135,     0,   142,    51,     0,    47,    50,     0,     0,
       0,     0,   155,     0,     0,    55,   111,   152,   114,     0,
     112,   174,     0,     0,     0,   159,     0,   164,   158,     0,
     177,   139,     0,     0,   170,   172,     0,    40,    58,    38,
      69,    37,    39,    41,     0,     0,     0,     0,   105,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   178,   182,
       0,     0,     0,   153,   154,     0,     0,     0,     0,     0,
     132,     0,     0,   146,     0,   139,   141,     0,    99,    98,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     103,    55,     0,     0,     0,    89,    90,     0,     0,     0,
      97,    92,    84,    87,    91,    88,    93,     0,    95,    96,
     113,     0,     0,     0,     0,     0,   161,   165,     0,     0,
     167,   169,   171,   176,     0,     0,    63,    68,     0,     0,
      57,     0,    53,    46,     0,    44,    43,     7,    10,    11,
      12,     9,     8,    14,    13,    15,    17,    16,    18,    31,
      32,    33,    34,    35,    36,    19,    20,    21,    22,    23,
      24,    25,    28,    26,    27,    29,    30,     0,    70,    56,
       0,     0,   181,   184,   108,     0,     0,   134,    49,     0,
     133,     0,    48,   147,     0,   144,    76,     0,    80,    81,
       0,     0,     0,     0,    79,     0,     0,     0,   130,   129,
      86,    83,    82,    77,    85,   100,   102,    94,     0,   173,
       0,     0,     0,   160,     0,   168,    54,     5,   104,     0,
      42,     0,    52,   185,     0,   179,   180,     0,   106,     0,
     131,   140,   117,     0,     0,    74,     0,    78,     0,     0,
       0,     0,   163,     0,   138,   157,    45,     0,   183,     0,
       0,     0,     0,   123,     0,     0,     0,   126,     0,   115,
     116,   166,   162,     0,   187,   107,   137,   118,   119,     0,
     122,   124,     0,    75,     0,   110,     0,     0,     0,     0,
     127,   128,     0,   125,   186,   121,   120,   109
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,     0,    -2,  -225,     9,  -225,  -225,   116,   -18,  -225,
     -86,  -225,  -225,   210,  -225,  -225,  -225,  -225,  -220,    94,
     -77,    10,   -76,   -24,   -33,   -43,  -225,  -225,   -44,  -225,
    -225,   -63,  -225,    14,  -225,  -109,    29,   359,   431,   -47,
     340,  -225,  -225,  -224,   -39,     5,    11,  -225,   212,  -148,
      15,    17,  -225,  -139,    21,   -28,  -225,     3,  -225
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    81,    13,    82,    14,    83,    84,   263,   264,   104,
     105,    85,    86,   116,   225,   226,   227,   228,   229,   230,
     149,    15,   406,   265,   118,   232,   233,   383,   384,   234,
     328,   329,   235,    49,    50,   132,   207,    51,    16,    17,
      18,    88,   126,   127,   128,   129,    19,   135,   136,   122,
      20,    21,   189,   190,    22,    38,    23,    24,    25
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      12,   206,    26,   186,    12,    34,    35,   120,   335,    39,
      40,    41,    48,    27,    28,    30,   192,   199,     2,    31,
     341,    32,   343,    12,   134,    33,    56,    37,     2,     2,
     117,   147,   114,   200,    37,    48,     2,    42,    91,     2,
     201,   326,    48,    43,    48,    48,   103,   327,     2,   111,
     120,   393,   120,    90,   115,    36,    94,     2,    42,   184,
     185,    48,   124,   131,    43,   305,   240,   120,   151,   138,
     211,    52,    53,   193,   123,   194,     2,    42,   115,   148,
      48,   200,    54,    43,   123,    55,   244,   111,   201,   103,
     241,    48,   188,   148,   339,   191,   134,   115,   130,   115,
     344,    92,    48,    48,    63,   120,    47,    57,    48,   222,
     205,   221,   308,   115,   115,    48,   312,   196,   373,   197,
     223,   231,   236,   245,    48,   152,   237,    47,   238,   306,
      58,    48,   239,     2,    42,   131,   326,    61,    59,    62,
      43,    60,   111,   101,   112,   249,    47,     2,    42,    89,
     102,   260,   115,   111,    43,    93,    65,    66,    67,     2,
      68,   354,    69,   356,   120,    70,   198,    71,   120,   110,
     144,   145,    72,   202,   242,   243,    73,   246,   247,   250,
      74,   348,   251,    12,    48,   299,   297,   317,   415,   253,
     185,   255,   154,   155,   156,   257,    48,    48,   103,   309,
      75,    48,   103,    47,    48,   206,   258,    76,   300,    77,
     316,   115,   259,    89,   240,   115,   301,    47,   302,   303,
     307,    48,   248,   314,   315,    78,   222,   318,   221,    79,
     108,    80,   319,     2,    42,    97,   331,   223,   231,   236,
      43,   332,    48,   237,   124,   238,   124,    87,    48,   239,
     334,   337,     2,    96,   184,   185,   336,   109,   148,     2,
      42,   115,     2,    42,   340,   342,    43,   330,   345,    43,
     347,   151,   351,   349,   352,   353,   359,   360,   137,   364,
     139,   140,   141,   142,   143,   304,     2,    42,   146,   366,
       2,    42,    99,    43,   370,   151,     5,    43,     6,     7,
     188,   377,   188,    47,   120,   357,   381,   372,   374,   378,
     379,   323,   382,   388,   205,     9,    10,    11,   404,   391,
     392,   224,    44,   142,    45,   396,   310,   369,   152,    47,
     401,   321,    47,   376,   414,   338,   417,   390,   398,   400,
     124,   411,   124,   361,    29,   371,    44,   252,    45,   394,
       0,   115,   152,     0,   254,     0,    47,     0,     0,    48,
      47,     0,     0,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,    12,    64,     0,   407,     0,     0,     0,
     358,    95,     0,    98,   100,   106,   222,     0,   221,     0,
       0,   362,     0,     0,     2,    42,   365,   223,   231,   236,
     121,    43,     0,   237,   320,   238,   322,     0,   325,   239,
       0,     0,     0,     0,     0,     2,    42,     0,   224,   150,
       0,     0,    43,   375,     2,    42,     0,     0,   106,     0,
     187,    43,     0,   154,   155,   156,   157,   158,     0,     0,
       0,   195,   387,     0,   389,     0,     0,   203,     0,     0,
       0,   142,     0,   395,    44,   397,    45,   107,     0,     0,
      46,     0,  -210,     1,    47,   119,     0,     0,     2,     0,
       0,     0,     3,   125,   133,   196,     0,   197,   410,     0,
     413,   110,     0,   416,   196,    47,   197,     0,     0,   119,
      89,   355,   248,     0,    47,   184,   185,     0,     0,     0,
     107,     0,     0,     0,     0,     0,     0,     0,   119,     0,
     119,     4,     5,     0,     6,     7,   368,     0,     0,     0,
       0,     0,     0,   298,   119,   119,     0,     0,     0,     0,
       8,     9,    10,    11,     0,    98,   100,   106,     0,     0,
     311,   106,     0,   313,     0,     0,   133,     0,     1,     0,
       0,     0,     0,     2,   385,     0,   386,     3,   154,   155,
     156,   157,   158,   266,   160,   161,   162,     0,     0,     0,
       0,     0,   399,     0,     0,     0,   171,   172,   405,     0,
       0,   121,     0,     0,     0,     0,     0,   121,     0,     0,
       0,     0,   409,     0,     0,     0,     4,     5,   224,     6,
       7,     0,   405,     0,     0,     0,     0,     0,     0,   107,
       0,     0,     0,   107,     0,     8,     9,    10,    11,     0,
     184,   185,   119,     0,     0,     0,   266,     0,     0,     0,
     208,     0,    65,    66,    67,     2,    68,     0,    69,   209,
       0,    70,     0,    71,     0,     0,     0,     0,    72,     0,
       0,     0,    73,     0,     0,   125,    74,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   350,     0,     0,     0,    75,     0,     0,     5,
       0,     6,     7,    76,   210,    77,   211,     0,   212,   213,
     214,  -101,   215,   216,   217,     0,   218,   219,   380,    10,
      11,    78,     0,   111,  -101,    79,     0,    80,     0,     0,
       0,     0,   208,     0,    65,    66,    67,     2,    68,     0,
      69,   209,     0,    70,     0,    71,     0,     0,     0,     0,
      72,     0,     0,     0,    73,     0,     0,     0,    74,     0,
       0,   154,   155,   156,   157,   158,     0,   160,   161,     0,
       0,   125,     0,   125,     0,     0,     0,     0,    75,   171,
     172,     5,   266,     6,     7,    76,   210,    77,   211,     0,
     212,   213,   214,     0,   215,   216,   217,     0,   218,   219,
       0,    10,    11,    78,     0,   111,   220,    79,   208,    80,
      65,    66,    67,     2,    68,     0,    69,   209,     0,    70,
       0,    71,     0,   184,   185,     0,    72,     0,     0,     0,
      73,     0,     0,     0,    74,     0,     0,   154,   155,   156,
     157,   158,     0,   160,   161,   162,     0,     0,     0,   165,
     166,   167,   168,     0,    75,   171,   172,     5,     0,     6,
       7,    76,   210,    77,   211,     0,   212,   213,   214,     0,
     215,   216,   217,     0,   218,   219,     0,    10,    11,    78,
       0,   111,     0,    79,     0,    80,    65,    66,    67,     2,
      68,     0,    69,     0,     0,    70,     0,    71,     0,   184,
     185,     0,    72,     0,     0,     0,   261,     0,     0,     0,
      74,     0,     0,     0,     0,     0,     0,     0,    65,    66,
      67,     2,    68,     0,    69,     0,     0,    70,     0,    71,
      75,     0,     0,     0,    72,     0,     0,    76,   113,    77,
     114,     0,    74,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    78,   262,     0,     0,    79,
       0,    80,    75,     0,    65,    66,    67,     2,    68,    76,
      69,    77,   114,    70,     0,    71,     0,     0,     0,     0,
      72,     0,     0,     0,   261,     0,     0,    78,    74,     0,
       0,    79,     0,    80,     0,     0,    65,    66,    67,     2,
      68,     0,    69,   324,     0,    70,     0,    71,    75,     0,
       0,     0,    72,     0,     0,    76,    73,    77,   114,     0,
      74,     0,     0,     0,     0,     0,     0,     0,  -207,     1,
       0,     0,     0,    78,     2,     0,     0,    79,     3,    80,
      75,     0,    65,    66,    67,     2,    68,    76,    69,    77,
       0,    70,     0,    71,     0,     0,     0,     0,    72,     0,
       0,     0,    73,     0,     0,    78,    74,     0,     0,    79,
       0,    80,     0,     0,     0,     0,     0,     4,     5,     0,
       6,     7,     0,     0,     0,     0,    75,   154,   155,   156,
     157,   158,     0,    76,   161,    77,     8,     9,    10,    11,
       0,     0,     0,  -207,     0,   171,   172,     0,     0,     0,
     153,    78,     0,     0,     0,    79,     0,    80,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,     0,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,     0,   179,   180,   181,   182,   184,
     185,   154,   155,   156,   157,   158,     0,   160,   161,   162,
     163,   164,     0,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,   153,     0,   183,     0,     0,     0,
     184,   185,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,     0,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,     0,   179,
     180,   181,   182,   184,   185,   154,   155,   156,   157,   158,
       0,   160,   161,   162,   163,     0,     0,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,   153,     0,
       0,     0,     0,   204,   184,   185,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,     0,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,     0,   179,   180,   181,   182,   184,   185,   154,
     155,   156,   157,   158,     0,   160,   161,   162,     0,     0,
       0,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,   153,   256,   333,     0,     0,     0,   184,   185,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,     0,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,     0,   179,   180,   181,
     182,   184,   185,   154,   155,   156,   157,   158,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   171,   172,     0,     0,     0,   153,     0,     0,     0,
       0,     0,   184,   185,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,     0,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
       0,   179,   180,   181,   182,   184,   185,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     153,   346,     0,     0,     0,     0,   184,   185,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,     0,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,     0,   179,   180,   181,   182,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   153,     0,   363,     0,     0,     0,
     184,   185,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,     0,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,     0,   179,
     180,   181,   182,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   153,
     111,   367,     0,     0,   184,   185,     0,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,     0,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,     0,   179,   180,   181,   182,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   153,     0,   402,     0,     0,     0,   184,
     185,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,     0,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,     0,   179,   180,
     181,   182,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   153,     0,   403,
       0,     0,     0,   184,   185,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,     0,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,     0,   179,   180,   181,   182,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   153,     0,     0,   408,     0,     0,   184,   185,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
       0,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,     0,   179,   180,   181,   182,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,     0,     0,     0,     0,
       0,   184,   185,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,     0,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,     0,
     179,   180,   181,   182,     0,   412,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   153,
       0,     0,     0,     0,     0,   184,   185,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,     0,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,     0,   179,   180,   181,   182,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   184,
     185
};

static const yytype_int16 yycheck[] =
{
       0,   110,     4,    89,     4,     5,     6,    54,   228,     9,
      10,    11,    12,     4,     4,     4,    93,     9,     6,     4,
     244,     4,   246,    23,    63,     4,    23,    57,     6,     6,
      54,    78,    57,    73,    57,    35,     6,     7,    11,     6,
      80,    57,    42,    13,    44,    45,    46,    63,     6,    74,
      97,    74,    99,    39,    54,     5,    42,     6,     7,    78,
      79,    61,    62,    63,    13,     9,   113,   114,    15,    69,
      57,    10,    10,    97,    51,    99,     6,     7,    78,    79,
      80,    73,     8,    13,    51,    10,    74,    74,    80,    89,
     114,    91,    92,    93,   242,    73,   135,    97,    75,    99,
     248,    74,   102,   103,    74,   152,    76,     0,   108,   111,
     110,   111,   198,   113,   114,   115,   202,    66,   342,    68,
     111,   111,   111,   123,   124,    72,   111,    76,   111,    73,
      10,   131,   111,     6,     7,   135,    57,    72,    10,    74,
      13,    10,    74,    73,    50,   131,    76,     6,     7,    72,
      80,   151,   152,    74,    13,    72,     3,     4,     5,     6,
       7,   300,     9,   302,   211,    12,    48,    14,   215,    72,
      72,    72,    19,    48,    48,    73,    23,    10,    75,    10,
      27,   258,    10,   183,   184,   185,   183,   211,   408,    75,
      79,     5,    16,    17,    18,    73,   196,   197,   198,   199,
      47,   201,   202,    76,   204,   314,    48,    54,    74,    56,
     210,   211,    77,    72,   261,   215,     8,    76,    48,    75,
      73,   221,    74,    48,    73,    72,   228,    10,   228,    76,
      77,    78,    10,     6,     7,     8,    10,   228,   228,   228,
      13,    10,   242,   228,   244,   228,   246,    37,   248,   228,
      10,    10,     6,    43,    78,    79,    75,    47,   258,     6,
       7,   261,     6,     7,    74,    74,    13,    11,    10,    13,
      73,    15,    48,   259,    73,    75,    80,    73,    68,    10,
      70,    71,    72,    73,    74,   191,     6,     7,    78,    64,
       6,     7,     8,    13,    58,    15,    50,    13,    52,    53,
     300,    58,   302,    76,   351,   305,    58,    75,    75,    75,
      73,   217,    62,    11,   314,    69,    70,    71,    58,    75,
      75,   111,    66,   113,    68,    73,    73,   327,    72,    76,
      75,   215,    76,   351,    75,   241,   412,   370,   381,   383,
     340,   404,   342,   314,     4,   340,    66,   135,    68,   377,
      -1,   351,    72,    -1,   144,    -1,    76,    -1,    -1,   359,
      76,    -1,    -1,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   393,    35,    -1,   393,    -1,    -1,    -1,
     306,    42,    -1,    44,    45,    46,   408,    -1,   408,    -1,
      -1,   317,    -1,    -1,     6,     7,   322,   408,   408,   408,
      61,    13,    -1,   408,   214,   408,   216,    -1,   218,   408,
      -1,    -1,    -1,    -1,    -1,     6,     7,    -1,   228,    80,
      -1,    -1,    13,   349,     6,     7,    -1,    -1,    89,    -1,
      91,    13,    -1,    16,    17,    18,    19,    20,    -1,    -1,
      -1,   102,   368,    -1,   370,    -1,    -1,   108,    -1,    -1,
      -1,   261,    -1,   379,    66,   381,    68,    46,    -1,    -1,
      72,    -1,     0,     1,    76,    54,    -1,    -1,     6,    -1,
      -1,    -1,    10,    62,    63,    66,    -1,    68,   404,    -1,
     406,    72,    -1,   409,    66,    76,    68,    -1,    -1,    78,
      72,   301,    74,    -1,    76,    78,    79,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      99,    49,    50,    -1,    52,    53,   326,    -1,    -1,    -1,
      -1,    -1,    -1,   184,   113,   114,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    -1,   196,   197,   198,    -1,    -1,
     201,   202,    -1,   204,    -1,    -1,   135,    -1,     1,    -1,
      -1,    -1,    -1,     6,   364,    -1,   366,    10,    16,    17,
      18,    19,    20,   152,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,   382,    -1,    -1,    -1,    34,    35,   388,    -1,
      -1,   242,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,
      -1,    -1,   402,    -1,    -1,    -1,    49,    50,   408,    52,
      53,    -1,   412,    -1,    -1,    -1,    -1,    -1,    -1,   198,
      -1,    -1,    -1,   202,    -1,    68,    69,    70,    71,    -1,
      78,    79,   211,    -1,    -1,    -1,   215,    -1,    -1,    -1,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      -1,    12,    -1,    14,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    23,    -1,    -1,   244,    27,   246,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   261,    -1,    -1,    -1,    47,    -1,    -1,    50,
      -1,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      61,    62,    63,    64,    65,    -1,    67,    68,   359,    70,
      71,    72,    -1,    74,    75,    76,    -1,    78,    -1,    -1,
      -1,    -1,     1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    10,    -1,    12,    -1,    14,    -1,    -1,    -1,    -1,
      19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    27,    -1,
      -1,    16,    17,    18,    19,    20,    -1,    22,    23,    -1,
      -1,   340,    -1,   342,    -1,    -1,    -1,    -1,    47,    34,
      35,    50,   351,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    63,    64,    65,    -1,    67,    68,
      -1,    70,    71,    72,    -1,    74,    75,    76,     1,    78,
       3,     4,     5,     6,     7,    -1,     9,    10,    -1,    12,
      -1,    14,    -1,    78,    79,    -1,    19,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    27,    -1,    -1,    16,    17,    18,
      19,    20,    -1,    22,    23,    24,    -1,    -1,    -1,    28,
      29,    30,    31,    -1,    47,    34,    35,    50,    -1,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      63,    64,    65,    -1,    67,    68,    -1,    70,    71,    72,
      -1,    74,    -1,    76,    -1,    78,     3,     4,     5,     6,
       7,    -1,     9,    -1,    -1,    12,    -1,    14,    -1,    78,
      79,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,    -1,     9,    -1,    -1,    12,    -1,    14,
      47,    -1,    -1,    -1,    19,    -1,    -1,    54,    23,    56,
      57,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    -1,    -1,    76,
      -1,    78,    47,    -1,     3,     4,     5,     6,     7,    54,
       9,    56,    57,    12,    -1,    14,    -1,    -1,    -1,    -1,
      19,    -1,    -1,    -1,    23,    -1,    -1,    72,    27,    -1,
      -1,    76,    -1,    78,    -1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    -1,    12,    -1,    14,    47,    -1,
      -1,    -1,    19,    -1,    -1,    54,    23,    56,    57,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,     1,
      -1,    -1,    -1,    72,     6,    -1,    -1,    76,    10,    78,
      47,    -1,     3,     4,     5,     6,     7,    54,     9,    56,
      -1,    12,    -1,    14,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    23,    -1,    -1,    72,    27,    -1,    -1,    76,
      -1,    78,    -1,    -1,    -1,    -1,    -1,    49,    50,    -1,
      52,    53,    -1,    -1,    -1,    -1,    47,    16,    17,    18,
      19,    20,    -1,    54,    23,    56,    68,    69,    70,    71,
      -1,    -1,    -1,    75,    -1,    34,    35,    -1,    -1,    -1,
       8,    72,    -1,    -1,    -1,    76,    -1,    78,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    43,    44,    45,    46,    78,
      79,    16,    17,    18,    19,    20,    -1,    22,    23,    24,
      25,    26,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,     8,    -1,    74,    -1,    -1,    -1,
      78,    79,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    43,
      44,    45,    46,    78,    79,    16,    17,    18,    19,    20,
      -1,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    77,    78,    79,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    45,    46,    78,    79,    16,
      17,    18,    19,    20,    -1,    22,    23,    24,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,     8,    73,    10,    -1,    -1,    -1,    78,    79,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    43,    44,    45,
      46,    78,    79,    16,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    -1,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    -1,    78,    79,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    46,    78,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       8,    73,    -1,    -1,    -1,    -1,    78,    79,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    74,    -1,    -1,    -1,
      78,    79,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
      74,    10,    -1,    -1,    78,    79,    -1,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     8,    -1,    10,    -1,    -1,    -1,    78,
      79,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    10,
      -1,    -1,    -1,    78,    79,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     8,    -1,    -1,    11,    -1,    -1,    78,    79,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      -1,    78,    79,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    -1,    78,    79,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    10,    49,    50,    52,    53,    68,    69,
      70,    71,    82,    83,    85,   102,   119,   120,   121,   127,
     131,   132,   135,   137,   138,   139,    83,    85,   102,   121,
     127,   131,   132,   135,    82,    82,     5,    57,   136,    82,
      82,    82,     7,    13,    66,    68,    72,    76,    82,   114,
     115,   118,    10,    10,     8,    10,   138,     0,    10,    10,
      10,    72,    74,    74,   118,     3,     4,     5,     7,     9,
      12,    14,    19,    23,    27,    47,    54,    56,    72,    76,
      78,    82,    84,    86,    87,    92,    93,    94,   122,    72,
     114,    11,    74,    72,   114,   118,    94,     8,   118,     8,
     118,    73,    80,    82,    90,    91,   118,   119,    77,    94,
      72,    74,   100,    23,    57,    82,    94,   104,   105,   119,
     120,   118,   130,    51,    82,   119,   123,   124,   125,   126,
      75,    82,   116,   119,   125,   128,   129,    94,    82,    94,
      94,    94,    94,    94,    72,    72,    94,   120,    82,   101,
     118,    15,    72,     8,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    43,
      44,    45,    46,    74,    78,    79,    91,   118,    82,   133,
     134,    73,   101,   104,   104,   118,    66,    68,    48,     9,
      73,    80,    48,   118,    77,    82,   116,   117,     1,    10,
      55,    57,    59,    60,    61,    63,    64,    65,    67,    68,
      75,    82,    83,    85,    94,    95,    96,    97,    98,    99,
     100,   102,   106,   107,   110,   113,   127,   131,   132,   135,
     120,   104,    48,    73,    74,    82,    10,    75,    74,   114,
      10,    10,   129,    75,    94,     5,    73,    73,    48,    77,
      82,    23,    73,    88,    89,   104,   119,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,   138,   118,    82,
      74,     8,    48,    75,   100,     9,    73,    73,    91,    82,
      73,   118,    91,   118,    48,    73,    82,   104,    10,    10,
      94,    88,    94,   100,    10,    94,    57,    63,   111,   112,
      11,    10,    10,    10,    10,    99,    75,    10,   100,   130,
      74,   124,    74,   124,   130,    10,    73,    73,   101,   114,
     119,    48,    73,    75,   134,    94,   134,    82,   100,    80,
      73,   117,   100,    74,    10,   100,    64,    10,    94,    82,
      58,   126,    75,   124,    75,   100,    89,    58,    75,    73,
     118,    58,    62,   108,   109,    94,    94,   100,    11,   100,
     105,    75,    75,    74,   136,   100,    73,   100,   106,    94,
     109,    75,    10,    10,    58,    94,   103,   138,    11,    94,
     100,   112,    48,   100,    75,    99,   100,   103
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    87,    87,    87,
      87,    87,    88,    88,    88,    89,    89,    90,    91,    91,
      91,    91,    92,    92,    93,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    95,    96,    97,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      99,    99,   100,   100,   101,   101,   102,   102,   102,   103,
     103,   104,   104,   104,   104,   105,   105,   106,   106,   106,
     107,   108,   109,   109,   110,   111,   112,   112,   112,   113,
     113,   114,   114,   114,   114,   114,   115,   115,   116,   116,
     117,   117,   118,   118,   118,   118,   118,   118,   118,   119,
     119,   119,   120,   120,   120,   121,   121,   122,   123,   123,
     124,   124,   125,   125,   126,   127,   127,   128,   128,   128,
     128,   129,   129,   130,   130,   131,   132,   132,   133,   133,
     134,   134,   134,   135,   135,   136,   136,   136,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   138,   138,   139,
     139
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     4,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     2,     2,     1,     1,     3,     1,     1,     3,     3,
       1,     1,     4,     3,     4,     1,     3,     3,     2,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     3,     2,
       3,     2,     1,     1,     3,     5,     2,     2,     3,     2,
       2,     2,     2,     2,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     1,     3,     2,     3,     1,     6,     8,     5,     3,
       1,     1,     1,     2,     1,     5,     5,     3,     5,     5,
       7,     4,     2,     1,     5,     5,     3,     5,     5,     2,
       2,     5,     3,     4,     4,     2,     1,     7,     4,     1,
       3,     1,     1,     2,     4,     2,     3,     4,     2,     3,
       3,     2,     3,     4,     4,     3,     3,     5,     1,     1,
       3,     2,     5,     4,     1,     5,     8,     2,     3,     2,
       1,     2,     1,     3,     1,     3,     5,     4,     1,     3,
       3,     2,     1,     7,     5,     5,     9,     7,     1,     1,
       1,     1,     1,     2,     2,     2,     1,     2,     2,     2,
       2,     3,     3,     2,     2,     3,     1,     1,     2,     1,
       0
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
#line 141 "src/parser.y"
            {}
#line 1915 "src/gen_parser.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 141 "src/parser.y"
            {}
#line 1921 "src/gen_parser.c"
        break;

    case YYSYMBOL_STRING: /* STRING  */
#line 141 "src/parser.y"
            {}
#line 1927 "src/gen_parser.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 141 "src/parser.y"
            {}
#line 1933 "src/gen_parser.c"
        break;

    case YYSYMBOL_id: /* id  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1939 "src/gen_parser.c"
        break;

    case YYSYMBOL_var: /* var  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1945 "src/gen_parser.c"
        break;

    case YYSYMBOL_embed: /* embed  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1951 "src/gen_parser.c"
        break;

    case YYSYMBOL_import: /* import  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1957 "src/gen_parser.c"
        break;

    case YYSYMBOL_binary_op: /* binary_op  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1963 "src/gen_parser.c"
        break;

    case YYSYMBOL_unary_op: /* unary_op  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1969 "src/gen_parser.c"
        break;

    case YYSYMBOL_arg: /* arg  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1975 "src/gen_parser.c"
        break;

    case YYSYMBOL_arg_list: /* arg_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1981 "src/gen_parser.c"
        break;

    case YYSYMBOL_param_decl: /* param_decl  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1987 "src/gen_parser.c"
        break;

    case YYSYMBOL_decl_list: /* decl_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1993 "src/gen_parser.c"
        break;

    case YYSYMBOL_call: /* call  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1999 "src/gen_parser.c"
        break;

    case YYSYMBOL_defer: /* defer  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2005 "src/gen_parser.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2011 "src/gen_parser.c"
        break;

    case YYSYMBOL_while: /* while  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2017 "src/gen_parser.c"
        break;

    case YYSYMBOL_do_while: /* do_while  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2023 "src/gen_parser.c"
        break;

    case YYSYMBOL_goto: /* goto  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2029 "src/gen_parser.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2035 "src/gen_parser.c"
        break;

    case YYSYMBOL_statement_list: /* statement_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2041 "src/gen_parser.c"
        break;

    case YYSYMBOL_body: /* body  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2047 "src/gen_parser.c"
        break;

    case YYSYMBOL_macro_list: /* macro_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2053 "src/gen_parser.c"
        break;

    case YYSYMBOL_macro: /* macro  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2059 "src/gen_parser.c"
        break;

    case YYSYMBOL_expr_list: /* expr_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2065 "src/gen_parser.c"
        break;

    case YYSYMBOL_init_expr: /* init_expr  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2071 "src/gen_parser.c"
        break;

    case YYSYMBOL_expr_if: /* expr_if  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2077 "src/gen_parser.c"
        break;

    case YYSYMBOL_if: /* if  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2083 "src/gen_parser.c"
        break;

    case YYSYMBOL_for: /* for  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2089 "src/gen_parser.c"
        break;

    case YYSYMBOL_case: /* case  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2095 "src/gen_parser.c"
        break;

    case YYSYMBOL_case_list: /* case_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2101 "src/gen_parser.c"
        break;

    case YYSYMBOL_switch: /* switch  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2107 "src/gen_parser.c"
        break;

    case YYSYMBOL_const_for: /* const_for  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2113 "src/gen_parser.c"
        break;

    case YYSYMBOL_const_if: /* const_if  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2119 "src/gen_parser.c"
        break;

    case YYSYMBOL_const: /* const  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2125 "src/gen_parser.c"
        break;

    case YYSYMBOL_func_sign: /* func_sign  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2131 "src/gen_parser.c"
        break;

    case YYSYMBOL_variadic_sign: /* variadic_sign  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2137 "src/gen_parser.c"
        break;

    case YYSYMBOL_impl: /* impl  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2143 "src/gen_parser.c"
        break;

    case YYSYMBOL_impl_list: /* impl_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2149 "src/gen_parser.c"
        break;

    case YYSYMBOL_type: /* type  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2155 "src/gen_parser.c"
        break;

    case YYSYMBOL_var_decl: /* var_decl  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2161 "src/gen_parser.c"
        break;

    case YYSYMBOL_var_init: /* var_init  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2167 "src/gen_parser.c"
        break;

    case YYSYMBOL_proc: /* proc  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2173 "src/gen_parser.c"
        break;

    case YYSYMBOL_lambda: /* lambda  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2179 "src/gen_parser.c"
        break;

    case YYSYMBOL_union_elem: /* union_elem  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2185 "src/gen_parser.c"
        break;

    case YYSYMBOL_union_list: /* union_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2191 "src/gen_parser.c"
        break;

    case YYSYMBOL_union: /* union  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2197 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct_list: /* struct_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2203 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct: /* struct  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2209 "src/gen_parser.c"
        break;

    case YYSYMBOL_template_elem: /* template_elem  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2215 "src/gen_parser.c"
        break;

    case YYSYMBOL_template_list: /* template_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2221 "src/gen_parser.c"
        break;

    case YYSYMBOL_type_list: /* type_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2227 "src/gen_parser.c"
        break;

    case YYSYMBOL_type_alias: /* type_alias  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2233 "src/gen_parser.c"
        break;

    case YYSYMBOL_type_template: /* type_template  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2239 "src/gen_parser.c"
        break;

    case YYSYMBOL_enum_val: /* enum_val  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2245 "src/gen_parser.c"
        break;

    case YYSYMBOL_enum_list: /* enum_list  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2251 "src/gen_parser.c"
        break;

    case YYSYMBOL_enum: /* enum  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2257 "src/gen_parser.c"
        break;

    case YYSYMBOL_top_if: /* top_if  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2263 "src/gen_parser.c"
        break;

    case YYSYMBOL_top: /* top  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2269 "src/gen_parser.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 142 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2275 "src/gen_parser.c"
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
#line 146 "src/parser.y"
       {
		(yyval.node) = gen_id(strdup((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 2584 "src/gen_parser.c"
    break;

  case 3: /* var: var_decl  */
#line 152 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2590 "src/gen_parser.c"
    break;

  case 4: /* var: var_init  */
#line 153 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2596 "src/gen_parser.c"
    break;

  case 5: /* embed: "embed" "(" STRING ")"  */
#line 156 "src/parser.y"
                              { (yyval.node) = gen_embed(clone_string((yyvsp[-1].str)));  }
#line 2602 "src/gen_parser.c"
    break;

  case 6: /* import: "import" STRING  */
#line 159 "src/parser.y"
                        { (yyval.node) = gen_import(clone_string((yyvsp[0].str)));  }
#line 2608 "src/gen_parser.c"
    break;

  case 7: /* binary_op: expr "=" expr  */
#line 162 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2614 "src/gen_parser.c"
    break;

  case 8: /* binary_op: expr "+" expr  */
#line 163 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2620 "src/gen_parser.c"
    break;

  case 9: /* binary_op: expr "-" expr  */
#line 164 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2626 "src/gen_parser.c"
    break;

  case 10: /* binary_op: expr "*" expr  */
#line 165 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2632 "src/gen_parser.c"
    break;

  case 11: /* binary_op: expr "/" expr  */
#line 166 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2638 "src/gen_parser.c"
    break;

  case 12: /* binary_op: expr "%" expr  */
#line 167 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2644 "src/gen_parser.c"
    break;

  case 13: /* binary_op: expr "^" expr  */
#line 168 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2650 "src/gen_parser.c"
    break;

  case 14: /* binary_op: expr "^^" expr  */
#line 169 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_POW, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2656 "src/gen_parser.c"
    break;

  case 15: /* binary_op: expr "&" expr  */
#line 170 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2662 "src/gen_parser.c"
    break;

  case 16: /* binary_op: expr "&&" expr  */
#line 171 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LAND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2668 "src/gen_parser.c"
    break;

  case 17: /* binary_op: expr "|" expr  */
#line 172 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2674 "src/gen_parser.c"
    break;

  case 18: /* binary_op: expr "||" expr  */
#line 173 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2680 "src/gen_parser.c"
    break;

  case 19: /* binary_op: expr "<<" expr  */
#line 174 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2686 "src/gen_parser.c"
    break;

  case 20: /* binary_op: expr ">>" expr  */
#line 175 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2692 "src/gen_parser.c"
    break;

  case 21: /* binary_op: expr "+=" expr  */
#line 176 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2698 "src/gen_parser.c"
    break;

  case 22: /* binary_op: expr "-=" expr  */
#line 177 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2704 "src/gen_parser.c"
    break;

  case 23: /* binary_op: expr "*=" expr  */
#line 178 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2710 "src/gen_parser.c"
    break;

  case 24: /* binary_op: expr "/=" expr  */
#line 179 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2716 "src/gen_parser.c"
    break;

  case 25: /* binary_op: expr "%=" expr  */
#line 180 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2722 "src/gen_parser.c"
    break;

  case 26: /* binary_op: expr "&=" expr  */
#line 181 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2728 "src/gen_parser.c"
    break;

  case 27: /* binary_op: expr "|=" expr  */
#line 182 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2734 "src/gen_parser.c"
    break;

  case 28: /* binary_op: expr "^=" expr  */
#line 183 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2740 "src/gen_parser.c"
    break;

  case 29: /* binary_op: expr "<<=" expr  */
#line 184 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2748 "src/gen_parser.c"
    break;

  case 30: /* binary_op: expr ">>=" expr  */
#line 187 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2756 "src/gen_parser.c"
    break;

  case 31: /* binary_op: expr "<" expr  */
#line 190 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_LT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2762 "src/gen_parser.c"
    break;

  case 32: /* binary_op: expr ">" expr  */
#line 191 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_GT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2768 "src/gen_parser.c"
    break;

  case 33: /* binary_op: expr "<=" expr  */
#line 192 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2774 "src/gen_parser.c"
    break;

  case 34: /* binary_op: expr ">=" expr  */
#line 193 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_GE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2780 "src/gen_parser.c"
    break;

  case 35: /* binary_op: expr "!=" expr  */
#line 194 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_NE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2786 "src/gen_parser.c"
    break;

  case 36: /* binary_op: expr "==" expr  */
#line 195 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_EQ, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2792 "src/gen_parser.c"
    break;

  case 37: /* unary_op: "-" expr  */
#line 198 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NEG, (yyvsp[0].node));  }
#line 2798 "src/gen_parser.c"
    break;

  case 38: /* unary_op: "!" expr  */
#line 199 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_LNOT, (yyvsp[0].node));  }
#line 2804 "src/gen_parser.c"
    break;

  case 39: /* unary_op: "&" expr  */
#line 200 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 2810 "src/gen_parser.c"
    break;

  case 40: /* unary_op: "'" expr  */
#line 201 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_DEREF, (yyvsp[0].node));  }
#line 2816 "src/gen_parser.c"
    break;

  case 41: /* unary_op: "~" expr  */
#line 202 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NOT, (yyvsp[0].node));  }
#line 2822 "src/gen_parser.c"
    break;

  case 42: /* arg: "&" var_decl  */
#line 205 "src/parser.y"
                  { (yyval.node) = gen_unop(SQUOTE, (yyvsp[0].node));  }
#line 2828 "src/gen_parser.c"
    break;

  case 43: /* arg: var_decl  */
#line 206 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2834 "src/gen_parser.c"
    break;

  case 44: /* arg: init_expr  */
#line 207 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2840 "src/gen_parser.c"
    break;

  case 45: /* arg_list: arg "," arg_list  */
#line 210 "src/parser.y"
                           { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2846 "src/gen_parser.c"
    break;

  case 46: /* arg_list: arg  */
#line 211 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2852 "src/gen_parser.c"
    break;

  case 47: /* param_decl: type  */
#line 214 "src/parser.y"
                 { (yyval.node) = gen_var(NULL, (yyvsp[0].node), NULL);  }
#line 2858 "src/gen_parser.c"
    break;

  case 48: /* decl_list: var_decl "," decl_list  */
#line 216 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2864 "src/gen_parser.c"
    break;

  case 49: /* decl_list: param_decl "," decl_list  */
#line 217 "src/parser.y"
                                   { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2870 "src/gen_parser.c"
    break;

  case 50: /* decl_list: var_decl  */
#line 218 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2876 "src/gen_parser.c"
    break;

  case 51: /* decl_list: param_decl  */
#line 219 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2882 "src/gen_parser.c"
    break;

  case 52: /* call: id "(" arg_list ")"  */
#line 223 "src/parser.y"
                          { (yyval.node) = gen_call((yyvsp[-3].node), (yyvsp[-1].node));  }
#line 2888 "src/gen_parser.c"
    break;

  case 53: /* call: id "(" ")"  */
#line 224 "src/parser.y"
                     { (yyval.node) = gen_call((yyvsp[-2].node), NULL);  }
#line 2894 "src/gen_parser.c"
    break;

  case 54: /* defer: "defer" "(" expr ")"  */
#line 227 "src/parser.y"
                            { (yyval.node) = gen_defer((yyvsp[-1].node));  }
#line 2900 "src/gen_parser.c"
    break;

  case 55: /* expr: id  */
#line 231 "src/parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 2906 "src/gen_parser.c"
    break;

  case 56: /* expr: expr "." id  */
#line 232 "src/parser.y"
                      { (yyval.node) = gen_dot((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2912 "src/gen_parser.c"
    break;

  case 57: /* expr: id "##" id  */
#line 233 "src/parser.y"
                     { (yyval.node) = gen_paste((yyvsp[-2].node), (yyvsp[0].node));  }
#line 2918 "src/gen_parser.c"
    break;

  case 58: /* expr: "..." id  */
#line 234 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2924 "src/gen_parser.c"
    break;

  case 59: /* expr: "@"  */
#line 235 "src/parser.y"
              { (yyval.node) = gen_last();  }
#line 2930 "src/gen_parser.c"
    break;

  case 60: /* expr: INT  */
#line 236 "src/parser.y"
              { (yyval.node) = gen_int((yyvsp[0].integer)); (yyval.node)->loc = to_src_loc(&yylloc); }
#line 2936 "src/gen_parser.c"
    break;

  case 61: /* expr: FLOAT  */
#line 237 "src/parser.y"
                { (yyval.node) = gen_float((yyvsp[0].dbl)); (yyval.node)->loc = to_src_loc(&yylloc);  }
#line 2942 "src/gen_parser.c"
    break;

  case 62: /* expr: STRING  */
#line 238 "src/parser.y"
                 {
		(yyval.node) = gen_string(clone_string((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 2951 "src/gen_parser.c"
    break;

  case 63: /* expr: "(" expr ")"  */
#line 242 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 2957 "src/gen_parser.c"
    break;

  case 64: /* expr: call  */
#line 243 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2963 "src/gen_parser.c"
    break;

  case 65: /* expr: defer  */
#line 244 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2969 "src/gen_parser.c"
    break;

  case 66: /* expr: binary_op  */
#line 245 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2975 "src/gen_parser.c"
    break;

  case 67: /* expr: unary_op  */
#line 246 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2981 "src/gen_parser.c"
    break;

  case 68: /* expr: "(" var_init ")"  */
#line 247 "src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 2987 "src/gen_parser.c"
    break;

  case 69: /* expr: "sizeof" expr  */
#line 248 "src/parser.y"
                        { (yyval.node) = gen_sizeof((yyvsp[0].node)); }
#line 2993 "src/gen_parser.c"
    break;

  case 70: /* expr: expr "as" type  */
#line 249 "src/parser.y"
                         { (yyval.node) = gen_cast((yyvsp[-2].node), (yyvsp[0].node));  }
#line 2999 "src/gen_parser.c"
    break;

  case 71: /* expr: "as" type  */
#line 250 "src/parser.y"
                    { (yyval.node) = gen_as((yyvsp[0].node)); }
#line 3005 "src/gen_parser.c"
    break;

  case 72: /* expr: embed  */
#line 251 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3011 "src/gen_parser.c"
    break;

  case 73: /* expr: lambda  */
#line 252 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3017 "src/gen_parser.c"
    break;

  case 74: /* while: "while" expr body  */
#line 255 "src/parser.y"
                         { (yyval.node) = gen_while((yyvsp[-1].node), (yyvsp[0].node));  }
#line 3023 "src/gen_parser.c"
    break;

  case 75: /* do_while: "do" body "while" expr ";"  */
#line 258 "src/parser.y"
                                     {
		(yyval.node) = gen_while((yyvsp[-3].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_DELAYED);
	}
#line 3032 "src/gen_parser.c"
    break;

  case 76: /* goto: "goto" id  */
#line 264 "src/parser.y"
                { (yyval.node) = gen_goto(gen_label((yyvsp[0].node)));  }
#line 3038 "src/gen_parser.c"
    break;

  case 77: /* statement: expr ";"  */
#line 266 "src/parser.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 3044 "src/gen_parser.c"
    break;

  case 78: /* statement: "return" expr ";"  */
#line 267 "src/parser.y"
                            { (yyval.node) = gen_return((yyvsp[-1].node));  }
#line 3050 "src/gen_parser.c"
    break;

  case 79: /* statement: "return" ";"  */
#line 268 "src/parser.y"
                       { (yyval.node) = gen_return(NULL); }
#line 3056 "src/gen_parser.c"
    break;

  case 80: /* statement: "break" ";"  */
#line 269 "src/parser.y"
                      { (yyval.node) = gen_ctrl(AST_CTRL_BREAK, to_src_loc(&yylloc)); }
#line 3062 "src/gen_parser.c"
    break;

  case 81: /* statement: "continue" ";"  */
#line 270 "src/parser.y"
                         { (yyval.node) = gen_ctrl(AST_CTRL_CONTINUE,
	to_src_loc(&yylloc));  }
#line 3069 "src/gen_parser.c"
    break;

  case 82: /* statement: import ";"  */
#line 272 "src/parser.y"
                     { (yyval.node) = (yyvsp[-1].node); }
#line 3075 "src/gen_parser.c"
    break;

  case 83: /* statement: var ";"  */
#line 273 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3081 "src/gen_parser.c"
    break;

  case 84: /* statement: if  */
#line 274 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3087 "src/gen_parser.c"
    break;

  case 85: /* statement: goto ";"  */
#line 275 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3093 "src/gen_parser.c"
    break;

  case 86: /* statement: id ":"  */
#line 276 "src/parser.y"
                 { (yyval.node) = gen_label((yyvsp[-1].node));  }
#line 3099 "src/gen_parser.c"
    break;

  case 87: /* statement: for  */
#line 277 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3105 "src/gen_parser.c"
    break;

  case 88: /* statement: const  */
#line 278 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3111 "src/gen_parser.c"
    break;

  case 89: /* statement: while  */
#line 279 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3117 "src/gen_parser.c"
    break;

  case 90: /* statement: do_while  */
#line 280 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3123 "src/gen_parser.c"
    break;

  case 91: /* statement: switch  */
#line 281 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3129 "src/gen_parser.c"
    break;

  case 92: /* statement: macro  */
#line 282 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3135 "src/gen_parser.c"
    break;

  case 93: /* statement: struct  */
#line 283 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3141 "src/gen_parser.c"
    break;

  case 94: /* statement: type_alias ";"  */
#line 284 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3147 "src/gen_parser.c"
    break;

  case 95: /* statement: type_template  */
#line 285 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3153 "src/gen_parser.c"
    break;

  case 96: /* statement: enum  */
#line 286 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3159 "src/gen_parser.c"
    break;

  case 97: /* statement: body  */
#line 287 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3165 "src/gen_parser.c"
    break;

  case 98: /* statement: ";"  */
#line 288 "src/parser.y"
              { (yyval.node) = gen_empty();  }
#line 3171 "src/gen_parser.c"
    break;

  case 99: /* statement: error  */
#line 289 "src/parser.y"
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
#line 3190 "src/gen_parser.c"
    break;

  case 100: /* statement_list: statement statement_list  */
#line 305 "src/parser.y"
                                         { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3196 "src/gen_parser.c"
    break;

  case 101: /* statement_list: statement  */
#line 306 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3202 "src/gen_parser.c"
    break;

  case 102: /* body: "{" statement_list "}"  */
#line 309 "src/parser.y"
                             { (yyval.node) = gen_block((yyvsp[-1].node));  }
#line 3208 "src/gen_parser.c"
    break;

  case 103: /* body: "{" "}"  */
#line 310 "src/parser.y"
                  { (yyval.node) = gen_block(gen_empty());  }
#line 3214 "src/gen_parser.c"
    break;

  case 104: /* macro_list: id "," macro_list  */
#line 313 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 3220 "src/gen_parser.c"
    break;

  case 105: /* macro_list: id  */
#line 314 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3226 "src/gen_parser.c"
    break;

  case 106: /* macro: "define" id "(" macro_list ")" body  */
#line 317 "src/parser.y"
                                           {
		(yyval.node) = gen_macro((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3235 "src/gen_parser.c"
    break;

  case 107: /* macro: "define" id "(" macro_list "..." id ")" body  */
#line 321 "src/parser.y"
                                                       {
		/* TODO: the location data of the variadic ID is way off */
		ast_append((yyvsp[-4].node), (yyvsp[-2].node));
		(yyval.node) = gen_macro((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3247 "src/gen_parser.c"
    break;

  case 108: /* macro: "define" id "(" ")" body  */
#line 328 "src/parser.y"
                                   {
		(yyval.node) = gen_macro((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3256 "src/gen_parser.c"
    break;

  case 109: /* expr_list: expr "," expr_list  */
#line 334 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3262 "src/gen_parser.c"
    break;

  case 110: /* expr_list: expr  */
#line 335 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3268 "src/gen_parser.c"
    break;

  case 111: /* init_expr: expr  */
#line 338 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3274 "src/gen_parser.c"
    break;

  case 112: /* init_expr: var_init  */
#line 339 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3280 "src/gen_parser.c"
    break;

  case 113: /* init_expr: "&" var_init  */
#line 340 "src/parser.y"
                       { (yyval.node) = gen_unop(AND, (yyvsp[0].node));  }
#line 3286 "src/gen_parser.c"
    break;

  case 114: /* init_expr: expr_if  */
#line 341 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 3292 "src/gen_parser.c"
    break;

  case 115: /* expr_if: "if" init_expr body "else" body  */
#line 344 "src/parser.y"
                                         { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3298 "src/gen_parser.c"
    break;

  case 116: /* expr_if: "if" init_expr body "else" expr_if  */
#line 345 "src/parser.y"
                                            { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3304 "src/gen_parser.c"
    break;

  case 117: /* if: "if" init_expr body  */
#line 348 "src/parser.y"
                        { (yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3310 "src/gen_parser.c"
    break;

  case 118: /* if: "if" init_expr body "else" body  */
#line 349 "src/parser.y"
                                          { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3316 "src/gen_parser.c"
    break;

  case 119: /* if: "if" init_expr body "else" if  */
#line 350 "src/parser.y"
                                        { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3322 "src/gen_parser.c"
    break;

  case 120: /* for: "for" arg ";" expr ";" expr body  */
#line 353 "src/parser.y"
                                      { (yyval.node) = gen_for((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 3329 "src/gen_parser.c"
    break;

  case 121: /* case: "case" expr ":" statement_list  */
#line 357 "src/parser.y"
                                     { (yyval.node) = gen_case((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3335 "src/gen_parser.c"
    break;

  case 122: /* case_list: case case_list  */
#line 360 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3341 "src/gen_parser.c"
    break;

  case 123: /* case_list: case  */
#line 361 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3347 "src/gen_parser.c"
    break;

  case 124: /* switch: "switch" expr "{" case_list "}"  */
#line 364 "src/parser.y"
                                        { (yyval.node) = gen_switch((yyvsp[-3].node), (yyvsp[-1].node));  }
#line 3353 "src/gen_parser.c"
    break;

  case 125: /* const_for: "for" id ":" expr_list body  */
#line 367 "src/parser.y"
                                       {
		/* TODO: should id be a separate rule? */
		(yyval.node) = gen_for((yyvsp[-3].node), NULL, (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3363 "src/gen_parser.c"
    break;

  case 126: /* const_if: "if" expr body  */
#line 374 "src/parser.y"
                         {
		(yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3372 "src/gen_parser.c"
    break;

  case 127: /* const_if: "if" expr body "else" body  */
#line 378 "src/parser.y"
                                     {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3382 "src/gen_parser.c"
    break;

  case 128: /* const_if: "if" expr body "else" const_if  */
#line 383 "src/parser.y"
                                         {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
	}
#line 3391 "src/gen_parser.c"
    break;

  case 129: /* const: "const" const_if  */
#line 391 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST);
      }
#line 3398 "src/gen_parser.c"
    break;

  case 130: /* const: "const" const_for  */
#line 393 "src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST);
	 }
#line 3405 "src/gen_parser.c"
    break;

  case 131: /* func_sign: "(" decl_list "=>" type ")"  */
#line 397 "src/parser.y"
                                       {
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 3413 "src/gen_parser.c"
    break;

  case 132: /* func_sign: "(" decl_list ")"  */
#line 400 "src/parser.y"
                            { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-1].node), NULL);
	 }
#line 3420 "src/gen_parser.c"
    break;

  case 133: /* func_sign: "(" decl_list "=>" ")"  */
#line 402 "src/parser.y"
                                 { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-2].node), NULL);
	 }
#line 3427 "src/gen_parser.c"
    break;

  case 134: /* func_sign: "(" "=>" type ")"  */
#line 404 "src/parser.y"
                            { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, (yyvsp[-1].node));
	 }
#line 3434 "src/gen_parser.c"
    break;

  case 135: /* func_sign: "(" ")"  */
#line 406 "src/parser.y"
                  { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, NULL);
	 }
#line 3441 "src/gen_parser.c"
    break;

  case 136: /* variadic_sign: func_sign  */
#line 410 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3447 "src/gen_parser.c"
    break;

  case 137: /* variadic_sign: "(" decl_list "..." id "=>" type ")"  */
#line 411 "src/parser.y"
                                               {
		ast_append((yyvsp[-5].node), (yyvsp[-3].node));
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
	}
#line 3457 "src/gen_parser.c"
    break;

  case 138: /* impl: id "{" type_list "}"  */
#line 418 "src/parser.y"
                           { (yyval.node) = gen_type(AST_TYPE_IMPL, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
     }
#line 3464 "src/gen_parser.c"
    break;

  case 139: /* impl: id  */
#line 420 "src/parser.y"
             { (yyval.node) = gen_type(AST_TYPE_IMPL, (yyvsp[0].node), NULL, NULL);  }
#line 3470 "src/gen_parser.c"
    break;

  case 140: /* impl_list: impl "," impl_list  */
#line 423 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node);}
#line 3476 "src/gen_parser.c"
    break;

  case 141: /* impl_list: impl  */
#line 424 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3482 "src/gen_parser.c"
    break;

  case 142: /* type: id  */
#line 427 "src/parser.y"
         { (yyval.node) = gen_type(AST_TYPE_ID, (yyvsp[0].node), NULL, NULL); }
#line 3488 "src/gen_parser.c"
    break;

  case 143: /* type: "'" func_sign  */
#line 428 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->next = (yyvsp[0].node);
	}
#line 3497 "src/gen_parser.c"
    break;

  case 144: /* type: id "(" impl_list ")"  */
#line 432 "src/parser.y"
                               {
		(yyval.node) = gen_type(AST_TYPE_STRUCT, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
	}
#line 3505 "src/gen_parser.c"
    break;

  case 145: /* type: "'" type  */
#line 435 "src/parser.y"
                   {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3514 "src/gen_parser.c"
    break;

  case 146: /* type: "[" "]" type  */
#line 439 "src/parser.y"
                       {
		(yyval.node) = gen_type(AST_TYPE_ARR, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3523 "src/gen_parser.c"
    break;

  case 147: /* type: "[" expr "]" type  */
#line 443 "src/parser.y"
                            {
		(yyval.node) = gen_type(AST_TYPE_ARR, NULL, (yyvsp[-2].node), NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3532 "src/gen_parser.c"
    break;

  case 148: /* type: "typeof" expr  */
#line 447 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_TYPEOF, NULL, (yyvsp[0].node), NULL);
	}
#line 3540 "src/gen_parser.c"
    break;

  case 149: /* var_decl: id "mut" type  */
#line 452 "src/parser.y"
                        {
		(yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_MUTABLE);
	}
#line 3549 "src/gen_parser.c"
    break;

  case 150: /* var_decl: id "const" type  */
#line 456 "src/parser.y"
                          { (yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);  }
#line 3555 "src/gen_parser.c"
    break;

  case 151: /* var_decl: id type  */
#line 457 "src/parser.y"
                  { (yyval.node) = gen_var((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3561 "src/gen_parser.c"
    break;

  case 152: /* var_init: var_decl "=" init_expr  */
#line 460 "src/parser.y"
                                 { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->_var.init = (yyvsp[0].node); }
#line 3567 "src/gen_parser.c"
    break;

  case 153: /* var_init: id "mut" "=" init_expr  */
#line 461 "src/parser.y"
                                 {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED | AST_FLAG_MUTABLE);
	}
#line 3576 "src/gen_parser.c"
    break;

  case 154: /* var_init: id "const" "=" init_expr  */
#line 465 "src/parser.y"
                                   {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 3585 "src/gen_parser.c"
    break;

  case 155: /* proc: id variadic_sign body  */
#line 471 "src/parser.y"
                            {
		(yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), (yyvsp[-1].node)->flags);
	}
#line 3594 "src/gen_parser.c"
    break;

  case 156: /* proc: "extern" id func_sign  */
#line 475 "src/parser.y"
                                {
		(yyval.node) = gen_proc((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_EXTERN);
	}
#line 3603 "src/gen_parser.c"
    break;

  case 157: /* lambda: "[" macro_list "]" func_sign body  */
#line 481 "src/parser.y"
                                          { (yyval.node) = gen_lambda((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
       }
#line 3610 "src/gen_parser.c"
    break;

  case 158: /* union_elem: union  */
#line 485 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 3616 "src/gen_parser.c"
    break;

  case 159: /* union_elem: var_decl  */
#line 486 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3622 "src/gen_parser.c"
    break;

  case 160: /* union_list: union_elem ";" union_list  */
#line 489 "src/parser.y"
                                      { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3628 "src/gen_parser.c"
    break;

  case 161: /* union_list: union_elem ";"  */
#line 490 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3634 "src/gen_parser.c"
    break;

  case 162: /* union: "union" id "{" union_list "}"  */
#line 493 "src/parser.y"
                                     {
		(yyval.node) = gen_type(AST_TYPE_UNION, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
	}
#line 3642 "src/gen_parser.c"
    break;

  case 163: /* union: "union" "{" union_list "}"  */
#line 496 "src/parser.y"
                                     {
		(yyval.node) = gen_type(AST_TYPE_UNION, NULL, (yyvsp[-1].node), NULL);  }
#line 3649 "src/gen_parser.c"
    break;

  case 164: /* struct_list: union_list  */
#line 501 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3655 "src/gen_parser.c"
    break;

  case 165: /* struct: "struct" id "{" struct_list "}"  */
#line 504 "src/parser.y"
                                        {
		(yyval.node) = gen_struct((yyvsp[-3].node), NULL, (yyvsp[-1].node));
	}
#line 3663 "src/gen_parser.c"
    break;

  case 166: /* struct: "struct" id "(" type_list ")" "{" struct_list "}"  */
#line 507 "src/parser.y"
                                                            {
		(yyval.node) = gen_struct((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
	}
#line 3671 "src/gen_parser.c"
    break;

  case 167: /* template_elem: impl ";"  */
#line 512 "src/parser.y"
                        { (yyval.node) = (yyvsp[-1].node); }
#line 3677 "src/gen_parser.c"
    break;

  case 168: /* template_elem: id func_sign ";"  */
#line 513 "src/parser.y"
                           { (yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), NULL);  }
#line 3683 "src/gen_parser.c"
    break;

  case 169: /* template_elem: var_decl ";"  */
#line 514 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3689 "src/gen_parser.c"
    break;

  case 170: /* template_elem: union  */
#line 515 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3695 "src/gen_parser.c"
    break;

  case 171: /* template_list: template_elem template_list  */
#line 518 "src/parser.y"
                                           { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3701 "src/gen_parser.c"
    break;

  case 172: /* template_list: template_elem  */
#line 519 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3707 "src/gen_parser.c"
    break;

  case 173: /* type_list: type "," type_list  */
#line 522 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3713 "src/gen_parser.c"
    break;

  case 174: /* type_list: type  */
#line 523 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3719 "src/gen_parser.c"
    break;

  case 175: /* type_alias: "type" id type  */
#line 526 "src/parser.y"
                           { (yyval.node) = gen_alias((yyvsp[-1].node), (yyvsp[0].node));  }
#line 3725 "src/gen_parser.c"
    break;

  case 176: /* type_template: "type" id "{" template_list "}"  */
#line 531 "src/parser.y"
                                               {
		(yyval.node) = gen_template((yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 3733 "src/gen_parser.c"
    break;

  case 177: /* type_template: "type" id "{" "}"  */
#line 534 "src/parser.y"
                            {
		/* should match anything, but doesn't implement anything */
		(yyval.node) = gen_template((yyvsp[-2].node), NULL);
	}
#line 3742 "src/gen_parser.c"
    break;

  case 178: /* enum_val: id  */
#line 540 "src/parser.y"
             { (yyval.node) = gen_val((yyvsp[0].node), gen_int(0));  }
#line 3748 "src/gen_parser.c"
    break;

  case 179: /* enum_val: id "=" expr  */
#line 541 "src/parser.y"
                      { (yyval.node) = gen_val((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3754 "src/gen_parser.c"
    break;

  case 180: /* enum_list: enum_val "," enum_list  */
#line 544 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3760 "src/gen_parser.c"
    break;

  case 181: /* enum_list: enum_val ","  */
#line 545 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3766 "src/gen_parser.c"
    break;

  case 182: /* enum_list: enum_val  */
#line 546 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3772 "src/gen_parser.c"
    break;

  case 183: /* enum: "enum" id ":" type "{" enum_list "}"  */
#line 549 "src/parser.y"
                                           { (yyval.node) = gen_enum((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3778 "src/gen_parser.c"
    break;

  case 184: /* enum: "enum" id "{" enum_list "}"  */
#line 550 "src/parser.y"
                                      {
		(yyval.node) = gen_enum((yyvsp[-3].node), NULL, (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 3787 "src/gen_parser.c"
    break;

  case 185: /* top_if: "if" expr "{" unit "}"  */
#line 556 "src/parser.y"
                               {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-1].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3796 "src/gen_parser.c"
    break;

  case 186: /* top_if: "if" expr "{" unit "}" "else" "{" unit "}"  */
#line 560 "src/parser.y"
                                                     {
		(yyval.node) = gen_if((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3805 "src/gen_parser.c"
    break;

  case 187: /* top_if: "if" expr "{" unit "}" "else" top_if  */
#line 564 "src/parser.y"
                                               {
		(yyval.node) = gen_if((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3814 "src/gen_parser.c"
    break;

  case 188: /* top: ";"  */
#line 572 "src/parser.y"
         { (yyval.node) = gen_empty(); }
#line 3820 "src/gen_parser.c"
    break;

  case 189: /* top: enum  */
#line 573 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3826 "src/gen_parser.c"
    break;

  case 190: /* top: proc  */
#line 574 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3832 "src/gen_parser.c"
    break;

  case 191: /* top: struct  */
#line 575 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3838 "src/gen_parser.c"
    break;

  case 192: /* top: macro  */
#line 576 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3844 "src/gen_parser.c"
    break;

  case 193: /* top: "const" top_if  */
#line 577 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 3850 "src/gen_parser.c"
    break;

  case 194: /* top: import ";"  */
#line 578 "src/parser.y"
                     { (yyval.node) = (yyvsp[-1].node); }
#line 3856 "src/gen_parser.c"
    break;

  case 195: /* top: type_alias ";"  */
#line 579 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3862 "src/gen_parser.c"
    break;

  case 196: /* top: type_template  */
#line 580 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3868 "src/gen_parser.c"
    break;

  case 197: /* top: "pub" enum  */
#line 581 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3874 "src/gen_parser.c"
    break;

  case 198: /* top: "pub" struct  */
#line 582 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3880 "src/gen_parser.c"
    break;

  case 199: /* top: "pub" proc  */
#line 583 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3886 "src/gen_parser.c"
    break;

  case 200: /* top: "pub" macro  */
#line 584 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3892 "src/gen_parser.c"
    break;

  case 201: /* top: "pub" import ";"  */
#line 585 "src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 3898 "src/gen_parser.c"
    break;

  case 202: /* top: "pub" type_alias ";"  */
#line 586 "src/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 3904 "src/gen_parser.c"
    break;

  case 203: /* top: "pub" type_template  */
#line 587 "src/parser.y"
                              { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3910 "src/gen_parser.c"
    break;

  case 204: /* top: var ";"  */
#line 588 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3916 "src/gen_parser.c"
    break;

  case 205: /* top: "pub" var ";"  */
#line 589 "src/parser.y"
                        { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 3922 "src/gen_parser.c"
    break;

  case 206: /* top: error  */
#line 590 "src/parser.y"
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
#line 3940 "src/gen_parser.c"
    break;

  case 207: /* unit: top  */
#line 605 "src/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 3946 "src/gen_parser.c"
    break;

  case 208: /* unit: top unit  */
#line 606 "src/parser.y"
                   { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3952 "src/gen_parser.c"
    break;

  case 209: /* input: unit  */
#line 609 "src/parser.y"
            { parser->tree = (yyvsp[0].node); }
#line 3958 "src/gen_parser.c"
    break;


#line 3962 "src/gen_parser.c"

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

#line 612 "src/parser.y"

