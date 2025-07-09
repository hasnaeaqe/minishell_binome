to handle dyal 3bd l7a9


AddressSanitizer:DEADLYSIGNAL
=================================================================
==43341==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x00010df38ce0 bp 0x7ffee1ccc1f0 sp 0x7ffee1ccc150 T0)
==43341==The signal is caused by a READ memory access.
==43341==Hint: address points to the zero page.
    #0 0x10df38ce0 in ft_strcmp+0x80 (minishell:x86_64+0x100005ce0)
    #1 0x10df3e9c3 in check_double_point+0x23 (minishell:x86_64+0x10000b9c3)
    #2 0x10df3eb4b in ft_cd+0xeb (minishell:x86_64+0x10000bb4b)
    #3 0x10df446a5 in check_builts+0x205 (minishell:x86_64+0x1000116a5)
    #4 0x10df3b5e8 in execute_cmd+0x2b8 (minishell:x86_64+0x1000085e8)
    #5 0x10df3c403 in exec_tree+0x93 (minishell:x86_64+0x100009403)
    #6 0x10df43f0e in main+0x3ae (minishell:x86_64+0x100010f0e)
    #7 0x7fff6d58ccc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

==43341==Register values:
rax = 0x0000000000000000  rbx = 0x00007ffee1ccc3a0  rcx = 0x0000100000000000  rdx = 0x0000100000000000  
rdi = 0x0000000000000000  rsi = 0x000000010df46600  rbp = 0x00007ffee1ccc1f0  rsp = 0x00007ffee1ccc150  
 r8 = 0x0000000000000005   r9 = 0x0000000000000000  r10 = 0x0000000000000000  r11 = 0x0000000000000203  
r12 = 0x0000000000000000  r13 = 0x0000000000000000  r14 = 0x0000000000000000  r15 = 0x0000000000000000  
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (minishell:x86_64+0x100005ce0) in ft_strcmp+0x80
==43341==ABORTING
[1]    43341 abort      ./minishell

THIS IN BASH

bash-3.2$ cd ././
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
bash-3.2$ pwd
/mnt/homes/haqajjef/Desktop/minishell/minishell/1/2/3/../././

./minishell | ./minishell 

parsing  -------
minishell$ unset PWD OLDPWD
minishell$ cd $PWD
minishell: cd: : No such file or directory

minishell$ export a="ls -la"
minishell$ $a
minishell: ls -la: command not found


minishell$ export $NOTHER $HOME
export: not an identifier: 
minishell$ export $NOTHER 
export: not an identifier: 


minishell$ unset PATH
main
minishell$ pwd
/mnt/homes/haqajjef/Desktop/minishell/minishell
minishell$ export | grep PATH
minishell: grep: command not found
minishell$ ls
minishell: ls: command not found
minishell$ ls
minishell: ls: command not found
minishell$ $?
minishell: 0: command not found
minishell$ /./
minishell$ builtins

////
➜  minishell git:(master) ✗ env -i ./minishell 
minishell$ env
PATH=/mnt/homes/haqajjef/.docker/bin:/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.
SHLVL=1
_=/usr/bin/env
minishell$ export
declare -x /mnt/homes/haqajjef/Desktop/minishell/minishell
declare -x PATH="/mnt/homes/haqajjef/.docker/bin:/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."
declare -x SHLVL="1"
declare -x _="/usr/bin/env"


minishell$ ls > /dev/stdout | ls
output redirection: Permission denied
-qwerty         builtins        minishell       minishell.h     parsing
Makefile        execusion       minishell.c     minishell.o


dup dup2 waitpid fork execve stat access 




/////////////////////////////


minishell$ ksadfgdfg
(null)
minishell: ksadfgdfg: No such file or directory
minishell$ 


////////////////////////////


minishell$ unset PATH
ana hona 

minishell$ ls
ana hona 

minishell: ls: No such file or directory
minishell$ 


minishell$ cd 1/2/3
minishell$ pwd
/mnt/homes/haqajjef/Desktop/minishell/minishell1/1/2/3
minishell$ unset $PWD $OLDPWD
$
$
minishell: unset: /mnt/homes/haqajjef/Desktop/minishell/minishell1/1/2/3 : not a valid identifier
minishell: unset: /mnt/homes/haqajjef/Desktop/minishell/minishell1 : not a valid identifier
minishell$ unset PWD OLDPWD
minishell$ /mnt/homes/haqajjef/Desktop/minishell/minishell1/1
minishell: /mnt/homes/haqajjef/Desktop/minishell/minishell1/1: is a directory
minishell$ rm -rf /mnt/homes/haqajjef/Desktop/minishell/minishell1/1
minishell$ cd .
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
minishell$ pwd
minishell$ cd ..
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
minishell$ pwd

