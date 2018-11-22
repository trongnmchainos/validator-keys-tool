![Jbcoin](/images/jbcoin.png)

**Do you work at a digital asset exchange or wallet provider?** 

Please [contact us](mailto:support@jbcoin.com). We can help guide your integration.

# What is Jbcoin?
Jbcoin is a network of computers which use the [Jbcoin consensus algorithm](https://www.youtube.com/watch?v=pj1QVb1vlC0) to atomically settle and record
transactions on a secure distributed database, the Jbcoin Consensus Ledger
(RCL). Because of its distributed nature, the RCL offers transaction immutability
without a central operator. The RCL contains a built-in currency exchange and its
path-finding algorithm finds competitive exchange rates across order books
and currency pairs.

### Key Features
- **Distributed**
  - Direct account-to-account settlement with no central operator
  - Decentralized global market for competitive FX
- **Secure**
  - Transactions are cryptographically signed using ECDSA or Ed25519
  - Multi-signing capabilities
- **Scalable**
  - Capacity to process the world’s cross-border payments volume
  - Easy access to liquidity through a competitive FX marketplace

## Cross-border payments
Jbcoin enables banks to settle cross-border payments in real-time, with
end-to-end transparency, and at lower costs. Banks can provide liquidity
for FX themselves or source it from third parties.

As Jbcoin adoption grows, so do the number of currencies and counterparties.
Liquidity providers need to maintain accounts with each counterparty for
each currency – a capital- and time-intensive endeavor that spreads liquidity
thin. Further, some transactions, such as exotic currency trades, will require
multiple trading parties, who each layer costs to the transaction. Thin
liquidity and many intermediary trading parties make competitive pricing
challenging.

![Flow - Direct](images/flow1.png)

### XRP as a Bridge Currency
Jbcoin can bridge even exotic currency pairs directly through XRP. Similar to
USD in today’s currency market, XRP allows liquidity providers to focus on
offering competitive FX rates on fewer pairs and adding depth to order books.
Unlike USD, trading through XRP does not require bank accounts, service fees,
counterparty risk, or additional operational costs. By using XRP, liquidity
providers can specialize in certain currency corridors, reduce operational
costs, and ultimately, offer more competitive FX pricing.

![Flow - Bridged over XRP](images/flow2.png)

# jbcoind - Jbcoin server
`jbcoind` is the reference server implementation of the Jbcoin
protocol. To learn more about how to build and run a `jbcoind`
server, visit https://jbcoin.com/build/jbcoind-setup/

[![travis-ci.org: Build Status](https://travis-ci.org/jbcoin/jbcoind.png?branch=develop)](https://travis-ci.org/jbcoin/jbcoind)
[![codecov.io: Code Coverage](https://codecov.io/gh/jbcoin/jbcoind/branch/develop/graph/badge.svg)](https://codecov.io/gh/jbcoin/jbcoind)

### License
`jbcoind` is open source and permissively licensed under the
ISC license. See the LICENSE file for more details.

#### Repository Contents

| Folder  | Contents |
|---------|----------|
| ./bin   | Scripts and data files for Jbcoin integrators. |
| ./build | Intermediate and final build outputs.          |
| ./Builds| Platform or IDE-specific project files.        |
| ./doc   | Documentation and example configuration files. |
| ./src   | Source code.                                   |

Some of the directories under `src` are external repositories inlined via
git-subtree. See the corresponding README for more details.

## For more information:

* [Jbcoin Knowledge Center](https://jbcoin.com/learn/)
* [Jbcoin Developer Center](https://jbcoin.com/build/)
* Jbcoin Whitepapers & Reports
  * [Jbcoin Consensus Whitepaper](https://jbcoin.com/files/jbcoin_consensus_whitepaper.pdf)
  * [Jbcoin Solutions Guide](https://jbcoin.com/files/jbcoin_solutions_guide.pdf)

To learn about how Jbcoin is transforming global payments visit
[https://jbcoin.com/contact/](https://jbcoin.com/contact/)

- - -

Copyright © 2017, Jbcoin Labs. All rights reserved.

Portions of this document, including but not limited to the Jbcoin logo,
images and image templates are the property of Jbcoin Labs and cannot be
copied or used without permission.
