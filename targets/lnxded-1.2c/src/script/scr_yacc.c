// Script grammar: GNU Bison 2.0 (yacc.c skeleton) parser with a flex 2.5.31 scanner,
// reconstructed in generated shape.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

typedef union sval_u
{
	int type;
	unsigned int stringValue;
	unsigned int idValue;
	float floatValue;
	int intValue;
	union sval_u *node;
	unsigned int sourcePosValue;
	const char *stringPtrValue;
} sval_u;

typedef struct stype_t
{
	sval_u val;
	unsigned int pos;
} stype_t;

typedef struct scrCompilePub_s
{
	int value_count;
	int far_function_count;
} scrCompilePub_t;

extern scrCompilePub_t scrCompilePub;

void CompileError( unsigned int sourcePos, const char *format, ... );
unsigned int SL_GetString_( const char *str, unsigned int user, int type );
unsigned int SL_GetStringOfLen( const char *str, unsigned int user, unsigned int len, int type );
unsigned int SL_ConvertToLowercase( unsigned int stringValue, unsigned int user, int type );
void SL_TransferRefToUser( unsigned int stringValue, unsigned int user );
int Scr_ScanFile( char *buf, int max_size );

sval_u node0( int type );
sval_u node1( int type, sval_u val1 );
sval_u node2( int type, sval_u val1, sval_u val2 );
sval_u node3( int type, sval_u val1, sval_u val2, sval_u val3 );
sval_u node4( int type, sval_u val1, sval_u val2, sval_u val3, sval_u val4 );
sval_u node5( int type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5 );
sval_u node6( int type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6 );
sval_u node7( int type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6, sval_u val7 );
sval_u node8( int type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6, sval_u val7, sval_u val8 );
sval_u linked_list_end( sval_u val1 );
sval_u prepend_node( sval_u val1, sval_u val2 );
sval_u append_node( sval_u val1, sval_u val2 );
sval_u node1_( int val1 );
sval_u node_pos( unsigned int sourcePos );
sval_u node2_( sval_u val1, sval_u val2 );
sval_u node3_( sval_u val1, sval_u val2, sval_u val3 );
sval_u node4_( sval_u val1, sval_u val2, sval_u val3, sval_u val4 );

int yylex();
int yyerror( const char *msg );

#define YYSTYPE stype_t
#define YYSTACK_USE_ALLOCA 1

static sval_u yaccResult;
static unsigned int g_out_pos;
static unsigned int g_sourcePos;
static unsigned char g_parse_user;
static sval_u g_dummyVal;

/*
==============
LowerCase
==============
*/
unsigned int LowerCase( unsigned int stringValue )
{
	return SL_ConvertToLowercase(stringValue, g_parse_user, 13);
}

/*
==============
TransferRefToParseUser
==============
*/
void TransferRefToParseUser( unsigned int stringValue )
{
	SL_TransferRefToUser(stringValue, g_parse_user);
}

/* Bison parser tables */

#define YYSTACK_ALLOC __builtin_alloca
#define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#define YYSIZE_T size_t

/* A type that is properly aligned for any stack member. */
union yyalloc
{
	short int yyss;
	YYSTYPE yyvs;
};

/* The size of the maximum gap between one aligned stack and the next. */
#define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large enough to hold all stacks, each with N elements. */
#define YYSTACK_BYTES(N) \
	((N) * (sizeof (short int) + sizeof (YYSTYPE)) + YYSTACK_GAP_MAXIMUM)

#define YYCOPY(To, From, Count) \
	__builtin_memcpy (To, From, (Count) * sizeof (*(From)))

/* Relocate STACK from its old location to the new one. */
#define YYSTACK_RELOCATE(Stack) \
	do \
	{ \
		YYSIZE_T yynewbytes; \
		YYCOPY (&yyptr->Stack, Stack, yysize); \
		Stack = &yyptr->Stack; \
		yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
		yyptr += yynewbytes / sizeof (*yyptr); \
	} \
	while (0)

#define YYFINAL 54
#define YYLAST 1314
#define YYNTOKENS 90
#define YYNNTS 27
#define YYNRULES 131
#define YYNSTATES 255
#define YYUNDEFTOK 2
#define YYMAXUTOK 344

#define YYTRANSLATE(YYX) ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

static const unsigned char yytranslate[] =
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
	   75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
	   85,    86,    87,    88,    89
};

static const unsigned char yyr1[] =
{
	    0,    90,    91,    91,    91,    91,    92,    92,    92,    92,
	   92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
	   92,    92,    92,    92,    92,    92,    92,    93,    93,    94,
	   94,    95,    95,    96,    96,    97,    97,    98,    98,    99,
	   99,   100,   100,   100,   100,   100,   100,   100,   100,   100,
	  100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
	  100,   100,   101,   101,   101,   101,   101,   102,   102,   102,
	  102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
	  102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
	  102,   102,   102,   103,   103,   104,   104,   105,   105,   105,
	  105,   105,   105,   105,   105,   106,   106,   106,   106,   107,
	  107,   108,   108,   108,   109,   109,   109,   110,   110,   111,
	  111,   112,   112,   113,   113,   113,   113,   114,   114,   115,
	  116,   116
};

static const unsigned char yyr2[] =
{
	    0,     2,     3,     2,     2,     2,     1,     3,     3,     3,
	    3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
	    3,     3,     3,     3,     3,     2,     2,     1,     0,     1,
	    1,     3,     1,     3,     2,     1,     5,     1,     2,     4,
	    5,     3,     1,     1,     2,     2,     1,     1,     1,     1,
	    1,     1,     1,     1,     1,     2,     1,     2,     2,     1,
	    1,     1,     3,     4,     1,     2,     3,     3,     2,     1,
	    2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
	    3,     3,     3,     5,     5,     1,     5,     5,     1,     1,
	    1,     4,     4,     1,     1,     0,     1,     2,     3,     5,
	    7,     5,     8,     7,     3,     1,     3,     2,     1,     2,
	    0,     3,     1,     0,     3,     1,     0,     3,     1,     3,
	    1,     3,     1,     7,     5,     1,     1,     2,     0,     2,
	    3,     0
};

static const unsigned char yydefact[] =
{
	    0,   131,     0,     0,   128,    64,    46,    47,   110,   113,
	    0,     0,     0,     0,     0,    42,    43,    69,     0,     0,
	   50,    51,    52,    53,    54,     0,     0,     0,    61,     0,
	   30,    85,     0,    88,    89,    59,    60,    90,     0,     0,
	  110,     0,     3,     0,    35,    56,    37,     0,    48,     6,
	   49,     4,     0,     5,     1,     0,     2,     0,     0,   112,
	   48,     6,    49,     0,     0,    57,    44,    45,    58,    25,
	   26,    68,    70,    29,     0,     0,    38,     0,     0,     0,
	   34,     0,     0,     0,     0,    65,     0,     0,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,     0,     0,     0,   113,     0,     0,    55,     0,
	    0,     0,     0,     0,     0,    71,    72,     0,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,    97,    29,   129,
	    0,     0,   125,   126,   127,   130,    98,   105,     0,     0,
	    0,    94,   108,   109,    41,     0,     0,     0,     0,     0,
	   28,     0,     0,     0,   104,     7,     8,     9,    10,    11,
	   12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
	   22,    23,    24,    33,     0,     0,     0,    62,    66,     0,
	    0,     0,     0,   113,    67,    73,    74,    75,    76,    77,
	   78,    79,    80,    81,    82,   116,     0,     0,   107,   111,
	    0,    31,     0,     0,    27,     0,     0,    91,    92,    39,
	   63,   118,     0,   120,     0,   122,     0,     0,     0,   115,
	    0,     0,   106,    36,    99,   101,    95,   110,    83,     0,
	   84,     0,    86,     0,    87,    40,     0,     0,     0,     0,
	   96,     0,     0,   117,   119,   121,   110,   114,   124,   100,
	    0,   103,     0,   102,   123
};

static const short int yydefgoto[] =
{
	   -1,     3,    59,   205,    43,    44,    45,    46,    47,    60,
	   61,    62,   141,    52,   241,   142,   143,    58,    63,   220,
	  212,   214,   216,   134,    56,    57,     4
};

static const short int yypact[] =
{
	    9,  -105,   690,    13,   -52,    -3,  -105,  -105,  -105,   976,
	   21,   -14,    20,   976,   976,  -105,  -105,   976,   976,    -1,
	 -105,  -105,  -105,  -105,  -105,    17,    30,    35,  -105,    25,
	 -105,  -105,    43,  -105,  -105,  -105,  -105,  -105,    46,    52,
	 -105,    59,   896,   -42,  -105,  -105,  -105,    55,    -8,    27,
	  131,    33,    37,  -105,  -105,     3,     1,    38,   265,   896,
	 -105,   133,  -105,     4,   976,  -105,  -105,  -105,  -105,  -105,
	 -105,   896,   896,    56,    57,   -33,  -105,   976,   976,   605,
	 -105,   976,    75,    78,   350,  -105,   976,   976,   976,   976,
	  976,   976,   976,   976,   976,   976,   976,   976,   976,   976,
	  976,   976,   976,   976,    81,   976,  1043,     8,  -105,    80,
	   82,    84,    85,    94,   976,  -105,  -105,   976,   976,   976,
	  976,   976,   976,   976,   976,   976,   976,  -105,  -105,  -105,
	   95,    96,  -105,  -105,  -105,  -105,  -105,  -105,  1074,    53,
	   27,  -105,  -105,  -105,  -105,   976,  1232,   102,  1150,  1171,
	  976,  1192,   101,   106,  -105,  1268,  1284,   261,   301,   344,
	  383,   383,   205,   205,   205,   205,   421,   421,    29,    29,
	 -105,  -105,  -105,   103,     5,   945,  1251,  -105,  -105,   976,
	  976,   976,   976,   976,   896,   896,   896,   896,   896,   896,
	  896,   896,   896,   896,   896,   110,   112,   104,  -105,   896,
	  128,  -105,   775,   775,   896,   105,   135,  -105,  -105,  -105,
	 -105,   896,     7,   896,    11,   896,    12,  1213,    15,  -105,
	   18,   138,  -105,  -105,   111,  -105,   860,  -105,  -105,   141,
	 -105,   976,  -105,   976,  -105,  -105,   153,   158,   126,   775,
	 -105,   155,   435,  -105,   896,   896,  -105,  -105,  -105,  -105,
	  775,  -105,   520,  -105,  -105
};

static const short int yypgoto[] =
{
	 -105,  -105,    32,  -105,    23,  -105,  -105,   147,   -38,     2,
	   -2,    16,   165,   -55,  -105,     6,    93,   -31,  -104,  -105,
	 -105,  -105,  -105,  -105,  -105,  -105,  -105
};

