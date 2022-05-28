//
// MongoDBReplicaSetTest.h
//
// Definition of the MongoDBReplicaSetTest class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#ifndef MONGODBREPLICASETTEST
#define MONGODBREPLICASETTEST


#ifndef MongoDBReplicaSetTest_INCLUDED
#define MongoDBReplicaSetTest_INCLUDED


#include "Poco/MongoDB/MongoDB.h"
#include "Poco/MongoDB/Connection.h"
#include "CppUnit/TestCase.h"


class MongoDBReplicaSetTest: public CppUnit::TestCase
{
public:
	MongoDBReplicaSetTest(const std::string& name);

	virtual ~MongoDBReplicaSetTest();

   void testConnectionPool();
	void testConnectURI();
	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	static Poco::MongoDB::Connection::Ptr _mongo;
};


#endif // MongoDBReplicaSetTest_INCLUDED


#endif /* MONGODBREPLICASETTEST */
