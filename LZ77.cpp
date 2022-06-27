#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<cstdlib>

using namespace std;

typedef struct info
{
    unsigned int position;
    unsigned int length;
    unsigned char next_sign;
    struct info *next;
}info;

void encode(info** node, char dict_buf[], int buf_len, int dict_len)
{
    if(strlen(dict_buf) < buf_len + dict_len && strlen(dict_buf) > dict_len )
    {
        buf_len = strlen(dict_buf) - dict_len;
    }
    if(strlen(dict_buf) <= dict_len)
    {
        return;
    }
    int len = buf_len + 1;
    bool is_found = false;
    while(!is_found && len >= 2)
    {
        len = len - 1;
        for(int i = 0 ; i + len <= dict_len ; i++)
        {
            for(int j = dict_len ; j <= dict_len + len - 1 ; j++)
            {
                if(dict_buf[i + j - dict_len] != dict_buf[j])
                {
                    is_found = false;
                    break;
                }
                else is_found = true;
            }

            if(is_found)
            {
                (*node)->position = i;
                (*node)->length = len;
                (*node)->next_sign = dict_buf[dict_len + len];
                break;
            }
        }
    }
    if(!is_found)
    {
         len = 0;
        (*node)->position = 0;
        (*node)->length = len;
        (*node)->next_sign = dict_buf[dict_len];
    }
    printf("\n<%d,%d,%c>",(*node)->position,(*node)->length,(*node)->next_sign);

    for(int i = 0 ; i < strlen(dict_buf) - len - 1 ; i++)
    {
        dict_buf[i] = dict_buf[i + len + 1];
    }
    dict_buf[strlen(dict_buf) - (len + 1)] = '\0';
}
void decode(char str[], char dict[], char word[], char exit[])
{
    int i = 0;
    for(i = 0 ; i < str[1] - 48 ; i++)
    {
        word[i] = dict[str[0] - 48 + i];
    }
    word[i] = str[2];
    word[i + 1] = '\0';
    int n = strlen(exit);
    for(i = 0 ; word[i] ; i++)
    {
        exit[n + i] = word[i];
    }
    exit[n + i] = '\0';
    for(i = 0 ; exit[i] ; i++) {
        printf("%c", exit[i]);
    }
    printf("\n");

    n = strlen(dict);
    int c = 0;
    for(i = 0 ; i < n ; i++)
    {
        if(i < n - strlen(word))
        {
            dict[i] = dict[i + strlen(word)];
        }
        else
        {
            dict[i] = word[c];
            c++;
        }
    }
    for(i = 0 ; str[i + 3] ; i++)
    {
        str[i] = str[i + 3];
    }
    str[i] = '\0';
}

int main()
{
    info *head = NULL;
    head = (info *) malloc(sizeof(info));
    head->next = NULL;
    info *node = head;

    int dict_len;
    int buf_len;
    unsigned int position = 0;
    unsigned int length = 0;
    unsigned char next_sign;
    int choice;
    FILE *text, *code;

    char dict_buf[100];

    std::cout << "Podaj dlugosc slownika: ";
    std::cin >> dict_len;
    std::cout << "Podaj dlugosc bufora: ";
    std::cin >> buf_len;

    char dict[dict_len];
    char word[dict_len];
    char str[100];
    char exit[100];
    std::cout << "Wybierz opcje:" << std::endl;
    std::cout << "[1] Kodowanie"  << std::endl;
    std::cout << "[2] Dekodowanie"<< std::endl;;
    std::cin >> choice;
    if(choice == 1)
    {
        text = fopen("./text.txt", "r");
        code = fopen("./code.txt", "w");
    }
    else code = fopen("./code.txt", "r");
    if (choice == 1)
    {
        fscanf(text, "%s", dict_buf);
        cout << dict_buf << endl;
        next_sign = dict_buf[0];

        for (int i = strlen(dict_buf) + dict_len - 1; i >= dict_len; i--)
        {
            dict_buf[i] = dict_buf[i - (dict_len - 1)];
        }
        for (int i = 0; i < dict_len; i++)
        {
            dict_buf[i] = next_sign;
        }
        (*node).position = 0;
        (*node).length = 0;
        (*node).next_sign = next_sign;
        cout << "<" << position << "," << length << "," << next_sign << ">";
        fprintf(code, "%d%d%c", node->position, node->length, node->next_sign);
        node->next = (info*)malloc(sizeof(info));
        node = node->next;
        node->next = NULL;

        while (strlen(dict_buf) > dict_len)
        {
            encode(&node, dict_buf, buf_len, dict_len);
            fprintf(code, "%d%d%c", node->position, node->length, node->next_sign);
            node->next = (info*)malloc(sizeof(info));
            node = node->next;
            node->next = NULL;
        }
        fclose(text);
        fclose(code);
    }
    else if (choice == 2)
    {
        fscanf(code, "%s", str);
        exit[0] = str[2];
        word[0] = str[2];
        int i;
        for(i = 0 ; i < dict_len ; i++)
        {
            dict[i] = str[2];
        }
        printf("\nSekwencja zdekodowana: \n");
        printf("%c\n",exit[0]);

        for(i = 0;  str[i + 3] ; i++)
        {
            str[i] = str[i + 3];
        }
        str[i] = '\0';

        while(strlen(str) != 0)
        {
            decode(str, dict, word, exit);
        }
        fclose(code);
    }

    return 0;
} 
