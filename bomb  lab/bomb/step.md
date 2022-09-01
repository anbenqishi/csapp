## 第一个炸弹
直接打印地址所对应的字符串即可；

## 第二个炸弹
我把汇编写成类似C的形式比较好看一点
```
rsp -= 40;
rsi = rsp;
read_six_numbers:
    进入时：rsp -= 24;
    rdx = rsi; // parameter 3
    rcx = rsi + 4; // parameter 4
    rax = rsi + 20;
    (rsp + 8) = rax = rsi + 20;
    (rsp) = rsi + 16;
    r9 = rsi + 12; // parameter 6
    r8 = rsi + 8;  // parameter 5
    esi = 0x4025c3; // parameter 2   "%d %d %d %d %d %d"
    eax = 0;
    sscanf(rdi, "%d %d %d %d %d %d", rdx, rcx, rsi+8, rsi+12, num1?, num2?);
    if (eax > 5)
        恢复：rsp += 24;
if ((rsp) == 1) {
    rbx = rsp + 4;
    rbp = rsp + 24;
    goto A;
} else {
    explode_bomb
}
A:
    eax = 2*(rbx - 4);
    if ((rbx) == eax) {
        rbx += 4;
        if (rbx != rbp) {
            goto A;
        }
        exit;
    } else {
        explode_bomb
    }
```

==> 第一次搞错的一点是对下面这条指令的理解，再看了下书才恍然大悟
          mov    -0x4(%rbx),%eax
    我理解成直接拿（%rbx）的值去减 4，实际是取（%rbx-4）
    这其实感觉也是写成类C伪码时，写的不准确造成的。

## 第三个炸弹

