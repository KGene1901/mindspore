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

#include "tools/converter/parser/caffe/caffe_relu6_parser.h"
#include <memory>

namespace mindspore {
namespace lite {
PrimitiveC *CaffeRelu6Parser::ParseLitePrimitive(const caffe::LayerParameter &proto,
                                                 const caffe::LayerParameter &weight) {
  std::unique_ptr<schema::ActivationT> attr(new schema::ActivationT());
  if (attr == nullptr) {
    MS_LOG(ERROR) << "new op failed";
    return nullptr;
  }

  attr->type = schema::ActivationType_RELU6;
  if (proto.has_relu_param() && proto.relu_param().has_negative_slope()) {
    float negative_slope = proto.relu_param().negative_slope();
    if (0 != negative_slope) {
      attr->type = schema::ActivationType_LEAKY_RELU;
      attr->alpha = negative_slope;
    }
  }
  auto primitive = std::make_unique<schema::PrimitiveT>();
  primitive->value.type = schema::PrimitiveType_Activation;
  primitive->value.value = attr.release();
  return PrimitiveC::Create(primitive.release());
}

CaffeNodeRegistrar g_caffeRelu6Parser("ReLU6", new CaffeRelu6Parser());
}  // namespace lite
}  // namespace mindspore
