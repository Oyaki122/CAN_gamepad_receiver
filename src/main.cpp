#include <mbed.h>

#include "controller.h"

DigitalOut led(LED1, false);
CAN can1(PA_11, PA_12, 500E3);

void onPushBtn(size_t btnNum, bool state) {
  if (btnNum != 0) return;  // ボタン番号0 = Xボタン
  led = state;
}

int main() {
  printf("start\n");

  Controller controller(can1, 0x334, 1);

  controller.setButtonEventListener(&onPushBtn);

  while (true) {
    // controller.receiveData();
    printf("Axes: %4d %4d %4d %4d ", controller.axes.x, controller.axes.y,
           controller.axes.z, controller.axes.rz);
    printf("Buttons: ");
    for (auto button : controller.buttons) {
      printf(button ? "1" : "0");
    }
    printf("\n");
    ThisThread::sleep_for(10ms);
  }
}
