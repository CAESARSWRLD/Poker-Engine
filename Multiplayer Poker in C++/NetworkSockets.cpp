#include "NetworkSockets.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")


int sendInstruction(std::string input)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "WSAStartup failed.\n";
        return 1;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET)
    {
        std::cout << "Failed to create socket.\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cout << "Bind failed.\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, 1) == SOCKET_ERROR)
    {
        std::cout << "Listen failed.\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port 5555...\n";
    std::cout << "Waiting for client...\n";

    SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Accept failed.\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }


    //Examples: YOUR_TURN, WAIT, SHOW_ALL, SHOW_FOLD_CALL

    while (true)
    {
        

        if (input == "quit")
            break;

        if (input.empty())
            continue;

        int result = send(clientSocket, input.c_str(), (int)input.size(), 0);
        if (result == SOCKET_ERROR)
        {
            std::cout << "Send failed.\n";
            break;
        }

        std::cout << "Sent: " << input << "\n";
    }

    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();

    std::cout << "Server shut down.\n";
    return 0;
}