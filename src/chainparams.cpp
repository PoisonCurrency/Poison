// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include <fstream>

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

unsigned int pnSeed[] =
{
0xd1dd3eb2,
0x5570aa6b
};

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
        pchMessageStart[0] = 0xca;
        pchMessageStart[1] = 0x22;
        pchMessageStart[2] = 0x3f;
        pchMessageStart[3] = 0x71;
        vAlertPubKey = ParseHex("04044b0114817177e44497e7a42947b3df59e74c171a56d21066d8a6435161d8bf512ee05eb8e51c41a01e9ecf0f635c0fcc46dec04a9ea133495975c65cc779d6");
        nDefaultPort = 38004;
        nRPCPort = 38005;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "May 2015 Poison Masternodes";
        CTransaction txNew;
        txNew.nTime = 1432056785;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1432056785;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact(); 
        genesis.nNonce   = 110584;

        hashGenesisBlock = genesis.GetHash();

/*
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }

        printf("%s\n MAIN ", hashGenesisBlock.ToString().c_str());
        printf("%s\n MAIN ", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n MAIN ", bnProofOfWorkLimit.GetCompact());
        printf("%d\n MAIN ", genesis.nNonce);
*/
        assert(hashGenesisBlock == uint256("0x00002dddd2c53a24a146f404faa04fb2fd4c4f54b2909110b95975a365df7328"));
        assert(genesis.hashMerkleRoot == uint256("0xe841a80f686bac7df850a95bc6c77b04be520068a60a1cd6aff0208b7cfc85d3"));


        vSeeds.push_back(CDNSSeedData("178.62.221.209", "178.62.221.209"));
		vSeeds.push_back(CDNSSeedData("107.170.112.85", "107.170.112.85"));
		
        base58Prefixes[PUBKEY_ADDRESS] = list_of(56);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(81);
        base58Prefixes[SECRET_KEY] =     list_of(121);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xE1)(0x2B);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0x4E)(0xDA);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 2000;

		for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
		
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
        pchMessageStart[0] = 0x2f;
        pchMessageStart[1] = 0xca;
        pchMessageStart[2] = 0x4d;
        pchMessageStart[3] = 0x3e;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04b386050b12b9f32cd7963ac6f92e43588f7cb70061ef6723581aa8f0ee186175638ee087284e56f5fc4aadc7b2e907552f100704817dcaa81c8facc7a0a20cc8");
        nDefaultPort = 32454;
        nRPCPort = 32454;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits    = bnProofOfWorkLimit.GetCompact(); 
        genesis.nNonce = 0;

/*
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }

        printf("%s\n TESTNET ", hashGenesisBlock.ToString().c_str());
        printf("%s\n TESTNET ", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n TESTNET ", bnProofOfWorkLimit.GetCompact());
        printf("%d\n TESTNET ", genesis.nNonce);
*/
        assert(hashGenesisBlock == uint256("0x00002dddd2c53a24a146f404faa04fb2fd4c4f54b2909110b95975a365df7328"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(97);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
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
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