static const short int yytable[] =
{
	   49,   174,   -93,    73,    48,   130,   -32,   128,    53,    84,
	   74,   113,   177,    54,   144,   209,    55,   228,    50,    66,
	   67,   230,   232,   113,    68,   235,    77,   104,   236,    80,
	  -93,    73,    64,    65,    42,     1,   147,     2,   106,    78,
	  145,   145,    75,   229,    79,    69,    70,   231,   233,    71,
	   72,   145,    81,   178,   237,    82,   140,   101,   102,   103,
	   48,    83,   107,    85,   105,   -32,   -29,   131,    64,    30,
	   19,   -94,    75,    30,    50,   127,   135,   140,   129,   218,
	  152,    48,   140,   153,    75,   173,    48,   132,   133,   179,
	  198,   180,   108,   181,   182,    50,   146,    30,   109,   110,
	   50,   111,   113,   183,   195,   196,   201,   112,    73,   148,
	  149,   207,   -31,   151,   219,   106,   208,   221,   155,   156,
	  157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
	  167,   168,   169,   170,   171,   172,   197,    73,   176,   107,
	  223,   222,   227,   226,   106,   243,   184,    19,   238,   185,
	  186,   187,   188,   189,   190,   191,   192,   193,   194,   113,
	  246,   239,   247,    75,   248,   250,    76,    51,   107,   108,
	  114,   240,   150,     0,    30,     0,    19,   199,     0,     0,
	    0,     0,   204,     0,   115,   116,   117,   118,   119,   120,
	  121,   122,   123,   124,   125,   126,   242,     0,   108,     0,
	  140,   140,     0,    30,    48,    48,     0,   146,   224,   225,
	    0,   211,   213,   215,   217,   252,     0,     0,    50,    50,
	   75,     0,     0,     0,   140,     0,     0,     0,    48,    97,
	   98,    99,   100,   101,   102,   103,     0,   140,     0,     0,
	  140,    48,    50,     0,    48,   249,     0,     0,   140,     0,
	  140,     0,    48,     0,    48,    50,   253,     0,    50,     0,
	    0,     0,     0,   244,     0,   245,    50,     0,    50,     5,
	    6,     7,     8,   136,     9,     0,    10,    89,    90,    91,
	   92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
	  102,   103,    11,     0,     0,    12,     0,     0,    15,    16,
	    0,     0,     0,   137,     0,     0,    17,    18,    19,    20,
	   21,    22,    23,    24,    25,     0,    26,    27,    90,    91,
	   92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
	  102,   103,    28,     0,    29,    30,     0,     0,    31,     0,
	   32,   138,   139,    33,    34,     0,    35,    36,    37,    38,
	   39,    40,     0,    41,     5,     6,     7,     8,     0,     9,
	    0,    10,    91,    92,    93,    94,    95,    96,    97,    98,
	   99,   100,   101,   102,   103,     0,     0,    11,     0,     0,
	   12,     0,     0,    15,    16,     0,     0,     0,   137,     0,
	    0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
	    0,    26,    27,    93,    94,    95,    96,    97,    98,    99,
	  100,   101,   102,   103,     0,     0,     0,    28,     0,    29,
	   30,     0,     0,    31,     0,    32,   138,   139,    33,    34,
	    0,    35,    36,    37,    38,    39,    40,   154,    41,     5,
	    6,     7,     8,   251,     9,     0,    10,    99,   100,   101,
	  102,   103,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,    11,     0,     0,    12,     0,     0,    15,    16,
	    0,     0,     0,   137,     0,     0,    17,    18,    19,    20,
	   21,    22,    23,    24,    25,     0,    26,    27,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,    28,     0,    29,    30,     0,     0,    31,     0,
	   32,   138,   139,    33,    34,     0,    35,    36,    37,    38,
	   39,    40,     0,    41,     5,     6,     7,     8,   254,     9,
	    0,    10,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
	   12,     0,     0,    15,    16,     0,     0,     0,   137,     0,
	    0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
	    0,    26,    27,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,    28,     0,    29,
	   30,     0,     0,    31,     0,    32,   138,   139,    33,    34,
	    0,    35,    36,    37,    38,    39,    40,     0,    41,     5,
	    6,     7,     8,     0,     9,     0,    10,     0,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,    11,     0,     0,    12,     0,     0,    15,    16,
	    0,     0,     0,   137,     0,     0,    17,    18,    19,    20,
	   21,    22,    23,    24,    25,     0,    26,    27,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,    28,     0,    29,    30,     0,     0,    31,     0,
	   32,   138,   139,    33,    34,     0,    35,    36,    37,    38,
	   39,    40,     0,    41,     5,     6,     7,     8,     0,     9,
	    0,    10,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
	   12,    13,    14,    15,    16,     0,     0,     0,     0,     0,
	    0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
	    0,    26,    27,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,    28,     0,    29,
	   30,     0,     0,    31,     0,    32,     0,     0,    33,    34,
	    0,    35,    36,    37,    38,    39,    40,     0,    41,     5,
	    6,     7,     8,     0,     9,     0,    10,     0,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,    11,     0,     0,    12,     0,     0,    15,    16,
	    0,     0,     0,     0,     0,     0,    17,    18,    19,    20,
	   21,    22,    23,    24,    25,     0,    26,    27,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,    28,     0,    29,    30,     0,     0,    31,     0,
	   32,     0,     0,    33,    34,     0,    35,    36,    37,    38,
	   39,    40,     0,    41,     5,     6,     7,     0,     0,     9,
	    0,    10,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
	   12,     0,     0,    15,    16,     0,     0,     0,     0,     0,
	    0,    17,    18,    19,    20,    21,    22,    23,    24,    86,
	   87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
	   97,    98,    99,   100,   101,   102,   103,    28,     0,    29,
	   30,     0,     0,    31,     0,     0,     0,     0,    33,    34,
	    0,    35,    36,    37,    38,    39,     0,     0,    41,     5,
	    6,     7,     0,     0,     9,     0,   175,    65,     0,     0,
	    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,     0,    11,     0,     0,    12,    13,    14,    15,    16,
	    5,     6,     7,     0,     0,     9,     0,    10,    19,    20,
	   21,    22,    23,    24,     0,     0,     0,     0,     0,     0,
	    0,     0,     0,    11,     0,     0,    12,    13,    14,    15,
	   16,     0,    28,     0,    29,    30,     0,     0,     0,    19,
	   20,    21,    22,    23,    24,     0,    35,    36,     0,     0,
	    0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
	    0,     0,     0,    28,     0,    29,    30,     5,     6,     7,
	    0,     0,     9,     0,   175,     0,     0,    35,    36,     0,
	    0,     0,     0,     0,    41,     0,     0,     0,     0,     0,
	   11,     0,     0,    12,    13,    14,    15,    16,     5,     6,
	    7,     0,     0,     9,     0,    10,    19,    20,    21,    22,
	   23,    24,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,    11,     0,     0,    12,     0,     0,    15,    16,     0,
	   28,     0,    29,    30,     0,     0,     0,    19,    20,    21,
	   22,    23,    24,     0,    35,    36,     0,     0,     0,     0,
	    0,    41,     0,     0,     0,     0,     0,     0,     0,     0,
	    0,    28,     0,    29,    30,     0,     0,     0,     0,     0,
	    0,     0,     0,     0,     0,    35,    36,     0,     0,     0,
	  202,     0,    41,    86,    87,    88,    89,    90,    91,    92,
	   93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
	  103,   203,     0,     0,    86,    87,    88,    89,    90,    91,
	   92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
	  102,   103,   206,     0,     0,    86,    87,    88,    89,    90,
	   91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
	  101,   102,   103,   234,     0,     0,    86,    87,    88,    89,
	   90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
	  100,   101,   102,   103,   200,    86,    87,    88,    89,    90,
	   91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
	  101,   102,   103,   210,    86,    87,    88,    89,    90,    91,
	   92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
	  102,   103,    87,    88,    89,    90,    91,    92,    93,    94,
	   95,    96,    97,    98,    99,   100,   101,   102,   103,    88,
	   89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
	   99,   100,   101,   102,   103
};

static const short int yycheck[] =
{
	    2,   105,    10,     4,     2,     4,     9,     4,     2,    40,
	   11,    49,     4,     0,    10,    10,    68,    10,     2,    33,
	   34,    10,    10,    61,     4,    10,     9,    69,    10,     4,
	   38,     4,    11,    12,     2,    26,    69,    28,    11,     9,
	   36,    36,    19,    36,     9,    13,    14,    36,    36,    17,
	   18,    36,     9,    45,    36,     9,    58,    28,    29,    30,
	   58,     9,    35,     4,     9,     9,    69,    66,    11,    70,
	   43,    38,    49,    70,    58,    38,    38,    79,    55,   183,
	    5,    79,    84,     5,    61,     4,    84,    86,    87,     9,
	   37,     9,    65,     9,     9,    79,    64,    70,    71,    72,
	   84,    74,   140,     9,     9,     9,     4,    80,     4,    77,
	   78,    10,     9,    81,     4,    11,    10,     5,    86,    87,
	   88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
	   98,    99,   100,   101,   102,   103,   138,     4,   106,    35,
	   12,    37,     7,    38,    11,     4,   114,    43,    10,   117,
	  118,   119,   120,   121,   122,   123,   124,   125,   126,   197,
	    7,    50,     4,   140,    38,    10,    19,     2,    35,    65,
	   39,   226,    79,    -1,    70,    -1,    43,   145,    -1,    -1,
	   -1,    -1,   150,    -1,    53,    54,    55,    56,    57,    58,
	   59,    60,    61,    62,    63,    64,   227,    -1,    65,    -1,
	  202,   203,    -1,    70,   202,   203,    -1,   175,   202,   203,
	   -1,   179,   180,   181,   182,   246,    -1,    -1,   202,   203,
	  197,    -1,    -1,    -1,   226,    -1,    -1,    -1,   226,    24,
	   25,    26,    27,    28,    29,    30,    -1,   239,    -1,    -1,
	  242,   239,   226,    -1,   242,   239,    -1,    -1,   250,    -1,
	  252,    -1,   250,    -1,   252,   239,   250,    -1,   242,    -1,
	   -1,    -1,    -1,   231,    -1,   233,   250,    -1,   252,     4,
	    5,     6,     7,     8,     9,    -1,    11,    16,    17,    18,
	   19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
	   29,    30,    27,    -1,    -1,    30,    -1,    -1,    33,    34,
	   -1,    -1,    -1,    38,    -1,    -1,    41,    42,    43,    44,
	   45,    46,    47,    48,    49,    -1,    51,    52,    17,    18,
	   19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
	   29,    30,    67,    -1,    69,    70,    -1,    -1,    73,    -1,
	   75,    76,    77,    78,    79,    -1,    81,    82,    83,    84,
	   85,    86,    -1,    88,     4,     5,     6,     7,    -1,     9,
	   -1,    11,    18,    19,    20,    21,    22,    23,    24,    25,
	   26,    27,    28,    29,    30,    -1,    -1,    27,    -1,    -1,
	   30,    -1,    -1,    33,    34,    -1,    -1,    -1,    38,    -1,
	   -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
	   -1,    51,    52,    20,    21,    22,    23,    24,    25,    26,
	   27,    28,    29,    30,    -1,    -1,    -1,    67,    -1,    69,
	   70,    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,
	   -1,    81,    82,    83,    84,    85,    86,    87,    88,     4,
	    5,     6,     7,     8,     9,    -1,    11,    26,    27,    28,
	   29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    27,    -1,    -1,    30,    -1,    -1,    33,    34,
	   -1,    -1,    -1,    38,    -1,    -1,    41,    42,    43,    44,
	   45,    46,    47,    48,    49,    -1,    51,    52,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    67,    -1,    69,    70,    -1,    -1,    73,    -1,
	   75,    76,    77,    78,    79,    -1,    81,    82,    83,    84,
	   85,    86,    -1,    88,     4,     5,     6,     7,     8,     9,
	   -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
	   30,    -1,    -1,    33,    34,    -1,    -1,    -1,    38,    -1,
	   -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
	   -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
	   70,    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,
	   -1,    81,    82,    83,    84,    85,    86,    -1,    88,     4,
	    5,     6,     7,    -1,     9,    -1,    11,    -1,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    27,    -1,    -1,    30,    -1,    -1,    33,    34,
	   -1,    -1,    -1,    38,    -1,    -1,    41,    42,    43,    44,
	   45,    46,    47,    48,    49,    -1,    51,    52,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    67,    -1,    69,    70,    -1,    -1,    73,    -1,
	   75,    76,    77,    78,    79,    -1,    81,    82,    83,    84,
	   85,    86,    -1,    88,     4,     5,     6,     7,    -1,     9,
	   -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
	   30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
	   -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
	   -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
	   70,    -1,    -1,    73,    -1,    75,    -1,    -1,    78,    79,
	   -1,    81,    82,    83,    84,    85,    86,    -1,    88,     4,
	    5,     6,     7,    -1,     9,    -1,    11,    -1,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    27,    -1,    -1,    30,    -1,    -1,    33,    34,
	   -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
	   45,    46,    47,    48,    49,    -1,    51,    52,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    67,    -1,    69,    70,    -1,    -1,    73,    -1,
	   75,    -1,    -1,    78,    79,    -1,    81,    82,    83,    84,
	   85,    86,    -1,    88,     4,     5,     6,    -1,    -1,     9,
	   -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
	   30,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
	   -1,    41,    42,    43,    44,    45,    46,    47,    48,    13,
	   14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
	   24,    25,    26,    27,    28,    29,    30,    67,    -1,    69,
	   70,    -1,    -1,    73,    -1,    -1,    -1,    -1,    78,    79,
	   -1,    81,    82,    83,    84,    85,    -1,    -1,    88,     4,
	    5,     6,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    27,    -1,    -1,    30,    31,    32,    33,    34,
	    4,     5,     6,    -1,    -1,     9,    -1,    11,    43,    44,
	   45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    -1,    27,    -1,    -1,    30,    31,    32,    33,
	   34,    -1,    67,    -1,    69,    70,    -1,    -1,    -1,    43,
	   44,    45,    46,    47,    48,    -1,    81,    82,    -1,    -1,
	   -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    -1,    67,    -1,    69,    70,     4,     5,     6,
	   -1,    -1,     9,    -1,    11,    -1,    -1,    81,    82,    -1,
	   -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,
	   27,    -1,    -1,    30,    31,    32,    33,    34,     4,     5,
	    6,    -1,    -1,     9,    -1,    11,    43,    44,    45,    46,
	   47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    27,    -1,    -1,    30,    -1,    -1,    33,    34,    -1,
	   67,    -1,    69,    70,    -1,    -1,    -1,    43,    44,    45,
	   46,    47,    48,    -1,    81,    82,    -1,    -1,    -1,    -1,
	   -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
	   -1,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,
	   -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
	   10,    -1,    88,    13,    14,    15,    16,    17,    18,    19,
	   20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
	   30,    10,    -1,    -1,    13,    14,    15,    16,    17,    18,
	   19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
	   29,    30,    10,    -1,    -1,    13,    14,    15,    16,    17,
	   18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
	   28,    29,    30,    10,    -1,    -1,    13,    14,    15,    16,
	   17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
	   27,    28,    29,    30,    12,    13,    14,    15,    16,    17,
	   18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
	   28,    29,    30,    12,    13,    14,    15,    16,    17,    18,
	   19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
	   29,    30,    14,    15,    16,    17,    18,    19,    20,    21,
	   22,    23,    24,    25,    26,    27,    28,    29,    30,    15,
	   16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
	   26,    27,    28,    29,    30
};

