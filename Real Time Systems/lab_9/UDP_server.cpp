#include <iostream>
#include <WS2tcpip.h> // библиотека сокетов

// Подключение библиотеки на этапе компановки
#pragma comment (lib, "ws2_32.lib")

// Cервер
int main()
{
    // Инициализация WINSOCK
    WSADATA data;

    int wsOk = WSAStartup(MAKEWORD(2, 2), &data); // запуск
    if (wsOk == 0) {
        std::cout << "Winsock started! " << std::endl;
    } else {
        std::cout << "Can't start Winsock " << wsOk << std::endl;
        return 1;
    }

    // Передача данных в виде отдельных сообщений
    SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);

    // Подсказка запроса
    sockaddr_in serverHint;

    serverHint.sin_addr.S_un.S_addr = INADDR_ANY; // любой доступный IP на машине
    serverHint.sin_family = AF_INET; // задаем формат адресов IPv4
    serverHint.sin_port = htons(54000); // порт

    // Биндим сокет с IP и порт
    if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR) {
        std::cout << "Can't bind socket! " << WSAGetLastError() << std::endl;
        return 1;
    } else {
        std::cout << "Socket binded!" << std::endl;
    }

    // Хранение инфы о клиенте (port / IP)
    sockaddr_in client; 
    int clientLength = sizeof(client);
    char buf[1024]; // буфер для приема инфы

    // Запуск сервера (жизненный цикл)
    while (true) {
        std::cout << "Server is alive" << std::endl;

        // Очистка временной памяти
        ZeroMemory(&client, clientLength);
        ZeroMemory(buf, 1024); 

        // Ожидание и получение сообщения 
        int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
        if (bytesIn != SOCKET_ERROR) {
            char clientIp[256]; // выделение памяти для конвертации адреса клиента в строку
            ZeroMemory(clientIp, 256); // заполнение памяти нулями

            // Чтение сообщения
            inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
            std::cout << "Message received from " << clientIp << " : " << buf << std::endl;
            
        } else {
            std::cout << "Error receiving from client! " << WSAGetLastError() << std::endl;
        }
    }

    // Закрываем socket
    closesocket(in);
    // Отключаем winsock
    WSACleanup();
    
    return 0;
}
