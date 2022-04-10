/*
 * @*: ********************************************************************
 * @Copyright: Copyright (c) 2021 CF.Studio. All rights reserved.
 * @Description:
 * @Version: 1.0
 * @Autor: mahxn0
 * @Date: 2022-04-08 23:55:00
 * @LastEditors: mahxn0
 * @LastEditTime: 2022-04-10 17:46:32
 * @Begin: ********************************************************************
 * @Modify:
 * @End**: ********************************************************************
 */
#include "hi_comm_sys.h"
#include "mpi_sys.h"
#include "opencv2/opencv.hpp"

#include "hi_tde_api.h"
#include "hi_tde_errcode.h"
#include "hi_tde_type.h"
#include "mpi_ive.h"
#include <arm_neon.h>
#ifndef __MMZ_RESIZE_H__
#define __MMZ_RESIZE_H__
int MMzResize(const cv::Mat &src, cv::Mat &dst);
#endif