static const unsigned char yystos[] =
{
	    0,    26,    28,    91,   116,     4,     5,     6,     7,     9,
	   11,    27,    30,    31,    32,    33,    34,    41,    42,    43,
	   44,    45,    46,    47,    48,    49,    51,    52,    67,    69,
	   70,    73,    75,    78,    79,    81,    82,    83,    84,    85,
	   86,    88,    92,    94,    95,    96,    97,    98,    99,   100,
	  101,   102,   103,   105,     0,    68,   114,   115,   107,    92,
	   99,   100,   101,   108,    11,    12,    33,    34,     4,    92,
	   92,    92,    92,     4,    11,    94,    97,     9,     9,     9,
	    4,     9,     9,     9,   107,     4,    13,    14,    15,    16,
	   17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
	   27,    28,    29,    30,    69,     9,    11,    35,    65,    71,
	   72,    74,    80,    98,    39,    53,    54,    55,    56,    57,
	   58,    59,    60,    61,    62,    63,    64,    38,     4,    94,
	    4,    66,    86,    87,   113,    38,     8,    38,    76,    77,
	  100,   102,   105,   106,    10,    36,    92,    69,    92,    92,
	  106,    92,     5,     5,    87,    92,    92,    92,    92,    92,
	   92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
	   92,    92,    92,     4,   108,    11,    92,     4,    45,     9,
	    9,     9,     9,     9,    92,    92,    92,    92,    92,    92,
	   92,    92,    92,    92,    92,     9,     9,   100,    37,    92,
	   12,     4,    10,    10,    92,    93,    10,    10,    10,    10,
	   12,    92,   110,    92,   111,    92,   112,    92,   108,     4,
	  109,     5,    37,    12,   105,   105,    38,     7,    10,    36,
	   10,    36,    10,    36,    10,    10,    10,    36,    10,    50,
	  103,   104,   107,     4,    92,    92,     7,     4,    38,   105,
	   10,     8,   107,   105,     8
};

#define YYPACT_NINF -105
#define YYTABLE_NINF -95

#define YYEMPTY (-2)
#define YYEOF 0

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab

#define YYTERROR 1
#define YYERRCODE 256

#define YYINITDEPTH 200
#define YYMAXDEPTH 10000

/*
==============
yydestruct
==============
*/
static void yydestruct( const char *yymsg, int yytype, YYSTYPE *yyvaluep )
{
	/* Pacify ``unused variable'' warnings. */
	(void) yyvaluep;

	if (!yymsg)
		yymsg = "Deleting";

	switch (yytype)
	{
	default:
		break;
	}
}

/* The look-ahead symbol. */
int yychar;

/* The semantic value of the look-ahead symbol. */
YYSTYPE yylval;

/* Number of syntax errors so far. */
int yynerrs;

