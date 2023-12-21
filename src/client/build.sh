#!/bin/bash

PROTO_DIR='../proto'
python3 -m grpc_tools.protoc -I$PROTO_DIR --python_out=. --pyi_out=. --grpc_python_out=. $PROTO_DIR/kvs_transactions.proto
