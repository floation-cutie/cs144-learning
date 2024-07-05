### Network Layer

#### Overview

The lowest layer that deals with **end to end** transmission, the datalink layer is about **point to point** transmission

- 端到端强调的是通过网络边缘（终端）进行复杂处理和控制。
- 点到点强调的是直接、独立的连接，不依赖中间节点。

Avoid **overloading** some of the communication lines and routers while leaving others **idle** 

#### Design Issues

1. Services **provided** to Transport Layer
2. Internal Organization of Network Layer (Store-and-Forward)

设置统一的地址交给传输层 

1. Connection-Oriented (虚电路 Virtual Circuit)
2. Connectionless Service (数据报 Datagram)

Datagram search for routing table(Need to big)

But the datagram may arrive out of order,due to connectionless

##### Virtual Circuit

Within a virtual-circuit subset

In — Out – In — Out has routing table order(虚电路号)

The datagram subnet don’t need circuit setup

The datagram subnet’s each packet contains the full source and destination address rather than a short VC number.

Routers don’t hold state information about connections, but need to route each packet independently.

The datagram subnet can’t achieve congestion control.

#### Routing Algorithms

How to construct a routing table? No matter the datagram subnet or virtual circuit subset.

For VC:

Routing decisions are made only when a new virtual circuit is being set up.(**Session routing**) 会话路由

For Datagram:

the decision must be made anew for every arriving data packet since the best route may have changed since last time(**Update**)

转发Forwarding 对于每个包

Routing 路由是设定规则

##### Goals

 Simplicity like the spanning tree Algorithm

Robustness : Avoid the crash router affect all the network devices

Optimality : Minimizing mean packet delay, Maximizing total network throughout…

Classification ::

1. Nonadaptive algorithms (Static Routing) 配置静态路由表

   1. Don’t base routing decisions on the current traffic and topology
   2. The choice of the route is downloaded to the routers when the network is booted

2. Adaptive algorithms 自适应

   Reflect changes in the topology, and usually the traffic as well

#####  The Optimality Principle

Every router runs at its own optimal path, avoiding the loop circuit.

##### Sink Tree

From all sources to a destination form a tree rooted at the destination

##### Shortest Path Routing

The weight value is largely dependent on yourself

1. Hops
2. Geographic distance in kilometers
3. Mean queueing and transmission delay
4. A function of all the factors

关键是形成统一的拓扑结构图

##### Flooding Algorithm

对网络信息不需要明确知晓

Eventually a number of copies will arrive at destination, but the downside is when the topology graph has local loop,the packets will be retransmitted infinite times

Unlike the Transparent Bridge,which use STP (Spanning Tree Protocol) to solve the potential of  infinite loop when flooding…

#####  Techniques for Damping the Flood

1. Header of each packet contains a **hop number**
   when hop event triggered, decrement the counter, discard the packet when the counter reaches zero
2. **Add sequence number** in each packet
   Each router records maximal seq per source 
3. Each data items contains **version number**

洪水算法用于通知所有节点网络中统一的路由信息

##### Distance Vector Routing

routed by surrounding routers

Router maintains a table (destination, distance, 接口line, next hop)

The table is updated by exchanging information with neighbors

1. RIP (routing information protocol) 周期性更新
2. Triggered update

Update by order each iteration –> until nothing changes

算法问题:

Count-to-infinity Problem

**Set infinity to 16** 

The problem is when X tells Y **some path**,Y itself has no way of knowing whether itself is on the  path

##### Path Vector Routing

BGP-4 IDRP

##### Link State Routing (通用)

掌握topology graph

1. Discover its neighbors,learn their network address
2. Measure the delay aka the cost metric
3. Construct a LSP (link-state packet) 
4. Send the packet to **all other routers** (==reliably==)
5. Compute the shortest path to every other router

==The LSP has its own owner who has unique authority==

1. Through HELLO packet broadcast in broadcast network,unicast in multi-access network
   The topology need to be simplified

###### Use Artificial Node

赋予虚权值 0

2. Measuring Line Cost

proportional to the bandwidth of the link (The routing tables may oscillate)

