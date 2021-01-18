// KeyValueDBClientStatic.cpp : Defines the functions for the static library.
//

#include "KeyValueDBClientStatic.h"
#include "grpcpp/support/time.h"

namespace KeyValueDB {
	int KeyValueDBClient::CreateTable(std::string name, std::vector<std::string> key_names) {
		CreateTableRequest req;
		CreateTableResponse resp;
		ClientContext ctx;
		if (name.length() == 0) {
			std::cout << "CreateTable - table name must not be empty" << std::endl;
			return -1;
		}
		if (key_names.size() == 0) {
			std::cout << "CreateTable - table should have at least one key" << std::endl;
			return -1;
		}

		for (int i = 0; i < key_names.size(); i++) {
			req.mutable_table()->add_keys(key_names[i]);
		}
		req.mutable_table()->set_name(name);

		Status status = this->stub_->CreateTable(&ctx, req, &resp);
		if (status.ok()) {
			return 0;
		}

		std::cout << "CreateTable - Error code: " << status.error_code() << ". Error message: " << status.error_message() << std::endl;
		return -1;
	}

	int KeyValueDBClient::DeleteTable(std::string name) {
		DeleteTableRequest req;
		DeleteTableResponse resp;
		ClientContext ctx;
		req.set_table_name(name);

		Status status = this->stub_->DeleteTable(&ctx, req, &resp);
		if (status.ok()) {
			return 0;
		}
		std::cout << "DeleteTable - Error code: " << status.error_code() << ". Error message: " << status.error_message() << std::endl;
		return -1;
	}

	std::string KeyValueDBClient::GetFirstEntry(std::string table_name, std::string key_name, bool desc_sort) {
		GetSeqEntryRequest req;
		GetSeqEntryResponse resp;
		ClientContext ctx;
		req.set_table_name(table_name);
		req.set_key_name(key_name);
		req.set_sort(desc_sort);

		Status status = this->stub_->GetFirstEntry(&ctx, req, &resp);
		if (status.ok()) {
			this->last_entry = resp.entry();
			return this->last_entry.value();
		}

		std::cout << "GetFirstEntry - Error code: " << status.error_code() << ". Error message: " << status.error_message() << std::endl;
		return "";
	}

	std::string KeyValueDBClient::GetLastEntry(std::string table_name, std::string key_name, bool desc_sort) {
		GetSeqEntryRequest req;
		GetSeqEntryResponse resp;
		ClientContext ctx;
		req.set_table_name(table_name);
		req.set_key_name(key_name);
		req.set_sort(desc_sort);

		Status status = this->stub_->GetLastEntry(&ctx, req, &resp);
		if (status.ok()) {
			this->last_entry = resp.entry();
			return this->last_entry.value();
		}

		std::cout << "GetLastEntry - Error code: " << status.error_code() << ". Error message: " << status.error_message() << std::endl;
		return "";
	}

	std::string KeyValueDBClient::GetEntry(std::string table_name, std::string key_name, std::string key_value) {
		GetEntryRequest req;
		GetEntryResponse resp;
		ClientContext ctx;
		req.set_table_name(table_name);
		req.set_key_name(key_name);
		req.set_key_value(key_value);

		Status status = this->stub_->GetEntry(&ctx, req, &resp);
		if (status.ok()) {
			this->last_entry = resp.entry();
			return this->last_entry.value();
		}

		std::cout << "GetEntry - Error code: " << status.error_code() << ". Error message: " << status.error_message() << std::endl;
		return "";
	}

	std::string KeyValueDBClient::GetNextEntry() {

		if (this->last_entry.global_index() == -1) {
			return "";
		}

		GetNextEntryRequest req;
		GetNextEntryResponse resp;
		ClientContext ctx;
		req.mutable_entry()->set_global_index(this->last_entry.global_index());
		req.mutable_entry()->set_key_name(this->last_entry.key_name());
		req.mutable_entry()->set_key_value(this->last_entry.key_value());
		req.mutable_entry()->set_value(this->last_entry.value());
		req.mutable_entry()->set_table_name(this->last_entry.table_name());
		req.mutable_entry()->set_sort(this->last_entry.sort());

		Status status = this->stub_->GetNextEntry(&ctx, req, &resp);
		if (status.ok()) {
			this->last_entry = resp.next_entry();
			return this->last_entry.value();
		}

		return "";
	}

