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
#include <jbcoin/protocol/TER.h>
#include <jbcoin/beast/unit_test.h>

namespace jbcoin {

struct TER_test : public beast::unit_test::suite
{
    void
    testTransResultInfo()
    {
        for (auto i = -400; i < 400; ++i)
        {
            TER t = static_cast<TER>(i);
            auto inRange = isTelLocal(t) ||
                isTemMalformed(t) ||
                isTefFailure(t) ||
                isTerRetry(t) ||
                isTesSuccess(t) ||
                isTecClaim(t);

            std::string token, text;
            auto good = transResultInfo(t, token, text);
            BEAST_EXPECT(inRange || !good);
            BEAST_EXPECT(transToken(t) == (good ? token : "-"));
            BEAST_EXPECT(transHuman(t) == (good ? text : "-"));

            auto code = transCode(token);
            BEAST_EXPECT(good == !!code);
            BEAST_EXPECT(!code || *code == t);
        }
    }

    void
    run() override
    {
        testTransResultInfo();
    }
};

BEAST_DEFINE_TESTSUITE(TER,protocol,jbcoin);

}