3. Building LSP(分组字段中包括 seq, age, neighbors and their distance)
4. Distributing LSP (avoid from using different **versions of the topology**)

###### About Link State Packet

The sequence number can be regarded as **version number**

If LSP is new, the seq number is larger, forward it on all lines 

If a router is down, and restart, The message can exist for some time

The restarted router number will be updated depending on other sites

Consider seq number wrap around situation                         

**Age**

duration of one site,When a connection was deleted(删除而非死亡)

发布新版本的老死消息	

==构造以某个节点为根的最短路径树== –> 构造路由表

IS-IS (路由器协议)  IPX / IP / AppleTalk…

OSPF (open shortest path first)

##### Hierarchical Routing

每个路由表的配置项太多了 So divide the Internet into **different region**

不同于链路层,这是网络层层次化路由

#### Congestion Control Algorithm

拥塞控制 congestion collapse

flow control & congestion control 

They are different,the latter one is global issue

##### Approaches

* Preventative
* Network provisioning
* Traffic-aware Routing(流量感知) 同时避免流量震荡 分布式算法无法解决
* Admission Control (准入控制)
  * 用于虚电路网络 
  * Traffic descriptions –> rate and shape
* Traffic Throttling(进行节流)
  * tell the sender to **slow down**(传输层控制)
  * determine congestion 计算平均值 $d_{new} = \alpha d_{old} + (1 - \alpha) s$
  * 发送choke packet(抑制包) or ECN(tag the congested packet) and the destination note the congestion and inform the sender (搭载bit)
  * And hop-by-hop choke packets
* Loading Shedding(丢包)
  * 丢弃对象–> 随机 or 新数据(file transfer) or 旧数据(multimedia) or  packet priority
  * RED – randomly early detection 丢包导致传输层源端降速

#### QoS

Reliability Delay Jitter抖动 Bandwidth

##### Traffic Shaping & Policing

 流量整形和监管

###### SLA

按照committed access rate承诺的访问速率

User adjust **average rate** and **burstiness** ,smooth out traffic 

Carrier monitor a traffic flow, mark as having lower priority

##### Bucket Algorithm

漏桶算法,network polices traffic, host shapes burstiness

令牌桶 –> 权利 本身也是突发量 average rate

##### Length of Maximum Rate Burst

Bucket capacity B bytes

token arrive rate R bytes/sec

Maximum output rate M

burst length S sec

$B + RS = MS$

原有量 + 补充量 = 消耗量

##### Packet Scheduling

分组调度 ==different flows can reserve different resources==

FIFO顺序 RED随机 

FQ: Fair Queueing algorithm(均分) Round-robin

WFQ:加权 带宽切割

PQ: Priority queueing

#### Internetworking

网络互联 Networks differ

1. Service offered 
2. Addressing (flat or hierarchical)
3. Broadcasting
4. Packet size
5. Ordering and unordered delivery
6. Parameters and Reliability..

##### How to connect those networks

###### Two choices

1. translate or convert packets from each kind of networks into packets(翻译)
2. Add a layer of indirection(间接层) and build a common layer on top of the different networks

Source(802.11) <–> router <-(MPLS)- >router <–> destination(Ethernet)

router之间采用Virtual circuit

Data from transport layer –> 虚拟层上传输

##### Bridge &  Router

the entire frame is transported on the  basis of its MAC address **For Bridge**

the packet is extracted from the frame and the Layer-3 address is used for deciding where to send it **For Router**

这两种方式中IP包的源地址和目的地址都不发生改变

##### Tunneling

If the source and destination hosts are on the same type of network

but the intermediate network on the path

the network that results is called **an overlay** (称为覆盖网络)since it has effectively been overlaid on **the base network** (称为基础网络)

​	网络进行包装 VPN (virtual private networks)

##### MTU

Hardware limitation(the size of an Ethernet frame) 

###### Fragmentation(分片)

Fragment and reassemble the fragments

==ATM== recombination occurs at the exit gateway

==IP== recombination occurs only at the destination host

* For transparent fragmentation 
  (has overhead in the internet) **exit gateway ** must know when it has received all pieces, and all packets must exit via the same gateway (适合虚电路)
