/**
 * Copyright 2019 Huawei Technologies Co., Ltd
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

#ifndef MINDSPORE_CCSRC_FRONTEND_PARALLEL_STRATEGY_CHEKCPOINT_PARALLEL_STRATEGY_CHECKPOINT_H_
#define MINDSPORE_CCSRC_FRONTEND_PARALLEL_STRATEGY_CHEKCPOINT_PARALLEL_STRATEGY_CHECKPOINT_H_

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "frontend/parallel/ops_info/ops_utils.h"
#include "frontend/parallel/strategy.h"
#include "frontend/parallel/context.h"
#include "frontend/parallel/tensor_layout/tensor_layout.h"
#include "frontend/parallel/tensor_layout/tensor_info.h"

namespace mindspore {
namespace parallel {
using StrategyMap = std::unordered_map<std::string, StrategyPtr>;
using TensorInfoMap = std::unordered_map<std::string, TensorInfo>;
using ManualShapeMap = std::unordered_map<std::string, std::vector<std::pair<int32_t, int32_t>>>;
class StrategyCheckpoint {
 public:
  StrategyCheckpoint() {
    current_stage_ = 0;
    load_file_ = "";
    load_checkpoint_on_ = false;
    save_file_ = "";
    save_checkpoint_on_ = false;
  }
  ~StrategyCheckpoint() = default;

  Status Load(StrategyMap *strategy_map);
  Status Save(const StrategyMap &strategy_map, const TensorInfoMap &tensor_info_map, ManualShapeMap *manual_shape_map);

  static StrategyCheckpoint &GetInstance();
  bool LoadCheckPointOn() const { return load_checkpoint_on_; }
  bool SaveCheckPointOn() const { return save_checkpoint_on_; }

 private:
  std::string load_file_;
  std::string save_file_;
  bool load_checkpoint_on_;
  bool save_checkpoint_on_;
  bool CheckPointExit(const std::string path) const;
  int32_t current_stage_;
};
}  // namespace parallel
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_FRONTEND_PARALLEL_STRATEGY_CHEKCPOINT_PARALLEL_STRATEGY_CHECKPOINT_H_
