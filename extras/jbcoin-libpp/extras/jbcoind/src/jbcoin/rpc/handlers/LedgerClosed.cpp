//------------------------------------------------------------------------------
/*
    This file is part of jbcoind: https://github.com/jbcoin/jbcoind
    Copyright (c) 2012-2014 Jbcoin Labs Inc.

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

#include <BeastConfig.h>
#include <jbcoin/app/ledger/LedgerMaster.h>
#include <jbcoin/app/misc/NetworkOPs.h>
#include <jbcoin/json/json_value.h>
#include <jbcoin/protocol/JsonFields.h>
#include <jbcoin/rpc/Context.h>

namespace jbcoin {

Json::Value doLedgerClosed (RPC::Context& context)
{
    auto ledger = context.ledgerMaster.getClosedLedger ();
    assert (ledger);

    Json::Value jvResult;
    jvResult[jss::ledger_index] = ledger->info().seq;
    jvResult[jss::ledger_hash] = to_string (ledger->info().hash);

    return jvResult;
}

} // jbcoin
