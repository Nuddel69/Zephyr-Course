# 5. The Application

The logic for a blinky application is inarguably, quite simple. We will,
however, take the time to properly define what we need, and try to do it in a
way building on the previous sections.

> [!NOTE]
>
> ### Intermission - the Application
>
> Firstly, let's discuss the goal of the application. We should control an LED,
> set its state and toggle it twice every second. This means we have one sensor
> and one actuator. The sensor will be the timer, 500ms in our case, and the
> actuator will be the LED.
>
> An LED can be simplified as a GPIO pin, meaning we'll need a hardware driver.
> We don't want to concern ourselves with how to interface with the GPIO
> controller or its specific quirks. That's not our job! Considering this,
> we'll use the `GPIO.h` API. It provides a function for fetching a particular
> GPIO port/pin, verifying that it's properly initialised, setting its data
> direction and toggling its state. All nifty functions, ready to use, without
> even considering how your board manages GPIO.
>
> We'll start by creating a new file `main.c` in the `src/` directory of our
> application. Import `<zephyr/sleep.h>` for the timing functions, and
> `<zephyr/drivers/gpio.h>` for the GPIO driver API. Add a main function and
> return 0.
>
> ```c
> #include <zephyr/sleep.h>
> #include <zephyr/drivers/gpio.h>
> 
> int main(int argc, char *argv[]) {
>   return 0;
> }
> ```
>
> So far so good. Now we'll start utilising some of the functions provided by
> the API. You can follow along by referencing the
> [documentation](https://docs.zephyrproject.org/latest/doxygen/html/group__gpio__interface.html).
>
> We'll start by getting the LED-pin from the devicetree. Luckily for us, the
> board definition for nucleo_h753zi includes a node label for the on-board
> LEDs. Choosing the red_led we'll select the `gpios` property and save it to a
> struct defined by the API. Add
>
> ```c
> struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_NODELABEL(red_led), gpios);
> ```
>
> When enabled in Kconfig, zephyr initialises all device drivers during boot.
> We won't have to do anything, but it's good practice to verify the device is
> ready before using it. This is a rather standard sequence for all devices in
> zephyr, and the GPIO API is no exception. Again referencing the
> documentation, add the line
>
> ```c
> gpio_is_ready_dt(&led)
> ```
>
> and exit with an error message if it returns false. Further we'll need to
> configure the data direction of the pin. We need an output, and we'll
> initialise it to high. What we initialise it to isn't really important, we
> just need it to be specified. Add the line
>
> ```c
> gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE)
> ```
>
> after your verification of the initialisation.
>
> Once again, refer to the documentation for a description of what the
> functions are doing. You won't learn *how* they work, but it'll give a fair
> description of how they're meant to be used. We don't care how it's done,
> only that it works as described!
>
> By now your application should look something like this
>
> ```c
> #include <zephyr/sleep.h>
> #include <zephyr/drivers/gpio.h>
>
> struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_NODELABEL(red_led), gpios);
> 
> int main(int argc, char *argv[]) {
>
>   if (!gpio_is_ready_dt(&led)) {
>     printk("Error initialising device!\n");
>     return -1;
>   }
>
>   gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
>
> return 0;
> }
>
> ```
>
> We've initialised and configured our GPIO, all that remains is the blinking
> itself. In an infinite loop use
>
> ```c
> gpio_pin_set_dt(&led, [1 or 0]);
> ```
>
> to set the state, and
>
> ```c
> k_sleep(K_MSEC([ms]));
> ```
>
> to sleep. Refer to the demo application in the course material if you
> struggle to figure it out! Feel free to have a look in the GPIO docs and
> extend the application to use a proper toggle function, rather than the
> explicit state.

> [!NOTE]
>
> ### Intermission - Kconfig Options for Our Application
>
> Now that we've created our application, we'll need to consider whether we
> need to set any Kconfig options. APIs are usually conditionally compiled, and
> GPIO is no exception. To figure out what option(s) we need to set we can
> either go through `menuconfig`, or query the [Zephyr Kconfig
> search](https://docs.zephyrproject.org/latest/kconfig.html). Either method
> will tell you that we need to enable the option `CONFIG_GPIO`.
>
> Create a file named `prj.conf` at your application root, and set
> `CONFIG_GPIO=y`. That's it!

## Next step: [implementation](./6_implementation.md)
