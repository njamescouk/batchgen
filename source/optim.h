#define PEEPSZ 5
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
char optimize (char **ca);
char optimize_line (char **ca, int lin);
char get_labels (char **ca);
char install_def (char *str);
char install_ref (char *str);
int find_label (char *str);
char del_unrefd_labs (char *name, char **ca);
void print_ca (char **ca, FILE *fp);
char *find_word (char *str, char *word);
char is_branch (char *str);
char is_call (char *str);
char is_uncond_br (char *str);
char is_label (char *str);
void del_line (char **ca, int line_no);
char *get_label_ref (char *str);
char *get_label_def (char *str);
char negate (char **str);
char is_cond_br (char *str);
char is_rem (char *str);
char is_blank (char *str);
char reref_labs (char **ca, char *newlab, char *oldlab);
char check_labels (void);
int cn_count (code_list_t *code);
char is_esr (char *lab);
