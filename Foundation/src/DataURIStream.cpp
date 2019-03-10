//
// DataURIStream.cpp
//
// Library: Foundation
// Package: Streams
// Module:  DataURIStreamFactory
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/DataURIStream.h"
#include "Poco/URI.h"
#include "Poco/Path.h"
#include "Poco/Exception.h"
#include "Poco/StreamUtil.h"
#include <string.h>


namespace Poco {


DataURIStream::DataURIStream(const URI& uri)
{
    if (uri.getScheme() != "data")
        throw DataFormatException();

    const std::string& path = uri.getPath();
    size_t comma = path.find(',');
    if (comma == std::string::npos)
        throw DataFormatException();
    _data = path.substr(comma + 1);
    _memoryStream = std::make_unique<MemoryInputStream>(_data.data(), _data.length());
    constexpr char base64[] = ";base64";
    const size_t base64Len = strlen(base64);
    bool base64Used = (comma >= base64Len && path.compare(comma - base64Len, base64Len, base64, base64Len) == 0);
    if (base64Used)
    {
        _base64Decoder = std::make_unique<Base64Decoder>(*_memoryStream, 0);
        poco_ios_init(_base64Decoder->rdbuf());
    }
    else
        poco_ios_init(_memoryStream->rdbuf());
}


DataURIStream::~DataURIStream()
{
}


} // namespace Poco
