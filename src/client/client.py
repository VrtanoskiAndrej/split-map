#!/bin/python3

import grpc
import kvs_transactions_pb2
import kvs_transactions_pb2_grpc


def generate_get_message(key: str) -> str:
    return kvs_transactions_pb2.GetRequest(key=key)

def generate_put_message(key:str, value: str) -> str:
    return kvs_transactions_pb2.PutRequest(key=key, value=value)


def kvs_get(stub: object, key: str):
    request = generate_get_message(key)
    response = stub.GetCommand(request)
    return response.value


def kvs_put(stub: object, key: str, value: str):
    request = generate_put_message(key, value)
    response = stub.PutCommand(request)
    return response.status


if __name__ == "__main__":
    with grpc.insecure_channel("localhost:50051") as channel:
        stub = kvs_transactions_pb2_grpc.KeyValueStoreStub(channel)

        print('--- PUT ---')
        print(kvs_put(stub, '1', '2'))

        print('--- GET ---')
        print(kvs_get(stub, '1'))
         

