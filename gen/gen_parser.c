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
  YYSYMBOL_func_sign = 124,                /* func_sign  */
  YYSYMBOL_type = 125,                     /* type  */
  YYSYMBOL_var_decl = 126,                 /* var_decl  */
  YYSYMBOL_var_init = 127,                 /* var_init  */
  YYSYMBOL_proc = 128,                     /* proc  */
  YYSYMBOL_captures = 129,                 /* captures  */
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
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2223

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  255
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  500

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
     245,   246,   247,   248,   251,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   275,   276,   277,   280,   281,   282,
     283,   284,   285,   289,   290,   291,   292,   293,   294,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   320,
     323,   329,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   369,   372,   373,   374,   377,   378,
     381,   382,   383,   387,   391,   398,   404,   405,   408,   409,
     415,   416,   419,   422,   423,   424,   428,   431,   433,   438,
     439,   442,   446,   453,   457,   462,   470,   471,   474,   477,
     478,   479,   480,   483,   484,   488,   491,   495,   499,   502,
     507,   511,   512,   515,   516,   520,   526,   530,   537,   538,
     541,   542,   545,   548,   549,   552,   555,   560,   563,   564,
     567,   570,   577,   578,   579,   580,   583,   584,   587,   588,
     591,   596,   599,   605,   606,   609,   610,   611,   614,   615,
     621,   625,   629,   635,   639,   640,   643,   644,   645,   648,
     649,   654,   655,   656,   657,   658,   659,   660,   661,   662,
     663,   664,   665,   666,   667,   668,   669,   670,   671,   672,
     676,   677,   692,   693,   696,   697
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
  "case", "cases", "switch", "const_for", "const_if", "const", "func_sign",
  "type", "var_decl", "var_init", "proc", "captures", "lambda",
  "struct_elem", "members", "union", "generic", "generics", "struct",
  "template_elem", "template_elems", "types", "alias", "template",
  "enum_val", "enums", "enum", "top_if", "top_var_decl", "top_var_init",
  "top_var", "top", "unit", "input", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-283)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-256)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1275,  -283,  -283,  -283,   220,    47,    47,    47,    24,   213,
      47,    47,    47,   872,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,    42,  -283,  -283,   124,  -283,    58,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,    66,    77,
     368,  -283,  -283,  -283,   213,   213,   213,   213,  -283,  -283,
    -283,  2036,   -11,    29,    -7,  -283,    28,  1230,   -11,   214,
     622,   272,    -5,    20,    54,  -283,   213,  -283,  -283,    47,
      47,    47,    47,    70,  -283,  -283,    -1,  -283,  1845,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,  1291,  -283,
      16,    47,    51,   213,  -283,  -283,  -283,  -283,  1230,    47,
    1035,  1230,  1230,  1230,  1230,    53,  1230,  1230,  1062,    47,
     419,    55,    59,  -283,  -283,  -283,  -283,  1908,  -283,  -283,
    -283,  -283,  -283,   213,  -283,   213,  -283,    47,  -283,    16,
     556,    92,    -9,  -283,    99,   929,    16,   956,  -283,  2106,
      16,   107,    -2,   924,  -283,   149,    84,    91,    94,  -283,
     789,   177,  -283,    10,   116,  -283,  -283,  -283,  -283,    -1,
      -1,  2126,   855,   482,  1082,  2166,  2146,   640,   640,   640,
     640,  2186,  2186,   321,   321,   122,   126,   191,   154,   127,
      47,    54,   172,    40,  1714,    35,  -283,   357,    35,    35,
     162,  1175,    35,   204,  1348,  1414,   585,  1480,   152,   215,
     155,   182,   153,  -283,   419,  1124,  1230,  1230,  1230,  1230,
    1230,  1230,  1230,  1230,  1230,  1230,  1230,  1230,  1230,  1230,
    1230,  1230,  1230,  1230,  1230,  1230,  1230,  1230,  1230,  1230,
    1230,  1230,  1230,  1230,  1230,  1230,  1151,  1230,   419,    47,
    2106,  2106,  -283,   160,    16,    16,  -283,   703,  -283,   382,
     703,  -283,   185,   167,  -283,  -283,  1230,    47,  -283,  -283,
    1257,  1230,    54,  1230,    63,  -283,   574,  -283,  -283,  -283,
    1811,  -283,  -283,  -283,   227,   755,   174,  -283,  -283,  -283,
    -283,   215,  -283,  -283,  -283,  -283,  -283,  -283,    47,   163,
      47,  -283,   173,  -283,  -283,   241,  -283,  -283,  -283,   196,
      47,  1230,    47,  -283,  -283,  -283,    22,    47,    54,   929,
      47,  1811,   208,   184,   192,   209,    93,   782,  1075,  -283,
    -283,  1230,  -283,    47,    96,  -283,  1230,  -283,   604,   230,
     201,  1811,  -283,  1877,   -27,   -27,   -27,   162,   162,  1383,
    1942,  1175,  1780,  1516,  1449,  1648,  1648,  1648,  1648,  1582,
    1582,   980,   980,  1877,  1877,  1877,  1877,  1877,  1877,  1877,
    1877,  1877,  1877,  -283,   219,  1547,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,   226,  -283,    16,  -283,  1811,  -283,   291,
    1348,   217,  1811,   213,    47,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,    47,  -283,    47,  -283,   -39,   229,  1811,  -283,
    -283,   233,  -283,  -283,   303,   357,  -283,  -283,   -38,   301,
     213,    93,   237,  1230,  1230,  1811,  -283,  -283,    54,  -283,
    1257,  -283,  -283,  -283,  -283,  -283,  1230,  -283,  1230,  2058,
     305,   245,   246,  1291,  -283,  -283,    54,  1230,  -283,  -283,
    -283,   841,  2084,  -283,  -283,  1811,  1811,  -283,  -283,  1613,
    1679,   266,  1230,  -283,  -283,   251,  -283,  1811,  -283,   841,
    1230,  -283,    49,  1745,    54,  -283,  -283,  1348,  -283,  -283,
    1230,  -283,  -283,  -283,   106,  1230,   252,   159,  1230,   254,
      16,   213,  1811,   213,    35,   419,  1973,  2007,    16,   419
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   251,     2,   250,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   238,   235,   232,   234,   233,   239,
     240,   231,   236,   229,   230,   237,     0,   254,     0,   246,
     245,   244,   243,   242,   247,   248,   241,   249,     0,     0,
       0,     7,    79,    80,     0,     0,     0,     0,    78,    81,
      82,     0,     0,     0,     0,     3,     0,     0,     0,     0,
       0,     0,   173,     0,     0,   225,     0,   253,     1,     0,
       0,     0,     0,     0,   210,    75,    74,    76,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   187,
       0,     0,     0,     0,   176,    86,    87,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    83,     0,   103,    90,    96,    97,   178,   107,   105,
     106,   104,   174,     0,   223,     0,   224,     0,   172,     0,
     173,    52,     0,    48,    51,     0,     0,     0,   186,   226,
       0,   199,     0,     0,   192,     0,     0,     0,     0,   212,
       0,     0,   205,   207,     0,    77,    57,    58,    59,    56,
      55,    61,    60,    62,    64,    63,    65,    68,    69,    70,
      71,    72,    73,    66,    67,     0,     0,   213,   217,     0,
       0,     0,   141,     0,     0,    41,    85,     0,    39,    99,
      38,    40,    42,     0,     0,     0,    83,     0,     0,     0,
       0,   189,     0,   102,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     227,   228,    53,     0,     0,     0,   182,     0,   169,     0,
       0,   179,   209,     0,   133,   132,     0,     0,   115,   116,
       0,     0,     0,   114,     0,   139,    83,   118,   117,   129,
     112,   123,   124,   119,   137,     0,     0,   131,   125,   121,
     122,     4,     5,   126,   127,   128,   130,   197,     0,     0,
     194,   200,     0,   195,   202,     0,   204,   206,   211,   220,
       0,     0,   216,   219,   142,   145,     0,     0,     0,     0,
       0,   148,   151,     0,     0,   153,     0,     0,     0,    89,
     108,     0,    98,     0,     0,   101,     0,    95,    83,    47,
       0,    45,    44,     8,    11,    12,    13,    10,     9,    15,
      14,    16,    18,    17,    19,    32,    33,    34,    35,    36,
      37,    20,    21,    22,    23,    24,    25,    26,    29,    27,
      28,    30,    31,    92,     0,     0,   100,    84,   171,   180,
     181,    50,   170,     0,    49,     0,   175,    54,   111,     0,
       0,     0,   113,     0,     0,   167,   166,   120,   134,   135,
     138,   198,     0,   193,     0,   203,     0,     0,   214,   215,
     140,     0,   143,   177,     0,     0,   152,     6,     0,     0,
       0,   160,     0,     0,     0,   183,   188,   191,     0,    43,
       0,    94,    91,    93,   168,   208,     0,   109,     0,     0,
       0,     0,     0,     0,   222,   218,     0,     0,   150,   154,
     155,     0,     0,   159,   161,   184,   185,   190,    46,     0,
       0,   163,     0,   201,   196,     0,   144,   149,   158,     0,
       0,   110,     0,   147,     0,   221,   157,     0,   164,   165,
       0,   162,   156,   146,     0,     0,   173,     0,     0,   173,
       0,     0,   178,     0,   178,     0,     0,     0,     0,     0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -283,     0,   151,  -283,  -283,    -3,  -283,  -283,  -283,    75,
    -231,  -283,  -146,  -283,  -283,  -283,   463,   504,  -283,  -283,
    -283,  -283,  -283,  -282,    95,    30,     4,  -133,  -283,   -66,
    -283,   -65,  -283,  -283,   -69,  -283,  -283,  -118,  -283,   -28,
     205,   421,   240,   355,    36,  -283,  -283,   -70,    32,  -283,
     -57,    23,  -283,   207,   -13,    37,    45,  -283,  -124,    46,
     -30,  -283,  -283,   375,  -283,     6,  -283
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   121,   122,   277,   123,    14,   124,   125,   126,   339,
     340,   141,   142,   279,    49,    50,    51,   280,   281,   282,
     283,   284,   285,   286,   287,   193,    15,   474,   322,   323,
     128,   129,   289,   421,   422,   130,   395,   396,   290,    64,
     256,   154,   292,    16,   212,   131,   155,   156,    17,   151,
     152,    18,   163,   164,   263,    19,    20,   188,   189,    21,
      22,    23,    24,    25,    26,    27,    28
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    29,   158,   399,    13,    38,    39,    40,    30,    48,
      52,    53,    54,    62,   157,   374,     2,    79,    80,    81,
       9,   116,     2,    55,    99,   484,    13,    33,     2,    41,
     132,   485,    67,   190,     2,    55,    32,    56,   443,   147,
     486,    34,   100,    57,    48,    48,    48,    48,   246,    35,
      36,   317,    66,     2,   248,   249,    62,     2,    68,    62,
      62,   140,   190,     6,    61,    58,    48,   258,   102,   150,
     153,   150,   153,   160,   299,   259,     2,    58,   145,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    13,   146,
     486,   187,   192,    48,   185,   162,   101,   103,   393,   196,
     246,   381,     2,    55,   384,   484,   318,   249,   206,   211,
     489,   485,   393,     6,  -252,     1,   147,   191,   203,   394,
       2,   147,   305,    48,   215,    48,     3,   252,   214,   486,
     486,    69,   257,    70,   278,    62,   486,   276,   159,   260,
     486,   288,    71,   486,    72,    58,   419,   298,   420,   148,
     486,   300,   301,   160,    63,     2,    55,   302,   487,   468,
     293,    61,   303,   147,   488,     4,     5,     6,     7,     8,
     217,   218,   219,     9,   294,   491,   407,   476,   409,   306,
     314,    63,   295,   296,   308,   162,    10,    11,    12,   458,
     309,   311,  -252,   310,   312,   313,    62,    63,    58,   324,
      63,    63,    63,   208,   489,   338,    42,    43,    65,     2,
       2,    55,   316,    56,   133,   331,     2,    44,   330,    57,
     403,   332,   333,   334,    45,   385,   378,   246,   493,   398,
     402,   401,    46,   248,   249,    74,   338,   386,   489,   377,
     404,    63,   400,   405,   486,   486,   406,   140,   415,   486,
     140,   104,   416,    58,   134,   136,   143,   388,   417,   418,
     338,    63,     5,     6,     7,     8,    62,   431,     2,    55,
     430,   484,   278,   137,   438,   276,   315,   485,    47,   288,
      63,    63,    10,    11,    12,   432,    63,    63,   150,   325,
     153,    63,   434,   436,    63,   186,   428,   445,   293,   446,
     187,    63,   187,   447,   451,   454,   192,   411,   462,    62,
     414,    58,   294,   463,   464,   213,   472,    62,    62,   475,
     295,   296,   441,   211,   442,   490,   338,   495,   486,    79,
      80,    81,    82,    83,   253,   389,   410,   483,   138,   448,
     261,   262,   453,   450,   479,   297,   139,    63,   210,    31,
     105,   106,   107,     2,    55,    63,   108,   391,   109,   426,
     307,   110,   435,   111,     2,    55,   444,   484,   112,    37,
       0,     0,   113,   485,     0,   486,   114,     0,     2,    55,
       0,   484,     0,    48,   440,     0,     0,   485,     0,    63,
       0,     0,   153,     0,   153,    63,    63,     0,    63,     0,
      63,    63,     0,   412,     0,   115,   116,    58,     0,   335,
      48,   117,     0,     0,     0,     2,    55,    63,   487,   427,
     338,    58,   118,     0,   488,     0,   119,     0,   120,   320,
       0,     0,     0,    13,     0,    73,     0,     0,   278,   465,
       0,   276,     0,   376,     0,   288,     0,     0,   382,   379,
     380,     0,   143,     0,   383,   143,   278,     0,    58,   276,
      63,     0,     0,   288,   293,     0,     0,     0,    63,    63,
       0,     0,   144,     0,   486,   437,     0,   489,   294,    63,
     486,    48,   293,    48,   161,   489,   295,   296,   486,   489,
      79,    80,    81,    82,    83,     0,   294,    75,    76,    77,
      78,     0,     0,   449,   295,   296,     0,     0,    96,    97,
       0,     0,     0,   457,   413,     0,     0,     0,     0,   149,
       0,     0,   379,   380,   461,     0,    63,     0,     0,   209,
       0,   466,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   127,     2,    55,     0,   484,   194,   478,   291,   481,
       0,   485,   482,     0,     0,     0,     0,     0,     0,     0,
       2,    55,     0,    56,   161,     0,     0,   397,     0,    57,
     262,     2,    55,     0,    56,     0,   250,     0,   251,     0,
      57,     0,     0,     0,     0,    58,     0,     0,     0,     0,
       2,    55,   195,   484,   198,   199,   200,   201,   202,   485,
     204,   205,   207,    58,     0,   254,     0,   255,     2,    55,
       0,    56,   135,     0,    58,    63,   342,    57,    63,   490,
       0,    63,     0,   327,     0,   328,    63,     0,     0,    63,
      63,     0,     0,    58,   327,     0,   328,   214,    79,    80,
      81,    82,    83,     0,    85,    86,    87,   342,   214,     0,
       0,    58,     0,   254,     0,   255,    96,    97,   144,     0,
       0,   144,     0,     0,     0,     0,     0,   214,     0,   104,
       0,   342,   104,     0,     0,   261,     0,     0,     0,     0,
     261,   321,     0,   413,   413,     0,   291,     0,     0,     2,
      55,     0,   484,     0,   137,     0,     0,     0,   485,   341,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     341,   375,    58,     0,     0,     0,   264,   429,   105,   106,
     107,     2,    55,     0,   108,     0,   109,   265,     0,   110,
     387,   111,     0,     0,   341,   390,   112,   392,     0,     0,
     113,     0,     0,     0,   114,     0,     0,     0,     2,    55,
       0,    56,   423,     0,     0,     2,    55,    57,   484,     0,
       0,   304,     0,     0,   485,     0,     0,     5,     0,     7,
       8,   266,   267,   115,   116,   408,   268,   269,  -136,   117,
    -136,   270,   271,   272,     0,   273,   274,     0,    11,    12,
     118,    58,   147,  -136,   119,   425,   120,     0,    58,     0,
     201,     0,   264,     0,   105,   106,   107,     2,    55,     0,
     108,   342,   109,   265,     0,   110,   439,   111,   254,     0,
     255,     0,   112,     0,    61,     0,   113,     0,     0,     0,
     114,     0,   291,    79,    80,    81,    82,    83,     2,    55,
      86,    56,     0,   452,     0,     0,     0,    57,     0,     0,
     291,    96,    97,     5,     0,     7,     8,   266,   267,   115,
     116,     0,   268,   269,     0,   117,     0,   270,   271,   272,
       0,   273,   274,     0,    11,    12,   118,     0,   147,   321,
     119,    58,   120,     0,     0,     0,     0,   455,   456,     0,
       2,    55,     0,   484,   341,     2,    55,     0,    56,   485,
     459,    59,   460,    60,    57,     0,     0,    61,     0,     0,
       0,   467,     0,     0,   496,     0,   497,   264,     0,   105,
     106,   107,     2,    55,     0,   108,   473,   109,   265,     0,
     110,     0,   111,    58,   477,     0,     0,   112,    58,     0,
       0,   113,     0,     0,   473,   114,     0,     0,     0,   492,
       0,     0,   494,   254,     0,   255,     0,     0,   217,   218,
     219,   220,   221,     0,     0,     0,     0,     0,     5,     0,
       7,     8,   266,   267,   115,   116,     0,   268,   269,     0,
     117,     0,   270,   271,   272,     0,   273,   274,     0,    11,
      12,   118,     0,   147,   275,   119,     0,   120,   105,   106,
     107,     2,    55,     0,   108,     0,   109,     0,     0,   110,
       0,   111,     0,     0,     0,   246,   112,     0,     0,     0,
     113,   248,   249,     0,   114,   105,   106,   107,     2,    55,
       0,   108,     0,   109,     0,     0,   110,     0,   111,     0,
       0,     2,    55,   112,    56,   424,     0,   113,     0,     0,
      57,   114,     0,   115,   116,     0,     0,     0,     0,   117,
      79,    80,    81,    82,    83,     0,    85,    86,     0,     0,
     118,     0,   197,     0,   119,     0,   120,     0,    96,    97,
     115,   116,     0,     0,    58,     0,   117,   105,   106,   107,
       2,    55,     0,   108,     0,   109,     0,   118,   110,   147,
     111,   119,     0,   120,     0,   112,     0,     0,     0,   336,
       0,     0,     0,   114,   105,   106,   107,     2,    55,     0,
     108,     0,   109,     0,     0,   110,     0,   111,     0,     0,
       0,     0,   112,     0,     0,     0,   336,     0,     0,     0,
     114,     0,   115,   116,     0,     0,     0,     0,   117,     0,
       0,     0,     0,   217,   218,   219,   220,   221,     0,   118,
     337,     0,     0,   119,     0,   120,     0,     0,     0,   115,
     116,   234,   235,     0,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,   373,     0,     0,
     119,     0,   120,   105,   106,   107,     2,    55,     0,   108,
       0,   109,     0,     0,   110,     0,   111,     0,     0,     0,
     246,   112,     0,     0,     0,   113,   248,   249,     0,   114,
     105,   106,   107,     2,    55,     0,   108,     0,   109,     0,
       0,   110,     0,   111,     0,  -255,     1,     0,   112,     0,
       0,     2,   336,     0,     0,     0,   114,     3,   115,   116,
       0,     0,     1,     0,   117,     0,     0,     2,     0,     0,
       0,     0,     0,     3,     0,   118,     0,     0,     0,   119,
       0,   120,     0,     0,     0,   115,   116,     0,     0,     0,
       0,   117,     0,     0,     0,     0,     4,     5,     6,     7,
       8,     0,   118,     0,     9,     0,   119,     0,   120,     0,
       0,     0,     4,     5,     6,     7,     8,    10,    11,    12,
       9,     0,     0,     0,     0,     0,     0,     0,   216,     0,
       0,     0,     0,    10,    11,    12,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,     0,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,     0,   242,   243,   244,   245,     0,     0,     0,
       0,   217,   218,   219,   220,   221,     0,   223,   224,   225,
     226,   227,     0,   228,   229,   230,   231,   232,   233,   234,
     235,     0,     0,   246,   216,   147,     0,   247,     0,   248,
     249,     0,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,     0,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   246,   242,
     243,   244,   245,     0,   248,   249,     0,   217,   218,   219,
     220,   221,     0,   223,   224,   225,   226,     0,     0,   228,
     229,   230,   231,   232,   233,   234,   235,     0,     0,   246,
     216,   326,     0,   247,     0,   248,   249,     0,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,     0,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   246,   242,   243,   244,   245,     0,
     248,   249,     0,     0,   217,   218,   219,   220,   221,     0,
     223,   224,   225,     0,     0,     0,   228,   229,   230,   231,
     232,   233,   234,   235,     0,   246,   329,   216,     0,   247,
       0,   248,   249,     0,     0,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,     0,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   246,   242,   243,   244,   245,     0,   248,   249,     0,
     217,   218,   219,   220,   221,     0,   223,   224,   225,     0,
       0,     0,   228,   229,   230,   231,     0,     0,   234,   235,
       0,     0,   246,   216,     0,   470,   247,   433,   248,   249,
       0,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,     0,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   246,   242,   243,
     244,   245,     0,   248,   249,     0,   217,   218,   219,   220,
     221,     0,   223,   224,   225,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   234,   235,     0,     0,   246,   216,
       0,   471,   247,     0,   248,   249,     0,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,     0,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   246,   242,   243,   244,   245,     0,   248,
     249,     0,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,     0,    90,    91,    92,    93,    94,    95,
      96,    97,     0,     0,   246,   216,     0,     0,   247,     0,
     248,   249,     0,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,     0,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,     0,
     242,   243,   244,   245,   319,   480,     0,     0,   217,   218,
     219,   220,   221,     0,   223,   224,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   234,   235,     0,     0,
     246,   216,     0,     0,   247,     0,   248,   249,     0,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
       0,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   246,   242,   243,   244,   245,
       0,   248,   249,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,    90,    91,    92,    93,    94,
      95,    96,    97,     0,     0,     0,   246,   216,     0,     0,
     247,     0,   248,   249,     0,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,     0,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   165,   242,   243,   244,   245,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,     0,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   246,   242,   243,   244,   245,     0,   248,   249,
     217,   218,   219,   220,   221,     0,     0,   224,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   234,   235,
       0,     0,     0,   246,     0,     0,     0,   247,     0,   248,
     249,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     0,    90,    91,    92,    93,    94,    95,    96,
      97,     0,     0,     0,     0,     0,     0,   246,     0,     0,
       0,     0,     0,   248,   249,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,    90,    91,    92,
      93,    94,    95,    96,    97,     0,     0,     0,     0,     0,
       0,     0,     0,   498,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,     0,    90,    91,    92,    93,
      94,    95,    96,    97,     0,     0,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   499,    90,    91,
      92,    93,    94,    95,    96,    97,     0,   469,     0,     0,
       0,     0,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    98,    90,    91,    92,    93,    94,    95,
      96,    97,     0,     0,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,   147,    90,    91,    92,    93,
      94,    95,    96,    97,    79,    80,    81,    82,    83,     0,
      85,    86,    87,    88,    89,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    79,    80,    81,    82,    83,     0,
      85,    86,    87,    88,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    79,    80,    81,    82,    83,     0,
      85,    86,    87,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    79,    80,    81,    82,    83,     0,
      85,    86,    87,     0,     0,     0,    90,    91,    92,    93,
       0,     0,    96,    97
};

