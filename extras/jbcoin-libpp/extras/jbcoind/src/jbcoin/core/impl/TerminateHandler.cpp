//------------------------------------------------------------------------------
/*
    This file is part of jbcoind: https://github.com/jbcoin/jbcoind
    Copyright (c) 2012 - 2017 Jbcoin Labs Inc.

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
#include <jbcoin/core/TerminateHandler.h>
#include <jbcoin/basics/Log.h>
#include <jbcoin/beast/core/CurrentThreadName.h>

#include <boost/coroutine/exceptions.hpp>
#include <exception>
#include <iostream>
#include <typeinfo>

namespace jbcoin {

void terminateHandler()
{
    if (std::current_exception())
    {
        auto const thName =
            beast::getCurrentThreadName().value_or("Unknown");
        try
        {
            throw;
        }
        catch (const std::exception& e)
        {
            auto exName = typeid (e).name();
            std::cerr
                << "Terminating thread " << thName << ": unhandled "
                << exName << " '" << e.what () << "'\n";
            JLOG(debugLog().fatal())
                << "Terminating thread " << thName << ": unhandled "
                << exName << " '" << e.what () << "'\n";
        }
        catch (boost::coroutines::detail::forced_unwind const&)
        {
            std::cerr
                << "Terminating thread " << thName << ": forced_unwind\n";
            JLOG(debugLog().fatal())
                << "Terminating thread " << thName << ": forced_unwind\n";
        }
        catch (...)
        {
            std::cerr
                << "Terminating thread " << thName << ": unknown exception\n";
            JLOG (debugLog().fatal())
                << "Terminating thread " << thName << ": unknown exception\n";
        }
    }
}

}
