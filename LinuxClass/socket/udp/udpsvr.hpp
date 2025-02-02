#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
using namespace std;

class udpsvr{
public:
    udpsvr(){sock=-1;}
    ~udpsvr(){}
    bool _creat(){
      sock=socket(AF_INET,SOCK_DGRAM,17);
      if(sock < 0){
        perror("socket creat failed");
        return false;
      }
      return true;
    }
    
    bool _bind(string& ip,uint16_t port){
      struct sockaddr_in addr;
      addr.sin_family=AF_INET;
      addr.sin_port=htons(port);
      addr.sin_addr.s_addr=inet_addr(ip.c_str());
      int ret=bind(sock,(struct sockaddr*)&addr,sizeof(addr));
      if(ret < 0){
        perror("bind error");
        return false;
      }
      return true;
    }
    
    bool _send(string& buff,struct sockaddr_in * aimaddr){
      int send_size=sendto(sock,buff.c_str(),buff.length(),0,(struct sockaddr*)aimaddr,sizeof(struct sockaddr_in));
      if(send_size < 0){
        perror("send failed");
        return false;
      }
      return true;
    }

    bool _recv(string& buff,struct sockaddr_in* comaddr){
      socklen_t leng=sizeof(struct sockaddr_in);
      char tmp[1024]={0};
      int recv_size=recvfrom(sock,tmp,sizeof(tmp),0,(struct sockaddr*)comaddr,&leng);
      if(recv_size < 0){
        perror("recv failed");
        return false;
      }
      buff.assign(tmp,recv_size);
      return true;
    }

    bool _close(){
      if(close(sock)==0){
        return true;
      }
      return false;
    }

private:
    size_t sock;
};
