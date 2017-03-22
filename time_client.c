#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define TIME_SERVER "223.195.16.37" //접속할 서버의 IP
#define TIME_PORT 5010 //해당 서버의 포트번호 

void main(){
        int sock; 
        struct sockaddr_in server; //인터넷 주소 체계를 지원하는 sockaddr_in 구조체의 이름을 server로 선언한다. 
        char buf[256];

        /* socket(int domain, int type, int protocol)
        인터넷 주소 체계를 지원하는 소켓을 만들고(AF_INET), 이 소켓이 연결형 서비스(TCP)임을 표기한 후(SOCK_STREAM)
        해당 소켓의 디스크립터를 반환한다)*/
        if ((sock = socket(AF_INET, SOCK_STREAM, 0))<0)
        {
                printf("Socket failed. \n"); //예외처리 
                exit(1);
        }

        memset(&server, 0, sizeof(server)); //소켓의 크기만큼 메모리를 확보 및 초기화해준다. 

        server.sin_family = AF_INET; //주소체계 구분(인터넷 주소체계)
        server.sin_port = htons(TIME_PORT); //포트 번호 

        /* connect(int s,const struct sockaddr *name, socklent_t namelen)
        server와 연결 설정을 시도한다. 해당 주소의 서버가 존재하지 않으면 오류 처리되고, 서버가 연결 대기중이면 연결이 설정된다 */
        if (connect(sock, (struct sockaddr *)&server, sizeof(server))<0)
        {
                printf("Error in connection failed. \n"); //예외처리 
                exit(1);
        }
        else   {
                printf("Connected \n");
        }

        /* recv(int s, void *buf, size_t len, int flags)
        연결형 서비스에서 데이터를 수신하는 역할을 한다. sock를 통해 데이터를 수신하고. 수신한 데이터를 buf에 보관한다*/
        if (recv(sock, buf, sizeof(buf), 0)==-1) //예외처리 
                exit(1);
        printf("Time information from server is %s", buf); //내용 출력 
        close(sock);
}
