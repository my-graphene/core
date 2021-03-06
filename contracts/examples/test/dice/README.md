
# dice

## 编译合约

### 生成wast和wasm文件

```bash
mycc -o dice/dice.wast dice/dice.cpp
```

### 生成abi

```bash
mycc -g dice/dice.abi dice/dice.cpp
```

## 部署合约

    unlocked >>> deploy_contract dice nathan 0 0 ./dice RUI true

* dice指定将要创建的合约名
* nathan为部署合约的帐户
* 0 0 分别指定了vm类型和版本号
* ./dice指定合约文件的路径
* RUI表示使用RUI支付手续费
* true表示执行，发起广播

## 调用合约

### 调用dice合约的deposit方法,beita/nathan向合约存入100个RUI用于dice游戏

```bash
call_contract beita dice {"amount":10000000,"asset_id":1.3.0} deposit "{}" RUI true
call_contract nathan dice {"amount":10000000,"asset_id":1.3.0} deposit "{}" RUI true
```

* beita/nathan指定调用合约的帐户
* dice指定要调用的合约帐户名
* {"amount":10000000,"asset_id":1.3.0} 表示不向合约发送资产100RUI
* deposit 表示要调用的合约方法
* "{}" 表示合约deposit的参数，参数以json格式传入
* RUI表示使用RUI支付手续费
* true表示执行，发起广播

### 调用dice合约的offerbet方法,beita/nathan分别押注10RUI并指定自己的commitment，commitment的生成方式详见后面：

    call_contract beita d11421 null offerbet "{\"bet\":{\"amount\":1000000,\"asset_id\":0},\"commitment\":\"492b184fdcb41f442d539e792600a8db67c47eb16c0265e5d1e553473f462486\"}" RUI true

    call_contract nathan d11421 null offerbet "{\"bet\":{\"amount\":1000000,\"asset_id\":0},\"commitment\":\"c807cc6c0b9121f6b151f39dcf5fd819e3cb9a6d18f46c7a635f1015148bcc76\"}" RUI true

### 调用dice合约的reveal方法,beita/nathan分别亮牌：

    call_contract beita d11421 null reveal "{\"commitment\":\"492b184fdcb41f442d539e792600a8db67c47eb16c0265e5d1e553473f462486\",\"source\":\"a80b8a6d1bf2cf798b045366d920531b2ce5f13082c4b2b08d53cfeab5d24b7a\"}" RUI true
    call_contract nathan d11421 null reveal "{\"commitment\":\"c807cc6c0b9121f6b151f39dcf5fd819e3cb9a6d18f46c7a635f1015148bcc76\",\"source\":\"5387ec637ac4bdbcf9577451cdc61f4d11ba600ba5540a27065a15aa3f8d45d1\"}" RUI true

### commitment及相应的resource生成方式如下(mac下)

* 生成resource：

```text
openssl rand 32 -hex
7d65a071c3f8b38f94e11be1fda97109ea41dfd305e06e677a55edd957327fab
```

* 根据resource生成commitment：

```text
echo -n '7d65a071c3f8b38f94e11be1fda97109ea41dfd305e06e677a55edd957327fab' | xxd -r -p | shasum -a 256 -b
24948ec739cd9963bae8805ae18a4a2f4d58689b8d48dc20f289c3ded47ef600 *-
```

### 亮牌后系统根据2位玩家的commitment和resource计算1个hash，比较hash值的第一个和第二个字节的大小来决定胜负，并完成account表的更新操作，查看account表

    get_table_objects d11421 account

    unlocked >>> get_table_objects dice account
    [{
        "owner": 17,
        "balance": {
          "amount": 11000000,
          "asset_id": 0
        },
        "open_offers": 0,
        "open_games": 0
      },{
        "owner": 18,
        "balance": {
          "amount": 9000000,
          "asset_id": 0
        },
        "open_offers": 0,
        "open_games": 0
      }
    ]