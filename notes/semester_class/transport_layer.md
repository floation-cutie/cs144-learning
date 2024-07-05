### The Transport Layer

#### The Transport Service

网络层不考虑可靠传输，对应职责由传输层实现

It is the heart of the whole protocol hierarchy

It provides reliable data transport **end to end **

It masks the diversity of communication subnets, provide a common interface to the upper layer (沙漏型层次)

* It provides **multiple SAPs** sharing one network link 服务访问点

传输层提供应用进程之间的逻辑通信 将网络层延展到APs

#### Network,Transport,Application Layers

虚电路服务在某些特定网络层协议（如X.25和帧中继）中确实提供了可靠传输，但这并不是网络层的一般特性.

Transport entity <–> Segment <–> Transport entity 传输层实体 传输报文段

##### Question

For network service, 虚电路&数据报；

For transport service, TCP & UDP

Why are there two distinct layer？Why is one layer not adequate?

##### Answer 

网络层和传输层提供的服务虽然在某些方面类似（都有连接导向和无连接服务），但它们的对象、功能和设计目标是不同的。

网络层关注的是不同网络之间的路由和数据包转发，而传输层关注的是在两端应用程序之间提供可靠的数据传输服务。

分层模型中的这两个层次各司其职，共同保证了数据通信的高效性和可靠性。

#### Nesting of segment, packet and frame

Frame Header, Packet Header, Segment Header , Segment payload

TPDU = Transport Protocol Data Units

socket is used for interface that transport layer provides to the upper application layer

**Socket Bind Listen Accept Connect Send Receive Close**

connect 主动连接的时候会 自动分配可分配的IP地址和端口号
进程会在多种情形下阻塞

#### Elements of Transport Protocols

##### Comparsion betweeen Transport Protocol & Data Link Protocol

Both have to deal with error control, sequencing and flow control

###### Environment differences

* Address of destinations (寻址复杂)
* Initial connection establishment
* Stroage capacity in the subnet (传输层子网有存储能力)
* Allocation of buffers (链路层分配缓冲区的内容简单，连接设备少)
* A large and varying number of connections with bandwidth that flutuates as the connections complete with each other(分配带宽 竞争处理)

##### Addressing

TSAPs 传输层的服务访问点 NSAPs 网络层的服务访问点

Service Access Point 端口号 + IP

* Get the Server’s TSAP (静态：指定服务TSAP 动态：Look up a name server or **directory** server 根据服务名确定TSAP)
* Process server 
  For rarely used processes, it is wasteful to have each of them active 

Process server and time-of-day server 一些服务放置在磁盘上

#### Connection Establishment

If still use two-hand, **Network can lose, store and duplicate pakcets**

数据链路层链路无存储能力 不会出现先发送的数据报文后到达的情形

而传输层的子网存在存储能力 

有可能已失效的TCP连接请求报⽂段突然又传送到了TCP服务器进程，

因而导致错误。

The TPDU could be delayed or duplicated

##### Solution

* Use throwaway transport address (but the address is finite)
* Give each connection a ID, but a crashed machine can’t know which identifier have been used
* Each connection starts numbering its segments with **different initial sequence number ISN**
* Set Recovery Time 

##### Three-way Handshake

本质原因 ：网络会存储

CR connect request (seq = x )

ACK (seq = y ACK = x)

DATA (seq = x ACK  = y)

**one host use two-way handshake to trust the other host**

So we use **three-way** to simplify the **four-way handshake** 

To prevent **Old Connection Request and Duplicate Connection Request and ACK**

#### Connection Release

1. Asymmetric Release **abrupt** may result in data loss
2. Treats connection as two separate unidirectional connections

避免infinite loop,最终阶段 ack的确认无法达成一致，故不能立刻断开连接

==two-army Problem== 

**Releasing a connection** means 

* The transport entity removes the information about the connection from its table of currently open connections and signals **the connection’s owner** (the transport user)

##### Half-open Connections

When the initial DR and N retransmissions are all lost, one host give up and release the connection, while the other side still keep connecting

==How should the host notice??== 发送Dummy TPDU(keepalive 发送心跳包 heartbeat) 发送前述已发送的数据包

#### Transmission Control Protocol

##### segment Header

source port 2字节 + destination port + Sequence number + Ack number + 8 bit 表示 Flags (SYN FIN RST ACK字段表示ack是否有效)

