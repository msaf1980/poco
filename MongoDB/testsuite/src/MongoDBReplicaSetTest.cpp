//
// MongoDBReplicaSetTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/DateTime.h"
#include "Poco/ObjectPool.h"
#include "Poco/MongoDB/InsertRequest.h"
#include "Poco/MongoDB/QueryRequest.h"
#include "Poco/MongoDB/DeleteRequest.h"
#include "Poco/MongoDB/GetMoreRequest.h"
#include "Poco/MongoDB/PoolableConnectionFactory.h"
#include "Poco/MongoDB/Database.h"
#include "Poco/MongoDB/Cursor.h"
#include "Poco/MongoDB/ObjectId.h"
#include "Poco/MongoDB/Binary.h"
#include "Poco/Net/NetException.h"
#include "Poco/UUIDGenerator.h"
#include "MongoDBReplicaSetTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include <iostream>


using namespace Poco::MongoDB;


Poco::MongoDB::Connection::Ptr MongoDBReplicaSetTest::_mongo;


MongoDBReplicaSetTest::MongoDBReplicaSetTest(const std::string& name):
	CppUnit::TestCase("MongoDB")
{
}


MongoDBReplicaSetTest::~MongoDBReplicaSetTest()
{
}


void MongoDBReplicaSetTest::setUp()
{
}


void MongoDBReplicaSetTest::tearDown()
{
}


void MongoDBReplicaSetTest::testConnectionPool()
{
#if POCO_OS == POCO_OS_ANDROID
		std::string host = "10.0.2.2";
#else
		std::string host = "127.0.0.1";
#endif

	Poco::Net::SocketAddress sa(host, 27017);
	Poco::PoolableObjectFactory<Poco::MongoDB::Connection, Poco::MongoDB::Connection::Ptr> factory(sa);
	Poco::ObjectPool<Poco::MongoDB::Connection, Poco::MongoDB::Connection::Ptr> pool(factory, 10, 15);

	Poco::MongoDB::PooledConnection pooledConnection(pool);

	Poco::MongoDB::QueryRequest request("team.$cmd");
	request.setNumberToReturn(1);
	request.selector().add("count", std::string("players"));

	Poco::MongoDB::ResponseMessage response;
	((Connection::Ptr) pooledConnection)->sendRequest(request, response);

	if ( response.documents().size() > 0 )
	{
		Poco::MongoDB::Document::Ptr doc = response.documents()[0];
		assertTrue (doc->getInteger("n") == 1);
	}
	else
	{
		fail("Didn't get a response from the count command");
	}
}


void MongoDBReplicaSetTest::testConnectURI()
{
	Poco::MongoDB::Connection conn;
	Poco::MongoDB::Connection::SocketFactory sf;

#if POCO_OS == POCO_OS_ANDROID
		std::string host = "10.0.2.2:30001,10.0.2.2:30002,10.0.2.2:30003";
#else
		std::string host = "127.0.0.1:30001,127.0.0.1:30002,127.0.0.1:30003";
#endif

	conn.connect("mongodb://" + host, sf);
	conn.disconnect();

	try
	{
		conn.connect("http://" + host, sf);
		fail("invalid URI scheme - must throw");
	}
	catch (Poco::UnknownURISchemeException&)
	{
	}

	try
	{
		conn.connect("mongodb://" + host + "?ssl=true", sf);
		fail("SSL not supported, must throw");
	}
	catch (Poco::NotImplementedException&)
	{
	}

	conn.connect("mongodb://" + host + "/admin?ssl=false&connectTimeoutMS=10000&socketTimeoutMS=10000", sf);
	conn.disconnect();

	try
	{
		conn.connect("mongodb://" + host + "/admin?connectTimeoutMS=foo", sf);
		fail("invalid parameter - must throw");
	}
	catch (Poco::Exception&)
	{
	}

#ifdef MONGODB_TEST_AUTH
	conn.connect("mongodb://admin:admin@127.0.0.1/admin", sf);
	conn.disconnect();
#endif
}


CppUnit::Test* MongoDBReplicaSetTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("MongoDBReplicaSetTest");
	CppUnit_addTest(pSuite, MongoDBReplicaSetTest, testConnectionPool);
	CppUnit_addTest(pSuite, MongoDBReplicaSetTest, testConnectURI);
	return pSuite;
}
