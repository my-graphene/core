# bank

bank 合约提供了充值(deposit)和提现(withdraw)方法，可以向合约充值、从合约中提取资产。

## 合约编译

### 1. 生成wast:

```bash
mycc -o contracts/examples/bank/bank.wast contracts/examples/bank/bank.cpp 
```

### 2. 生成abi:

```bash
mycc -g contracts/examples/bank/bank.abi contracts/examples/bank/bank.cpp 
```

## 合约部署和调用

### 启动cli_wallet

```bash
./programs/cli_wallet/cli_wallet -sws:///127.0.0.1:28099 --chain-id xxxx
```

### 部署合约

```bash
// 这里使用nathan帐户部署合约，部署的合约名为bank
unlocked >>> deploy_contract bank nathan 0 0 ./contracts/examples/bank <TOKEN> true
```

### 调用合约

* 调用合约的deposit方法

  ```bash
  // 使用nathan帐户，调用bank合约，方法名为deposit,  发送资产总量为100 <TOKEN>(链上为大数，需要乘以10万)
  unlocked >>> call_contract nathan bank {"amount":10000000,"asset_id":1.3.1} deposit "{}" <TOKEN> true
  ```

* 查询bank合约的帐户余额

  ```bash
  unlocked >>> list_account_balances bank
  100 <TOKEN>
  ```

* 列出合约所有的存储表

  ```bash
  unlocked >>> get_contract_tables bank
  [
    "account"
  ]
  ```

  该bank合约只有一个account表

* 查询合约的account表，该表记录了帐户在合约中的余额

```bash
  unlocked >>> get_table_objects bank account
  [{
      "owner": 17,
      "balances": [{
          "amount": 10000000,
          "asset_id": 1
        }
      ]
    }
  ]
  ```

* 调用合约的withdraw方法提现

  ```bash
  // 提现到nathan帐户
  unlocked >>> call_contract nathan bank null withdraw "{\"to_account\":\"nathan\", \"amount\":{\"asset_id\": 1, \"amount\":100000}}" <TOKEN> true

  // 提现到init0帐户
  unlocked >>> call_contract nathan bank null withdraw "{\"to_account\":\"init0\", \"amount\":{\"asset_id\": 1, \"amount\":100000}}" <TOKEN> true
  ```