/*
==============
yyparse
==============
*/
int yyparse()
{
	register int yystate;
	register int yyn;
	int yyresult;
	/* Number of tokens to shift before error messages enabled. */
	int yyerrstatus;
	/* Look-ahead token as an internal (translated) token number. */
	int yytoken = 0;

	/* The state stack. */
	short int yyssa[YYINITDEPTH];
	short int *yyss = yyssa;
	register short int *yyssp;

	/* The semantic value stack. */
	YYSTYPE yyvsa[YYINITDEPTH];
	YYSTYPE *yyvs = yyvsa;
	register YYSTYPE *yyvsp;

#define YYPOPSTACK (yyvsp--, yyssp--)

	YYSIZE_T yystacksize = YYINITDEPTH;

	/* The variables used to return semantic value and location from the action routines. */
	YYSTYPE yyval;

	/* When reducing, the number of symbols on the RHS of the reduced rule. */
	int yylen;

	yystate = 0;
	yyerrstatus = 0;
	yynerrs = 0;
	yychar = YYEMPTY; /* Cause a token to be read. */

	/* Initialize stack pointers.
	   Waste one element of value and location stack
	   so that they stay on the same level as the state stack.
	   The wasted elements are never initialized. */
	yyssp = yyss;
	yyvsp = yyvs;

	yyvsp[0] = yylval;

	goto yysetstate;

/* yynewstate -- Push a new state, which is found in yystate. */
yynewstate:
	/* In all cases, when you get here, the value and location stacks
	   have just been pushed. so pushing a state here evens the stacks. */
	yyssp++;

yysetstate:
	*yyssp = yystate;

	if (yyss + yystacksize - 1 <= yyssp)
	{
		/* Get the current used size of the three stacks, in elements. */
		YYSIZE_T yysize = yyssp - yyss + 1;

		/* Extend the stack our own way. */
		if (YYMAXDEPTH <= yystacksize)
			goto yyoverflowlab;
		yystacksize *= 2;
		if (YYMAXDEPTH < yystacksize)
			yystacksize = YYMAXDEPTH;

		{
			short int *yyss1 = yyss;
			union yyalloc *yyptr =
				(union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
			if (! yyptr)
				goto yyoverflowlab;
			YYSTACK_RELOCATE (yyss);
			YYSTACK_RELOCATE (yyvs);
#undef YYSTACK_RELOCATE
			if (yyss1 != yyssa)
				YYSTACK_FREE (yyss1);
		}

		yyssp = yyss + yysize - 1;
		yyvsp = yyvs + yysize - 1;

		if (yyss + yystacksize - 1 <= yyssp)
			YYABORT;
	}

	goto yybackup;

/* yybackup. */
yybackup:
	/* Do appropriate processing given the current state. */
	/* Read a look-ahead token if we need one and don't already have one. */

	/* First try to decide what to do without reference to look-ahead token. */
	yyn = yypact[yystate];
	if (yyn == YYPACT_NINF)
		goto yydefault;

	/* Not known => get a look-ahead token if don't already have one. */

	/* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol. */
	if (yychar == YYEMPTY)
	{
		yychar = yylex();
	}

	if (yychar <= YYEOF)
	{
		yychar = yytoken = YYEOF;
	}
	else
	{
		yytoken = YYTRANSLATE (yychar);
	}

	/* If the proper action on seeing token YYTOKEN is to reduce or to
	   detect an error, take that action. */
	yyn += yytoken;
	if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
		goto yydefault;
	yyn = yytable[yyn];
	if (yyn <= 0)
	{
		if (yyn == 0 || yyn == YYTABLE_NINF)
			goto yyerrlab;
		yyn = -yyn;
		goto yyreduce;
	}

	if (yyn == YYFINAL)
		YYACCEPT;

	/* Shift the look-ahead token. */

	/* Discard the token being shifted unless it is eof. */
	if (yychar != YYEOF)
		yychar = YYEMPTY;

	*++yyvsp = yylval;

	/* Count tokens shifted since error; after three, turn off error status. */
	if (yyerrstatus)
		yyerrstatus--;

	yystate = yyn;
	goto yynewstate;

/* yydefault -- do the default action for the current state. */
yydefault:
	yyn = yydefact[yystate];
	if (yyn == 0)
		goto yyerrlab;
	goto yyreduce;

/* yyreduce -- Do a reduction. */
yyreduce:
	/* yyn is the number of a rule to reduce with. */
	yylen = yyr2[yyn];

	/* If YYLEN is nonzero, implement the default value of the action: `$$ = $1'. */
	yyval = yyvsp[1-yylen];

	switch (yyn)
	{
	case 2:
		yaccResult = node2_(yyvsp[-1].val, yyvsp[0].val);
		break;
	case 3:
		yaccResult = node1(0x41, yyvsp[0].val);
		break;
	case 4:
		yaccResult = node1(0x52, yyvsp[0].val);
		break;
	case 5:
		yaccResult = node1(0x52, yyvsp[0].val);
		break;
	case 6:
		yyval.val = node2(6, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 7:
		yyval.val = node5(0x2f, yyvsp[-2].val, yyvsp[0].val, (node_pos(yyvsp[-2].pos)), (node_pos(yyvsp[0].pos)), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 8:
		yyval.val = node5(0x30, yyvsp[-2].val, yyvsp[0].val, (node_pos(yyvsp[-2].pos)), (node_pos(yyvsp[0].pos)), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 9:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x66), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 10:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x67), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 11:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x68), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 12:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x69), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 13:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x6a), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 14:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x6b), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 15:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x6c), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 16:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x6d), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 17:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x6e), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 18:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x6f), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 19:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x70), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 20:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x71), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 21:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x72), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 22:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x73), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 23:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x74), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 24:
		yyval.val = node4(0x31, yyvsp[-2].val, yyvsp[0].val, node1_(0x75), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-1].pos;
		break;
	case 25:
		yyval.val = node2(0x32, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 26:
		yyval.val = node2(0x33, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 27:
		yyval.val = node1(0x41, yyvsp[0].val);
		break;
	case 28:
		yyval.val = node0(0);
		break;
	case 29:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = yyvsp[0].val;
		break;
	case 30:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = yyvsp[0].val;
		break;
	case 31:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = node3(0x15, yyvsp[-2].val, yyvsp[0].val, node_pos(yyvsp[-2].pos));
		++scrCompilePub.far_function_count;
		break;
	case 32:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = node2(0x14, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 33:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = node3(0x15, yyvsp[-2].val, yyvsp[0].val, node_pos(yyvsp[-2].pos));
		yyval.pos = yyvsp[-1].pos;
		++scrCompilePub.far_function_count;
		break;
	case 34:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = node2(0x14, yyvsp[0].val, node_pos(yyvsp[-1].pos));
		break;
	case 35:
		yyval.val = node2(0x12, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 36:
		yyval.val = node2(0x16, yyvsp[-2].val, node_pos(yyvsp[-2].pos));
		break;
	case 37:
		yyval.val = node2(0x1a, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 38:
		yyval.val = node3(0x1e, yyvsp[0].val, node_pos(yyvsp[-1].pos), node_pos(yyvsp[0].pos));
		yyval.pos = yyvsp[0].pos;
		break;
	case 39:
		yyval.val = node3(0x17, yyvsp[-3].val, yyvsp[-1].val, node_pos(yyvsp[-2].pos));
		yyval.pos = yyvsp[-2].pos;
		break;
	case 40:
		yyval.val = node5(0x18, yyvsp[-4].val, yyvsp[-3].val, yyvsp[-1].val, (node_pos(yyvsp[-4].pos)), (node_pos(yyvsp[-2].pos)));
		yyval.pos = yyvsp[-2].pos;
		break;
	case 41:
		yyval.val = node2(0x2e, yyvsp[-1].val, node_pos(yyvsp[-2].pos));
		break;
	case 42:
		yyval.val = node2(7, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 43:
		yyval.val = node2(8, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 44:
		yyval.val = node2(9, yyvsp[0].val, node_pos(yyvsp[-1].pos));
		break;
	case 45:
		yyval.val = node2(0xa, yyvsp[0].val, node_pos(yyvsp[-1].pos));
		break;
	case 46:
		yyval.val = node2(0xb, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 47:
		yyval.val = node2(0xc, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 48:
		yyval.val = node1(0x13, yyvsp[0].val);
		break;
	case 49:
		yyval.val = node2(0x11, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 50:
		yyval.val = node1(0x1f, node_pos(yyvsp[0].pos));
		break;
	case 51:
		yyval.val = node1(0x20, node_pos(yyvsp[0].pos));
		break;
	case 52:
		yyval.val = node1(0x22, node_pos(yyvsp[0].pos));
		break;
	case 53:
		yyval.val = node1(0x23, node_pos(yyvsp[0].pos));
		break;
	case 54:
		yyval.val = node1(0x24, node_pos(yyvsp[0].pos));
		break;
	case 55:
		yyval.val = node2(0x34, yyvsp[-1].val, node_pos(yyvsp[-1].pos));
		yyval.pos = yyvsp[0].pos;
		break;
	case 56:
		yyval.val = node2(0x12, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 57:
		yyval.val = node1(0x42, node_pos(yyvsp[-1].pos));
		break;
	case 58:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = node2(0x43, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 59:
		yyval.val = node1(0x48, node_pos(yyvsp[0].pos));
		break;
	case 60:
		yyval.val = node1(0x49, node_pos(yyvsp[0].pos));
		break;
	case 61:
		yyval.val = node1(0x4a, node_pos(yyvsp[0].pos));
		break;
	case 62:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = node3(0xf, yyvsp[-2].val, yyvsp[0].val, node_pos(yyvsp[-2].pos));
		yyval.pos = yyvsp[0].pos;
		break;
	case 63:
		yyval.val = node4(0xd, yyvsp[-3].val, yyvsp[-1].val, (node_pos(yyvsp[-3].pos)), (node_pos(yyvsp[-1].pos)));
		yyval.pos = yyvsp[-2].pos;
		break;
	case 64:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = node2(4, yyvsp[0].val, node_pos(yyvsp[0].pos));
		break;
	case 65:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = node2(0x4f, yyvsp[0].val, node_pos(yyvsp[-1].pos));
		break;
	case 66:
		yyval.val = node2(0x35, yyvsp[-2].val, node_pos(yyvsp[-2].pos));
		yyval.pos = yyvsp[0].pos;
		break;
	case 67:
		yyval.val = node4(2, yyvsp[-2].val, yyvsp[0].val, (node_pos(yyvsp[-1].pos)), (node_pos(yyvsp[0].pos)));
		break;
	case 68:
		yyval.val = node2(0x1b, yyvsp[0].val, node_pos(yyvsp[-1].pos));
		break;
	case 69:
		yyval.val = node1(0x1c, node_pos(yyvsp[0].pos));
		break;
	case 70:
		yyval.val = node3(0x1d, yyvsp[0].val, (node_pos(yyvsp[0].pos)), (node_pos(yyvsp[-1].pos)));
		break;
	case 71:
		yyval.val = node2(0x29, yyvsp[-1].val, node_pos(yyvsp[-1].pos));
		break;
	case 72:
		yyval.val = node2(0x2a, yyvsp[-1].val, node_pos(yyvsp[-1].pos));
		break;
	case 73:
		yyval.val = node4(0x2b, yyvsp[-2].val, yyvsp[0].val, node1_(0x66), (node_pos(yyvsp[-1].pos)));
		break;
	case 74:
		yyval.val = node4(0x2b, yyvsp[-2].val, yyvsp[0].val, node1_(0x67), (node_pos(yyvsp[-1].pos)));
		break;
	case 75:
		yyval.val = node4(0x2b, yyvsp[-2].val, yyvsp[0].val, node1_(0x68), (node_pos(yyvsp[-1].pos)));
		break;
	case 76:
		yyval.val = node4(0x2b, yyvsp[-2].val, yyvsp[0].val, node1_(0x6f), (node_pos(yyvsp[-1].pos)));
		break;
	case 77:
		yyval.val = node4(0x2b, yyvsp[-2].val, yyvsp[0].val, node1_(0x70), (node_pos(yyvsp[-1].pos)));
		break;
	case 78:
		yyval.val = node4(0x2b, yyvsp[-2].val, yyvsp[0].val, node1_(0x71), (node_pos(yyvsp[-1].pos)));
		break;
	case 79:
		yyval.val = node4(0x2b, yyvsp[-2].val, yyvsp[0].val, node1_(0x72), (node_pos(yyvsp[-1].pos)));
		break;
	case 80:
		yyval.val = node4(0x2b, yyvsp[-2].val, yyvsp[0].val, node1_(0x73), (node_pos(yyvsp[-1].pos)));
		break;
	case 81:
		yyval.val = node4(0x2b, yyvsp[-2].val, yyvsp[0].val, node1_(0x74), (node_pos(yyvsp[-1].pos)));
		break;
	case 82:
		yyval.val = node4(0x2b, yyvsp[-2].val, yyvsp[0].val, node1_(0x75), (node_pos(yyvsp[-1].pos)));
		break;
	case 83:
		yyval.val = node4(0x37, yyvsp[-4].val, yyvsp[-1].val, (node_pos(yyvsp[-4].pos)), (node_pos(yyvsp[-3].pos)));
		break;
	case 84:
		yyval.val = node4(0x38, yyvsp[-4].val, yyvsp[-1].val, (node_pos(yyvsp[-4].pos)), (node_pos(yyvsp[-3].pos)));
		break;
	case 85:
		yyval.val = node1(0x39, node_pos(yyvsp[0].pos));
		break;
	case 86:
		yyval.val = node4(0x3a, yyvsp[-4].val, yyvsp[-1].val, (node_pos(yyvsp[-4].pos)), (node_pos(yyvsp[-3].pos)));
		break;
	case 87:
		yyval.val = node4(0x3b, yyvsp[-4].val, yyvsp[-1].val, (node_pos(yyvsp[-4].pos)), (node_pos(yyvsp[-1].pos)));
		break;
	case 88:
		yyval.val = node1(0x3f, node_pos(yyvsp[0].pos));
		break;
	case 89:
		yyval.val = node1(0x40, node_pos(yyvsp[0].pos));
		break;
	case 90:
		yyval.val = node1(0x4b, node_pos(yyvsp[0].pos));
		break;
	case 91:
		yyval.val = node2(0x4c, yyvsp[-1].val, node_pos(yyvsp[-3].pos));
		break;
	case 92:
		yyval.val = node2(0x4d, yyvsp[-1].val, node_pos(yyvsp[-3].pos));
		break;
	case 93:
		yyval.val = node1(0x19, yyvsp[0].val);
		break;
	case 95:
		yyval.val = node0(0);
		break;
	case 98:
		yyval.val = node3(0x2c, yyvsp[-1].val, (node_pos(yyvsp[-2].pos)), (node_pos(yyvsp[0].pos)));
		break;
	case 99:
		yyval.val = node4(0x25, yyvsp[-2].val, yyvsp[0].val, node_pos(yyvsp[-2].pos), g_dummyVal);
		break;
	case 100:
		yyval.val = node7(0x26, yyvsp[-4].val, yyvsp[-2].val, yyvsp[0].val, (node_pos(yyvsp[-4].pos)), (node_pos(yyvsp[-1].pos)), g_dummyVal, g_dummyVal);
		break;
	case 101:
		yyval.val = node5(0x27, yyvsp[-2].val, yyvsp[0].val, (node_pos(yyvsp[-2].pos)), (node_pos(yyvsp[-4].pos)), g_dummyVal);
		break;
	case 102:
		yyval.val = node8(0x28, yyvsp[-5].val, yyvsp[-4].val, yyvsp[-2].val, yyvsp[0].val, (node_pos(yyvsp[-4].pos)), (node_pos(yyvsp[-7].pos)), g_dummyVal, g_dummyVal);
		break;
	case 103:
		yyval.val = node3(0x3c, yyvsp[-4].val, yyvsp[-1].val, node_pos(yyvsp[-4].pos));
		break;
	case 104:
		yyval.val = node3(0x2d, yyvsp[-1].val, node_pos(yyvsp[-2].pos), g_dummyVal);
		break;
	case 105:
		yyval.val = node0(0);
		break;
	case 106:
		yyval.val = node3(0x3d, yyvsp[-1].val, node_pos(yyvsp[-2].pos), g_dummyVal);
		break;
	case 107:
		yyval.val = node2(0x3e, node_pos(yyvsp[-1].pos), g_dummyVal);
		break;
	case 109:
		yyval.val = append_node(yyvsp[-1].val, yyvsp[0].val);
		break;
	case 110:
		yyval.val = linked_list_end(node0(0));
		break;
	case 111:
		yyval.val = prepend_node((node2_(yyvsp[0].val, node_pos(yyvsp[0].pos))), yyvsp[-2].val);
		break;
	case 112:
		yyval.val = prepend_node((node2_(yyvsp[0].val, node_pos(yyvsp[0].pos))), node0(0));
		break;
	case 113:
		yyval.val = node0(0);
		break;
	case 114:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = append_node(yyvsp[-2].val, node2_(yyvsp[0].val, node_pos(yyvsp[0].pos)));
		break;
	case 115:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = append_node(linked_list_end(node0(0)), node2_(yyvsp[0].val, node_pos(yyvsp[0].pos)));
		break;
	case 116:
		yyval.val = linked_list_end(node0(0));
		break;
	case 117:
		yyvsp[0].val.intValue = LowerCase(yyvsp[0].val.intValue);
		yyval.val = append_node(yyvsp[-2].val, node2_(yyvsp[0].val, node_pos(yyvsp[0].pos)));
		break;
	case 118:
		yyval.val = append_node(linked_list_end(node0(0)), (node2_(yyvsp[0].val, node_pos(yyvsp[0].pos))));
		break;
	case 119:
		yyval.val = append_node(yyvsp[-2].val, (node2_(yyvsp[0].val, node_pos(yyvsp[0].pos))));
		break;
	case 120:
		yyval.val = append_node(linked_list_end(node0(0)), (node2_(yyvsp[0].val, node_pos(yyvsp[0].pos))));
		break;
	case 121:
		yyval.val = prepend_node((node2_(yyvsp[0].val, node_pos(yyvsp[0].pos))), yyvsp[-2].val);
		break;
	case 122:
		yyval.val = prepend_node((node2_(yyvsp[0].val, node_pos(yyvsp[0].pos))), node0(0));
		break;
	case 123:
		yyvsp[-6].val.intValue = LowerCase(yyvsp[-6].val.intValue);
		yyval.val = node6(0x44, yyvsp[-6].val, yyvsp[-4].val, yyvsp[-1].val, (node_pos(yyvsp[-6].pos)), (node_pos(yyvsp[0].pos)), g_dummyVal);
		break;
	case 124:
		yyval.val = node3(0x47, yyvsp[-2].val, (node_pos(yyvsp[-4].pos)), (node_pos(yyvsp[-2].pos)));
		break;
	case 125:
		yyval.val = node1(0x45, node_pos(yyvsp[0].pos));
		break;
	case 126:
		yyval.val = node1(0x46, node_pos(yyvsp[0].pos));
		break;
	case 127:
		yyval.val = append_node(yyvsp[-1].val, yyvsp[0].val);
		break;
	case 128:
		yyval.val = linked_list_end(node0(0));
		break;
	case 129:
		yyval.val = node2(0x55, yyvsp[0].val, node_pos(yyvsp[-1].pos));
		++scrCompilePub.far_function_count;
		break;
	case 130:
		yyval.val = append_node(yyvsp[-2].val, yyvsp[-1].val);
		break;
	case 131:
		yyval.val = linked_list_end(node0(0));
		break;
	}

	yyvsp -= yylen;
	yyssp -= yylen;

	*++yyvsp = yyval;

	/* Now `shift' the result of the reduction.  Determine what state
	   that goes to, based on the state we popped back to and the rule
	   number reduced by. */
	yyn = yyr1[yyn];

	yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
	if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
		yystate = yytable[yystate];
	else
		yystate = yydefgoto[yyn - YYNTOKENS];

	goto yynewstate;

/* yyerrlab -- here on detecting error */
yyerrlab:
	/* If not already recovering from an error, report this error. */
	if (!yyerrstatus)
	{
		++yynerrs;
		yyerror ("syntax error");
	}

	if (yyerrstatus == 3)
	{
		/* If just tried and failed to reuse look-ahead token after an
		   error, discard it. */
		if (yychar <= YYEOF)
		{
			/* If at end of input, pop the error token,
			   then the rest of the stack, then return failure. */
			if (yychar == YYEOF)
				for (;;)
				{
					YYPOPSTACK;
					if (yyssp == yyss)
						YYABORT;
					yydestruct ("Error: popping", yystos[*yyssp], yyvsp);
				}
		}
		else
		{
			yydestruct ("Error: discarding", yytoken, &yylval);
			yychar = YYEMPTY;
		}
	}

	/* Else will try to reuse look-ahead token after shifting the error token. */
	goto yyerrlab1;

/* yyerrorlab -- error raised explicitly by YYERROR. */
yyerrorlab:
	/* Pacify GCC when the user code never invokes YYERROR and the label
	   yyerrorlab therefore never appears in user code. */
	if (0)
		goto yyerrorlab;

	yyvsp -= yylen;
	yyssp -= yylen;
	yystate = *yyssp;
	goto yyerrlab1;

/* yyerrlab1 -- common code for both syntax error and YYERROR. */
yyerrlab1:
	yyerrstatus = 3; /* Each real token shifted decrements this. */

	for (;;)
	{
		yyn = yypact[yystate];
		if (yyn != YYPACT_NINF)
		{
			yyn += YYTERROR;
			if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
			{
				yyn = yytable[yyn];
				if (0 < yyn)
					break;
			}
		}

		/* Pop the current state because it cannot handle the error token. */
		if (yyssp == yyss)
			YYABORT;

		yydestruct ("Error: popping", yystos[yystate], yyvsp);
		YYPOPSTACK;
		yystate = *yyssp;
	}

	if (yyn == YYFINAL)
		YYACCEPT;

	*++yyvsp = yylval;

	yystate = yyn;
	goto yynewstate;

/* yyacceptlab -- YYACCEPT comes here. */
yyacceptlab:
	yyresult = 0;
	goto yyreturn;

/* yyabortlab -- YYABORT comes here. */
yyabortlab:
	yydestruct ("Error: discarding lookahead", yytoken, &yylval);
	yychar = YYEMPTY;
	yyresult = 1;
	goto yyreturn;

/* yyoverflowlab -- parser overflow comes here. */
yyoverflowlab:
	yyerror ("parser stack overflow");
	yyresult = 2;
	/* Fall through. */

yyreturn:
	if (yyss != yyssa)
		YYSTACK_FREE (yyss);

	return yyresult;
}

/* flex 2.5.31 scanner */

#define YY_INT_ALIGNED short int

#define FLEX_SCANNER
#define YY_FLEX_MAJOR_VERSION 2
#define YY_FLEX_MINOR_VERSION 5
#define YY_FLEX_SUBMINOR_VERSION 31

typedef unsigned char YY_CHAR;
typedef int yy_state_type;
typedef size_t yy_size_t;

/* Promotes a possibly negative, possibly signed char to an unsigned
 * integer for use as an array index.  If the signed char is negative,
 * we want to instead treat it as an 8-bit unsigned char, hence the
 * double cast.
 */
#define YY_SC_TO_UI(c) ((unsigned int) (unsigned char) c)

#define YY_BUF_SIZE 16384
#define YY_READ_BUF_SIZE 8192
#define YY_END_OF_BUFFER_CHAR 0
#define YY_MORE_ADJ 0

#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE 1
#define EOB_ACT_LAST_MATCH 2

#define YY_FATAL_ERROR(msg) yy_fatal_error( msg )

typedef struct yy_buffer_state *YY_BUFFER_STATE;

struct yy_buffer_state
{
	FILE *yy_input_file;

	char *yy_ch_buf; /* input buffer */
	char *yy_buf_pos; /* current position in input buffer */

	/* Size of input buffer in bytes, not including room for EOB characters. */
	yy_size_t yy_buf_size;

	/* Number of characters read into yy_ch_buf, not including EOB characters. */
	int yy_n_chars;

	/* Whether we "own" the buffer - i.e., we know we created it,
	 * and can realloc() it to grow it, and should free() it to
	 * delete it.
	 */
	int yy_is_our_buffer;

	/* Whether this is an "interactive" input source; if so, and
	 * if we're using stdio for input, then we want to use getc()
	 * instead of fread(), to make sure we stop fetching input after
	 * each newline.
	 */
	int yy_is_interactive;

	/* Whether we're considered to be at the beginning of a line.
	 * If so, '^' rules will be active on the next match, otherwise
	 * not.
	 */
	int yy_at_bol;

	int yy_bs_lineno; /**< The line count. */
	int yy_bs_column; /**< The column count. */

	/* Whether to try to fill the input buffer when we reach the end of it. */
	int yy_fill_buffer;

	int yy_buffer_status;

#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
#define YY_BUFFER_EOF_PENDING 2
};

/* Stack of input buffers. */
static size_t yy_buffer_stack_top = 0; /**< index of top of stack. */
static size_t yy_buffer_stack_max = 0; /**< capacity of stack. */
static YY_BUFFER_STATE *yy_buffer_stack = 0; /**< Stack as an array. */

/* Returns the top of the stack, or NULL. */
#define YY_CURRENT_BUFFER ( (yy_buffer_stack) \
                          ? (yy_buffer_stack)[(yy_buffer_stack_top)] \
                          : NULL)

/* Same as previous macro, but useful when we know that the buffer stack is not
 * NULL or when we need an lvalue. For internal use only.
 */
#define YY_CURRENT_BUFFER_LVALUE (yy_buffer_stack)[(yy_buffer_stack_top)]

/* yy_hold_char holds the character lost when yytext is formed. */
static char yy_hold_char;
static int yy_n_chars; /* number of characters read into yy_ch_buf */
int yyleng;

/* Points to current character in buffer. */
static char *yy_c_buf_p = (char *) 0;
static int yy_init = 1; /* whether we need to initialize */
static int yy_start = 0; /* start state number */

/* Flag which is used to allow yywrap()'s to do buffer switches
 * instead of setting up a fresh yyin.  A bit of a hack ...
 */
static int yy_did_buffer_switch_on_eof;

void yyrestart( FILE *input_file );
void yy_switch_to_buffer( YY_BUFFER_STATE new_buffer );
YY_BUFFER_STATE yy_create_buffer( FILE *file, int size );
void yy_delete_buffer( YY_BUFFER_STATE b );
void yy_flush_buffer( YY_BUFFER_STATE b );
void yypush_buffer_state( YY_BUFFER_STATE new_buffer );
void yypop_buffer_state( void );

static void yyensure_buffer_stack( void );
static void yy_load_buffer_state( void );
static void yy_init_buffer( YY_BUFFER_STATE b, FILE *file );

YY_BUFFER_STATE yy_scan_buffer( char *base, yy_size_t size );
YY_BUFFER_STATE yy_scan_string( const char *yy_str );
YY_BUFFER_STATE yy_scan_bytes( const char *bytes, int len );

void *yyalloc( yy_size_t );
void *yyrealloc( void *, yy_size_t );
void yyfree( void * );

FILE *yyin = (FILE *) 0, *yyout = (FILE *) 0;

extern int yylineno;

int yylineno = 1;

extern char *yytext;
#define yytext_ptr yytext

static yy_state_type yy_get_previous_state( void );
static yy_state_type yy_try_NUL_trans( yy_state_type current_state );
static int yy_get_next_buffer( void );
static void yy_fatal_error( const char msg[] );

/* Done after the current pattern has been matched and before the
 * corresponding action - sets up yytext.
 */
#define YY_DO_BEFORE_ACTION \
	(yytext_ptr) = yy_bp; \
	yyleng = (size_t) (yy_cp - yy_bp); \
	(yy_hold_char) = *yy_cp; \
	*yy_cp = '\0'; \
	(yy_c_buf_p) = yy_cp;

static const short int yy_accept[] =
{
	    0,     0,     0,     0,     0,     0,     0,    94,    92,     1,
	    4,    33,    92,    92,    89,    32,    19,    11,    12,    30,
	   28,    37,    29,    38,    31,    35,    40,    42,    22,    41,
	   23,    39,    90,    13,    14,    18,    90,    90,    90,    90,
	   90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
	   90,    90,     9,    17,    10,    34,     3,     3,     4,    21,
	    0,     7,     0,    88,     0,     0,     0,    66,     0,    16,
	   59,    64,    55,    62,    56,    63,    36,     0,    87,     6,
	    5,    65,     0,    35,     0,    71,    26,    24,    20,    25,
	   27,    90,     0,    58,    90,    90,    90,    90,    90,    90,
	   90,    90,    90,    90,    51,    90,    90,    90,    90,    90,
	   90,    90,    90,    90,    90,    90,    57,    15,     2,     0,
	    0,     0,     0,     8,     0,     0,     5,     0,    36,    60,
	   61,    91,    90,    90,    90,    90,    90,    90,    90,    90,
	   54,    90,    90,    90,    90,    90,    90,    90,    90,    90,
	   90,    90,    90,     0,     0,     0,     0,    91,    50,    90,
	   77,    90,    90,    52,    90,    90,    49,    90,    90,    90,
	   90,    47,    90,    90,    83,    90,    44,    90,     0,     0,
	    0,    67,    79,    90,    90,    81,    82,    48,    90,    90,
	   90,    90,    90,    90,    90,    53,     0,     0,     0,    90,
	   90,    90,    75,    90,    90,    43,    76,    45,    90,    90,
	    0,     0,     0,    90,    90,    78,    90,    90,    90,    90,
	    0,    70,     0,    90,    80,    90,    86,    90,    72,    69,
	    0,    90,    90,    46,    90,    90,     0,    84,    85,    90,
	   90,     0,    90,    90,     0,    90,    90,     0,    90,    73,
	    0,    90,    68,    90,    74,     0,
};

static const int yy_ec[] =
{
	0, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	3, 1, 1, 2, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 2, 4, 5, 6, 7, 8, 9, 1,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 18,
	18, 18, 18, 18, 18, 18, 18, 18, 19, 20,
	21, 22, 23, 24, 1, 25, 25, 25, 25, 26,
	25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
	25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
	25, 27, 28, 29, 30, 31, 1, 32, 33, 34,
	35, 36, 37, 38, 39, 40, 25, 41, 42, 43,
	44, 45, 46, 25, 47, 48, 49, 50, 51, 52,
	25, 53, 54, 55, 56, 57, 58, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1
};

static const int yy_meta[] =
{
	0,    1,    1,    2,    1,    1,    1,    1,    1,    1,
	1,    1,    1,    1,    1,    1,    1,    1,    3,    1,
	1,    1,    1,    1,    1,    4,    4,    1,    3,    1,
	1,    4,    4,    4,    4,    4,    4,    4,    4,    4,
	4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
	4,    4,    4,    4,    4,    1,    1,    1,    1,
};

static const short int yy_base[] =
{
	    0,   427,   426,     0,     0,    56,    57,   428,   431,   431,
	  425,   404,    56,    45,   431,   403,    58,   431,   431,   402,
	   51,   431,    50,    48,    64,    71,   404,   431,    53,   400,
	   56,   431,   393,   431,   431,   398,    54,    43,    60,    55,
	   65,    71,    72,    73,    66,    78,    80,    83,    84,    85,
	   86,    89,   431,    93,   431,   431,   431,   402,   416,   431,
	  113,   431,     0,   431,   373,   372,   367,   431,   117,   431,
	  431,   431,   431,   431,   431,   431,   107,   374,   431,   431,
	    0,   431,   395,   113,   122,   431,   390,   431,   431,   431,
	  389,   382,     0,   431,    98,   106,   115,   116,   118,   119,
	  122,   120,   123,   125,   381,   124,   128,   126,   130,   131,
	  136,   133,   137,   146,   138,   144,   431,   431,   431,   368,
	  373,   366,   164,   431,     0,   351,     0,   386,   385,   431,
	  431,   374,   154,   157,   155,   158,   162,   160,   165,   167,
	  373,   170,   172,   171,   175,   173,   176,   177,   181,   186,
	  188,   190,   191,   357,   357,   354,   361,   368,   367,   193,
	  366,   192,   197,   365,   199,   200,   364,   202,   201,   209,
	  203,   363,   207,   214,   362,   217,   220,   221,   340,   338,
	  349,   431,   224,   223,   230,   358,   357,   356,   225,   227,
	  231,   234,   233,   236,   237,   355,   335,   346,   349,   238,
	  243,   246,   351,   251,   252,   350,   349,   348,   253,   256,
	  339,   338,   341,   254,   263,   344,   262,   257,   273,   260,
	  335,   431,   326,   261,   341,   275,   340,   276,   279,   431,
	  327,   278,   280,   338,   282,   285,   318,   329,   323,   286,
	  284,   291,   291,   292,   292,   295,   293,   302,   300,   307,
	  250,   297,   431,   302,   228,   431,   341,   345,   349,   351,
	  355,   359,   198,   361,     0,     0,     0,     0,     0,     0,
	    0,     0,
};

static const short int yy_def[] =
{
	    0,   256,   256,   255,     3,   257,   257,   255,   255,   255,
	  255,   255,   258,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   259,   255,   255,   255,   259,   259,   259,   259,
	  259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
	  259,   259,   255,   255,   255,   255,   255,   255,   255,   255,
	  258,   255,   258,   255,   255,   255,   255,   255,   260,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  261,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   259,   262,   255,   259,   259,   259,   259,   259,   259,
	  259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
	  259,   259,   259,   259,   259,   259,   255,   255,   255,   255,
	  255,   255,   260,   255,   260,   255,   261,   255,   255,   255,
	  255,   263,   259,   259,   259,   259,   259,   259,   259,   259,
	  259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
	  259,   259,   259,   255,   255,   255,   255,   263,   259,   259,
	  259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
	  259,   259,   259,   259,   259,   259,   259,   259,   255,   255,
	  255,   255,   259,   259,   259,   259,   259,   259,   259,   259,
	  259,   259,   259,   259,   259,   259,   255,   255,   255,   259,
	  259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
	  255,   255,   255,   259,   259,   259,   259,   259,   259,   259,
	  255,   255,   255,   259,   259,   259,   259,   259,   259,   255,
	  255,   259,   259,   259,   259,   259,   255,   259,   259,   259,
	  259,   255,   259,   259,   255,   259,   259,   255,   259,   259,
	  255,   259,   255,   259,   259,     0,   255,   255,   255,   255,
	  255,   255,   255,   255,     0,     0,     0,     0,     0,     0,
	    0,     0,
};

static const short int yy_nxt[] =
{
	    0,     8,    10,     9,    11,    12,    13,    14,    15,    16,
	   17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
	   27,    28,    29,    30,    31,    32,    32,    33,     8,    34,
	   35,    32,    36,    37,    38,    39,    40,    41,    42,    32,
	   43,    32,    44,    32,    45,    32,    46,    47,    48,    49,
	   50,    32,    51,    32,    32,    52,    53,    54,    55,     9,
	    9,    61,    63,    68,    72,    74,    76,    69,    57,    57,
	   78,    92,    75,    73,    86,    87,    79,    64,    89,    90,
	   70,    80,    92,    92,    62,    65,    81,    82,    92,    83,
	   95,    98,    96,    92,    92,    66,    77,    84,    94,    92,
	   92,    92,   105,   101,   103,    97,    92,    99,    92,   100,
	  104,    92,    92,    92,    92,   116,   102,    92,    61,   108,
	  109,   114,   123,   106,   111,    76,    92,   107,   115,    82,
	  113,    83,   112,    84,    92,   127,   110,   127,   132,    84,
	  128,    62,   133,    92,    92,   124,    92,    92,    92,   117,
	   92,    92,    92,    92,    92,   136,    92,   138,    92,    92,
	  135,    92,   139,   134,    92,    92,    92,   137,   141,   123,
	  140,   144,    92,   146,    92,   142,   147,   143,   151,   145,
	  148,   150,    92,    92,   152,    92,    92,   149,    92,   159,
	   92,   160,   124,    92,   162,    92,   163,   158,    92,    92,
	   92,    92,   131,    92,    92,    92,   166,   161,   167,    92,
	  164,   168,   169,   171,    92,   165,    92,   173,    92,    92,
	   92,    92,   174,   170,   175,    92,   172,    92,    92,    92,
	   92,    92,   183,   177,   182,    92,   186,    92,   188,   176,
	  189,   191,    92,   185,   187,    92,   192,   184,    92,    92,
	  190,    92,    92,    92,   193,    92,    92,   195,    92,    92,
	  203,    92,    92,   204,    92,    92,    92,   200,   207,   194,
	  199,    92,   201,   206,    92,   205,   208,   209,   202,    92,
	   92,    92,    92,   213,    92,    92,   252,   216,    92,    92,
	   92,    92,   226,   214,   223,   215,   217,   218,   219,   224,
	  225,    92,   228,    92,    92,   231,    92,    92,    92,   227,
	   92,   233,    92,    92,    92,   232,   234,   240,   242,    92,
	   92,    92,   235,    92,   238,    92,   246,   237,    92,   239,
	   92,   248,   249,   243,   245,    92,   251,   254,   250,   247,
	  244,   253,     8,     8,     8,     8,    56,    56,    56,    56,
	   60,    92,    60,    60,    91,    91,   122,    92,   122,   122,
	  126,   241,   126,   126,   157,   157,    92,   236,    92,    92,
	  230,   229,    92,   222,   221,   220,    92,    92,    92,    92,
	  212,   211,   210,    92,    92,    92,    92,   198,   197,   196,
	   92,    92,    92,    92,    92,    92,    92,   181,   180,   179,
	  178,    92,    92,   128,   128,   156,   155,   154,   153,    92,
	   92,   130,   129,    76,   125,   121,   120,   119,    58,   118,
	   93,    92,    88,    85,    71,    67,    59,    58,   255,     9,
	    9,     7,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	    0,     0,     0,     0,     0,     0,
};

static const short int yy_chk[] =
{
	    0,     3,     3,     3,     3,     3,     3,     3,     3,     3,
	    3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
	    3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
	    3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
	    3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
	    3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
	    6,    12,    13,    16,    20,    22,    23,    16,     5,     6,
	   24,    37,    22,    20,    28,    28,    24,    13,    30,    30,
	   16,    24,    36,    39,    12,    13,    24,    25,    38,    25,
	   37,    39,    38,    40,    44,    13,    23,    25,    36,    41,
	   42,    43,    44,    41,    42,    38,    45,    40,    46,    40,
	   43,    47,    48,    49,    50,    53,    41,    51,    60,    47,
	   48,    51,    68,    45,    49,    76,    94,    46,    51,    83,
	   50,    83,    49,    76,    95,    84,    48,    84,    94,    83,
	   84,    60,    95,    96,    97,    68,    98,    99,   101,    53,
	  100,   102,   105,   103,   107,    98,   106,   100,   108,   109,
	   97,   111,   101,    96,   110,   112,   114,    99,   103,   122,
	  102,   107,   115,   109,   113,   105,   110,   106,   114,   108,
	  111,   113,   132,   134,   115,   133,   135,   112,   137,   133,
	  136,   134,   122,   138,   136,   139,   137,   132,   141,   143,
	  142,   145,   262,   144,   146,   147,   141,   135,   142,   148,
	  138,   143,   144,   146,   149,   139,   150,   148,   151,   152,
	  161,   159,   149,   145,   150,   162,   147,   164,   165,   168,
	  167,   170,   161,   152,   159,   172,   165,   169,   168,   151,
	  169,   172,   173,   164,   167,   175,   173,   162,   176,   177,
	  170,   183,   182,   188,   175,   189,   254,   177,   184,   190,
	  189,   192,   191,   189,   193,   194,   199,   183,   192,   176,
	  182,   200,   184,   191,   201,   190,   193,   194,   188,   203,
	  204,   208,   213,   199,   209,   217,   250,   203,   219,   223,
	  216,   214,   217,   200,   213,   201,   204,   208,   209,   214,
	  216,   218,   219,   225,   227,   223,   231,   228,   232,   218,
	  234,   227,   240,   235,   239,   225,   228,   235,   239,   242,
	  243,   246,   228,   245,   232,   251,   243,   231,   248,   234,
	  253,   245,   246,   240,   242,   249,   248,   253,   247,   244,
	  241,   251,   256,   256,   256,   256,   257,   257,   257,   257,
	  258,   238,   258,   258,   259,   259,   260,   237,   260,   260,
	  261,   236,   261,   261,   263,   263,   233,   230,   226,   224,
	  222,   220,   215,   212,   211,   210,   207,   206,   205,   202,
	  198,   197,   196,   195,   187,   186,   185,   180,   179,   178,
	  174,   171,   166,   163,   160,   158,   157,   156,   155,   154,
	  153,   140,   131,   128,   127,   125,   121,   120,   119,   104,
	   91,    90,    86,    82,    77,    66,    65,    64,    58,    57,
	   35,    32,    29,    26,    19,    15,    11,    10,     7,     2,
	    1,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	  255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
	    0,     0,     0,     0,     0,     0,
};

static yy_state_type yy_last_accepting_state;
static char *yy_last_accepting_cpos;

extern int yy_flex_debug;
int yy_flex_debug = 0;

char *yytext;

int yywrap();
static void yyunput( int c, char *buf_ptr );

static char ch_buf[YY_BUF_SIZE];

/*
==============
yysetlength
==============
*/
void yysetlength( const char *text, int len )
{
	yylval.val.stringValue = SL_GetStringOfLen(text, 0, len + 1, 0xd);
}

/*
==============
StringValue
==============
*/
int StringValue( char *str, int len )
{
	char *pC;
	char string[8192];

	if ( len >= 8192 )
	{
		CompileError(g_sourcePos, "max string length exceeded: \"%s\"", str);
		return 0;
	}

	pC = string;

	while ( len )
	{
		if ( *str != '\\' )
		{
			len--;
			*pC++ = *str++;
			continue;
		}

		len--;

		if ( !len )
			break;

		str++;

		switch ( *str )
		{
		case 'n':
			*pC++ = '\n';
			break;
		case 'r':
			*pC++ = '\r';
			break;
		case 't':
			*pC++ = '\t';
			break;
		default:
			*pC++ = *str;
			break;
		}

		len--;
		str++;
	}

	*pC = 0;

	yylval.val.stringValue = SL_GetString_(string, g_parse_user, 13);
	return 1;
}

/*
==============
yycopyint
==============
*/
int yycopyint( char *s )
{
	return sscanf(s, "%d", &yylval);
}

/*
==============
yycopyfloat
==============
*/
int yycopyfloat( char *s )
{
	return sscanf(s, "%f", &yylval);
}
int yylex()
{
	/** The main scanner function which does all the work.
	*/
	int yy_amount_of_matched_text;
	int yy_next_state;
	int yy_retval;
	register int yy_current_state;
	register char *yy_cp;
	register char *yy_bp;
	register int yy_act;
	register unsigned char yy_c;

	if ( yy_init )
	{
		yy_init = 0;
		if ( !yy_start )
		{
			yy_start = 1; /* first start state */
		}

		if ( !yyin )
		{
			yyin = stdin;
		}

		if ( !yyout )
		{
			yyout = stdout;
		}

		if ( !YY_CURRENT_BUFFER )
		{
			yyensure_buffer_stack();
			YY_CURRENT_BUFFER_LVALUE = yy_create_buffer(yyin, YY_BUF_SIZE);
		}

		yy_load_buffer_state();
	}

	while ( 1 ) /* loops until end-of-file is reached */
	{
		yy_cp = yy_c_buf_p;

		/* Support of yytext. */
		*yy_cp = yy_hold_char;

		/* yy_bp points to the position in yy_ch_buf of the start of
		* the current run.
		*/
		yy_bp = yy_cp;

		yy_current_state = yy_start;

yy_match:
		do
		{
			yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)];
			if ( yy_accept[yy_current_state] )
			{
				yy_last_accepting_state = yy_current_state;
				yy_last_accepting_cpos = yy_cp;
			}
			while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
			{
				yy_current_state = (int) yy_def[yy_current_state];

				if ( yy_current_state >= 256 )
				{
					yy_c = yy_meta[(unsigned int) yy_c];
				}
			}
			yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
			++yy_cp;
		}
		while ( yy_base[yy_current_state] != 431 );

yy_find_action:

		yy_act = yy_accept[yy_current_state];
		if ( !yy_act )
		{
			/* have to back up */
			yy_cp = yy_last_accepting_cpos;
			yy_current_state = yy_last_accepting_state;
			yy_act = yy_accept[yy_current_state];
		}

		yytext = yy_bp;
		yyleng = yy_cp - yy_bp;
		yy_hold_char = *yy_cp;
		*yy_cp = 0;
		yy_c_buf_p = yy_cp;

do_action: /* This label is used only to access EOF actions. */
		switch ( yy_act )
		{
		/* beginning of action switch */
		case 0: /* must back up */
			/* undo the effects of YY_DO_BEFORE_ACTION */
			*yy_cp = yy_hold_char;
			yy_cp = yy_last_accepting_cpos;
			yy_current_state = yy_last_accepting_state;
			goto yy_find_action;
		case 1:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			break;
		case 2:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			yy_start = 3;
			break;
		case 3:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			break;
		case 4:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			break;
		case 5:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			break;
		case 6:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			yy_start = 5;
			break;
		case 7:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = StringValue(yytext + 1, yyleng - 2) != 0 ? 260 : 258; goto lex_done; }
		case 8:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = StringValue(yytext + 2, yyleng - 3) != 0 ? 261 : 258; goto lex_done; }
		case 9:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 262; goto lex_done; }
		case 10:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 263; goto lex_done; }
		case 11:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 264; goto lex_done; }
		case 12:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 265; goto lex_done; }
		case 13:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 266; goto lex_done; }
		case 14:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 267; goto lex_done; }
		case 15:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 268; goto lex_done; }
		case 16:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 269; goto lex_done; }
		case 17:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 270; goto lex_done; }
		case 18:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 271; goto lex_done; }
		case 19:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 272; goto lex_done; }
		case 20:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 273; goto lex_done; }
		case 21:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 274; goto lex_done; }
		case 22:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 275; goto lex_done; }
		case 23:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 276; goto lex_done; }
		case 24:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 277; goto lex_done; }
		case 25:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 278; goto lex_done; }
		case 26:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 279; goto lex_done; }
		case 27:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 280; goto lex_done; }
		case 28:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 281; goto lex_done; }
		case 29:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 282; goto lex_done; }
		case 30:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 283; goto lex_done; }
		case 31:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 284; goto lex_done; }
		case 32:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 285; goto lex_done; }
		case 33:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 286; goto lex_done; }
		case 34:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 287; goto lex_done; }
		case 35:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			yycopyint(yytext);       // IntegerValue
			{ yy_retval = 288; goto lex_done; }
		case 36:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			yycopyfloat(yytext);       // FloatValue
			{ yy_retval = 289; goto lex_done; }
		case 37:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 291; goto lex_done; }
		case 38:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 290; goto lex_done; }
		case 39:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 295; goto lex_done; }
		case 40:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 292; goto lex_done; }
		case 41:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 294; goto lex_done; }
		case 42:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 293; goto lex_done; }
		case 43:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 296; goto lex_done; }
		case 44:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 297; goto lex_done; }
		case 45:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 298; goto lex_done; }
		case 46:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 299; goto lex_done; }
		case 47:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 300; goto lex_done; }
		case 48:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 301; goto lex_done; }
		case 49:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 302; goto lex_done; }
		case 50:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 303; goto lex_done; }
		case 51:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 304; goto lex_done; }
		case 52:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 305; goto lex_done; }
		case 53:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 306; goto lex_done; }
		case 54:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 307; goto lex_done; }
		case 55:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 308; goto lex_done; }
		case 56:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 309; goto lex_done; }
		case 57:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 310; goto lex_done; }
		case 58:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 311; goto lex_done; }
		case 59:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 312; goto lex_done; }
		case 60:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 313; goto lex_done; }
		case 61:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 314; goto lex_done; }
		case 62:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 315; goto lex_done; }
		case 63:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 316; goto lex_done; }
		case 64:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 317; goto lex_done; }
		case 65:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 318; goto lex_done; }
		case 66:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 319; goto lex_done; }
		case 67:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 320; goto lex_done; }
		case 68:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 321; goto lex_done; }
		case 69:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 322; goto lex_done; }
		case 70:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 323; goto lex_done; }
		case 71:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 324; goto lex_done; }
		case 72:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 326; goto lex_done; }
		case 73:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 327; goto lex_done; }
		case 74:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 328; goto lex_done; }
		case 75:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 329; goto lex_done; }
		case 76:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 330; goto lex_done; }
		case 77:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 331; goto lex_done; }
		case 78:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 332; goto lex_done; }
		case 79:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 333; goto lex_done; }
		case 80:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 334; goto lex_done; }
		case 81:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 335; goto lex_done; }
		case 82:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 336; goto lex_done; }
		case 83:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 337; goto lex_done; }
		case 84:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 338; goto lex_done; }
		case 85:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 339; goto lex_done; }
		case 86:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 340; goto lex_done; }
		case 87:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 341; goto lex_done; }
		case 88:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 342; goto lex_done; }
		case 89:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			{ yy_retval = 343; goto lex_done; }
		case 90:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;                  // TextValue
			yysetlength(yytext, yyleng);
			{ yy_retval = 259; goto lex_done; }
		case 91:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			yysetlength(yytext, yyleng);
			{ yy_retval = 325; goto lex_done; }
		case 92:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			CompileError(g_sourcePos, "bad token '%s'", yytext);
			{ yy_retval = 258; goto lex_done; }
		case 93:
			yylval.pos = g_out_pos;
			g_sourcePos = g_out_pos;
			g_out_pos += yyleng;
			fwrite(yytext, yyleng, 1u, yyout);
			break;
		case 95: // YY_STATE_EOF(...)
		case 96:
		case 97:
			{ yy_retval = 0; goto lex_done; } // YYNULL
		case 94: // YY_END_OF_BUFFER
		{
			/* Amount of text matched not including the EOB char. */
			yy_amount_of_matched_text = yy_cp - yytext - 1;

			/* Undo the effects of YY_DO_BEFORE_ACTION. */
			*yy_cp = yy_hold_char;

			if ( !YY_CURRENT_BUFFER_LVALUE->yy_buffer_status ) // YY_BUFFER_NEW
			{
				/* We're scanning a new file or input source.  It's
				* possible that this happened because the user
				* just pointed yyin at a new source and called
				* yylex().  If so, then we have to assure
				* consistency between YY_CURRENT_BUFFER and our
				* globals.  Here is the right place to do so, because
				* this is the first action (other than possibly a
				* back-up) that will match for the new input source.
				*/
				yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
				YY_CURRENT_BUFFER_LVALUE->yy_input_file = yyin;
				YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = 1;
			}

			/* Note that here we test for yy_c_buf_p "<=" to the position
			* of the first EOB in the buffer, since yy_c_buf_p will
			* already have been incremented past the NUL character
			* (since all states make transitions on EOB to the
			* end-of-buffer state).  Contrast this with the test
			* in input().
			*/
			if ( yy_c_buf_p <= &(YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yy_n_chars]) )
			{
				/* This was really a NUL. */

				yy_c_buf_p = &((yytext)[yy_amount_of_matched_text]);
				yy_current_state = yy_get_previous_state();

				/* Okay, we're now positioned to make the NUL
				* transition.  We couldn't have
				* yy_get_previous_state() go ahead and do it
				* for us because it doesn't know how to deal
				* with the possibility of jamming (and we don't
				* want to build jamming into it because then it
				* will run more slowly).
				*/

				yy_next_state = yy_try_NUL_trans(yy_current_state);
				yy_bp = yytext; // YY_MORE_ADJ

				if ( yy_next_state )
				{
					yy_cp = ++yy_c_buf_p;
					yy_current_state = yy_next_state;
					goto yy_match;
				}

				yy_cp = yy_c_buf_p;
				goto yy_find_action;
			}

			else switch ( yy_get_next_buffer() )
			{
			case EOB_ACT_END_OF_FILE:
				yy_did_buffer_switch_on_eof = 0;

				if ( yywrap() )
				{
					/* Note: because we've taken care in
					* yy_get_next_buffer() to have set up
					* yytext, we can now set up
					* yy_c_buf_p so that if some total
					* hoser (like flex itself) wants to
					* call the scanner after we return the
					* YY_NULL, it'll still work - another
					* YY_NULL will get returned.
					*/
					yy_c_buf_p = yytext; // YY_MORE_ADJ
					yy_act = (yy_start - 1) / 2 + 95;
					goto do_action;
				}

				else
				{
					if ( ! yy_did_buffer_switch_on_eof )
						yyrestart( yyin );
				}
				break;

			case EOB_ACT_CONTINUE_SCAN:
				yy_c_buf_p = &((yytext)[yy_amount_of_matched_text]);
				yy_current_state = yy_get_previous_state();
				yy_cp = yy_c_buf_p;
				yy_bp = yytext;
				goto yy_match;

			case EOB_ACT_LAST_MATCH:
				yy_c_buf_p = &(YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yy_n_chars]);
				yy_current_state = yy_get_previous_state();
				yy_cp = yy_c_buf_p;
				yy_bp = yytext;
				goto yy_find_action;
			}

			break;
		}
		default:
			yy_fatal_error("fatal flex scanner internal error--no action found");
			break;
		}
	}
