#include <iostream>
#include "fcgio.h"

int main(void) {
    std::streambuf *cin_streambuf = std::cin.rdbuf();
    std::streambuf *cout_streambuf = std::cout.rdbuf();
    std::streambuf *cerr_streambuf = std::cerr.rdbuf();

    int sock = FCGX_OpenSocket(":50001", 10);
    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, sock, 0);

    while (FCGX_Accept_r(&request) == 0) {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        std::cin.rdbuf(&cin_fcgi_streambuf);
        std::cout.rdbuf(&cout_fcgi_streambuf);
        std::cerr.rdbuf(&cerr_fcgi_streambuf);

        std::cout << "Content-type: text/html\r\n"
            << "\r\n"
            << "<html>\n"
            << "  <head>\n"
            << "    <title>Hello, World2</title>\n"
            << "  </head>\n"
            << "  <body>\n"
            << "    <h1>Hello, World!</h1>\n"
            << "  </body>\n"
            << "</html>\n";
    }

    std::cin.rdbuf(cin_streambuf);
    std::cout.rdbuf(cout_streambuf);
    std::cerr.rdbuf(cerr_streambuf);

    return EXIT_SUCCESS;
}
