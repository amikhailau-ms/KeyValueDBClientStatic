// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: service.proto

#include "service.pb.h"
#include "service.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/sync_stream.h>
#include <gmock/gmock.h>

class MockDBInterfaceStub : public DBInterface::StubInterface {
 public:
  MOCK_METHOD3(CreateTable, ::grpc::Status(::grpc::ClientContext* context, const ::CreateTableRequest& request, ::CreateTableResponse* response));
  MOCK_METHOD3(AsyncCreateTableRaw, ::grpc::ClientAsyncResponseReaderInterface< ::CreateTableResponse>*(::grpc::ClientContext* context, const ::CreateTableRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncCreateTableRaw, ::grpc::ClientAsyncResponseReaderInterface< ::CreateTableResponse>*(::grpc::ClientContext* context, const ::CreateTableRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(DeleteTable, ::grpc::Status(::grpc::ClientContext* context, const ::DeleteTableRequest& request, ::DeleteTableResponse* response));
  MOCK_METHOD3(AsyncDeleteTableRaw, ::grpc::ClientAsyncResponseReaderInterface< ::DeleteTableResponse>*(::grpc::ClientContext* context, const ::DeleteTableRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncDeleteTableRaw, ::grpc::ClientAsyncResponseReaderInterface< ::DeleteTableResponse>*(::grpc::ClientContext* context, const ::DeleteTableRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(GetFirstEntry, ::grpc::Status(::grpc::ClientContext* context, const ::GetSeqEntryRequest& request, ::GetSeqEntryResponse* response));
  MOCK_METHOD3(AsyncGetFirstEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::GetSeqEntryResponse>*(::grpc::ClientContext* context, const ::GetSeqEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncGetFirstEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::GetSeqEntryResponse>*(::grpc::ClientContext* context, const ::GetSeqEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(GetLastEntry, ::grpc::Status(::grpc::ClientContext* context, const ::GetSeqEntryRequest& request, ::GetSeqEntryResponse* response));
  MOCK_METHOD3(AsyncGetLastEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::GetSeqEntryResponse>*(::grpc::ClientContext* context, const ::GetSeqEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncGetLastEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::GetSeqEntryResponse>*(::grpc::ClientContext* context, const ::GetSeqEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(GetEntry, ::grpc::Status(::grpc::ClientContext* context, const ::GetEntryRequest& request, ::GetEntryResponse* response));
  MOCK_METHOD3(AsyncGetEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::GetEntryResponse>*(::grpc::ClientContext* context, const ::GetEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncGetEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::GetEntryResponse>*(::grpc::ClientContext* context, const ::GetEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(GetNextEntry, ::grpc::Status(::grpc::ClientContext* context, const ::GetNextEntryRequest& request, ::GetNextEntryResponse* response));
  MOCK_METHOD3(AsyncGetNextEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::GetNextEntryResponse>*(::grpc::ClientContext* context, const ::GetNextEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncGetNextEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::GetNextEntryResponse>*(::grpc::ClientContext* context, const ::GetNextEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(GetPrevEntry, ::grpc::Status(::grpc::ClientContext* context, const ::GetPrevEntryRequest& request, ::GetPrevEntryResponse* response));
  MOCK_METHOD3(AsyncGetPrevEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::GetPrevEntryResponse>*(::grpc::ClientContext* context, const ::GetPrevEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncGetPrevEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::GetPrevEntryResponse>*(::grpc::ClientContext* context, const ::GetPrevEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(AddEntry, ::grpc::Status(::grpc::ClientContext* context, const ::AddEntryRequest& request, ::AddEntryResponse* response));
  MOCK_METHOD3(AsyncAddEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::AddEntryResponse>*(::grpc::ClientContext* context, const ::AddEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncAddEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::AddEntryResponse>*(::grpc::ClientContext* context, const ::AddEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(DeleteCurrentEntry, ::grpc::Status(::grpc::ClientContext* context, const ::DeleteCurrentEntryRequest& request, ::DeleteCurrentEntryResponse* response));
  MOCK_METHOD3(AsyncDeleteCurrentEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::DeleteCurrentEntryResponse>*(::grpc::ClientContext* context, const ::DeleteCurrentEntryRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncDeleteCurrentEntryRaw, ::grpc::ClientAsyncResponseReaderInterface< ::DeleteCurrentEntryResponse>*(::grpc::ClientContext* context, const ::DeleteCurrentEntryRequest& request, ::grpc::CompletionQueue* cq));
};