static const yytype_int16 yycheck[] =
{
       0,     4,    72,   285,     4,     5,     6,     7,     4,     9,
      10,    11,    12,    13,    71,   246,     6,    18,    19,    20,
      59,    59,     6,     7,    52,     9,    26,     4,     6,     5,
      58,    15,    26,    11,     6,     7,     4,     9,    77,    77,
      40,     4,    13,    15,    44,    45,    46,    47,    75,     4,
       4,    11,    10,     6,    81,    82,    56,     6,     0,    59,
      60,    61,    11,    53,    75,    49,    66,    76,    75,    69,
      70,    71,    72,    73,    76,    84,     6,    49,    83,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    79,
     100,   101,   102,   103,    98,    73,    77,    79,    59,   109,
      75,   257,     6,     7,   260,     9,    76,    82,   118,   119,
     120,    15,    59,    53,     0,     1,    77,    76,    75,    66,
       6,    77,   160,   133,    75,   135,    12,   137,    83,   139,
     140,    75,    50,    77,   147,   145,   146,   147,    78,    50,
     150,   147,    75,   153,    77,    49,    63,    50,    65,    64,
     160,    12,    78,   163,    13,     6,     7,    76,     9,   451,
     147,    75,    78,    77,    15,    51,    52,    53,    54,    55,
      18,    19,    20,    59,   147,    79,   310,   469,   312,    12,
     190,    40,   147,   147,    78,   163,    72,    73,    74,   430,
      78,    10,    78,    77,    50,    78,   206,    56,    49,     5,
      59,    60,    61,   118,   214,   215,     3,     4,    13,     6,
       6,     7,    50,     9,    10,    10,     6,    14,    76,    15,
     300,    76,    50,    80,    21,    50,    76,    75,    79,    12,
      77,   298,    29,    81,    82,    40,   246,    80,   248,   249,
      77,   100,    78,    12,   254,   255,    60,   257,    50,   259,
     260,    56,    78,    49,    59,    60,    61,   267,    76,    60,
     270,   120,    52,    53,    54,    55,   276,    76,     6,     7,
      50,     9,   285,    11,    67,   285,   191,    15,    75,   285,
     139,   140,    72,    73,    74,    76,   145,   146,   298,   204,
     300,   150,    76,    12,   153,   100,   334,    78,   285,    76,
     310,   160,   312,    10,    13,    78,   316,   317,    13,   319,
     320,    49,   285,    78,    78,   120,    60,   327,   328,    78,
     285,   285,   402,   333,   404,    83,   336,    83,   338,    18,
      19,    20,    21,    22,   139,   270,   316,   480,    76,   415,
     145,   146,   421,   418,   472,   150,    84,   206,   118,     4,
       3,     4,     5,     6,     7,   214,     9,   272,    11,   333,
     163,    14,   385,    16,     6,     7,   406,     9,    21,     4,
      -1,    -1,    25,    15,    -1,   385,    29,    -1,     6,     7,
      -1,     9,    -1,   393,   394,    -1,    -1,    15,    -1,   248,
      -1,    -1,   402,    -1,   404,   254,   255,    -1,   257,    -1,
     259,   260,    -1,   318,    -1,    58,    59,    49,    -1,   214,
     420,    64,    -1,    -1,    -1,     6,     7,   276,     9,   334,
     430,    49,    75,    -1,    15,    -1,    79,    -1,    81,    82,
      -1,    -1,    -1,   443,    -1,    77,    -1,    -1,   451,   443,
      -1,   451,    -1,   248,    -1,   451,    -1,    -1,    76,   254,
     255,    -1,   257,    -1,   259,   260,   469,    -1,    49,   469,
     319,    -1,    -1,   469,   451,    -1,    -1,    -1,   327,   328,
      -1,    -1,    61,    -1,   484,   390,    -1,   487,   451,   338,
     490,   491,   469,   493,    73,   495,   451,   451,   498,   499,
      18,    19,    20,    21,    22,    -1,   469,    44,    45,    46,
      47,    -1,    -1,   418,   469,   469,    -1,    -1,    36,    37,
      -1,    -1,    -1,   428,   319,    -1,    -1,    -1,    -1,    66,
      -1,    -1,   327,   328,   439,    -1,   385,    -1,    -1,   118,
      -1,   446,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    57,     6,     7,    -1,     9,   103,   472,   147,   474,
      -1,    15,   477,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       6,     7,    -1,     9,   163,    -1,    -1,    13,    -1,    15,
     385,     6,     7,    -1,     9,    -1,   133,    -1,   135,    -1,
      15,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
       6,     7,   108,     9,   110,   111,   112,   113,   114,    15,
     116,   117,   118,    49,    -1,    69,    -1,    71,     6,     7,
      -1,     9,    10,    -1,    49,   484,   215,    15,   487,    83,
      -1,   490,    -1,    69,    -1,    71,   495,    -1,    -1,   498,
     499,    -1,    -1,    49,    69,    -1,    71,    83,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,   246,    83,    -1,
      -1,    49,    -1,    69,    -1,    71,    36,    37,   257,    -1,
      -1,   260,    -1,    -1,    -1,    -1,    -1,    83,    -1,   484,
      -1,   270,   487,    -1,    -1,   490,    -1,    -1,    -1,    -1,
     495,   197,    -1,   498,   499,    -1,   285,    -1,    -1,     6,
       7,    -1,     9,    -1,    11,    -1,    -1,    -1,    15,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,    49,    -1,    -1,    -1,     1,   336,     3,     4,
       5,     6,     7,    -1,     9,    -1,    11,    12,    -1,    14,
     266,    16,    -1,    -1,   270,   271,    21,   273,    -1,    -1,
      25,    -1,    -1,    -1,    29,    -1,    -1,    -1,     6,     7,
      -1,     9,    10,    -1,    -1,     6,     7,    15,     9,    -1,
      -1,    12,    -1,    -1,    15,    -1,    -1,    52,    -1,    54,
      55,    56,    57,    58,    59,   311,    61,    62,    63,    64,
      65,    66,    67,    68,    -1,    70,    71,    -1,    73,    74,
      75,    49,    77,    78,    79,   331,    81,    -1,    49,    -1,
     336,    -1,     1,    -1,     3,     4,     5,     6,     7,    -1,
       9,   430,    11,    12,    -1,    14,   393,    16,    69,    -1,
      71,    -1,    21,    -1,    75,    -1,    25,    -1,    -1,    -1,
      29,    -1,   451,    18,    19,    20,    21,    22,     6,     7,
      25,     9,    -1,   420,    -1,    -1,    -1,    15,    -1,    -1,
     469,    36,    37,    52,    -1,    54,    55,    56,    57,    58,
      59,    -1,    61,    62,    -1,    64,    -1,    66,    67,    68,
      -1,    70,    71,    -1,    73,    74,    75,    -1,    77,   415,
      79,    49,    81,    -1,    -1,    -1,    -1,   423,   424,    -1,
       6,     7,    -1,     9,   430,     6,     7,    -1,     9,    15,
     436,    69,   438,    71,    15,    -1,    -1,    75,    -1,    -1,
      -1,   447,    -1,    -1,   491,    -1,   493,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,   462,    11,    12,    -1,
      14,    -1,    16,    49,   470,    -1,    -1,    21,    49,    -1,
      -1,    25,    -1,    -1,   480,    29,    -1,    -1,    -1,   485,
      -1,    -1,   488,    69,    -1,    71,    -1,    -1,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      54,    55,    56,    57,    58,    59,    -1,    61,    62,    -1,
      64,    -1,    66,    67,    68,    -1,    70,    71,    -1,    73,
      74,    75,    -1,    77,    78,    79,    -1,    81,     3,     4,
       5,     6,     7,    -1,     9,    -1,    11,    -1,    -1,    14,
      -1,    16,    -1,    -1,    -1,    75,    21,    -1,    -1,    -1,
      25,    81,    82,    -1,    29,     3,     4,     5,     6,     7,
      -1,     9,    -1,    11,    -1,    -1,    14,    -1,    16,    -1,
      -1,     6,     7,    21,     9,    10,    -1,    25,    -1,    -1,
      15,    29,    -1,    58,    59,    -1,    -1,    -1,    -1,    64,
      18,    19,    20,    21,    22,    -1,    24,    25,    -1,    -1,
      75,    -1,    77,    -1,    79,    -1,    81,    -1,    36,    37,
      58,    59,    -1,    -1,    49,    -1,    64,     3,     4,     5,
       6,     7,    -1,     9,    -1,    11,    -1,    75,    14,    77,
      16,    79,    -1,    81,    -1,    21,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    29,     3,     4,     5,     6,     7,    -1,
       9,    -1,    11,    -1,    -1,    14,    -1,    16,    -1,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      29,    -1,    58,    59,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    18,    19,    20,    21,    22,    -1,    75,
      76,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    58,
      59,    36,    37,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,    -1,
      79,    -1,    81,     3,     4,     5,     6,     7,    -1,     9,
      -1,    11,    -1,    -1,    14,    -1,    16,    -1,    -1,    -1,
      75,    21,    -1,    -1,    -1,    25,    81,    82,    -1,    29,
       3,     4,     5,     6,     7,    -1,     9,    -1,    11,    -1,
      -1,    14,    -1,    16,    -1,     0,     1,    -1,    21,    -1,
      -1,     6,    25,    -1,    -1,    -1,    29,    12,    58,    59,
      -1,    -1,     1,    -1,    64,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    12,    -1,    75,    -1,    -1,    -1,    79,
      -1,    81,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    51,    52,    53,    54,
      55,    -1,    75,    -1,    59,    -1,    79,    -1,    81,    -1,
      -1,    -1,    51,    52,    53,    54,    55,    72,    73,    74,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    10,    -1,
      -1,    -1,    -1,    72,    73,    74,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    -1,    45,    46,    47,    48,    -1,    -1,    -1,
      -1,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    75,    10,    77,    -1,    79,    -1,    81,
      82,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    75,    45,
      46,    47,    48,    -1,    81,    82,    -1,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    75,
      10,    77,    -1,    79,    -1,    81,    82,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    75,    45,    46,    47,    48,    -1,
      81,    82,    -1,    -1,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    75,    76,    10,    -1,    79,
      -1,    81,    82,    -1,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    75,    45,    46,    47,    48,    -1,    81,    82,    -1,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    36,    37,
      -1,    -1,    75,    10,    -1,    12,    79,    80,    81,    82,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    75,    45,    46,
      47,    48,    -1,    81,    82,    -1,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    75,    10,
      -1,    12,    79,    -1,    81,    82,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    75,    45,    46,    47,    48,    -1,    81,
      82,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    75,    10,    -1,    -1,    79,    -1,
      81,    82,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    48,    80,    50,    -1,    -1,    18,    19,
      20,    21,    22,    -1,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      75,    10,    -1,    -1,    79,    -1,    81,    82,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    75,    45,    46,    47,    48,
      -1,    81,    82,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    75,    10,    -1,    -1,
      79,    -1,    81,    82,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    76,    45,    46,    47,    48,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    75,    45,    46,    47,    48,    -1,    81,    82,
      18,    19,    20,    21,    22,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    -1,    81,
      82,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,
      -1,    -1,    -1,    81,    82,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    80,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    13,    -1,    -1,
      -1,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    77,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    77,    30,    31,    32,    33,
      34,    35,    36,    37,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    27,    28,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    12,    51,    52,    53,    54,    55,    59,
      72,    73,    74,    86,    90,   111,   128,   133,   136,   140,
     141,   144,   145,   146,   147,   148,   149,   150,   151,    90,
     111,   128,   133,   136,   140,   141,   144,   148,    86,    86,
      86,     5,     3,     4,    14,    21,    29,    75,    86,    99,
     100,   101,    86,    86,    86,     7,     9,    15,    49,    69,
      71,    75,    86,    87,   124,   125,    10,   150,     0,    75,
      77,    75,    77,    77,   125,   101,   101,   101,   101,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      30,    31,    32,    33,    34,    35,    36,    37,    77,   124,
      13,    77,    75,    79,   125,     3,     4,     5,     9,    11,
      14,    16,    21,    25,    29,    58,    59,    64,    75,    79,
      81,    86,    87,    89,    91,    92,    93,   102,   115,   116,
     120,   130,   124,    10,   125,    10,   125,    11,    76,    84,
      86,    96,    97,   125,   126,    83,    79,    77,   109,   101,
      86,   134,   135,    86,   126,   131,   132,   135,   132,    78,
      86,   126,   133,   137,   138,    76,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   150,   125,    86,   142,   143,
      11,    76,    86,   110,   101,   102,    86,    77,   102,   102,
     102,   102,   102,    75,   102,   102,    86,   102,   109,   126,
     127,    86,   129,   125,    83,    75,    10,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    45,    46,    47,    48,    75,    79,    81,    82,
     101,   101,    86,   125,    69,    71,   125,    50,    76,    84,
      50,   125,   125,   139,     1,    12,    56,    57,    61,    62,
      66,    67,    68,    70,    71,    78,    86,    88,    90,    98,
     102,   103,   104,   105,   106,   107,   108,   109,   111,   117,
     123,   126,   127,   136,   140,   141,   144,   125,    50,    76,
      12,    78,    76,    78,    12,   124,    12,   138,    78,    78,
      77,    10,    50,    78,    86,   109,    50,    11,    76,    80,
      82,   102,   113,   114,     5,   109,    77,    69,    71,    76,
      76,    10,    76,    50,    80,   125,    25,    76,    86,    94,
      95,   102,   126,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,    76,    95,   102,   125,    86,    76,   125,
     125,    97,    76,   125,    97,    50,    80,   102,    86,    94,
     102,   109,   102,    59,    66,   121,   122,    13,    12,   108,
      78,   135,    77,   132,    77,    12,    60,   143,   102,   143,
     110,    86,   109,   125,    86,    50,    78,    76,    60,    63,
      65,   118,   119,    10,    10,   102,   129,   109,   124,   126,
      50,    76,    76,    80,    76,   139,    12,   109,    67,   101,
      86,   132,   132,    77,   145,    78,    76,    10,   114,   109,
     116,    13,   101,   119,    78,   102,   102,   109,    95,   102,
     102,   109,    13,    78,    78,   150,   109,   102,   108,    13,
      12,    12,    60,   102,   112,    78,   108,   102,   109,   122,
      50,   109,   109,   112,     9,    15,    86,     9,    15,    86,
      83,    79,   102,    79,   102,    83,   101,   101,    80,    80
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    88,    88,    89,    90,    91,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    93,    93,
      93,    93,    93,    94,    94,    94,    95,    95,    96,    97,
      97,    97,    97,    97,    98,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   100,   101,   101,   101,
     101,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   103,
     104,   105,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   107,   108,   108,   108,   109,   109,
     110,   110,   110,   111,   111,   111,   112,   112,   113,   113,
     114,   114,   115,   116,   116,   116,   117,   118,   118,   119,
     119,   120,   121,   122,   122,   122,   123,   123,   124,   124,
     124,   124,   124,   125,   125,   125,   125,   125,   125,   125,
     126,   126,   126,   127,   127,   127,   128,   128,   129,   129,
     130,   130,   131,   132,   132,   133,   133,   134,   135,   135,
     136,   136,   137,   137,   137,   137,   138,   138,   139,   139,
     140,   141,   141,   142,   142,   143,   143,   143,   144,   144,
     145,   145,   145,   146,   146,   146,   147,   147,   147,   148,
     148,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   150,   150,   151,   151
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     4,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     2,     1,     1,     3,     1,     1,     3,
       3,     1,     1,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     3,     1,     1,
       1,     1,     1,     1,     3,     2,     1,     1,     1,     3,
       1,     4,     3,     4,     4,     3,     1,     1,     3,     2,
       3,     3,     2,     1,     1,     1,     1,     1,     3,     3,
       5,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     1,     3,     2,
       3,     1,     2,     6,     8,     5,     3,     1,     1,     4,
       3,     1,     4,     3,     5,     5,     7,     4,     3,     2,
       1,     5,     5,     3,     5,     5,     2,     2,     5,     3,
       4,     4,     2,     1,     2,     4,     2,     5,     2,     3,
       3,     3,     2,     3,     4,     4,     3,     3,     3,     1,
       5,     4,     1,     3,     2,     5,     8,     2,     3,     1,
       5,     8,     2,     3,     2,     1,     2,     1,     3,     1,
       3,     5,     4,     1,     3,     3,     2,     1,     7,     5,
       5,     9,     7,     3,     3,     2,     3,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     2,     1,     0
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
#line 2020 "gen/gen_parser.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 159 "src/parser.y"
            {}
#line 2026 "gen/gen_parser.c"
        break;

    case YYSYMBOL_STRING: /* STRING  */
#line 159 "src/parser.y"
            {}
#line 2032 "gen/gen_parser.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 159 "src/parser.y"
            {}
#line 2038 "gen/gen_parser.c"
        break;

    case YYSYMBOL_APPLY: /* APPLY  */
#line 159 "src/parser.y"
            {}
#line 2044 "gen/gen_parser.c"
        break;

    case YYSYMBOL_id: /* id  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2050 "gen/gen_parser.c"
        break;

    case YYSYMBOL_apply: /* apply  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2056 "gen/gen_parser.c"
        break;

    case YYSYMBOL_var: /* var  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2062 "gen/gen_parser.c"
        break;

    case YYSYMBOL_embed: /* embed  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2068 "gen/gen_parser.c"
        break;

    case YYSYMBOL_import: /* import  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2074 "gen/gen_parser.c"
        break;

    case YYSYMBOL_assign: /* assign  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2080 "gen/gen_parser.c"
        break;

    case YYSYMBOL_binop: /* binop  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2086 "gen/gen_parser.c"
        break;

    case YYSYMBOL_unop: /* unop  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2092 "gen/gen_parser.c"
        break;

    case YYSYMBOL_arg: /* arg  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2098 "gen/gen_parser.c"
        break;

    case YYSYMBOL_args: /* args  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2104 "gen/gen_parser.c"
        break;

    case YYSYMBOL_param_decl: /* param_decl  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2110 "gen/gen_parser.c"
        break;

    case YYSYMBOL_decls: /* decls  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2116 "gen/gen_parser.c"
        break;

    case YYSYMBOL_defer: /* defer  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2122 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_binop: /* const_binop  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2128 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_unop: /* const_unop  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2134 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_expr: /* const_expr  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2140 "gen/gen_parser.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2146 "gen/gen_parser.c"
        break;

    case YYSYMBOL_while: /* while  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2152 "gen/gen_parser.c"
        break;

    case YYSYMBOL_do_while: /* do_while  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2158 "gen/gen_parser.c"
        break;

    case YYSYMBOL_goto: /* goto  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2164 "gen/gen_parser.c"
        break;

    case YYSYMBOL_statelet: /* statelet  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2170 "gen/gen_parser.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2176 "gen/gen_parser.c"
        break;

    case YYSYMBOL_statements: /* statements  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2182 "gen/gen_parser.c"
        break;

    case YYSYMBOL_body: /* body  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2188 "gen/gen_parser.c"
        break;

    case YYSYMBOL_references: /* references  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2194 "gen/gen_parser.c"
        break;

    case YYSYMBOL_macro: /* macro  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2200 "gen/gen_parser.c"
        break;

    case YYSYMBOL_exprs: /* exprs  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2206 "gen/gen_parser.c"
        break;

    case YYSYMBOL_construct_arg: /* construct_arg  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2212 "gen/gen_parser.c"
        break;

    case YYSYMBOL_construct_args: /* construct_args  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2218 "gen/gen_parser.c"
        break;

    case YYSYMBOL_construct: /* construct  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2224 "gen/gen_parser.c"
        break;

    case YYSYMBOL_if: /* if  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2230 "gen/gen_parser.c"
        break;

    case YYSYMBOL_for: /* for  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2236 "gen/gen_parser.c"
        break;

    case YYSYMBOL_case: /* case  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2242 "gen/gen_parser.c"
        break;

    case YYSYMBOL_cases: /* cases  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2248 "gen/gen_parser.c"
        break;

    case YYSYMBOL_switch: /* switch  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2254 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_for: /* const_for  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2260 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const_if: /* const_if  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2266 "gen/gen_parser.c"
        break;

    case YYSYMBOL_const: /* const  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2272 "gen/gen_parser.c"
        break;

    case YYSYMBOL_func_sign: /* func_sign  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2278 "gen/gen_parser.c"
        break;

    case YYSYMBOL_type: /* type  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2284 "gen/gen_parser.c"
        break;

    case YYSYMBOL_var_decl: /* var_decl  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2290 "gen/gen_parser.c"
        break;

    case YYSYMBOL_var_init: /* var_init  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2296 "gen/gen_parser.c"
        break;

    case YYSYMBOL_proc: /* proc  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2302 "gen/gen_parser.c"
        break;

    case YYSYMBOL_captures: /* captures  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2308 "gen/gen_parser.c"
        break;

    case YYSYMBOL_lambda: /* lambda  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2314 "gen/gen_parser.c"
        break;

    case YYSYMBOL_struct_elem: /* struct_elem  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2320 "gen/gen_parser.c"
        break;

    case YYSYMBOL_members: /* members  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2326 "gen/gen_parser.c"
        break;

    case YYSYMBOL_union: /* union  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2332 "gen/gen_parser.c"
        break;

    case YYSYMBOL_generic: /* generic  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2338 "gen/gen_parser.c"
        break;

    case YYSYMBOL_generics: /* generics  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2344 "gen/gen_parser.c"
        break;

    case YYSYMBOL_struct: /* struct  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2350 "gen/gen_parser.c"
        break;

    case YYSYMBOL_template_elem: /* template_elem  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2356 "gen/gen_parser.c"
        break;

    case YYSYMBOL_template_elems: /* template_elems  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2362 "gen/gen_parser.c"
        break;

    case YYSYMBOL_types: /* types  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2368 "gen/gen_parser.c"
        break;

    case YYSYMBOL_alias: /* alias  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2374 "gen/gen_parser.c"
        break;

    case YYSYMBOL_template: /* template  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2380 "gen/gen_parser.c"
        break;

    case YYSYMBOL_enum_val: /* enum_val  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2386 "gen/gen_parser.c"
        break;

    case YYSYMBOL_enums: /* enums  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2392 "gen/gen_parser.c"
        break;

    case YYSYMBOL_enum: /* enum  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2398 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top_if: /* top_if  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2404 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top_var_decl: /* top_var_decl  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2410 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top_var_init: /* top_var_init  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2416 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top_var: /* top_var  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2422 "gen/gen_parser.c"
        break;

    case YYSYMBOL_top: /* top  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2428 "gen/gen_parser.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 160 "src/parser.y"
            { destroy_ast_tree(((*yyvaluep).node)); }
#line 2434 "gen/gen_parser.c"
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
#line 2743 "gen/gen_parser.c"
    break;

  case 3: /* apply: APPLY  */
#line 171 "src/parser.y"
                {
		(yyval.node) = gen_id(strdup((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 2752 "gen/gen_parser.c"
    break;

  case 4: /* var: var_decl  */
#line 177 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2758 "gen/gen_parser.c"
    break;

  case 5: /* var: var_init  */
#line 178 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2764 "gen/gen_parser.c"
    break;

  case 6: /* embed: "embed" "(" STRING ")"  */
#line 181 "src/parser.y"
                                 { (yyval.node) = gen_embed(clone_string((yyvsp[-1].str)));  }
#line 2770 "gen/gen_parser.c"
    break;

  case 7: /* import: "import" STRING  */
#line 184 "src/parser.y"
                          { (yyval.node) = gen_import(clone_string((yyvsp[0].str)));  }
#line 2776 "gen/gen_parser.c"
    break;

  case 8: /* assign: expr "=" expr  */
#line 187 "src/parser.y"
                        { (yyval.node) = gen_assign((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2782 "gen/gen_parser.c"
    break;

  case 9: /* binop: expr "+" expr  */
#line 190 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2788 "gen/gen_parser.c"
    break;

  case 10: /* binop: expr "-" expr  */
#line 191 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2794 "gen/gen_parser.c"
    break;

  case 11: /* binop: expr "*" expr  */
#line 192 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2800 "gen/gen_parser.c"
    break;

  case 12: /* binop: expr "/" expr  */
#line 193 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2806 "gen/gen_parser.c"
    break;

  case 13: /* binop: expr "%" expr  */
#line 194 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2812 "gen/gen_parser.c"
    break;

  case 14: /* binop: expr "^" expr  */
#line 195 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2818 "gen/gen_parser.c"
    break;

  case 15: /* binop: expr "^^" expr  */
#line 196 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_POW, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2824 "gen/gen_parser.c"
    break;

  case 16: /* binop: expr "&" expr  */
#line 197 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2830 "gen/gen_parser.c"
    break;

  case 17: /* binop: expr "&&" expr  */
#line 198 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LAND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2836 "gen/gen_parser.c"
    break;

  case 18: /* binop: expr "|" expr  */
#line 199 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2842 "gen/gen_parser.c"
    break;

  case 19: /* binop: expr "||" expr  */
#line 200 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2848 "gen/gen_parser.c"
    break;

  case 20: /* binop: expr "<<" expr  */
#line 201 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2854 "gen/gen_parser.c"
    break;

  case 21: /* binop: expr ">>" expr  */
#line 202 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2860 "gen/gen_parser.c"
    break;

  case 22: /* binop: expr "+=" expr  */
#line 203 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2866 "gen/gen_parser.c"
    break;

  case 23: /* binop: expr "-=" expr  */
#line 204 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2872 "gen/gen_parser.c"
    break;

  case 24: /* binop: expr "*=" expr  */
#line 205 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2878 "gen/gen_parser.c"
    break;

  case 25: /* binop: expr "/=" expr  */
#line 206 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2884 "gen/gen_parser.c"
    break;

  case 26: /* binop: expr "%=" expr  */
#line 207 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2890 "gen/gen_parser.c"
    break;

  case 27: /* binop: expr "&=" expr  */
#line 208 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2896 "gen/gen_parser.c"
    break;

  case 28: /* binop: expr "|=" expr  */
#line 209 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2902 "gen/gen_parser.c"
    break;

  case 29: /* binop: expr "^=" expr  */
#line 210 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_ASSIGN_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2908 "gen/gen_parser.c"
    break;

  case 30: /* binop: expr "<<=" expr  */
#line 211 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2916 "gen/gen_parser.c"
    break;

  case 31: /* binop: expr ">>=" expr  */
#line 214 "src/parser.y"
                          {
		(yyval.node) = gen_binop(AST_ASSIGN_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));
	}
#line 2924 "gen/gen_parser.c"
    break;

  case 32: /* binop: expr "<" expr  */
#line 217 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_LT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2930 "gen/gen_parser.c"
    break;

  case 33: /* binop: expr ">" expr  */
#line 218 "src/parser.y"
                        { (yyval.node) = gen_binop(AST_GT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2936 "gen/gen_parser.c"
    break;

  case 34: /* binop: expr "<=" expr  */
#line 219 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_LE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2942 "gen/gen_parser.c"
    break;

  case 35: /* binop: expr ">=" expr  */
#line 220 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_GE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2948 "gen/gen_parser.c"
    break;

  case 36: /* binop: expr "!=" expr  */
#line 221 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_NE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2954 "gen/gen_parser.c"
    break;

  case 37: /* binop: expr "==" expr  */
#line 222 "src/parser.y"
                         { (yyval.node) = gen_binop(AST_EQ, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 2960 "gen/gen_parser.c"
    break;

  case 38: /* unop: "-" expr  */
#line 225 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NEG, (yyvsp[0].node));  }
#line 2966 "gen/gen_parser.c"
    break;

  case 39: /* unop: "!" expr  */
#line 226 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_LNOT, (yyvsp[0].node));  }
#line 2972 "gen/gen_parser.c"
    break;

  case 40: /* unop: "&" expr  */
#line 227 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 2978 "gen/gen_parser.c"
    break;

  case 41: /* unop: "'" expr  */
#line 228 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_DEREF, (yyvsp[0].node));  }
#line 2984 "gen/gen_parser.c"
    break;

  case 42: /* unop: "~" expr  */
#line 229 "src/parser.y"
                   { (yyval.node) = gen_unop(AST_NOT, (yyvsp[0].node));  }
#line 2990 "gen/gen_parser.c"
    break;

  case 43: /* arg: "&" var_decl  */
#line 232 "src/parser.y"
                       { (yyval.node) = gen_unop(AST_REF, (yyvsp[0].node));  }
#line 2996 "gen/gen_parser.c"
    break;

  case 44: /* arg: var_decl  */
#line 233 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3002 "gen/gen_parser.c"
    break;

  case 45: /* arg: expr  */
#line 234 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3008 "gen/gen_parser.c"
    break;

  case 46: /* args: arg "," args  */
#line 237 "src/parser.y"
                       { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3014 "gen/gen_parser.c"
    break;

  case 47: /* args: arg  */
#line 238 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3020 "gen/gen_parser.c"
    break;

  case 48: /* param_decl: type  */
#line 241 "src/parser.y"
               { (yyval.node) = gen_var(NULL, (yyvsp[0].node), NULL);  }
#line 3026 "gen/gen_parser.c"
    break;

  case 49: /* decls: var_decl "," decls  */
#line 244 "src/parser.y"
                             { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3032 "gen/gen_parser.c"
    break;

  case 50: /* decls: param_decl "," decls  */
#line 245 "src/parser.y"
                               { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3038 "gen/gen_parser.c"
    break;

  case 51: /* decls: var_decl  */
#line 246 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3044 "gen/gen_parser.c"
    break;

  case 52: /* decls: param_decl  */
#line 247 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 3050 "gen/gen_parser.c"
    break;

  case 53: /* decls: "..." id  */
#line 248 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_VARIADIC); }
#line 3056 "gen/gen_parser.c"
    break;

  case 54: /* defer: "defer" expr  */
#line 251 "src/parser.y"
                       { (yyval.node) = gen_defer((yyvsp[0].node));  }
#line 3062 "gen/gen_parser.c"
    break;

  case 55: /* const_binop: const_expr "+" const_expr  */
#line 254 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_ADD, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3068 "gen/gen_parser.c"
    break;

  case 56: /* const_binop: const_expr "-" const_expr  */
#line 255 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_SUB, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3074 "gen/gen_parser.c"
    break;

  case 57: /* const_binop: const_expr "*" const_expr  */
#line 256 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_MUL, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3080 "gen/gen_parser.c"
    break;

  case 58: /* const_binop: const_expr "/" const_expr  */
#line 257 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_DIV, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3086 "gen/gen_parser.c"
    break;

  case 59: /* const_binop: const_expr "%" const_expr  */
#line 258 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_REM, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3092 "gen/gen_parser.c"
    break;

  case 60: /* const_binop: const_expr "^" const_expr  */
#line 259 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_XOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3098 "gen/gen_parser.c"
    break;

  case 61: /* const_binop: const_expr "^^" const_expr  */
#line 260 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_POW, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3104 "gen/gen_parser.c"
    break;

  case 62: /* const_binop: const_expr "&" const_expr  */
#line 261 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_AND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3110 "gen/gen_parser.c"
    break;

  case 63: /* const_binop: const_expr "&&" const_expr  */
#line 262 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_LAND, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3116 "gen/gen_parser.c"
    break;

  case 64: /* const_binop: const_expr "|" const_expr  */
#line 263 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_OR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3122 "gen/gen_parser.c"
    break;

  case 65: /* const_binop: const_expr "||" const_expr  */
#line 264 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_LOR, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3128 "gen/gen_parser.c"
    break;

  case 66: /* const_binop: const_expr "<<" const_expr  */
#line 265 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3134 "gen/gen_parser.c"
    break;

  case 67: /* const_binop: const_expr ">>" const_expr  */
#line 266 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3140 "gen/gen_parser.c"
    break;

  case 68: /* const_binop: const_expr "<" const_expr  */
#line 267 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_LT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3146 "gen/gen_parser.c"
    break;

  case 69: /* const_binop: const_expr ">" const_expr  */
#line 268 "src/parser.y"
                                    { (yyval.node) = gen_binop(AST_GT, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3152 "gen/gen_parser.c"
    break;

  case 70: /* const_binop: const_expr "<=" const_expr  */
#line 269 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_LE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3158 "gen/gen_parser.c"
    break;

  case 71: /* const_binop: const_expr ">=" const_expr  */
#line 270 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_GE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3164 "gen/gen_parser.c"
    break;

  case 72: /* const_binop: const_expr "!=" const_expr  */
#line 271 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_NE, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3170 "gen/gen_parser.c"
    break;

  case 73: /* const_binop: const_expr "==" const_expr  */
#line 272 "src/parser.y"
                                     { (yyval.node) = gen_binop(AST_EQ, (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3176 "gen/gen_parser.c"
    break;

  case 74: /* const_unop: "-" const_expr  */
#line 275 "src/parser.y"
                         { (yyval.node) = gen_unop(AST_NEG, (yyvsp[0].node));  }
#line 3182 "gen/gen_parser.c"
    break;

  case 75: /* const_unop: "!" const_expr  */
#line 276 "src/parser.y"
                         { (yyval.node) = gen_unop(AST_LNOT, (yyvsp[0].node));  }
#line 3188 "gen/gen_parser.c"
    break;

  case 76: /* const_unop: "~" const_expr  */
#line 277 "src/parser.y"
                         { (yyval.node) = gen_unop(AST_NOT, (yyvsp[0].node));  }
#line 3194 "gen/gen_parser.c"
    break;

  case 77: /* const_expr: "(" const_expr ")"  */
#line 280 "src/parser.y"
                             { (yyval.node) = (yyvsp[-1].node); }
#line 3200 "gen/gen_parser.c"
    break;

  case 78: /* const_expr: id  */
#line 281 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3206 "gen/gen_parser.c"
    break;

  case 79: /* const_expr: INT  */
#line 282 "src/parser.y"
              { (yyval.node) = gen_int((yyvsp[0].integer)); }
#line 3212 "gen/gen_parser.c"
    break;

  case 80: /* const_expr: FLOAT  */
#line 283 "src/parser.y"
                { (yyval.node) = gen_float((yyvsp[0].dbl)); }
#line 3218 "gen/gen_parser.c"
    break;

  case 81: /* const_expr: const_binop  */
#line 284 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3224 "gen/gen_parser.c"
    break;

  case 82: /* const_expr: const_unop  */
#line 285 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 3230 "gen/gen_parser.c"
    break;

  case 83: /* expr: id  */
#line 289 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3236 "gen/gen_parser.c"
    break;

  case 84: /* expr: expr "." id  */
#line 290 "src/parser.y"
                      { (yyval.node) = gen_dot((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3242 "gen/gen_parser.c"
    break;

  case 85: /* expr: "..." id  */
#line 291 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3248 "gen/gen_parser.c"
    break;

  case 86: /* expr: INT  */
#line 292 "src/parser.y"
              { (yyval.node) = gen_int((yyvsp[0].integer)); (yyval.node)->loc = to_src_loc(&yylloc); }
#line 3254 "gen/gen_parser.c"
    break;

  case 87: /* expr: FLOAT  */
#line 293 "src/parser.y"
                { (yyval.node) = gen_float((yyvsp[0].dbl)); (yyval.node)->loc = to_src_loc(&yylloc);  }
#line 3260 "gen/gen_parser.c"
    break;

  case 88: /* expr: STRING  */
#line 294 "src/parser.y"
                 {
		(yyval.node) = gen_string(clone_string((yyvsp[0].str)));
		(yyval.node)->loc = to_src_loc(&yylloc);
	}
#line 3269 "gen/gen_parser.c"
    break;

  case 89: /* expr: "(" expr ")"  */
#line 298 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3275 "gen/gen_parser.c"
    break;

  case 90: /* expr: assign  */
#line 299 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3281 "gen/gen_parser.c"
    break;

  case 91: /* expr: expr "(" args ")"  */
#line 300 "src/parser.y"
                            { (yyval.node) = gen_call((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3287 "gen/gen_parser.c"
    break;

  case 92: /* expr: expr "(" ")"  */
#line 301 "src/parser.y"
                       { (yyval.node) = gen_call((yyvsp[-2].node), NULL); }
#line 3293 "gen/gen_parser.c"
    break;

  case 93: /* expr: expr "[" expr "]"  */
#line 302 "src/parser.y"
                            { (yyval.node) = gen_call((yyvsp[-3].node), (yyvsp[-1].node)); /** @todo add arr access */}
#line 3299 "gen/gen_parser.c"
    break;

  case 94: /* expr: apply "(" args ")"  */
#line 303 "src/parser.y"
                             { (yyval.node) = gen_call((yyvsp[-3].node), (yyvsp[-1].node)); /* macro call */}
#line 3305 "gen/gen_parser.c"
    break;

  case 95: /* expr: apply "(" ")"  */
#line 304 "src/parser.y"
                        { (yyval.node) = gen_call((yyvsp[-2].node), NULL); /* macro call */}
#line 3311 "gen/gen_parser.c"
    break;

  case 96: /* expr: binop  */
#line 305 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3317 "gen/gen_parser.c"
    break;

  case 97: /* expr: unop  */
#line 306 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3323 "gen/gen_parser.c"
    break;

  case 98: /* expr: "(" var_init ")"  */
#line 307 "src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 3329 "gen/gen_parser.c"
    break;

  case 99: /* expr: "sizeof" expr  */
#line 308 "src/parser.y"
                        { (yyval.node) = gen_sizeof((yyvsp[0].node)); }
#line 3335 "gen/gen_parser.c"
    break;

  case 100: /* expr: expr "as" type  */
#line 309 "src/parser.y"
                         { (yyval.node) = gen_cast((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3341 "gen/gen_parser.c"
    break;

  case 101: /* expr: id "::" type  */
#line 310 "src/parser.y"
                       { (yyval.node) = gen_fetch((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3347 "gen/gen_parser.c"
    break;

  case 102: /* expr: "as" type  */
#line 311 "src/parser.y"
                    { (yyval.node) = gen_as((yyvsp[0].node)); }
#line 3353 "gen/gen_parser.c"
    break;

  case 103: /* expr: embed  */
#line 312 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3359 "gen/gen_parser.c"
    break;

  case 104: /* expr: lambda  */
#line 313 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3365 "gen/gen_parser.c"
    break;

  case 105: /* expr: if  */
#line 314 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3371 "gen/gen_parser.c"
    break;

  case 106: /* expr: switch  */
#line 315 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3377 "gen/gen_parser.c"
    break;

  case 107: /* expr: construct  */
#line 316 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3383 "gen/gen_parser.c"
    break;

  case 108: /* expr: "(" body ")"  */
#line 317 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3389 "gen/gen_parser.c"
    break;

  case 109: /* while: "while" expr body  */
#line 320 "src/parser.y"
                            { (yyval.node) = gen_while((yyvsp[-1].node), (yyvsp[0].node));  }
#line 3395 "gen/gen_parser.c"
    break;

  case 110: /* do_while: "do" body "while" expr ";"  */
#line 323 "src/parser.y"
                                     {
		(yyval.node) = gen_while((yyvsp[-3].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_DELAYED);
	}
#line 3404 "gen/gen_parser.c"
    break;

  case 111: /* goto: "goto" id  */
#line 329 "src/parser.y"
                    { (yyval.node) = gen_goto(gen_label((yyvsp[0].node)));  }
#line 3410 "gen/gen_parser.c"
    break;

  case 112: /* statelet: expr  */
#line 332 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3416 "gen/gen_parser.c"
    break;

  case 113: /* statelet: "return" expr  */
#line 333 "src/parser.y"
                        { (yyval.node) = gen_return((yyvsp[0].node));  }
#line 3422 "gen/gen_parser.c"
    break;

  case 114: /* statelet: "return"  */
#line 334 "src/parser.y"
                   { (yyval.node) = gen_return(NULL); }
#line 3428 "gen/gen_parser.c"
    break;

  case 115: /* statelet: "break"  */
#line 335 "src/parser.y"
                  { (yyval.node) = gen_ctrl(AST_CTRL_BREAK, to_src_loc(&yylloc)); }
#line 3434 "gen/gen_parser.c"
    break;

  case 116: /* statelet: "continue"  */
#line 336 "src/parser.y"
                     { (yyval.node) = gen_ctrl(AST_CTRL_CONTINUE, to_src_loc(&yylloc)); }
#line 3440 "gen/gen_parser.c"
    break;

  case 117: /* statelet: import  */
#line 337 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3446 "gen/gen_parser.c"
    break;

  case 118: /* statelet: var  */
#line 338 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3452 "gen/gen_parser.c"
    break;

  case 119: /* statelet: goto  */
#line 339 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3458 "gen/gen_parser.c"
    break;

  case 120: /* statelet: id ":"  */
#line 340 "src/parser.y"
                 { (yyval.node) = gen_label((yyvsp[-1].node));  }
#line 3464 "gen/gen_parser.c"
    break;

  case 121: /* statelet: for  */
#line 341 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3470 "gen/gen_parser.c"
    break;

  case 122: /* statelet: const  */
#line 342 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3476 "gen/gen_parser.c"
    break;

  case 123: /* statelet: while  */
#line 343 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3482 "gen/gen_parser.c"
    break;

  case 124: /* statelet: do_while  */
#line 344 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3488 "gen/gen_parser.c"
    break;

  case 125: /* statelet: macro  */
#line 345 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3494 "gen/gen_parser.c"
    break;

  case 126: /* statelet: struct  */
#line 346 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 3500 "gen/gen_parser.c"
    break;

  case 127: /* statelet: alias  */
#line 347 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3506 "gen/gen_parser.c"
    break;

  case 128: /* statelet: template  */
#line 348 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3512 "gen/gen_parser.c"
    break;

  case 129: /* statelet: defer  */
#line 349 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 3518 "gen/gen_parser.c"
    break;

  case 130: /* statelet: enum  */
#line 350 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3524 "gen/gen_parser.c"
    break;

  case 131: /* statelet: body  */
#line 351 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3530 "gen/gen_parser.c"
    break;

  case 132: /* statelet: ";"  */
#line 352 "src/parser.y"
              { (yyval.node) = gen_empty();  }
#line 3536 "gen/gen_parser.c"
    break;

  case 133: /* statelet: error  */
#line 353 "src/parser.y"
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
#line 3555 "gen/gen_parser.c"
    break;

  case 134: /* statement: statelet ";"  */
#line 369 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 3561 "gen/gen_parser.c"
    break;

  case 135: /* statements: statement statements  */
#line 372 "src/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3567 "gen/gen_parser.c"
    break;

  case 136: /* statements: statement  */
#line 373 "src/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3573 "gen/gen_parser.c"
    break;

  case 137: /* statements: statelet  */
#line 374 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3579 "gen/gen_parser.c"
    break;

  case 138: /* body: "{" statements "}"  */
#line 377 "src/parser.y"
                             { (yyval.node) = gen_block((yyvsp[-1].node));  }
#line 3585 "gen/gen_parser.c"
    break;

  case 139: /* body: "{" "}"  */
#line 378 "src/parser.y"
                  { (yyval.node) = gen_block(gen_empty());  }
#line 3591 "gen/gen_parser.c"
    break;

  case 140: /* references: id "," references  */
#line 381 "src/parser.y"
                            { (yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 3597 "gen/gen_parser.c"
    break;

  case 141: /* references: id  */
#line 382 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3603 "gen/gen_parser.c"
    break;

  case 142: /* references: "..." id  */
#line 383 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_VARIADIC); }
#line 3609 "gen/gen_parser.c"
    break;

  case 143: /* macro: "define" id "(" references ")" body  */
#line 387 "src/parser.y"
                                              {
		(yyval.node) = gen_macro((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3618 "gen/gen_parser.c"
    break;

  case 144: /* macro: "define" id "(" references "..." id ")" body  */
#line 391 "src/parser.y"
                                                       {
		/* TODO: the location data of the variadic ID is way off */
		ast_append((yyvsp[-4].node), (yyvsp[-2].node));
		(yyval.node) = gen_macro((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_VARIADIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3630 "gen/gen_parser.c"
    break;

  case 145: /* macro: "define" id "(" ")" body  */
#line 398 "src/parser.y"
                                   {
		(yyval.node) = gen_macro((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3639 "gen/gen_parser.c"
    break;

  case 146: /* exprs: expr "," exprs  */
#line 404 "src/parser.y"
                         { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3645 "gen/gen_parser.c"
    break;

  case 147: /* exprs: expr  */
#line 405 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3651 "gen/gen_parser.c"
    break;

  case 148: /* construct_arg: expr  */
#line 408 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3657 "gen/gen_parser.c"
    break;

  case 149: /* construct_arg: "." id "=" expr  */
#line 409 "src/parser.y"
                          {
		(yyval.node) = gen_var((yyvsp[-2].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_MEMBER);
	}
#line 3666 "gen/gen_parser.c"
    break;

  case 150: /* construct_args: construct_arg "," construct_args  */
#line 415 "src/parser.y"
                                           { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3672 "gen/gen_parser.c"
    break;

  case 151: /* construct_args: construct_arg  */
#line 416 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 3678 "gen/gen_parser.c"
    break;

  case 152: /* construct: "!" "{" construct_args "}"  */
#line 419 "src/parser.y"
                                     { (yyval.node) = gen_init((yyvsp[-1].node)); }
#line 3684 "gen/gen_parser.c"
    break;

  case 153: /* if: "if" expr body  */
#line 422 "src/parser.y"
                         { (yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3690 "gen/gen_parser.c"
    break;

  case 154: /* if: "if" expr body "else" body  */
#line 423 "src/parser.y"
                                     { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3696 "gen/gen_parser.c"
    break;

  case 155: /* if: "if" expr body "else" if  */
#line 424 "src/parser.y"
                                   { (yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));  }
#line 3702 "gen/gen_parser.c"
    break;

  case 156: /* for: "for" arg ";" expr ";" expr body  */
#line 428 "src/parser.y"
                                           { (yyval.node) = gen_for((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3708 "gen/gen_parser.c"
    break;

  case 157: /* case: "case" const_expr ":" statements  */
#line 431 "src/parser.y"
                                           {
		(yyval.node) = gen_case((yyvsp[-2].node), (yyvsp[0].node));  }
#line 3715 "gen/gen_parser.c"
    break;

  case 158: /* case: "default" ":" statements  */
#line 433 "src/parser.y"
                                   {
		(yyval.node) = gen_case(NULL, (yyvsp[0].node));
	}
#line 3723 "gen/gen_parser.c"
    break;

  case 159: /* cases: case cases  */
#line 438 "src/parser.y"
                     { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 3729 "gen/gen_parser.c"
    break;

  case 160: /* cases: case  */
#line 439 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 3735 "gen/gen_parser.c"
    break;

  case 161: /* switch: "switch" expr "{" cases "}"  */
#line 442 "src/parser.y"
                                      { (yyval.node) = gen_switch((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3741 "gen/gen_parser.c"
    break;

  case 162: /* const_for: "for" id ":" exprs body  */
#line 446 "src/parser.y"
                                  {
		/* TODO: should id be a separate rule? */
		(yyval.node) = gen_for((yyvsp[-3].node), NULL, (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3751 "gen/gen_parser.c"
    break;

  case 163: /* const_if: "if" const_expr body  */
#line 453 "src/parser.y"
                               {
		(yyval.node) = gen_if((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3760 "gen/gen_parser.c"
    break;

  case 164: /* const_if: "if" const_expr body "else" body  */
#line 457 "src/parser.y"
                                           {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
		ast_set_flags((yyvsp[0].node), AST_FLAG_UNHYGIENIC);
	}
#line 3770 "gen/gen_parser.c"
    break;

  case 165: /* const_if: "if" const_expr body "else" const_if  */
#line 462 "src/parser.y"
                                               {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
		ast_set_flags((yyvsp[-2].node), AST_FLAG_UNHYGIENIC);
	}
#line 3779 "gen/gen_parser.c"
    break;

  case 166: /* const: "const" const_if  */
#line 470 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 3785 "gen/gen_parser.c"
    break;

  case 167: /* const: "const" const_for  */
#line 471 "src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 3791 "gen/gen_parser.c"
    break;

  case 168: /* func_sign: "(" decls "=>" type ")"  */
#line 474 "src/parser.y"
                                  {
		(yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 3799 "gen/gen_parser.c"
    break;

  case 169: /* func_sign: "(" decls ")"  */
#line 477 "src/parser.y"
                        { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-1].node), NULL); }
#line 3805 "gen/gen_parser.c"
    break;

  case 170: /* func_sign: "(" decls "=>" ")"  */
#line 478 "src/parser.y"
                             { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, (yyvsp[-2].node), NULL); }
#line 3811 "gen/gen_parser.c"
    break;

  case 171: /* func_sign: "(" "=>" type ")"  */
#line 479 "src/parser.y"
                            { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, (yyvsp[-1].node)); }
#line 3817 "gen/gen_parser.c"
    break;

  case 172: /* func_sign: "(" ")"  */
#line 480 "src/parser.y"
                  { (yyval.node) = gen_type(AST_TYPE_SIGN, NULL, NULL, NULL); }
#line 3823 "gen/gen_parser.c"
    break;

  case 173: /* type: id  */
#line 483 "src/parser.y"
             { (yyval.node) = gen_type(AST_TYPE_ID, (yyvsp[0].node), NULL, NULL); }
#line 3829 "gen/gen_parser.c"
    break;

  case 174: /* type: "@" func_sign  */
#line 484 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3838 "gen/gen_parser.c"
    break;

  case 175: /* type: apply "[" types "]"  */
#line 488 "src/parser.y"
                              {
		(yyval.node) = gen_type(AST_TYPE_GENERIC, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
	}
#line 3846 "gen/gen_parser.c"
    break;

  case 176: /* type: "'" type  */
#line 491 "src/parser.y"
                   {
		(yyval.node) = gen_type(AST_TYPE_POINTER, NULL, NULL, NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3855 "gen/gen_parser.c"
    break;

  case 177: /* type: "'" "[" const_expr "]" type  */
#line 495 "src/parser.y"
                                      {
		(yyval.node) = gen_type(AST_TYPE_ARR, NULL, (yyvsp[-2].node), NULL);
		(yyval.node)->_type.next = (yyvsp[0].node);
	}
#line 3864 "gen/gen_parser.c"
    break;

  case 178: /* type: "typeof" expr  */
#line 499 "src/parser.y"
                        {
		(yyval.node) = gen_type(AST_TYPE_TYPEOF, NULL, (yyvsp[0].node), NULL);
	}
#line 3872 "gen/gen_parser.c"
    break;

  case 179: /* type: id "::" type  */
#line 502 "src/parser.y"
                       {
		(yyval.node) = gen_type(AST_TYPE_MEMBER, (yyvsp[-2].node), (yyvsp[0].node), NULL);
	}
#line 3880 "gen/gen_parser.c"
    break;

  case 180: /* var_decl: id "mut" type  */
#line 507 "src/parser.y"
                        {
		(yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_MUTABLE);
	}
#line 3889 "gen/gen_parser.c"
    break;

  case 181: /* var_decl: id "const" type  */
#line 511 "src/parser.y"
                          { (yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);  }
#line 3895 "gen/gen_parser.c"
    break;

  case 182: /* var_decl: id type  */
#line 512 "src/parser.y"
                  { (yyval.node) = gen_var((yyvsp[-1].node), (yyvsp[0].node), NULL);  }
#line 3901 "gen/gen_parser.c"
    break;

  case 183: /* var_init: var_decl "=" expr  */
#line 515 "src/parser.y"
                            { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->_var.init = (yyvsp[0].node); }
#line 3907 "gen/gen_parser.c"
    break;

  case 184: /* var_init: id "mut" "=" expr  */
#line 516 "src/parser.y"
                            {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED | AST_FLAG_MUTABLE);
	}
#line 3916 "gen/gen_parser.c"
    break;

  case 185: /* var_init: id "const" "=" expr  */
#line 520 "src/parser.y"
                              {
		(yyval.node) = gen_var((yyvsp[-3].node), NULL, (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 3925 "gen/gen_parser.c"
    break;

  case 186: /* proc: id func_sign body  */
#line 526 "src/parser.y"
                            {
		(yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), (yyvsp[-1].node)->flags);
	}
#line 3934 "gen/gen_parser.c"
    break;

  case 187: /* proc: "extern" id func_sign  */
#line 530 "src/parser.y"
                                {
		/* todo check that we don't have a variadic function */
		(yyval.node) = gen_proc((yyvsp[-1].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_EXTERN);
	}
#line 3944 "gen/gen_parser.c"
    break;

  case 188: /* captures: id "," captures  */
#line 537 "src/parser.y"
                          { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3950 "gen/gen_parser.c"
    break;

  case 189: /* captures: id  */
#line 538 "src/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3956 "gen/gen_parser.c"
    break;

  case 190: /* lambda: "[" captures "]" func_sign body  */
#line 541 "src/parser.y"
                                          { (yyval.node) = gen_lambda((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3962 "gen/gen_parser.c"
    break;

  case 191: /* lambda: "[" captures "]" body  */
#line 542 "src/parser.y"
                                { (yyval.node) = gen_lambda((yyvsp[-2].node), NULL, (yyvsp[0].node)); }
#line 3968 "gen/gen_parser.c"
    break;

  case 192: /* struct_elem: var_decl  */
#line 545 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3974 "gen/gen_parser.c"
    break;

  case 193: /* members: struct_elem ";" members  */
#line 548 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 3980 "gen/gen_parser.c"
    break;

  case 194: /* members: struct_elem ";"  */
#line 549 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 3986 "gen/gen_parser.c"
    break;

  case 195: /* union: "union" id "{" members "}"  */
#line 552 "src/parser.y"
                                     {
		(yyval.node) = gen_union((yyvsp[-3].node), NULL, (yyvsp[-1].node));
	}
#line 3994 "gen/gen_parser.c"
    break;

  case 196: /* union: "union" id "(" generics ")" "{" members "}"  */
#line 555 "src/parser.y"
                                                      {
		(yyval.node) = gen_union((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
	}
#line 4002 "gen/gen_parser.c"
    break;

  case 197: /* generic: id type  */
#line 560 "src/parser.y"
                  { (yyval.node) = gen_alias((yyvsp[-1].node), (yyvsp[0].node)); }
#line 4008 "gen/gen_parser.c"
    break;

  case 198: /* generics: generic "," generics  */
#line 563 "src/parser.y"
                               { (yyval.node) = (yyvsp[-2].node); (yyval.node)->next = (yyvsp[0].node); }
#line 4014 "gen/gen_parser.c"
    break;

  case 199: /* generics: generic  */
#line 564 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 4020 "gen/gen_parser.c"
    break;

  case 200: /* struct: "struct" id "{" members "}"  */
#line 567 "src/parser.y"
                                      {
		(yyval.node) = gen_struct((yyvsp[-3].node), NULL, (yyvsp[-1].node));
	}
#line 4028 "gen/gen_parser.c"
    break;

  case 201: /* struct: "struct" id "(" generics ")" "{" members "}"  */
#line 570 "src/parser.y"
                                                       {
		(yyval.node) = gen_struct((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
	}
#line 4036 "gen/gen_parser.c"
    break;

  case 202: /* template_elem: id ";"  */
#line 577 "src/parser.y"
                 { (yyval.node) = (yyvsp[-1].node); }
#line 4042 "gen/gen_parser.c"
    break;

  case 203: /* template_elem: id func_sign ";"  */
#line 578 "src/parser.y"
                           { (yyval.node) = gen_proc((yyvsp[-2].node), (yyvsp[-1].node), NULL);  }
#line 4048 "gen/gen_parser.c"
    break;

  case 204: /* template_elem: var_decl ";"  */
#line 579 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 4054 "gen/gen_parser.c"
    break;

  case 205: /* template_elem: union  */
#line 580 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 4060 "gen/gen_parser.c"
    break;

  case 206: /* template_elems: template_elem template_elems  */
#line 583 "src/parser.y"
                                       { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 4066 "gen/gen_parser.c"
    break;

  case 207: /* template_elems: template_elem  */
#line 584 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 4072 "gen/gen_parser.c"
    break;

  case 208: /* types: type "," types  */
#line 587 "src/parser.y"
                         { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 4078 "gen/gen_parser.c"
    break;

  case 209: /* types: type  */
#line 588 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 4084 "gen/gen_parser.c"
    break;

  case 210: /* alias: "typedef" id type  */
#line 591 "src/parser.y"
                            { (yyval.node) = gen_alias((yyvsp[-1].node), (yyvsp[0].node));  }
#line 4090 "gen/gen_parser.c"
    break;

  case 211: /* template: "typedef" id "{" template_elems "}"  */
#line 596 "src/parser.y"
                                              {
		(yyval.node) = gen_template((yyvsp[-3].node), (yyvsp[-1].node));
	}
#line 4098 "gen/gen_parser.c"
    break;

  case 212: /* template: "typedef" id "{" "}"  */
#line 599 "src/parser.y"
                               {
		/* should match anything, but doesn't implement anything */
		(yyval.node) = gen_template((yyvsp[-2].node), NULL);
	}
#line 4107 "gen/gen_parser.c"
    break;

  case 213: /* enum_val: id  */
#line 605 "src/parser.y"
             { (yyval.node) = gen_val((yyvsp[0].node), NULL);  }
#line 4113 "gen/gen_parser.c"
    break;

  case 214: /* enum_val: id "=" expr  */
#line 606 "src/parser.y"
                      { (yyval.node) = gen_val((yyvsp[-2].node), (yyvsp[0].node));  }
#line 4119 "gen/gen_parser.c"
    break;

  case 215: /* enums: enum_val "," enums  */
#line 609 "src/parser.y"
                             { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->next = (yyvsp[0].node); }
#line 4125 "gen/gen_parser.c"
    break;

  case 216: /* enums: enum_val ","  */
#line 610 "src/parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 4131 "gen/gen_parser.c"
    break;

  case 217: /* enums: enum_val  */
#line 611 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 4137 "gen/gen_parser.c"
    break;

  case 218: /* enum: "enum" id ":" type "{" enums "}"  */
#line 614 "src/parser.y"
                                           { (yyval.node) = gen_enum((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 4143 "gen/gen_parser.c"
    break;

  case 219: /* enum: "enum" id "{" enums "}"  */
#line 615 "src/parser.y"
                                  {
		(yyval.node) = gen_enum((yyvsp[-3].node), NULL, (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNTYPED);
	}
#line 4152 "gen/gen_parser.c"
    break;

  case 220: /* top_if: "if" const_expr "{" unit "}"  */
#line 621 "src/parser.y"
                                       {
		(yyval.node) = gen_if((yyvsp[-3].node), (yyvsp[-1].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 4161 "gen/gen_parser.c"
    break;

  case 221: /* top_if: "if" const_expr "{" unit "}" "else" "{" unit "}"  */
#line 625 "src/parser.y"
                                                           {
		(yyval.node) = gen_if((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-1].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 4170 "gen/gen_parser.c"
    break;

  case 222: /* top_if: "if" const_expr "{" unit "}" "else" top_if  */
#line 629 "src/parser.y"
                                                     {
		(yyval.node) = gen_if((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[0].node));
		ast_set_flags((yyval.node), AST_FLAG_UNHYGIENIC);
	}
#line 4179 "gen/gen_parser.c"
    break;

  case 223: /* top_var_decl: id "mut" type  */
#line 635 "src/parser.y"
                        {
		(yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL);
		ast_set_flags((yyval.node), AST_FLAG_MUTABLE);
	}
#line 4188 "gen/gen_parser.c"
    break;

  case 224: /* top_var_decl: id "const" type  */
#line 639 "src/parser.y"
                          { (yyval.node) = gen_var((yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 4194 "gen/gen_parser.c"
    break;

  case 225: /* top_var_decl: id type  */
#line 640 "src/parser.y"
                  { (yyval.node) = gen_var((yyvsp[-1].node), (yyvsp[0].node), NULL); }
#line 4200 "gen/gen_parser.c"
    break;

  case 226: /* top_var_init: top_var_decl "=" const_expr  */
#line 643 "src/parser.y"
                                      { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->_var.init = (yyvsp[0].node); }
#line 4206 "gen/gen_parser.c"
    break;

  case 227: /* top_var_init: id "mut" "=" const_expr  */
#line 644 "src/parser.y"
                                  { (yyval.node) = (yyvsp[-3].node); (yyvsp[-3].node)->_var.init = (yyvsp[0].node); }
#line 4212 "gen/gen_parser.c"
    break;

  case 228: /* top_var_init: id "const" "=" const_expr  */
#line 645 "src/parser.y"
                                    { (yyval.node) = (yyvsp[-3].node); (yyvsp[-3].node)->_var.init = (yyvsp[0].node); }
#line 4218 "gen/gen_parser.c"
    break;

  case 229: /* top_var: top_var_decl  */
#line 648 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 4224 "gen/gen_parser.c"
    break;

  case 230: /* top_var: top_var_init  */
#line 649 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 4230 "gen/gen_parser.c"
    break;

  case 231: /* top: enum  */
#line 654 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 4236 "gen/gen_parser.c"
    break;

  case 232: /* top: proc  */
#line 655 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 4242 "gen/gen_parser.c"
    break;

  case 233: /* top: struct  */
#line 656 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 4248 "gen/gen_parser.c"
    break;

  case 234: /* top: union  */
#line 657 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 4254 "gen/gen_parser.c"
    break;

  case 235: /* top: macro  */
#line 658 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 4260 "gen/gen_parser.c"
    break;

  case 236: /* top: top_if  */
#line 659 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 4266 "gen/gen_parser.c"
    break;

  case 237: /* top: top_var  */
#line 660 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyval.node), AST_FLAG_CONST); }
#line 4272 "gen/gen_parser.c"
    break;

  case 238: /* top: import  */
#line 661 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 4278 "gen/gen_parser.c"
    break;

  case 239: /* top: alias  */
#line 662 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 4284 "gen/gen_parser.c"
    break;

  case 240: /* top: template  */
#line 663 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 4290 "gen/gen_parser.c"
    break;

  case 241: /* top: "pub" enum  */
#line 664 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4296 "gen/gen_parser.c"
    break;

  case 242: /* top: "pub" struct  */
#line 665 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4302 "gen/gen_parser.c"
    break;

  case 243: /* top: "pub" union  */
#line 666 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4308 "gen/gen_parser.c"
    break;

  case 244: /* top: "pub" proc  */
#line 667 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4314 "gen/gen_parser.c"
    break;

  case 245: /* top: "pub" macro  */
#line 668 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4320 "gen/gen_parser.c"
    break;

  case 246: /* top: "pub" import  */
#line 669 "src/parser.y"
                       { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4326 "gen/gen_parser.c"
    break;

  case 247: /* top: "pub" alias  */
#line 670 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4332 "gen/gen_parser.c"
    break;

  case 248: /* top: "pub" template  */
#line 671 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC); }
#line 4338 "gen/gen_parser.c"
    break;

  case 249: /* top: "pub" top_var  */
#line 672 "src/parser.y"
                        {
		(yyval.node) = (yyvsp[0].node); ast_set_flags((yyvsp[0].node), AST_FLAG_PUBLIC);
		ast_set_flags((yyval.node), AST_FLAG_CONST);
	}
#line 4347 "gen/gen_parser.c"
    break;

  case 250: /* top: ";"  */
#line 676 "src/parser.y"
              { (yyval.node) = gen_empty(); }
#line 4353 "gen/gen_parser.c"
    break;

  case 251: /* top: error  */
#line 677 "src/parser.y"
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
#line 4371 "gen/gen_parser.c"
    break;

  case 252: /* unit: top  */
#line 692 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 4377 "gen/gen_parser.c"
    break;

  case 253: /* unit: top unit  */
#line 693 "src/parser.y"
                   { (yyval.node) = (yyvsp[-1].node); (yyvsp[-1].node)->next = (yyvsp[0].node); }
#line 4383 "gen/gen_parser.c"
    break;

  case 254: /* input: unit  */
#line 696 "src/parser.y"
               { parser->tree = (yyvsp[0].node); }
#line 4389 "gen/gen_parser.c"
    break;


#line 4393 "gen/gen_parser.c"

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

#line 699 "src/parser.y"

