#include <stdio.h>
#include <stdlib.h>

//note that: this is octal number
unsigned int prim_poly_4 = 023; // x*x+x+1=16+2+1=19
unsigned int prim_poly_8 = 0435;
unsigned int prim_poly_16 = 0210013;
unsigned short *gflog, *gfilog;
int setup_tables(int w)
{
    unsigned int b, log, x_to_w, prim_poly;
    switch (w)
    {
    case 4:
        prim_poly = prim_poly_4;
        break;
    case 8:
        prim_poly = prim_poly_8;
        break;
    case 16:
        prim_poly = prim_poly_16;
        break;
    default:
        return -1;
    }
    printf("prim_poly: %d\n", prim_poly);
    x_to_w = 1 << w;
    gflog = (unsigned short *)malloc(sizeof(unsigned short) * x_to_w);
    gfilog = (unsigned short *)malloc(sizeof(unsigned short) * x_to_w);
    b = 1;
    for (log = 0; log < x_to_w - 1; log++)
    {
        gflog[b] = (unsigned short)log;
        gfilog[log] = (unsigned short)b;
        b = b << 1;
        if (b & x_to_w){
            printf("b: %02d --> ", b);
            b = b ^ prim_poly;
            printf("%02d\n", b);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int w = 4;
    int ret = setup_tables(w);
    if (ret != 0)
    {
        printf("setup_tables failed with err: %d\n", ret);
        return ret;
    }
    int num = 1 << w;
    for (int i = 0; i < num; i++)
    {
        printf("%02d ", i);
    }
    printf("\n");
    for (int i = 0; i < num; i++)
    {
        if (0 == i)
        {
            printf("-- ");
            continue;
        }
        printf("%02d ", gflog[i]);
    }
    printf("\n");
    for (int i = 0; i < num; i++)
    {
        if (i == num - 1)
        {
            printf("-- \n");
            break;
        }
        printf("%02d ", gfilog[i]);
    }
    return 0;
}
