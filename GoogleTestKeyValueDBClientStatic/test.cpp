#include "pch.h"
#include "KeyValueDBClientStatic.h"

const std::string db_url("localhost:50051");

TEST(TestConnection, SuccessfulConnection) {
	try {
		KeyValueDB::KeyValueDBClient dbconn(db_url);
		dbconn.Close();
	}
	catch (std::exception err) {
		std::cout << err.what() << std::endl;
		FAIL();
	}
}

TEST(TestConnection, Timeout) {
	try {
		KeyValueDB::KeyValueDBClient dbconn("localhost:10000");
		FAIL();
	}
	catch (std::runtime_error err) {
		EXPECT_EQ(err.what(), std::string("connection failed: timeout"));
	}
}

TEST(TestFlow, SuccessfulCreateTable) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	int res = dbconn.CreateTable("test_table", { "key1", "key2", "key3" });
	EXPECT_EQ(res, 0);

	dbconn.Close();
}

TEST(TestFlow, FailedCreateTable) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	int res = dbconn.CreateTable("", { "key1", "key2", "key3" });
	EXPECT_EQ(res, -1);

	res = dbconn.CreateTable("test_table2", {});
	EXPECT_EQ(res, -1);

	dbconn.Close();
}

TEST(TestFlow, SuccessfulAddEntries) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	int res = dbconn.AddEntry("test_table", { { "key1", "1 1 key" }, { "key2", "1 2 key" }, { "key3", "1 3 key" } }, "First value");
	EXPECT_EQ(res, 0);

	res = dbconn.AddEntry("test_table", { { "key1", "2 1 key" }, { "key2", "2 2 key" }, { "key3", "2 3 key" } }, "Second value");
	EXPECT_EQ(res, 0);

	res = dbconn.AddEntry("test_table", { { "key1", "3 1 key" }, { "key2", "3 2 key" }, { "key3", "3 3 key" } }, "Third value");
	EXPECT_EQ(res, 0);

	dbconn.Close();
}

TEST(TestFlow, FailedAddEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	int res = dbconn.AddEntry("test_table1", { { "key1", "1 1 key" }, { "key2", "1 2 key" }, { "key3", "1 3 key" } }, "First value");
	EXPECT_EQ(res, -1);

	res = dbconn.AddEntry("test_table", { { "key1", "1 1 key" }, { "key2", "1 2 key" }, { "key4", "1 3 key" } }, "First value");
	EXPECT_EQ(res, -1);

	dbconn.Close();
}

TEST(TestFlow, SuccessfulGetFirstEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetFirstEntry("test_table", "key1");
	EXPECT_EQ(value, "First value");

	value = dbconn.GetFirstEntry("test_table", "key2");
	EXPECT_EQ(value, "First value");

	value = dbconn.GetFirstEntry("test_table", "key3");
	EXPECT_EQ(value, "First value");

	value = dbconn.GetFirstEntry("test_table", "key1", true);
	EXPECT_EQ(value, "Third value");

	dbconn.Close();
}

TEST(TestFlow, FailedGetFirstEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetFirstEntry("test_table1", "key1");
	EXPECT_EQ(value, "");

	value = dbconn.GetFirstEntry("test_table", "key4");
	EXPECT_EQ(value, "");

	dbconn.Close();
}

TEST(TestFlow, SuccessfulGetLastEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetLastEntry("test_table", "key1");
	EXPECT_EQ(value, "Third value");

	value = dbconn.GetLastEntry("test_table", "key2");
	EXPECT_EQ(value, "Third value");

	value = dbconn.GetLastEntry("test_table", "key3");
	EXPECT_EQ(value, "Third value");

	value = dbconn.GetLastEntry("test_table", "key1", true);
	EXPECT_EQ(value, "First value");

	dbconn.Close();
}

TEST(TestFlow, FailedGetLastEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetLastEntry("test_table1", "key1");
	EXPECT_EQ(value, "");

	value = dbconn.GetLastEntry("test_table", "key4");
	EXPECT_EQ(value, "");

	dbconn.Close();
}

TEST(TestFlow, SuccessfulGetEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetEntry("test_table", "key1", "1 1 key");
	EXPECT_EQ(value, "First value");

	value = dbconn.GetEntry("test_table", "key2", "2 2 key");
	EXPECT_EQ(value, "Second value");

	value = dbconn.GetEntry("test_table", "key3", "3 3 key");
	EXPECT_EQ(value, "Third value");

	dbconn.Close();
}

TEST(TestFlow, FailedGetEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetEntry("test_table1", "key1", "1 1 key");
	EXPECT_EQ(value, "");

	value = dbconn.GetEntry("test_table", "key4", "2 2 key");
	EXPECT_EQ(value, "");

	value = dbconn.GetEntry("test_table", "key3", "4 3 key");
	EXPECT_EQ(value, "");

	dbconn.Close();
}

TEST(TestFlow, SuccessfulGetNextEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetFirstEntry("test_table", "key1");
	EXPECT_EQ(value, "First value");
	value = dbconn.GetNextEntry();
	EXPECT_EQ(value, "Second value");

	value = dbconn.GetFirstEntry("test_table", "key1", true);
	EXPECT_EQ(value, "Third value");
	value = dbconn.GetNextEntry();
	EXPECT_EQ(value, "Second value");

	value = dbconn.GetLastEntry("test_table", "key1");
	EXPECT_EQ(value, "Third value");
	value = dbconn.GetNextEntry();
	EXPECT_EQ(value, "First value");

	dbconn.Close();
}

TEST(TestFlow, FailedGetNextEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetNextEntry();
	EXPECT_EQ(value, "");

	dbconn.Close();
}

TEST(TestFlow, SuccessfulGetPrevEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetLastEntry("test_table", "key1");
	EXPECT_EQ(value, "Third value");
	value = dbconn.GetPrevEntry();
	EXPECT_EQ(value, "Second value");

	value = dbconn.GetLastEntry("test_table", "key1", true);
	EXPECT_EQ(value, "First value");
	value = dbconn.GetPrevEntry();
	EXPECT_EQ(value, "Second value");

	value = dbconn.GetFirstEntry("test_table", "key1");
	EXPECT_EQ(value, "First value");
	value = dbconn.GetPrevEntry();
	EXPECT_EQ(value, "Third value");

	dbconn.Close();
}

TEST(TestFlow, FailedGetPrevEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetPrevEntry();
	EXPECT_EQ(value, "");

	dbconn.Close();
}

TEST(TestFlow, SuccessfulDeleteCurrentEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	std::string value = dbconn.GetLastEntry("test_table", "key1");
	EXPECT_EQ(value, "Third value");
	int res = dbconn.DeleteCurrentEntry();
	EXPECT_EQ(res, 0);

	dbconn.Close();
}

TEST(TestFlow, FailedDeleteCurrentEntry) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	int res = dbconn.DeleteCurrentEntry();
	EXPECT_EQ(res, -1);

	dbconn.Close();
}

TEST(TestFlow, SuccessfulDeleteTable) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	int res = dbconn.DeleteTable("test_table");
	EXPECT_EQ(res, 0);

	dbconn.Close();
}

TEST(TestFlow, FailedDeleteTable) {
	KeyValueDB::KeyValueDBClient dbconn(db_url);

	int res = dbconn.DeleteTable("test_table5");
	EXPECT_EQ(res, -1);

	dbconn.Close();
}