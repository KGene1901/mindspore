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

#include "src/runtime/kernel/arm/fp32/nchw2nhwc.h"

using mindspore::kernel::KERNEL_ARCH::kCPU;
using mindspore::lite::KernelRegistrar;
using mindspore::lite::RET_ERROR;
using mindspore::lite::RET_OK;
using mindspore::schema::PrimitiveType_Nchw2Nhwc;

namespace mindspore::kernel {
int Nchw2NhwcCPUKernel::Init() { return RET_OK; }

int Nchw2NhwcCPUKernel::ReSize() { return RET_OK; }

int Nchw2NhwcCPUKernel::Run() {
  auto input = inputs_[0];
  auto output = outputs_[0];

  PackNCHWToNHWCFp32(input->Data(), output->Data(), output->Batch(), output->Height() * output->Width(),
                     output->Channel());
  return RET_OK;
}

kernel::LiteKernel *CpuNchw2NhwcFp32KernelCreator(const std::vector<lite::tensor::Tensor *> &inputs,
                                                  const std::vector<lite::tensor::Tensor *> &outputs,
                                                  OpParameter *opParameter, const lite::Context *ctx,
                                                  const kernel::KernelKey &desc) {
  MS_ASSERT(opParameter != nullptr);
  MS_ASSERT(desc.type == schema::PrimitiveType_Nchw2Nhwc);
  auto *kernel = new (std::nothrow) Nchw2NhwcCPUKernel(opParameter, inputs, outputs);
  auto ret = kernel->Init();
  if (ret != RET_OK) {
    MS_LOG(ERROR) << "Init kernel failed, name: " << opParameter->name_ << ", type: "
                  << schema::EnumNamePrimitiveType(static_cast<schema::PrimitiveType>(opParameter->type_));
    delete kernel;
    return nullptr;
  }
  return kernel;
}

REG_KERNEL(kCPU, PrimitiveType_Nchw2Nhwc, CpuNchw2NhwcFp32KernelCreator)
}  // namespace mindspore::kernel

