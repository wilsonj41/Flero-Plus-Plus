#ifndef IDATABASEDRIVER_HPP
#define IDATABASEDRIVER_HPP

#include <string>
#include <unordered_map>

class IDatabaseDriver {
    public:
        virtual bool create_entry(const std::string& query) = 0;
        virtual std::unordered_map<std::string, std::string> read_entry(const std::string& query) = 0;
        virtual bool update_entry(const std::string& query) = 0;
        virtual bool delete_entry(const std::string& query) = 0;
        virtual void connect(const std::string& username, const std::string& password, 
                             const std::string& db, const std::string& host="localhost") = 0;
};

#endif /* IDATABASEDRIVER_HPP */