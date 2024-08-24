导引：能够上QQ,但不能上网?

可能原因：DNS服务器故障

Domain Name System 

>  what is hostname? Because of domain name only exists in the public network
>
> one IP address may corresponds to differnet domain names
>
> In LAN,one machine has its hostname **/etc/hosts** 
>
> the format ==*127.0.0.1 localhost.localdomain localhost*==
>
> IP address + hostname.domainname + alias of hostname
>
> In LAN,the hostname could be mapped to the IP addresss,but in MAN or WAN,can’t be done

局域网中机器可以通过配置局域网中所有主机的hosts文件实现通过主机名互访

the other method is **LAN DNS server**  

主机名 = 计算机名 + 域名 (域名的范围大于主机名)

DNS通常为其他应用层协议所使用 也可以运行在UDP和TCP上

**它是一个使得主机能够查询分布式数据库的应用层协议**



模型机 微程序控制 CPU四大功能 D触发器六大功能



读入“ IP地址 – 域名”对照表

1. ip地址 0.0.0.0 不良网站拦截
2. 普通ip地址  服务器功能
3. 中继功能

通过hosts.txt访问 –> gethostbyname()

层次化namespace 是分布式数据库 Naming是组织边界organizational boundaries,而不是物理边界

Hierarchical Namespace 

命名最大深度为128 

Naming policy by the path upward from leaf to root

different zone进行管理 Resource Records

资源类型Type:specify the type of the resource in this RR

TTL: Time to Live of the **cached RRs** 

DNS Client-Server

客户端有resolver解析器,access at least one name server(IP地址)

DNS server也是层次化的

Every server knows the root, root server knows all top-level domains (递归or迭代) 实际用迭代 – 避免中间服务器一直缓存

先send request first to local name server — port 53

DNS Caching

主机可以有cache, Server有cache,继续查找

DNS报文构成 Header + Question + Answer + Authority + Additional

ID 由客户程序设置并由服务器返回结果

QR 0表示查询报 AA 权威答案

最初,进行wireshark抓包

Email System 文本协议 通过Sender User Agent代理,消息传输代理和接收方用户代理多方协作

MIME: multipurose Internet Mail Extension用于处理原邮件容量小的问题

SMTP 使用TCP连接  POP接收方 Mail-server to UA

发展到IMAP

HTTP 文本协议



关于代码简洁性方面,由于c语言中没有RAII的思想,不能将socket直接封装,但可以包装函数

Compression Labels

是一种用于减少 DNS 报文大小的机制，通过指针压缩重复的域名部分。这种机制可以显著减少报文中的重复数据，从而提高传输效率。

### 压缩标签的基本原理

在 DNS 报文中，域名部分通常由多个标签（labels）组成，每个标签以长度字节开头，后跟该标签的实际内容。

偏移量（offset）指的是相对于 DNS 报文起始位置的偏移量

DNS查询 DNS响应和 DNS转发

考虑后续将输出时间的类型缩短

哈希表的删除(存储方式避免使用线性探索)

### 文本搜索查询

最大限度地减少无谓的字符串比较, 查询效率比Hash Table高

对**输入的字符串的总长度**有限制

- 单个字符串由各国文字的特定字符集、字母、数字、连字符（-）组成，字母不区分大小写，连字符（-）不得出现在字符串的头部或者尾部。

期末考试 4类题型

配置文件可设置 — 是否debug 是否记录成日志  设置远程DNS服务器

设置静态二级缓存地址   是否输出提示信息(直接返回0)

程序初始化时，对于本地主机需要初始化唯一的ID映射表 对应的缓存 对应的二级缓存 对应的socket 对于每个客户端开启对应的线程 

注意double free的问题

IP对应不上 cache中的问题

去除队列任务开始执行

Something about dereferencing ‘void *’ pointer

过程中遇到了只返回IPv4的情况

nslookup的工作原理是什么呢?

注意NAME这个字段可能为奇数字节，不需要进行边界填充对齐。

C语言不支持Lambda与RAII机制

### 查询机制

递归查询 (线性) && 迭代查询 本人

### HTTP

使用TCP作为传输层协议

#### 1.0

采用非持续连接

**每次请求一个文件，建立TCP连接，收到响应之后立即关闭连接**

浏览器会建立多个并行的TCP连接同时请求多个对象

#### 1.1

采用持续连接 使得对象服务器和客户浏览器之间的连接上持续传送文档数据  —- 流水线工作方式

##### 报文格式

* 起始行
* 请求头部
* —- 分割空行 —
* 实体

Header 起始行和头部字段 + body 消息正文 实体

##### What differences between special newline characters or EOL characters?

Different line break types problem was confronted when cross-platform compatibility.

CR : Carriage Return LF: Line Feed to modify both the x-axis and y-axis of the cursor.

##### HTTP Request and Response

<img src="C:\Users\WESLEY\AppData\Roaming\Typora\typora-user-images\image-20240814172653345.png" alt="image-20240814172653345" style="zoom:50%;" />

**Some important segment:**

Accept: 可接受的文本类型

Connection: keep-alive | closed 连接模式

Host: 访问的主机名

User-Agent: 客户用户代理信息

4xx 客户差错 5xx 服务器差错(如服务器失效)

Content-length: 343 用于区分粘包问题，表示正文数据包长度

##### HTTP协议

1. 支持C-S模式
2. 简单快速
3. 灵活
4. 无连接：每次连接只处理一个请求
5. 无状态：协议对于事务处理没有记忆能力

### Cookie and session

为了解决HTTP的无状态特性 **不同的用户数据如何进行区分**

HTTP协议中的cookie包含 Web Cookie 和 浏览器 Cookie

服务器发送给浏览器的Cookie，浏览器会进行存储，并与下一个请求一起发送给服务器

**用于判断两个请求是否来自于同一个浏览器** 

session: 

1. 服务器提供仓库，专门保存每一个客户链接所需要的状态
2. 时效性信息 放置在**内存数据库**中 redis

需要 服务器将仓库的唯一状态值 通过cookie技术，给到浏览器 session-id **sid** 

cookie中包含 session id

代理服务器的存在 位于中间系统上的Web缓存

### World Wide Web

万维网是运行在因特网上的分布式应用

<协议>://<主机>:<端口>/<路径>

web协议:

​	传输协议 HTTP

​	数据解析协议 HTML CSS JavaScript — pdf rstp

### Overall Architecture

面向不同业务的产生和使用数据的逻辑层

⼀般常⻅的 Web 服务器主要有Apache、IIS、Jboss、Tomcat、WebSphere、WebLogic 等

C-S架构 — 需要Data Center

P2P方式 — **没有固定的服务请求者和服务提供者** （分布式存储）

**扩展性强** 不需要庞大的服务器设置和服务器带宽



