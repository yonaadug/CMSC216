# Name:                     Yonathan Adugna Kebede
# TerpConnect Username:     ykebed12
# UID:                      115659780
# Section Number:           0302

# This program counts the number of times a digit
# occurs in a number recursively

# I pledge on my honor that I have not given or recieved
# any unauthorized assistance on this examination or assignment.

        .data

x:      .word 0
y:      .word 0
answer: .word 0

        .text

# Main function
main:   li          $sp, 0x7ffffffc     # set up stack ptr

        li          $v0, 5              # scanf("%d", &x)
        syscall
        move        $t0, $v0
        sw          $t0, x

        li          $v0, 5              # scanf("%d", &y)
        syscall
        move        $t1, $v0
        sw          $t1, y

        sw          $t0, ($sp)          # push x and y into stack
        sub         $sp, $sp, 4
        sw          $t1, ($sp)
        sub         $sp, $sp, 4

        jal         count_digit         # call count_digit function

        add         $sp, $sp 8          # pop x and y from stack

        move        $t0, $v0            # store value in register
        sw	    $t0, answer

        li          $v0, 1              # printf("%d", n)
        lw          $a0, answer
        syscall

        li          $v0, 11             # printf("\n");
        li          $a0, 10
        syscall

        li          $v0, 10             # quit program
        syscall
# End of Main Function

# Start of count_digit function
count_digit:
                                        # prologue
        sub         $sp, $sp, 16        # set new stack ptr
        sw          $ra, 16($sp)        # save ret addr in stack
        sw          $fp, 12($sp)        # save old frame ptr in stack
        add         $fp, $sp, 16        # set new frame ptr

        lw          $t0, 8($fp)         # get num arg
        lw          $t1, 4($fp)         # get digit arg
        li          $t2, -1             # result in register
        li          $t3, 0              # rightmost_digit in register

        li          $t4, 9              # load 9 into register
                                        # for comparisons


        sw          $t2, 8($sp)         # int result = -1
        sw          $t3, 4($sp)         # int rightmost_digit

        # first if
        bltz        $t1, exit           # skip if digit < 0
        bgt         $t1, $t4, exit      # skip if digit > 9

        li          $t2, 0              # result = 0
        sw          $t2, 8($sp)

        # second if: if (num >= 0) go to base case
        bgez        $t0, basecase       # if (num >= 0)
        neg         $t0, $t0            # negate num
        sw          $t0, 8($fp)

        # start of first base case
basecase:   
        bltz        $t0, recurs         # if num < 0 || num > 9 
        bgt         $t0, $t4, recurs    #   go to recursion

        bne         $t0, $t1, case_2    # if num == digit

        li          $t2, 1              # result = 1
        sw          $t2, 8($sp)

        j           exit                # exit function
        # end of first base case


        # second base case
case_2: li          $t2, 0              # result = 0
        sw          $t2, 8($sp)
        
        j		    exit                # exit function


recurs:     
        rem         $t3, $t0, 10        # rightmost = num % 10;
        sw          $t3, 4($sp)
        # end of second base case


        # recursion section start
        div         $t0, $t0, 10        # num/10 in register

        sw          $t0, ($sp)          # push num/10 and digit 
        sub         $sp, $sp, 4         #   into stack
        sw          $t1, ($sp)
        sub         $sp, $sp, 4

        jal         count_digit         # call count_digit (recursion)

        add         $sp, $sp 8          # pop num/10 and digit from stack

        move        $t2, $v0            # result = 
        sw          $t2, 8($sp)         #   count_digit(num / 10, digit);

        lw          $t3, 4($sp)         # put rightmost in register
        lw          $t1, 4($fp)         # put digit in register

        
        bne         $t3, $t1, exit      # if (rightmost_digit != digit)
                                        #   go to exit

        add         $t2, $t2, 1         # result++
        sw          $t2, 8($sp)
        # recursive section end


        # exit for count_digit
exit:       
        lw          $v0, 8($sp)         # return result

                                        # epilogue
        lw          $ra, 16($sp)        # load ret addr from stack
        lw          $fp, 12($sp)        # restore old frame ptr from stack
        add         $sp, $sp, 16        # reset stack ptr
        jr          $ra                 # ret to caller using saved ret
                                            # addr
# End of count_digit function
