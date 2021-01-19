

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <string>
#include <iostream>
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buf[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    std::cout<<"Welcome Client!"<<std::endl;



    std::string userinput;
    
    do{
    

        std::cout<<"Redy-> ";
        getline(std::cin,userinput);
        //send to server
        int sendToServer = send(sock, userinput.c_str() ,userinput.size(), 0);
        if(sendToServer==-1)
        {
            std::cout<<"could not send to server"<<std::endl;
        }


        //wait for response
        memset(buf,0,1024);
        int tobyte = recv(sock,buf,1024,0);

        std::cout<<"Server response-> ( "<<std::string(buf,tobyte)<<" )"<<std::endl;




        
    } while (true);
    

    close(sock);

    return 0; 
}
