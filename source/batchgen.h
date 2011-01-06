struct code_list
{
   char *code;
   struct code_list *next;
   struct goto_list *gotos;
};

typedef struct code_list code_list_t;

struct goto_list
{
   char **labelptr;
   struct goto_list *next;
};

typedef struct goto_list goto_list_t;


struct expr
{
    code_list_t *expr_code;
    goto_list_t *truelist;
    goto_list_t *falselist;
};

typedef struct expr expr_t;

#define TEXTLEN 200
#define LAB_PFX "L_"
#define END_CASE_PFX "EC"
#define END_SWITCH_PFX "ES"
#define ENDIF_PFX "EI"
#define ELSE_PFX "LS"
#define IF_PFX "IF"
#define WHILE_PFX "WH"
#define ENDWHILE_PFX "EW"
#define WHILE_BODY_PFX "WB"
#define OR_FALSE_PFX "ORF"
#define AND_TRUE_PFX "AT"
#define SR_PFX "SR"
#define END_SR_PFX "ESR"
/*#define END_SR_STMT "goto RET_LABEL\n"*/
#define RET_LABEL "_ret_label"
#define END_LABEL "batch_end"
#define DUD_FILE_LABEL "dud_file"

extern char optflag;
extern code_list_t *cl;

int yyparse (void);
int yylex (void);
code_list_t *new_code_node (void);
char add_string (code_list_t *node, char *string);
char add_text (expr_t *node, char *string);
code_list_t *code_join (int n, ...);
expr_t *new_expr (void);
code_list_t *make_expr_code (char *text, expr_t *expr);
void emit (code_list_t *c1, FILE *fp);
char concat_text (expr_t *n1, expr_t *n2);
 
