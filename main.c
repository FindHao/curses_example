#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <locale.h>
#include <openssl/md5.h>
#include <string.h>
#include <openssl/sha.h>
#include "rsa_enctypt.h"

#define menu_item_number 5   /*菜单项目数*/
#define menu_left_margin 4   /*菜单项目左边空白*/

char menu[menu_item_number][60]=//菜单文本
        {"md5加密字符串\0", "SHA1加密文件\0", "RSA加解密\0","键盘码\0", "Exit\0"};

int menu_pos[menu_item_number][2]=
        {{2,3},{2,4},{2,5},{2,6},{2,7}};
void md5sum(){
    echo();
    char  raw_str[100];
    clear();
    getstr(raw_str);
    MD5_CTX ctx;
    unsigned char outmd[16];
    int i=0;

    memset(outmd,0,sizeof(outmd));
    MD5_Init(&ctx);
    int len_str = strlen(raw_str);
    MD5_Update(&ctx,raw_str,len_str);
    MD5_Final(outmd,&ctx);
    printw("--------\n密文：\n");
    for(i=0;i<16;i<i++)
    {
        printw("%02X",outmd[i]);
    }
    printw("\n");
    noecho();
}
void sha_encrypt(){
    SHA_CTX stx;
    unsigned char outmd[20];//注意这里的字符个数为20
    char buffer[1024];
    char filename[32]="the_zen_of_python";
    int len=0;
    int i;
    FILE * fp=NULL;
    fp=fopen(filename,"rb");
    printw("Encrypting the file : the_zen_of_python\n");
    if(fp==NULL)
    {
        printw("Can't open file\n");
        return;
    }

    SHA1_Init(&stx);
    while((len=fread(buffer,1,1024,fp))>0)
    {
        SHA1_Update(&stx,buffer,len);
        memset(buffer,0,sizeof(buffer));
    }
    SHA1_Final(outmd,&stx);

    for(i=0;i<20;i<i++)
    {
        printw("%02X",outmd[i]);
    }
    printf("\n");
    return;
}
void rsa_encrypt(){
    char *source="i like dancing !";
    char *ptr_en,*ptr_de;
    printw("source is    :%s\n",source);
    ptr_en=my_encrypt(source,PUBLICKEY);
    printw("after encrypt:%s\n",ptr_en);
    ptr_de=my_decrypt(ptr_en,OPENSSLKEY);
    printw("after decrypt:%s\n",ptr_de);
    if(ptr_en!=NULL){
        free(ptr_en);
    }
    if(ptr_de!=NULL){
        free(ptr_de);
    }
    return ;
}
void initial() /* 自定开启 curses 函式*/
{
    setlocale(LC_ALL,"");
    initscr();
    cbreak();
    nonl();
    //设置不回显
    noecho();
    intrflush(stdscr,FALSE);
    keypad(stdscr,TRUE);
    refresh();
}

/*显示主菜单：参数1：当前选中菜单；参数2：是否显示子菜单*/
void menu_display(int selected_index)
{
    int i;
    move (1,menu_left_margin);
    printw ("嵌入式系统实验一");

    for (i=0; i<menu_item_number; i++)
    {
        move (menu_pos[i][1], menu_pos[i][0]+menu_left_margin);
        if(i== selected_index){
            attron(A_REVERSE);
            /* 开启反白模式*/
            printw ("%s", menu[i]);
            /* 输出反白字元  addstr(menu[i]);*/
            attroff(A_REVERSE);
            /* 关闭反白模式*/
        }else
            printw ("%s", menu[i]); /* 输出反白字元, addstr(menu[i]); */
    }
}

int main()
{
    int ch; /* 宣告 ch 为整数,配合 getch()使用 */
    int selected_index = 0;//选中父菜单，默认为第一个
    initial(); /* 调用 initial(), 启动 curses模式, */

    menu_display(selected_index);

    while(1) { /* 以无限循环不断等待输入*/
        ch=getch(); /* 等待自键盘输入字元*/
        switch(ch) /* 判断输入字元为何*/
        {
            case KEY_UP:   /* 判断是否"↑"键被按下*/

                --selected_index;
                if (selected_index < 0)
                    selected_index=menu_item_number-1;
                menu_display(selected_index);

                break;
            case KEY_DOWN:  /* 判断是否"↓"键被按下*/
                ++selected_index;
                if (selected_index >= menu_item_number)
                    selected_index=0;
                menu_display(selected_index);
                break;
            case '\r': /* 判断是否 ENTER 键被按下*/
                clear();
                switch(selected_index)//菜单对应处理函数
                {
                    case 0:
                        md5sum();break;
                    case 1: sha_encrypt();break;
                    case 2: rsa_encrypt();break;
                    case 3:
                        endwin();
                        system("clear");
                        system("sudo showkey -as ");
                        clear();
                        break;
                    default:
                        endwin();
                        exit(0);
                }
                printw(" Press any to continue...");
                getch();
                clear();
                menu_display(selected_index);
                break;
            case 27: /* 判断是否[ESC]键被按下*/
                endwin(); /* 结束此程式*/
                exit(1); /* 结束 curses 模式*/
            default:
                break;
        }
    }
}