
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE_CONFIG 5
#define SIZE_BUF 2048



typedef struct configServer{
    char *id;
    char *filtro;
    int limite;
} ConfigS;
 

// Lê uma linha e coloca em um buf 
ssize_t readln(int fd, char *buf, int sizeBuf){
    size_t res = 0;
    int i = 0;
    while(i< sizeBuf && (res = read(fd,&buf[i],1)) > 0){
        if (buf[i] == '\n'){
            i += res;
            return i;
        }
        i += res;  
    }
    return i;
}

// Faz o carregamento do arquivo para a estrutura configServer
ConfigS* readConfig(int fd){
    char *buf = malloc(sizeof(char)*SIZE_BUF);
    ConfigS *cs = malloc(SIZE_CONFIG * sizeof(struct configServer));
    ssize_t res;
    int i = 0;
    while((res = readln(fd,buf,SIZE_BUF))> 0 && i < 5){
        char*id = strsep(&buf," ");
        cs[i].id = strdup(id);
        char*filtro = strsep(&buf," ");
        cs[i].filtro = strdup(filtro);
        char*limite = strsep(&buf,"\n");
        cs[i].limite = atoi(limite);
        i++;            
    }
    return cs;
}


// Achar o filtro correspondente pelo id que o usuario deu
char *findFilterById(ConfigS *config, char* id){
	char* filtro = NULL;
	int flag = 0;
	int i = 0;
	while(i < SIZE_CONFIG && flag == 0){
		if(!(strcmp(config[i].id,id))){
			filtro = strdup(config[i].filtro);
			flag++;
		}
		i++;
	}
	return filtro;
}