➜  minishell1 git:(master) ✗ env -i ./minishell 
minishell$ unset PWD OLDPWD
AddressSanitizer:DEADLYSIGNAL
=================================================================
==3200==ERROR: AddressSanitizer: BUS on unknown address 0x000109a45870 (pc 0x000509aa5b98 bp 0x7ffee61d5050 sp 0x7ffee61d5020 T0)
    #0 0x509aa5b98 in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType)+0x48 (/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/12.0.0/lib/darwin/libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x6b98)
    #1 0x509ae832a in wrap_free+0x10a (/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/12.0.0/lib/darwin/libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x4932a)
    #2 0x109a3b717 in free_node+0x47 (/mnt/homes/haqajjef/Desktop/minishell/minishell1/./minishell:x86_64+0x100011717)
    #3 0x109a3bafe in unset_one+0x30e (/mnt/homes/haqajjef/Desktop/minishell/minishell1/./minishell:x86_64+0x100011afe)
    #4 0x109a3bc29 in ft_unset+0x109 (/mnt/homes/haqajjef/Desktop/minishell/minishell1/./minishell:x86_64+0x100011c29)
    #5 0x109a43432 in check_builts+0x462 (/mnt/homes/haqajjef/Desktop/minishell/minishell1/./minishell:x86_64+0x100019432)
    #6 0x109a3509b in execute_cmd+0x2fb (/mnt/homes/haqajjef/Desktop/minishell/minishell1/./minishell:x86_64+0x10000b09b)
    #7 0x109a36113 in exec_tree+0x93 (/mnt/homes/haqajjef/Desktop/minishell/minishell1/./minishell:x86_64+0x10000c113)
    #8 0x109a42d9a in main+0x36a (/mnt/homes/haqajjef/Desktop/minishell/minishell1/./minishell:x86_64+0x100018d9a)
    #9 0x7fff73376cc8 in start+0x0 (/usr/lib/system/libdyld.dylib:x86_64+0x1acc8)

==3200==Register values:
rax = 0x0000000000000002  rbx = 0x0000000109a45880  rcx = 0x0000000000000003  rdx = 0x0000000000000000  
rdi = 0x0000000109a45880  rsi = 0x0000000109a45880  rbp = 0x00007ffee61d5050  rsp = 0x00007ffee61d5020  
 r8 = 0x00007ffee61d5060   r9 = 0x0000000000000001  r10 = 0x00007fff734bb41e  r11 = 0x0000000000000202  
r12 = 0x0000000000000001  r13 = 0x0000000000000000  r14 = 0x00007ffee61d5060  r15 = 0x0000000509b43d40  
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: BUS (/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/12.0.0/lib/darwin/libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x6b98) in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType)+0x48
==3200==ABORTING
[1]    3200 abort      env -i ./minishell


COMMAND    PID     USER   FD   TYPE DEVICE SIZE/OFF                NODE NAME
minishell 7351 haqajjef  cwd    DIR    1,9      408              872039 /mnt/homes/haqajjef/Desktop/minishell/minishell1
minishell 7351 haqajjef  txt    REG    1,9    88776              907526 /mnt/homes/haqajjef/Desktop/minishell/minishell1/minishell
minishell 7351 haqajjef  txt    REG    1,8  1568368 1152921500311885629 /usr/lib/dyld
minishell 7351 haqajjef    0u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    1u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    2u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    3u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    4u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    5u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    6u   CHR   16,1  0t92032                 685 /dev/ttys001
COMMAND    PID     USER   FD   TYPE DEVICE SIZE/OFF                NODE NAME
minishell 7351 haqajjef  cwd    DIR    1,9      408              872039 /mnt/homes/haqajjef/Desktop/minishell/minishell1
minishell 7351 haqajjef  txt    REG    1,9    88776              907526 /mnt/homes/haqajjef/Desktop/minishell/minishell1/minishell
minishell 7351 haqajjef  txt    REG    1,8  1568368 1152921500311885629 /usr/lib/dyld
minishell 7351 haqajjef    0u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    1u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    2u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    3u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    4u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    5u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    6u   CHR   16,1  0t92032                 685 /dev/ttys001
COMMAND    PID     USER   FD   TYPE DEVICE SIZE/OFF                NODE NAME
minishell 7351 haqajjef  cwd    DIR    1,9      408              872039 /mnt/homes/haqajjef/Desktop/minishell/minishell1
minishell 7351 haqajjef  txt    REG    1,9    88776              907526 /mnt/homes/haqajjef/Desktop/minishell/minishell1/minishell
minishell 7351 haqajjef  txt    REG    1,8  1568368 1152921500311885629 /usr/lib/dyld
minishell 7351 haqajjef    0u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    1u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    2u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    3u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    4u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    5u   CHR   16,1  0t92032                 685 /dev/ttys001
minishell 7351 haqajjef    6u   CHR   16,1  0t92032                 685 /dev/ttys001

