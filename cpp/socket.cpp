//g++ --std=gnu++17 socket.cpp -o socket.exe

#include "libraries.cpp"
#include "helpers.cpp"
#include "calculator.cpp"

int main()
{  
   while(true) {
      int s;
      int optval;
      socklen_t optlen = sizeof(optval);

      if((s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
         perror("Error with socket()");
         exit(EXIT_FAILURE);
      }

      int enable = 1;
      if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
         perror("Error with setsockopt(SO_REUSEADDR)");
         exit(EXIT_FAILURE);
      }

      sockaddr_in sockaddr;
      sockaddr.sin_family = AF_INET;
      sockaddr.sin_addr.s_addr = INADDR_ANY;
      sockaddr.sin_port = htons(4000); 

      if (bind(s, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
         std::cout << "Error with bind to port, errno = " << errno << std::endl;
         exit(EXIT_FAILURE);
      }

      if (listen(s, 10) < 0) {
         std::cout << "Failed to listen on socket, errno = " << errno << std::endl;
         exit(EXIT_FAILURE);
      }

      auto addrlen = sizeof(sockaddr);
      int connection = accept(s, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
      if (connection < 0) {
         std::cout << "Failed to find connection. errno: " << errno << std::endl;
         exit(EXIT_FAILURE);
      }

      // Read from the connection
      int buflen = 10000;
      char *buffer = new char [buflen];
      auto bytesRead = read(connection, buffer, buflen+2);
      Subject subject = parseRequest(removeHeaders(buffer, buflen));
      delete [] buffer;

      //sending response
      std::string headers = "HTTP/1.1 200 OK\r\n" 
                            "Connection: keep-alive\r\n"
                            "Content-Type: text/html\r\n"
                            "\r\n";
      send(connection, headers.c_str(), headers.size(), 0);

      std::string res = std::to_string(get_tax(subject));
      send(connection, res.c_str(), res.size(), 0);
      close(connection);
      close(s);
   }

}