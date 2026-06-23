/*
source /Users/siddharthmanikant/zephyr-venv/bin/activate
west init -m https://github.com/zephyrproject-rtos/zephyr .
west update
west zephyr-export
pip install -r zephyr/scripts/requirements.txt
west sdk install
west sdk list
west build -b nucleo_f103rb -p always
west flash --runner openocd
*/

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/reboot.h>
// #include <stmboot/stmboot.h>
#include "/Users/siddharthmanikant/Desktop/Bachelor_Project/stmboot/zephyr/include/stmboot.h" // todo temp fix

#define SW0_NODE DT_ALIAS(sw0)
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static struct gpio_callback button_cb_data;

void my_button_handler(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    printk("Button pressed!\n");
    stmboot_request_upgrade();
    printk("Upgrade requested — rebooting to apply\n");
    sys_reboot(SYS_REBOOT_WARM);
}

int main(void) {
    if (!gpio_is_ready_dt(&button)) {
        printk("Button device not ready\n");
        return -1;
    }

    gpio_pin_configure_dt(&button, GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);

    gpio_init_callback(&button_cb_data, my_button_handler, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data);

    while (1) {
        k_msleep(1000);
    }
}
