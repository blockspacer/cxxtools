/*
 * Copyright (C) 2011 Tommi Maekitalo
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * As a special exception, you may use this file as part of a free
 * software library without restriction. Specifically, if other files
 * instantiate templates or use macros or inline functions from this
 * file, or you compile this file and link it with other files to
 * produce an executable, this file does not by itself cause the
 * resulting executable to be covered by the GNU General Public
 * License. This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU Library
 * General Public License.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CXXTOOLS_JSON_RESPONDER_H
#define CXXTOOLS_JSON_RESPONDER_H

#include <cxxtools/jsondeserializer.h>
#include <cxxtools/decomposer.h>
#include <cxxtools/iostream.h>
#include <cxxtools/jsonparser.h>
#include <cxxtools/jsonformatter.h>

namespace cxxtools
{

class ServiceRegistry;

namespace json
{
class Socket;

class Responder
{
        friend class Socket;

    public:
        static const int ParseError = -32700;
        static const int InvalidRequest = -32600;
        static const int MethodNotFound = -32601;
        static const int InvalidParams = -32602;
        static const int InternalError = -32603;
        static const int ApplicationError = -32500;

        explicit Responder(ServiceRegistry& serviceRegistry);
        ~Responder();

        void begin();
        bool advance(char ch);
        void finalize(std::ostream& out);
        bool failed() const
        { return _failed; }

    private:
        ServiceRegistry& _serviceRegistry;
        JsonDeserializer _deserializer;

        bool _failed;
        int _errorCode;
        std::string _errorMessage;
};
}
}
#endif // CXXTOOLS_JSON_RESPONDER_H