If a response to a FIN is not forthcoming within **two maximum packet lifetimes,** the sender of the FIN releases the connections

等待 **2 MSL** 4分钟

TCP header length has the same meaning compared with IP packet header

##### Notice

数据链路层的ACK确认的是最后一个成功接收到的帧，而传输层的ACK表示接收方期望下一个接收到的数据包的起始序列号,后者表示字节

三次握手SYN –> SYN-ACK -> ACK 如果过程中出现数据报的丢失,即重传保证双方正常建立连接

实际发送的第一个数据包序列号 和 第三次握手发送的ACK数据包的相同

**Reason** ==SYN包和FIN包实际占用一个序列号==

##### Finite State Machine

Release divided into three situation : 四次挥手 , 无单向传输, 同时断连

#### Error Control && Flow Control

Error-detecting code (检错)

ARQ  自动重传 -> 停等 和 滑动窗口

###### Source Buffering & Destination Buffering

对于接收方的缓存 ==Decouple buffering from ack== 同时告知ACK和缓存

Variable sized windows: Dynamic buffer management **避免潜在的deadlock** –通过重发过去的数据 

There’s two control factor

* Buffer space availabe in the receiver 端点角度
* The capacity of the subnet 网络角度

piggybacks both ack and buffer allocations onto the reverse traffic

#### Congestion Control

##### Desirable Bandwidth Allocation

拥塞控制 **combine network layer with transport layer**

* Congestion occurs at routers, so it is detected at the network layer
* ==The only effective way== is for the transport protocols to send packets into the network **more slowly**

Nowadays, Internet relies **heavily** on the transport layer for congestion control

Goals:

1. Avoid congestion —— Prevention
2. Good allocation of bandwidth efficiently
3. Be fair across competing transport entities
4. Quickly track changes in traffic (convergence收敛速度)

拥塞坍塌 congestion collapse  

根据实际吞吐量和网络发出的数据量之间的关系

==Use delay to sense congestion== 

Onset of congestion 延迟的抖动

对于单个的通信实体，他通过看延迟的变化时间判断拥塞

**power = load / delay**

拥有最大的power的load表示传输层实体中最有效的load

###### Max-Min Fairness

最大最小公平分配算法的形式化定义如下：

- 资源按照需求递增的顺序进行分配
- 不存在用户得到的资源超过自己的需求
- 未得到满足的用户等价的分享资源

The bandwidth control can’t be done in network layer

优先满足需求最小的用户，然后依次满足需求更大的用户，直到资源耗尽

进一步扩展到按权分配稀缺资源

Host-Host or **L4 connection** (不同的连接的视为不同的实体)

###### Convergence

The algorithm should rapidly converge to the ideal operating points, and it should track that point as it changes

##### Regulating the Sending Rule

限制因素 两大限制 – 流量限制 和 拥塞限制 

Small-capacity receiver and internal congestion

###### Feedback from Network

XCP – signal : tell the rate to use, it is explicit and precise

经典TCP: packet loss 选择丢包

TCP with ECN : congestion warning, 通过沿途的路由器上的ECN标记，接收方收到之后通知发送方江苏 explicit but not precise

Fast TCP: signal is End-to-End delay 端到端时延抖动分析 not explicit and precise

Compound TCP: packet loss && end-to-end delay…

**The control law** 

If no congestion signal, senders should **increase** their rates

When a congestion signal is given, senders should **decrease** their rates

那么具体如何加速降速呢?

![image-20240610144027858](C:\Users\WESLEY\AppData\Roaming\Typora\typora-user-images\image-20240610144027858.png)



分析该图: 过原点的45° Fairness line 公平线，表示两用户之间User’s bandwidth相同

Efficiency line效率线与公平线之间的交点为 Optimal point即最优点

四种调节方法 –> Additive increase / Additive decrease / Multiplicative increase/ Multiplicative decrease

​				数值变化 与 倍数变化

###### AIMD Control Law (Additive Increase Multiplicative Decrease)

算术增 乘法减 converge to optimal point **both fair and efficient**

###### AIMD Used by TCP

==However, we can’t adjust the rate directly==

We can only **adjust the size of a sliding window**

计算等价速率 **the equivalent rate** = $\frac{W(the-window-size)}{RTT(round-trip-time)}$

