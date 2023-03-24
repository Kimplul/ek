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
  YYSYMBOL_union_elem = 126,               /* union_elem  */
  YYSYMBOL_union_list = 127,               /* union_list  */
  YYSYMBOL_union = 128,                    /* union  */
  YYSYMBOL_struct_list = 129,              /* struct_list  */
  YYSYMBOL_struct = 130,                   /* struct  */
  YYSYMBOL_template_elem = 131,            /* template_elem  */
  YYSYMBOL_template_list = 132,            /* template_list  */
  YYSYMBOL_type_list = 133,                /* type_list  */
  YYSYMBOL_type_alias = 134,               /* type_alias  */
  YYSYMBOL_type_template = 135,            /* type_template  */
  YYSYMBOL_enum_val = 136,                 /* enum_val  */
  YYSYMBOL_enum_list = 137,                /* enum_list  */
  YYSYMBOL_enum = 138,                     /* enum  */
  YYSYMBOL_top_if = 139,                   /* top_if  */
  YYSYMBOL_top = 140,                      /* top  */
  YYSYMBOL_unit = 141,                     /* unit  */
  YYSYMBOL_input = 142                     /* input  */
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
#define YYLAST   2009

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  215
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  428

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
       0,   147,   147,   153,   154,   157,   160,   163,   164,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   191,   194,   195,   196,   197,   198,   199,   202,   203,
     204,   205,   206,   209,   210,   211,   214,   215,   218,   220,
     221,   222,   223,   227,   228,   231,   235,   236,   237,   238,
     239,   240,   241,   242,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   260,   263,   269,   271,
     272,   273,   274,   275,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   310,   311,   314,   315,   318,   319,   322,   326,
     333,   339,   340,   343,   344,   347,   348,   351,   354,   355,
     356,   357,   360,   361,   365,   366,   369,   370,   371,   374,
     377,   380,   381,   384,   387,   394,   398,   403,   411,   413,
     417,   420,   422,   424,   426,   430,   431,   438,   439,   443,
     446,   450,   454,   458,   463,   467,   468,   471,   472,   476,
     482,   486,   492,   496,   497,   500,   501,   504,   507,   512,
     515,   518,   525,   526,   527,   528,   531,   532,   535,   536,
     539,   544,   547,   553,   554,   557,   558,   559,   562,   563,
     569,   573,   577,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     602,   603,   618,   619,   622,   623
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
  "type", "var_decl", "var_init", "proc", "lambda", "union_elem",
  "union_list", "union", "struct_list", "struct", "template_elem",
  "template_list", "type_list", "type_alias", "type_template", "enum_val",
  "enum_list", "enum", "top_if", "top", "unit", "input", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-235)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-216)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     413,  -235,  -235,  -235,   504,    46,    46,    29,    -1,    46,
      46,    46,   496,    49,    76,  -235,    60,  -235,  -235,  -235,
      77,  -235,  -235,   269,  -235,    88,    79,    81,  -235,  -235,
    -235,    86,  -235,  -235,   -19,    69,  -235,  1116,  -235,    41,
      28,    61,   209,  1116,   270,   341,    25,  1006,    67,  -235,
      70,  -235,  -235,  -235,   928,  -235,  -235,  -235,  -235,  -235,
    -235,   960,    30,    44,  -235,  -235,  -235,  -235,  1116,    46,
    1116,  1116,  1116,  1116,  1116,  -235,    74,    91,  1116,    46,
     350,     1,  -235,  -235,  -235,  -235,  -235,  -235,  1225,  -235,
      25,  -235,   350,    46,    45,  -235,  -235,    62,   928,  -235,
     928,  -235,  -235,   350,   540,   101,    56,  -235,   105,   350,
    1289,   350,   693,  -235,  1162,   522,  1930,    82,  -235,  -235,
    1116,    93,   120,    98,  -235,  -235,    23,    64,  -235,   162,
    -235,  -235,   106,  -235,   292,   163,  -235,    30,   107,    62,
    -235,    62,    62,   159,  1458,    62,  1116,   175,   259,  1353,
      60,   110,   136,   108,  -235,    46,   850,  1038,  1116,  1116,
    1116,  1116,  1116,  1116,  1116,  1116,  1116,  1116,  1116,  1116,
    1116,  1116,  1116,  1116,  1116,  1116,  1116,  1116,  1116,  1116,
    1116,  1116,  1116,  1116,  1116,  1116,  1116,   490,   350,    46,
     -43,   112,   185,   146,   121,    70,    58,  -235,  -235,   122,
     350,   350,   350,    46,  -235,   184,   350,  -235,   350,   150,
     126,  -235,  -235,    46,  1162,   194,   197,  1116,   960,  1116,
      70,   882,    -9,  -235,   151,   200,   202,  1417,  -235,  -235,
     204,   617,   145,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
     211,  -235,  -235,  1084,  1930,    70,    46,   177,   153,  -235,
     350,  -235,   960,   156,    30,   158,    30,  -235,  -235,   223,
    -235,  -235,  -235,  1481,   166,  -235,  -235,    46,    41,  -235,
    -235,   167,  1930,  -235,     6,     6,     6,   159,   159,  1258,
    1194,  1458,  1450,  1386,  1322,   631,   631,   631,   631,   788,
     788,   488,   488,  1930,  1930,  1930,  1930,  1930,  1930,  1930,
    1930,  1930,  1930,   161,  -235,  -235,    46,  1116,    46,  -235,
    -235,    46,    70,  -235,  -235,   169,  -235,   178,  -235,  -235,
     350,  -235,  -235,    70,  -235,  -235,  1545,   245,  1609,   198,
    -235,   248,  1116,    46,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,   188,   206,   260,   522,  -235,  -235,
    -235,    30,   196,    30,  -235,  -235,  -235,  -235,  -235,    70,
    -235,   215,   205,  1930,  -235,   220,  -235,   350,  -235,  -235,
     224,   235,  1116,  -235,  1116,  -235,  1609,   289,  -235,   -17,
     928,  -235,   226,  -235,   228,  -235,   -16,  -235,    70,   231,
     -14,  1116,   235,   234,  1674,  1738,   252,  1116,  -235,  -235,
    -235,  -235,  -235,   490,  -235,  -235,  -235,  -235,  -235,  1802,
    -235,  -235,  1116,  -235,     9,  1866,    70,   237,   774,  1609,
    -235,  -235,  1116,  -235,  -235,  -235,  -235,  -235
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   211,     2,   193,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   197,     3,     4,   195,   196,
       0,   201,   194,     0,   214,     0,     0,     0,   205,   204,
     203,     0,   208,   202,     0,     0,     6,     0,   198,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,   145,
       0,   156,   209,   199,     0,   200,   213,     1,   210,   206,
     207,     0,     0,     0,   180,    61,    62,    63,     0,     0,
       0,     0,     0,     0,     0,    60,     0,     0,     0,     0,
       0,    56,    74,    65,    68,    69,    66,    67,     0,    75,
       0,   161,     0,     0,     0,   148,   150,   153,     0,   154,
       0,   155,   144,     0,   147,    52,     0,    48,    51,     0,
       0,     0,     0,   160,     0,     0,   118,   120,   157,   119,
       0,    56,    47,     0,    45,    44,     0,     0,   164,     0,
     169,   163,     0,   182,     0,     0,   175,   177,     0,    41,
      59,    39,    71,    38,    40,    42,     0,     0,    56,     0,
       0,     0,   107,     0,    73,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   183,   187,     0,     0,     0,   158,   159,     0,
       0,     0,     0,     0,   141,     0,     0,   151,     0,   179,
       0,   101,   100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,    56,     0,     0,     0,    91,    92,
       0,     0,     0,    99,    94,    86,    89,    93,    90,    95,
       0,    97,    98,     0,   122,     0,     0,   116,     0,   113,
       0,    43,     0,     0,     0,     0,   166,   170,   172,     0,
     174,   176,   181,     0,     0,    64,    70,     0,     0,    58,
      54,     0,     7,     8,    11,    12,    13,    10,     9,    15,
      14,    16,    18,    17,    19,    32,    33,    34,    35,    36,
      37,    20,    21,    22,    23,    24,    25,    26,    29,    27,
      28,    30,    31,     0,    72,    57,     0,     0,   186,   189,
     110,     0,     0,   143,    50,     0,   142,     0,    49,   152,
       0,   149,    78,     0,    82,    83,     0,     0,     0,     0,
      81,     0,     0,     0,   139,   138,    88,    85,    84,    79,
      87,   102,   104,    96,     0,     0,     0,     0,   117,   121,
      46,     0,     0,     0,   165,   173,    55,     5,   106,     0,
      53,   190,     0,   184,   185,     0,   108,     0,   140,   178,
     126,     0,     0,    76,     0,    80,     0,     0,   123,     0,
       0,   115,     0,   168,     0,   162,     0,   188,     0,     0,
       0,     0,   132,     0,     0,     0,   135,     0,   124,   125,
     114,   171,   167,     0,   192,   109,   146,   127,   128,     0,
     131,   133,     0,    77,     0,   112,     0,     0,     0,     0,
     136,   137,     0,   134,   191,   130,   129,   111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -235,     0,    -2,  -235,     3,  -235,  -235,  -235,    95,  -135,
    -235,   -64,  -235,  -235,   216,  -235,  -235,  -235,  -235,  -207,
      97,   -93,     4,  -108,  -235,   -32,   193,   -51,   102,  -225,
     -67,  -235,  -235,   -68,  -235,  -235,   -88,  -235,   -20,  -235,
     409,    89,   -65,   330,  -235,  -235,  -229,   -30,     8,    10,
    -235,   218,    32,    11,    13,  -235,  -234,    16,   -25,  -235,
       5,  -235
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    81,    13,    82,    14,    83,    84,    85,   122,   123,
     105,   106,    86,    87,   116,   228,   229,   230,   231,   232,
     233,   153,    15,   416,   247,   248,   117,   124,   245,   119,
     235,   236,   392,   393,   237,   334,   335,   238,    49,    50,
      51,    16,    17,    18,    89,   129,   130,   131,   132,    19,
     137,   138,   210,    20,    21,   193,   194,    22,    38,    23,
      24,    25
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      12,   196,    26,   118,    12,    34,    35,    27,    28,    39,
      40,    41,    48,   151,    30,    31,   155,    32,   344,    91,
      33,   271,    95,    12,   341,   352,   190,   354,    56,     2,
     204,     2,    42,   136,    36,    48,     2,   205,    43,    92,
     114,    37,    48,   214,    48,    48,   104,   197,   332,   198,
       2,     2,     2,    61,   333,    62,    37,   112,   403,    52,
     112,   121,   127,   134,   249,   203,   332,   311,    54,   140,
       2,    42,   362,   156,   364,     2,    42,    43,   148,   152,
      48,   126,    43,   112,   188,   189,    53,    55,    57,    58,
     104,    59,    48,   192,   152,   126,    60,   254,   102,     2,
      42,    47,    93,    48,    48,   103,    43,   136,   155,    48,
     225,    48,   224,    90,   259,   226,   234,   350,   195,   133,
     121,    48,   239,   240,   384,   241,   255,    48,   242,   204,
     200,   312,   201,    94,    48,   108,   205,   134,   314,   111,
      47,   189,   318,    63,   112,    47,   146,   113,    48,   202,
     125,   128,   135,   206,   399,   269,   121,     2,    42,   200,
     250,   201,   336,   147,    43,   156,   155,   150,   252,    47,
     331,   253,   256,   260,   358,   158,   159,   160,   151,   108,
     264,   257,   262,   266,   267,   268,   306,    12,    48,   305,
       2,    42,   303,   307,   308,   313,   309,    43,   320,   321,
      48,    48,   104,   315,   324,    48,   104,   325,    48,   251,
     337,   425,   338,   322,   340,     2,    42,    44,   121,    45,
     342,   343,    43,   156,    48,   347,   135,    47,   348,   225,
     351,   224,   353,   355,   226,   234,   361,   188,   189,   357,
     360,   239,   240,   148,   241,   125,   346,   242,   359,   367,
      48,   368,   121,    88,   127,   372,   127,   316,   375,    97,
      47,   378,   374,   110,   379,     2,    42,   152,   380,  -212,
       1,   383,    43,   386,   155,     2,     2,    42,    98,     3,
     387,    90,   390,    43,   139,    47,   141,   142,   143,   144,
     145,   108,   310,   388,   149,   108,   249,   391,     2,    42,
     397,   401,   258,   402,   406,    43,   192,   125,   192,   411,
     414,   365,   424,   327,   427,   381,   323,   329,     4,     5,
      48,     6,     7,   408,   410,    44,   421,    45,   227,   400,
     244,   156,   150,   377,    29,    47,   144,     8,     9,    10,
      11,   125,   345,   128,  -212,   128,    47,     2,    42,   100,
     273,   127,   369,   127,    43,   261,     2,    42,   200,   382,
     201,   404,   263,    43,    90,     0,     0,    48,    47,     0,
       0,     0,     0,   272,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,    12,     0,     0,     0,     0,   417,   366,
       0,     0,     0,  -215,     1,     0,   225,    47,   224,     2,
     370,   226,   234,     3,     0,   373,    47,     0,   239,   240,
     244,   241,     0,   326,   242,   328,     0,     0,     0,     0,
     128,     0,   128,     0,    64,     0,     0,   227,     0,     0,
       0,    96,     0,    99,   101,   107,   385,     0,     0,   149,
       0,     0,     4,     5,     0,     6,     7,     0,     0,     0,
       0,     0,     0,   396,     0,     0,   398,     0,     0,     0,
       0,     8,     9,    10,    11,   405,     0,   407,     0,   154,
       0,     1,     0,     0,     0,     0,     2,     0,     0,   107,
       3,   191,     2,    42,   158,   159,   160,   161,   162,    43,
       2,   420,   199,   423,     0,     0,   426,     0,   207,     0,
     209,     0,     0,   363,     0,    65,    66,    67,     2,    68,
       0,    69,     0,     0,    70,     0,    71,     0,     0,     4,
       5,    72,     6,     7,     0,    73,     2,    42,   376,    74,
       0,     0,     0,    43,     5,     0,     6,     7,     8,     9,
      10,    11,    44,     0,    45,     0,   188,   189,    46,    75,
       0,     0,    47,     9,    10,    11,    76,     0,    77,   114,
       0,     0,     0,     0,     0,     0,     0,     0,   394,     0,
     395,     0,     0,     0,    78,     0,   115,   304,    79,     0,
      80,   246,     0,     0,     0,     0,   200,   409,   201,    99,
     101,   107,   111,   415,   317,   107,    47,   319,   211,     0,
      65,    66,    67,     2,    68,     0,    69,   212,   419,    70,
       0,    71,     0,     0,   227,     0,    72,     0,   415,     0,
      73,     0,     0,     0,    74,     0,     0,   158,   159,   160,
     161,   162,     0,   164,   165,   166,     0,     0,     0,   349,
       0,     0,     0,     0,    75,   175,   176,     5,     0,     6,
       7,    76,   213,    77,   214,     0,   215,   216,   217,  -103,
     218,   219,   220,     0,   221,   222,     0,    10,    11,    78,
       0,   112,  -103,    79,   211,    80,    65,    66,    67,     2,
      68,     0,    69,   212,     0,    70,     0,    71,     0,   188,
     189,     0,    72,     0,     0,     0,    73,     0,     0,     0,
      74,     0,     0,     0,     0,     0,     0,     0,     0,   209,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     5,     0,     6,     7,    76,   213,    77,
     214,     0,   215,   216,   217,     0,   218,   219,   220,     0,
     221,   222,     0,    10,    11,    78,     0,   112,   223,    79,
       0,    80,     0,     0,     0,   211,   389,    65,    66,    67,
       2,    68,     0,    69,   212,     0,    70,     0,    71,     0,
       0,     0,     0,    72,     0,     0,     0,    73,     0,     0,
       0,    74,     0,     0,   158,   159,   160,   161,   162,     0,
     164,   165,   166,     0,     0,     0,   169,   170,   171,   172,
       0,    75,   175,   176,     5,     0,     6,     7,    76,   213,
      77,   214,     0,   215,   216,   217,     0,   218,   219,   220,
       0,   221,   222,     0,    10,    11,    78,     0,   112,     0,
      79,     0,    80,    65,    66,    67,     2,    68,     0,    69,
       0,     0,    70,     0,    71,     0,   188,   189,     0,    72,
       0,     0,     0,   120,     0,     0,     0,    74,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,     2,    68,
       0,    69,   330,     0,    70,     0,    71,    75,     0,     0,
       0,    72,     0,     0,    76,    73,    77,   114,     0,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    78,   270,   115,     0,    79,     0,    80,    75,
       0,    65,    66,    67,     2,    68,    76,    69,    77,   114,
      70,     0,    71,     0,     0,     0,     0,    72,     0,     0,
       0,    73,     0,     0,    78,    74,   115,     0,    79,     0,
      80,     0,     0,    65,    66,    67,     2,    68,     0,    69,
       0,     0,    70,     0,    71,    75,     0,     0,     0,    72,
       0,     0,    76,   120,    77,   114,     0,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      78,     0,   115,     0,    79,     0,    80,    75,     0,    65,
      66,    67,     2,    68,    76,    69,    77,   114,    70,     0,
      71,     0,     0,     0,     0,    72,     0,     0,     0,    73,
       0,     0,    78,    74,   115,     0,    79,     0,    80,     0,
       0,    65,    66,    67,     2,    68,     0,    69,     0,     0,
      70,     0,    71,    75,     0,     0,     0,    72,     0,     0,
      76,    73,    77,     0,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    78,     0,
       0,     0,    79,   109,    80,    75,     0,    65,    66,    67,
       2,    68,    76,    69,    77,     0,    70,     0,    71,     0,
       0,     0,     0,    72,     0,     0,     0,    73,     0,     0,
      78,    74,   115,     0,    79,     0,    80,     0,     0,    65,
      66,    67,     2,    68,     0,    69,     0,     0,    70,     0,
      71,    75,     0,     0,     0,    72,     0,     0,    76,    73,
      77,   114,     0,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    78,     0,     0,     0,
      79,     0,    80,    75,     0,    65,    66,    67,     2,    68,
      76,    69,    77,     0,    70,     0,    71,     0,     0,     0,
       0,    72,     0,     0,     0,    73,     0,     0,    78,    74,
       0,     0,    79,     0,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    75,
     158,   159,   160,   161,   162,     0,    76,   165,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   175,   176,
       0,     0,     0,   157,   243,     0,     0,     0,    79,     0,
      80,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,     0,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,     0,   183,   184,
     185,   186,   188,   189,   158,   159,   160,   161,   162,     0,
     164,   165,   166,   167,   168,     0,   169,   170,   171,   172,
     173,   174,   175,   176,     0,     0,     0,   157,     0,   187,
       0,     0,     0,   188,   189,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,     0,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,     0,   183,   184,   185,   186,   188,   189,   158,   159,
     160,   161,   162,     0,   164,   165,   166,   167,     0,     0,
     169,   170,   171,   172,   173,   174,   175,   176,     0,     0,
       0,   157,     0,     0,     0,     0,   208,   188,   189,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
       0,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,     0,   183,   184,   185,   186,
     188,   189,   158,   159,   160,   161,   162,     0,   164,   165,
     166,     0,     0,     0,   169,   170,   171,   172,   173,   174,
     175,   176,     0,     0,     0,   157,   265,   339,     0,     0,
       0,   188,   189,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,     0,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
     183,   184,   185,   186,   188,   189,   158,   159,   160,   161,
     162,     0,   164,   165,   158,   159,   160,   161,   162,     0,
       0,     0,     0,     0,   175,   176,     0,     0,     0,   157,
       0,     0,   175,   176,     0,   188,   189,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,     0,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,     0,   183,   184,   185,   186,   188,   189,
       0,     0,     0,     0,     0,     0,   188,   189,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,   356,     0,     0,     0,     0,   188,
     189,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,     0,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,     0,   183,   184,
     185,   186,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,     0,   371,
       0,     0,     0,   188,   189,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,     0,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,     0,   183,   184,   185,   186,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   157,   112,   412,     0,     0,   188,   189,     0,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,     0,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,     0,   183,   184,   185,
     186,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,     0,   413,     0,
       0,     0,   188,   189,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
       0,   183,   184,   185,   186,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,     0,     0,   418,     0,     0,   188,   189,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,     0,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,     0,   183,   184,   185,   186,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   157,     0,     0,     0,     0,     0,
     188,   189,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,     0,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,     0,   183,
     184,   185,   186,     0,   422,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,     0,
       0,     0,     0,     0,   188,   189,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,     0,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,     0,   183,   184,   185,   186,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,   189
};

