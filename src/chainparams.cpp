// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The BIOA3 developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h" 
#include "chainparams.h"
#include "consensus/merkle.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h" 

#include <assert.h>

#include <boost/assign/list_of.hpp>
#include <limits>


struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("00000cac69b815ae0d79aa645e46d897f744c1e085f89df15e46315454c1cec5"))
	(50, uint256("0000013ebd17cb85bfc36dd40a3a214a99d127c88dfacb9cb3db004623af952f"))
    (100, uint256("00000031e3ebed2ddd2d9094d87ad8be60d0cfce3cdae8119af06a171afe6b8c"))
    (500, uint256("77bd17d04f886ea3e3ae93536f8882abbf75f22687446c3be4c01c11debd974e"))
    (1000, uint256("440ca1a6969850208a5dbaa17faef1b4a20a530ea8b211bb8829806c1cc4d540"))
    (2500, uint256("fd0ae2ec4e08c8cd13ada7d4fe9195c62dba498a99d08f4c245ab53086005bb5"))
    (5000, uint256("f605c20da693b1cab29d006fb92aa0a3b76db80e4399fb70db69c0f39fc8070b"))
	(10000, uint256("2f5ea194b20b75810cabf56fb0b24e72fe960d6742ea67678f2b4ba6589cd6de"))
    (20000, uint256("66b79d9c94b90099ac97f8dccd545b3fb7599097d1bb21035a9dce0c664a7c52"))
    (40000, uint256("6b037fc76de617e527c2b15de13bb728cd4c5efcb8da24b30f0a64f840e31c70"))
	(100000, uint256("5f52f0ea6933d57a083fb46250df9d181a3e7bf3cb53aa31ca39100147e78527"))
    /*(200000, uint256(""))*/
    //(400000, uint256(""))
    ;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1620012225, // * UNIX timestamp of last checkpoint block
    5116987,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("00000cac69b815ae0d79aa645e46d897f744c1e085f89df15e46315454c1cec5"))
	(50, uint256("000000d75277a267284cdda9e480e714fdc8a301c4d4c6905bc7cb63c211c900"))
    (100, uint256("0000009306f8cb5e4d9ba198f9895db0642924737efe9f9f81f760c5c97d6eb1"))
    (500, uint256("ecfe31715d0ddea5d4fc833e3717a444deeed142c680e9fa634f0883cac46407"))
    (1000, uint256("3ff183253f4bcc4c41a7f34ebdf1ca78b25438a3e7187ce68ddecf3dc6a6b42c")) 
    (2500, uint256("b919892bde6cf2dd26ad632a78dcb2d6f36b303ff36af1e140be50faadb84f5e"))
    (5000, uint256("7ae83f6a5d29c1b9ccc4513b4ba3189b2cd35d7a917be807c4f4416bfe971efc"))
	(10000, uint256("3b81c5ff6c1f6594b38507b186228a811688a3c81ab17b5443856806c0b9fd67"))
    (20000, uint256("60c2849d1a49eb13ae3433f9a43cb3a0c0ee9cf7735f27286c0fb8dcf78dd400"))
    (40000, uint256("96d842f5c6d670b9cd2a6e83e38b7da24dfd3f7bb050d3e094c41ca436c5b8d5"))    
	(100000, uint256("14a9366c64fa40d2f797dbc94678d082d267cff44f8b63773f8dd58ba6ad4f45"))
    /*(200000, uint256(""))*/
    //(400000, uint256("")) 
    ;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1620927615,
    5116987,
    2000};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1613860282,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

bool CChainParams::HasStakeMinAgeOrDepth(const int contextHeight, const uint32_t contextTime,
        const int utxoFromBlockHeight, const uint32_t utxoFromBlockTime) const
{
    // before stake modifier V2, the age required was 60 * 60 (1 hour). Not required for regtest
    if (!IsStakeModifierV2(contextHeight))
        return NetworkID() == CBaseChainParams::REGTEST || (utxoFromBlockTime + nStakeMinAge <= contextTime);

    // after stake modifier V2, we require the utxo to be nStakeMinDepth deep in the chain
    return (contextHeight - utxoFromBlockHeight >= nStakeMinDepth);
}

