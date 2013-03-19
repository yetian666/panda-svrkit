#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "test.pb.h"

using namespace std;

int main(int argc, char** argv)
{
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in svraddr;
	bzero(&svraddr, sizeof(struct sockaddr_in));
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(7000);
	svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(listenfd,(struct sockaddr*)&svraddr, sizeof(struct sockaddr));

	listen(listenfd,10);	
	
	while(1)
	{	
		int fd = accept(listenfd, NULL, 0);
		char buf[1024];
		int nr = read(fd, buf, 1024);
		if( nr < 0 )
		{
			cout<<strerror(errno)<<endl;
			continue;
		}
		cout<<buf<<endl;
		SearchRequest r;
		r.set_page_number(3);
		r.set_query("test ok");
		int needw = r.SerializeToArray(buf, 1024);

		cout<<"Serialize size:"<<needw<<endl;
		if( write(fd, buf, r.ByteSize()) > 0)
		cout<<"write ok"<<endl;
		close(fd);
	}
	return 0;
}