* Nontransparent fragmentation
  Recombination only occurs at the destination host, the total overhead increases because **each fragment must have a header, a whole packet is lost if any of its fragments are lost**

###### Numbering

1. the packet number (id 编号) 
2. Offset Number of the first elementary fragment in the packet
3. End of the packet bit (判断后续是否还有分片) if the bit is 1,it is the end

The offset is about the **data itself,not include header**

##### Solution of Getting Rid of Fragmentation

In modern Internet, we use **Path MTU discovery**

###### One slightly simple way

from source, IP packet is send with its header bits **set to indicate that no fragmentation is allowed**

If a **router** receives a packet that is too large, it generates an error packet, returns it to source and **drops the packet**

When the source receives the error packet, it uses the information inside to re-fragment the packet into pieces that small enough

the process repeated…

###### More modern way

In TCP connection, we negotiate the common maximum segment size (在传输层建立连接过程中即协商报文段大小)

#### The Network Layer in the Internet

##### The top10 principles

1. Make sure it works (need multiple **prototypes**)
2. Keep it simple
3. Make clear choices
4. Exploit modularity
5. Expect heterogeneity 异构网络
6. Avoid static options and parameters
7. Look for a good design; it need not be perfect
8. Be strict when sending and tolerant when receiving
9. Think about scalability
10. Consider performance and cost

##### The Internet’s Network Layer

The Internet is a collection of subnetworks (autonomous Systems) that are interconnected

**provide a best-efforts way ** to transport datagrams from source to destination

##### IPv4 Protocol

###### header structure

变长字段 each line has 32 bits

4bits - Version版本号 + IHL(Internet header length)首部长度 4bits **times 4 aka the unit is 32-bit words**

Differentiated services field区分服务 8bit 

* Originally, it was called **TOS** type of service 优先级 服务要求
* Now, the top 6 bits are used to mark the packet with its **service class** the bottom 2 bits are used for explicit congestion notification (ECN) information 
  **Actually, the last bit is used to distinguish with the original protocol, the true ECN information just need one bit**

Total length has **16 bits** ==include both header and data== 最大为65535

Identification (16 bits) **All the fragments of  a datagram contain the same Identification value** 

DF (don’t fragment) It is used as part of the process to discover the path MTU

MF (more fragments?) 

Fragment offset (13 bit) 

**Tell where  in the current datagram this fragment belongs** 

==so the unit of fragment offset is 8 bytes==

TTL (8 bits) **count time in seconds** 
It must be **decremented on each hop** (to avoid infinite loop in the router forwarding process)
 When it hits **zero**,the packet is discarded and a warning packet is sent back to the source host

Protocol field (8 bits) Which transport process to give it to (TCP/UDP…)

The header checksum(16 bits)  ==IPv6 has removed it==

* Verifies the header only 
* Must be **recomputed** at each hop

Source address + Destination address 32 bit –>(For CPU, it is convenient to access)

###### Some of the IP options

1. **Strict** source routing option
   * Gives the **complete path** from source to destination as a sequence of IP addresses
2. **Loose** source routing option
   * Requires the packet to traverse the **list of routers** specified, and in the order specified,but it is allowed to pass through other routers on the way
3. Record route option && the timestamp option

Why in IP protocol, the source address is at the head of the destination address?

To help error report and route trace, while the datalink layer aims to transport frame rapidly(Its destination MAC address is before source MAC address)…

#### IP Addresses

In the past time, address was assigned by ICANN

A, B, C class address are unicast address

###### Special IP address

全0 –> this 全1 –> all

This host: 0.0.0.0 ==used for DHCP protocol==

A host on this network : 0.0.Host-id ==only used for source address==

Broadcast on the **local network** : 255.255.255.255 ==各路由器均不转发== **避免广播风暴**

Broadcast on a distant network :net-id.255.255…  会进行路由器转发

127.(Anything) –> loopback 本地软件测试回环

###### Prefixes

The address is comprised of a **variable-length** network portion and a **host** portion

a network corresponds to a contiguous block of IP address space (**IP address block**)

###### CIDR

###### Routing aggregation

To reduce routing table sizes,combine multiple  small prefixes into a single larger prefix

