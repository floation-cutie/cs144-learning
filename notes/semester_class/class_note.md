#### Channel allocation 
信道分配
1. static allocation -> example: Divide time 将时间戳切片，允许不同的机器在其所分配的时间槽 time slot内进行广播 常见于局域网
2. Dynamic 
   1. 集中式
   2. 分布式

WAN中的subnet是指通信子网 只负责信息传输
Router中 进行分片功能 reassembled 将大数据包分片转发再重组

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

差错 + 失序out of sequence

#### Service primitives
原子信息