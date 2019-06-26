# linear_vesting_asset

线性解冻资产合约，可以通过vestingcreate方法向某一帐户(A)转帐，同时设置冻结时间(lock_duration)和释放时间(release_duration)，即经过lock_duration 秒后，资产开始解冻，经过release_duration秒后，A帐户可以调用vestingclaim方法，将资产全部取出。

## 编译合约

* 生成wast:

  ```bash
  mycc -o contracts/examples/linear_vesting_asset/linear_vesting_asset.wast contracts/examples/linear_vesting_asset/linear_vesting_asset.cpp
  ```

* 生成abi

  ```bash
  mycc -g contracts/examples/linear_vesting_asset/linear_vesting_asset.abi contracts/examples/linear_vesting_asset/linear_vesting_asset.cpp
  ```

## 部署合约

  ```bash
  deploy_contract ch3 nathan 0 0 ./contracts/examples/linear_vesting_asset/ <TOKEN> true
  ```

## 调用合约

* 从beita账号转账给nathan，100<TOKEN>(1.3.0)，锁定30秒后开始根据时间线性释放，120秒全部释放完毕

  ```bash
  call_contract beita t81611 {"amount":10000000,"asset_id":1.3.0} vestingcreate "{\"to\":\"nathan\",\"lock_duration\":30,\"release_duration\":120}" <TOKEN> true
  ```

* 查询合约ch3有哪些表

  ```bash
  unlocked >>> get_contract_tables ch3
  [
    "vestingrule"
  ]
  ```

* 查询合约ch3 vestingrule，最多查询10ms就立即返回结果

  ```bash
  unlocked >>> get_table_objects ch3 vestingrule
  [{
      "account_id": 17,
      "asset_id": 0,
      "vesting_amount": 10000000,
      "vested_amount": 0,
      "lock_time_point": 1534422875,
      "lock_duration": 30,
      "release_time_point": 1534422905,
      "release_duration": 120
    }
  ]
  ```

* 查询合约下有多少资产

  ```bash
  unlocked >>> list_account_balances ch3
  100 <TOKEN>
  ```

* 尝试释放ch3中nathan的<TOKEN>(1.3.0)资产，根据当前时间和vestingrule来释放

  ```bash
  call_contract beita t81611 null vestingclaim "{\"who\":\"nathan\"}" <TOKEN> true
  ```