	std::string KeyValueDBClient::GetPrevEntry() {

		if (this->last_entry.global_index() == -1) {
			return "";
		}

		GetPrevEntryRequest req;
		GetPrevEntryResponse resp;
		ClientContext ctx;
		req.mutable_entry()->set_global_index(this->last_entry.global_index());
		req.mutable_entry()->set_key_name(this->last_entry.key_name());
		req.mutable_entry()->set_key_value(this->last_entry.key_value());
		req.mutable_entry()->set_value(this->last_entry.value());
		req.mutable_entry()->set_table_name(this->last_entry.table_name());
		req.mutable_entry()->set_sort(!this->last_entry.sort());

		Status status = this->stub_->GetPrevEntry(&ctx, req, &resp);
		if (status.ok()) {
			this->last_entry = resp.prev_entry();
			return this->last_entry.value();
		}

		return "";
	}

	int KeyValueDBClient::AddEntry(std::string table_name, std::vector<std::pair<std::string, std::string>> keys, std::string value) {
		if (value == "") {
			std::cout << "AddEntry - value must not be empty" << std::endl;
			return -1;
		}

		AddEntryRequest req;
		AddEntryResponse resp;
		ClientContext ctx;
		std::vector<KeyValue> pb_keys;
		req.set_table_name(table_name);
		req.set_value(value);
		for (std::pair<std::string, std::string> key : keys) {
			KeyValue* kv = req.add_keys();
			kv->set_name(key.first);
			kv->set_value(key.second);
		}

		Status status = this->stub_->AddEntry(&ctx, req, &resp);
		if (status.ok()) {
			return 0;
		}

		std::cout << "AddEntry - Error code: " << status.error_code() << ". Error message: " << status.error_message() << std::endl;
		return -1;
	}

	int KeyValueDBClient::DeleteCurrentEntry() {

		if (this->last_entry.global_index() == -1) {
			return -1;
		}

		DeleteCurrentEntryRequest req;
		DeleteCurrentEntryResponse resp;
		ClientContext ctx;
		req.mutable_entry()->set_global_index(this->last_entry.global_index());
		req.mutable_entry()->set_key_name(this->last_entry.key_name());
		req.mutable_entry()->set_key_value(this->last_entry.key_value());
		req.mutable_entry()->set_value(this->last_entry.value());
		req.mutable_entry()->set_table_name(this->last_entry.table_name());
		req.mutable_entry()->set_sort(this->last_entry.sort());

		Status status = this->stub_->DeleteCurrentEntry(&ctx, req, &resp);
		if (status.ok()) {
			Entry empty;
			empty.set_value("");
			empty.set_global_index(-1);
			this->last_entry = empty;
			return 0;
		}

		std::cout << "DeleteCurrentEntry - Error code: " << status.error_code() << ". Error message: " << status.error_message() << std::endl;
		return -1;
	}

	void KeyValueDBClient::Close() {}

	KeyValueDBClient::KeyValueDBClient(std::shared_ptr<Channel> channel) : stub_(DBInterface::NewStub(channel)) {
		Entry empty;
		empty.set_value("");
		empty.set_global_index(-1);
		this->last_entry = empty;
	}

	KeyValueDBClient::~KeyValueDBClient() {};


	KeyValueDBClient::KeyValueDBClient(std::string dsn) {
		this->ch = grpc::CreateChannel(dsn, grpc::InsecureChannelCredentials());
		if (!ch->WaitForConnected(gpr_time_add(
			gpr_now(GPR_CLOCK_REALTIME),
			gpr_time_from_seconds(20, GPR_TIMESPAN)))) {
			throw std::runtime_error("connection failed: timeout");
		}
		this->stub_ = DBInterface::NewStub(ch);
		Entry empty;
		empty.set_value("");
		empty.set_global_index(-1);
		this->last_entry = empty;
	}
}