    #include <stdio.h>

    int main()
    {
        switch (int c = getchar())
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                printf("Saw vowel %c\n", c);
            break;

            case EOF:
                printf("Saw EOF\n");
            break;

            case '0' ... '9':
                printf("Saw number character %c\n", c);
            break;

            default:
                printf("Saw other character, hex value 0x%2x\n", c);
        }
    }
