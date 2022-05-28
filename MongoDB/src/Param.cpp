//
// Param.cpp
//
// Library: MongoDB
// Package: MongoDB
// Module:  Param
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#include "Poco/MongoDB/Param.h"

Param::Param(const std::string& uri):
    _ssl(false),
	_authMechanism(Database::AUTH_SCRAM_SHA1),
	databaseName("admin")
{
	Poco::URI theURI(uri);
	if (theURI.getScheme() != "mongodb") throw Poco::UnknownURISchemeException(uri);

	std::string userInfo = theURI.getUserInfo();
	if (!userInfo.empty())
	{
		if (uri.find(',') == std::string::npos){

		std::string::size_type pos = userInfo.find(':');
		if (pos != std::string::npos)
		{
			_username.assign(userInfo, 0, pos++);
			_password.assign(userInfo, pos, userInfo.size() - pos);
		}
		else _username = userInfo;
	
		std::string host = theURI.getHost();
		Poco::UInt16 port = theURI.getPort();
		if (port == 0) port = 27017;
	}

	std::string databaseName = theURI.getPath();
	if (!databaseName.empty() && databaseName[0] == '/') databaseName.erase(0, 1);
	if (!databaseName.empty()) _databaseName = databaseName;

	Poco::URI::QueryParameters params = theURI.getQueryParameters();
	for (Poco::URI::QueryParameters::const_iterator it = params.begin(); it != params.end(); ++it)
	{
		if (it->first == "ssl")
		{
			_ssl = (it->second == "true");
		}
		else if (it->first == "connectTimeoutMS")
		{
			_connectTimeout = static_cast<Poco::Timespan::TimeDiff>(1000)*Poco::NumberParser::parse(it->second);
		}
		else if (it->first == "socketTimeoutMS")
		{
			_socketTimeout = static_cast<Poco::Timespan::TimeDiff>(1000)*Poco::NumberParser::parse(it->second);
		}
		else if (it->first == "authMechanism")
		{
			_authMechanism = it->second;
		}
	}

	
}
