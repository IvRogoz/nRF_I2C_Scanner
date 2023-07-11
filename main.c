#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/i2c.h>

#define MY_I2C DT_ALIAS(i2c1)

void scan_i2c_bus(const struct device *dev, int i2cbus)
{
	printk("\e[32m\e[1m|| Scanning I2C_%u bus:\e[0m\n", i2cbus);

	for (uint8_t addr = 0; addr < 128; addr++)
	{
		struct i2c_msg msg = {
				.buf = NULL,
				.len = 0,
				.flags = I2C_MSG_WRITE};

		int ret = i2c_transfer(dev, &msg, 1, addr);
		if (ret == 0)
			printk("|> Found device at address \e[31m0x%02X\e[0m\n", addr);
	}
}

void main(void){
	devi2c = DEVICE_DT_GET(MY_I2C);
	if (!devi2c)
	{
		printk("Could not get I2C device\n");
		return;
	}
	scan_i2c_bus(devi2c, 1);
}
