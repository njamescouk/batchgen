parser grammar batchgen;

batch_file : statement_list ;

statement : 'dos_command'
            | compound_statement
            | selection_statement
            | while_statement
            | labelled_statement
            | jump_statement
            | function_definition
            | function_call
            | 'error' ;

 
function_definition : 'FDEF' 'identifier' '(' ')' compound_statement ;

function_call : function_identifier '(' ')' ;

labelled_statement : 'CASE' primary_expression ':' statement
                     | 'DEFAULT' ':' statement ;

compound_statement : '{' statement_list '}'
                     | '{' '}' ;

statement_list : statement
                 | statement statement_list ;

selection_statement : 'IF' '(' dos_expression ')' statement
                      | 'IF' '(' dos_expression ')' statement 'ELSE' statement 
                      | 'SWITCH' '(' primary_expression ')' statement ;


while_statement : 'WHILE' '(' dos_expression ')' statement ;

jump_statement : 'BREAK' ';'
                 | 'RETURN' ';'
                 | 'RETURN' primary_expression ';' ;

dos_expression : logical_AND_expression
                 | logical_AND_expression 'LOG_OR' dos_expression ;

logical_AND_expression : unary_expression
                         | unary_expression 'LOG_AND' logical_AND_expression ;

unary_expression : dos_logical_expression
                   | '(' dos_expression ')'
                   | '!' unary_expression ;
                   
dos_logical_expression : 'ERRORLEVEL' 'GE' primary_expression
                         | 'ERRORLEVEL' '<' primary_expression
                         | 'ERRORLEVEL' 'EQ' primary_expression
                         | 'ERRORLEVEL' 'NE' primary_expression
                         | 'EXIST' primary_expression
                         | primary_expression 'EQ' primary_expression
                         | primary_expression 'NE' primary_expression ;

primary_expression : 'identifier'
                     | 'identifier' primary_expression
                     | 'en_var'
                     | 'en_var' primary_expression
                     | 'param'
                     |  'param'primary_expression
                     | 'number'
                     | 'number' primary_expression
                     | 'empty' ;

function_identifier : 'func_id' ;


