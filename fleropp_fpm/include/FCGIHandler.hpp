#ifndef FCGI_HANDLER_HPP
#define FCGI_HANDLER_HPP

#include "IView.hpp"
#include "CompUnit.hpp"
#include "ConstexprMap.hpp"
#include "IDatabaseDriver.hpp"

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <memory>

#include "fcgiapp.h"

namespace fleropp::fpm {
    using endpoints_map_t = std::unordered_map<std::string, std::vector<CompUnit<IViewWrapper>>>; 
    class FCGIHandler {
      public:
        /**
         * Constructor
         * 
         * \param unix_socket Path to unix socket file
         * \param backlog The number of incoming requests in the background
         */
        FCGIHandler(const std::string &unix_sock, const unsigned int backlog = 512);
        
        /**
         * Constructor
         * 
         * \param tcp_sock Port number assigned to socket
         * \param backlog The number of incoming requests in the background
         */
        FCGIHandler(const unsigned int tcp_sock, const unsigned int backlog = 512);

        /**
         * Spawns pool of worker threads.
         * 
         * \param n_thr The number of threads to spawn 
         */
        void spawn(std::size_t n_thr);

        /**
         * Wait on the worker threads (blocking). 
         */
        void wait();

        /**
         * Loads in a map of endpoints to their corresponding compilation units.
         * This will generally be created by a `fleropp::fpm::ConfigParser`.
         * 
         * \param endpoints_map The map of endpoints to compilation units.
         */
        void load_endpoints(const endpoints_map_t& endpoints_map);

        void connect_db(
            const std::string &driver, const std::string &username,
            const std::string &password, const std::string &dbname,
            const std::string &host, const std::string &port);

      private: 
        int m_fd;
        FCGX_Request m_request;
        endpoints_map_t m_endpoints;
        std::shared_ptr<IDatabaseDriver> m_db_handle;
        std::vector<std::thread> m_workers;
    };
}

#endif /* FCGI_HANDLER_HPP */