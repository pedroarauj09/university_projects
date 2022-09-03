import sys
import lexer as l

doc = sys.stdin.read()
l.lexer.input(doc)
for tok in l.lexer:
    print(tok)