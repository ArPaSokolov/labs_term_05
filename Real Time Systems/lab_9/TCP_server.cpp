#include <iostream>
#include <WS2tcpip.h> // библиотека сокетов

// Подключение библиотеки на этапе компановки
#pragma comment (lib, "ws2_32.lib")

// TCP сервер
int main()
{
    // Инициализация winsock
    WSADATA data;

    int wsOk = WSAStartup(MAKEWORD(2, 2), &data); // запуск
    if (wsOk == 0) {
        std::cout << "Winsock started!" << std::endl;
    } else {
        std::cerr << "Can't start winsock, Err #" << wsOk << " Quitting..." << std::endl;
        WSACleanup();
        return 1;
    }

    // Создание сокета
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        std::cerr << "Can't create a socket, Err #" << WSAGetLastError() << " Quitting..." << std::endl;
        WSACleanup();
        return 1;
    }

    // Биндим IP и порт c сокетом
    sockaddr_in serverHint;
    serverHint.sin_family = AF_INET; // задаем формат адресов IPv4
    serverHint.sin_port = htons(54000); // порт
    serverHint.sin_addr.S_un.S_addr = INADDR_ANY; // любой доступный IP на машине

    bind(listening, (sockaddr*)&serverHint, sizeof(serverHint));
    
    // Настройка сокета для прослушивания
    listen(listening, SOMAXCONN);
   
    // Ожидание подключения
    sockaddr_in client;
    int clientLength = sizeof(client);

    SOCKET clientSocket =  accept(listening, (sockaddr*)&client, &clientLength);

    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Can't connect to client, Err #" << WSAGetLastError() << " Quitting..." << std::endl;
        closesocket(listening);
        WSACleanup();
        return 1;
    }

    char host[NI_MAXHOST]; // имя клиента
    char service[NI_MAXHOST]; // порт подключения клиента

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXHOST);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
        std::cout << host << " connection on port " << service << std::endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connection on port " << ntohs(client.sin_port) << std::endl;
    }

    closesocket(listening);

    // Запуск сервера (жизненный цикл)
    char buf[1024];

    std::cout << "Server is listening..." << std::endl;
    while (true) {
        // Очистка временной памяти
        ZeroMemory(buf, 1024);

        // Получение данных от клиента
        int bytesIn = recv(clientSocket, buf, 1024, 0);

        
        if (bytesIn == 0) {
            std::cerr << "Client disconnected!" << std::endl;
            break;
        } 

        if (bytesIn == SOCKET_ERROR) {
            std::cerr << "Can't receive message, Err #" << WSAGetLastError() << std::endl;
            break;
        } 

        // Отправка полученного сообщения обратно клиенту (эхо)
        send(clientSocket, buf, bytesIn + 1, 0);
        std::cout << "Message from client: " << buf << std::endl;

        // Условие выхода из цикла сервера
        if (std::string(buf) == "kill") {
            break;
        }
    }
    
    std::cout << "Quitting..." << std::endl;
    
    // Закрываем socket для прослушивания
    closesocket(clientSocket);
    // Отключаем winsock
    WSACleanup();

    return 0;
}
