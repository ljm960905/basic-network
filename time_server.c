#include <sys/types.h> 
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

    /* socket(int domain, int type, int protocol)
    인터넷 주소 체계를 지원하는 소켓을 만들고(AF_INET), 이 소켓이 연결형 서비스(TCP)임을 표기한 후(SOCK_STREAM)
    해당 소켓의 디스크립터를 반환한다)*/
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) //예외처리 
		exit(1);
	
	server.sin_family = AF_INET; //주소체계 구분(인터넷 주소체계)
	server.sin_addr.s_addr = htonl(INADDR_ANY); //IP주소 
	server.sin_port = htons(TIME_PORT); //포트번호 

	/* bind(int s, const struct sockaddr *name, socklen_t *namelen) 
	sock에 주소를 부여한다. 두 번째 인자는 바인드될 소켓의 주소값이다 */
	if (bind(sock, (struct sockaddr *)&server, sizeof(server))) //예외처리
		exit(1);

	/* listen(int s, int backlog) 
	sock을 활성화하고, 이는 보통 서버 프로세스에서 실행된다, 시스템에서 연결을 거부하지 않고 대기할 수 있는 연결 설정 요구의 최대 수는 5 이다.*/
	if (listen(sock, 5)) //예외처리
		exit(1);

	/* accept(int s, struct sockaddr *addr, socklen_t *addrlen)
	sock에서 클라이언트의 연결 요구가 들어올 때까지 대기한다. 
	임의의 클라이언트로부터 연결 설정요구가 발생하면 둘 사이에 연결이 설정되고, 서버에 새로운 소켓이 생성된다.
	만약 클라이언트의 연결 설정요구가 없으면 서버는 accept()함수에서 대기한다. 
	sock2는 새로 생성된 소켓의 디스크립터를 담는 공간이다*/
	while(1){
		if ((sock2 = accept(sock, (struct sockaddr *)&client, &len)) == -1) //예외처리
			exit(1); 
	time(&today); 

	/* ctime (const time_t *timer)
	time_t형 변수인 today를 읽어들여 지역 시간에 맞추어 "날짜, 월, 요일, 현재시간, 현재년도 + 개행 및 NULL값"으로 바꿔준다.*/
	strcpy(buf, ctime(&today));

	/* send(int s, const void *msg, size_t len, int flags)
	연결형 서비스를 제공하는 환경에서 데이터를 전송하는 역할을 한다. sock2를 통해 상대방 프로세스에 buf에 보관된 데이터를 전송한다. */
	send(sock2, buf, strlen(buf) + 1, 0);
	close(sock2);
     }
}
