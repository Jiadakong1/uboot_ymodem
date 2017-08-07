#include <common.h>
#include <command.h>

#include <serial.h>

DECLARE_GLOBAL_DATA_PTR;

volatile unsigned int * p_uart_zynq_control = (volatile unsigned int *)0xe0000000;   //第3位和第5位改不了，可能被定义为const了
volatile unsigned int * p_uart_zynq_mode =    (volatile unsigned int *)0xe0000004;
volatile unsigned int * p_uart_zynq_bgen =    (volatile unsigned int *)0xe0000018;    //加了volatile之后不能间接寻址？
volatile unsigned int * p_uart_zynq_channel = (volatile unsigned int *)0xe000002c;
volatile unsigned int * p_uart_zynq_fifo =    (volatile unsigned int *)0xe0000030;
volatile unsigned int * p_uart_zynq_bdiv =    (volatile unsigned int *)0xe0000034;


#define ZYNQ_UART_SR_TXEMPTY	(1 << 3) /* TX FIFO empty */
#define ZYNQ_UART_SR_TXACTIVE	(1 << 11)  /* TX active */
#define ZYNQ_UART_SR_RXEMPTY	0x00000002 /* RX FIFO empty */

// struct uart_zynq {   //	reg = <0xE0000000 0x1000>;
// 	u32 control; /* 0x0 - Control Register [8:0] */
// 	u32 mode; /* 0x4 - Mode Register [10:0] */
// 	u32 reserved1[4];
// 	u32 baud_rate_gen; /* 0x18 - Baud Rate Generator [15:0] */
// 	u32 reserved2[4];
// 	u32 channel_sts; /* 0x2c - Channel Status [11:0] */
// 	u32 tx_rx_fifo; /* 0x30 - FIFO [15:0] or [7:0] */
// 	u32 baud_rate_divider; /* 0x34 - Baud Rate Divider [7:0] */
// };

static unsigned long str10_to_u32(const char* str)
{
    const char *s = str;
    unsigned long len;
    int c;

    do {                //得到第一个字符，跳过空格
        c = *s++;
    } while (c == ' ');

    for (len = 0; (c >= '0') && (c <= '9'); c = *s++) {
        c -= '0';
        len *= 10;
        len += c;
    }
    return len;
}


// static int _uart_zynq_serial_putc(const char c)
// {
//     while(1)
//     {
//         if (readl(p_uart_zynq_channel) & ZYNQ_UART_SR_TXEMPTY)
//         {
//             printf("readl(p_uart_zynq_channel) & ZYNQ_UART_SR_TXEMPTY =  %d\n",readl(p_uart_zynq_channel) & ZYNQ_UART_SR_TXEMPTY);
//             writel(c, p_uart_zynq_fifo);
//             break;
//         }
//
//     }
//     // if (!(readl(p_uart_zynq_channel) & ZYNQ_UART_SR_TXEMPTY))
// 	// 	return -EAGAIN;
// 	// writel(c, p_uart_zynq_fifo);
//
// 	return 0;
// }

static int uart_putc(char c)
{
    while(1)
    {
        if ((*p_uart_zynq_channel) & ZYNQ_UART_SR_TXEMPTY)   //1可以发送
        {
            *p_uart_zynq_fifo = c;
            break;
        }
    }
	return 0;
}

static int uart_puts(char * const str)
{
    char *p = str;
    while((p != NULL) && ((*p) != '\0'))
    {
        uart_putc(*p++);
    }
	return 0;
}


static int uart_getc(void)   //用crt或者xshell发送一个字符时，收到字符和换行符， x
{
    while(1)
    {
        if ((*p_uart_zynq_channel) & ZYNQ_UART_SR_RXEMPTY)
            ;
        else
            return *p_uart_zynq_fifo;
    }
}



static int zynq_serial_getc(void)
{
    while(1){
        if (readl(p_uart_zynq_channel) & ZYNQ_UART_SR_RXEMPTY)
    	       ;
        else
            return readl(p_uart_zynq_fifo);
    }
}


static int do_baudrate(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    //char ch;
    unsigned int temp = 0;
    int current_baudrate = 115200;
    int rec = 0;

    if(argv[1] != NULL)
        current_baudrate = str10_to_u32(argv[1]);
    gd->baudrate = current_baudrate;
    // uart_putc('j');
    // uart_putc('\n');

    printf("rec = %x\n", rec);

    rec = zynq_serial_getc();
    printf("rec = %x\n", rec);

    rec = zynq_serial_getc();
    printf("rec = %x\n", rec);

    rec = uart_getc();
    printf("rec = %x\n", rec);

    //uart_putc((char)rec);
    uart_puts("jiaxiyang\n");


    // printf("baud_rate_divider = %d\t",Bdiv);
    // printf("bgen = %d\n", Bgen);
    //
    //serial_setbrg();
    // *p_uart_zynq_bgen = 2083;
    // *p_uart_zynq_bdiv = 4;
    //temp = *p_uart_zynq_control;
    //printf("*p_uart_zynq_control = %d\n", temp);

    // *p_uart_zynq_control = 0x100;
    // //*p_uart_zynq_control = temp;
    //*p_uart_zynq_control = 0x14;
    //*p_uart_zynq_mode = 0x0;
    // while(1){
    //     printf("current_baudrate = %d\n", current_baudrate);
    //     printf("baud_rate_divider = %d\t",Bdiv);
    //     printf("bgen = %d\n", Bgen);
    //
    // }

    //printf("Hello world!\n");
    //char putc('C');
    //ch = getc();
    //printf("ch = %c\n", ch);
    return 0;
}


U_BOOT_CMD(
    baudrate,    5,  0,  do_baudrate,
    "baudrate, ---just for test\n",
    "baudrate, baudrate [rate]\n"
);

