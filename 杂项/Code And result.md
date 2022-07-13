```c
#include <stdio.h>  
#include <cmath>  
  
int main(){  
    int n = 0, d = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0, z1 = 0, z2 = 0;  
    scanf("%d%d%d%d%d%d%d%d",  
          &n, &d, &x1, &y1, &z1, &x2, &y2, &z2);  
    double lambda = 0, x = 0, y = 0, z = 0;  
    double ak[3];  
    //int key = 0;  
    for (x = 0; x < n * d; x++){  
        lambda = (x - x1) / (x1 - x2);  
        y = y1 + lambda * (y1 - y2);  
        z = z1 + lambda * (z1 - z2);  
        if ((0 <= y && y <= n) && (0 <= z && z <= n)){  
            ak[0] = x;  
            ak[1] = y;  
            ak[2] = z;  
            //break;  
        }  
    }  
  
    double yk[3];  
    for (y = 0; y < n * d; y++) {  
        lambda = (y - y1) / (y1 - y2);  
        x = x1 + lambda * (x1 - x2);  
        z = z1 + lambda * (z1 - z2);  
        if ((0 <= x && x <= n) && (0 <= z && z <= n)){  
            yk[0] = x;  
            yk[1] = y;  
            yk[2] = z;  
            //break;  
        }  
    }  
  
    double zk[3];  
    for (z = 0; z < n * d; z++) {  
        lambda = (z - z1) / (z1 - z2);  
        x = x1 + lambda * (x1 - x2);  
        y = y1 + lambda * (y1 - y2);  
        if ((0 <= x && x <= n) && (0 <= y && y <= n)){  
            zk[0] = x;  
            zk[1] = y;  
            zk[2] = z;  
            //break;  
        }  
    }  
  
    double theta[3][3] = {  
            ak[0], yk[0], zk[0],  
            ak[1], yk[1], zk[1],  
            ak[2], yk[2], zk[2]  
    };  
  
    double L = 0;  
    for (int z0 = 0; z0 < 3; z0++){  
        if ((int)theta[z0][2] == theta[z0][2]) {  
            if (((int)theta[z0][0] == theta[z0][0]) && ((int)theta[z0][1] == theta[z0][1])) {  
                L = L + 4 * pow(d, 3);  
                break;  
            } else{  
                L = L + 2 * pow(d, 3);  
                break;  
            }  
        } else{  
            if (((int)theta[z0][0] == theta[z0][0]) && ((int)theta[z0][1] == theta[z0][1])) {  
                L = L + 3 * pow(d, 2) * ((int)fabs(theta[z0][2]) + 1 - theta[z0][2]);  
                break;  
            } else{  
                L = L + ((int)fabs(theta[z0][2]) + 1 - theta[z0][2]) * pow(d, 2);  
                break;  
            }  
        }  
    }  
    printf("%lf\n", L);
```

> 第一组数据2  20  0  0  0  10  10  10 
>> 结果为32000(因为第一组数据为0, 所以求lambda的时候会导致程序出现未定义问题)
>第二组数据2  20  0  0  0  10  10  0
>> 结果为32000(因为第一组数据为0, 所以求lambda的时候会导致程序出现未定义问题)
> 第三组数据2  20  0  0  0  0  10  0 
>> 结果为32000(因为第一组数据为0, 所以求lambda的时候会导致程序出现未定义问题)
> 第四组数据2  20  0  0  10  10  10  10 
>> 结果为32000(因为第一组数据为0, 所以求lambda的时候会导致程序出现未定义问题)
>第五组数据2  20  10  0  10  10  5  10 
>> 结果为32000(结果正常)
>第六组数据2  20  5  5  0  5  5  10 
>> 结果为32000(结果正常)
>第七组数据2  20  7  15  91  20  20  20 
>> 结果为32000(结果正常)
> 第八组数据5  25  5  15  0  5  15  100
>> 结果为62500(结果正常)
> 第九组数据3  30  0  -35  0  3  -25  3
>> 结果为108000(结果正常)
> 第十组数据10  16  8  17  11  12  19  60
>> 结果为16384(结果正常)