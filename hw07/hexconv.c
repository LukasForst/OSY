#define MAX_SIZE_HEX 8
#define MAX_STRING_SIZE 10

char new_line[1];
char prefix[2];

unsigned int string_len(const char *buffer) {
    unsigned int cursor = 0;
    while (buffer[cursor] != '\0') {
        cursor++;
    }

    return cursor;
}

void dex_to_hec(unsigned int n, char *buffer) {
    if(n == 0){
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    char hexaDeciNum[21];

    int i = 0;
    while (n != 0) {
        unsigned int temp = 0;
        temp = n % 16;
        hexaDeciNum[i++] = (char) (temp + (temp < 10 ? 48 : 87));
        n = n / 16;
    }

    int index = 0;
    for (int j = i - 1; j >= 0; j--) {
        buffer[index++] = hexaDeciNum[j];
    }
    buffer[index] = '\0';
}

int isnum(char ch) {
    return ch >= '0' && ch <= '9';
}

int isspc(char ch) {
    return ch == ' ' || ch == '\n';
}

unsigned int syscall3(unsigned int v, unsigned int a1, unsigned int a2, unsigned int a3) {
    asm volatile("int $0x80":"+a"(v): "b"(a1), "c"(a2), "d"(a3):"memory");
    return v;
}

int end(unsigned int return_value) {
    return syscall3(1, return_value, 0, 0);
}

static void print(unsigned num) {
    char buf[21];
    dex_to_hec(num, buf);

    int ret = syscall3(4, 1, (unsigned int) prefix, 2);
    if (ret == -1)
        end(1);

    ret = syscall3(4, 1, (unsigned int) buf, string_len(buf));
    if (ret == -1)
        end(1);

    ret = syscall3(4, 1, (unsigned int) new_line, 1);
    if (ret == -1)
        end(1);
}


void _start() {
    new_line[0] = '\n';
    prefix[0] = '0';
    prefix[1] = 'x';

    char buf[20];
    unsigned num = 0;
    int i = 0;
    int num_digits = 0;
    unsigned chars_in_buffer = 0;

    for (/* no init */; /* no end condition */; i++, chars_in_buffer--) {
        if (chars_in_buffer == 0) {
            int ret = syscall3(3, 0, (unsigned int) buf, 20);
            if (ret < 0)
                end(1);
            i = 0;
            chars_in_buffer = ret;
        }
        if (num_digits > 0 && (chars_in_buffer == 0 /* EOF */ || !isnum(buf[i]))) {
            print(num);
            num_digits = 0;
            num = 0;
        }
        if (chars_in_buffer == 0 /* EOF */ || (!isspc(buf[i]) && !isnum(buf[i])))
            break;

        if (isnum(buf[i])) {
            num = num * 10 + buf[i] - '0';
            num_digits++;
        }
    }
    end(0);
}