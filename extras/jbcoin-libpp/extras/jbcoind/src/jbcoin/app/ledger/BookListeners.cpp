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

#include <BeastConfig.h>
#include <jbcoin/app/ledger/OrderBookDB.h>
#include <jbcoin/app/misc/NetworkOPs.h>
#include <jbcoin/json/to_string.h>

namespace jbcoin {

void
BookListeners::addSubscriber(InfoSub::ref sub)
{
    std::lock_guard<std::recursive_mutex> sl(mLock);
    mListeners[sub->getSeq()] = sub;
}

void
BookListeners::removeSubscriber(std::uint64_t seq)
{
    std::lock_guard<std::recursive_mutex> sl(mLock);
    mListeners.erase(seq);
}

void
BookListeners::publish(
    Json::Value const& jvObj,
    hash_set<std::uint64_t>& havePublished)
{
    std::lock_guard<std::recursive_mutex> sl(mLock);
    auto it = mListeners.cbegin();

    while (it != mListeners.cend())
    {
        InfoSub::pointer p = it->second.lock();

        if (p)
        {
            // Only publish jvObj if this is the first occurence
            if(havePublished.emplace(p->getSeq()).second)
            {
                p->send(jvObj, true);
            }
            ++it;
        }
        else
            it = mListeners.erase(it);
    }
}

}  // namespace jbcoin
