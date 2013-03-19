#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include "test.pb.h"

using namespace std;

int main()
{	
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in svraddr;
	bzero(&svraddr, sizeof svraddr);
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(7000);
	svraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(fd, (struct sockaddr*)&svraddr, sizeof(svraddr))<0)
	{
		cout<<strerror(errno)<<endl;
		exit(1);
	}
	char buf[1024] = "give me some info";
	int nw = write(fd,buf,strlen(buf) );
	int n =0;
	int nr = read(fd,buf,1024 );
	while(nr > 0 )
	{
		n += nr;
		nr = read(fd, buf ,1024- n );
	}
	SearchRequest r;
	cout<<r.ParseFromArray(buf, 1024)<<" "<<n<<" "<<nw<<endl;
	cout<<r.query()<<" "<<r.page_number()<<" "<<r.result_per_page()<<endl;
	return 0;
}