First address –> Last address (How many?? ) –> Appropriate subnet mask 倍数要求

**As we can see, the assignment of network must have large waste**

###### Longest matching prefix routing

When all the IP address match, we will choose the more **precise** one

#### Routing Table

It’s an array of 

(IP address, netmask(describe destination network address),outgoing line, Next hop )

1. 与运算的操作速度快 
2. For each outgoing line, there may be multiple routers you can choose,aka next hop

间接交付(for routers) 与 直接交付(for computers)

##### Scan the routing table

Mask the destination address and comparing it to the table entry **looking for a match**

It’s possible that multiple entries(with different netmask lengths) match, in which case **the longest mask** is used

* If the mask length is the same, meaning they are equivalent router
* Choose the longest netmask lengths

Commercial routers use **custom VLSI chips** (TCAM) with these algorithms embedded in hardware

For backbone network, it can also have own computer devices

==Hosts and Routers all have their own routing table==

默认路由 对于主机为 0.0.0.0/0 往往网络结构中发送数据的路径和接收数据的路径可能不同

##### NAT

Network address translation

特点: 对于主机(客户端或服务器)和路由器来说，NAT的存在是完全透明的

For outgoing packet, source address and TCP source port are replaced, both the IP and TCP checksums are recomputed

For incoming packet, the Destination Port -> internal IP address and original TCP source port, and recompute IP and TCP checksums 

**There are three reserved ranges (10/8) (172.16.0.0/12) (192.168/16)**

###### 动态NAT表项

Router create the NAT table entry dynamically 

**Local – Global – Peer**

And the capacity of NAT extension is huge (The internal source address port + external source address port + destination address port)

###### 静态NAT表项

When 10.0.0.7 need to be Web server

**Local 10.0.0.7:8080 – Global 123.123.42.12:80 – Peer 0:0 ** 

###### Some of the objections to NAT

* It violates the most fundamental rule of protocol layering:
  The layer k may not make any assumptions about what layer k + 1 has put into the payload field
* Processes on the Internet  are not required to use TCP or UDP
* Some applications insert IP address in the body of the data….



#### IPv6

To reduce the size of routing table : How? By decreasing the number of entry

Simplify the protocol, to allow routers to process packets faster

##### Main IPv6 Header

The source IP address has 16 bytes 

It has a fixed length,removed the IHL field

remove the checksum field and remove the fields relating to fragmentation

**The TTL field is replaced by Hop limit field**

##### Extension IPv6 Header

##### Notation

8 groups of 4 hex digits with colons between the groups 

with 3 optimizations 

#### Internet Control Protocols

ICMP message is encapsulated in an IP packet

分为ICMP差错报告报文 && ICMP询问报文

* Destination Unreachable
* Time exceeded
* Source Quench
* Redirect
  差错报告
* Echo and echo reply
* Timestamp request and Timestamp reply
* The Router Advertisement and Router Solicitation

前四个字节 一字节类型 + 一字节代码(子类型) + 校验和

用于traceroute && 主机分片…

#### ARP

##### optimization

Other machines on the same Ethernet actually needn’t keep the IP/MAC mapping in ARP request into the ARP caches

###### Gratuitous ARP

host broadcasts its IP/MAC when it boots, an ARP looking for its own IP address (avoid IP collision)

##### Proxy ARP

代理路由器将自身的MAC地址交给本网段中的主机

#### DHCP

如何在局域网中进行IP编址？应用层程序

Dynamic Host Configuration Protocol

Allows both manual IP address assignment and automatic assignment

Discover –> Offer –> Request –> Ack (Using UDP)

需要DHCP Relay Agent中继服务器

#### OSPF (Open Shortest Path First)

路由协议

1. Interior Gateway Protocol 内部网关协议
   1. OSPF
   2. IS-IS
2. Exterior Gateway Protocol
   1. BGP-4 边界网关协议

层次化 AS自治系统 divided into numbered **area**

**only have one backbone area** area 0

**Within an area, each router has the same link state database and runs the same shortest path algorithm**

A router connects to two areas must keep different databases for both areas

stub area is the only router out

EGP 控制路由的传播和选择最佳路由