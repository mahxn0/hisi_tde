/*
 * @*: ********************************************************************
 * @Copyright: Copyright (c) 2021 CF.Studio. All rights reserved.
 * @Description:
 * @Version: 1.0
 * @Autor: mahxn0
 * @Date: 2022-04-08 23:45:48
 * @LastEditors: mahxn0
 * @LastEditTime: 2022-04-10 17:46:41
 * @Begin: ********************************************************************
 * @Modify:
 * @End**: ********************************************************************
 */

#include "mmz_resize.h"
#include "common.h"
#include <unistd.h>

int MMzResize(const cv::Mat &src, cv::Mat &dst) {
  SYS_VIRMEM_INFO_S srcMemInfo;
  SYS_VIRMEM_INFO_S pstMemInfo;
  TDE_HANDLE s32Handle;
  int s32Ret = 0;
  s32Ret = HI_MPI_SYS_GetVirMemInfo(src.data, &srcMemInfo);
  if (s32Ret != 0) {
    printf("src GetVirMemInfo error = %x please check InputPvir \n", s32Ret);
    return -111;
  }
  s32Ret = HI_MPI_SYS_GetVirMemInfo(dst.data, &pstMemInfo);
  if (s32Ret != 0) {
    printf("dst GetVirMemInfo error = %x please check InputPvir \n", s32Ret);
    return -111;
  }

  s32Handle = HI_TDE2_BeginJob();
  if (HI_ERR_TDE_INVALID_HANDLE == s32Handle ||
      HI_ERR_TDE_DEV_NOT_OPEN == s32Handle) {
    printf("start job failed!\n");
    return -1;
  }
  TDE2_RECT_S stSrcRect;
  stSrcRect.s32Xpos = 0;
  stSrcRect.s32Ypos = 0;
  stSrcRect.u32Width = src.cols;
  stSrcRect.u32Height = src.rows;

  TDE2_RECT_S stDstRect;
  stDstRect.s32Xpos = 0;
  stDstRect.s32Ypos = 0;
  stDstRect.u32Width = dst.cols;
  stDstRect.u32Height = dst.rows;

  TDE2_SURFACE_S tdesrc;
  tdesrc.PhyAddr = srcMemInfo.u64PhyAddr;
  tdesrc.enColorFmt = TDE2_COLOR_FMT_BGR888;
  tdesrc.u32Width = src.cols;
  tdesrc.u32Height = src.rows;
  tdesrc.u32Stride = src.channels() * src.cols;
  tdesrc.u8Alpha0 = 0xff;
  tdesrc.u8Alpha1 = 0xff;
  tdesrc.bAlphaMax255 = HI_TRUE;
  tdesrc.bAlphaExt1555 = HI_TRUE;
  tdesrc.u32CbCrStride = 0;
  tdesrc.bYCbCrClut = HI_TRUE;
  tdesrc.CbCrPhyAddr = 0;
  tdesrc.ClutPhyAddr = 0;

  TDE2_SURFACE_S tdedst;
  tdedst.PhyAddr = pstMemInfo.u64PhyAddr;
  tdedst.enColorFmt = TDE2_COLOR_FMT_BGR888;
  tdedst.u32Width = dst.cols;
  tdedst.u32Height = dst.rows;
  tdedst.u32Stride = dst.cols * dst.channels();

  tdedst.u8Alpha0 = 0xff;
  tdedst.u8Alpha1 = 0xff;
  tdedst.bAlphaMax255 = HI_TRUE;
  tdedst.bAlphaExt1555 = HI_TRUE;

  tdedst.u32CbCrStride = 0;
  tdedst.bYCbCrClut = HI_TRUE;
  tdedst.CbCrPhyAddr = 0;
  tdedst.ClutPhyAddr = 0;

  s32Ret =
      HI_TDE2_QuickResize(s32Handle, &tdesrc, &stSrcRect, &tdedst, &stDstRect);
  if (s32Ret < 0) {
    printf("imageResize HI_TDE2_QuickResize failed,ret=0x%x!\n", s32Ret);
    HI_TDE2_CancelJob(s32Handle);
    return -1;
  }
  HI_TDE2_WaitForDone(s32Handle);
  s32Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 500);
  if (s32Ret < 0) {
    printf("HI_TDE2_EndJob failed,ret=0x%x!\n", s32Ret);
    HI_TDE2_CancelJob(s32Handle);
    return -1;
  }
}