lex_done:
	return yy_retval;
}

/* yy_get_next_buffer - try to read in a new buffer
 *
 * Returns a code representing an action:
 *	EOB_ACT_LAST_MATCH -
 *	EOB_ACT_CONTINUE_SCAN - continue scanning from current position
 *	EOB_ACT_END_OF_FILE - end of file
 */
static int yy_get_next_buffer( void )
{
	register char *dest = YY_CURRENT_BUFFER_LVALUE->yy_ch_buf;
	register char *source = (yytext_ptr);
	register int number_to_move, i;
	int ret_val;

	if ( (yy_c_buf_p) > &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars) + 1] )
		YY_FATAL_ERROR(
		"fatal flex scanner internal error--end of buffer missed" );

	if ( YY_CURRENT_BUFFER_LVALUE->yy_fill_buffer == 0 )
	{ /* Don't try to fill the buffer, so this is an EOF. */
		if ( (yy_c_buf_p) - (yytext_ptr) - YY_MORE_ADJ == 1 )
		{
			/* We matched a single character, the EOB, so
			 * treat this as a final EOF.
			 */
			return EOB_ACT_END_OF_FILE;
		}

		else
		{
			/* We matched some text prior to the EOB, first
			 * process it.
			 */
			return EOB_ACT_LAST_MATCH;
		}
	}

	/* Try to read more data. */

	/* First move last chars to start of buffer. */
	number_to_move = (int) ((yy_c_buf_p) - (yytext_ptr)) - 1;

	for ( i = 0; i < number_to_move; ++i )
		*(dest++) = *(source++);

	if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_EOF_PENDING )
		/* don't do the read, it's not guaranteed to return an EOF,
		 * just force an EOF
		 */
		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars) = 0;

	else
	{
		size_t num_to_read =
			YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;

		while ( num_to_read <= 0 )
		{ /* Not enough room in the buffer - grow it. */

			/* just a shorter name for the current buffer */
			YY_BUFFER_STATE b = YY_CURRENT_BUFFER;

			int yy_c_buf_p_offset =
				(int) ((yy_c_buf_p) - b->yy_ch_buf);

			if ( b->yy_is_our_buffer )
			{
				int new_size = b->yy_buf_size * 2;

				if ( new_size <= 0 )
					b->yy_buf_size += b->yy_buf_size / 8;
				else
					b->yy_buf_size *= 2;

				b->yy_ch_buf = (char *)
					/* Include room in for 2 EOB chars. */
					yyrealloc((void *) b->yy_ch_buf, b->yy_buf_size + 2 );
			}
			else
				/* Can't grow it, we don't own it. */
				b->yy_ch_buf = 0;

			if ( ! b->yy_ch_buf )
				YY_FATAL_ERROR(
				"fatal error - scanner input buffer overflow" );

			(yy_c_buf_p) = &b->yy_ch_buf[yy_c_buf_p_offset];

			num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -
						number_to_move - 1;
		}

		if ( num_to_read > YY_READ_BUF_SIZE )
			num_to_read = YY_READ_BUF_SIZE;

		/* Read in more data. */
		(yy_n_chars) = Scr_ScanFile( &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move], num_to_read );

		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
	}

	if ( (yy_n_chars) == 0 )
	{
		if ( number_to_move == YY_MORE_ADJ )
		{
			ret_val = EOB_ACT_END_OF_FILE;
			yyrestart(yyin );
		}

		else
		{
			ret_val = EOB_ACT_LAST_MATCH;
			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status =
				YY_BUFFER_EOF_PENDING;
		}
	}

	else
		ret_val = EOB_ACT_CONTINUE_SCAN;

	(yy_n_chars) += number_to_move;
	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] = YY_END_OF_BUFFER_CHAR;
	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars) + 1] = YY_END_OF_BUFFER_CHAR;

	(yytext_ptr) = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0];

	return ret_val;
}

