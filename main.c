#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//////////////////////////////////
#define MAXOP 100
#define NUMBER '0'
#define NAME 'n'
void mathfnc(char []);



//////////////////////////////////
int getop(char s[]);
int getch(void);
void ungetch(int);
//////////////////////////////////
void push(double);
double pop(void);
void clear(void);

////////////////////////////////////
#define MAX_J 3
char arr_type[MAX_J];
void buffortype(char arr[], int type);
void ungets(char s[]);


int main()
{
    char s[MAXOP];
    int type, var=0;
    double val[26];
    
    for(int i=0; i<26; i++)
    {
        val[i]=0.0;
    }
    
    double op2, op1, v;
   
    char s2[]="3.333 1.67 +";

    ungets(s2);    
    
    while((type=getop(s))!=EOF){
        buffortype(arr_type, type);
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case NAME:
            mathfnc(s);
            break;
        case '+':
            push(pop()+pop());
            break;
        case '*':
            push(pop()*pop());
            break;
        case '-':
            op2=pop();
            push(pop()-op2);
            break;
        case '/':
            op2=pop();
            if(op2!=0.0){
                push(pop()/op2);                 
            }else{
                printf("Error, делить на 0 нельзя!\n");               
            }
            break;
        case 'c':
            clear();
            break;
        case '?':
            op2=pop();
            printf("\t%.8g\n",op2);
            push(op2);
            break;
        case 'd':
            op2=pop();
            push(op2);
            push(op2);
            break;
        case 's':
            op1=pop();
            op2=pop();
            push(op1);
            push(op2);
            break;    
        case '\n':
            v=pop();                               
            if(arr_type[1]!='='){
                printf("\t%.8g\n", v);
            }           
            break;
        case '=':
            pop();
            if(var>='A' && var<='Z'){                
                val[var-'A']=pop();
                printf("%c %c %.8g\n", arr_type[1], arr_type[0], val[var-'A']);
            }else{
                printf("Ошибка, отсутсвует имя переменной\n");
            }
            break;
        default:
            if(type>='A' && type<='Z'){
                push(val[type-'A']);
                
            }
            else if(type==v)
            {
                push(v);                
            } 
            else
            {
                printf("Error, неивестная команда %s\n", s);
            }                      
            break;
        }
        var=type;
    }    
    return 0;
}

///////////////////////////////////////
int getop(char s[]){
    int i, c;
    while((s[0]=c=getch())==' ' || c=='\t');
    s[1]='\0';
    i=0;

    if(islower(c)){
        while (islower(s[++i]=c=getch()));
        s[i]='\0';
        if(c!=EOF){
            ungetch(c);
        }
        if(strlen(s)>1){
            return NAME;
        }
        else{
            return c;
        }
    }

    if(!isdigit(c) && c!='.' && c!='-'){
        return c;
    }
    
    if(c=='-'){
        if(isdigit(c=getch()) || c=='.'){
            s[++i]=c;
        }else{
            if(c!=EOF){
                ungetch(c);
            }
            return '-';
        }
    }
    if(isdigit(c)){
        while(isdigit(s[++i]=c=getch()));       
    }
    if(c=='.'){
        while(isdigit(s[++i]=c=getch()));
    }
    s[i]='\0';
    if(c!=EOF){
        ungetch(c);
    }
    return NUMBER;
}




////////////////////////////////////////
#define MAXBUF 100

int buf[MAXBUF];
int bufp = 0;

int getch(void){
    return (bufp>0)? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp>MAXBUF){
        printf("Error, too many characters (buf is full)!\n");
    }else{
        buf[bufp++]=c;
    }
}

////////////////////////////////////

#define MAXVAL 100
double val[MAXVAL];
int sp = 0;

void push(double f){
    if(sp>MAXVAL){
        printf("Error, stack is full, can't push %.8g\n", f);
    }else{
        val[sp++]=f;
    }
}

double pop(void){
    if(sp>0){
        return val[--sp];
    }
    else{
        if(arr_type[1]!='='){
            printf("Error, stack is empty!\n");
            //printf("%c\n",arr_type[1]);
        }
        
        return 0.0;
    }
}

void clear(void){
    sp=0;
}

////////////////////////////////////////////
void buffortype(char arr[], int type)
{
    for(int i=MAX_J-1; i>0; i--){
        arr[i]=arr[i-1];
    }
    arr[0]=type;
}

void ungets(char s[]){
    int len=strlen(s);
    while(len>0){
        ungetch(s[--len]);
    }
}

////////////////////////////////////////////////
void mathfnc(char s[])
{
    double op2;
    if(strcmp(s,"sin")==0){
        push(sin(pop()));
    }
    else if(strcmp(s,"cos")==0){
        push(cos(pop()));
    }
    else if(strcmp(s,"exp")==0){
        push(exp(pop()));
    }
    else if(strcmp(s,"pow")==0){
        op2=pop();
        push(pow(pop(),op2));
    }else{
        printf("Ошибка: %s  не поддерживается \n", s);
    }    
}
