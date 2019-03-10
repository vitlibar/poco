//
// DataURIStream.h
//
// Library: Foundation
// Package: Streams
// Module:  DataURIStreamFactory
//
// Definition of the DataURIStream class.
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_DataURIStream_INCLUDED
#define Foundation_DataURIStream_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/MemoryStream.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Nullable.h"


namespace Poco {


class URI;


class DataURIStream : public std::istream
{
    /// An input stream for reading data from a data URI.
    /// For example, when constructed from  "data:text/plain;base64,SGVsbG8sIFdvcmxkIQ%3D%3D" it reads "Hello, World!".
public:
    DataURIStream(const URI& uri);
        /// Creates a DataURIStream for the given data URI,
        /// ready for reading data.
        /// Throws a DataFormatException exception if the data is incorrect format.

    ~DataURIStream();
        /// Destroys the DataURIStream.

private:
    std::string _data;
    std::unique_ptr<MemoryInputStream> _memoryStream;
    std::unique_ptr<Base64Decoder> _base64Decoder;
};


} // namespace Poco


#endif // Foundation_DataURIStream_INCLUDED
