####  The properties of different kinds of physical channels

1.bandwidth 频率范围Hz

2.Throughout 单位时间传输数据位数 bps

3.Delay

* processing: 检错check bits/ 选路 deciding link
* Queuing: Waiting at output link
* Transmission：发送时延 Packet Length / link Length 
* Propagation: d / s

Something about “propagation” : [backward propagation](https://www.youtube.com/watch?v=ibJpTrp5mcE)



Simplex Half-duplex Full-duplex 单工,半双工…

Asynchronous transmission: 即异步传输 

数据以不定时的间隔发送，发送端和接收端之间没有共享的时钟信号 需要特定的标志位标记数据段的起始

异步串行传输 : 通过字符为单位传输 独立时钟

同步串行传输 : 比特同步 且 以数据块传输

####  theoretical analysis of data transmission

Review of  **Fourier Analysis**





==The Sample Rate must at least greater than or equal to the Data BandWidth,so that It can reconstruct the original Data== 	

 the ratio of the signal power to the noise power, called the **SNR** (**Signal-to-Noise Ratio**)

SNR is used to measure the amount of noise

And $10 \times \log_{10}{S / N} $ is defined as UNITs ==dB== decibels

 Shannon : maximum number of bits/sec = *B* log2 (1 + *S/N*) 注意单位 

#### Guided Transmission Media

内部传输数据信号时，信号被限制在某种物理介质内部传播的通信媒介 35051

##### Magnetic Media

磁带or光盘

##### twisted pair

 A signal is usually carried as the difference in voltage between the two wires in the pair. 

This provides better immunity to external noise because the noise tends to affect both wires the same, leaving the differential unchanged.

Bandwidths factor: distance travelled and the thickness of the wire

**UTP** (**Unshielded Twisted Pair**) 

##### coaxial cable

Two kinds of coaxial cable are widely used. 

One kind, 

50-ohm cable, is commonly used when it is intended for digital transmission from the start.

 The other kind, 

75-ohm cable, is commonly used for analog transmission and cable television.

##### Power Line

##### Fiber optic cables

#### Wireless Transmission

#### digital modulation

模拟信号和比特之间的转换过程 即 **数字调制**

基带信号 and 宽带信号

##### baseband transmission

适用于近距离传输，信号衰减小

Line Codes线路编码方案

NRZ  高一低0 需要额外信道传输时钟信号

NRZI 跳变表示1 不跳变表示0 不适用于信号中0的比例高的情形

Manchester 将一个码元分为两个相同的间隔，前一个间隔高，后一个间隔低表示码元1

Feature: 每一个码元的中间出现电平跳变，位中间的跳变既作为时钟信号(可用于同步)

也用于数据信号，但它所占用的频带是原始基带宽度的两倍

差分曼彻斯特编码

###### Bandwidth efficiency

One strategy for using limited bandwidth more efficiently is to use more than two signaling levels.

 By using four voltages, for instance, we can send 2 bits at once as a single **symbol**.

 the rate at which the signal changes the **symbol rate** aka **baud rate**

###### Clock Recovery

the receiver must know when one symbol ends 

and the next symbol begins to correctly decode the bits

Accurate clocks are needed.

Manchester coding 在一次时钟内信号发生跳变，其数据传输速率是码元传输速率(Baud)的一半

How to solve a long runs of 1/0 ? 

use a scheme of 4B/5B by adding 25% overhead to limit more than three sequence of 0s

###### 码元 脉冲

一个**固定时长**的**信号波形** 这个码元宽度内的信号为M进制码元

一个码元可以携带多个bit的信息量 码元本身是信号状态，用于表示数据 

##### Balanced Signals

Signals that have as much positive voltage as negative voltage even over short periods of time

###### A straightforward way to construct a balanced code

use two voltage levels to represent a logical 1, (say +1 V or −1 V)

 with 0 V representing a logical zero.

###### other solution

8B/10B

##### Passband Transmission

1. Amplitude modulation Shift keying 调幅

2. Frequency modulation

3. Phase modulation

   different phase不同的相位影响

We can combine these schemes and use more levels to transmit more bits per symbol.

 Only one of frequency and phase can be modulated at a time because they are related, 

with frequency being the rate of change of phase over time.

Usually, amplitude and phase are modulated in combination

###### Quadrature Amplitude Modulation

结合调频调制 和 正交调制

modem constellation diagram

模拟信道上进行调制与解调

#### Multiplexing

Channels are often shared by multiple signals.

 It is much more convenient to use a single wire to carry several signals

##### Frequency division multiplexing

频分复用

带宽拆分 each user possess unique band of width

Different frequencies are allocated to different logical channels

==Notice that even though there are gaps between the channels thanks to the guard bands==

==there is some overlap between adjacent channels.==

​	使用场景: 广播调频

###### further idea

**OFDM** (**Orthogonal Frequency Division Multiplexing**)

the frequency response of each subcarrier is designed 

so that it is zero at the center of the adjacent subcarriers

The subcarrierscan therefore be sampled at their center frequencies 

without interference from their neighbors

需要维护一个guard time to repeat a portion of the symbol signals in time

##### Time Division Multiplexing

时分复用 对于数字信号

each one periodically getting the entire bandwidth for a little burst of time

即在固定的时间戳内不同信号占据的时间间隔被确定，发送方和接收方进行同步沟通

. Small intervals of **guard time** are added to accommodate small timing variations

##### Code Division Multiplexing

利用多路信号波形的正交性

the key to CDMA is to be able to extract the desired signal 

while rejecting everything else as random noise.

一个bit划分为不同chips 每个站点保存独特的chip sequence

故而带宽的变化:  the bandwidth needed for CDMA is greater by a factor of *m*

 than the bandwidth needed for a station not using CDMA

但这并不代表其效率的降低. 相较于FDM,线路整体的带宽被多个站点公用且分隔

而CMDA可以独占整个带宽，用原来空出的效率用于chip的扩展位

==接收方提前预知所有站点的chip sequence==

不同站点的信号可以进行直接的元素叠加

根据S*C的点积值，判断C是否发送数据以及发送数据的种类

#### Public Switched Telephone Network

##### Local Loop

存在于终端设备与End Office之间 常被成为Last Mile

> 指代从通信服务提供商的机房交换机到用户电脑等终端设备之间的连接。

以模拟信号形式存在

old local loops: 

relatively narrow bandwidth, 

attenuation and distortion of signals,

 and susceptibility to electrical noise such as crosstalk串线

###### Modems

###### Digital Subscriber Lines

对应声音带宽在4000Hz以下

数字用户线路

offer new digital services over the local loop.

ADSL 非对称 下载速率远大于上传速率

非对称用户数据线

###### Trunks and Multiplexing

 how voice signals are digitized?

The analog signals are digitized in the end office by a device called a **codec**

##### Switching

Inside plant

###### Circuit switching 

自动电话交换设备

###### packet switching

 store-and-forward