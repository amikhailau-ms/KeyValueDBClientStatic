#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <string>
#include <vector>
#include <grpcpp/grpcpp.h>
#include "service.grpc.pb.h"

using namespace std;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

namespace KeyValueDB {

    class KeyValueDBClient {
    public:
        KeyValueDBClient(std::string dsn);
        ~KeyValueDBClient();

        int CreateTable(std::string name, std::vector<std::string> key_names);
        int DeleteTable(std::string name);
        std::string GetFirstEntry(std::string table_name, std::string key_name, bool desc_sort = false);
        std::string GetLastEntry(std::string table_name, std::string key_name, bool desc_sort = false);
        std::string GetEntry(std::string table_name, std::string key_name, std::string key_value);
        std::string GetNextEntry();
        std::string GetPrevEntry();
        int AddEntry(std::string table_name, std::vector<std::pair<std::string, std::string>> keys, std::string value);
        int DeleteCurrentEntry();
        void Close();

    private:
        KeyValueDBClient(std::shared_ptr<Channel> channel);

        std::unique_ptr<DBInterface::Stub> stub_;
        std::shared_ptr<Channel> ch;
        Entry last_entry;
    };
}