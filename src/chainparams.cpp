// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017-2020 The Sheet Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>
#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint64_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << CScriptNum(0) << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint64_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "The Times 03/10/2021 Housing Boss Earns 1 Million to Run Shelters Despite a Troubled Past";
    const CScript genesisOutputScript = CScript() << ParseHex("04897db9262dbc1a81bd6930f98057f9bcc6ca681368f6a2d4b715bdaa6a4f9c5e70026c306521bf9d7f3207a856cfbc1edfba71d35d4256e7033c175bf5984a4f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

void CChainParams::TurnOffSegwit() {
	consensus.nSegwitEnabled = false;
}

void CChainParams::TurnOffCSV() {
	consensus.nCSVEnabled = false;
}

void CChainParams::TurnOffBIP34() {
	consensus.nBIP34Enabled = false;
}

void CChainParams::TurnOffBIP65() {
	consensus.nBIP65Enabled = false;
}

void CChainParams::TurnOffBIP66() {
	consensus.nBIP66Enabled = false;
}

bool CChainParams::BIP34() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP65() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP66() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::CSVEnabled() const{
	return consensus.nCSVEnabled;
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
        consensus.nSubsidyHalvingInterval = 622080;
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true;
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.powLimit = uint256S("0x0fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60;
        consensus.nPowTargetSpacing = 1 * 50;
	    consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1613;
        consensus.nMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230768001;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1633219201;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1664755201;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1633219201;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1664755201;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1714;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 1633219201;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1664755201;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 1714;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1633219201;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1664755201;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 1633219201;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1664755201;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 1411;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 2016;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000a17ab845ed2e");
        consensus.defaultAssumeValid = uint256S("0x000000000263747bc47d4d18016a4d52e36d7e7bf37ccd4a106881f18d0a668c");

        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x48;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x58;
        nDefaultPort = 9943;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1633219211, 4891505, 0x1e00ffff, 4, 10 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000000220f2f100b4a68af5fa2aa7177d7e989292ee9db57daac4da9bf6f848d"));
        assert(genesis.hashMerkleRoot == uint256S("0x1f7e67c97f6d81a7e36ed825d76f6fdff3fa7c11050f182a083a989ad49859c3"));

        vSeeds.emplace_back("mainnet-seeds.sheetproject.org", false);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,122);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        nExtCoinType = 225;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {
                { 0, uint256S("0x000000220f2f100b4a68af5fa2aa7177d7e989292ee9db57daac4da9bf6f848d")},
                { 100, uint256S("0x00000005404e3aa577d73289f0aed075acbcec94ccaa2b90e1d84a3223d1af37")},
                { 200, uint256S("0x00000001799ee448153bb208560469cd0cadd2b85d8d7e0ce6eb7df0a3288f86")},
                { 500, uint256S("0x0000000002369f91bc6630c408e318360717787484b6e347276d25f637ceefe9")},
                { 1000, uint256S("0x0000000007c836805ef4abf000f01068f9043c31830423efe54fec47089b65a2")},
                { 1500, uint256S("0x000000000263747bc47d4d18016a4d52e36d7e7bf37ccd4a106881f18d0a668c")}
            }
        };

        chainTxData = ChainTxData{
            1633435933,
            3322,
            0
        };

        nIssueAssetBurnAmount = 5 * COIN;
        nReissueAssetBurnAmount = 1 * COIN;
        nIssueSubAssetBurnAmount = 1 * COIN;
        nIssueUniqueAssetBurnAmount = 0.05 * COIN;
        nIssueMsgChannelAssetBurnAmount = 1 * COIN;
        nIssueQualifierAssetBurnAmount = 10 * COIN;
        nIssueSubQualifierAssetBurnAmount = 1 * COIN;
        nIssueRestrictedAssetBurnAmount = 15 * COIN;
        nAddNullQualifierTagBurnAmount = .001 * COIN;

        strIssueAssetBurnAddress = "SheetCreateAssetXXXXXXXXXXXXXzvzfK";
        strReissueAssetBurnAddress = "SheetRecreateAssetXXXXXXXXXXXnYD3e";
        strIssueSubAssetBurnAddress = "SheetCreateSubassetXXXXXXXXXY3uXrx";
        strIssueUniqueAssetBurnAddress = "SheetCreateUniqueAssetXXXXXXUtLgEV";
        strIssueMsgChannelAssetBurnAddress = "SheetCreateMessageAssetXXXXXaXebeQ";
        strIssueQualifierAssetBurnAddress = "SheetCreateModifierXXXXXXXXXVm8ZCz";
        strIssueSubQualifierAssetBurnAddress = "SheetCreateSubmodifierXXXXXXYqsiER";
        strIssueRestrictedAssetBurnAddress = "SheetCreateRestrictedAssetXXXoazvM";
        strAddNullQualifierTagBurnAddress = "SheetCreateTagXXXXXXXXXXXXXXSLsNpq";

        strGlobalBurnAddress = "SheetGenericBurnXXXXXXXXXXXXbwyLPi";

        nMaxReorganizationDepth = 60;
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12;

        nAssetActivationHeight = 0;
        nMessagingActivationBlock = 0;
        nRestrictedActivationBlock = 0;
    }
};

