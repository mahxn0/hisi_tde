/*
 * @*: ********************************************************************
 * @Copyright: Copyright (c) 2021 CF.Studio. All rights reserved.
 * @Description:
 * @Version: 1.0
 * @Autor: mahxn0
 * @Date: 2022-04-07 23:38:12
 * @LastEditors: mahxn0
 * @LastEditTime: 2022-04-10 17:45:27
 * @Begin: ********************************************************************
 * @Modify:
 * @End**: ********************************************************************
 */
#include "mmz_resize.h"
#include "mpi_sys.h"
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

int mmz_MatCreate(cv::Mat &img) {
  // printf("create start\n");
  int Result = 0;
  HI_U64 phy;
  HI_U64 vir;
  Result = HI_MPI_SYS_MmzAlloc(&phy, (void **)&vir, "LDD_IMAGE", NULL,
                               img.cols * img.rows * img.channels());
  if (Result != HI_SUCCESS) {
    printf("HI_MPI_SYS_MmzAlloc_Cached error = %x \n", Result);
    return -1;
  }
  img.data = (unsigned char *)vir;
  return 0;
}

int mmz_MatDestroy(cv::Mat &img) {
  SYS_VIRMEM_INFO_S pstMemInfo;
  int Result = 0;
  Result = HI_MPI_SYS_GetVirMemInfo(img.data, &pstMemInfo);
  if (Result != 0) {
    printf("GetVirMemInfo error = %x please check InputPvir \n", Result);
    return -111;
  } else {
    Result = HI_MPI_SYS_MmzFree(pstMemInfo.u64PhyAddr, (void *)img.data);
    if (Result != HI_SUCCESS) {
      printf("HI_MPI_SYS_MmzFree error = %x \n", Result);
      return -1;
    }
  }
  return 0;
}

int main() {

  int s32Ret = 0;
  s32Ret = HI_TDE2_Open();
  if (s32Ret != HI_SUCCESS) {
    printf("tdeopen error 0x%x\n", s32Ret);
  }

  std::string image_file = "../data/data.jpg";
  cv::Mat im = cv::imread(image_file);
  cv::Mat im_input(im.rows, im.cols, CV_8UC3);
  cv::Mat im_output(240, 320, CV_8UC3);
  //创建mmz内存的opencv
  s32Ret = mmz_MatCreate(im_input);
  s32Ret = mmz_MatCreate(im_output);
  if (s32Ret != 0) {
    return 0;
  }
  memcpy(im_input.data, im.data,
         im.rows * im.cols * im.channels() * sizeof(unsigned char));
  printf("111\n");
  MMzResize(im_input, im_output);
  printf("111\n");
  cv::imwrite("mmz_resize.jpg", im_output);
  mmz_MatDestroy(im_input);
  mmz_MatDestroy(im_output);
  return 0;
}