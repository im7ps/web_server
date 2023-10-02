#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int PORT = 8080;

void handleRequest(int clientSocket) 
{
    const char* response = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html\r\n"
                           "\r\n"
                           "<html><body><h1>Hello, World!</h1></body></html>";

    send(clientSocket, response, strlen(response), 0);
}

int main() 
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Errore nel binding del socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 10) == -1) {
        perror("Errore nell'ascolto delle connessioni");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server in ascolto sulla porta " << PORT << std::endl;

    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            perror("Errore nell'accettare la connessione");
            continue;
        }

        std::cout << "Connessione accettata da " << inet_ntoa(clientAddr.sin_addr) << std::endl;

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            std::cout << "Richiesta HTTP ricevuta:\n" << buffer << std::endl;
            handleRequest(clientSocket); // Gestisce la richiesta HTTP
        }

        close(clientSocket);
    }

    close(serverSocket);

    return 0;
}
