##### 检错码or纠错码

前置结论:当信道非常稳定时，检错码代价小于纠错码(检错码的长度短，代价小)

checksum 检验和

##### CRC的核心

添加一段冗余码 **使得组合后的新数据流能够整除除数**

对应除数的选择对应不同的规范，讲究也有所不同

表现形式为  `<original intact message> <checksum> `

##### 模2运算的正确性

正是由于模2运算的约定性，要求对应除数的r比特和最后商的x比特之间的关系一定为

$r + 1 \ge x$    因而也可以构造出对应的速算表

> 同时$x$可以补充0至$r-1$ bit

##### 硬件设计

通过递归，归纳出移位寄存器的状态方程

```c
unsigned short crc16(unsigned short crc, unsigned char *p, int len)
{
          while (len--)
               crc = (crc >> 8) ^ crctab[(crc ^ *p++) & 0xff]; //异或指模2减法
          return crc;
}
```

##### 纠错要求

```txt
causes each incoming byte to have an effect on the entire checksum register.
通过拓展checksum register 降低误判的概率
```

###### 要求一

```txt
   WIDTH: A register width wide enough to provide a low a-priori
             probability of failure (e.g. 32-bits gives a 1/2^32 chance
             of failure).
```

######    

###### 要求二

```txt
   CHAOS: A formula that gives each input byte the potential to change
          any number of bits in the register.
```



##### polynomial arithmetic (mod 2)

多项式中，独立项的次数代表着二进制运算中数位的权值。故而运算可以等价

且多项式运算相邻项之间联系不大，故省去进位概念

定义模2运算中的数的大小—>由数位数比较确定

##### 多项式环

1. prove that the equation $x^2 - 7y^2-24=0$ has no integer solutions….
   construct $z_7$ as the natural homomorphism image

软件实现过程为 查表的映射  `*p++` 表示从当前索引指针解引用，从当前内存单元，进一步指向下一内存单元

```c
r = 0;
while(len--){
    r = (r << 8)| (*p++) ^ t[(r>>24)&0xff];
} // 原始数据的装填和运算
for (i=0; i<W/8; i++) r = (r << 8) ^ t[(r >> 24) & 0xFF]; // 末尾补充的0位运算
```

1. 装填过程
2. 常规运算
3. 把装填进寄存器的数据流最后的字节全部移出

版本二的第一次迭代省去了初次装填过程  而与之等价

```c
 r=0; while (len--) r = (r<<8) ^ t[(r >> 24) ^ *p++];//版本2
```

