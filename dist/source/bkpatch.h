goto_list_t *makelist (code_list_t *goto_node);
goto_list_t *merge (goto_list_t *l1, goto_list_t *l2);
void backpatch (goto_list_t *goto_list, int label);
void backpatch_str (goto_list_t *goto_list, char *label);
