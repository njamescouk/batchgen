#define LEXERROR 257
#define FDEF 258
#define identifier 259
#define en_var 260
#define param 261
#define ERRORLEVEL 262
#define GE 263
#define EXIST 264
#define EQ 265
#define NE 266
#define number 267
#define empty 268
#define dos_command 269
#define CASE 270
#define DEFAULT 271
#define IF 272
#define SWITCH 273
#define WHILE 274
#define BREAK 275
#define RETURN 276
#define ELSE 277
#define LOG_OR 278
#define LOG_AND 279
typedef union
{
   code_list_t *code_node;
   expr_t *expr_node;
   int integer;
} YYSTYPE;
extern YYSTYPE yylval;
