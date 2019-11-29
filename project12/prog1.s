        .data

n:      .word 0
ans:    .word -1
eoln:   .asciiz "\n"
        
        .text
 
main:   li              $v0, 5              # scanf("%d", &n)
        syscall
        move            $t2, $v0
        sw              $t2, n

        bltz            $t2, skip           # if n < 0 then skip
        
        add             $t3, $t2, 1         # ans = ((n * (n + 1)) / 2) * ((n * (n + 1)) / 2);
        mul             $t3, $t3, $t2
        div             $t3, $t3, 2
        mul             $t3, $t3, $t3
        sw              $t3, ans

skip:   move            $a0, $t3            # print("%d", ans);
        li              $v0, 1
        syscall

        la              $a0, eoln            # printf("%c", '\n')
        li              $v0, 4
        syscall

        li              $v0, 10              # quit program
        syscall