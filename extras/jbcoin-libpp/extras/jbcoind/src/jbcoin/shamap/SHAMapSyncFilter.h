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

#ifndef JBCOIN_SHAMAP_SHAMAPSYNCFILTER_H_INCLUDED
#define JBCOIN_SHAMAP_SHAMAPSYNCFILTER_H_INCLUDED

#include <jbcoin/shamap/SHAMapNodeID.h>
#include <jbcoin/shamap/SHAMapTreeNode.h>

/** Callback for filtering SHAMap during sync. */
namespace jbcoin {

class SHAMapSyncFilter
{
public:
    virtual ~SHAMapSyncFilter () = default;
    SHAMapSyncFilter() = default;
    SHAMapSyncFilter(SHAMapSyncFilter const&) = delete;
    SHAMapSyncFilter& operator=(SHAMapSyncFilter const&) = delete;

    // Note that the nodeData is overwritten by this call
    virtual void gotNode (bool fromFilter,
                          SHAMapHash const& nodeHash,
                          Blob&& nodeData,
                          SHAMapTreeNode::TNType type) const = 0;

    virtual
    boost::optional<Blob>
    getNode(SHAMapHash const& nodeHash) const = 0;
};

}

#endif
