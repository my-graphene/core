# store

```bash
mycc -o store.wast store.cpp
mycc -g store.abi store.cpp
```

```bash
deploy_contract store nathan 0 0 /root/core/contracts/examples/store RUI true
call_contract nathan store null set "{}" RUI true
call_contract nathan store null show "{}" RUI true
```