/* yy_get_previous_state - get the state just before the EOB char was reached */
static yy_state_type yy_get_previous_state( void )
{
	register yy_state_type yy_current_state;
	register char *yy_cp;

	yy_current_state = (yy_start);

	for ( yy_cp = (yytext_ptr) + YY_MORE_ADJ; yy_cp < (yy_c_buf_p); ++yy_cp )
	{
		register YY_CHAR yy_c = (*yy_cp ? yy_ec[YY_SC_TO_UI(*yy_cp)] : 1);
		if ( yy_accept[yy_current_state] )
		{
			(yy_last_accepting_state) = yy_current_state;
			(yy_last_accepting_cpos) = yy_cp;
		}
		while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
		{
			yy_current_state = (int) yy_def[yy_current_state];
			if ( yy_current_state >= 256 )
				yy_c = yy_meta[(unsigned int) yy_c];
		}
		yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
	}

	return yy_current_state;
}

/* yy_try_NUL_trans - try to make a transition on the NUL character
 *
 * synopsis
 *	next_state = yy_try_NUL_trans( current_state );
 */
static yy_state_type yy_try_NUL_trans( yy_state_type yy_current_state )
{
	register int yy_is_jam;
	register char *yy_cp = (yy_c_buf_p);

	register YY_CHAR yy_c = 1;
	if ( yy_accept[yy_current_state] )
	{
		(yy_last_accepting_state) = yy_current_state;
		(yy_last_accepting_cpos) = yy_cp;
	}
	while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
	{
		yy_current_state = (int) yy_def[yy_current_state];
		if ( yy_current_state >= 256 )
			yy_c = yy_meta[(unsigned int) yy_c];
	}
	yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
	yy_is_jam = (yy_current_state == 255);

	return yy_is_jam ? 0 : yy_current_state;
}

