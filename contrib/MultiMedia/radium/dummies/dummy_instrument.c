
#include "../common/nsmtracker.h"


int DUMMYgetMaxVelocity(struct Tracks *track){
  return 127;
}

int DUMMYgetFX(struct Tracker_Windows *window,struct Tracks *track,struct FX *fx){
  return FX_FAILED;
}

int DUMMYgetPatch(struct Tracker_Windows *window,ReqType reqtype,struct Tracks *track,struct Patch *patch){
  return PATCH_FAILED;
}

void DUMMYtreatSpecialCommand(char *command,struct Tracks *track){
}

void DUMMYCloseInstrument(struct Instruments *instrument){
}

void DUMMYSelectTrackInstrument(struct Tracks *track,struct Instruments *instrument){
}

void DUMMYStopPlaying(struct Instruments *instrument){
}

int DUMMYgetStandardVelocity(struct Tracks *track){
  return 0x50;
}

void DUMMYPP_Update(struct Instruments *instrument,struct Patch *patch){
}

/* Necesarry for undo. */
void *DUMMYCopyInstrumentData(struct Tracks *track){
  return NULL;
}

void DUMMYPlayFromStartHook(struct Instruments *instrument){
}

void *DUMMYLoadFX(struct FX *fx,struct Tracks *track){
  return NULL;
}

int InitInstrumentPlugIn(struct Instruments *instrument){
  instrument->instrumentname="CAMD instrument";
  instrument->getStandardVelocity= &DUMMYgetStandardVelocity;
  instrument->getMaxVelocity= &DUMMYgetMaxVelocity;
  instrument->getFX= &DUMMYgetFX;
  instrument->getPatch= &DUMMYgetPatch;
  instrument->CloseInstrument=DUMMYCloseInstrument;
  instrument->SelectTrackInstrument=DUMMYSelectTrackInstrument;
  instrument->StopPlaying=DUMMYStopPlaying;
  instrument->PP_Update=DUMMYPP_Update;
  instrument->CopyInstrumentData=DUMMYCopyInstrumentData;
  instrument->PlayFromStartHook=DUMMYPlayFromStartHook;
  instrument->LoadFX=DUMMYLoadFX;
  return INSTRUMENT_SUCCESS;
}

