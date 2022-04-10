/*
 * @*: ********************************************************************
 * @Copyright: Copyright (c) 2021 CF.Studio. All rights reserved.
 * @Description:
 * @Version: 1.0
 * @Autor: mahxn0
 * @Date: 2022-04-07 23:38:12
 * @LastEditors: mahxn0
 * @LastEditTime: 2022-04-10 17:41:33
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
int main() {
  std::string image_file = "../data/test_result.jpg";
  cv::Mat im = cv::imread(image_file);
  int w = im.cols;
  int h = im.rows;
  unsigned char *addr;
  HI_U64 phy;
  HI_U64 vir;
  HI_MPI_SYS_MmzAlloc(&phy, (void **)&vir, "test", NULL, w * h * 3);
  addr = (unsigned char *)vir;
  memset(addr, 0, w * h * 3);
  memcpy(addr, im.data, w * h * 3 * sizeof(unsigned char));
  cv::Mat mmz_im = cv::Mat(h, w, CV_8UC3, addr);
  cv::imwrite("mmz_result.jpg", mmz_im);
  HI_MPI_SYS_MmzFree(phy, (void *)vir);
  return 0;
}