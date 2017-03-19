// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x25;
        pchMessageStart[1] = 0x04;
        pchMessageStart[2] = 0x24;
        pchMessageStart[3] = 0x09;
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 54371;
        nRPCPort = 54372;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "The best suburb to live, Also the best Ba-Mi";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1489232382, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1489232382;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1603190;

		// uncomment to log genesis block info        
        //  start
//        if (true && genesis.GetHash() != hashGenesisBlock)
//                       {
//                           printf("Searching for genesis block...\n");
//                           uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
//                           uint256 thash;
//
//                           while (true)
//                           {
//                               thash = genesis.GetHash();
//                               if (thash <= hashTarget)
//                                   break;
//                               if ((genesis.nNonce & 0xFFF) == 0)
//                               {
//                                  printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
//                               }
//                               ++genesis.nNonce;
//                               if (genesis.nNonce == 0)
//                               {
//                                   printf("NONCE WRAPPED, incrementing time\n");
//                                   ++genesis.nTime;
//                               }
//                           }
//                           printf("genesis.nTime = %u \n", genesis.nTime);
//                           printf("genesis.nNonce = %u \n", genesis.nNonce);
//                           printf("genesis.nVersion = %u \n", genesis.nVersion);
//                           //printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
//                           printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root
//
//                       }
//
//        //end
		
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000de54f7634ed9918c51ed9d19d44a8508b468658d794f6dd94afea7bcd55"));
        assert(genesis.hashMerkleRoot == uint256("0xf3d70d50c8cca6c4ae95d74b461b6913dda8d64bf97cc37f76bde8ea5c68adf0"));


        vSeeds.push_back(CDNSSeedData("seed.mnc.cryptooz.com", "seed.mnc.cryptooz.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 40);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 27);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 125);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 100;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x3b;
        pchMessageStart[1] = 0x1c;
        pchMessageStart[2] = 0x2b;
        pchMessageStart[3] = 0xe6;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 154371;
        nRPCPort = 154372;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 60176;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x00000de54f7634ed9918c51ed9d19d44a8508b468658d794f6dd94afea7bcd55"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 100;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        return false;
    }

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
