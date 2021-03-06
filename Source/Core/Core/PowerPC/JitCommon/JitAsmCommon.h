// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "Core/PowerPC/JitCommon/Jit_Util.h"

extern const u8 GC_ALIGNED16(pbswapShuffle1x4[16]);
extern const u8 GC_ALIGNED16(pbswapShuffle2x4[16]);
extern const float GC_ALIGNED16(m_one[]);
extern const float GC_ALIGNED16(m_quantizeTableS[]);
extern const float GC_ALIGNED16(m_dequantizeTableS[]);

class CommonAsmRoutinesBase
{
public:

	const u8 *fifoDirectWrite8;
	const u8 *fifoDirectWrite16;
	const u8 *fifoDirectWrite32;
	const u8 *fifoDirectWrite64;

	const u8 *enterCode;

	const u8 *dispatcherMispredictedBLR;
	const u8 *dispatcher;
	const u8 *dispatcherNoCheck;

	const u8 *doTiming;

	const u8 *frsqrte;
	const u8 *fres;
	const u8 *mfcr;

	// In: array index: GQR to use.
	// In: ECX: Address to read from.
	// Out: XMM0: Bottom two 32-bit slots hold the read value,
	//            converted to a pair of floats.
	// Trashes: all three RSCRATCH
	const u8 **pairedLoadQuantized;

	// In: array index: GQR to use.
	// In: ECX: Address to write to.
	// In: XMM0: Bottom two 32-bit slots hold the pair of floats to be written.
	// Out: Nothing.
	// Trashes: all three RSCRATCH
	const u8 **pairedStoreQuantized;

	// In: array index: GQR to use.
	// In: ECX: Address to write to.
	// In: XMM0: Bottom 32-bit slot holds the float to be written.
	const u8 **singleStoreQuantized;

};

class CommonAsmRoutines : public CommonAsmRoutinesBase, public EmuCodeBlock
{
protected:
	void GenQuantizedLoads();
	void GenQuantizedStores();
	void GenQuantizedSingleStores();

public:
	void GenFifoWrite(int size);
	void GenFrsqrte();
	void GenFres();
	void GenMfcr();
};
