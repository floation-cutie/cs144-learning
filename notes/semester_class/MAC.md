### Medium Access Control Sublayer

**这一章很重要** ==以太网相关知识== 

媒体访问控制 – –多点通信(广播) 比datalink层次更低

在局域网中非常常见 分配信道

#### Channel Allocation Problem

M/M/1 System

排队论

P[k]服从泊松分布 $T = \frac{1}{\mu - \lambda}$ Incoming number is K in period T 

$\lambda$ 表示平均到达率 frames / sec

$uC$ 表示平均服务率 C is data transmission rate (bits/sec)

$\frac{1}{\mu}$ 表示frame length (bits/frame)

  

##### Static Channel Allocation

分频 分时 

From Single Channel to Divide the channel into N

$T_{sub} = \frac{1}{\mu C/N - \lambda / N} = NT$ 

the mean delay increase to the N times of the original one

##### Dynamic Channel Allocation

Assumption:

1. ==Station Model==
   N independent stations
   the probability of generating frame is $\lambda \times T$ for time internal $T$
2. every channel is equivalent
3. all stations can detect collisions 
   1. for wireless, by infer of ACK frame
   2. for wire channel, by detect the feedback signal
4. Continuous Time && Slotted time
   1. For slotted time, Frame transmissions can be 0,1 or more frames in a single slot
5. Carrier Sense 载波
   用于other stations detect if the channel is being used



##### ALOHA

上行线路: use a shared channel

下行线路: for different unique terminal, it marks and distinguish

Each station transmit frames arbitrarily 

And sender will resend frames after a **random** time if collisions occurs

###### Performance Analysis

Defining Vulnerable time

collide with the start or end of the shared frame –> defines $2\times T $ 

1. Throughout S : successful frames per frame 归一化 0 <= S <= 1
2. Network load G : G >= S
3. S = G * P0 ==successful transmission==

$S = G \times e^{-2G} $  



**Slotted ALOHA**

$S = G \times e^{-G} $

each internal corresponding to one frame –> each user must know the slot boundaries

##### CSMA protocols

载波监听

Station listens for a carrier before Sending 

###### 1-persistent CSMA

if the channel is busy,waits until it becomes idle

空闲时直接传输



**Still can get collision** if a collision occurs, waits for a **random** amount of time 

Reason: The carrier propagation also has a particular time, two sides may transfer  information to each other

if collision occurs,wait for a random amount of time and start all over again减少了媒体利用率的损失

缺点是如果多个站点发送数据，冲突不可避免

###### Nonpersistent CSMA

if the channel is busy,wait for a random time and **sense the channel again**

==High throughtout when high load==

###### p-persistent CSMA

in a slotted channel 

Step：

1. If the channel is busy, waits to the next slot
2. If idle, transmit frame with probability p,
3. else wait for the next mini - slot and repeat

###### Collision Detection CD

aborts transmission as soon as it detects a collision

一边发送 一边监听 Only in Contention period and contention slots，collisions may happen在竞争周期中

**The whole three states of CSMA/CD:**

Contention  Transmission or Idle 三种状态

Which is a **half-duplex** system  半双工系统

##### Wireless LAN Protocols

无线电不能通过反馈的叠加信号检测冲突

Interference at the **receiver**,not at the **sender** (so the sender can’t detect if there’s collision)

Radio Transmitter & Receiver

> Wireless systems can’t detect a collision while it’s occurring, ACK are used to discover collisions

Hidden station(the interference at the receiver) 

Exposed station

PCF and DCF 

Point Coordination Function use **the base station** to control all activity in its cell 单点控制

Distributed Coordination Function 

分布式管理

###### MACA multiple access with collision avoidance 

The wireless communication has range limit

A send a RTS(request to send 请求发送) frame to B (30 bytes, contains data length)

B replies with a CTS(clear to send 允许发送) frame to A (contains data length from RTS)

**other stations who only hear RTS but no CTS:**

it can send data to other free stations and infer how much time he needs to wait for the RTS station

**other stations who only hear CTS but no RTS:**

it remains silent

**stations heard both:**

must be silent until the data frame is complete



#### Ethernet

以太网电缆

早期同轴电缆和集线器的工作逻辑保持为 总线逻辑

HUB 逻辑上总线结构 物理上星型结构  dedicated cable

MAC: 目标在前 IP：目标在后

**速度的发展** 10Mb/s (曼彻斯特编码)—> 100Mb/s —-> 1Gb/s —> 10Gb/s

**类型的发展** 早期为共享式以太网

需网络适配器Adapter

10BASE-T means 10Mbps and 基带信号 and twisted pair双绞线

