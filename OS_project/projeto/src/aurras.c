
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Tratamento de sinal para sair graciosamente
void signal_toQuit(int sig){
		
		printf("Saindo...\n");
		sleep(2);
		kill(getpid(),SIGTERM);
}


int main(int argc, char const *argv[])
{
	int argsTot, argAtual;
    argsTot = argc - 1;
    argAtual = 1;
	int fd1;
	// FIFO file path
	char * myfifo = "/tmp/myfifo";
    if(argsTot > 3 && (!(strcmp(argv[argAtual],"transform")))){
		//Criação do pipe
		mkfifo(myfifo, 0666);

		printf("Press ctrl^\\ to quit\n\n");
		signal(SIGQUIT,signal_toQuit);
		fd1 = open(myfifo,O_WRONLY);
        while(argAtual < argsTot){ // escrita na pipe os args que o user passou
          if(write(fd1,argv[argAtual],strlen(argv[argAtual]))){};
          argAtual++;
          if(write(fd1," ",1)){};
        }
        if(write(fd1,argv[argAtual],strlen(argv[argAtual]))){};
		close(fd1);
		
		/* Respostas do Servidor*/
    	char *str1 = malloc(sizeof(char)*2048);
    	bzero(str1,2048);
		fd1 = open(myfifo,O_RDONLY);
		while ((read(fd1, str1, 2048))>0)
		{	
			printf("[server]: %s\n", str1);
			close(fd1);
    	    free(str1);
			char *str1 = malloc(sizeof(char)*2048);
    		bzero(str1,2048);
			fd1 = open(myfifo,O_RDONLY);
		}
	}
	return 0;
}
