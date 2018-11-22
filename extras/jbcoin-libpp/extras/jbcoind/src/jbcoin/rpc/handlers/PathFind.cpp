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
#include <jbcoin/app/main/Application.h>
#include <jbcoin/app/misc/NetworkOPs.h>
#include <jbcoin/app/paths/PathRequests.h>
#include <jbcoin/net/RPCErr.h>
#include <jbcoin/protocol/ErrorCodes.h>
#include <jbcoin/protocol/JsonFields.h>
#include <jbcoin/resource/Fees.h>
#include <jbcoin/rpc/Context.h>

namespace jbcoin {

Json::Value doPathFind (RPC::Context& context)
{
    if (context.app.config().PATH_SEARCH_MAX == 0)
        return rpcError (rpcNOT_SUPPORTED);

    auto lpLedger = context.ledgerMaster.getClosedLedger();

    if (!context.params.isMember (jss::subcommand) ||
        !context.params[jss::subcommand].isString ())
    {
        return rpcError (rpcINVALID_PARAMS);
    }

    if (!context.infoSub)
        return rpcError (rpcNO_EVENTS);

    auto sSubCommand = context.params[jss::subcommand].asString ();

    if (sSubCommand == "create")
    {
        context.loadType = Resource::feeHighBurdenRPC;
        context.infoSub->clearPathRequest ();
        return context.app.getPathRequests().makePathRequest (
            context.infoSub, lpLedger, context.params);
    }

    if (sSubCommand == "close")
    {
        PathRequest::pointer request = context.infoSub->getPathRequest ();

        if (!request)
            return rpcError (rpcNO_PF_REQUEST);

        context.infoSub->clearPathRequest ();
        return request->doClose (context.params);
    }

    if (sSubCommand == "status")
    {
        PathRequest::pointer request = context.infoSub->getPathRequest ();

        if (!request)
            return rpcError (rpcNO_PF_REQUEST);

        return request->doStatus (context.params);
    }

    return rpcError (rpcINVALID_PARAMS);
}

} // jbcoin
