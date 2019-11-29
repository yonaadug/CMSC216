            .data

x:          .word 0
y:          .word 0
result:     .word 0

            .text

main:       li      $sp, 0x7ffffffc
            





  scanf("%d %d", &x, &y);

  result= count_digit(x, y);

  printf("%d\n", result);

  return 0;
}