if i do export

minishell$ pwd
/mnt/homes/haqajjef/Desktop/minishell/minishell1
minishell$ cd /bin
minishell$ pwd
/bin
minishell$ cd $OLDPWD
$
minishell$ pwd
/mnt/homes/haqajjef/Desktop/minishell/minishell1
minishell$ unset $OLDPWD
$
minishell: unset: /bin : not a valid identifier
minishell$ unset OLDPWD 
minishell(7772,0x507d55dc0) malloc: *** error for object 0x104fbedfb: pointer being freed was not allocated
minishell(7772,0x507d55dc0) malloc: *** set a breakpoint in malloc_error_break to debug
[1]    7772 abort      env -i ./minishell

minishell$ << $"USER"
>USER
>$USER


minishell$ echo q w e r t y > 1 > 2 > 3 > 4 > 5
minishell$ cat 5
cat: 5: No such file or directory





/////////////////////////////////

minishell$ ls > $dfgdfg
minishell: ambiguous redirect
Makefile        builtins        execusion       l               ls              minishell       minishell.c     minishell.h     minishell.o     parsing         |


//////////////////////////////////

cd :

Process 19640: 446 nodes malloced for 95 KB
Process 19640: 1 leak for 1024 total leaked bytes.

    1 (1.00K) ROOT LEAK: 0x7f8250009800 [1024]  length: 37  "/mnt/homes/haqajjef/Desktop/minishell"



bash-3.2$ exit fbdfb 41
exit
bash: exit: fbdfb: numeric argument required

bash-3.2$ exit "         1            "
exit
➜  minishell1 git:(master) ✗ $?

minishell$ unset _
{{{---> }}}_ls
{{{---> }}}(null)
[1]    98085 segmentation fault  ./minishell

minishell$ unset dfgfg
{{{---> }}}_
{{{---> }}}/mnt/homes/haqajjef/Desktop/minishell/minishell1/./minishell
[1]    98340 segmentation fault  ./minishell

leaks Report Version: 4.0
Process 3213: 408 nodes malloced for 104 KB
Process 3213: 1 leak for 1024 total leaked bytes.

    1 (1.00K) ROOT LEAK: 0x7fa8ae009800 [1024]  length: 47  has-length-byte:  "mnt/homes/haqajjef/Desktop/minishell/minishell1"

env -i ./minishell 
pwd


leaks Report Version: 4.0
Process 4525: 2413 nodes malloced for 174 KB
Process 4525: 14 leaks for 224 total leaked bytes.

    14 (224 bytes) << TOTAL >>
      1 (16 bytes) ROOT LEAK: 0x7fba83c05930 [16]
      1 (16 bytes) ROOT LEAK: 0x7fba83c05940 [16]
      1 (16 bytes) ROOT LEAK: 0x7fba83c05950 [16]
      1 (16 bytes) ROOT LEAK: 0x7fba83d0d5a0 [16]  length: 1  "3"
      1 (16 bytes) ROOT LEAK: 0x7fba83d0dde0 [16]
      1 (16 bytes) ROOT LEAK: 0x7fba83d0e0b0 [16]
      1 (16 bytes) ROOT LEAK: 0x7fba83d0e0c0 [16]  length: 1  "1"
      1 (16 bytes) ROOT LEAK: 0x7fba83e0ff90 [16]  length: 1  "4"
      1 (16 bytes) ROOT LEAK: 0x7fba83f04080 [16]
      1 (16 bytes) ROOT LEAK: 0x7fba83f04090 [16]
      1 (16 bytes) ROOT LEAK: 0x7fba86004080 [16]
      1 (16 bytes) ROOT LEAK: 0x7fba86004090 [16]  length: 1  "4"
      1 (16 bytes) ROOT LEAK: 0x7fba860040a0 [16]  length: 1  "2"
      1 (16 bytes) ROOT LEAK: 0x7fba86104080 [16]  length: 3  "101"

➜  minishell1 git:(master) ✗ env -i ./minishell
Bienvenue dans une nouvelle instance de minishell 🐚
minishell$  cat << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 101 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10
>
>
>
>
>
>
>
>
>1
>2
>3
>4
>4
>5
>6
>7
>8
>9
>101
>1
>2
>3
>4
>5 


minishell$ cat << $""
>
>
>
>
>^D





minishell$ 

bash-3.2$ cat << $""
> 
bash-3.2$ 


bash-3.2$ echo "'"
'
bash-3.2$ 

minishell$ echo "'"

minishell$ 