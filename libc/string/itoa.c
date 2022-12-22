void itoa(char *dest, int num) {
    memset(dest, 0, sizeof dest);
    char stack[12] = {0};
    int i;
    for (i = 0; i < 11; i++) {
        stack[i] = num % 10;
        num /= 10;
        if (num == 0) break;
    }
    for (int k = 0; k <= i; k++) {
        dest[k] = stack[i - k] + '0';
    }
    dest[i + 1] = '\0';
}