由于物理上星型 –> 接收通信范围为半径

以太网的拓朴结构 Linear Spine Tree Segmented中继器(避免信号过于削弱)

==为什么共享以太网的总线长度不能太长?== 

总线长度越大，端到端时间延迟越长，发生碰撞的概率越大

#### Manchester Encoding

将时钟和bit stream XOR

#### Ethernet MAC sublayer Protocol

帧格式！！

1. DIX Ethernet
   Preamble前导 (准备信号) + Dest + Source + Type类型 + Data + Pad(填充) + Checksum 32位
2. IEEE 802.3

Preamble前导 (准备信号) + SOF + Dest + Source + Length + Data + Pad(填充) + Checksum

将Type的范围超过 1500+ 两个字节

MAC Address 6 bytes

01 byte means multicast

###### Frame Length

最大最小帧长度

1518 bytes Based on the fact that transceiver needs enough RAM to hold an entire frame

And the minimum frame is at least 64 bytes long **the minimum boundary**

To prevent a station from completing the transmission of the short frame 

before the first bit has reached the far end of the cable

最大1500 最小46，如果更小，填充至46

**Collision detection can take as long as 2T**

2T被标准规定了为51.2us

最小帧长是可以被计算得到的 51.2us * 10Mb/s  = 512b = 64B

###### Binary Exponential Backoff Algorithm

二进制指数退避算法

1st collision, choose random number 0 - 1 backoff **circle of the particular time** ==2^n - 1==

… until 10 +th collision, every device backoff random circles

if 16 collisions still wrong, reports failure to higher layers停止发送



#### Switched Ethernet

交换机也是用STP生成树协议

**本质上就是多接口的网桥** 全双工 && 自身内部同时连通多对接口 不是CSMA/CD

扩大了广播域 隔离了冲突域

现代交换机可以自动识别连接模式，并进行自配置

Cut-through 增加了数据链路的负担

==存储转发orCut-Through==  接收完目的MAC地址就开始转发，此时的转发延迟为 6 * 8 / 100  = 0.48us

Token Ring 令牌环 single,shared medium 

data always flows in one direction

The destination puts the frame back after receving it,but with a “special mark” 

Hub && Switch

Switch only output frames to the ports for which those frames are destined

with fast backplane 矩阵形式

For Hub,All stations are in the same collision domain

For Switch,Each port is its own independent collision domain



#### Fast Ethernet

100Base-T

802.3u : A Soaped-up Ethernet 向后兼容

Keep the old rules but make it faster

category 5 UTP use 125MHz

**最小帧长不变 最大长度从1000m减少到100m 争用期缩短到5.12us**

使用了以太网交换机

can negotiate the speed(10Mbps for 曼彻斯特 100Mbps for 4B/5B) and duplexity(half CSMA/CD / full)

autoconfigure

#### Gigabit Ethernet

go 10 times faster 并不完全兼容 

**如何提升速率呢?** 减少网段长度或者增大最小帧长似乎最好

**但是**千兆以太网网段长度若减少到10m,无利用价值

若最小帧长提升到640B,开销太大

##### How does Gigabit Etherent improve speed?

在半双工时

**Carrier Extension to remain the long distance** 进行载波延伸(填充字节，使争用期为512字节)

**它在硬件上将帧扩展到512bytes** (How to solve problem of short radius?)

==争用期进行帧扩展== Key： 帧扩展 + 帧突发

**Frame Bursting** 进行分组突发(连续发送短帧，减少overload)

802.3z  8B/10B coding

需要注意的是, 在全双工时，这些都不需要存在



#### 万兆以太网

只有全双工 —> 不再考虑碰撞检测了

#### Flow Control

流量控制 Control Frames 告知CTS  or give a special control PAUSE frame

10Gb Ethernet 为64B/66B code

#### Wireless LAN

##### 802.11 Protocol

==one specific product implementation is WIFI==

access point (AP) base station  CSMA/CA

1. 有固定基础设施的 基站AP 最小构件BSS
2. 无固定基础设施的 ad hoc Network 对等的移动站点

radios are always half duplex and can’t do collision detection(the singal is very weak)

有隐蔽站问题

第一步 等待DIFS 帧间间隔 以便使高优先级的帧先发送

**count down idle slots** 

如果被占用 — 冻结剩余时间

if lack of ACK,double the backoff

the data and ACK internal is less than 30us

###### Channel Sensing

Each frame carries a NAV

Each station records when the channel is in use by tracking NAV network allocation vector

调整自己的NAV **虚拟载波监听机制**