int CChainParams::FutureBlockTimeDrift(const int nHeight) const
{
    if (IsTimeProtocolV2(nHeight))
        // PoS (TimeV2): 14 seconds
        return TimeSlotLength() - 1;

    // PoS (TimeV1): 3 minutes
    // PoW: 2 hours
    return (nHeight > LAST_POW_BLOCK()) ? nFutureTimeDriftPoS : nFutureTimeDriftPoW;
}

bool CChainParams::IsValidBlockTimeStamp(const int64_t nTime, const int nHeight) const
{
    // Before time protocol V2, blocks can have arbitrary timestamps
    if (!IsTimeProtocolV2(nHeight))
        return true;

    // Time protocol v2 requires time in slots
    return (nTime % TimeSlotLength()) == 0;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x93;
        pchMessageStart[1] = 0xcb;
        pchMessageStart[2] = 0xff;
        pchMessageStart[3] = 0xeb;
        vAlertPubKey = ParseHex("044a5b63e90bc54aaa8a00b91c441598ceed219fb9aa7d0c27b59c075dace8aa373b16e5d2fc6a019b95acf08f83bf364660da2bead59071eef9a358c31337513b");
        nDefaultPort = 41372;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // BIOA3 starting difficulty is 1 / 2^12
        bnProofOfStakeLimit = ~uint256(0) >> 24;
        bnProofOfStakeLimit_V2 = ~uint256(0) >> 20; // 60/4 = 15 ==> use 2**4 higher limit
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetSpacing = 1 * 60;                        // 1 minute
        nTargetTimespan = 40 * 60;                      // 40 minutes
        nTimeSlotLength = 15;                           // 15 seconds
        nTargetTimespan_V2 = 2 * nTimeSlotLength * 60;  // 30 minutes
        nMaturity = 100;
        nStakeMinAge = 60 * 60;                         // 1 hour
        nStakeMinDepth = 100;
        nFutureTimeDriftPoW = 7200;
        nFutureTimeDriftPoS = 180;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 0x7FFFFFFFFFFFFFFF;
        nMinColdStakingAmount = 1 * COIN;
        nMNCollateral = 100000 * COIN;
        strBackboneAddr = "BShVFT2CozqJUwBxk6YMUKbTVZ73k1qnoV";

        /** Height or Time Based Activations **/
        nLastPOWBlock = 400;
        nBioA3BadBlockTime = 1471401614; // Skip nBit validation of Block 259201 per PR #915
        nBioA3BadBlocknBits = 0x1c056dac; // Skip nBit validation of Block 259201 per PR #915
        nModifierUpdateBlock = 401;
        nZerocoinStartHeight = 401;
        nZerocoinStartTime = 1577858523; // January 01, 2020 6:02:00 AM
        nBlockEnforceSerialRange = 401; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 401; //Trigger a recalculation of accumulators 
        nBlockFirstFraudulent = 401; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 401; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 401; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0;
        nBlockZerocoinV2 = 401; //!> The block that zerocoin v2 becomes active
        nBlockDoubleAccumulated = 401;
        nEnforceNewSporkKey = 1566860400; //!> Sporks signed after Monday, August 26, 2019 11:00:00 PM GMT must use the new spork key
        nRejectOldSporkKey = 1569538800; //!> Fully reject old spork key after Thursday, September 26, 2019 11:00:00 PM GMT
        nBlockStakeModifierlV2 = 401;
        nBIP65ActivationHeight = 401;
        nBlockTimeProtocolV2 = 401;
        nPublicZCSpends = 401;

        // New P2P messages signatures
        nBlockEnforceNewMessageSignatures = nBlockTimeProtocolV2;

        // Blocks v7
        nBlockLastAccumulatorCheckpoint = 401;
        nBlockV7StartHeight = nBlockTimeProtocolV2;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;
        nSupplyBeforeFakeSerial = 0 * COIN;   // zerocoin supply at block nFakeSerialBlockheightEnd

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         */
        const char* pszTimestamp = "Wall Street Charging Bull sculptor Arturo Di Modica 'dies aged 80': Feb 20, 2021";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0435a30786824c2f78fbae675df68b0fa13f4f86e5739d813f8cbb8b1d64fffe2de4f44ecadcd37a905a29d89e0f32e1c6a2efd378a2bbfcfe103111f4abae568d") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
        genesis.nVersion = 1;
        genesis.nTime = 1613860282;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 2816219;         

        hashGenesisBlock = genesis.GetHash();
		
		/*if(genesis.GetHash() != uint256("0x"))
		{
			  printf("MSearching for genesis block...\n");
			  uint256 hashTarget;
			  hashTarget.SetCompact(genesis.nBits);
			  while(uint256(genesis.GetHash()) > uint256(hashTarget))
			  {
				  ++genesis.nNonce;
				  if (genesis.nNonce == 0)
				  {
					  printf("Mainnet NONCE WRAPPED, incrementing time");
					  std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
					  ++genesis.nTime;
				  }
				  if (genesis.nNonce % 10000 == 0)
				  {
					  printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
				  }
			  }
			  printf("Mainnet block.nTime = %u \n", genesis.nTime);
			  printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
			  printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
			  printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
		}*/
         
        assert(hashGenesisBlock == uint256("0x00000cac69b815ae0d79aa645e46d897f744c1e085f89df15e46315454c1cec5"));
        assert(genesis.hashMerkleRoot == uint256("0x3fcb473c5a16b254309ae3b39a3a6f2301bce8a836eea3f1e4d2d3afc568c3b9"));

        vSeeds.push_back(CDNSSeedData("bioa3.org", "seed01.bioa3.org")); // Primary DNS Seeder from EcoZion
        vSeeds.push_back(CDNSSeedData("bioa3.org", "seed02.bioa3.org")); // Primary DNS Seeder from EcoZion
        vSeeds.push_back(CDNSSeedData("bioa3.org", "seed03.bioa3.org")); // Primary DNS Seeder from EcoZion
        vSeeds.push_back(CDNSSeedData("bioa3.org", "seed04.bioa3.org")); // Primary DNS Seeder from EcoZion
        vSeeds.push_back(CDNSSeedData("bioa3.org", "seed05.bioa3.org")); // Primary DNS Seeder from EcoZion
        vSeeds.push_back(CDNSSeedData("bioa3.org", "seed06.bioa3.org")); // Primary DNS Seeder from EcoZion

        //vSeeds.push_back(CDNSSeedData("bioa3.org", "seed07.bioa3.org")); // Primary DNS Seeder from EcoZion
        //vSeeds.push_back(CDNSSeedData("bioa3.org", "seed08.bioa3.org")); // Primary DNS Seeder from EcoZion
        //vSeeds.push_back(CDNSSeedData("bioa3.org", "seed09.bioa3.org")); // Primary DNS Seeder from EcoZion
        //vSeeds.push_back(CDNSSeedData("bioa3.org", "seed10.bioa3.org")); // Primary DNS Seeder from EcoZion

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63);     // starting with 'S'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = true;

        nPoolMaxTransactions = 3;
        nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
        strSporkPubKey = "0497081eb58060f9a70fd4cd0324178f825bbc1f49e1e14151b29eba9c73039daf6d08373a7a50ecd3964fdbf0b6c91067d14f974b85189550aa272bc44eafc647";
        strSporkPubKeyOld = "04219e6618b15a0339adadeee219d9115f769a8e8e33bf8b44447a05c0b64f4ec2c391bc6b7f769e21c57bba5c60f355789c3d41130a49470429ac4937448074ff";
        strObfuscationPoolDummyAddress = "D87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMaxZerocoinPublicSpendsPerTransaction = 637; // Assume about 220 bytes each input
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zbioa3 to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("049ca19936c46d286676ca27002105cdc5921fe5d2d6fb98cd2d4a143e4f5d37601ebc380595772bef6618e45ade567c905b4c7ce51d47a734dd8ade38412a8dcc");
        nDefaultPort = 41374;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nLastPOWBlock = 400;
        nBioA3BadBlockTime = 1489001494; // Skip nBit validation of Block 259201 per PR #915
        nBioA3BadBlocknBits = 0x1e0a20bd; // Skip nBit validation of Block 201 per PR #915
        nMaturity = 15;
        nStakeMinDepth = 100;
        nMasternodeCountDrift = 4;
        //nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nModifierUpdateBlock = 401;
        nMaxMoneyOut = 0x7FFFFFFFFFFFFFFF;
        nMinColdStakingAmount = 1 * COIN;
        nMNCollateral = 100000 * COIN;
        strBackboneAddr = "y8caddAXUpTXhSTirKDivi2uvh6BRhpYUZ";

        //nZerocoinStartHeight = 201576;
        nZerocoinStartHeight = 401;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 401; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 401; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 401; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 401; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 401; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 401; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1566860400; //!> Sporks signed after Monday, August 26, 2019 11:00:00 PM GMT must use the new spork key
        nRejectOldSporkKey = 1569538800; //!> Reject old spork key after Thursday, September 26, 2019 11:00:00 PM GMT
        nBlockStakeModifierlV2 = 401;
        nBIP65ActivationHeight = 401;
        // Activation height for TimeProtocolV2, Blocks V7 and newMessageSignatures
        //nBlockTimeProtocolV2 = 1347000;
        nBlockTimeProtocolV2 = 401;

        // Public coin spend enforcement
        nPublicZCSpends = 401;

        // New P2P messages signatures
        nBlockEnforceNewMessageSignatures = nBlockTimeProtocolV2;

        // Blocks v7
        nBlockLastAccumulatorCheckpoint = nPublicZCSpends - 10;
        nBlockV7StartHeight = nBlockTimeProtocolV2;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;
        nSupplyBeforeFakeSerial = 0;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.

		
        genesis.nTime = 1613860282;
        genesis.nNonce = 2816219;   

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000cac69b815ae0d79aa645e46d897f744c1e085f89df15e46315454c1cec5"));
		
        vFixedSeeds.clear();
        vSeeds.clear();
        
        vSeeds.push_back(CDNSSeedData("bioa3.org", "testseed01.bioa3.org")); // Primary DNS Seeder from EcoZion
        vSeeds.push_back(CDNSSeedData("bioa3.org", "testseed02.bioa3.org")); // Primary DNS Seeder from EcoZion
        vSeeds.push_back(CDNSSeedData("bioa3.org", "testseed03.bioa3.org")); // Primary DNS Seeder from EcoZion
        vSeeds.push_back(CDNSSeedData("bioa3.org", "testseed04.bioa3.org")); // Primary DNS Seeder from EcoZion
        vSeeds.push_back(CDNSSeedData("bioa3.org", "testseed05.bioa3.org")); // Primary DNS Seeder from EcoZion
        vSeeds.push_back(CDNSSeedData("bioa3.org", "testseed06.bioa3.org")); // Primary DNS Seeder from EcoZion

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet pivx addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet pivx script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet pivx BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet pivx BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet pivx BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
        
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        nBudgetCycleBlocks = 144; //!< Ten cycles per day on testnet
        strSporkPubKey = "04bf8e29dfe9fa58db660c088fe23f99a08d67d7e56316d49594bcb68d53eebe3e2bdd19e44e86e266320fa2060bf063cc5d7010226ebbf71aae14babc344a0600";
        strSporkPubKeyOld = "04745cb524aaa912d8fe15c8ce840504200fc76bc09169b7bfb3d982ca27bec51c90e007e004ee942b3058ef4d926bc5ae64462ea95592d2f565b73a2bbd602518";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nProposalEstablishmentTime = 60 * 5; // Proposals must be at least 5 mns old to make it into a test budget
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 51476;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nLastPOWBlock = 250;
        nMaturity = 100;
        nStakeMinAge = 0;
        nStakeMinDepth = 0;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0;
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 300;
        nBlockZerocoinV2 = 300;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1;               // Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999;  // Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999;          // First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999;       // Last valid accumulator checkpoint
        nBlockStakeModifierlV2 = nLastPOWBlock + 1; // start with modifier V2 on testnet
        nBlockTimeProtocolV2 = 999999999;

        nMintRequiredConfirmations = 10;
        nZerocoinRequiredStakeDepth = nMintRequiredConfirmations;

        // Public coin spend enforcement
        nPublicZCSpends = 400;

        // Blocks v7
        nBlockV7StartHeight = nPublicZCSpends + 1;
        nBlockLastAccumulatorCheckpoint = nPublicZCSpends - 10;

        // New P2P messages signatures
        nBlockEnforceNewMessageSignatures = 1;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;

        //! Modify the regtest genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1613860282;
        genesis.nNonce = 2816219;      

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000cac69b815ae0d79aa645e46d897f744c1e085f89df15e46315454c1cec5"));
        
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933debioa38162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;

static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
