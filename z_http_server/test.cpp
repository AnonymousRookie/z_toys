#include <iostream>
#include "z_http_server.h"

int main()
{
    ZHttpServer server;
    server.Start(8001);
    return 0;
}

