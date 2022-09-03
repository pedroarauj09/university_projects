import ply.yacc as yacc

from lexer import tokens, literals

def p_parserLex(p):
    "parser : lex yacc"
    p[0] = p[1] + p[2]


def p_lex_inicio(p):
    "lex : '%' '%' LEX lexStats lexDefs"
    p[0] = "import ply.lex as lex\n\n" + p[4] + p[5]

def p_lexStatements(p):
    "lexStats : lexStats lexStat"
    p[0] = p[1] + p[2] 

def p_lexStatements_one(p):
    "lexStats : lexStat"
    p[0] = p[1]


def p_lexStatement_literals(p):
    "lexStat : LIT '=' '§' simbols '§' "
    p[0] =  p[1] + " = [" +  p[4] + "]\n"


def p_lexStatement_tokens(p):
    "lexStat : TOK '=' '[' tokens ']' "
    p[0] =  p[1] + " = [" +  p[4] + "]\n"

def p_lexStatement_ignore(p):
    "lexStat : IGNORE '=' TOIGNORE "
    p[0] = "t_ignore = " + p[3] + "\n"

def p_simbols(p):
    "simbols :  simbols simbol "
    p[0] = p[1] + "," + p[2]

def p_simbols_one(p):
    "simbols : simbol" 
    p[0] = p[1]

def p_simbol_mais(p):
    "simbol : '+' "
    p[0] = "\"+\"" 

def p_simbol_menos(p):
    "simbol : '-' "
    p[0] = "\"-\""

def p_simbol_igual(p):
    "simbol : '=' "
    p[0] = "\"=\""

def p_simbol_bar(p):
    "simbol : '/' "
    p[0] = "\"/\""

def p_simbol_asterisc(p):
    "simbol : '*' "
    p[0] = "\"*\""

def p_simbol_pa(p):
    "simbol : '(' "
    p[0] = "\"(\""

def p_simbol_pf(p):
    "simbol : ')' "
    p[0] = "\")\""

def p_simbol_ca(p):
    "simbol : '[' "
    p[0] = "\"[\""

def p_simbol_cf(p):
    "simbol : ']' "
    p[0] = "\"]\""



def p_tokens_single(p):
    "tokens : token"
    p[0] = p[1]

def p_tokens_varios(p):
    "tokens : tokens ',' token"
    p[0] = p[1] + p[2] + p[3]

def p_token(p):
    "token : ASPAS ID ASPAS"
    p[0] = '"' + p[2] + '"'
    parser.tokensList.append(p[2])

def p_lex_defs(p):
    "lexDefs : lexDefs lexDef"
    p[0] = p[1] + p[2]

def p_lex_defs_one(p):
    "lexDefs : lexDef"
    p[0] = p[1] 

def p_lex_def(p):
    "lexDef : REGEX RET '(' ASPAS2 ID ASPAS2 ',' valueRet ')' "
    if p[5] in parser.tokensList:
        result = "def t_" + p[5] + "(t):\n\t" + p[1] + "\n"
        if p[8] != "t.value":
             result+= "\tt.value = " + p[8] + "(t.value)\n"
        p[0] = result + "\treturn t\n\n"     
    else:
        print(f"(error) token '{p[5]}' não definido\n")
        p.parser.error = True

def p_lex_def_error(p):
    "lexDef : ERROR"
    p[0] = "def t_error(t):\n\tprint(" + p[1] + ")\n\n" 

def p_lex_valueret_simple(p):
    "valueRet :  RETVALUE "
    p[0] = "t.value"

def p_lex_withType(p):
    "valueRet :  TYPE '(' RETVALUE ')' "
    p[0] = p[1]



def p_yacc(p):
    "yacc : '%' '%' YAC precedence yaccGram yaccFim"
    p[0] = "\nlexer = lex.lex()\n\nimport ply.yacc as yacc\n\n" + p[4] + p[5] + p[6]

def p_precedence(p):
    "precedence : PRECED"
    values = p[1].split(',(')
    i = 1
    length = len(values)
    res = "precedence = [\n"
    for value in values:
        res = res + "\t"
        if i != 1 : 
            res = res + "("
        res = res + value    
        if i != length:
            res = res + ","
        res = res + "\n" 
        i = i + 1 
    p[0] = res + "]\n"

    
def p_no_precedence(p):
    "precedence : "
    p[0] = ""


def p_yaccGram_one(p):
    "yaccGram : yaccStat"
    p[0] = p[1]

def p_yaccGram_stats(p):
    "yaccGram : yaccGram yaccStat"
    p[0] = p[1] + p[2]

def p_yaccGram_stat(p):
    " yaccStat : ID GRAMM FUNC"
    p[0] = "\ndef p_" + p[1] + "(t):\n\t" + '"' + p[2] + '"\n\t' + p[3] +"\n\n"

def p_yaccGram_stat_error(p):
    "yaccStat : ERROR"
    p[0] = "\ndef p_error(t):\n\tprint(" + p[1] + ")\n"

def p_yaccFim(p):
    "yaccFim : ANY"
    p[0] = p[1]

    

def p_error(p):
    print("Sytax error: ", p)
    parser.success = False


parser = yacc.yacc()
# lista , para salvar os tokens lidos para depois verificar autenticar a validação de um token
parser.tokensList = []

parser.success = True

import sys
xdoc = sys.stdin.read()
result = parser.parse(xdoc)
print(result)


if parser.success == False:
    print("?$& Documento XML mal formado &$?")
