### Medium Access Control Sublayer

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

Contention  Transmission or Idle

Which is a **half-duplex** system

##### Wireless LAN Protocols

无线电不能通过反馈的叠加信号检测冲突

Radio Transmitter & Receiver

> Wireless systems can’t detect a collision while it’s occurring, ACK are used to discover collisions

Hidden station(the interference at the receiver) 

Exposed station



###### MACA collision avoidance

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

HUB 逻辑上总线结构 物理上星型结构  dedicated cable

10BASE-T means 10Mbps and 基带信号 and twisted pair双绞线

由于物理上星型 –> 接收通信范围为半径

以太网的拓朴结构 Linear Spine Tree Segmented中继器(避免信号过于削弱)

#### Manchester Encoding

将时钟和bit stream XOR

#### Ethernet MAC sublayer Protocol

帧格式！！

1. DIX Ethernet
   Preamble前导 (准备信号) + Dest + Source + Type类型 + Data + Pad(填充) + Checksum
2. IEEE 802.3

Preamble前导 (准备信号) + SOF + Dest + Source + Length + Data + Pad(填充) + Checksum

将Type的范围超过 1500+ 两个字节

MAC Address 6 bytes

01 byte means multicast

###### Frame Length

1514 bytes Based on the fact that transceiver needs enough RAM to hold an entire frame

And the minimum frame is at least 64 bytes long **the minimum boundary**

To prevent a station from completing the transmission of the short frame 

before the first bit has reached the far end of the cable



**Collision detection can take as long as 2T**



###### Binary Exponential Backoff Algorithm

二进制指数退避算法

1st collision, choose random number 0 - 1 backoff **circle of the particular time**

… until 10 +th collision, every device backoff random circles

if 16 collisions still wrong, reports failure to higher layers



#### Switched Ethernet

Token Ring 令牌环 single,shared medium 

data always flows in one direction

The destination puts the frame back after receving it,but with a “special mark” 

Hub && Switch

Switch only output frames to the ports for which those frames are destined

with fast backplane 矩阵形式

For Hub,All stations are in the same collision domain

For Switch,Each port is its own independent collision domain



#### Fast Ethernet

802.3u : A Soaped-up Ethernet 向后兼容

Keep the old rules but make it faster

category 5 UTP use 125MHz

can negotiate the speed(10Mbps for 曼彻斯特 100Mbps for 4B/5B) and duplexity(half CSMA/CD / full)

autoconfigure

#### Gigabit Ethernet

go 10 times faster 并不完全兼容 

在半双工时:

Carrier Extension to remain the long distance

它在硬件上将帧扩展到512bytes (How to solve problem of short radius?)

Frame Bursting

802.3z  8B/10B coding

#### Flow Control

流量控制 Control Frames 告知CTS  or give a special control PAUSE frame

#### Wireless LAN

##### 802.11 Protocol

==one specific product implementation is WIFI==

access point (AP) base station  CSMA/CA

radios are always half duplex and can’t do collision detection(the singal is very weak)

**count down idle slots** 

if lack of ACK,double the backoff

the data and ACK internal is less than 30us

###### Channel Sensing

Each frame carries a NAV

Each station records when the channel is in use by tracking NAV network allocation vector

==To Increase Successful Transmissions==

lower the transmission rate

allows frame to be split into fragments



**IFS** 

what’s the interframe spacing in 802.11?

==SIFS==: short interframe space (allow the parties in a single dialog)

Here are some case

* ACK frames
* A burst of fragments
* other control frame sequences like RTS and CTS

==DIFS== regular data frames

==AIFS== arbitration interframe space   PCF



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

For **WDS**

**1.Recipient address 2.transmitter address**

**3.Destination address 4. Source address**

==BSS== means basic service set基本服务集





address 3: is optional MAC address of router interface to which AP is attached



LLC logical link control is taller than MAC protocol

#### Data Link Layer Switching

##### **Transparent Learning Bridge**

How to transmit from 802.x to 802.y？

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

避免已关机的站点长期占用一个表项

*  means if a machine is quiet for some time, any traffic sent to it will have to be flooded until it next sends a frame itself

##### **Spanning Tree Bridges**

分布式算法 distributed

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

Cut-through switches 快速交换机 不存储 直接转发

#### Virtual LANs

虚拟局域网使得在同一局域网内

avoid Broadcast storm & ensure Security

only set by the Bridges

**configuration tables** tell which VLANS are accessible via which **ports**

新增4个字节 protocol标志  有12Bits用于标识颜色

##### VLAN aware感知

第一个 VLAN 感知的网桥在帧上添加一个 VLAN 字段，路径上的最后一个网桥把添加的 VLAN 字段删除。