
<div align='center'>

<h1> Projeto Aurras : Processamento de ficheiros de áudio
<hr/>    

<a href='#desc'> DESCRIÇÃO DAS PASTAS </a> &nbsp;&nbsp;|&nbsp;&nbsp;
<a href='#about'> SOBRE O PROJETO </a> &nbsp;&nbsp;|&nbsp;&nbsp;
<a href='#tools'> FUNCIONALIDADES </a> &nbsp;&nbsp;|&nbsp;&nbsp;
<a href='#comps'> COMPETÊNCIAS ENVOLVIDAS </a> &nbsp;&nbsp;
</div>

<hr/>
<br/>
<br/>

# <p id='desc'> Descrição das pastas </p>

Segue-se uma breve descrição das pastas relativas ao processo de compilação e linkagem do projecto: <br/>

    src/ : contém o código-fonte do vosso projecto; 
    obj/ : contém o código-objecto resultante da compilação do código-fonte.;
    bin/ : contém os executáveis resultantes da "linkagem" do código-objecto; 

Nessa estrutura pode encontrar ainda as seguintes pastas: <br/>

    etc/ : contém o(s) ficheiro(s) de configuração do servidor (o ficheiro "aurrasd.conf" apresenta um exemplo de configuração); 
    bin/aurrasd-filters : contém programas executáveis para Linux (e Mac) que funcionam como filtros de áudio (recebem o conteúdo de ficheiros de áudio (em qualquer formato)
    pelo seu standard input e produzem o conteúdo de um ficheiro de áudio (no formato MP3) no seu standard output; 
    samples/ : contém ficheiros de áudio que pode usar para testar a execução dos filtros disponibilizados e para testar o correcto funcionamento do serviço a desenvolver; 
    tmp/ : pasta de ficheiros temporários, irrelevantes para a avaliação do trabalho, ou que tenha necessidade de gerar durante a execução do serviço a desenvolver. 

<br/>

# <p id='about'> 🔎 Sobre o projeto </p>

Consiste em uma aplicação que processa ficheiros de áudio tranformando-os , através de filtros , em outro ficheiro mp3, utilizando recursos como pipes.

<br/>
    
# <p id='tools'>⚙ Funcionalidades </p>

A aplicação deve correr paralelamente dois programas:

<br/>

## User (Aurras)


&rarr; Responsável por indicar o ficheiro a ser processado, filtros a serem aplicados e o ficheiro final.

&rarr; Os pedidos podem ser feitos paralelos porém executa sequencialmente.

&rarr; Possível de se aplicar no máximo 2 filtros.

&rarr; O código fonte de desenvolvimento está <a href='./projeto/src/aurras.c'> aqui <a/>

<h4>Exemplo de execução:</h4>


bash$ ./aurras  transform input-filename output-filename filter-id-1 filter-id-2 

Exemplo concreto:

$ ./aurras transform samples/sample-1.m4a output.m4a alto eco rapido

<br/>
<br/>

## Servidor (Aurrasd)


&rarr; Responsável por receber os requisitos do usário e aplicar os filtros por meio de pipelines

&rarr; O código fonte de desenvolvimento está <a href='./projeto/src/aurrasd.c'> aqui <a/>


<h4>Exemplo de execução:</h4>

$ ./aurrasd config-filename filters-folder

Por exemplo,

$ ./aurrasd etc/aurrasd.conf bin/aurras-filters

<br/>
<br/>


# <p id='comps'>📚 Competências presente no projeto </p>    

- [x] Pipes com nomes: para comunicação entre servidor e usuário 
- [x] Pipes anônimos: para execução de filtros 
- [x] Forks: para execução paralela e geração de diferentes processos
- [x] Tratamento de sinais: para uma saída graciosa do programa
        
    