CSMA/CD在共享式以太网没有确认机制 

CSMA/CA在无线信道(误码率比较高) 需要确认机制 采用停等协议 **ACK** 

==To Increase Successful Transmissions==

lower the transmission rate

allows frame to be split into fragments



**IFS** 

what’s the interframe spacing in 802.11?

==SIFS==: short interframe space (allow the parties in a single dialog) 最短的帧间间隔

Here are some case

* ACK frames
* A burst of fragments
* other control frame sequences like RTS and CTS

==DIFS== regular data frames

==AIFS== arbitration interframe space   PCF

DIFS > SIFS

##### Saving Power

Beacon frames by AP 信标帧  Client can enter power-save mode

AP will buffer the traffic and the client send a poll message to the AP

自动省电

**APSD**  the AP buffers frames and sends them to the client just after client sends frame message

###### TXOP

从均等发送帧数  ——> 均等发送时间

the original CSMA/CA let stations ==send one frame at a time==

if different speed stations collide, and both has same chance to transmit **Decrease the total quality**

> Each station get an equal **amout of airtime**



WiFi Frame is unique

数据帧 + 控制帧 ACK rts cts+ 管理帧

For **WDS**

AP地址 + 源地址 + 目的地址

以太网中 网桥透明 802.11 AP不透明

**1.Recipient address 2.transmitter address**

**3.Destination address 4. Source address**

==BSS== means basic service set基本服务集

address 3: is optional MAC address of router interface to which AP is attached

LLC logical link control is taller than MAC protocol

#### Data Link Layer Switching

在数据链路层上扩展以太网 - - - 分离不同的碰撞域

**转发表** [地址，接口，时间戳] 

> 网桥的接口在向其连接的网段转发帧时，会执行相应的媒体接入控制协议，对于共享式以太网就是CSMA/CD协议



##### **Transparent Learning Bridge**

How to transmit from 802.x to 802.y？

What’s **transparent**? 以太网的各网桥对于**各站点**而言是看不见的 802.1D标准

透明网桥!! 通过backward Learning

Split a single LAN into separate LANs to accommodate the load

同一网段进行内部的划分，实现LAN之间的数据传输

or use the bridge to create a extended LAN.

It takes a station table,list the destination and tell which output line it belongs on

*flooding algorithm*

Init & Add 

==Dynamic topologies==

the topology can change as machines and bridges are powered up and down and moved around 

Solution:

**Add the arrival time of frame to the table entry and update it**

Periodically scan the table and **purges** all entries too old

每条记录有时限

避免已关机的站点长期占用一个表项

*  means if a machine is quiet for some time, any traffic sent to it will have to be flooded until it next sends a frame itself

##### **Spanning Tree Bridges**

分布式算法 distributed

STP —–> BRDU

###### Problem

Loops in the topology

To **increase reliability**,some sites may use two or more bridges in parallel between pairs of LANs

This introduces problems that need to discard the loop frame

###### Solution

802.1D

The interconnected port can be connected physically

but can disconnected logically

每个网桥周期性地向自己的各个端口multicast message

这个消息中包含基于自己MAC address的ID号(占两个字节)

它认为的根网桥 root 的ID

其到root的distance距离

选择具有lowest ID的bridge作为root 

After  enough messages exchanged,all bridges will **agree on the root**

记录**Root Port ** of Every Bridge 每个网桥的根端口

**Designated Port** 

Repeaters，Hub,Bridge,Switch,

中继器实现物理信号的放大

Speical-purpose CAM 内容查询比较 ==VLSI== 集成芯片

Cut-through switches 快速交换机 不存储 直接转发(需要先查看完目标MAC地址)

##### Remote Bridges



#### Virtual LANs

虚拟局域网使得在同一局域网内划分为不同的网段

隔离广播域 

**avoid Broadcast storm & ensure Security**

only set by the Bridges 不改变实际的网络设备的内部配置

> 属于同一VLAN的站点之间可以直接进行通信，不同的VLAN中的站点不能直接通信

连接在同一交换机可以属于不同的VLAN

802.1Q帧

**configuration tables** tell which VLANS are accessible via which **ports**

新增4个字节 protocol标志  有12Bits用于标识颜色VID 所属VLAN的编号

##### VLAN aware感知

第一个 VLAN 感知的网桥在帧上添加一个 VLAN 字段，路径上的最后一个网桥把添加的 VLAN 字段删除。

打标签 和 去标签 处理

接口类型分为Access 和 Trunk

默认接口VLAN ID为1 接口类型默认为Access

Trunk类型用于交换机之间或 交换机与路由器之间 的互连