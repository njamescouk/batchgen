#define PEEPSZ 3
#define TMPFNAM "bgo.tmp"

struct label_details
{
   char *label;
   char refd;
   char defd;
};

typedef struct label_details label_detail_t;

extern char remove_rems;
extern char remove_blanks;

char **copy_lines (code_list_t *code);
int list_line_count (code_list_t *cl);
char next_char (void);
char install_def (char *str);
char install_ref (char *str);
int find_label (char *str);
char del_unrefd_labs (char *name, char **ca);
void print_ca (char **ca, FILE *fp);
char *find_word (char *str, char *word);
char is_branch (char *str);
char is_uncond_br (char *str);
char is_label (char *str);
char *get_label_ref (char *str);
char *get_label_def (char *str);
char negate (char *str);
char is_cond_br (char *str);
char is_rem (char *str);
char is_blank (char *str);
char check_labels (void);
int cn_count (code_list_t *code);
char is_esr (char *lab);
char F_optimize (void);
char F_get_labels (void);
void F_del_line (int line_no);
char F_reref_labs (char *newlab, char *oldlab);
int F_remove_blanks (void);
int F_remove_rems (void);
int F_line_count (char *fname);
char F_del_unrefd_labs (char *name);
char next_peep(char peep [PEEPSZ][TEXTLEN], int *end_of_file_head);
char dead_code (int i, int valid_lines, int page);
char redund_goto (int i);
char jump_over_jump (int i);
char lablabjmpjmp (int i);
