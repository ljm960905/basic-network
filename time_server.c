#include <sys/types.h> // 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#define TIME_PORT 5010

void main(){
	int sock, sock2;
	struct sockaddr_in server, client;
	int len;
	char buf[256];
	time_t today;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		exit(1);
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(TIME_PORT);

	if (bind(sock, (struct sockaddr *)&server, sizeof(server)))
		exit(1);

	if (listen(sock, 5))
		exit(1);

	while(1){
		if ((sock2 = accept(sock, (struct sockaddr *)&client, &len)) == -1)
			exit(1);
	time(&today);
	strcpy(buf, ctime(&today));
	send(sock2, buf, strlen(buf) + 1, 0);
	close(sock2);
     }
}
