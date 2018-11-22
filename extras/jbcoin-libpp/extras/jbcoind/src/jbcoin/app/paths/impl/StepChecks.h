//------------------------------------------------------------------------------
/*
    This file is part of jbcoind: https://github.com/jbcoin/jbcoind
    Copyright (c) 2015 Jbcoin Labs Inc.

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

#ifndef JBCOIN_APP_PATHS_IMPL_STEP_CHECKS_H_INCLUDED
#define JBCOIN_APP_PATHS_IMPL_STEP_CHECKS_H_INCLUDED

#include <jbcoin/basics/Log.h>
#include <jbcoin/beast/utility/Journal.h>
#include <jbcoin/ledger/ReadView.h>
#include <jbcoin/protocol/AccountID.h>
#include <jbcoin/protocol/UintTypes.h>

namespace jbcoin {

inline
TER
checkFreeze (
    ReadView const& view,
    AccountID const& src,
    AccountID const& dst,
    Currency const& currency)
{
    assert (src != dst);

    // check freeze
    if (auto sle = view.read (keylet::account (dst)))
    {
        if (sle->isFlag (lsfGlobalFreeze))
        {
            return terNO_LINE;
        }
    }

    if (auto sle = view.read (keylet::line (src, dst, currency)))
    {
        if (sle->isFlag ((dst > src) ? lsfHighFreeze : lsfLowFreeze))
        {
            return terNO_LINE;
        }
    }

    return tesSUCCESS;
}

inline
TER
checkNoJbcoin (
    ReadView const& view,
    AccountID const& prev,
    AccountID const& cur,
    // This is the account whose constraints we are checking
    AccountID const& next,
    Currency const& currency,
    beast::Journal j)
{
    // fetch the jbcoin lines into and out of this node
    auto sleIn = view.read (keylet::line (prev, cur, currency));
    auto sleOut = view.read (keylet::line (cur, next, currency));

    if (!sleIn || !sleOut)
        return terNO_LINE;

    if ((*sleIn)[sfFlags] &
            ((cur > prev) ? lsfHighNoJbcoin : lsfLowNoJbcoin) &&
        (*sleOut)[sfFlags] &
            ((cur > next) ? lsfHighNoJbcoin : lsfLowNoJbcoin))
    {
        JLOG (j.info()) << "Path violates noJbcoin constraint between " << prev
                      << ", " << cur << " and " << next;

        return terNO_JBCOIN;
    }
    return tesSUCCESS;
}

}

#endif
