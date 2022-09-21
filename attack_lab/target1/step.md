
## level 1

关于如何计算callq后的二进制码（虽然此处没用到）：https://stackoverflow.com/questions/26672064/editing-elf-binary-call-instruction

```shell
b *0x4017b4
run -q < raw.txt

cat exploit.txt | ./hex2raw | ./ctarget -q
./hex2raw < exploit.txt > raw.txt
```


## level2

