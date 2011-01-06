#define LEXERROR 257
#define FDEF 258
#define identifier 259
#define func_id 260
#define en_var 261
#define param 262
#define ERRORLEVEL 263
#define GE 264
#define EXIST 265
#define EQ 266
#define NE 267
#define number 268
#define empty 269
#define dos_command 270
#define CASE 271
#define DEFAULT 272
#define IF 273
#define SWITCH 274
#define WHILE 275
#define BREAK 276
#define RETURN 277
#define ELSE 278
#define LOG_OR 279
#define LOG_AND 280
typedef union
{
   code_list_t *code_node;
   expr_t *expr_node;
   int integer;
} YYSTYPE;
extern YYSTYPE yylval;
