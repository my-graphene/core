rxx -o store.wast store.cpp
rxx -g store.abi store.cpp
deploy_contract store nathan 0 0 /root/dbxchain/contracts/examples/store RUI true
call_contract nathan store null set "{}" RUI true
call_contract nathan store null show "{}" RUI true
