# Name:                     Yonathan Adugna Kebede
# TerpConnect Username:     ykebed12
# UID:                      115659780
# Section Number:           0302

# This program counts the number of times a digit
# occurs in a number using a while loop to iterate
# through each digit using mod (rem) and integer
# division.
        .data

x:      .word 0
y:      .word 0
result: .word 0

        .text

# Main Function Start
main:       
        li          $sp, 0x7ffffffc     # set up stack ptr

        li          $v0, 5              # scanf("%d", &x)
        syscall
        move        $t0, $v0
        sw          $t0, x

        li          $v0, 5              # scanf("%d", &y)
        syscall
        move        $t1, $v0
        sw          $t1, y

        sw          $t0, ($sp)          # push x and y into stack
        sub         $sp, $sp, 4         #   for use in the function
        sw          $t1, ($sp)
        sub         $sp, $sp, 4

        jal         count_digit         # call the count_digit func

        add		    $sp, $sp 8          # pop x and y from stack

        move        $t0, $v0            # store value in register
        sw	        $t0, result

        li          $v0, 1              # printf("%d", n)
        lw          $a0, result
        syscall

        li          $v0, 11             # printf("\n");
        li          $a0, 10
        syscall

        li          $v0, 10             # quit program
        syscall
# Main Function End

# Count_digit function start
count_digit:
                                        # prologue
        sub         $sp, $sp, 16        # set new stack ptr
        sw          $ra, 16($sp)        # save ret addr in stack
        sw          $fp, 12($sp)        # save old frame ptr in stack
        add         $fp, $sp, 16        # set new frame ptr

        lw          $t0, 8($fp)         # get num arg
        lw          $t1, 4($fp)         # get digit arg
        li          $t2, -1             # count in register
        li          $t3, 0              # rightmost_digit in register

        sw          $t2, 8($sp)         # int count = -1
        sw          $t3, 4($sp)         # int rightmost_digit


        bltz        $t1, exit           # skip if digit < 0
        li          $t4, 9
        bgt         $t1, $t4, exit      # skip if digit > 9

        li          $t2, 0              # count = 0
        sw          $t2, 8($sp)

        bgez        $t0, if             # if (num >= 0)
        neg         $t0, $t0            # negate num
        sw          $t0, 8($fp)


if:         
        bnez        $t0, loop           # if (digit < 0 || digit > 9)
        bnez        $t1, loop           # loop

        li          $t2, 1              # count = 1
        sw          $t2, 8($sp)

        # While Loop & else statment start
loop:       
        blez		$t0, exit           # beginning of while loop

        rem         $t3, $t0, 10        # rightmost = num % 10
        sw          $t3, 4($sp)

        bne         $t3, $t1, skipcount # if rightmost_digit != digit
        add         $t2, $t2, 1
        sw          $t2, 8($sp)
        
skipcount:  
        div         $t0, $t0, 10        # num /= 10
        sw          $t0, 8($sp)
        j           loop
        # While Loop end

        # last part of count_digit function
exit:       
        move        $v0, $t2            # return count
        
                                        # epilogue
        lw          $ra, 16($sp)        # load ret addr from stack
        lw          $fp, 12($sp)        # restore old frame ptr from stack
        add         $sp, $sp, 16        # reset stack ptr
        jr          $ra                 # ret to caller using saved ret
                                            # addr
# Count_digit function end
