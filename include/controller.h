#pragma once

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <inttypes.h>
#include <mbed.h>
#include <stddef.h>

#include <vector>

class Controller {
 public:
  // pollingPeriod: データの受信チェックを行う間隔(ms)
  Controller(CAN& can, const uint32_t canId, int pollingPeriod = 4);
  struct {
    int8_t x;
    int8_t y;
    int8_t z;
    int8_t rz;
  } axes = {};
  std::vector<bool> buttons;
  void setButtonEventListener(Callback<void(size_t, bool)>);
  void receiveData();

 private:
  CAN& can;
  const uint32_t canId;
  const int pollingPeriod;
  Callback<void(size_t, bool)> buttonCallback;
  void parse(const uint8_t*, const size_t);
  void threadStart();

  EventQueue canEventQueue;
  Thread canEventThread;
};

#endif
