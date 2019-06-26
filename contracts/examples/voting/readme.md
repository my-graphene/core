# voting

投票合约，记录查看删除候选人的id，姓名，票数等。

## 编译合约

```bash
mycc -o voting.wast voting.cpp
mycc -g voting.abi voting.cpp
```

## 部署合约

部署合约要求账户私钥已经导入钱包，并且是解锁状态

```bash
unlocked >>> deploy_contract voting nathan 0 0 ./voting <TOKEN> true
```

* voting指定将要创建的合约名
* nathan为部署合约的帐户
* 0 0 分别指定了vm类型和版本号
* ./voting指定合约文件的路径
* <TOKEN>表示使用<TOKEN>支付手续费
* true表示执行，发起广播

## 调用合约

### 投票

```bash
call_contract nathan voting null vote "{\"id\":1, \"name\":\"user1\"}" <TOKEN> true
call_contract nathan voting null vote "{\"id\":1, \"name\":\"user1\"}" <TOKEN> true

call_contract nathan voting null vote "{\"id\":2, \"name\":\"user2\"}" <TOKEN> true
call_contract nathan voting null vote "{\"id\":3, \"name\":\"user3\"}" <TOKEN> true
```

### 查看票数

```
call_contract nathan voting null count "{\"id\":1}" <TOKEN> true
```

此时在witness_node运行日志看到如下内容.

```text
[(22,count)->22] CONSOLE OUTPUT BEGIN =====================
id=1, name=user1, count=2
[(22,count)->22] CONSOLE OUTPUT END =====================
```

### 查看投票列表

```bash
call_contract nathan voting null list "{}" <TOKEN> true
```

此时在witness_node运行日志看到如下内容.

```text
[(22,count)->22] CONSOLE OUTPUT BEGIN =====================
id=1, name=user1, count=2
id=2, name=user2, count=1
id=3, name=user3, count=1
[(22,count)->22] CONSOLE OUTPUT END =====================
```

### 删除候选人

```
call_contract nathan voting null remove "{\"id\":1}" <TOKEN> true
```

此时在witness_node运行日志看到如下内容.

```bash
[(22,count)->22] CONSOLE OUTPUT BEGIN =====================
remove name==user1
[(22,count)->22] CONSOLE OUTPUT END =====================
```
