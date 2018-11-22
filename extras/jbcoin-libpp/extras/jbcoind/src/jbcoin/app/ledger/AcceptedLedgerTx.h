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

#ifndef JBCOIN_APP_LEDGER_ACCEPTEDLEDGERTX_H_INCLUDED
#define JBCOIN_APP_LEDGER_ACCEPTEDLEDGERTX_H_INCLUDED

#include <jbcoin/app/ledger/Ledger.h>
#include <jbcoin/protocol/AccountID.h>
#include <boost/container/flat_set.hpp>

namespace jbcoin {

class Logs;

/**
    A transaction that is in a closed ledger.

    Description

    An accepted ledger transaction contains additional information that the
    server needs to tell clients about the transaction. For example,
        - The transaction in JSON form
        - Which accounts are affected
          * This is used by InfoSub to report to clients
        - Cached stuff

    @code
    @endcode

    @see {uri}

    @ingroup jbcoin_ledger
*/
class AcceptedLedgerTx
{
public:
    using pointer = std::shared_ptr <AcceptedLedgerTx>;
    using ref = const pointer&;

public:
    AcceptedLedgerTx (
        std::shared_ptr<ReadView const> const& ledger,
        std::shared_ptr<STTx const> const&,
        std::shared_ptr<STObject const> const&,
        AccountIDCache const&,
        Logs&);
    AcceptedLedgerTx (
        std::shared_ptr<ReadView const> const&,
        std::shared_ptr<STTx const> const&,
        TER,
        AccountIDCache const&,
        Logs&);

    std::shared_ptr <STTx const> const& getTxn () const
    {
        return mTxn;
    }
    std::shared_ptr <TxMeta> const& getMeta () const
    {
        return mMeta;
    }

    boost::container::flat_set<AccountID> const&
    getAffected() const
    {
        return mAffected;
    }

    TxID getTransactionID () const
    {
        return mTxn->getTransactionID ();
    }
    TxType getTxnType () const
    {
        return mTxn->getTxnType ();
    }
    TER getResult () const
    {
        return mResult;
    }
    std::uint32_t getTxnSeq () const
    {
        return mMeta->getIndex ();
    }

    bool isApplied () const
    {
        return bool(mMeta);
    }
    int getIndex () const
    {
        return mMeta ? mMeta->getIndex () : 0;
    }
    std::string getEscMeta () const;
    Json::Value getJson () const
    {
        return mJson;
    }

private:
    std::shared_ptr<ReadView const> mLedger;
    std::shared_ptr<STTx const> mTxn;
    std::shared_ptr<TxMeta> mMeta;
    TER                             mResult;
    boost::container::flat_set<AccountID> mAffected;
    Blob        mRawMeta;
    Json::Value                     mJson;
    AccountIDCache const& accountCache_;
    Logs& logs_;

    void buildJson ();
};

} // jbcoin

#endif