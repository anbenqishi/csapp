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
    eax = 2*[(rbx - 4)];
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

```c
    rsp -= 24    // 3格
    rcx = rsp + 12
    rdx = rsp + 8
    esi = 0x4025cf   "%d %d"
    eax = 0
    sscanf(rdi, "%d %d", rdx, rcx);
    if (eax > 1) {
        if ((rsp + 8) > 7) {
            explode
        } else {
            eax = (rsp + 8)
            goto *(rax * 8 + 0x402470) [0x400f7c]
            eax = 0xcf
            if (eax == (rsp + 12)) {
                rsp += 18   // exit
            } else {
                explode
            }
        }
    } else {
        explode
    }
```

===> 这题貌似有多个答案，很快做出来了，但是寄存器rcx,rdx那边理解有点偏差，卡了一下
0 207
2 0x2c3
3 0x100
4 0x185
5 0xce
6 0x2aa
7 0x147

## 第四个炸弹

```c

rsp -= 24;
rcx = rsp + 12; // 2nd
rdx = rsp + 8;  // 1st
[esi] = "%d %d"
eax = 0;
sscanf(rdi, "%d %d", rdx, rcx);
if (eax != 2) {
    explode;
    return;
}
if (1st <= 14) {              // !!!!!!!
    edx = 14;
    esi = 0;
    edi = 1st;
    func4(1st, 0, 14);
    if (eax & eax != 0) {
        explode; return;
    } else {                 // !!!!!!!
        if (2nd == 0) {
            rsp += 24;
            return;
        } else {explode;}
    }
} else {
    explode;
    return;
}


func4(edi=1st, esi=0, edx=14) {
    rsp -= 8;
    eax = edx;  //14
    eax -= esi; //14
    ecx = eax;  //14
    ecx >>= 31; //0
    eax += ecx; //14
    eax >>= 1;  //7
    ecx = rsi + rax; //7
    if (ecx <= edi) {
        eax =  0;
        if (ecx >= edi) {
            rsp += 8;
            return;
        } else {
            esi = rcx + 1;
            func4();
            eax = rax + rax + 1;
            rsp += 8;
            return;
        }
    } else {
        edx = rcx - 1;
        func4();
        eax += eax;
        rsp += 8;
        return;
    }
}
```

## 第5个炸弹

1. sub比较的是内存里村的数据吗，还是两个寄存器值？

```
    save rbx;
    rsp -= 32; // 4 * 8
    rbx = rdi; // 1st
    rax = %fs:40;
    (rsp + 24) = rax;
    eax = eax ^ eax; // 清0
    string_length(rdi); // 6个字符
    if (eax == 6) {
        eax = 0;
A:
        ecx = (rax + rbx); //movzbl
        (rsp)  = cl; // 1B = char
        rdx = (rsp);
        edx = edx & 0xf;
        edx = (rdx + 0x4024b0); // movzbl
        (rax + rsp + 16) = dl;
        rax = rax + 1;
        if (rax != 6) {
            goto A;
        } else {
            (rsp + 22)  = 0; // byte
            esi = 0x40245e;
            rdi = rsp + 16;
            strings_not_equal(rdi, rsi);
            if (eax & eax == 0) {
                rax = (rsp + 24);
                rax ^= %fs:0x28;
                je;
                rsp += 32;
                pop rbx;
                return;
            } else { explode; }
        }
    } else { explode; }