这里的W表示窗口大小字节数 不等同于帧数

 Be easy to **combine with flow control**,and the sender **paces packets using acknowledgements** 

==The closer hosts receive more bandwidth than connections to distant hosts==

#### TCP congestion control

TCP 同时维护一个拥塞窗口 congestion window (cwin) 一个流量窗口(flow control window) 而发送窗口为二者的较小值

TCP通过packet loss 作为拥塞信号**congestion signal** 原因是现有的链路差错很罕见

而对于802.11协议，其丢包率很高，不适用这种方法，其有自己的重传机制

**How to set a TCP timer accurately?**

* The timer includes estimates of the **mean** and **variation** in RTT

##### Two Problems in Practice

1. The way packets are sent into the network 

   **It must be matched to the network path, otherwise the traffic will cause congestion**

2. The initial congestion windows size
   can’t be too large or too small 

   初始窗口过小时，线性增到optimal point的时延太大
   初始窗口过大时，会直接导致网络拥塞
   理想值为 线路约束最小速率 x RTT往返时间

##### ACK Clock

* The timer for the ACKs **reflect** the times at which the packets arrived at the receiver after crossing the slow link
* As the ACKs travel over the net and back to the sender, they preserve the timing
* If TCP injects packets **at the rate of ACKs returned**,packets will be sent as fast as the slow link permits, they will not queue up and congest any router along the path.

##### Slow Start

* the cwin is **initialized** to a value of 1 or 4 segments

* For **each** ACK, adds one segment to the cwin(exponential growth)

* slow start is actually compared to set entire windows size slow

###### Slow Start Threshold

当在向慢启动阈值增加的过程中，如果检测到丢包，将ssthresh 的值减少为一半，然后重新开始慢启动

若正常到达ssthresh,进入Additive Increase Mode(通过修改窗口大小)

##### TCP Tahoe (老版本)

将新的Threshold设置为拥塞峰值的一半

##### Fast Retransmission

For the sender to recognize quickly that one of the packets has been lost:

As the packets beyond the lost packet arrive at the receiver, they trigger ACKs, there ACKs have **the same ACK number**

If the sender receives 3 duplicate ACKs imply that a packet has been lost. The packet is retransmitted before timeout, otherwise we have to restart the Slow-Start Process again!

##### Fast Recovery

* The new threshold is set to half of the current cwin at the time of fast retransmission

* From now on, count down the duplicate ACKs on the network, until it falls to the new threshold(Without sending new packets)
* Then a new packet can be sent for each duplicate ACK that is received
* After one RTT, the lost packet has been ACKed, meaning that the capacity of network has decreased, change to the addictive increase mode

##### TCP Reno

with some new options, SACK and ECN,通过通信双方和路由器之间的协商确认，对于Selective Acknowledgements,在发送duplicate ACK的时候，同时设置SACK选项(以表示接收到的四个数据包边界)

ECN = ECE + CWR

#### UDP

No flow control, no error control, hardly bad segment

**can demultiplexing** 核心就是端口

首部只有八个字节

UDP Header checksum(optional) 

used in DNS NFS DHCP RIP

UDP提供消息边界，为消息流服务

#### TCP

是字节流服务，不是消息流服务

为TCP优化提供了方便 灵活 简单 适应

used in FTP SSH HTTP HTTPS

PUSH flag 用于即时的消息通信,作用于接收方，对于发送方只需要配置socket

对于UDP和TCP，他们的伪首部都用于帮助检测错发的分组

MSS默认为536字节，两方的MSS不需要相同	

RST bit used to refuse a connection

在TCP中的窗口管理 –> 接收方也是通过滑动窗口进行接收的，当窗口大小为0时，发送方会一段时间重传1-byte segment以验证ACK和window，防止死锁现象

#### Nagle’s Algorithm

应用场景：数据量小，对于大负载来说，网络利用效率低下

慢网络缓冲多，快网络缓冲少

对于Receiver,Delay ack and window update, 减少由发送方造成的负载浪费

对于Sender, 当最后一包ack到达或者缓冲的数据达到起码一个maximum segment,之后再发送分组

#### Silly Window

receiver should not send a window update until it can handlt the MSS or its buffer is half empty, which is smaller

#### TCP Timer

动态调整timeout interval, 这样设置其重传计时器，以重新Slow-Start

