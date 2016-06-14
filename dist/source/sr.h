/* subroutines */
char is_func (char *sought);
char *find_func (int func_number);
void install_func (char *name);
char add_srcode (char *name, code_list_t *code);
extern int sr_no;
extern int num_sr;
extern char in_sr;
extern code_list_t **srcode;
extern char **srnames;
extern int sr_call_count;

