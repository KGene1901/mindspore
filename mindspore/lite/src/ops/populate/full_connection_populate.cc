/**
 * Copyright 2019-2020 Huawei Technologies Co., Ltd
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

#include "src/ops/full_connection.h"
#include "src/ops/primitive_c.h"
#include "src/ops/populate/populate_register.h"
#include "nnacl/matmul_parameter.h"

namespace mindspore {
namespace lite {

OpParameter *PopulateFullconnectionParameter(const mindspore::lite::PrimitiveC *primitive) {
  auto param =
    reinterpret_cast<mindspore::lite::FullConnection *>(const_cast<mindspore::lite::PrimitiveC *>(primitive));
  MatMulParameter *matmul_param = reinterpret_cast<MatMulParameter *>(malloc(sizeof(MatMulParameter)));
  if (matmul_param == nullptr) {
    MS_LOG(ERROR) << "malloc MatMulParameter failed.";
    return nullptr;
  }
  memset(matmul_param, 0, sizeof(MatMulParameter));
  matmul_param->op_parameter_.type_ = primitive->Type();
  matmul_param->b_transpose_ = true;
  matmul_param->a_transpose_ = false;
  matmul_param->has_bias_ = param->GetHasBias();
  if (param->GetActivationType() == schema::ActivationType_RELU) {
    matmul_param->act_type_ = ActType_Relu;
  } else if (param->GetActivationType() == schema::ActivationType_RELU6) {
    matmul_param->act_type_ = ActType_Relu6;
  } else {
    matmul_param->act_type_ = ActType_No;
  }

  return reinterpret_cast<OpParameter *>(matmul_param);
}

Registry FullConnectionParameterRegistry(schema::PrimitiveType_FullConnection, PopulateFullconnectionParameter);

}  // namespace lite
}  // namespace mindspore
