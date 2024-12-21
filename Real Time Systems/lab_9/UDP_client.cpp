#include <iostream>
#include <WS2tcpip.h> // библиотека сокетов

// Подключение библиотеки на этапе компановки
#pragma comment (lib, "ws2_32.lib")

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

    // Подсказка запроса
    sockaddr_in serverHint;
    serverHint.sin_family = AF_INET; // задаем формат адресов IPv4
    serverHint.sin_port = htons(54000); // порт
    inet_pton(AF_INET, "127.0.0.1", &serverHint.sin_addr);

    // Сокет с типом данных SOCK_DGRAM
    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

    // Запускаем клиента (жизненный цикл)
    std::string msg;
    while (true) {
        // Очищаем сообщение
        msg.clear();

        // Считываем новое сообщение из консоли
        std::cin >> msg;

        // Отправляем данные
        int sendOk = sendto(out, msg.c_str(), msg.size() + 1, 0, (sockaddr*)&serverHint, sizeof(serverHint));
        if (sendOk != SOCKET_ERROR) {
            std::cout << "Message '" << msg << "' has been sent to " << inet_ntoa(serverHint.sin_addr) << "!" << std::endl;
        } else {
            std::cout << "Message hasn't been sent! Error code: " << WSAGetLastError() << std::endl;
        }
    }

    // Закрываем socket
    closesocket(out);
    // Отключаем winsock
    WSACleanup();

    return 0;
}