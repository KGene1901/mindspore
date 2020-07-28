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

#include "src/runtime/kernel/arm/opclib/reverse_sequence.h"
#include <string.h>
#include "src/runtime/kernel/arm/opclib/arithmetic_common.h"

void ReverseSequence(float *input0, int *input1, float *output, ReverseSequenceParameter *para) {
  (void)memcpy(output, input0, para->total_data_size_);
  ComputeStrides(para->input_shape0_, para->input_stride_, para->ndim_);
  ComputeStrides(para->output_shape_, para->output_stride_, para->ndim_);
  for (int i = 0; i < para->outer_count_; ++i) {
    auto in = input0 + i * para->outer_stride_;
    auto out = output + i * para->outer_stride_;
    for (int batch = 0; batch < para->input_shape0_[para->batch_axis_]; batch++) {
      auto in_batch = in + batch * para->input_stride_[para->batch_axis_];
      auto out_batch = out + batch * para->output_stride_[para->batch_axis_];
      for (int n = 0; n < input1[batch]; ++n) {
        auto in_seq = in_batch + (input1[batch]  - 1 - n) * para->input_stride_[para->seq_axis_];
        auto out_seq = out_batch + n * para->output_stride_[para->seq_axis_];
        for (int j = 0; j < para->inner_count_; ++j) {
          (void)memcpy(out_seq + j * para->inner_stride_, in_seq + j * para->inner_stride_, para->copy_byte_size_);
        }
      }
    }
  }
}