static const yytype_int16 yycheck[] =
{
       0,    94,     4,    54,     4,     5,     6,     4,     4,     9,
      10,    11,    12,    78,     4,     4,    15,     4,   243,    39,
       4,   156,    42,    23,   231,   254,    90,   256,    23,     6,
      73,     6,     7,    63,     5,    35,     6,    80,    13,    11,
      57,    57,    42,    57,    44,    45,    46,    98,    57,   100,
       6,     6,     6,    72,    63,    74,    57,    74,    74,    10,
      74,    61,    62,    63,   115,     9,    57,     9,     8,    69,
       6,     7,   306,    72,   308,     6,     7,    13,    78,    79,
      80,    51,    13,    74,    78,    79,    10,    10,     0,    10,
      90,    10,    92,    93,    94,    51,    10,    74,    73,     6,
       7,    76,    74,   103,   104,    80,    13,   137,    15,   109,
     112,   111,   112,    72,   134,   112,   112,   252,    73,    75,
     120,   121,   112,   112,   353,   112,   126,   127,   112,    73,
      66,    73,    68,    72,   134,    46,    80,   137,   202,    72,
      76,    79,   206,    74,    74,    76,    72,    50,   148,    48,
      61,    62,    63,    48,   379,   155,   156,     6,     7,    66,
      78,    68,    11,    72,    13,    72,    15,    78,    48,    76,
     221,    73,    10,    10,   267,    16,    17,    18,   243,    90,
       5,    75,    75,    73,    48,    77,    74,   187,   188,   189,
       6,     7,   187,     8,    48,    73,    75,    13,    48,    73,
     200,   201,   202,   203,    10,   205,   206,    10,   208,   120,
      10,   418,    10,   213,    10,     6,     7,    66,   218,    68,
      75,    10,    13,    72,   224,    48,   137,    76,    75,   231,
      74,   231,    74,    10,   231,   231,    75,    78,    79,    73,
      73,   231,   231,   243,   231,   156,   246,   231,   268,    80,
     250,    73,   252,    37,   254,    10,   256,    73,    10,    43,
      76,    73,    64,    47,    58,     6,     7,   267,     8,     0,
       1,    75,    13,    58,    15,     6,     6,     7,     8,    10,
      75,    72,    58,    13,    68,    76,    70,    71,    72,    73,
      74,   202,   195,    73,    78,   206,   347,    62,     6,     7,
      11,    75,    10,    75,    73,    13,   306,   218,   308,    75,
      58,   311,    75,   218,   422,   347,   214,   220,    49,    50,
     320,    52,    53,   390,   392,    66,   414,    68,   112,   380,
     114,    72,   243,   333,     4,    76,   120,    68,    69,    70,
      71,   252,   245,   254,    75,   256,    76,     6,     7,     8,
     157,   351,   320,   353,    13,   137,     6,     7,    66,   351,
      68,   386,   146,    13,    72,    -1,    -1,   367,    76,    -1,
      -1,    -1,    -1,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   403,    -1,    -1,    -1,    -1,   403,   312,
      -1,    -1,    -1,     0,     1,    -1,   418,    76,   418,     6,
     323,   418,   418,    10,    -1,   328,    76,    -1,   418,   418,
     214,   418,    -1,   217,   418,   219,    -1,    -1,    -1,    -1,
     351,    -1,   353,    -1,    35,    -1,    -1,   231,    -1,    -1,
      -1,    42,    -1,    44,    45,    46,   359,    -1,    -1,   243,
      -1,    -1,    49,    50,    -1,    52,    53,    -1,    -1,    -1,
      -1,    -1,    -1,   376,    -1,    -1,   379,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,   388,    -1,   390,    -1,    80,
      -1,     1,    -1,    -1,    -1,    -1,     6,    -1,    -1,    90,
      10,    92,     6,     7,    16,    17,    18,    19,    20,    13,
       6,   414,   103,   416,    -1,    -1,   419,    -1,   109,    -1,
     111,    -1,    -1,   307,    -1,     3,     4,     5,     6,     7,
      -1,     9,    -1,    -1,    12,    -1,    14,    -1,    -1,    49,
      50,    19,    52,    53,    -1,    23,     6,     7,   332,    27,
      -1,    -1,    -1,    13,    50,    -1,    52,    53,    68,    69,
      70,    71,    66,    -1,    68,    -1,    78,    79,    72,    47,
      -1,    -1,    76,    69,    70,    71,    54,    -1,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   372,    -1,
     374,    -1,    -1,    -1,    72,    -1,    74,   188,    76,    -1,
      78,    79,    -1,    -1,    -1,    -1,    66,   391,    68,   200,
     201,   202,    72,   397,   205,   206,    76,   208,     1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,   412,    12,
      -1,    14,    -1,    -1,   418,    -1,    19,    -1,   422,    -1,
      23,    -1,    -1,    -1,    27,    -1,    -1,    16,    17,    18,
      19,    20,    -1,    22,    23,    24,    -1,    -1,    -1,   250,
      -1,    -1,    -1,    -1,    47,    34,    35,    50,    -1,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      63,    64,    65,    -1,    67,    68,    -1,    70,    71,    72,
      -1,    74,    75,    76,     1,    78,     3,     4,     5,     6,
       7,    -1,     9,    10,    -1,    12,    -1,    14,    -1,    78,
      79,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   320,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    50,    -1,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    -1,    63,    64,    65,    -1,
      67,    68,    -1,    70,    71,    72,    -1,    74,    75,    76,
      -1,    78,    -1,    -1,    -1,     1,   367,     3,     4,     5,
       6,     7,    -1,     9,    10,    -1,    12,    -1,    14,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    27,    -1,    -1,    16,    17,    18,    19,    20,    -1,
      22,    23,    24,    -1,    -1,    -1,    28,    29,    30,    31,
      -1,    47,    34,    35,    50,    -1,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    -1,    63,    64,    65,
      -1,    67,    68,    -1,    70,    71,    72,    -1,    74,    -1,
      76,    -1,    78,     3,     4,     5,     6,     7,    -1,     9,
      -1,    -1,    12,    -1,    14,    -1,    78,    79,    -1,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    12,    -1,    14,    47,    -1,    -1,
      -1,    19,    -1,    -1,    54,    23,    56,    57,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    76,    -1,    78,    47,
      -1,     3,     4,     5,     6,     7,    54,     9,    56,    57,
      12,    -1,    14,    -1,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    23,    -1,    -1,    72,    27,    74,    -1,    76,    -1,
      78,    -1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      -1,    -1,    12,    -1,    14,    47,    -1,    -1,    -1,    19,
      -1,    -1,    54,    23,    56,    57,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    -1,    76,    -1,    78,    47,    -1,     3,
       4,     5,     6,     7,    54,     9,    56,    57,    12,    -1,
      14,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    23,
      -1,    -1,    72,    27,    74,    -1,    76,    -1,    78,    -1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    -1,    -1,
      12,    -1,    14,    47,    -1,    -1,    -1,    19,    -1,    -1,
      54,    23,    56,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,
      -1,    -1,    76,    77,    78,    47,    -1,     3,     4,     5,
       6,     7,    54,     9,    56,    -1,    12,    -1,    14,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,
      72,    27,    74,    -1,    76,    -1,    78,    -1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    -1,    -1,    12,    -1,
      14,    47,    -1,    -1,    -1,    19,    -1,    -1,    54,    23,
      56,    57,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,
      76,    -1,    78,    47,    -1,     3,     4,     5,     6,     7,
      54,     9,    56,    -1,    12,    -1,    14,    -1,    -1,    -1,
      -1,    19,    -1,    -1,    -1,    23,    -1,    -1,    72,    27,
      -1,    -1,    76,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      16,    17,    18,    19,    20,    -1,    54,    23,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,
      -1,    -1,    -1,     8,    72,    -1,    -1,    -1,    76,    -1,
      78,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    43,    44,
      45,    46,    78,    79,    16,    17,    18,    19,    20,    -1,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,     8,    -1,    74,
      -1,    -1,    -1,    78,    79,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    43,    44,    45,    46,    78,    79,    16,    17,
      18,    19,    20,    -1,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    77,    78,    79,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    43,    44,    45,    46,
      78,    79,    16,    17,    18,    19,    20,    -1,    22,    23,
      24,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,     8,    73,    10,    -1,    -1,
      -1,    78,    79,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      43,    44,    45,    46,    78,    79,    16,    17,    18,    19,
      20,    -1,    22,    23,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    -1,    34,    35,    -1,    -1,    -1,     8,
      -1,    -1,    34,    35,    -1,    78,    79,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    43,    44,    45,    46,    78,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     8,    73,    -1,    -1,    -1,    -1,    78,
      79,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    74,
      -1,    -1,    -1,    78,    79,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,    74,    10,    -1,    -1,    78,    79,    -1,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    10,    -1,
      -1,    -1,    78,    79,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       8,    -1,    -1,    11,    -1,    -1,    78,    79,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,
      78,    79,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    43,
      44,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    -1,    78,    79,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    10,    49,    50,    52,    53,    68,    69,
      70,    71,    82,    83,    85,   103,   122,   123,   124,   130,
     134,   135,   138,   140,   141,   142,    83,    85,   103,   124,
     130,   134,   135,   138,    82,    82,     5,    57,   139,    82,
      82,    82,     7,    13,    66,    68,    72,    76,    82,   119,
     120,   121,    10,    10,     8,    10,   141,     0,    10,    10,
      10,    72,    74,    74,   121,     3,     4,     5,     7,     9,
      12,    14,    19,    23,    27,    47,    54,    56,    72,    76,
      78,    82,    84,    86,    87,    88,    93,    94,    95,   125,
      72,   119,    11,    74,    72,   119,   121,    95,     8,   121,
       8,   121,    73,    80,    82,    91,    92,   121,   122,    77,
      95,    72,    74,   101,    57,    74,    95,   107,   108,   110,
      23,    82,    89,    90,   108,   122,    51,    82,   122,   126,
     127,   128,   129,    75,    82,   122,   128,   131,   132,    95,
      82,    95,    95,    95,    95,    95,    72,    72,    82,    95,
     122,   123,    82,   102,   121,    15,    72,     8,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    43,    44,    45,    46,    74,    78,    79,
      92,   121,    82,   136,   137,    73,   102,   108,   108,   121,
      66,    68,    48,     9,    73,    80,    48,   121,    77,   121,
     133,     1,    10,    55,    57,    59,    60,    61,    63,    64,
      65,    67,    68,    75,    82,    83,    85,    95,    96,    97,
      98,    99,   100,   101,   103,   111,   112,   115,   118,   130,
     134,   135,   138,    72,    95,   109,    79,   105,   106,   108,
      78,   122,    48,    73,    74,    82,    10,    75,    10,   119,
      10,   132,    75,    95,     5,    73,    73,    48,    77,    82,
      73,    90,    95,   107,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,   141,   121,    82,    74,     8,    48,    75,
     101,     9,    73,    73,    92,    82,    73,   121,    92,   121,
      48,    73,    82,   109,    10,    10,    95,    89,    95,   101,
      10,   108,    57,    63,   116,   117,    11,    10,    10,    10,
      10,   100,    75,    10,   110,   101,    82,    48,    75,   121,
      90,    74,   127,    74,   127,    10,    73,    73,   102,   119,
      73,    75,   137,    95,   137,    82,   101,    80,    73,   133,
     101,    74,    10,   101,    64,    10,    95,    82,    73,    58,
       8,   106,   129,    75,   127,   101,    58,    75,    73,   121,
      58,    62,   113,   114,    95,    95,   101,    11,   101,   110,
     108,    75,    75,    74,   139,   101,    73,   101,   111,    95,
     114,    75,    10,    10,    58,    95,   104,   141,    11,    95,
     101,   117,    48,   101,    75,   100,   101,   104
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
     124,   124,   125,   126,   126,   127,   127,   128,   128,   129,
     130,   130,   131,   131,   131,   131,   132,   132,   133,   133,
     134,   135,   135,   136,   136,   137,   137,   137,   138,   138,
     139,   139,   139,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   141,   141,   142,   142
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
       3,     3,     5,     1,     1,     3,     2,     5,     4,     1,
       5,     8,     2,     3,     2,     1,     2,     1,     3,     1,
       3,     5,     4,     1,     3,     3,     2,     1,     7,     5,
       5,     9,     7,     1,     1,     1,     1,     1,     2,     2,
       2,     1,     2,     2,     2,     2,     3,     3,     2,     2,
       3,     1,     1,     2,     1,     0
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
#line 142 "src/parser.y"
            {}
#line 1933 "src/gen_parser.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 142 "src/parser.y"
            {}
#line 1939 "src/gen_parser.c"
        break;

    case YYSYMBOL_STRING: /* STRING  */
#line 142 "src/parser.y"
            {}
#line 1945 "src/gen_parser.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 142 "src/parser.y"
            {}
#line 1951 "src/gen_parser.c"
        break;

    case YYSYMBOL_id: /* id  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1957 "src/gen_parser.c"
        break;

    case YYSYMBOL_var: /* var  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1963 "src/gen_parser.c"
        break;

    case YYSYMBOL_embed: /* embed  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1969 "src/gen_parser.c"
        break;

    case YYSYMBOL_import: /* import  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1975 "src/gen_parser.c"
        break;

    case YYSYMBOL_assign: /* assign  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1981 "src/gen_parser.c"
        break;

    case YYSYMBOL_binary_op: /* binary_op  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1987 "src/gen_parser.c"
        break;

    case YYSYMBOL_unary_op: /* unary_op  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1993 "src/gen_parser.c"
        break;

    case YYSYMBOL_arg: /* arg  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 1999 "src/gen_parser.c"
        break;

    case YYSYMBOL_arg_list: /* arg_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2005 "src/gen_parser.c"
        break;

    case YYSYMBOL_param_decl: /* param_decl  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2011 "src/gen_parser.c"
        break;

    case YYSYMBOL_decl_list: /* decl_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2017 "src/gen_parser.c"
        break;

    case YYSYMBOL_call: /* call  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2023 "src/gen_parser.c"
        break;

    case YYSYMBOL_defer: /* defer  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2029 "src/gen_parser.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2035 "src/gen_parser.c"
        break;

    case YYSYMBOL_while: /* while  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2041 "src/gen_parser.c"
        break;

    case YYSYMBOL_do_while: /* do_while  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2047 "src/gen_parser.c"
        break;

    case YYSYMBOL_goto: /* goto  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2053 "src/gen_parser.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2059 "src/gen_parser.c"
        break;

    case YYSYMBOL_statement_list: /* statement_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2065 "src/gen_parser.c"
        break;

    case YYSYMBOL_body: /* body  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2071 "src/gen_parser.c"
        break;

    case YYSYMBOL_macro_list: /* macro_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2077 "src/gen_parser.c"
        break;

    case YYSYMBOL_macro: /* macro  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2083 "src/gen_parser.c"
        break;

    case YYSYMBOL_expr_list: /* expr_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2089 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct_init: /* struct_init  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2095 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct_inits: /* struct_inits  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2101 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct_construct: /* struct_construct  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2107 "src/gen_parser.c"
        break;

    case YYSYMBOL_init_expr: /* init_expr  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2113 "src/gen_parser.c"
        break;

    case YYSYMBOL_cond: /* cond  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2119 "src/gen_parser.c"
        break;

    case YYSYMBOL_expr_if: /* expr_if  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2125 "src/gen_parser.c"
        break;

    case YYSYMBOL_if: /* if  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2131 "src/gen_parser.c"
        break;

    case YYSYMBOL_for: /* for  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2137 "src/gen_parser.c"
        break;

    case YYSYMBOL_case: /* case  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2143 "src/gen_parser.c"
        break;

    case YYSYMBOL_case_list: /* case_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2149 "src/gen_parser.c"
        break;

    case YYSYMBOL_switch: /* switch  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2155 "src/gen_parser.c"
        break;

    case YYSYMBOL_const_for: /* const_for  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2161 "src/gen_parser.c"
        break;

    case YYSYMBOL_const_if: /* const_if  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2167 "src/gen_parser.c"
        break;

    case YYSYMBOL_const: /* const  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2173 "src/gen_parser.c"
        break;

    case YYSYMBOL_func_sign: /* func_sign  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2179 "src/gen_parser.c"
        break;

    case YYSYMBOL_variadic_sign: /* variadic_sign  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2185 "src/gen_parser.c"
        break;

    case YYSYMBOL_type: /* type  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2191 "src/gen_parser.c"
        break;

    case YYSYMBOL_var_decl: /* var_decl  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2197 "src/gen_parser.c"
        break;

    case YYSYMBOL_var_init: /* var_init  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2203 "src/gen_parser.c"
        break;

    case YYSYMBOL_proc: /* proc  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2209 "src/gen_parser.c"
        break;

    case YYSYMBOL_lambda: /* lambda  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2215 "src/gen_parser.c"
        break;

    case YYSYMBOL_union_elem: /* union_elem  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2221 "src/gen_parser.c"
        break;

    case YYSYMBOL_union_list: /* union_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2227 "src/gen_parser.c"
        break;

    case YYSYMBOL_union: /* union  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2233 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct_list: /* struct_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2239 "src/gen_parser.c"
        break;

    case YYSYMBOL_struct: /* struct  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2245 "src/gen_parser.c"
        break;

    case YYSYMBOL_template_elem: /* template_elem  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2251 "src/gen_parser.c"
        break;

    case YYSYMBOL_template_list: /* template_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2257 "src/gen_parser.c"
        break;

    case YYSYMBOL_type_list: /* type_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2263 "src/gen_parser.c"
        break;

    case YYSYMBOL_type_alias: /* type_alias  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2269 "src/gen_parser.c"
        break;

    case YYSYMBOL_type_template: /* type_template  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2275 "src/gen_parser.c"
        break;

    case YYSYMBOL_enum_val: /* enum_val  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2281 "src/gen_parser.c"
        break;

    case YYSYMBOL_enum_list: /* enum_list  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2287 "src/gen_parser.c"
        break;

    case YYSYMBOL_enum: /* enum  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2293 "src/gen_parser.c"
        break;

    case YYSYMBOL_top_if: /* top_if  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2299 "src/gen_parser.c"
        break;

    case YYSYMBOL_top: /* top  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2305 "src/gen_parser.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 143 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2311 "src/gen_parser.c"
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
#line 147 "src/parser.y"
       {
		(yyval.node) = gen_id(strdup((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 2620 "src/gen_parser.c"
    break;

  case 3: /* var: var_decl  */
#line 153 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2626 "src/gen_parser.c"
    break;

  case 4: /* var: var_init  */
#line 154 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2632 "src/gen_parser.c"
    break;

  case 5: /* embed: "embed" "(" STRING ")"  */
#line 157 "src/parser.y"
                              { (yyval.node) = gen_embed(clone_string((yyvsp[-1].str)));  }
#line 2638 "src/gen_parser.c"
    break;

  case 6: /* import: "import" STRING  */
#line 160 "src/parser.y"
                        { (yyval.node) = gen_import(clone_string((yyvsp[0].str)));  }
#line 2644 "src/gen_parser.c"
    break;

  case 7: /* assign: expr "=" expr  */
#line 163 "src/parser.y"
                      { (yyval.node) = gen_assign((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2650 "src/gen_parser.c"
    break;

  case 8: /* assign: expr "=" struct_construct  */
#line 164 "src/parser.y"
                                    { (yyval.node) = gen_assign((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2656 "src/gen_parser.c"
    break;

  case 9: /* binary_op: expr "+" expr  */
#line 167 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2662 "src/gen_parser.c"
    break;

  case 10: /* binary_op: expr "-" expr  */
#line 168 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2668 "src/gen_parser.c"
    break;

  case 11: /* binary_op: expr "*" expr  */
#line 169 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2674 "src/gen_parser.c"
    break;

  case 12: /* binary_op: expr "/" expr  */
#line 170 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2680 "src/gen_parser.c"
    break;

  case 13: /* binary_op: expr "%" expr  */
#line 171 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2686 "src/gen_parser.c"
    break;

  case 14: /* binary_op: expr "^" expr  */
#line 172 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2692 "src/gen_parser.c"
    break;

  case 15: /* binary_op: expr "^^" expr  */
#line 173 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_POW, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2698 "src/gen_parser.c"
    break;

  case 16: /* binary_op: expr "&" expr  */
#line 174 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2704 "src/gen_parser.c"
    break;

  case 17: /* binary_op: expr "&&" expr  */
#line 175 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LAND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2710 "src/gen_parser.c"
    break;

  case 18: /* binary_op: expr "|" expr  */
#line 176 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2716 "src/gen_parser.c"
    break;

  case 19: /* binary_op: expr "||" expr  */
#line 177 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2722 "src/gen_parser.c"
    break;

  case 20: /* binary_op: expr "<<" expr  */
#line 178 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2728 "src/gen_parser.c"
    break;

  case 21: /* binary_op: expr ">>" expr  */
#line 179 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2734 "src/gen_parser.c"
    break;

  case 22: /* binary_op: expr "+=" expr  */
#line 180 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2740 "src/gen_parser.c"
    break;

  case 23: /* binary_op: expr "-=" expr  */
#line 181 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2746 "src/gen_parser.c"
    break;

  case 24: /* binary_op: expr "*=" expr  */
#line 182 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2752 "src/gen_parser.c"
    break;

  case 25: /* binary_op: expr "/=" expr  */
#line 183 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2758 "src/gen_parser.c"
    break;

  case 26: /* binary_op: expr "%=" expr  */
#line 184 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2764 "src/gen_parser.c"
    break;

  case 27: /* binary_op: expr "&=" expr  */
#line 185 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2770 "src/gen_parser.c"
    break;

  case 28: /* binary_op: expr "|=" expr  */
#line 186 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2776 "src/gen_parser.c"
    break;

  case 29: /* binary_op: expr "^=" expr  */
#line 187 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2782 "src/gen_parser.c"
    break;

  case 30: /* binary_op: expr "<<=" expr  */
#line 188 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2790 "src/gen_parser.c"
    break;

  case 31: /* binary_op: expr ">>=" expr  */
#line 191 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2798 "src/gen_parser.c"
    break;

  case 32: /* binary_op: expr "<" expr  */
#line 194 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_LT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2804 "src/gen_parser.c"
    break;

  case 33: /* binary_op: expr ">" expr  */
#line 195 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_GT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2810 "src/gen_parser.c"
    break;

  case 34: /* binary_op: expr "<=" expr  */
#line 196 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2816 "src/gen_parser.c"
    break;

  case 35: /* binary_op: expr ">=" expr  */
#line 197 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_GE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2822 "src/gen_parser.c"
    break;

  case 36: /* binary_op: expr "!=" expr  */
#line 198 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_NE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2828 "src/gen_parser.c"
    break;

  case 37: /* binary_op: expr "==" expr  */
#line 199 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_EQ, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2834 "src/gen_parser.c"
    break;

  case 38: /* unary_op: "-" expr  */
#line 202 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NEG, (yyvsp[0].node));  }
#line 2840 "src/gen_parser.c"
    break;

  case 39: /* unary_op: "!" expr  */
#line 203 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_LNOT, (yyvsp[0].node));  }
#line 2846 "src/gen_parser.c"
    break;

  case 40: /* unary_op: "&" expr  */
#line 204 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 2852 "src/gen_parser.c"
    break;

  case 41: /* unary_op: "'" expr  */
#line 205 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_DEREF, (yyvsp[0].node));  }
#line 2858 "src/gen_parser.c"
    break;

  case 42: /* unary_op: "~" expr  */
#line 206 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NOT, (yyvsp[0].node));  }
#line 2864 "src/gen_parser.c"
    break;

  case 43: /* arg: "&" var_decl  */
#line 209 "src/parser.y"
                  { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 2870 "src/gen_parser.c"
    break;

  case 44: /* arg: var_decl  */
#line 210 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2876 "src/gen_parser.c"
    break;

  case 45: /* arg: init_expr  */
#line 211 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2882 "src/gen_parser.c"
    break;

  case 46: /* arg_list: arg "," arg_list  */
#line 214 "src/parser.y"
                           { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2888 "src/gen_parser.c"
    break;

  case 47: /* arg_list: arg  */
#line 215 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2894 "src/gen_parser.c"
    break;

  case 48: /* param_decl: type  */
#line 218 "src/parser.y"
                 { (yyval.node) = gen_var(NULL, (yyvsp[0].node), NULL);  }
#line 2900 "src/gen_parser.c"
    break;

  case 49: /* decl_list: var_decl "," decl_list  */
#line 220 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2906 "src/gen_parser.c"
    break;

  case 50: /* decl_list: param_decl "," decl_list  */
#line 221 "src/parser.y"
                                   { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 2912 "src/gen_parser.c"
    break;

  case 51: /* decl_list: var_decl  */
#line 222 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2918 "src/gen_parser.c"
    break;

  case 52: /* decl_list: param_decl  */
#line 223 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2924 "src/gen_parser.c"
    break;

  case 53: /* call: id "(" arg_list ")"  */
#line 227 "src/parser.y"
                          { (yyval.node) = gen_call((yyvsp[-3].node), (yyvsp[-1].node));  }
#line 2930 "src/gen_parser.c"
    break;

  case 54: /* call: id "(" ")"  */
#line 228 "src/parser.y"
                     { (yyval.node) = gen_call((yyvsp[-2].node), NULL);  }
#line 2936 "src/gen_parser.c"
    break;

  case 55: /* defer: "defer" "(" expr ")"  */
#line 231 "src/parser.y"
                            { (yyval.node) = gen_defer((yyvsp[-1].node));  }
#line 2942 "src/gen_parser.c"
    break;

  case 56: /* expr: id  */
#line 235 "src/parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 2948 "src/gen_parser.c"
    break;

  case 57: /* expr: expr "." id  */
#line 236 "src/parser.y"
                      { (yyval.node) = gen_dot((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2954 "src/gen_parser.c"
    break;

  case 58: /* expr: id "##" id  */
#line 237 "src/parser.y"
                     { (yyval.node) = gen_paste((yyvsp[-2].node), (yyvsp[0].node));  }
#line 2960 "src/gen_parser.c"
    break;

  case 59: /* expr: "..." id  */
#line 238 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2966 "src/gen_parser.c"
    break;

  case 60: /* expr: "@"  */
#line 239 "src/parser.y"
              { (yyval.node) = gen_last();  }
#line 2972 "src/gen_parser.c"
    break;

  case 61: /* expr: INT  */
#line 240 "src/parser.y"
              { (yyval.node) = gen_int((yyvsp[0].integer)); (yyval.node)->loc = to_src_loc(&yylloc); }
#line 2978 "src/gen_parser.c"
    break;

  case 62: /* expr: FLOAT  */
#line 241 "src/parser.y"
                { (yyval.node) = gen_float((yyvsp[0].dbl)); (yyval.node)->loc = to_src_loc(&yylloc);  }
#line 2984 "src/gen_parser.c"
    break;

  case 63: /* expr: STRING  */
#line 242 "src/parser.y"
                 {
		(yyval.node) = gen_string(clone_string((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 2993 "src/gen_parser.c"
    break;

  case 64: /* expr: "(" expr ")"  */
#line 246 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 2999 "src/gen_parser.c"
    break;

  case 65: /* expr: assign  */
#line 247 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3005 "src/gen_parser.c"
    break;

  case 66: /* expr: call  */
#line 248 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3011 "src/gen_parser.c"
    break;

  case 67: /* expr: defer  */
#line 249 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3017 "src/gen_parser.c"
    break;

  case 68: /* expr: binary_op  */
#line 250 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3023 "src/gen_parser.c"
    break;

  case 69: /* expr: unary_op  */
#line 251 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3029 "src/gen_parser.c"
    break;

  case 70: /* expr: "(" var_init ")"  */
#line 252 "src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 3035 "src/gen_parser.c"
    break;

  case 71: /* expr: "sizeof" expr  */
#line 253 "src/parser.y"
                        { (yyval.node) = gen_sizeof((yyvsp[0].node)); }
#line 3041 "src/gen_parser.c"
    break;

  case 72: /* expr: expr "as" type  */
#line 254 "src/parser.y"
                         { (yyval.node) = gen_cast((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3047 "src/gen_parser.c"
    break;

  case 73: /* expr: "as" type  */
#line 255 "src/parser.y"
                    { (yyval.node) = gen_as((yyvsp[0].node)); }
#line 3053 "src/gen_parser.c"
    break;

  case 74: /* expr: embed  */
#line 256 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3059 "src/gen_parser.c"
    break;

  case 75: /* expr: lambda  */
#line 257 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3065 "src/gen_parser.c"
    break;

  case 76: /* while: "while" expr body  */
#line 260 "src/parser.y"
                         { (yyval.node) = gen_while((yyvsp[-1].node), (yyvsp[0].node));  }
#line 3071 "src/gen_parser.c"
    break;

  case 77: /* do_while: "do" body "while" expr ";"  */
#line 263 "src/parser.y"
                                     {
		(yyval.node) = gen_while((yyvsp[-3].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_DELAYED);
	}
#line 3080 "src/gen_parser.c"
    break;

  case 78: /* goto: "goto" id  */
#line 269 "src/parser.y"
                { (yyval.node) = gen_goto(gen_label((yyvsp[0].node)));  }
#line 3086 "src/gen_parser.c"
    break;

  case 79: /* statement: expr ";"  */
#line 271 "src/parser.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 3092 "src/gen_parser.c"
    break;

  case 80: /* statement: "return" init_expr ";"  */
#line 272 "src/parser.y"
                                 { (yyval.node) = gen_return((yyvsp[-1].node));  }
#line 3098 "src/gen_parser.c"
    break;

  case 81: /* statement: "return" ";"  */
#line 273 "src/parser.y"
                       { (yyval.node) = gen_return(NULL); }
#line 3104 "src/gen_parser.c"
    break;

  case 82: /* statement: "break" ";"  */
#line 274 "src/parser.y"
                      { (yyval.node) = gen_ctrl(AST_CTRL_BREAK, to_src_loc(&yylloc)); }
#line 3110 "src/gen_parser.c"
    break;

  case 83: /* statement: "continue" ";"  */
#line 275 "src/parser.y"
                         { (yyval.node) = gen_ctrl(AST_CTRL_CONTINUE,
	to_src_loc(&yylloc));  }
#line 3117 "src/gen_parser.c"
    break;

  case 84: /* statement: import ";"  */
#line 277 "src/parser.y"
                     { (yyval.node) = (yyvsp[-1].node); }
#line 3123 "src/gen_parser.c"
    break;

  case 85: /* statement: var ";"  */
#line 278 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3129 "src/gen_parser.c"
    break;

  case 86: /* statement: if  */
#line 279 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3135 "src/gen_parser.c"
    break;

  case 87: /* statement: goto ";"  */
#line 280 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3141 "src/gen_parser.c"
    break;

  case 88: /* statement: id ":"  */
#line 281 "src/parser.y"
                 { (yyval.node) = gen_label((yyvsp[-1].node));  }
#line 3147 "src/gen_parser.c"
    break;

  case 89: /* statement: for  */
#line 282 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3153 "src/gen_parser.c"
    break;

  case 90: /* statement: const  */
#line 283 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3159 "src/gen_parser.c"
    break;

  case 91: /* statement: while  */
#line 284 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3165 "src/gen_parser.c"
    break;

  case 92: /* statement: do_while  */
#line 285 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3171 "src/gen_parser.c"
    break;

  case 93: /* statement: switch  */
#line 286 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3177 "src/gen_parser.c"
    break;

  case 94: /* statement: macro  */
#line 287 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3183 "src/gen_parser.c"
    break;

  case 95: /* statement: struct  */
#line 288 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3189 "src/gen_parser.c"
    break;

  case 96: /* statement: type_alias ";"  */
#line 289 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3195 "src/gen_parser.c"
    break;

  case 97: /* statement: type_template  */
#line 290 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3201 "src/gen_parser.c"
    break;

  case 98: /* statement: enum  */
#line 291 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3207 "src/gen_parser.c"
    break;

  case 99: /* statement: body  */
#line 292 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3213 "src/gen_parser.c"
    break;

  case 100: /* statement: ";"  */
#line 293 "src/parser.y"
              { (yyval.node) = gen_empty();  }
#line 3219 "src/gen_parser.c"
    break;

  case 101: /* statement: error  */
#line 294 "src/parser.y"
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
#line 3238 "src/gen_parser.c"
    break;

  case 102: /* statement_list: statement statement_list  */
#line 310 "src/parser.y"
                                         { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3244 "src/gen_parser.c"
    break;

  case 103: /* statement_list: statement  */
#line 311 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3250 "src/gen_parser.c"
    break;

  case 104: /* body: "{" statement_list "}"  */
#line 314 "src/parser.y"
                             { (yyval.node) = gen_block((yyvsp[-1].node));  }
#line 3256 "src/gen_parser.c"
    break;

  case 105: /* body: "{" "}"  */
#line 315 "src/parser.y"
                  { (yyval.node) = gen_block(gen_empty());  }
#line 3262 "src/gen_parser.c"
    break;

  case 106: /* macro_list: id "," macro_list  */
#line 318 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 3268 "src/gen_parser.c"
    break;

  case 107: /* macro_list: id  */
#line 319 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3274 "src/gen_parser.c"
    break;

  case 108: /* macro: "define" id "(" macro_list ")" body  */
#line 322 "src/parser.y"
                                           {
		(yyval.node) = gen_macro((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3283 "src/gen_parser.c"
    break;

  case 109: /* macro: "define" id "(" macro_list "..." id ")" body  */
#line 326 "src/parser.y"
                                                       {
		/* TODO: the location data of the variadic ID is way off */
		ast_append((yyvsp[-4].node), (yyvsp[-2].node));
		(yyval.node) = gen_macro((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3295 "src/gen_parser.c"
    break;

  case 110: /* macro: "define" id "(" ")" body  */
#line 333 "src/parser.y"
                                   {
		(yyval.node) = gen_macro((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3304 "src/gen_parser.c"
    break;

  case 111: /* expr_list: expr "," expr_list  */
#line 339 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3310 "src/gen_parser.c"
    break;

  case 112: /* expr_list: expr  */
#line 340 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3316 "src/gen_parser.c"
    break;

  case 113: /* struct_init: init_expr  */
#line 343 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 3322 "src/gen_parser.c"
    break;

  case 114: /* struct_init: "." id "=" init_expr  */
#line 344 "src/parser.y"
                               { (yyval.node) = gen_var((yyvsp[-2].node), NULL, (yyvsp[0].node)); }
#line 3328 "src/gen_parser.c"
    break;

  case 115: /* struct_inits: struct_init "," struct_inits  */
#line 347 "src/parser.y"
                                           { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3334 "src/gen_parser.c"
    break;

  case 116: /* struct_inits: struct_init  */
#line 348 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3340 "src/gen_parser.c"
    break;

  case 117: /* struct_construct: "{" struct_inits "}"  */
#line 351 "src/parser.y"
                                       { (yyval.node) = gen_init((yyvsp[-1].node)); }
#line 3346 "src/gen_parser.c"
    break;

  case 118: /* init_expr: expr  */
#line 354 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3352 "src/gen_parser.c"
    break;

  case 119: /* init_expr: expr_if  */
#line 355 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 3358 "src/gen_parser.c"
    break;

  case 120: /* init_expr: struct_construct  */
#line 356 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 3364 "src/gen_parser.c"
    break;

  case 121: /* init_expr: struct_construct "as" type  */
#line 357 "src/parser.y"
                                     { (yyval.node) = gen_cast((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3370 "src/gen_parser.c"
    break;

  case 122: /* cond: expr  */
#line 360 "src/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 3376 "src/gen_parser.c"
    break;

  case 123: /* cond: "(" expr_if ")"  */
#line 361 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 3382 "src/gen_parser.c"
    break;

  case 124: /* expr_if: "if" cond body "else" body  */
#line 365 "src/parser.y"
                                    { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3388 "src/gen_parser.c"
    break;

  case 125: /* expr_if: "if" cond body "else" expr_if  */
#line 366 "src/parser.y"
                                        { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3394 "src/gen_parser.c"
    break;

  case 126: /* if: "if" cond body  */
#line 369 "src/parser.y"
                   { (yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3400 "src/gen_parser.c"
    break;

  case 127: /* if: "if" cond body "else" body  */
#line 370 "src/parser.y"
                                     { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3406 "src/gen_parser.c"
    break;

  case 128: /* if: "if" cond body "else" if  */
#line 371 "src/parser.y"
                                   { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3412 "src/gen_parser.c"
    break;

  case 129: /* for: "for" arg ";" expr ";" expr body  */
#line 374 "src/parser.y"
                                      { (yyval.node) = gen_for((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3418 "src/gen_parser.c"
    break;

  case 130: /* case: "case" expr ":" statement_list  */
#line 377 "src/parser.y"
                                     { (yyval.node) = gen_case((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3424 "src/gen_parser.c"
    break;

  case 131: /* case_list: case case_list  */
#line 380 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3430 "src/gen_parser.c"
    break;

  case 132: /* case_list: case  */
#line 381 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3436 "src/gen_parser.c"
    break;

  case 133: /* switch: "switch" expr "{" case_list "}"  */
#line 384 "src/parser.y"
                                        { (yyval.node) = gen_switch((yyvsp[-3].node), (yyvsp[-1].node));  }
#line 3442 "src/gen_parser.c"
    break;

  case 134: /* const_for: "for" id ":" expr_list body  */
#line 387 "src/parser.y"
                                       {
		/* TODO: should id be a separate rule? */
		(yyval.node) = gen_for((yyvsp[-3].node), NULL, (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3452 "src/gen_parser.c"
    break;

  case 135: /* const_if: "if" expr body  */
#line 394 "src/parser.y"
                         {
		(yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3461 "src/gen_parser.c"
    break;

  case 136: /* const_if: "if" expr body "else" body  */
#line 398 "src/parser.y"
                                     {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3471 "src/gen_parser.c"
    break;

  case 137: /* const_if: "if" expr body "else" const_if  */
#line 403 "src/parser.y"
                                         {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
	}
#line 3480 "src/gen_parser.c"
    break;

  case 138: /* const: "const" const_if  */
#line 411 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST);
      }
#line 3487 "src/gen_parser.c"
    break;

  case 139: /* const: "const" const_for  */
#line 413 "src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST);
	 }
#line 3494 "src/gen_parser.c"
    break;

  case 140: /* func_sign: "(" decl_list "=>" type ")"  */
#line 417 "src/parser.y"
                                       {
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 3502 "src/gen_parser.c"
    break;

  case 141: /* func_sign: "(" decl_list ")"  */
#line 420 "src/parser.y"
                            { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-1].node), NULL);
	 }
#line 3509 "src/gen_parser.c"
    break;

  case 142: /* func_sign: "(" decl_list "=>" ")"  */
#line 422 "src/parser.y"
                                 { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-2].node), NULL);
	 }
#line 3516 "src/gen_parser.c"
    break;

  case 143: /* func_sign: "(" "=>" type ")"  */
#line 424 "src/parser.y"
                            { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, (yyvsp[-1].node));
	 }
#line 3523 "src/gen_parser.c"
    break;

  case 144: /* func_sign: "(" ")"  */
#line 426 "src/parser.y"
                  { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, NULL);
	 }
#line 3530 "src/gen_parser.c"
    break;

  case 145: /* variadic_sign: func_sign  */
#line 430 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3536 "src/gen_parser.c"
    break;

  case 146: /* variadic_sign: "(" decl_list "..." id "=>" type ")"  */
#line 431 "src/parser.y"
                                               {
		ast_append((yyvsp[-5].node), (yyvsp[-3].node));
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
	}
#line 3546 "src/gen_parser.c"
    break;

  case 147: /* type: id  */
#line 438 "src/parser.y"
         { (yyval.node) = gen_type(AST_TYPE_ID, (yyvsp[0].node), NULL, NULL); }
#line 3552 "src/gen_parser.c"
    break;

  case 148: /* type: "'" func_sign  */
#line 439 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->next = (yyvsp[0].node);
	}
#line 3561 "src/gen_parser.c"
    break;

  case 149: /* type: id "(" type_list ")"  */
#line 443 "src/parser.y"
                               {
		(yyval.node) = gen_type(AST_TYPE_STRUCT, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
	}
#line 3569 "src/gen_parser.c"
    break;

  case 150: /* type: "'" type  */
#line 446 "src/parser.y"
                   {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3578 "src/gen_parser.c"
    break;

  case 151: /* type: "[" "]" type  */
#line 450 "src/parser.y"
                       {
		(yyval.node) = gen_type(AST_TYPE_ARR, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3587 "src/gen_parser.c"
    break;

  case 152: /* type: "[" expr "]" type  */
#line 454 "src/parser.y"
                            {
		(yyval.node) = gen_type(AST_TYPE_ARR, NULL, (yyvsp[-2].node), NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3596 "src/gen_parser.c"
    break;

  case 153: /* type: "typeof" expr  */
#line 458 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_TYPEOF, NULL, (yyvsp[0].node), NULL);
	}
#line 3604 "src/gen_parser.c"
    break;

  case 154: /* var_decl: id "mut" type  */
#line 463 "src/parser.y"
                        {
		(yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_MUTABLE);
	}
#line 3613 "src/gen_parser.c"
    break;

  case 155: /* var_decl: id "const" type  */
#line 467 "src/parser.y"
                          { (yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);  }
#line 3619 "src/gen_parser.c"
    break;

  case 156: /* var_decl: id type  */
#line 468 "src/parser.y"
                  { (yyval.node) = gen_var((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3625 "src/gen_parser.c"
    break;

  case 157: /* var_init: var_decl "=" init_expr  */
#line 471 "src/parser.y"
                                 { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->_var.init = (yyvsp[0].node); }
#line 3631 "src/gen_parser.c"
    break;

  case 158: /* var_init: id "mut" "=" init_expr  */
#line 472 "src/parser.y"
                                 {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED | AST_FLAG_MUTABLE);
	}
#line 3640 "src/gen_parser.c"
    break;

  case 159: /* var_init: id "const" "=" init_expr  */
#line 476 "src/parser.y"
                                   {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 3649 "src/gen_parser.c"
    break;

  case 160: /* proc: id variadic_sign body  */
#line 482 "src/parser.y"
                            {
		(yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), (yyvsp[-1].node)->flags);
	}
#line 3658 "src/gen_parser.c"
    break;

  case 161: /* proc: "extern" id func_sign  */
#line 486 "src/parser.y"
                                {
		(yyval.node) = gen_proc((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_EXTERN);
	}
#line 3667 "src/gen_parser.c"
    break;

  case 162: /* lambda: "[" macro_list "]" func_sign body  */
#line 492 "src/parser.y"
                                          { (yyval.node) = gen_lambda((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
       }
#line 3674 "src/gen_parser.c"
    break;

  case 163: /* union_elem: union  */
#line 496 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 3680 "src/gen_parser.c"
    break;

  case 164: /* union_elem: var_decl  */
#line 497 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3686 "src/gen_parser.c"
    break;

  case 165: /* union_list: union_elem ";" union_list  */
#line 500 "src/parser.y"
                                      { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3692 "src/gen_parser.c"
    break;

  case 166: /* union_list: union_elem ";"  */
#line 501 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3698 "src/gen_parser.c"
    break;

  case 167: /* union: "union" id "{" union_list "}"  */
#line 504 "src/parser.y"
                                     {
		(yyval.node) = gen_type(AST_TYPE_UNION, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
	}
#line 3706 "src/gen_parser.c"
    break;

  case 168: /* union: "union" "{" union_list "}"  */
#line 507 "src/parser.y"
                                     {
		(yyval.node) = gen_type(AST_TYPE_UNION, NULL, (yyvsp[-1].node), NULL);  }
#line 3713 "src/gen_parser.c"
    break;

  case 169: /* struct_list: union_list  */
#line 512 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3719 "src/gen_parser.c"
    break;

  case 170: /* struct: "struct" id "{" struct_list "}"  */
#line 515 "src/parser.y"
                                        {
		(yyval.node) = gen_struct((yyvsp[-3].node), NULL, (yyvsp[-1].node));
	}
#line 3727 "src/gen_parser.c"
    break;

  case 171: /* struct: "struct" id "(" arg_list ")" "{" struct_list "}"  */
#line 518 "src/parser.y"
                                                           {
		(yyval.node) = gen_struct((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
	}
#line 3735 "src/gen_parser.c"
    break;

  case 172: /* template_elem: id ";"  */
#line 525 "src/parser.y"
                      { (yyval.node) = (yyvsp[-1].node); }
#line 3741 "src/gen_parser.c"
    break;

  case 173: /* template_elem: id func_sign ";"  */
#line 526 "src/parser.y"
                           { (yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), NULL);  }
#line 3747 "src/gen_parser.c"
    break;

  case 174: /* template_elem: var_decl ";"  */
#line 527 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3753 "src/gen_parser.c"
    break;

  case 175: /* template_elem: union  */
#line 528 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3759 "src/gen_parser.c"
    break;

  case 176: /* template_list: template_elem template_list  */
#line 531 "src/parser.y"
                                           { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3765 "src/gen_parser.c"
    break;

  case 177: /* template_list: template_elem  */
#line 532 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3771 "src/gen_parser.c"
    break;

  case 178: /* type_list: type "," type_list  */
#line 535 "src/parser.y"
                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3777 "src/gen_parser.c"
    break;

  case 179: /* type_list: type  */
#line 536 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3783 "src/gen_parser.c"
    break;

  case 180: /* type_alias: "type" id type  */
#line 539 "src/parser.y"
                           { (yyval.node) = gen_alias((yyvsp[-1].node), (yyvsp[0].node));  }
#line 3789 "src/gen_parser.c"
    break;

  case 181: /* type_template: "type" id "{" template_list "}"  */
#line 544 "src/parser.y"
                                               {
		(yyval.node) = gen_template((yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 3797 "src/gen_parser.c"
    break;

  case 182: /* type_template: "type" id "{" "}"  */
#line 547 "src/parser.y"
                            {
		/* should match anything, but doesn't implement anything */
		(yyval.node) = gen_template((yyvsp[-2].node), NULL);
	}
#line 3806 "src/gen_parser.c"
    break;

  case 183: /* enum_val: id  */
#line 553 "src/parser.y"
             { (yyval.node) = gen_val((yyvsp[0].node), gen_int(0));  }
#line 3812 "src/gen_parser.c"
    break;

  case 184: /* enum_val: id "=" expr  */
#line 554 "src/parser.y"
                      { (yyval.node) = gen_val((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3818 "src/gen_parser.c"
    break;

  case 185: /* enum_list: enum_val "," enum_list  */
#line 557 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3824 "src/gen_parser.c"
    break;

  case 186: /* enum_list: enum_val ","  */
#line 558 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3830 "src/gen_parser.c"
    break;

  case 187: /* enum_list: enum_val  */
#line 559 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3836 "src/gen_parser.c"
    break;

  case 188: /* enum: "enum" id ":" type "{" enum_list "}"  */
#line 562 "src/parser.y"
                                           { (yyval.node) = gen_enum((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3842 "src/gen_parser.c"
    break;

  case 189: /* enum: "enum" id "{" enum_list "}"  */
#line 563 "src/parser.y"
                                      {
		(yyval.node) = gen_enum((yyvsp[-3].node), NULL, (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 3851 "src/gen_parser.c"
    break;

  case 190: /* top_if: "if" expr "{" unit "}"  */
#line 569 "src/parser.y"
                               {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-1].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3860 "src/gen_parser.c"
    break;

  case 191: /* top_if: "if" expr "{" unit "}" "else" "{" unit "}"  */
#line 573 "src/parser.y"
                                                     {
		(yyval.node) = gen_if((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3869 "src/gen_parser.c"
    break;

  case 192: /* top_if: "if" expr "{" unit "}" "else" top_if  */
#line 577 "src/parser.y"
                                               {
		(yyval.node) = gen_if((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 3878 "src/gen_parser.c"
    break;

  case 193: /* top: ";"  */
#line 585 "src/parser.y"
         { (yyval.node) = gen_empty(); }
#line 3884 "src/gen_parser.c"
    break;

  case 194: /* top: enum  */
#line 586 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3890 "src/gen_parser.c"
    break;

  case 195: /* top: proc  */
#line 587 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3896 "src/gen_parser.c"
    break;

  case 196: /* top: struct  */
#line 588 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3902 "src/gen_parser.c"
    break;

  case 197: /* top: macro  */
#line 589 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3908 "src/gen_parser.c"
    break;

  case 198: /* top: "const" top_if  */
#line 590 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 3914 "src/gen_parser.c"
    break;

  case 199: /* top: import ";"  */
#line 591 "src/parser.y"
                     { (yyval.node) = (yyvsp[-1].node); }
#line 3920 "src/gen_parser.c"
    break;

  case 200: /* top: type_alias ";"  */
#line 592 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3926 "src/gen_parser.c"
    break;

  case 201: /* top: type_template  */
#line 593 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3932 "src/gen_parser.c"
    break;

  case 202: /* top: "pub" enum  */
#line 594 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3938 "src/gen_parser.c"
    break;

  case 203: /* top: "pub" struct  */
#line 595 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3944 "src/gen_parser.c"
    break;

  case 204: /* top: "pub" proc  */
#line 596 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3950 "src/gen_parser.c"
    break;

  case 205: /* top: "pub" macro  */
#line 597 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3956 "src/gen_parser.c"
    break;

  case 206: /* top: "pub" import ";"  */
#line 598 "src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 3962 "src/gen_parser.c"
    break;

  case 207: /* top: "pub" type_alias ";"  */
#line 599 "src/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 3968 "src/gen_parser.c"
    break;

  case 208: /* top: "pub" type_template  */
#line 600 "src/parser.y"
                              { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 3974 "src/gen_parser.c"
    break;

  case 209: /* top: var ";"  */
#line 601 "src/parser.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 3980 "src/gen_parser.c"
    break;

  case 210: /* top: "pub" var ";"  */
#line 602 "src/parser.y"
                        { (yyval.node) = (yyvsp[-1].node); ast_set_flags((yyvsp[-1].node), AST_FLAG_PUBLIC); }
#line 3986 "src/gen_parser.c"
    break;

  case 211: /* top: error  */
#line 603 "src/parser.y"
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
#line 4004 "src/gen_parser.c"
    break;

  case 212: /* unit: top  */
#line 618 "src/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 4010 "src/gen_parser.c"
    break;

  case 213: /* unit: top unit  */
#line 619 "src/parser.y"
                   { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 4016 "src/gen_parser.c"
    break;

  case 214: /* input: unit  */
#line 622 "src/parser.y"
            { parser->tree = (yyvsp[0].node); }
#line 4022 "src/gen_parser.c"
    break;


#line 4026 "src/gen_parser.c"

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

#line 625 "src/parser.y"

