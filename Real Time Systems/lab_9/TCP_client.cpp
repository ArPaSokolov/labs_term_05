#include <iostream>
#include <WS2tcpip.h> // библиотека сокетов

// Подключение библиотеки на этапе компановки
#pragma comment (lib, "ws2_32.lib")

std::string ipAddress = "127.0.0.1";
int port = 54000;


int main()
{
    // Инициализация WINSOCK
    WSADATA data;
    int wsOk = WSAStartup(MAKEWORD(2, 2), &data); // запуск
    if (wsOk == 0) {
        std::cout << "Winsock started! " << wsOk << std::endl;
    } else {
        std::cerr << "Can't start winsock, Err #" << wsOk << " Quitting " << std::endl;
        WSACleanup();
        return 1;
    }

    // Создание TCP сокета
    SOCKET out = socket(AF_INET, SOCK_STREAM, 0);
    if (out == INVALID_SOCKET) {
        std::cerr << "Can't create a socket, Err #" << WSAGetLastError() << " Quitting..." << std::endl;
        WSACleanup();
        return 1;
    }

    // Подсказка запроса
    sockaddr_in serverHint;
    serverHint.sin_family = AF_INET; // задаем формат адресов IPv4
    serverHint.sin_port = htons(port); // порт
    inet_pton(AF_INET, ipAddress.c_str(), &serverHint.sin_addr);

    // Установка соединения с сервером
    int connResult = connect(out, (sockaddr*)&serverHint, sizeof(serverHint));
    if (connResult == SOCKET_ERROR) {
        std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << " Quitting..." << std::endl;
        closesocket(out);
        WSACleanup();
        return 1;
    }

    // Запускаем клиента (жизненный цикл)
    std::string msg;
    char buf[1024];

    do {
        // Очищаем сообщение
        msg.clear();

        std::cout << "> ";
        
        // Считываем новое сообщение из консоли
        std::cin >> msg;

        if (msg.size() > 0) {
            bool ok = false;
            const int maxAttempts = 5;  // Максимальное количество попыток
            int attempt = 0;

            while (!ok && attempt < maxAttempts) {
                attempt++;

                // Отправляем данные
                int sendOk =  send(out, msg.c_str(), msg.size() + 1, 0);
                if (sendOk == SOCKET_ERROR) {
                    std::cerr << "Failed to send message. Error: " << WSAGetLastError() << std::endl;
                    closesocket(out);
                    WSACleanup();
                    return 1;
                }

                // Получаем ответ от сервера
                ZeroMemory(buf, 1024);
                int bytesReceived = recv(out, buf, 1024, 0);
                if (bytesReceived > 0) {
                    std::string receivedMsg(buf, 0, bytesReceived);
                    if (receivedMsg == msg) {
                        std::cout << "SERVER> " << receivedMsg << std::endl;
                        ok = true;
                    } else {
                        std::cerr << "Received message does not match sent message. Retrying..." << std::endl;
                        std::cerr << "Attempt " << attempt << " out of " << maxAttempts << std::endl;
                    }
                } else if (bytesReceived == 0) {
                    std::cerr << "Connection closed by the server." << std::endl;
                    closesocket(out);
                    WSACleanup();
                    return 1;
                } else {
                    std::cerr << "Failed to receive message. Error: " << WSAGetLastError() << std::endl;
                    closesocket(out);
                    WSACleanup();
                    return 1;
                }
            }

            if (!ok) {
                std::cerr << "Failed to send the correct message after " << maxAttempts << " attempts." << std::endl;
            }
        }

    } while (msg.size() > 0);

    std::cout << "Quitting..." << std::endl;

    // Закрываем socket
    closesocket(out);
    // Отключаем winsock
    WSACleanup();

    return 0;
}
