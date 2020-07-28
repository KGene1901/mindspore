/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_OPCLIB_FP32_ARG_MIN_MAX_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_OPCLIB_FP32_ARG_MIN_MAX_H_

#ifdef ENABLE_NEON
#include <arm_neon.h>
#endif
#include "src/runtime/kernel/arm/opclib/op_base.h"

// For arg min, arg max.
struct ArgMinMaxParameter {
    OpParameter op_parameter_;
    int axis_;
    int topk_;
    int axis_type_;
    bool out_value_;
    bool keep_dims_;
};

void ArgMax(const float *input, const int *shape, int dims_number, int axis, bool out_value, float *output);
void ArgMin(const float *input, const int *shape, int dims_number, int axis, bool out_value, float *output);
#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_OPCLIB_FP32_ARG_MIN_MAX_H_

