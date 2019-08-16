// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2019 The HashShareCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

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
(0, uint256("0x000008948ad86e610b4b29d8627e4490938f3886e1c5ea2b2de5831573656bc5"))
(78, uint256("0x00000011227bf0440bbba6ee7c0b8aae387844e3a04bdf0b9bf9b88f7e878b29"))
(637, uint256("0xbb0b65e10c5ba47014f0ba4225e3114fdc4dc3d1e765c338d4f1933f93a53d2e"))
(1481, uint256("0xa64db28ec351e731c7374ae542aa4eaf36a35c66dc32ddc796197eb64030725b"))
(4101, uint256("0xe4ca8b41251eda001d48f7233a976f81d28071f092da4f7a6b07771480664289"))
(7874, uint256("0x0ed2c229d1147078d9f6fc312e306fbd7ddcccaa4e5a9fc85da184c12b35289a"))
(11521, uint256("0x2d834f612abda894f69239bc1a733b2ae3e74c45fca5aaf67a7305cbc9f457a3"))
(16294, uint256("0x9391e0c68aa13b8bf92d96bd911004b9433af759d651db155745dd0359fac5bd"))

;
static const Checkpoints::CCheckpointData data = {
	&mapCheckpoints,
	1565005733, // * UNIX timestamp of last checkpoint block
	34076,    // * total number of transactions between genesis and last checkpoint
				//   (the tx=... number in the SetBestChain debug.log lines)
	2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
boost::assign::map_list_of
(0, uint256("0x001"))
;
static const Checkpoints::CCheckpointData dataTestnet = {
	&mapCheckpointsTestnet,
	1560843157,
	2501682,
	250 };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
	&mapCheckpointsRegtest,
	1564038000,
	0,
	100 };

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
	assert(this);
	static CBigNum bnDecModulus = 0;
	if (!bnDecModulus)
		bnDecModulus.SetDec(zerocoinModulus);
	static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

	return &ZCParamsDec;
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
		pchMessageStart[0] = 0x7a;
		pchMessageStart[1] = 0xd8;
		pchMessageStart[2] = 0xc7;
		pchMessageStart[3] = 0xe5;
		vAlertPubKey = ParseHex("0000091d3ba6ba6e7423fa2cad6b65e0a9a5348f18b332b24a5cb1a8b7eadc1eaa335fc8dc4f012cb8241cc0bdafd6ca70c5f5448916e4e6f811bcd71ced18da31");
		nDefaultPort = 15112;
		bnProofOfWorkLimit = ~uint256(0) >> 20; // HashShareCoin starting difficulty is 1 / 2^12
		nSubsidyHalvingInterval = 210000;
		nMaxReorganizationDepth = 100;
		nEnforceBlockUpgradeMajority = 8100; // 75%
		nRejectBlockOutdatedMajority = 10260; // 95%
		nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
		nMinerThreads = 0;
		nTargetTimespan = 1 * 60; // HashShareCoin: 1 day
		nTargetSpacing = 1 * 60;  // HashShareCoin: 1 minute
		nMaturity = 61;
		nMasternodeCountDrift = 20;
		nMaxMoneyOut = 200000000 * COIN;

		/** Height or Time Based Activations **/
		nLastPOWBlock = 200;
		nZerocoinStartHeight = 210;
		nZerocoinStartTime = 1564038000;
		nBlockLastGoodCheckpoint = 210; //Last valid accumulator checkpoint
		nBlockZerocoinV2 = 210; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
		nBlockDoubleAccumulated = 0;

		// Public coin spend enforcement
		nPublicZCSpends = 300;

		/**
		 * Build the genesis block. Note that the output of the genesis coinbase cannot
		 * be spent as it did not originally exist in the database.
		 *
		 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
		 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
		 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
		 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
		 *   vMerkleTree: e0028e
		 */
		const char* pszTimestamp = "HSS Masternode Coin.";
		CMutableTransaction txNew;
		txNew.vin.resize(1);
		txNew.vout.resize(1);
		txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		txNew.vout[0].nValue = 250 * COIN;
		txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83b2703bc1265f7dbd1bad5815ac7c10bd055814be121ba32607d573b1d10c02c0582aed15b4deb9c4b77b26d92422a4e256cd42774babeaba073b2ed9a1") << OP_CHECKSIG;
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 3;
		genesis.nAccumulatorCheckpoint = 0;
		genesis.nTime = 1564038000;
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 153033;

		hashGenesisBlock = genesis.GetHash();

		assert(hashGenesisBlock == uint256("0x000008948ad86e610b4b29d8627e4490938f3886e1c5ea2b2de5831573656bc5"));
		assert(genesis.hashMerkleRoot == uint256("0xb5f150d2b9c09bdef05d378ab18e658a98f1da45d8547ef71d9e690f4f21fdf5"));

		vSeeds.push_back(CDNSSeedData("0", "dnsseederhss.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("1", "explorer.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("2", "dnsseed1.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("3", "dnsseed2.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("4", "dnsseed3.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("5", "dnsseed4.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("6", "dnsseed5.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("7", "dnsseed6.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("8", "dnsseed7.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("9", "dnsseed8.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("10", "dnsseed9.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("11", "dnsseed10.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("12", "dnsseed11.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("13", "dnsseed12.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("14", "dnsseed13.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("15", "dnsseed14.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("16", "dnsseed15.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("17", "dnsseed16.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("18", "dnsseed17.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("19", "dnsseed18.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("20", "dnsseed19.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("21", "dnsseed20.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("22", "dnsseed21.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("23", "dnsseed22.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("24", "dnsseed23.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("25", "dnsseed24.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("26", "dnsseed25.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("27", "dnsseed26.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("28", "dnsseed27.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("29", "dnsseed28.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("30", "dnsseed29.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("31", "dnsseed30.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("32", "dnsseed31.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("33", "dnsseed32.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("34", "dnsseed33.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("35", "dnsseed34.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("36", "dnsseed35.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("37", "dnsseed36.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("38", "dnsseed37.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("39", "dnsseed38.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("40", "dnsseed39.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("41", "dnsseed40.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("42", "dnsseed41.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("43", "dnsseed42.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("44", "dnsseed43.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("45", "dnsseed44.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("46", "dnsseed45.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("47", "dnsseed46.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("48", "dnsseed47.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("49", "dnsseed48.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("50", "dnsseed49.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("51", "dnsseed50.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("52", "dnsseed51.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("53", "dnsseed52.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("54", "dnsseed53.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("55", "dnsseed54.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("56", "dnsseed55.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("57", "dnsseed56.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("58", "dnsseed57.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("59", "dnsseed58.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("60", "dnsseed59.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("61", "dnsseed60.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("62", "dnsseed61.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("63", "dnsseed62.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("64", "dnsseed63.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("65", "dnsseed64.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("66", "dnsseed65.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("67", "dnsseed66.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("68", "dnsseed67.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("69", "dnsseed68.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("70", "dnsseed69.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("71", "dnsseed70.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("72", "dnsseed71.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("73", "dnsseed72.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("74", "dnsseed73.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("75", "dnsseed74.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("76", "dnsseed75.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("77", "dnsseed76.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("78", "dnsseed77.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("79", "dnsseed78.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("80", "dnsseed79.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("81", "dnsseed80.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("82", "dnsseed81.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("83", "dnsseed82.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("84", "dnsseed83.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("85", "dnsseed84.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("86", "dnsseed85.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("87", "dnsseed86.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("88", "dnsseed87.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("89", "dnsseed88.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("90", "dnsseed89.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("91", "dnsseed90.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("92", "dnsseed91.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("93", "dnsseed92.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("94", "dnsseed93.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("95", "dnsseed94.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("96", "dnsseed95.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("97", "dnsseed96.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("98", "dnsseed97.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("99", "dnsseed98.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("100", "dnsseed99.hashshare.org"));
		vSeeds.push_back(CDNSSeedData("101", "dnsseed100.hashshare.org"));


		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
		// 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

		convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

		fMiningRequiresPeers = true;
		fAllowMinDifficultyBlocks = false;
		fDefaultConsistencyChecks = false;
		fRequireStandard = true;
		fMineBlocksOnDemand = false;
		fSkipProofOfWorkCheck = false;
		fTestnetToBeDeprecatedFieldRPC = false;
		fHeadersFirstSyncingActive = false;

		nPoolMaxTransactions = 3;
		nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
		strSporkKey = "04015d2a166421d6f9146ccb9019fb648f72d82c789c670e6f8df010309266caad536c720cf9cc06781dabd6f1a17be2a91aaade40e5b80f56a4ba5c70e732d466";
		strObfuscationPoolDummyAddress = "HAg6LVyZjbaUce9GoYuwfo9Q2r8itSj4pq";

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
		nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zhss to be stakable

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
		vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
		nDefaultPort = 51474;
		nEnforceBlockUpgradeMajority = 4320; // 75%
		nRejectBlockOutdatedMajority = 5472; // 95%
		nToCheckBlockUpgradeMajority = 5760; // 4 days
		nMinerThreads = 0;
		nTargetTimespan = 1 * 60; // HashShareCoin: 1 day
		nTargetSpacing = 1 * 60;  // HashShareCoin: 1 minute
		nLastPOWBlock = 200;
		nMaturity = 15;
		nMasternodeCountDrift = 4;
		nMaxMoneyOut = 43199500 * COIN;

		// Public coin spend enforcement
		nPublicZCSpends = 1106100;

		//! Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nTime = 1564038000;
		genesis.nNonce = 2402015;

		hashGenesisBlock = genesis.GetHash();
		//assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));

		vFixedSeeds.clear();
		vSeeds.clear();
		vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "hashsharecoin-testnet.seed.fuzzbawls.pw"));
		vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "hashsharecoin-testnet.seed2.fuzzbawls.pw"));
		vSeeds.push_back(CDNSSeedData("warrows.dev", "testnet.dnsseed.hashsharecoin.warrows.dev"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet hashsharecoin addresses start with 'x' or 'y'
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet hashsharecoin script addresses start with '8' or '9'
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
		// Testnet hashsharecoin BIP32 pubkeys start with 'DRKV'
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
		// Testnet hashsharecoin BIP32 prvkeys start with 'DRKP'
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
		// Testnet hashsharecoin BIP44 coin type is '1' (All coin's testnet default)
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
		strSporkKey = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
		strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
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
		nEnforceBlockUpgradeMajority = 750;
		nRejectBlockOutdatedMajority = 950;
		nToCheckBlockUpgradeMajority = 1000;
		nMinerThreads = 1;
		nTargetTimespan = 24 * 60 * 60; // HashShareCoin: 1 day
		nTargetSpacing = 1 * 60;        // HashShareCoin: 1 minutes
		bnProofOfWorkLimit = ~uint256(0) >> 1;
		nLastPOWBlock = 250;
		nMaturity = 100;
		nMasternodeCountDrift = 4;
		//nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
		nMaxMoneyOut = 43199500 * COIN;
		nZerocoinStartHeight = 300;
		nBlockZerocoinV2 = 300;
		nZerocoinStartTime = 1501776000;
		nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
		nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
		nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
		nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint

		// Public coin spend enforcement
		nPublicZCSpends = 350;

		//! Modify the regtest genesis block so the timestamp is valid for a later start.
		genesis.nTime = 1564038000;
		genesis.nNonce = 2402015;

		hashGenesisBlock = genesis.GetHash();
		//assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
		//assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));

		vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
		vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

		fMiningRequiresPeers = false;
		fAllowMinDifficultyBlocks = true;
		fDefaultConsistencyChecks = true;
		fRequireStandard = false;
		fMineBlocksOnDemand = true;
		fTestnetToBeDeprecatedFieldRPC = false;
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
