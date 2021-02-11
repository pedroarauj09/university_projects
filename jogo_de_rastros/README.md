# Desenvolvido por

<a href='http://github.com/pedroarauj09'> Pedro Araujo </a>

<a href='http://github.com/soseiquenadasei00'> Pedro Saldanha  </a>

<a href='http://github.com/VitorLelis'> Vitor Lelis </a>

<br/>
<br/>

# Descrição

Este é o jogo de Rastros. Para descobrir as regras do jogo, abra o <a href='./manualDoJogo.pdf'> Manual Do Jogo  </a>. O programa permite que dois jogadores, partilhando o mesmo teclado, o possam jogar. Os comandos são introduzidos através de um interpretador de comandos.

<br/>
<br/>

# Interpretador de comandos

O programa funciona como um interpretador de comandos. Esta estratégia costuma ser chamada REPL (Read, Evaluate, Print, Loop). O interpretador responde aos seguintes 
comandos:

<br/>

`coordenada`: Tal como nas coordenadas de um tabuleiro de Xadrez: uma letra (a coluna) seguida de um algarismo (a linha). Neste caso, o programa efetua essa jogada desde que ela seja válida.

`gr nome_do_ficheiro` : O programa grava o estado do tabuleiro num ficheiro

`ler nome_do_ficheiro` :O programa lê o estado do tabuleiro a partir do ficheiro

`movs`: O programa deverá imprimir a lista dos movimentos do jogo

`jog` : O rograma escolhe a melhor jogada para o jogador atual

`pos numero_da_jogada` : O programa permite visualizar uma posição anterior através do seu número.

`Q`: O programa acaba

<br/>
<br/>

# Formato do ficheiro

O formato do ficheiro é o seguinte:

- [x] O estado do tabuleiro

- [x] Uma linha em branco

- [x] A lista de movimentos

<br/>
<br/>

# Lista de movimentos

A lista de movimentos é dada por tantas linhas como jogadas. Cada linha começa com o número da jogada (sempre com dois algarismos) seguida dos movimentos de cada jogador. Assim se os jogadores fizeram os seguintes movimentos: d4, e4, e3, a lista de movimentos seria a seguinte:

01: d4 e4

02: e3

# Exemplo completo

Segue um exemplo completo do estado do ficheiro onde foram executados os seguintes comandos:

`d4 e4 e3 f4 f3`

`gravar pos`

A seguir a estes comandos, o conteúdo do ficheiro pos:

```shell
.  .  .  .  .  .  .  2  | 8 |

.  .  .  .  .  .  .  .  | 7 |

.  .  .  .  .  .  .  .  | 6 |

.  .  .  .  #  .  .  .  | 5 |

.  .  .  #  #  #  .  .  | 4 |

.  .  .  .  #  *  .  .  | 3 |

.  .  .  .  .  .  .  .  | 2 |

1  .  .  .  .  .  .  .  | 1 |

------------------------

a  b  c  d  e  f  g  h 

01: d4 e4

02: e3 f4

03: f3
```

# Visualização de posições anteriores
A visualização de posições anteriores será feita conforme o número da jogada, sendo 0 a posição inicial. Usando o exemplo completo da secção anterior, o comando pos 2 mostra o seguinte tabuleiro:

```shell
.  .  .  .  .  .  .  2  | 8 |

.  .  .  .  .  .  .  .  | 7 |

.  .  .  .  .  .  .  .  | 6 |

.  .  .  .  #  .  .  .  | 5 |

.  .  .  #  #  *  .  .  | 4 |

.  .  .  .  #  .  .  .  | 3 |

.  .  .  .  .  .  .  .  | 2 |

1  .  .  .  .  .  .  .  | 1 |

------------------------

a  b  c  d  e  f  g  h 
```