static void yyunput( int c, register char *yy_bp )
{
	register char *yy_cp;

	yy_cp = (yy_c_buf_p);

	/* undo effects of setting up yytext */
	*yy_cp = (yy_hold_char);

	if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
	{ /* need to shift things up to make room */
		/* +2 for EOB chars. */
		register int number_to_move = (yy_n_chars) + 2;
		register char *dest = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[
					YY_CURRENT_BUFFER_LVALUE->yy_buf_size + 2];
		register char *source =
				&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move];

		while ( source > YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
			*--dest = *--source;

		yy_cp += (int) (dest - source);
		yy_bp += (int) (dest - source);
		YY_CURRENT_BUFFER_LVALUE->yy_n_chars =
			(yy_n_chars) = YY_CURRENT_BUFFER_LVALUE->yy_buf_size;

		if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
			YY_FATAL_ERROR( "flex scanner push-back overflow" );
	}

	*--yy_cp = (char) c;

	(yytext_ptr) = yy_bp;
	(yy_hold_char) = *yy_cp;
	(yy_c_buf_p) = yy_cp;
}

static int input( void )
{
	int c;

	*(yy_c_buf_p) = (yy_hold_char);

	if ( *(yy_c_buf_p) == YY_END_OF_BUFFER_CHAR )
	{
		/* yy_c_buf_p now points to the character we want to return.
		 * If this occurs *before* the EOB characters, then it's a
		 * valid NUL; if not, then we've hit the end of the buffer.
		 */
		if ( (yy_c_buf_p) < &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] )
			/* This was really a NUL. */
			*(yy_c_buf_p) = '\0';

		else
		{ /* need more input */
			int offset = (yy_c_buf_p) - (yytext_ptr);
			++(yy_c_buf_p);

			switch ( yy_get_next_buffer( ) )
			{
				case EOB_ACT_LAST_MATCH:
					/* This happens because yy_g_n_b()
					 * sees that we've accumulated a
					 * token and flags that we need to
					 * try matching the token before
					 * proceeding.  But for input(),
					 * there's no matching to consider.
					 * So convert the EOB_ACT_LAST_MATCH
					 * to EOB_ACT_END_OF_FILE.
					 */

					/* Reset buffer status. */
					yyrestart(yyin );

					/*FALLTHROUGH*/

				case EOB_ACT_END_OF_FILE:
				{
					if ( yywrap( ) )
						return EOF;

					if ( ! (yy_did_buffer_switch_on_eof) )
						yyrestart(yyin );
					return input();
				}

				case EOB_ACT_CONTINUE_SCAN:
					(yy_c_buf_p) = (yytext_ptr) + offset;
					break;
			}
		}
	}

	c = *(unsigned char *) (yy_c_buf_p); /* cast for 8-bit char's */
	*(yy_c_buf_p) = '\0'; /* preserve yytext */
	(yy_hold_char) = *++(yy_c_buf_p);

	return c;
}

/** Immediately switch to a different input stream.
 * @param input_file A readable stream.
 *
 * @note This function does not reset the start condition to @c INITIAL .
 */
void yyrestart( FILE *input_file )
{
	if ( ! YY_CURRENT_BUFFER )
	{
		yyensure_buffer_stack ();
		YY_CURRENT_BUFFER_LVALUE =
			yy_create_buffer(yyin, YY_BUF_SIZE );
	}

	yy_init_buffer(YY_CURRENT_BUFFER, input_file );
	yy_load_buffer_state( );
}

/** Switch to a different input buffer.
 * @param new_buffer The new input buffer.
 */
