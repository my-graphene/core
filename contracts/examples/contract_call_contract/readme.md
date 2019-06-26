deploy_contract ccca nathan 0 0 examples/contract_call_contract/contracta <TOKEN> true

deploy_contract cccb nathan 0 0 examples/contract_call_contract/contractb <TOKEN> true

call_contract beita ccca null hicontract "{\"act_id\":77}" <TOKEN> true
