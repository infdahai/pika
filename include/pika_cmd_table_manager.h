// Copyright (c) 2018-present, Qihoo, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#ifndef PIKA_CMD_TABLE_MANAGER_H_
#define PIKA_CMD_TABLE_MANAGER_H_

#include <thread>

#include "include/pika_command.h"
#include "include/pika_data_distribution.h"

class PikaCmdTableManager {
 public:
  PikaCmdTableManager();
  virtual ~PikaCmdTableManager();
  std::shared_ptr<Cmd> GetCmd(const std::string& opt);
  uint32_t DistributeKey(const std::string& key, uint32_t partition_num);

 private:
  std::shared_ptr<Cmd> NewCommand(const std::string& opt);

  void InsertCurrentThreadDistributionMap();
  bool CheckCurrentThreadDistributionMapExist(const std::thread::id& tid);

  CmdTable* cmds_ = nullptr;

  pthread_rwlock_t map_protector_;
  std::unordered_map<std::thread::id, PikaDataDistribution*> thread_distribution_map_;
};
#endif
