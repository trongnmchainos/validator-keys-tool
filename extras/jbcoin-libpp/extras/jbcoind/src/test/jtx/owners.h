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

#ifndef JBCOIN_TEST_JTX_OWNERS_H_INCLUDED
#define JBCOIN_TEST_JTX_OWNERS_H_INCLUDED

#include <test/jtx/Env.h>
#include <jbcoin/ledger/View.h>
#include <jbcoin/protocol/LedgerFormats.h>
#include <jbcoin/protocol/UintTypes.h>
#include <cstdint>

namespace jbcoin {
namespace test {
namespace jtx {

namespace detail {

std::uint32_t
owned_count_of (ReadView const& view,
    AccountID const& id,
        LedgerEntryType type);

void
owned_count_helper(Env& env,
    AccountID const& id,
        LedgerEntryType type,
            std::uint32_t value);

} // detail

// Helper for aliases
template <LedgerEntryType Type>
class owner_count
{
private:
    Account account_;
    std::uint32_t value_;

public:
    owner_count (Account const& account,
            std::uint32_t value)
        : account_(account)
        , value_(value)
    {
    }

    void
    operator()(Env& env) const
    {
        detail::owned_count_helper(
            env, account_.id(), Type, value_);
    }
};

/** Match the number of items in the account's owner directory */
class owners
{
private:
    Account account_;
    std::uint32_t value_;
public:
    owners (Account const& account,
            std::uint32_t value)
        : account_(account)
        , value_(value)
    {
    }

    void
    operator()(Env& env) const;
};

/** Match the number of trust lines in the account's owner directory */
using lines = owner_count<ltJBCOIN_STATE>;

/** Match the number of offers in the account's owner directory */
using offers = owner_count<ltOFFER>;

} // jtx
} // test
} // jbcoin

#endif