/**
 * Testnet (v7)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 622080;
        consensus.nBIP34Enabled = true; 
        consensus.nBIP65Enabled = true;
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.powLimit = uint256S("0x0fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60;
        consensus.nPowTargetSpacing = 1 * 50;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1310;
        consensus.nMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145621;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230768021;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 5;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1633219221;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1664755221;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1633219221;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1664755221;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 1633219221;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1664755221;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1633219221;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1664755221;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 1633219221;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1664755221;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 1411;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 2016;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000001000100");
        consensus.defaultAssumeValid = uint256S("0x000000229652bfa0f1e94825acfc8d18d91df228ae202caec50464d970052528");

        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x48;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x54;
        nDefaultPort = 19943;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1633219231, 25658351, 0x1e00ffff, 2, 10 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000000229652bfa0f1e94825acfc8d18d91df228ae202caec50464d970052528"));
        assert(genesis.hashMerkleRoot == uint256S("0x1f7e67c97f6d81a7e36ed825d76f6fdff3fa7c11050f182a083a989ad49859c3"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.emplace_back("testnet-seeds.sheetproject.org", false);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        nExtCoinType = 125;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {
                    { 0, uint256S("0x000000229652bfa0f1e94825acfc8d18d91df228ae202caec50464d970052528")}
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        nIssueAssetBurnAmount = 5 * COIN;
        nReissueAssetBurnAmount = 1 * COIN;
        nIssueSubAssetBurnAmount = 1 * COIN;
        nIssueUniqueAssetBurnAmount = 0.05 * COIN;
        nIssueMsgChannelAssetBurnAmount = 1 * COIN;
        nIssueQualifierAssetBurnAmount = 10 * COIN;
        nIssueSubQualifierAssetBurnAmount = 1 * COIN;
        nIssueRestrictedAssetBurnAmount = 15 * COIN;
        nAddNullQualifierTagBurnAmount = .001 * COIN;

        strIssueAssetBurnAddress = "TestnetCreateAssetXXXXXXXXXXXLt4Va";
        strReissueAssetBurnAddress = "TestnetRecreateAssetXXXXXXXXb9qmHD";
        strIssueSubAssetBurnAddress = "TestnetCreateSubassetXXXXXXXWVvDAc";
        strIssueUniqueAssetBurnAddress = "TestnetCreateUniqueAssetXXXXb6sxBD";
        strIssueMsgChannelAssetBurnAddress = "TestnetCreateMessageAssetXXXWD6ofe";
        strIssueQualifierAssetBurnAddress = "TestnetCreateModifierXXXXXXXX2H18e";
        strIssueSubQualifierAssetBurnAddress = "TestnetCreateSubmodifierXXXXZ1NKwx";
        strIssueRestrictedAssetBurnAddress = "TestnetCreateRestrictedAssetap2f1R";
        strAddNullQualifierTagBurnAddress = "TestnetCreateTagXXXXXXXXXXXXX9j73U";

        strGlobalBurnAddress = "TestnetGenericBurnXXXXXXXXXXTzLGbr";

        nMaxReorganizationDepth = 60;
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12;

        nAssetActivationHeight = 0;
        nMessagingActivationBlock = 0;
        nRestrictedActivationBlock = 0;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 51840;
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true;
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.powLimit = uint256S("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60;
        consensus.nPowTargetSpacing = 1 * 50;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108;
        consensus.nMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 208;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 288;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 400;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 500;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000002");
        consensus.defaultAssumeValid = uint256S("0x60beb5fb3e75d7f06e4cd504301950fdd5262434ae40901339ed59e8113e8030");

        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x48;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x52;
        nDefaultPort = 29943;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1633219251, 1, 0x207fffff, 4, 10 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x60beb5fb3e75d7f06e4cd504301950fdd5262434ae40901339ed59e8113e8030"));
        assert(genesis.hashMerkleRoot == uint256S("1f7e67c97f6d81a7e36ed825d76f6fdff3fa7c11050f182a083a989ad49859c3"));

        vFixedSeeds.clear();
        vSeeds.clear();

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
                { 0, uint256S("0x60beb5fb3e75d7f06e4cd504301950fdd5262434ae40901339ed59e8113e8030")}
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,61);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        nExtCoinType = 25;

        nIssueAssetBurnAmount = 5 * COIN;
        nReissueAssetBurnAmount = 1 * COIN;
        nIssueSubAssetBurnAmount = 1 * COIN;
        nIssueUniqueAssetBurnAmount = 0.05 * COIN;
        nIssueMsgChannelAssetBurnAmount = 1 * COIN;
        nIssueQualifierAssetBurnAmount = 10 * COIN;
        nIssueSubQualifierAssetBurnAmount = 1 * COIN;
        nIssueRestrictedAssetBurnAmount = 15 * COIN;
        nAddNullQualifierTagBurnAmount = .001 * COIN;

        strIssueAssetBurnAddress = "RegtestCreateAssetXXXXXXXXXXXHFcnb";
        strReissueAssetBurnAddress = "RegtestRecreateAssetXXXXXXXXWUeroV";
        strIssueSubAssetBurnAddress = "RegtestCreateSubassetXXXXXXXb1vswu";
        strIssueUniqueAssetBurnAddress = "RegtestCreateUniqueAssetXXXXTJKXL9";
        strIssueMsgChannelAssetBurnAddress = "RegtestCreateMessageAssetXXXTC5Lh1";
        strIssueQualifierAssetBurnAddress = "RegtestCreateModifierXXXXXXXVqm1XD";
        strIssueSubQualifierAssetBurnAddress = "RegtestCreateSubmodifierXXXXYzdeNr";
        strIssueRestrictedAssetBurnAddress = "RegtestCreateRestrictedAssetbAxUkS";
        strAddNullQualifierTagBurnAddress = "RegtestCreateTagXXXXXXXXXXXXUuWw3g";

        strGlobalBurnAddress = "RegtestGenericBurnXXXXXXXXXXVss7Yi";

        nMaxReorganizationDepth = 60;
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12;

        nAssetActivationHeight = 0;
        nMessagingActivationBlock = 0;
        nRestrictedActivationBlock = 0;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &GetParams() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network, bool fForceBlockNetwork)
{
    SelectBaseParams(network);
    if (fForceBlockNetwork) {
        bNetwork.SetNetwork(network);
    }
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}

void TurnOffSegwit(){
	globalChainParams->TurnOffSegwit();
}

void TurnOffCSV() {
	globalChainParams->TurnOffCSV();
}

void TurnOffBIP34() {
	globalChainParams->TurnOffBIP34();
}

void TurnOffBIP65() {
	globalChainParams->TurnOffBIP65();
}

void TurnOffBIP66() {
	globalChainParams->TurnOffBIP66();
}
