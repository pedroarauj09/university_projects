import ply.lex as lex

# palavras específicas reservadas do token ID
reserved = {
    'LEX' : 'LEX',
    'literals' : 'LIT',
    'YACC' : 'YAC',
    'tokens' : 'TOK',
    'return': 'RET',
    'ignore': 'IGNORE'
}
 
tokens = ["GRAMM", "ID", "ASPAS2", "ASPAS", "REGEX", "RETVALUE", "TYPE", "TOIGNORE" , "SPACE", "ERROR","FUNC", "ANY", "BEGINEND", "PRECED"] + list(reserved.values())
literals = ['%','[', ']','-','*','=','(',')','+','/', ',','.','{','}',':','§']

# estado criado com o objetivo ler qualquer tipo de caracter ao entrar neste estado 
states = [("readall","exclusive")]


# definição do começo do estado readall, ao encontrar o caracter '@' 
def t_BEGINEND(t):
    r'@'
    t.lexer.begin("readall")

# definição do token PRECED, para identificão do campo precendence 
def t_PRECED(t):
    r'precedence\s=\s\[(.*)\]'
    t.value = t.lexer.lexmatch.group(3)
    return t

# token que lê qualquer sequencia de caracteres desde que não seja @
def t_readall_ANY(t):
    r'[^@]+'
    return t

# definicão da leitura do caracter @ no estado readall, onde volta ao estado inicial
def t_readall_BEGINEND(t):
    r'@'
    t.lexer.begin("INITIAL")

def t_readall_error(t):
    print(f"Illegal character '{t.value[0]}', [{t.lexer.lineno}]",t.lexer.skip(1))

# token GRAMM que identifica a gramática que está entre os caracteres '->' e '=>'
def t_GRAMM(t):
    r'->(\s\w+\s:.*)=>'
    t.value = t.lexer.lexmatch.group(5)
    return t

# token FUNC responsável captar a semântica da gramática 
def t_FUNC(t):
    r'{\s(.*)}'
    t.value = t.lexer.lexmatch.group(7)
    return t

# token ERROR que identifica o campo error(...)
def t_ERROR(t):
    r'error\((.+)\)'
    t.value = t.lexer.lexmatch.group(9)
    return t

# leitura do valor de ignore = 'valor' 
def t_TOIGNORE(t):
    r"\'\s?(\\[ntr])+\'"
    return t

# identificação do t.value 
def t_RETVALUE(t):
    r'[a-z]\.value'
    return t

# identificação de expressões regulares
def t_REGEX(t):
    r"r\'.*\'"    
    return t

# token que do tipo do t.value , podendo ser float ou int
def t_TYPE(t):
    r'(float|int)'
    return t

# token ID que identifica qualquer sequencia textual
def t_ID(t):
    r'[a-zA-Z_]\w*'
    t.type = reserved.get(t.value, 'ID')
    return t

# token que capta o caracter "
def t_ASPAS2(t):
    r'\"'
    return t

# token que capta o caracter '
def t_ASPAS(t):
    r'\''
    return t

# leitura de qualquer espaço que se encontre
def t_SPACE(t):
    r'\s'
    pass


def t_error(t):
    print(f"Illegal character '{t.value[0]}', [{t.lexer.lineno}]",t.lexer.skip(1))

lexer = lex.lex()

