User are exposed to the actual machines直接操作硬件资源，而不是通过额外的中间件访问接口

802.11 Wireless LANs / Switched Ethernet Wired LANs

#### Channel allocation

信道分配
1. static allocation -> example: Divide time 将时间戳切片，允许不同的机器在其所分配的时间槽 time slot内进行广播 常见于局域网
2. Dynamic 
   1. 集中式
   2. 分布式

WAN中的subnet是指通信子网 只负责信息传输
Router中 进行分片功能 reassembled 将大数据包分片转发再重组

internet更广泛的称呼 Internet 最大的互联网

Subnet 路由器和通信链路的集合

Network subnet和its hosts的结合

internetwork 不同的networks互联

#### Protocol Hierarchies

Offering certain **services** to the higher layers 
**shielding** the layers from the details of how the services are implemented

peers 作为对等体 can be processes or hardware devices
The communicating parties reach a agreement on how the communication is to proceed
Information flow is vertical between layers and layers ---> the corresponding layers should "virtually" transimit the same message

message --> segment --> datagram --> frame

#### Design issues for the layers

1. Reliability 
   1. 纠错检错
   2. Routing path
2. Network evolution 
   1. Protocol layering 
   2. Addressing and naming
   3. Internetworking
   4. Scalability
3. Resource allocation
   1. Statistical multiplexing(统计复用 按需分配)
   2. Flow Control
4. QoS
5. Security

差错 + 失序out of sequence

#### Service primitives

原子信息

The sender and receiver are both a process on a machine

SAP – Service Access Point 服务访问点

PDU – 协议数据单元 

通过一系列元语操作

If the protocol stack is located in the operating system, the primitives are normally system calls

Services and protocol are completely decoupled

传输层Transport —– 会话层Session  —- 表示层Presentation —— 应用层 Application

#### Different Layers’ usage

物理层 比特流的传输 定义传输类型 电气标准 传输速率 定义传输模式(全双工…)  数据编码方式

数据链路层 可靠传输 差错控制 封装成帧 透明传输 流量控制 介质访问控制子层 逻辑链路控制子层

网络层 转发 路由 差错处理 异构网络互联 

传输层 端到端通信 数据不丢失 可靠传输 流量控制 拥塞控制

会话层 进程管理

表示层 数据加密解密

