import ply.lex as lex

literals = ["[","]","(",")"]
tokens = ["texto"]
t_ignore = ' \t\n'
def t_texto(t):
	r'\"[^"]+\"'
	return t

def t_error(t):
	print(f"Illegal character '{t.value[0]}', [{t.lexer.lineno}]",t.lexer.skip(1))


lexer = lex.lex()

import ply.yacc as yacc


def p_dir_pasta(t):
	" Dir : '(' texto Conteudo ')' "
	t[0] = [f"mkdir {t[2]}", f"cd {t[2]}"] + t[3] + ["cd .."] 


def p_dir_ficheiro(t):
	" Dir : Ficheiro "
	t[0] = [t[1]] 


def p_conteudo(t):
	" Conteudo : Conteudo Dir "
	t[0] = t[1] + t[2] 


def p_conteudo_empty(t):
	" Conteudo :  "
	t[0] = [] 


def p_ficheiro(t):
	" Ficheiro : '[' texto texto ']' "
	t[0] = f"cp {t[3]} {t[2]}" 


def p_error(t):
	print('Erro sintático: ', t)


# Build the parser
parser = yacc.yacc()
# Definir o estado
parser.registos = {}

# Read line from input and parse it
import sys
xdoc = sys.stdin.read()
result = parser.parse(xdoc)
print(result)


