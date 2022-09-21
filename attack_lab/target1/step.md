
## level 1

关于如何计算callq后的二进制码（虽然此处没用到）：https://stackoverflow.com/questions/26672064/editing-elf-binary-call-instruction

```shell
b *0x4017b4
run -q < raw.txt

cat exploit.txt | ./hex2raw | ./ctarget -q
./hex2raw < exploit.txt > raw.txt
```


## level2

1. 溢出的地方是填地址，之前一直想的是这个地址从何而来，因为你要在这个地址处执行自己的代码
2. 碰到打印“Valid solution”后还是提示错误，这个[链接](https://stackoverflow.com/questions/53255874/buffer-overflow-attack-the-attack-lab-phase-2)有提示，照着改可以pass了。
3. 自己容易犯错的地方，为了凑一个整的8B，用0来填充，其实指令间是可以连续放置，汇编害死有点不熟。

```shell
./hex2raw < exploit2.txt > raw2.txt
b *0x4017b4
run -q < raw2.txt

cat exploit2.txt | ./hex2raw | ./ctarget -q

```

## level3

