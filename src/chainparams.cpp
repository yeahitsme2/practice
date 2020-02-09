// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2018 The Growth Coin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "ISS Tweets Photo Of Miami Prior To Superbowl Kick-Off - 2 Feb 2020";
    const CScript genesisOutputScript = CScript() << ParseHex("049114e2dfc88457dc2b1bfb2b6d751ec1fcabbe0fe4de4a10f416c90b070bb22c0873456e4b2f5199413665b2c3fc965dfeb670477b3a2b163cef9689426885fe") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 60000; // every130k blocks
        consensus.nMasternodePaymentsStartBlock = 2; // block after premine
        consensus.nMasternodePaymentsIncreaseBlock = 158000000; // not used
        consensus.nMasternodePaymentsIncreasePeriod = 576*30; // not used
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 2100000000; // year 10000+
        consensus.nBudgetPaymentsCycleBlocks = 16616;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 2100000000; // year 10000+
        consensus.nSuperblockCycle = 16616;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 227931; // FIX
        consensus.BIP34Hash = uint256S("0x000000000000024b89b42a942fe0d9fea3bb44ab7bd1b19115dd6a759c0808b8"); // FIX
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        //consensus.nPowTargetTimespan = 2 * 60; // Growth: every blocks
        //consensus.nPowTargetSpacing = 2 * 60; // Growth: 2 minutes
        consensus.nPowTargetTimespan = 1 * 60; // Growth: every blocks
        consensus.nPowTargetSpacing = 1 * 60; // Growth: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1523675804; // Aug 17th, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1555459200; // April 17, 2019

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000b64ffc1b4535b3163a60098f187653d7012044d7647439a0f07b825830"); //1938
        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000000b64ffc1b4535b3163a60098f187653d7012044d7647439a0f07b825830"); //1938

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x7a;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0x9e;
        pchMessageStart[3] = 0x4f;
        vAlertPubKey = ParseHex("04f17593e66fe42905300cffe3ef146de8a54c2f809c7ab5b2f2477c394d8285d63b806e5b87b14950e5c9f21c15f3af4be3aa3b55edf0626128c2d0bb3b3fe022");
        //changed default port so it wont conflict with reden
        nDefaultPort = 10300
        nMaxTipAge = 1.5 * 60 * 60; // ~36 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nPruneAfterHeight = 100000;

        //genesis = CreateGenesisBlock(1523764584, 360505, 0x1e0ffff0, 1, 50 * COIN);

        uint32_t nTime = 1581238800;
        uint32_t nNonce = 885106;
        uint32_t nBits = 504365040;
        int32_t nVersion = 1;
        //const CAmount& genesisReward = 50 * COIN;
        const CAmount& genesisReward = 5000 * COIN;
        genesis = CreateGenesisBlock(nTime, nNonce, nBits, nVersion, genesisReward);
        consensus.hashGenesisBlock = genesis.GetHash();
