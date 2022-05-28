//
// Connection.h
//
// Library: MongoDB
// Package: MongoDB
// Module:  Connection
//
// Definition of the Connection class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#ifndef PARAM
#define PARAM


#ifndef MongoDB_Connection_INCLUDED
#define MongoDB_Connection_INCLUDED

#include <string>

namespace Poco {
namespace MongoDB {


class MongoDB_API Param
	/// Represents a a MongoDB connection param
{
public:
    Param(const std::string& param);

	inline bool isSSL() const { return _ssl; }
	inline Poco::Timespan connectTimeout() const { return _connectTimeout; }
	inline Poco::Timespan socketTimeout() const { return _socketTimeout; }
	inline const std::vector<Poco::Net::SocketAddress>& { return _addresses; }

	inline const std::string& databaseName() { return _databaseName; }

	inline const std::string& authMechanism() { return _authMechanism; }

	inline bool noAuth() const { return _username.empty(); }
	inline const std::string& username() { return _username; }
	inline const std::string& password() { return _password; }

private:
    bool _ssl;
	Poco::Timespan _connectTimeout;
	Poco::Timespan _socketTimeout;
	std::vector<Poco::Net::SocketAddress> _addresses;

	std::string _databaseName;

	std::string _authMechanism;
	std::string _username;
	std::string _password;
};


} } // namespace Poco::MongoDB


#endif // MongoDB_Connection_INCLUDED


#endif /* PARAM */
