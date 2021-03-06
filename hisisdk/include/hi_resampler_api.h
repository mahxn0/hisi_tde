#ifndef _HI_RESAMPLER_API_H_
#define _HI_RESAMPLER_API_H_

#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAXFRAMESIZE 2048

/**************************************************************************************
 * Function:    HI_Resampler_Create
 *
 * Description: allocate memory for platform-specific data
 *              clear all the user-accessible fields
 *
 * Inputs:      inrate:  8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000
 *              outrate: 8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000
 *              chans:   1 or 2
 * Outputs:     none
 *
 * Return:      handle to Resampler instance, 0 if malloc fails
 **************************************************************************************/
HI_VOID* HI_Resampler_Create(HI_S32 s32Inrate, HI_S32 s32Outrate, HI_S32 s32Chans);


/**************************************************************************************
 * Function:    HI_Resampler_Process
 *
 * Description: Resample pcm data to specific samplerate, only for interlaced format
 *
 * Inputs:      inst: valid Resampler instance pointer (HResampler)
 *              inbuf:   pointer to inputbuf
 *              insamps: input number of sample pointers
 * Outputs:     outbuf:  pointer to outputbuf
 *
 * Return:      output sample number per-channel
 * Notes:       sure insamps < MAXFRAMESIZE


 **************************************************************************************/
HI_S32 HI_Resampler_Process(HI_VOID* inst, HI_S16* s16Inbuf, HI_S32 s32Insamps, HI_S16* s16Outbuf);


/**************************************************************************************
 * Function:    HI_Resampler_Destroy
 *
 * Description: free platform-specific data allocated by ResamplerCreate
 *
 * Inputs:      valid Resampler instance pointer (HResampler)
 * Outputs:     none
 *
 * Return:      none
 **************************************************************************************/
HI_VOID HI_Resampler_Destroy(HI_VOID* inst);


/*******************************************************************************
 * Function:    HI_Resampler_GetMaxOutputNum
 *
 * Description: Caculate max output number at specific input number
 *
 * Inputs:        inst:      valid Resampler instance pointer (HI_HANDLE)
 *                insamps:  input data number per-channel, insamps must be even
 * Outputs:     none
 * Return:        >=0:      Success, return the max output number per-channel
 *                other:      Fail, return error code
 * Notes:
 * 1  if stereo(chans==2), sure insamps%2 == 0
 ******************************************************************************/
HI_S32 HI_Resampler_GetMaxOutputNum(HI_VOID* inst, HI_S32 s32Insamps);


#ifdef __cplusplus
}
#endif



#endif