void yy_switch_to_buffer( YY_BUFFER_STATE new_buffer )
{
	/* TODO. We should be able to replace this entire function body
	 * with
	 *		yypop_buffer_state();
	 *		yypush_buffer_state(new_buffer);
	 */
	yyensure_buffer_stack ();
	if ( YY_CURRENT_BUFFER == new_buffer )
		return;

	if ( YY_CURRENT_BUFFER )
	{
		/* Flush out information for old buffer. */
		*(yy_c_buf_p) = (yy_hold_char);
		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = (yy_c_buf_p);
		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
	}

	YY_CURRENT_BUFFER_LVALUE = new_buffer;
	yy_load_buffer_state( );

	/* We don't actually know whether we did this switch during
	 * EOF (yywrap()) processing, but the only time this flag
	 * is looked at is after yywrap() is called, so it's safe
	 * to go ahead and always set it.
	 */
	(yy_did_buffer_switch_on_eof) = 1;
}

static void yy_load_buffer_state( void )
{
	(yy_n_chars) = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
	(yytext_ptr) = (yy_c_buf_p) = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;
	yyin = YY_CURRENT_BUFFER_LVALUE->yy_input_file;
	(yy_hold_char) = *(yy_c_buf_p);
}

/** Allocate and initialize an input buffer state.
 * @param file A readable stream.
 * @param size The character buffer size in bytes. When in doubt, use @c YY_BUF_SIZE.
 *
 * @return the allocated buffer state.
 */
YY_BUFFER_STATE yy_create_buffer( FILE *file, int size )
{
	YY_BUFFER_STATE b;

	b = (YY_BUFFER_STATE) yyalloc(sizeof( struct yy_buffer_state ) );
	if ( ! b )
		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

	b->yy_buf_size = size;

	/* yy_ch_buf has to be 2 characters longer than the size given because
	 * we need to put in 2 end-of-buffer characters.
	 */
	b->yy_ch_buf = (char *) yyalloc(b->yy_buf_size + 2 );
	if ( ! b->yy_ch_buf )
		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

	b->yy_is_our_buffer = 1;

	yy_init_buffer(b, file );

	return b;
}

/** Destroy the buffer.
 * @param b a buffer created with yy_create_buffer()
 */
void yy_delete_buffer( YY_BUFFER_STATE b )
{
	if ( ! b )
		return;

	if ( b == YY_CURRENT_BUFFER ) /* Not sure if we should pop here. */
		YY_CURRENT_BUFFER_LVALUE = (YY_BUFFER_STATE) 0;

	if ( b->yy_is_our_buffer )
		yyfree((void *) b->yy_ch_buf );

	yyfree((void *) b );
}

extern int isatty( int );

/* Initializes or reinitializes a buffer.
 * This function is sometimes called more than once on the same buffer,
 * such as during a yyrestart() or at EOF.
 */
static void yy_init_buffer( YY_BUFFER_STATE b, FILE *file )
{
	int oerrno = errno;

	yy_flush_buffer(b );

	b->yy_input_file = file;
	b->yy_fill_buffer = 1;

	/* If b is the current buffer, then yy_init_buffer was _probably_
	 * called from yyrestart() or through yy_get_next_buffer.
	 * In that case, we don't want to reset the lineno or column.
	 */
	if (b != YY_CURRENT_BUFFER)
	{
		b->yy_bs_lineno = 1;
		b->yy_bs_column = 0;
	}

	b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;

	errno = oerrno;
}

/** Discard all buffered characters. On the next scan, YY_INPUT will be called.
 * @param b the buffer state to be flushed, usually @c YY_CURRENT_BUFFER.
 */
void yy_flush_buffer( YY_BUFFER_STATE b )
{
	if ( ! b )
		return;

	b->yy_n_chars = 0;

	/* We always need two end-of-buffer characters.  The first causes
	 * a transition to the end-of-buffer state.  The second causes
	 * a jam in that state.
	 */
	b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
	b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;

	b->yy_buf_pos = &b->yy_ch_buf[0];

	b->yy_at_bol = 1;
	b->yy_buffer_status = YY_BUFFER_NEW;

	if ( b == YY_CURRENT_BUFFER )
		yy_load_buffer_state( );
}

/** Pushes the new state onto the stack. The new state becomes
 *  the current state. This function will allocate the stack
 *  if necessary.
 *  @param new_buffer The new state.
 */
void yypush_buffer_state( YY_BUFFER_STATE new_buffer )
{
	if (new_buffer == NULL)
		return;

	yyensure_buffer_stack();

	/* This block is copied from yy_switch_to_buffer. */
	if ( YY_CURRENT_BUFFER )
	{
		/* Flush out information for old buffer. */
		*(yy_c_buf_p) = (yy_hold_char);
		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = (yy_c_buf_p);
		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
	}

	/* Only push if top exists. Otherwise, replace top. */
	if (YY_CURRENT_BUFFER)
		(yy_buffer_stack_top)++;
	YY_CURRENT_BUFFER_LVALUE = new_buffer;

	/* copied from yy_switch_to_buffer. */
	yy_load_buffer_state( );
	(yy_did_buffer_switch_on_eof) = 1;
}

/** Removes and deletes the top of the stack, if present.
 *  The next element becomes the new top.
 */
void yypop_buffer_state( void )
{
	if (!YY_CURRENT_BUFFER)
		return;

	yy_delete_buffer(YY_CURRENT_BUFFER );
	YY_CURRENT_BUFFER_LVALUE = NULL;
	if ((yy_buffer_stack_top) > 0)
		--(yy_buffer_stack_top);

	if (YY_CURRENT_BUFFER)
	{
		yy_load_buffer_state( );
		(yy_did_buffer_switch_on_eof) = 1;
	}
}

/* Allocates the stack if it does not exist.
 *  Guarantees space for at least one push.
 */
static void yyensure_buffer_stack( void )
{
	int num_to_alloc;

	if (!(yy_buffer_stack))
	{
		/* First allocation is just for 2 elements, since we don't know if this
		 * scanner will even need a stack. We use 2 instead of 1 to avoid an
		 * immediate realloc on the next call.
		 */
		num_to_alloc = 1;
		(yy_buffer_stack) = (struct yy_buffer_state**)yyalloc
								(num_to_alloc * sizeof(struct yy_buffer_state*)
								);

		memset((yy_buffer_stack), 0, num_to_alloc * sizeof(struct yy_buffer_state*));

		(yy_buffer_stack_max) = num_to_alloc;
		(yy_buffer_stack_top) = 0;
		return;
	}

	if ((yy_buffer_stack_top) >= ((yy_buffer_stack_max)) - 1)
	{
		/* Increase the buffer to prepare for a possible push. */
		int grow_size = 8 /* arbitrary grow size */;

		num_to_alloc = (yy_buffer_stack_max) + grow_size;
		(yy_buffer_stack) = (struct yy_buffer_state**)yyrealloc
								((yy_buffer_stack),
								num_to_alloc * sizeof(struct yy_buffer_state*)
								);

		/* zero only the new slots.*/
		memset((yy_buffer_stack) + (yy_buffer_stack_max), 0, grow_size * sizeof(struct yy_buffer_state*));
		(yy_buffer_stack_max) = num_to_alloc;
	}
}

/** Setup the input buffer state to scan directly from a user-specified character buffer.
 * @param base the character buffer
 * @param size the size in bytes of the character buffer
 *
 * @return the newly allocated buffer state object.
 */
YY_BUFFER_STATE yy_scan_buffer( char *base, yy_size_t size )
{
	YY_BUFFER_STATE b;

	if ( size < 2 ||
	     base[size-2] != YY_END_OF_BUFFER_CHAR ||
	     base[size-1] != YY_END_OF_BUFFER_CHAR )
		/* They forgot to leave room for the EOB's. */
		return 0;

	b = (YY_BUFFER_STATE) yyalloc(sizeof( struct yy_buffer_state ) );
	if ( ! b )
		YY_FATAL_ERROR( "out of dynamic memory in yy_scan_buffer()" );

	b->yy_buf_size = size - 2; /* "- 2" to take care of EOB's */
	b->yy_buf_pos = b->yy_ch_buf = base;
	b->yy_is_our_buffer = 0;
	b->yy_input_file = 0;
	b->yy_n_chars = b->yy_buf_size;
	b->yy_is_interactive = 0;
	b->yy_at_bol = 1;
	b->yy_fill_buffer = 0;
	b->yy_buffer_status = YY_BUFFER_NEW;

	yy_switch_to_buffer(b );

	return b;
}

/** Setup the input buffer state to scan a string. The next call to yylex() will
 * scan from a @e copy of @a str.
 * @param yy_str a NUL-terminated string to scan
 *
 * @return the newly allocated buffer state object.
 */
YY_BUFFER_STATE yy_scan_string( const char *yy_str )
{
	return yy_scan_bytes(yy_str, strlen(yy_str) );
}

/** Setup the input buffer state to scan the given bytes. The next call to yylex() will
 * scan from a @e copy of @a bytes.
 * @param bytes the byte buffer to scan
 * @param len the number of bytes in the buffer pointed to by @a bytes.
 *
 * @return the newly allocated buffer state object.
 */
YY_BUFFER_STATE yy_scan_bytes( const char *bytes, int len )
{
	YY_BUFFER_STATE b;
	char *buf;
	yy_size_t n;
	int i;

	/* Get memory for full buffer, including space for trailing EOB's. */
	n = len + 2;
	buf = (char *) yyalloc(n );
	if ( ! buf )
		YY_FATAL_ERROR( "out of dynamic memory in yy_scan_bytes()" );

	for ( i = 0; i < len; ++i )
		buf[i] = bytes[i];

	buf[len] = buf[len+1] = YY_END_OF_BUFFER_CHAR;

	b = yy_scan_buffer(buf, n );
	if ( ! b )
		YY_FATAL_ERROR( "bad buffer in yy_scan_bytes()" );

	/* It's okay to grow etc. this buffer, and we should throw it
	 * away when we're done.
	 */
	b->yy_is_our_buffer = 1;

	return b;
}

#define YY_EXIT_FAILURE 2

static void yy_fatal_error( const char *msg )
{
	(void) fprintf( stderr, "%s\n", msg );
	exit( YY_EXIT_FAILURE );
}

/* Accessor methods (get/set functions) to struct members. */

/** Get the current line number.
 */
int yyget_lineno( void )
{
	return yylineno;
}

/** Get the input stream.
 */
FILE *yyget_in( void )
{
	return yyin;
}

/** Get the output stream.
 */
FILE *yyget_out( void )
{
	return yyout;
}

/** Get the length of the current token.
 */
int yyget_leng( void )
{
	return yyleng;
}

/** Get the current token.
 */
char *yyget_text( void )
{
	return yytext;
}

/** Set the current line number.
 * @param line_number
 */
void yyset_lineno( int line_number )
{
	yylineno = line_number;
}

/** Set the input stream. This does not discard the current
 * input buffer.
 * @param in_str A readable stream.
 */
void yyset_in( FILE *in_str )
{
	yyin = in_str;
}

void yyset_out( FILE *out_str )
{
	yyout = out_str;
}

int yyget_debug( void )
{
	return yy_flex_debug;
}

void yyset_debug( int bdebug )
{
	yy_flex_debug = bdebug;
}

/* yylex_destroy is for both reentrant and non-reentrant scanners. */
int yylex_destroy( void )
{
	/* Pop the buffer stack, destroying each element. */
	while(YY_CURRENT_BUFFER)
	{
		yy_delete_buffer(YY_CURRENT_BUFFER );
		YY_CURRENT_BUFFER_LVALUE = NULL;
		yypop_buffer_state();
	}

	/* Destroy the stack itself. */
	yyfree((yy_buffer_stack) );
	(yy_buffer_stack) = NULL;

	return 0;
}

void *yyalloc( yy_size_t size )
{
	return (void *) malloc( size );
}

void *yyrealloc( void *ptr, yy_size_t size )
{
	/* The cast to (char *) in the following accommodates both
	 * implementations that use char* generic pointers, and those
	 * that use void* generic pointers.  It works with the latter
	 * because both ANSI C and C++ allow castless assignment from
	 * any pointer type to void*, and deal with argument conversions
	 * as though doing an assignment.
	 */
	return (void *) realloc( (char *) ptr, size );
}

void yyfree( void *ptr )
{
	free( (char *) ptr ); /* see yyrealloc() for (char *) cast */
}

/*
==============
yyerror
==============
*/
int yyerror( const char *msg )
{
	if ( !yychar )
		CompileError(g_sourcePos, "unexpected end of file found");
	else if ( yychar != 258 )
		CompileError(g_sourcePos, "bad syntax");

	return 0;
}

/*
==============
ScriptParse
==============
*/
void ScriptParse( sval_u *parseData, unsigned char user )
{
	struct yy_buffer_state buffer_state;

	memset(&buffer_state, 0, sizeof(buffer_state));

	g_out_pos = -1;
	g_sourcePos = 0;
	g_parse_user = user;
	g_dummyVal.node = 0;

	yy_init = 1;

	buffer_state.yy_buf_size = YY_BUF_SIZE;
	buffer_state.yy_ch_buf = ch_buf;
	buffer_state.yy_is_our_buffer = 0;

	yy_init_buffer(&buffer_state, 0);

	yyensure_buffer_stack();
	YY_CURRENT_BUFFER_LVALUE = &buffer_state;
	yy_start = 0;
	yy_start = 1 + 2 * 1;

	yyparse();

	*parseData = yaccResult;
}

/*
==============
yywrap
==============
*/
int yywrap()
{
	return 1;
}

// Unreferenced storage; original declarations unknown (sized from the layout).
static int scr_yacc_unreferenced[2];
