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
#include <jbcoin/app/main/Application.h>
#include <jbcoin/basics/StringUtilities.h>
#include <jbcoin/ledger/ReadView.h>
#include <jbcoin/net/RPCErr.h>
#include <jbcoin/protocol/ErrorCodes.h>
#include <jbcoin/protocol/JsonFields.h>
#include <jbcoin/protocol/PayChan.h>
#include <jbcoin/protocol/STAccount.h>
#include <jbcoin/resource/Fees.h>
#include <jbcoin/rpc/Context.h>
#include <jbcoin/rpc/impl/RPCHelpers.h>
#include <jbcoin/rpc/impl/Tuning.h>

namespace jbcoin {

// {
//   secret_key: <signing_secret_key>
//   channel_id: 256-bit channel id
//   drops: 64-bit uint (as string)
// }
Json::Value doChannelAuthorize (RPC::Context& context)
{
    auto const& params (context.params);
    for (auto const& p : {jss::secret, jss::channel_id, jss::amount})
        if (!params.isMember (p))
            return RPC::missing_field_error (p);

    Json::Value result;
    auto const keypair = RPC::keypairForSignature (params, result);
    if (RPC::contains_error (result))
        return result;

    uint256 channelId;
    if (!channelId.SetHexExact (params[jss::channel_id].asString ()))
        return rpcError (rpcCHANNEL_MALFORMED);

    std::uint64_t drops = 0;
    try
    {
        drops = std::stoul (params[jss::amount].asString ());
    }
    catch (std::exception const&)
    {
        return rpcError (rpcCHANNEL_AMT_MALFORMED);
    }

    Serializer msg;
    serializePayChanAuthorization (msg, channelId, XRPAmount (drops));

    try
    {
        auto const buf = sign (keypair.first, keypair.second, msg.slice ());
        result[jss::signature] = strHex (buf);
    }
    catch (std::exception&)
    {
        result =
            RPC::make_error (rpcINTERNAL, "Exception occurred during signing.");
    }
    return result;
}

// {
//   public_key: <public_key>
//   channel_id: 256-bit channel id
//   drops: 64-bit uint (as string)
//   signature: signature to verify
// }
Json::Value doChannelVerify (RPC::Context& context)
{
    auto const& params (context.params);
    for (auto const& p :
        {jss::public_key, jss::channel_id, jss::amount, jss::signature})
        if (!params.isMember (p))
            return RPC::missing_field_error (p);

    std::string const strPk = params[jss::public_key].asString ();
    auto const pk =
        parseBase58<PublicKey> (TokenType::TOKEN_ACCOUNT_PUBLIC, strPk);
    if (!pk)
        return rpcError (rpcPUBLIC_MALFORMED);

    uint256 channelId;
    if (!channelId.SetHexExact (params[jss::channel_id].asString ()))
        return rpcError (rpcCHANNEL_MALFORMED);

    std::uint64_t drops = 0;
    try
    {
        drops = std::stoul (params[jss::amount].asString ());
    }
    catch (std::exception const&)
    {
        return rpcError (rpcCHANNEL_AMT_MALFORMED);
    }

    std::pair<Blob, bool> sig(strUnHex (params[jss::signature].asString ()));
    if (!sig.second || !sig.first.size ())
        return rpcError (rpcINVALID_PARAMS);

    Serializer msg;
    serializePayChanAuthorization (msg, channelId, XRPAmount (drops));

    Json::Value result;
    result[jss::signature_verified] =
        verify (*pk, msg.slice (), makeSlice (sig.first), /*canonical*/ true);
    return result;
}

} // jbcoin