/*
        if(genesis.GetHash() != uint256S("0x"))
            {
                    bool fNegative;
                    bool fOverflow;
                    arith_uint256 bigNum;
                    printf("Searching for genesis block...\n");
                    bigNum.SetCompact(genesis.nBits, &fNegative, &fOverflow);
                    while(UintToArith256(genesis.GetHash()) > bigNum)
                    {
                            ++genesis.nNonce;
                            if (genesis.nNonce == 0)
                            {
                                    printf("NONCE WRAPPED, incrementing time");
                                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                                    ++genesis.nTime;
                            }
                            if (genesis.nNonce % 10000 == 0)
                            {
                                  //  printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                            }
                    }
                    printf("Mainnet block.nBits = %u \n", genesis.nBits);
                    printf("Mainnet block.nTime = %u \n", genesis.nTime);
                    printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
                    printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
                    printf("Mainnet block.GetHash = %s\n", genesis.GetHash().GetHex().c_str());
                    printf("Mainnet block.Merkleroot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
            }
         **/
            //printf("block.hashGenesisBlock = %s\n",consensus.hashGenesisBlock.ToString().c_str());
            //printf("block.hashMerkleRoot = %s\n",genesis.hashMerkleRoot.ToString().c_str());
	    //assert(consensus.hashGenesisBlock == uint256S("0x000000b64ffc1b4535b3163a60098f187653d7012044d7647439a0f07b825830"));
        //assert(genesis.hashMerkleRoot == uint256S("0x96f89d848b498032dbfafc5282fbe48a7acd6856181b13c100b20c45764056c6"));


        vSeeds.clear();
	
	//vSeeds.clear();
	//vFixedSeeds.clear();
        // Growth addresses start with 'G
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,38
        // Growth script addresses start with '7'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,16);
        // Growth private keys start with 'E'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,33);
        // Growth BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Growth BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Growth BIP44 coin type is '5'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "04d329e7e50f57a73f7f4ee4d3b0b5477b77b4e187519ef6e53c6aa4bbd09ab31a3ca7f7c626016f3900108d5aed96ed6095380a8213a7764d009b1e599b058093";
        strMasternodePaymentsPubKey = "04d329e7e50f57a73f7f4ee4d3b0b5477b77b4e187519ef6e53c6aa4bbd09ab31a3ca7f7c626016f3900108d5aed96ed6095380a8213a7764d009b1e599b058093";

        /*checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (    0, uint256S("0x000000b64ffc1b4535b3163a60098f187653d7012044d7647439a0f07b825830"))
            1581238800, // * UNIX timestamp of last checkpoint block
            0,     // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            2800        // * estimated number of transactions per day after checkpoint
        };*/
       checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x000000b64ffc1b4535b3163a60098f187653d7012044d7647439a0f07b825830")),
           1581238800 , // * UNIX timestamp of last checkpoint block
            0,          // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            500	        // * estimated number of transactions per day after checkpoint
        };
            /**  */
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 130000;
        consensus.nMasternodePaymentsStartBlock = 2; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 46000;
        consensus.nMasternodePaymentsIncreasePeriod = 576;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 2100000000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 2100000000; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 21111; // FIX
        consensus.BIP34Hash = uint256S("0x0000000023b3a96d3484e5abb3755c413e7d41500f8e2a5c3f0dd01299cd8ef8"); // FIX
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 1 * 60; // Growth: 1 hour
        //consensus.nPowTargetSpacing = 2 * 60; // Growth: 2 minutes
        consensus.nPowTargetSpacing = 1 * 60; // Growth: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1523923200; // Apr 17, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1555459200; // Apr 17, 2018

        pchMessageStart[0] = 0x70;
        pchMessageStart[1] = 0xb7;
        pchMessageStart[2] = 0x7a;
        pchMessageStart[3] = 0xe4;
        vAlertPubKey = ParseHex("049114e2dfc88457dc2b1bfb2b6d751ec1fcabbe0fe4de4a10f416c90b070bb22c0873456e4b2f5199413665b2c3fc965dfeb670477b3a2b163cef9689426885fe");
        nDefaultPort = 10301;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nPruneAfterHeight = 1000;
        uint32_t nTime =1581238801 ;
        uint32_t nNonce = 2020001;
        uint32_t nBits = 504365040;
        int32_t nVersion = 1;
        //const CAmount& genesisReward = 50 * COIN;
        const CAmount& genesisReward = 5000 * COIN;
        genesis = CreateGenesisBlock(nTime, nNonce, nBits, nVersion, genesisReward);
        //genesis = CreateGenesisBlock(1513728000, 21635, 0x1e0ffff0, 1, 50 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();
        /**if(genesis.GetHash() != uint256S("0x"))
             {
                     bool fNegative;
                     bool fOverflow;
                     arith_uint256 bigNum;
                     printf("Searching for genesis block...\n");
                     bigNum.SetCompact(genesis.nBits, &fNegative, &fOverflow);
                     while(UintToArith256(genesis.GetHash()) > bigNum)
                     {
                             ++genesis.nNonce;
                             if (genesis.nNonce == 0)
                             {
                                     printf("NONCE WRAPPED, incrementing time");
                                     std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                                     ++genesis.nTime;
                             }
                             if (genesis.nNonce % 10000 == 0)
                             {
                                     printf("Testnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                             }
                     }
                     printf("Testnet block.nBits = %u \n", genesis.nBits);
                     printf("Testnet block.nTime = %u \n", genesis.nTime);
                     printf("Testnet block.nNonce = %u \n", genesis.nNonce);
                     printf("Testnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
                     printf("Testnet block.GetHash = %s\n", genesis.GetHash().GetHex().c_str());
                     printf("Testnet block.Merkleroot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
             }
**/

       assert(consensus.hashGenesisBlock == uint256S("0x0000018a84798e0a70f7f198c3d96c2637e720338b9e85fdfe51a09a82435273"));
       assert(genesis.hashMerkleRoot == uint256S("0x96f89d848b498032dbfafc5282fbe48a7acd6856181b13c100b20c45764056c6"));


        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet Growth addresses start with 'R'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,61);
        // Testnet Growth script addresses start with '5'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,10);
        // Testnet private keys start with '5' or 'n' (Bitcoin defaults) (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,33);
        // Testnet Growth BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Growth BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Growth BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "04bd429fcefdd9775510ebb36e824e8184659c72fdc09e4083f129b5de2971032941a43e1114c0da68ece23d5e60dc830fa40b525fb64c2447ed411b4830531a92";
        strMasternodePaymentsPubKey = "04bd429fcefdd9775510ebb36e824e8184659c72fdc09e4083f129b5de2971032941a43e1114c0da68ece23d5e60dc830fa40b525fb64c2447ed411b4830531a92";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x0000018a84798e0a70f7f198c3d96c2637e720338b9e85fdfe51a09a82435273")),
            1581238801, // * UNIX timestamp of last checkpoint block
            0,          // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            500	        // * estimated number of transactions per day after checkpoint
        };
        /** */

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 240;
        consensus.nMasternodePaymentsIncreaseBlock = 350;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 60 * 60; // Growth: 1 hour
        //consensus.nPowTargetSpacing = 2 * 60; // Growth: 2 minutes
        consensus.nPowTargetSpacing = 1 * 60; // Growth: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        pchMessageStart[0] = 0x75;
        pchMessageStart[1] = 0x9e;
        pchMessageStart[2] = 0x4e;
        pchMessageStart[3] = 0xd6;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDefaultPort = 11617;
        nPruneAfterHeight = 1000;
        uint32_t nTime = 1581238802;
        uint32_t nNonce = 240373;
        uint32_t nBits = 545259519;
        int32_t nVersion = 1;
        //const CAmount& genesisReward = 50 * COIN;
        const CAmount& genesisReward = 5000 * COIN;
        genesis = CreateGenesisBlock(nTime, nNonce, nBits, nVersion, genesisReward);
        //genesis = CreateGenesisBlock(1513814400, 3, 0x207fffff, 1, 50 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();
        /**if(genesis.GetHash() != uint256S("0x000006e3cc34e815a71e65082746123924922128e31c60ef2b3e1ccf588595cf"))
             {
                     bool fNegative;
                     bool fOverflow;
                     arith_uint256 bigNum;
                     printf("Searching for genesis block...\n");
                     bigNum.SetCompact(genesis.nBits, &fNegative, &fOverflow);
                     while(UintToArith256(genesis.GetHash()) > bigNum)
                     {
                             ++genesis.nNonce;
                             if (genesis.nNonce == 0)
                             {
                                     printf("NONCE WRAPPED, incrementing time");
                                     std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                                     ++genesis.nTime;
                             }
                             if (genesis.nNonce % 10000 == 0)
                             {
                                 //    printf("RegTestNet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                             }
                     }
                     printf("RegTestNet block.nBits = %u \n", genesis.nBits);
                     printf("RegTestNet block.nTime = %u \n", genesis.nTime);
                     printf("RegTestNet block.nNonce = %u \n", genesis.nNonce);
                     printf("RegTestNet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
                     printf("RegTestNet block.GetHash = %s\n", genesis.GetHash().GetHex().c_str());
                     printf("RegTestNet block.Merkleroot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
             }

         */
        assert(consensus.hashGenesisBlock == uint256S("0x000006e3cc34e815a71e65082746123924922128e31c60ef2b3e1ccf588595cf"));
        assert(genesis.hashMerkleRoot == uint256S("0x96f89d848b498032dbfafc5282fbe48a7acd6856181b13c100b20c45764056c6"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x000006e3cc34e815a71e65082746123924922128e31c60ef2b3e1ccf588595cf")),
            0,
            0,
            0
        };
        // Regtest Growth addresses start with 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        // Regtest Growth script addresses start with '5'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,10);
        // Regtest private keys start with '5' or 'c' (Bitcoin defaults) (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        // Regtest Growth BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Growth BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Regtest Growth BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
