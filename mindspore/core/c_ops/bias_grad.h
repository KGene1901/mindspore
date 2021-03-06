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

#ifndef MINDSPORE_CORE_C_OPS_BIASGRAD_H_
#define MINDSPORE_CORE_C_OPS_BIASGRAD_H_
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "c_ops/primitive_c.h"
#include "abstract/abstract_value.h"
#include "utils/check_convert_utils.h"

namespace mindspore {
constexpr auto kNameBiasGrad = "BiasGrad";
class BiasGrad : public PrimitiveC {
 public:
  BiasGrad() : PrimitiveC(kNameBiasGrad) {}
  ~BiasGrad() = default;
  MS_DECLARE_PARENT(BiasGrad, PrimitiveC);
  void Init(const std::vector<int64_t> &axis);
  void set_axis(const std::vector<int64_t> &axis);
  std::vector<int64_t> get_axis() const;
};
}  // namespace mindspore

#endif  // MINDSPORE_CORE_C_OPS_BIASGRAD_H_
