/**gpio.h
 * This file contains the GPIO routines definitions
 */
 
#ifndef __GPIO_H
#define	__GPIO_H

//#include "mloader.h"

/* Configuration */
#define CONFIG_GPIO_BANK        2
#define CONFIG_0_GPIO_SHIFT     2
#define CONFIG_1_GPIO_SHIFT     3
#define CONFIG_2_GPIO_SHIFT     4
#define CONFIG_3_GPIO_SHIFT     5
#define CONFIG_GPIO_MASK        ((1<<CONFIG_0_GPIO_SHIFT) | (1<<CONFIG_1_GPIO_SHIFT) | (1<<CONFIG_2_GPIO_SHIFT) | (1<<CONFIG_3_GPIO_SHIFT))

typedef enum
{	GPIOFUNC_GPIO=0,		/* Set to GPIO mode, does not touch the direction */
	GPIOFUNC_GPIO_IN=1,		/* Set to GPIO mode, set to input */
	GPIOFUNC_GPIO_IN_PULLUP=2,	/* Set to GPIO mode, set to input with a weak pull-up */
	GPIOFUNC_GPIO_IN_PULLDOWN=3,	/* Set to GPIO mode, set to input with a weak pull-down */
	GPIOFUNC_GPIO_OUT=4,		/* Set to GPIO mode, set to output */
	GPIOFUNC_PERIPH=5,		/* Set to peripheral mode */
} gpio_func_t;

extern int gpio_select(gpio_func_t func, int bank, uint32_t mask);
extern uint32_t gpio_bank_read(int bank, uint32_t mask);
extern int gpio_bank_write(int bank, uint32_t mask, uint32_t data);

#define GPIO2BANK(gpio)		((gpio<8) ? 0 : (gpio-8)>>5)
#define GPIO2BIT(gpio)		((gpio<8) ? gpio : (gpio-8) & 0x1f)

#define gpio_enable(gpio)	(gpio_select(GPIOFUNC_GPIO,GPIO2BANK(gpio), 1<<GPIO2BIT(gpio)))
#define gpio_read(gpio)		(gpio_bank_read(GPIO2BANK(gpio), 1<<GPIO2BIT(gpio))?1:0)
#define gpio_write(gpio,data)	(gpio_bank_write(GPIO2BANK(gpio), 1<<GPIO2BIT(gpio),data?1<<GPIO2BIT(gpio):0))

#endif	/* #ifndef __GPIO_H */
