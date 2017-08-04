
#include <common.h>
#include <command.h>

static unsigned long str16_to_u32(const char* str)
{
    const char *s = str;
    unsigned long len;
    int c;

    do {                //得到第一个字符，跳过空格
        c = *s++;
    } while (c == ' ');
    if(c == '0')
    {
        c = *s++;
    }
    else
    {
        printf("wrong number!\n");
        return -1;
    }


    if((c == 'x') || (c == 'X'))
    {
        c = *s++;
    }
    else
    {
        printf("wrong number!\n");
        return -1;
    }


    for (len = 0; ((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F'))  ; c = *s++) {
        if(((c >= '0') && (c <= '9')) )
            c = c - '0';
        else if((c >= 'a') && (c <= 'f'))
            c = c - 'a' + 10;
        else if((c >= 'A') && (c <= 'F'))
            c = c - 'A' + 10;
        len *= 16;
        len += c;
    }
    return len;
}


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

static int do_memcmp(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char * pmem1 = NULL;
    char * pmem2 = NULL;
    int len = 0;

    if((argv[1] != NULL) && (argv[2] != NULL) && (argv[3] != NULL))
    {
        pmem1 = (char *)str16_to_u32(argv[1]);
        pmem2 = (char *)str16_to_u32(argv[2]);
        len = (int)str10_to_u32(argv[3]);
        printf("%p\t ", pmem1);
        printf("%p\t ", pmem2);
        printf("%d\n", len);
    }
    else
    {
        printf("wrong input!\n");
        return 0;
    }

    while(len--)
    {
        if ((*pmem1++) != (*pmem2++)) {
            printf("Different!\n");
            return 0;
        }
    }
    printf("same!\n");
    return 0;
}

U_BOOT_CMD(
    memcmp,    5,  0,  do_memcmp,
    "memcmp - compare memory",
    "- memcmp mem_addr1 mem_addr2 len \
     - memcmp 0x1000000 0x2000000 100"
);

