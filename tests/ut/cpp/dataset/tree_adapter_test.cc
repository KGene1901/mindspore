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

#include "minddata/dataset/engine/tree_adapter.h"
#include "common/common.h"
#include "minddata/dataset/core/tensor_row.h"
#include "minddata/dataset/include/datasets.h"
#include "minddata/dataset/include/transforms.h"

using namespace mindspore::dataset;
using mindspore::dataset::Tensor;

class MindDataTestTreeAdapter : public UT::DatasetOpTesting {
 protected:
};

TEST_F(MindDataTestTreeAdapter, TestSimpleTreeAdapter) {
  MS_LOG(INFO) << "Doing MindDataTestTreeAdapter-TestSimpleTreeAdapter.";

  // Create a Mnist Dataset
  std::string folder_path = datasets_root_path_ + "/testMnistData/";
  std::shared_ptr<api::Dataset> ds = Mnist(folder_path, "all", api::SequentialSampler(0, 4));
  EXPECT_NE(ds, nullptr);

  ds = ds->Batch(2);
  EXPECT_NE(ds, nullptr);

  mindspore::dataset::TreeAdapter tree_adapter;

  Status rc = tree_adapter.BuildAndPrepare(ds, 1);

  EXPECT_TRUE(rc.IsOk());

  const std::unordered_map<std::string, int32_t> map = {{"label", 1}, {"image", 0}};
  EXPECT_EQ(tree_adapter.GetColumnNameMap(), map);

  std::vector<size_t> row_sizes = {2, 2, 0, 0};

  TensorRow row;
  for (size_t sz : row_sizes) {
    rc = tree_adapter.GetNext(&row);
    EXPECT_TRUE(rc.IsOk());
    EXPECT_EQ(row.size(), sz);
  }

  rc = tree_adapter.GetNext(&row);
  EXPECT_TRUE(rc.IsError());
  const std::string err_msg = rc.ToString();
  EXPECT_TRUE(err_msg.find("EOF has already been reached") != err_msg.npos);
}

TEST_F(MindDataTestTreeAdapter, TestTreeAdapterWithRepeat) {
  MS_LOG(INFO) << "Doing MindDataTestTreeAdapter-TestTreeAdapterWithRepeat.";

  // Create a Mnist Dataset
  std::string folder_path = datasets_root_path_ + "/testMnistData/";
  std::shared_ptr<api::Dataset> ds = Mnist(folder_path, "all", api::SequentialSampler(0, 3));
  EXPECT_NE(ds, nullptr);

  ds = ds->Batch(2, false);
  EXPECT_NE(ds, nullptr);

  mindspore::dataset::TreeAdapter tree_adapter;

  Status rc = tree_adapter.BuildAndPrepare(ds, 2);
  EXPECT_TRUE(rc.IsOk());

  const std::unordered_map<std::string, int32_t> map = tree_adapter.GetColumnNameMap();
  EXPECT_EQ(tree_adapter.GetColumnNameMap(), map);

  std::vector<size_t> row_sizes = {2, 2, 0, 2, 2, 0, 0};

  TensorRow row;
  for (size_t sz : row_sizes) {
    rc = tree_adapter.GetNext(&row);
    EXPECT_TRUE(rc.IsOk());
    EXPECT_EQ(row.size(), sz);
  }
  rc = tree_adapter.GetNext(&row);
  const std::string err_msg = rc.ToString();
  EXPECT_TRUE(err_msg.find("EOF has already been reached") != err_msg.npos);
}

TEST_F(MindDataTestTreeAdapter, TestProjectMapTreeAdapter) {
  MS_LOG(INFO) << "Doing MindDataTestPipeline-TestProjectMap.";

  // Create an ImageFolder Dataset
  std::string folder_path = datasets_root_path_ + "/testPK/data/";
  std::shared_ptr<api::Dataset> ds = ImageFolder(folder_path, true, api::SequentialSampler(0, 2));
  EXPECT_NE(ds, nullptr);

  // Create objects for the tensor ops
  std::shared_ptr<api::TensorOperation> one_hot = api::transforms::OneHot(10);
  EXPECT_NE(one_hot, nullptr);

  // Create a Map operation, this will automatically add a project after map
  ds = ds->Map({one_hot}, {"label"}, {"label"}, {"label"});
  EXPECT_NE(ds, nullptr);

  mindspore::dataset::TreeAdapter tree_adapter;

  Status rc = tree_adapter.BuildAndPrepare(ds, 2);

  EXPECT_TRUE(rc.IsOk());

  const std::unordered_map<std::string, int32_t> map = {{"label", 0}};
  EXPECT_EQ(tree_adapter.GetColumnNameMap(), map);

  std::vector<size_t> row_sizes = {1, 1, 0, 1, 1, 0, 0};
  TensorRow row;

  for (size_t sz : row_sizes) {
    rc = tree_adapter.GetNext(&row);
    EXPECT_TRUE(rc.IsOk());
    EXPECT_EQ(row.size(), sz);
  }
  rc = tree_adapter.GetNext(&row);
  const std::string err_msg = rc.ToString();
  EXPECT_TRUE(err_msg.find("EOF has already been reached") != err_msg.npos);
}