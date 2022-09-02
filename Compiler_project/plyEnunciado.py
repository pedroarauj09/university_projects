import ply.lex as lex

literals = ["+","-","=","/","*","(",")"]
tokens = ["VAR","NUMBER"]
t_ignore = ' \t\n'
def t_VAR(t):
	r'[a-zA-Z_][a-zA-Z0-9_]*'
	return t

def t_NUMBER(t):
	r'\d+(\.\d+)?'
	t.value = float(t.value)
	return t

def t_error(t):
	print(f"Illegal character '{t.value[0]}', [{t.lexer.lineno}]",t.lexer.skip(1))


lexer = lex.lex()

import ply.yacc as yacc

precedence = [
	('left','+','-'),
	('left','*','/'),
	('right','UMINUS')
]

def p_atrib(t):
	" stat : VAR '=' exp "
	t.y.ts[t[1]] = t[3] 


def p_statExp(t):
	" stat : exp "
	print(t[1]) 


def p_plus(t):
	" exp : exp '+' exp "
	t[0] = t[1] + t[3] 


def p_minus(t):
	" exp : exp '-' exp "
	t[0] = t[1] - t[3] 


def p_mult(t):
	" exp : exp '*' exp "
	t[0] = t[1] * t[3] 


def p_div(t):
	" exp : exp '/' exp "
	t[0] = t[1] / t[3] 


def p_uminus(t):
	" exp : '-' exp %prec UMINUS "
	t[0] = -t[2] 


def p_expPar(t):
	" exp : '(' exp ')' "
	t[0] = t[2] 


def p_expNumber(t):
	" exp : NUMBER "
	t[0] = t[1] 


def p_expVAR(t):
	" exp : VAR "
	t[0] = getval(t[1]) 


def p_error(t):
	print(f"Illegal character '{t.value[0]}', [{t.lexer.lineno}]",t.lexer.skip(1))

def getval(n):
    if n not in y.ts: 
        print(f"Undefined name '{n}'")
    return y.ts.get(n,0)

y=yacc.yacc()
y.ts = {}
y.parse("3*5+4*7")

