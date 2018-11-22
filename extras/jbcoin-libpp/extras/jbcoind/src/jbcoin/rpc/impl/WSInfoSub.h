//------------------------------------------------------------------------------
/*
    This file is part of jbcoind: https://github.com/jbcoin/jbcoind
    Copyright (c) 2012, 2013 Jbcoin Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef JBCOIN_RPC_WSINFOSUB_H
#define JBCOIN_RPC_WSINFOSUB_H

#include <jbcoin/server/WSSession.h>
#include <jbcoin/net/InfoSub.h>
#include <jbcoin/beast/net/IPAddressConversion.h>
#include <jbcoin/json/Output.h>
#include <jbcoin/json/to_string.h>
#include <jbcoin/rpc/Role.h>
#include <memory>
#include <string>

namespace jbcoin {

class WSInfoSub : public InfoSub
{
    std::weak_ptr<WSSession> ws_;
    std::string user_;
    std::string fwdfor_;

public:
    WSInfoSub(Source& source, std::shared_ptr<WSSession> const& ws)
        : InfoSub(source)
        , ws_(ws)
    {
        auto const& h = ws->request();
        auto it = h.find("X-User");
        if (it != h.end() &&
            isIdentified(
                ws->port(), beast::IPAddressConversion::from_asio(
                    ws->remote_endpoint()).address(), it->value().to_string()))
        {
            user_ = it->value().to_string();
            it = h.find("X-Forwarded-For");
            if (it != h.end())
                fwdfor_ = it->value().to_string();
        }
    }

    std::string
    user() const
    {
        return user_;
    }

    std::string
    forwarded_for() const
    {
        return fwdfor_;
    }

    void
    send(Json::Value const& jv, bool)
    {
        auto sp = ws_.lock();
        if(! sp)
            return;
        beast::multi_buffer sb;
        stream(jv,
            [&](void const* data, std::size_t n)
            {
                sb.commit(boost::asio::buffer_copy(
                    sb.prepare(n), boost::asio::buffer(data, n)));
            });
        auto m = std::make_shared<
            StreambufWSMsg<decltype(sb)>>(
                std::move(sb));
        sp->send(m);
    }
};

} // jbcoin

#endif
