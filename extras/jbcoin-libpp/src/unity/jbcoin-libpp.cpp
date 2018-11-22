//------------------------------------------------------------------------------
/*
    This file is part of jbcoin-libpp: https://github.com/jbcoin/jbcoin-libpp
    Copyright (c) 2016 Jbcoin Labs Inc.

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

#include <jbcoin/protocol/impl/AccountID.cpp>
#include <jbcoin/protocol/impl/Book.cpp>
#include <jbcoin/protocol/impl/BuildInfo.cpp>
#include <jbcoin/protocol/impl/ByteOrder.cpp>
#include <jbcoin/protocol/impl/digest.cpp>
#include <jbcoin/protocol/impl/ErrorCodes.cpp>
#include <jbcoin/protocol/impl/Feature.cpp>
#include <jbcoin/protocol/impl/HashPrefix.cpp>
#include <jbcoin/protocol/impl/Indexes.cpp>
#include <jbcoin/protocol/impl/Issue.cpp>
#include <jbcoin/protocol/impl/Keylet.cpp>
#include <jbcoin/protocol/impl/LedgerFormats.cpp>
#include <jbcoin/protocol/impl/PublicKey.cpp>
#include <jbcoin/protocol/impl/Quality.cpp>
#include <jbcoin/protocol/impl/Rate2.cpp>
#include <jbcoin/protocol/impl/SecretKey.cpp>
#include <jbcoin/protocol/impl/Seed.cpp>
#include <jbcoin/protocol/impl/Serializer.cpp>
#include <jbcoin/protocol/impl/SField.cpp>
#include <jbcoin/protocol/impl/Sign.cpp>
#include <jbcoin/protocol/impl/SOTemplate.cpp>
#include <jbcoin/protocol/impl/TER.cpp>
#include <jbcoin/protocol/impl/tokens.cpp>
#include <jbcoin/protocol/impl/TxFormats.cpp>
#include <jbcoin/protocol/impl/UintTypes.cpp>

#include <jbcoin/protocol/impl/STAccount.cpp>
#include <jbcoin/protocol/impl/STArray.cpp>
#include <jbcoin/protocol/impl/STAmount.cpp>
#include <jbcoin/protocol/impl/STBase.cpp>
#include <jbcoin/protocol/impl/STBlob.cpp>
#include <jbcoin/protocol/impl/STInteger.cpp>
#include <jbcoin/protocol/impl/STLedgerEntry.cpp>
#include <jbcoin/protocol/impl/STObject.cpp>
#include <jbcoin/protocol/impl/STParsedJSON.cpp>
#include <jbcoin/protocol/impl/InnerObjectFormats.cpp>
#include <jbcoin/protocol/impl/STPathSet.cpp>
#include <jbcoin/protocol/impl/STTx.cpp>
#include <jbcoin/protocol/impl/STValidation.cpp>
#include <jbcoin/protocol/impl/STVar.cpp>
#include <jbcoin/protocol/impl/STVector256.cpp>
#include <jbcoin/protocol/impl/IOUAmount.cpp>

#include <jbcoin/basics/impl/contract.cpp>
#include <jbcoin/basics/impl/CountedObject.cpp>
#include <jbcoin/basics/impl/Log.cpp>
#include <jbcoin/basics/impl/strHex.cpp>
#include <jbcoin/basics/impl/StringUtilities.cpp>
#include <jbcoin/basics/impl/Time.cpp>
#include <jbcoin/beast/core/SemanticVersion.cpp>
#include <jbcoin/beast/hash/impl/spookyv2.cpp>
#include <jbcoin/beast/utility/src/beast_Journal.cpp>
#include <jbcoin/crypto/impl/csprng.cpp>
#include <jbcoin/crypto/impl/ec_key.cpp>
#include <jbcoin/crypto/impl/GenerateDeterministicKey.cpp>
#include <jbcoin/crypto/impl/KeyType.cpp>
#include <jbcoin/crypto/impl/openssl.cpp>
#include <jbcoin/crypto/impl/RFC1751.cpp>
#include <jbcoin/json/impl/json_value.cpp>
#include <jbcoin/json/impl/json_valueiterator.cpp>
#include <jbcoin/json/impl/json_reader.cpp>
#include <jbcoin/json/impl/json_writer.cpp>
#include <jbcoin/json/impl/to_string.cpp>

#include <jbcoin/unity/secp256k1.cpp>
/* ed25519_donna.c needs to be built separately because it's C. */
//#include <jbcoin/unity/ed25519_donna.c>
