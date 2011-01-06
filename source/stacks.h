void stack_init (void);
void wpush (code_list_t *item);
void spush (code_list_t *item);
code_list_t **more_whiles (void);
code_list_t **more_switches (void);
code_list_t *wpop (void);
code_list_t *spop (void);
int inwhile (void);
int inswitch (void);
code_list_t *to_ws (void);
code_list_t *to_ss (void);
char *more_chars (void);
void wawi_push (char item);
char *wawi_pop (void);
char to_wawi_stk (void);
code_list_t *top_cur_stk (void);



