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

// This has to be included early to prevent an obscure MSVC compile error
#include <boost/asio/deadline_timer.hpp>

#include <jbcoin/protocol/JsonFields.h>
#include <jbcoin/rpc/RPCHandler.h>
#include <jbcoin/rpc/handlers/Handlers.h>

#include <jbcoin/rpc/handlers/AccountCurrenciesHandler.cpp>
#include <jbcoin/rpc/handlers/AccountInfo.cpp>
#include <jbcoin/rpc/handlers/AccountLines.cpp>
#include <jbcoin/rpc/handlers/AccountChannels.cpp>
#include <jbcoin/rpc/handlers/AccountObjects.cpp>
#include <jbcoin/rpc/handlers/AccountOffers.cpp>
#include <jbcoin/rpc/handlers/AccountTx.cpp>
#include <jbcoin/rpc/handlers/AccountTxOld.cpp>
#include <jbcoin/rpc/handlers/AccountTxSwitch.cpp>
#include <jbcoin/rpc/handlers/BlackList.cpp>
#include <jbcoin/rpc/handlers/BookOffers.cpp>
#include <jbcoin/rpc/handlers/CanDelete.cpp>
#include <jbcoin/rpc/handlers/Connect.cpp>
#include <jbcoin/rpc/handlers/ConsensusInfo.cpp>
#include <jbcoin/rpc/handlers/Feature1.cpp>
#include <jbcoin/rpc/handlers/Fee1.cpp>
#include <jbcoin/rpc/handlers/FetchInfo.cpp>
#include <jbcoin/rpc/handlers/GatewayBalances.cpp>
#include <jbcoin/rpc/handlers/GetCounts.cpp>
#include <jbcoin/rpc/handlers/LedgerHandler.cpp>
#include <jbcoin/rpc/handlers/LedgerAccept.cpp>
#include <jbcoin/rpc/handlers/LedgerCleanerHandler.cpp>
#include <jbcoin/rpc/handlers/LedgerClosed.cpp>
#include <jbcoin/rpc/handlers/LedgerCurrent.cpp>
#include <jbcoin/rpc/handlers/LedgerData.cpp>
#include <jbcoin/rpc/handlers/LedgerEntry.cpp>
#include <jbcoin/rpc/handlers/LedgerHeader.cpp>
#include <jbcoin/rpc/handlers/LedgerRequest.cpp>
#include <jbcoin/rpc/handlers/LogLevel.cpp>
#include <jbcoin/rpc/handlers/LogRotate.cpp>
#include <jbcoin/rpc/handlers/NoJbcoinCheck.cpp>
#include <jbcoin/rpc/handlers/OwnerInfo.cpp>
