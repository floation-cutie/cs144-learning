```cpp
typedef struct{
	frame_kind kind;
    seq_nr seq;
    seq_nr ack;
    packet info;
}frame;
```

Ensure that slow receivers not swamped by fast senders

1. 字符计数
2. 字节填充 PPP
3. 比特填充 HDLC
4. 物理层编码违例法 Coding Violations

流量控制通过 Feedback-based flow control and Rate-based flow control

Error detection CRC & ARQ

Bit Error Rate Compute —- Choose scheme 

#### Why Hamming Code so excellent?

Basic idea : no any scheme can deal with all noise.

Hamming Code –> Hamming Distance(差异比特的数量的最大值) 检错和纠错

作为纠错码 —> 原消息码m位  + r冗余位 + 1 <= 2^r 

原理： 从二维矩阵的角度进行观察 对于2的幂次的位置，它们的组合可以构成全体整数

于是对于这个精心设计的子集，对他们一个个进行设问，最终发现问题 (check bit 保证位于判断集合之和为偶数)

No error or error on the first position, or set the first position to make the whole block to be even(detect two errors)

We can consider that from the perspective of **bit** 

> 1 1  1 1  = 15,by four bits encoding 2^4 info
>
> if we set one bit to be the check bit, there could be 2^3 info every set
>
> we can let every set have even property,then every time’s ask will half the scope
>
> And most important is that the ask every time(every bit) encode the position bit of error number.

#### 1.Simplex Utopia protocol

#### 2.Stop-and-Wait protocol without noise

#### **3.Simplex Protocol for a noisy Channel**   PAR

停等协议 – 序列号(链路层1bit) 可以确保按序到达，在实际链路上传输

而传输层的序列号需要设为更大 保证同编号的旧帧不可能被缓冲在网络中 因为传输层通过TCP无线传输

Go-Back-N协议 窗口大小2^n - 1

SR协议 2^(n-1)

To avoid duplicate frame passing and delayed ACK

We need Sequence Number to distinguish a frame that is seen for the first time from a **retransmission**

How much space should be assigned for seq??

收到了坏帧  重新启动定时器

The Timer Internal also affect performance or waste

==Full duplex==

A **piggybacking** method 搭载

Use the same circuit for data in both directions

ACK is attached to the outgoing data frame

如果相对的“接收方”的网络层没有分组可以搭载ack报文，就不传递回去了吗??

“接收方”也会设置定时器 timeout 



#### 4.Sliding Window Protocol

Sending windows :: 发送方给即将发送的帧编号

发送窗口的大小 –> 待缓存的数 据

Receiving windows 

链路层上窗口大小固定  –>>  构造比较简单

**One-bit Sliding Window Protocol**

With a 3-bit sequence number 序列号和确认号

各自存储发送缓冲区 && 接收缓冲区

发送方 和 接收方 采取相同的程序

当第一次通信的时候，ACK的值应该定为多少呢?

​	在传输层中，通过增加确认ACK字段是否有效的一段空间来实现通信

​	在数据链路层，约定首次ACK数据为 1 - frame_expected

**Notation (seq,ack, packet)**  

协议四可能存在多分组在链路上同时发送的问题

延迟 导致效率低  考虑 Round - trip propagation 

==计算时间比例==



#### **5.Go Back N**

多发多确认 (保证线路上不空载)

核心也是差错恢复的方法

##### Pipelining and Error Recovery

###### 1.Receiver’s window size is 1

The sender didn’t whether a particular packet is lost unless

the ack timer timeout,and the receiver discard anything it didn’t wish

###### 2.Receiver’s window size is large

the frames buffered in the receiver but it sends back NAK 2,

then it sends back ack1,if the frame 2 arrives,then sends sequential frames one time



If ack frame is damaged, ack are cumulative, next ACK(i+n)

may arrive before transmitter times out on frame i



##### Maximum of Sending Window Size

For 3 bit sequence number,

 the Sending Window and Receiving Window can’t be overlapped on the same sequence number

So the Sending Window Size maximum is 7

==Principle must ensure the desired window don’t overlap==

协议实现中: 

1. 判断序号b是否位于range(a,c)中

##### Protocol5改进

设计ACK帧和ACK定时器

* 发送数据量并非源源不断的分组流
  * 当真的无法通过搭载的方式传递ACK时，发送短的ACK帧
* 用于回送ACK定时器
  * ACK timer 并不重新计时
* 协议参数设计



定时器设计:: Time Queue in Software

**时间队列**                                                   

**Selective Repeat**

Wind0w Size of Selective Repeat

滑动窗口大小最大 为 数据量 / 2 

$Ws + Wr <= 2^n, Ws >= Wr$ 

How many buffers must the receiver have？

Equal to the window size! Not to the range of sequence numbers



To avoid **multiple requests** for retransmission of the **same frame** ==receiver should keep track of whether a NAK has already been sent for a given frame==

#### Performance

平均重传数量为 1 / 1 - P P为出错概率

HDLC 主站-》 从站 命令– 响应 **帧的结构** 支持可靠传输

不等长编码 Next域



RR   		 RNR 		REJ		 SREJ

P \ F 位 poll invite the terminal to send data

而 接收方 response with the last frames have bit 1

SLP serial line IP 字节填充

PPP 分配IP地址 + IPCP

