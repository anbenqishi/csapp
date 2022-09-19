## 第一个炸弹

直接打印地址所对应的字符串即可；

## 第二个炸弹

我把汇编写成类似C的形式比较好看一点

```c
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

 这题貌似有多个答案，很快做出来了，但是寄存器rcx,rdx那边理解有点偏差，卡了一下
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

## 第五个炸弹

1. sub比较的是内存里村的数据吗，还是两个寄存器值？

2. 查看 0x4024b0 附近的数据？ maduiersnfotvbyl

3. f l   y e r s
   9 15 14 5 6 7
   f: 102  0x66  -> 0x69  i
   l: 108  0x6c  -> 0x6f  o
   y: 121  0x79  -> 0x7e  ~  0x6e n   [验证结果都可以其实]
   e: 101  0x65  -> 0x65  e
   r: 114  0x72  -> 0x76  v
   s: 115  0x73  -> 0x77  w
   
   ```c
    save rbx;
    rsp -= 32; // 4 * 8
    rbx = rdi; // 1st
    rax = %fs:40;
    (rsp + 24) = rax; // ""
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
            esi = 0x40245e;  // "flyers"
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
   ```

## 第六个炸弹

1. 还是6个数字；
2. 

<pre>
-------
           <--- old rsp
-------
      72
-------
      64
-------
      56
-------
      48
-------
      40
-------
      32
-------
      24
-------
[6] [5]
-------
[4] [3]
-------
[2] [1]   <---  phase_6 rsp [r13, rsi init]
-------
</pre>

* [12345] <= 6,

* 各不相同

* d0 -> e0 : 14c -> 0a8
  e0 -> f0 : 0a8 -> 39c
  f0 ->3300: 39c -> 2b3
  3300 ->3310: 2b3 -> 1dd
  3310 ->3320: 1dd -> 1bb

* 0a8 < 14c < 1bb < 1dd < 2b3 < 39c
  32e0 -> 32d0 -> 3320 -> 3310 -> 3300 -> 32f0
   2       1       6       5       4       3
  7-x
  x  5       6       1       2       3       4
  so, non-increasing:
  4 3 2 1 6 5

```shell
(gdb) x/24w 0x6032d0
0x6032d0 <node1>:    0x0000014c    0x00000001    0x006032e0    0x00000000
0x6032e0 <node2>:    0x000000a8    0x00000002    0x006032f0    0x00000000
0x6032f0 <node3>:    0x0000039c    0x00000003    0x00603300    0x00000000
0x603300 <node4>:    0x000002b3    0x00000004    0x00603310    0x00000000
0x603310 <node5>:    0x000001dd    0x00000005    0x00603320    0x00000000
0x603320 <node6>:    0x000001bb    0x00000006    0x00000000    0x00000000
(gdb)
```

```c
    save r14, r13, r12, rbp, rbx;
    rsp -= 8 * 10;
    r13  = rsp;
    rsi  = rsp;
    read_six_numbers(rdi, rsi);
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

    r14 = rsp;
    r12d = 0;
D:
    rbp = r13;   // [1][2]...[6]
    eax = (r13); // [1]...[6]
    eax -= 1;
    if (eax <= 5) {  // [1] <= 6  all numbers <= 6
        r12d += 1;
        if (r12d == 6) {
            rsi = rsp + 24; // end position
            rax = r14;      // [1]
            ecx = 7;
A:
            edx = ecx;     // 7
            edx -= (rax);  // 7 - [1]
            (rax) = edx;   // (rax) = 7 - [1] turn original numbers to 7-x
            rax += 4;      // [2]
            if (rax != rsi) { // iterate
                goto A;
            }
            esi = 0;
G:
            ecx = (rsi + rsp);   // from top
            if (ecx <= 1) {
                edx = 0x6032d0;
F:
                (rsi*2+rsp + 32) = rdx;  // +32 ~ +72 (six numbers)
                rsi += 4;
                if (rsi == 24) {     // 6次
                    rbx = (rsp + 32);  // stack top num
                    rax = rsp + 40;    // next
                    rsi = rsp + 80;    // end
                    rcx = rbx;         // stack top
H:
                    rdx = (rax);      // next num
                    (rcx+8) = rdx;
                    rax += 8;
                    if (rax == rsi) {  // end position
                        (rdx+8) = 0;
                        ebp = 5;
B:
                        rax = (rbx+8); // next num
                        eax = (rax);
                        if ((rbx) < eax) {
                            explode;
                            return;
                        } // asure (rbx) >= eax, 这意味着数字是按非递增排列的
                        rbx = (rbx + 8);
                        ebp -= 1;
                        if (ebp != 0) {  // sub后的jne
                            goto B;
                        }
                        rsp += 8 * 10;
                        pop rbx, rbp, r12, r13, r14;
                        return;
                    } else {
                        rcx = rdx;  // next num
                        goto H;
                    }
                } else {
                    goto G;
                }
            } else {
                eax = 1;
                edx = 0x6032d0;
E:
                rdx = (rdx + 8);
                eax += 1;
                if (eax != ecx) { // iterate based on num on stack
                    goto E;
                } else {
                    goto F;
                }
            }
        } else {
            ebx = r12d;
C:
            rax = ebx; //movslq
            eax = (rax*4+rsp);
            if ((rbp) != eax) { // all numbers are different
                ebx +=1;
                if (ebx <= 5) {
                    goto C;
                } else {
                    r13 += 4;
                    goto D;
                }
            } else { explode; }
        }
    } else { explode; }
```

## 听说有彩蛋

```c
phase_defused() {
    rsp -= 0x78;
    (rsp+0x68) = rax;
    eax ^= eax;
    if ((rip+0x202181) != 6) {
        // check fail;
        return;
    } else {
        r8 = rsp + 16;
        rcx = rsp + 0xc;
        rdx = rsp + 8;
        esi = 0x402619;
        edi = 0x603870;
        sscanf(edi, esi, rdx, rcx , r8);
        if (eax != 3) {
A:
            puts(& 0x402558);
            rax = rsp + 0x68;
            // check fail;
            return;
        } else {
            esi = 0x402622;
            rdi = rsp + 16;
            strings_not_equal(rdi, esi);
            if (eax & eax != 0) {
                goto A;
            } else {
                edi = 0x4024f8;
                puts(edi);
                edi = 0x402520;
                puts(edi);
                eax = 0;
                secret_phase();
                goto A;
            }
        }
    }
}


secret_phase:
    save rbx;
    read_line();
    edx = 0xa;
    esi = 0;
    rdi = rax;
    strtol(rdi, NULL, 10);
    rbx = rax;
    eax = rax-1;
    if (eax <= 0x3e8) {
        esi = ebx;
        edi = 0x6030f0;
        fun7(edi, esi, ...);
        if (eax = 2) {
            edi = 0x402438;
            puts(edi);
            phase_defused();
            pop rbx;
            return;
        } else { explode; }
    } else {
        explode;
    }

fun7() {
    rsp -= 8;
    if (rdi & rdi == 0) {
        eax = 0xffffffff;
        rsp += 8;
        return;
    }
    edx = (rdi);
    if (edx <= esi) {
        eax = 0;
        if (edx == esi) {
            rsp += 8;
            return;
        } else {
            rdi = rdi + 16;
            fun7();
            eax = rax + rax + 1;
            rsp += 8;
            return;
        }
    } else {
        rdi = rdi + 8;
        fun7();
        eax += eax;
        rsp += 8;
        return;
    }
}
```