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

#ifndef MINDSPORE_CCSRC_TOOLS_LITE_CONVERTER_PARSER_CAFFE_CAFFE_SCALE_PARSER_H_
#define MINDSPORE_CCSRC_TOOLS_LITE_CONVERTER_PARSER_CAFFE_CAFFE_SCALE_PARSER_H_

#include <vector>
#include "mindspore/lite/tools/converter/parser/caffe/caffe_node_parser.h"
#include "mindspore/lite/tools/converter/parser/caffe/caffe_node_parser_registry.h"

namespace mindspore {
namespace lite {
class CaffeScaleParser : public CaffeNodeParser {
 public:
  CaffeScaleParser() : CaffeNodeParser("scale") {}

  STATUS Parse(const caffe::LayerParameter &proto, const caffe::LayerParameter &weight, schema::CNodeT *op,
               std::vector<schema::TensorT *> *weightVec) override;

  STATUS GetAxisIndex(const int32_t &axis, uint32_t *axis_index);
};
}  // namespace lite
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_TOOLS_LITE_CONVERTER_PARSER_CAFFE_CAFFE_SCALE_PARSER_H_

