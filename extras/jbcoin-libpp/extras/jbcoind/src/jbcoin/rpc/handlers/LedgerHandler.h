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

#ifndef JBCOIN_RPC_HANDLERS_LEDGER_H_INCLUDED
#define JBCOIN_RPC_HANDLERS_LEDGER_H_INCLUDED

#include <jbcoin/app/main/Application.h>
#include <jbcoin/app/ledger/LedgerToJson.h>
#include <jbcoin/app/ledger/LedgerMaster.h>
#include <jbcoin/ledger/ReadView.h>
#include <jbcoin/json/Object.h>
#include <jbcoin/protocol/JsonFields.h>
#include <jbcoin/rpc/Context.h>
#include <jbcoin/rpc/Status.h>
#include <jbcoin/rpc/impl/Handler.h>
#include <jbcoin/rpc/Role.h>

namespace Json {
class Object;
}

namespace jbcoin {
namespace RPC {

struct Context;

// ledger [id|index|current|closed] [full]
// {
//    ledger: 'current' | 'closed' | <uint256> | <number>,  // optional
//    full: true | false    // optional, defaults to false.
// }

class LedgerHandler {
public:
    explicit LedgerHandler (Context&);

    Status check ();

    template <class Object>
    void writeResult (Object&);

    static const char* const name()
    {
        return "ledger";
    }

    static Role role()
    {
        return Role::USER;
    }

    static Condition condition()
    {
        return NO_CONDITION;
    }

private:
    Context& context_;
    std::shared_ptr<ReadView const> ledger_;
    std::vector<TxQ::TxDetails> queueTxs_;
    Json::Value result_;
    int options_ = 0;
    LedgerEntryType type_;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Implementation.

template <class Object>
void LedgerHandler::writeResult (Object& value)
{
    if (ledger_)
    {
        Json::copyFrom (value, result_);
        addJson (value, {*ledger_, options_, queueTxs_, type_});
    }
    else
    {
        auto& master = context_.app.getLedgerMaster ();
        {
            auto&& closed = Json::addObject (value, jss::closed);
            addJson (closed, {*master.getClosedLedger(), 0});
        }
        {
            auto&& open = Json::addObject (value, jss::open);
            addJson (open, {*master.getCurrentLedger(), 0});
        }
    }
}

} // RPC
} // jbcoin

#endif
