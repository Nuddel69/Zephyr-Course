#include <zephyr/drivers/gpio.h>
#include <zephyr/sleep.h>

#define LED0_NODE DT_ALIAS(led0)

struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(int argc, char *argv[]) {
  printk("Hello World!\n");

  if (!gpio_is_ready_dt(&led)) {
    printk("Error initialising device!\n");
    return -1;
  }

  gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

  while (1) {
    gpio_pin_set_dt(&led, 1);
    k_sleep(K_MSEC(500));
    gpio_pin_set_dt(&led, 0);
    k_sleep(K_MSEC(500));
  }

  return 0;
}