int execOnefilter(char* input_file, char * output_file, char*filtro, char *filtPathByUser){
	char * filterPath = strdup(filtPathByUser);
	strcat(filterPath,filtro);
	pid_t pid;
	int status;
    int input_fd = open(input_file,O_RDONLY);
    if (input_fd < 0){
        perror("input");
		return -1;
    }
    int output_fd = open(output_file,O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (output_fd < 0){
        perror("output");
		return -1;
    }
	if ((pid = fork()) == 0){ //Filho que faz a execução 
    	if(dup2(input_fd,0)){}; // faz cópia do input_fd para o stdin
    	close(input_fd);
    	if(dup2(output_fd,1)){}; // faz cópia do output_fd para o stdout
    	close(output_fd);

    	setbuf(stdout,NULL);
    	execlp(filterPath, filterPath, NULL);
    	perror("erro no exec");
		exit(-1);
	}
	else{ 
		int espera;
		espera = wait(&status);
		if (WIFEXITED(status)){
			if(WEXITSTATUS(status) == -1) return -1;
            printf("processo pid(%d) [realizado com sucesso]\n", espera);
		}	
        else{
            printf("processo pid[%d] deu algum erro\n", espera);
			return -1;
        }

	}
	
    return 0;
}


int execDoisFiltros(char* input_file, char* output_file, char*filtros[], char* filtPathByUser){
	int p[2];
    int status;
	int input_fd;
	char * filtro1, *filtro2; 
	pid_t pids[2];
	pid_t espera;

    if (pipe(p) == -1){
        perror("pipe");
        return -1;
    }
	
	for(int i = 0; i<2; i++){
		
		switch(i){
    	    case 0:
				// aplicação do primeiro filtro no input_file
    	        if((pids[i]=fork()) == 0){
					close(p[0]);
    				input_fd = open(input_file,O_RDONLY);
    				if (input_fd < 0){
    				    perror("input");
    				}
    				dup2(input_fd,0);
    				close(input_fd);


    	        	dup2(p[1],1);
    	        	close(p[1]);

					filtro1 = strdup(filtPathByUser);
					strcat(filtro1,filtros[0]);

    	        	execlp(filtro1,filtro1,NULL);         
    	        	perror("Filtro 1"); 
    	        	_exit(-1);
				}	
				close(p[1]);
				break;

    	    case 1:
				// aplicar o segundo filtro no que foi gerado do filtro1, para gerar o output_file
    	        if((pids[i]=fork()) == 0){

					close(p[1]);
            		dup2(p[0],0);
            		close(p[0]);
    	        	int output_fd = open(output_file,O_CREAT | O_TRUNC | O_WRONLY, 0666);
    	        	if (output_fd < 0){
    	        	    perror("output");
    	        	}
            		dup2(output_fd,1);
					close(output_fd);
					filtro2 = strdup(filtPathByUser);
					strcat(filtro2,filtros[1]);
            		execlp(filtro2,filtro2,NULL);
            		perror("Filtro 2");
					_exit(-1);
				}
				close(p[0]);
				break;
    	}
	}
	for(int i = 0; i<2; i++){
		espera = waitpid(pids[i],&status,0);
		if (WIFEXITED(status)){
			if(WEXITSTATUS(status) == -1) return -1;
            printf("processo pid(%d) [realizado com sucesso]\n", espera);
		}	
        else{
            printf("processo pid[%d] deu algum erro\n", espera);
			return -1;
        }
	}
    return 0;
}

// Fala para o usuário que o pedido está sendo processado
void processing(int fd2, char*myfifo){
	char *arr1 = "processing...\n";
	fd2 = open(myfifo, O_WRONLY);
	if(write(fd2, arr1, strlen(arr1))){};
	close(fd2);
}

// Mensagem de erro caso ocorra algum imprevisto na execução
void errorMsg(int fd2, char*myfifo){
	char *arr1 = "Não foi processado por completo\n";
	fd2 = open(myfifo, O_WRONLY);
	if(write(fd2, arr1, strlen(arr1))){};
	close(fd2);
}

// Fala para o usuário que o pedido já foi processado
void processed(int fd2, char*myfifo, char *output_file){
	char arr1[1024];
	sprintf(arr1, "processed!! Foi gerado o ficheiro %s\n",output_file);
	fd2 = open(myfifo, O_WRONLY);
	if(write(fd2, arr1, strlen(arr1))){};
	close(fd2);
}

// Executar os filtros e gerar o .mp3  
void transform(char *arg, ConfigS *cs, char *filtersPath, int fd2){
	int nfiltros = 0;

	char * myfifo = "/tmp/myfifo";
	processing(fd2,myfifo);
	// Fazer o parse do que leu
	char*input_file = strsep(&arg," ");
	char*output_file = strsep(&arg," ");
	char*filtroAtual = strsep(&arg," ");
	char *filtros[10];
	while(filtroAtual!=NULL){
		filtros[nfiltros++]= findFilterById(cs,filtroAtual); 
		filtroAtual = strsep(&arg," ");
	}

	char *arr1 = "pending...\n";
	fd2 = open(myfifo, O_WRONLY);
	if(write(fd2, arr1, strlen(arr1))){};
	close(fd2);
	switch(nfiltros){  
		case 1:
			if (execOnefilter(input_file,output_file,filtros[0],filtersPath) != -1){
				processed(fd2,myfifo,output_file);
			}
			else{
				errorMsg(fd2,myfifo);
			}
			break;
		case 2:
			if (execDoisFiltros(input_file,output_file,filtros,filtersPath) != -1){
				processed(fd2,myfifo,output_file);
			}
			else{
				errorMsg(fd2,myfifo);
			}
			break;
		default:
			arr1 = "Este número de filtros não está disponível\n";
			fd2 = open(myfifo, O_WRONLY);
			if(write(fd2, arr1, strlen(arr1))){};
			close(fd2);		
	}
	

}

int ocupado = 0;


/* Para terminar o programa graciosamente */

void signal_toQuit(int sig){
	if(ocupado == 1){
		alarm(1);
	}	
	else {
		printf("Encerrando o servidor...\n");
		sleep(2);
		kill(getpid(),SIGTERM);
	}
}


void signal_toWaitQuit(int sig){
	if(ocupado == 1) alarm(1);
	else {
		printf("Encerrando o servidor...\n");
		sleep(2);
		kill(getpid(),SIGTERM);
	}
}


int main(int argc, char const *argv[])
{
	// Declaração de variáveis
	int fd2,bytes_read, configFd,status;
	//char *input_file = malloc(sizeof(char)*SIZE_BUF);
	//char *output_file = malloc(sizeof(char)*SIZE_BUF);
	char *type = malloc(sizeof(char)*SIZE_BUF);
	

	// Standard paths
	char * myfifo = "/tmp/myfifo";
	


	if (argc > 2){
		printf("Press ctrl^\\ to quit\n\n");
		signal(SIGQUIT,signal_toQuit);
		signal(SIGALRM,signal_toWaitQuit);
		/* Carregamento do arquivo de conf do servidor em uma estrutura de dados*/
		if((configFd=open(argv[1],O_RDONLY))== -1){ // abrir o arquivo da configuração do servidor 
            perror("open");
            return -1;
        }
		char *filtersPath = strdup(argv[2]);
        ConfigS *cs = readConfig(configFd); //carregar o arquivo de configuração na struct  
        printf("configurações do server [carregado]\n");
        close(configFd);

		/*Comunicação com o user */
		char *arr2 = malloc(sizeof(char)*SIZE_BUF);
		bzero(arr2,SIZE_BUF);
		//mkfifo(myfifo, 0666);
		fd2 = open(myfifo, O_RDONLY);
		while ((bytes_read = read(fd2, arr2, SIZE_BUF)) > 0){ 
			ocupado=1;
			close(fd2);
			if (fork()==0){
				// Verificar oq leu do usuario
				printf("[user]: %s \n", arr2);
			
				char * aux = strdup(arr2);
				// Fazer o parse do que leu
				type = strsep(&aux," ");


				// verificar o tipo de funcionalidade que o usuário quer
				if(!(strcmp(type,"transform"))){
					ocupado=1; 				
					transform(aux,cs,filtersPath,fd2); // executar os filtros
				}
			}
			else{
				wait(&status);
				ocupado = 0;
				fd2 = open(myfifo, O_RDONLY);
				free(arr2);
				char *arr2 = malloc(sizeof(char)*SIZE_BUF);
				bzero(arr2,SIZE_BUF);	
			}
		}
	}
	
	else{
        printf("Invalid number of instances\n");
    }
	
	
	return 0;
}
