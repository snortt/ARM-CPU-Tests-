/**gpio.c
 * This file contains gpio access routines
 */
 
#include "mloader.h"
#include "gpio.h"
#include "gpio_regs.h"
#include "qcc.h"

int gpio_select(gpio_func_t func, int bank, uint32_t mask)
{	
    dwc_gpio_t *gpio;
    int GPIOSelAddr, GPIOPupAddr, GPIOPdnAddr;
    uint32_t data;

    switch(bank) {	
#if 0 //NEED_SPACE
	case 0: 
	    gpio=(dwc_gpio_t *)MERLIN_GPIOBANK0_BASE;
	    GPIOSelAddr=-1;
	    GPIOPupAddr=QREG_ADDR(CHIP_CTL_x_GPIO0PullUpEnable);
	    GPIOPdnAddr=QREG_ADDR(CHIP_CTL_x_GPIO0PullDownEnable);
	    break;
	case 1: 
	    gpio=(dwc_gpio_t *)MERLIN_GPIOBANK1_BASE;
	    GPIOSelAddr=QREG_ADDR(CHIP_CTL_x_GPIO1Sel);
	    GPIOPupAddr=QREG_ADDR(CHIP_CTL_x_GPIO1PullUpEnable);
	    GPIOPdnAddr=QREG_ADDR(CHIP_CTL_x_GPIO1PullDownEnable);
	    break;
#endif
	case 2: 
	    gpio=(dwc_gpio_t *)MERLIN_GPIOBANK2_BASE;
	    GPIOSelAddr=QREG_ADDR(CHIP_CTL_x_GPIO2Sel);
	    GPIOPupAddr=QREG_ADDR(CHIP_CTL_x_GPIO2PullUpEnable);
	    GPIOPdnAddr=QREG_ADDR(CHIP_CTL_x_GPIO2PullDownEnable);
	    break;
	default:
	    dputs("Unknown GPIO bank ");
	    dputint(bank);
	    dputs(".\n");
	    BUG();
	    return -EINVAL;
    };
    /* switch GPIO to requested direction */
    switch(func) {	
	case GPIOFUNC_GPIO_IN:
	    gpio->dir=gpio->dir & (~mask);
	    break;
#if 0 //NEED_SPACE
	case GPIOFUNC_GPIO_OUT:
	    gpio->dir=gpio->dir | mask;
	    break;
#endif
    };
    /* Set pull-ups / pull-downs if necessary */
    switch(func) {	
	case GPIOFUNC_GPIO_IN_PULLUP:
	    data=qcc_read(QCC_BID_CHIPCTL, GPIOPdnAddr, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    data&=~mask;
	    qcc_write(QCC_BID_CHIPCTL, GPIOPdnAddr, data, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    data=qcc_read(QCC_BID_CHIPCTL, GPIOPupAddr, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    data|=mask;
	    qcc_write(QCC_BID_CHIPCTL, GPIOPupAddr, data, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    break;
#if 0 //NEED_SPACE
	case GPIOFUNC_GPIO_IN_PULLDOWN:
	    data=qcc_read(QCC_BID_CHIPCTL, GPIOPupAddr, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    data&=~mask;
	    qcc_write(QCC_BID_CHIPCTL, GPIOPupAddr, data, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    data=qcc_read(QCC_BID_CHIPCTL, GPIOPdnAddr, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    data|=mask;
	    qcc_write(QCC_BID_CHIPCTL, GPIOPdnAddr, data, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    break;
	case GPIOFUNC_GPIO:
	default:
	    data=qcc_read(QCC_BID_CHIPCTL, GPIOPupAddr, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    data&=~mask;
	    qcc_write(QCC_BID_CHIPCTL, GPIOPupAddr, data, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    data=qcc_read(QCC_BID_CHIPCTL, GPIOPdnAddr, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    data&=~mask;
	    qcc_write(QCC_BID_CHIPCTL, GPIOPdnAddr, data, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
	    break;
#endif
    };
    /* select GPIO mode */
    if(GPIOSelAddr>=0) {
	switch(func) {	
	    case GPIOFUNC_GPIO:
	    case GPIOFUNC_GPIO_IN:
	    case GPIOFUNC_GPIO_IN_PULLUP:
	    case GPIOFUNC_GPIO_IN_PULLDOWN:
	    case GPIOFUNC_GPIO_OUT:
		gpio->mode&=~mask;	/* Make sure GPIO is in software mode */
		data=qcc_read(QCC_BID_CHIPCTL, GPIOSelAddr, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
		data|=mask;
		qcc_write(QCC_BID_CHIPCTL, GPIOSelAddr, data, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
		break;
#if 0 //NEED_SPACE
	    case GPIOFUNC_PERIPH:
		data=qcc_read(QCC_BID_CHIPCTL, GPIOSelAddr, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
		data&=~mask;
		qcc_write(QCC_BID_CHIPCTL, GPIOSelAddr, data, QREG_NUMB(CHIP_CTL_x_GPIO1Sel));
		break;
#endif
	    default:
		dputs("Invalid function ");
		dputint(func);
		dputs("for GPIO.\n");
		BUG();
		return -EINVAL;
	};
    } 
#if 0 //NEED_SPACE
    else if(func==GPIOFUNC_PERIPH) {	
	dputs("Trying to switch to periph mode a GPIO from bank ");
	dputint(bank);
	dputs(", which is dedicated.\n");
	BUG();
	return -EINVAL;
    };
#endif
    return 0;
}

/*
uint32_t gpio_bank_read(int bank, uint32_t mask)
{	dwc_gpio_t *gpio;
	switch(bank)
	{	case 0: gpio=(dwc_gpio_t *)MERLIN_GPIOBANK0_BASE; break;
		case 1: gpio=(dwc_gpio_t *)MERLIN_GPIOBANK1_BASE; break;
		case 2: gpio=(dwc_gpio_t *)MERLIN_GPIOBANK2_BASE; break;
		default:
			puts("Unknown GPIO bank ");
			putint(bank);
			puts(".\n");
			BUG();
			return -EINVAL;
	};
	return gpio->extdata & mask;
}
*/

#if 0
int gpio_bank_write(int bank, uint32_t mask, uint32_t data)
{	dwc_gpio_t *gpio;
	switch(bank)
	{	case 0: gpio=(dwc_gpio_t *)MERLIN_GPIOBANK0_BASE; break;
		case 1: gpio=(dwc_gpio_t *)MERLIN_GPIOBANK1_BASE; break;
		case 2: gpio=(dwc_gpio_t *)MERLIN_GPIOBANK2_BASE; break;
		default:
			puts("Unknown GPIO bank ");
			putint(bank);
			puts(".\n");
			BUG();
			return -EINVAL;
	};
	gpio->data=gpio->data | (data & mask);
	return 0;
}
#endif
