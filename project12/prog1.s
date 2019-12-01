# Name:                     Yonathan Adugna Kebede
# TerpConnect Username:     ykebed12
# UID:                      115659780
# Section Number:           0302

# This assembly program calculates the sum
# of cubes. The user enters a number, n, and 
# the program will calculate and print
# 1^3 + 2^3 + 3^3 + .... + n^3
# using the equation ((n * (n + 1)) / 2) ^ 2;

        .data

n:      .word 0
ans:    .word -1
        
        .text

main:   
        li              $v0, 5            # scanf("%d", &n)
        syscall
        move            $t0, $v0
        sw              $t0, n

        bltz            $t0, skip         # if n < 0 then skip
        
        # ans = ((n * (n + 1)) / 2) * ((n * (n + 1)) / 2);  
        add             $t1, $t0, 1       # ((n * (n + 1)) / 2) in register
        mul             $t1, $t1, $t0       
        div             $t1, $t1, 2

        mul             $t1, $t1, $t1     # ans = register ^ 2
        sw              $t1, ans

skip:   
        lw              $a0, ans          # print("%d", ans);
        li              $v0, 1
        syscall

        li              $v0, 11           # printf("\n");
        li              $a0, 10
        syscall

        li              $v0, 10           # quit program
        syscall