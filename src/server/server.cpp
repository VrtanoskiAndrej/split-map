#include <iostream>
#include <memory>
#include <string>

#include "../split_map.hpp"
#include "kvs_transactions.grpc.pb.h"
#include <grpcpp/grpcpp.h>

class KeyValueStoreServiceImpl final
    : public KVSTransactions::KeyValueStore::Service
{
private:
  int server_id;
  split_map<std::string, std::string> map;

public:
  grpc::Status
  GetCommand (grpc::ServerContext *context,
              const KVSTransactions::GetRequest *request,
              KVSTransactions::GetReply *reply) override
  {
    std::optional<std::string> get_result = map.get (request->key ());
    if (get_result.has_value ())
      {
        reply->set_value (get_result.value ());
      }
    else
      {
        reply->set_value ("key does not exist");
      }
    return grpc::Status::OK;
  }

  grpc::Status
  PutCommand (grpc::ServerContext *context,
              const KVSTransactions::PutRequest *request,
              KVSTransactions::PutReply *reply) override
  {
    map.put (request->key (), request->value ());
    reply->set_status ("Put OK");
    return grpc::Status::OK;
  }

  KeyValueStoreServiceImpl () { server_id = -1; }
};

int
main (int argc, char **argv)
{
  std::string server_address ("0.0.0.0:50051");

  KeyValueStoreServiceImpl service;
  grpc::ServerBuilder builder;
  builder.AddListeningPort (server_address,
                            grpc::InsecureServerCredentials ());
  builder.RegisterService (&service);
  std::unique_ptr<grpc::Server> server (builder.BuildAndStart ());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait ();

  return 0;
}
