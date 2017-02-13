#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdio.h>

#define MAX 1000
using namespace std;

bool quit = false;

typedef struct LinkedList{
    char data[MAX] = {0};
    LinkedList *next = NULL;
} LinkedList;

class TextEdit{
    public:
        LinkedList *head;
        int currentLine, totalLines;
        char fileOut[100];

        TextEdit()
        {
            head = new LinkedList;
            currentLine = 0;
            totalLines = 0;
        }

        bool readFile(const char *name){
            FILE *fp;
            char buffer[MAX];
            fp = fopen(name,"r");

            if(!fp){
                cout << "Invalid File\n";
                return false;
            }

            LinkedList *cur = head;
            while(fgets(buffer,1000,fp) != NULL){
                LinkedList *newnode = new LinkedList;
                memcpy(newnode->data,buffer,MAX);
                newnode->next = NULL;
                cur->next = newnode;
                cur = newnode;
                totalLines++;
            }
            printFile();
            currentLine = totalLines;
            cout << "Current Line: " << currentLine << endl;
            fclose(fp);
            return true;
        }

        void printFile(){
            int counter = 1;
            LinkedList *cur = head->next;
            while(cur){
                cout << counter << ":";
                if(strncmp(cur->data,"",MAX) == 0){
                    cout << cur->data << endl;
                }
                else{
                    cout << cur->data;
                }
                cur = cur->next;
                counter++;
            }
        }

        void insert(char *text, int line){

            LinkedList *cur = head, *next = head->next;

            if(line <= totalLines){
                cout << "<=\n";
                for(int i = 1; i < line; i++){
                    cur = next;
                    next = next->next;
                }
                totalLines++;
                currentLine = line;
            }

            else{
                cout << ">\n";
                for(int i = 1; i < totalLines; i++){
                    cur = next;
                    next = next->next;
                }

                for(int i = 0; i < line - totalLines - 1; ++i){
                    LinkedList *newnode = new LinkedList;
                    cur->next = newnode;
                    newnode->next = NULL;
                    cur = newnode;
                }
                next = cur->next;
                currentLine = line;
                totalLines += line - totalLines;
            }

            LinkedList *newnode = new LinkedList;
            memcpy(newnode->data,text,MAX);
            newnode->next = next;
            cur->next = newnode;

            printFile();
            return;
        }

        void replace(char *text, int line){
            //cout << "Replacing line: "<< line << " with: " << text << endl;
            LinkedList *cur = head->next;
            for(int i = 1; i < line; i++){
                cur = cur->next;
            }
            memcpy(cur->data,text,MAX);
            printFile();
        }

        void del(int n, int m){
            LinkedList *cur = head->next, *next, *prev = head;
            //do some garb cleanup maybe lol

            LinkedList *singleDel;
            if (m == 0){
                if(n == 1){ // special case adjust head
                    singleDel = cur;
                    head->next = cur->next;
                    delete singleDel;
                }
                //go to n then delete
                else{
                    for(int i = 1; i < n; i++){
                        prev = prev->next;
                        cur = cur->next;
                        next = cur->next;
                    }
                    prev->next = next;
                    singleDel = cur;
                    delete singleDel;
                }
                totalLines--;
                currentLine--;
            }
            else{ // del n to m inclusive
                LinkedList *delPtr[m-n+1];
                int ctr = 0;

                for(int i = 1; i < n; i++){
                    prev = prev->next;
                    cur = cur->next;
                    next = cur->next;
                }

                for(int j = 0; j < m - n + 1; j++ ){
                    delPtr[ctr] = cur;
                    cur = cur->next;
                    ctr++;
                }

                prev->next = cur; // points to before delete -> after;

                for(int k = 0; k < m-n+1; k++){
                    delete delPtr[k];
                }
                totalLines -= m - n + 1;
                currentLine -= m - n + 1;
            }
        }

        void printLine(int n, int m){
            LinkedList *cur = head->next;
            for (int i = 1; i < n; ++i){
                cur = cur->next;
            }
            if (m == 0){ //single line
                cout << cur->data;
            }
            else{
                for(int i = n; i < m; ++i){
                    if(strncmp(cur->data,"",MAX) == 0){
                        cout << n << ":" << cur->data << endl;
                    }
                    else{
                        cout << n << ":" << cur->data;
                    }
                    cur = cur->next;
                }
            }
        }

        bool command(char *cmd){
            char *token;

            token = strtok(cmd," ");

            if(strncmp(token,"I",1) == 0){
                char *token1,*token2;
                token1 = strtok(NULL," ");
                token2 = strtok(NULL," ");

                if(token2 == NULL){ //only one param insert before curr line
                    insert(token1, currentLine);
                    return true;
                }
                else{ //go to line then insert
                    insert(token2, atoi(token1));
                    return true;
                }
            }

            else if(strncmp(token,"D",1) == 0){
                int n,m;
                token = strtok(NULL," ");
                if (token == NULL){ //delete current line
                    del(currentLine, 0);
                    return true;
                }
                n = atoi(token);
                if (n > totalLines){
                    cout << "Error: n > totalLines\n";
                    return false;
                }
                token = strtok(NULL," ");
                if (token == NULL){ //delete line n
                    del(n,0);
                    return true;
                }
                m = atoi(token);
                if (n > m || m == 0 || n == 0){
                    cout << "Error: n>m || m == 0 || n == 0\n";
                    return false;
                }
                //delete line n to m
                del(n,m);
                return true;
            }
            else if(strncmp(token,"V",1) == 0){
                printFile();
                return true;
            }
            else if(strncmp(token,"G",1) == 0){
                token = strtok(NULL," ");
                if (token == NULL){ //go to first line
                    currentLine = 1;
                    return true;
                }
                else{ // go to line n
                    currentLine = atoi(token);
                    return true;
                }
            }
            else if(strncmp(token,"L",1) == 0){
                int n,m;
                token = strtok(NULL," ");
                if (token == NULL){ //display content of current line
                    printLine(currentLine,0);
                    return true;
                }
                n = atoi(token);
                if (n > totalLines){
                    cout << "Value > TotalLines\n";
                    return false;
                }
                token = strtok(NULL," ");
                if (token == NULL){ //display line n
                    printLine(n,0);
                    return true;
                }
                m = atoi(token);
                if (n > m || m == 0 || n == 0){
                    cout << "Error: n>m || m == 0 || n == 0\n";
                    return false;
                }
                //display line n to m
                printLine(n,m);
                return true;
            }
            else if(strncmp(token,"S",1) == 0){
                token = strtok(NULL," ");
                //prompt for line

                if (token != NULL && atoi(token) > totalLines){
                    return false;
                }
                char buffer[MAX];
                cout << "Enter replacement string:";
                fgets(buffer,MAX,stdin);
                cout << "You Entered: " << buffer << endl;

                if (token == NULL){
                    replace(buffer,currentLine);
                    //replace current line with this
                    //call V w/ current line #
                    return true;
                }

                else{
                    replace(buffer,atoi(token));
                    //replace  line n with this
                    //call v with line n
                    return true;
                }
            }
            else if(strncmp(token,"E",1) == 0){
                //save and exit write line by line to fileOut;
                FILE *fp;
                fp = fopen(fileOut,"w");
                cout << "Saving to:" << fileOut << "===" <<  endl;
                if(!fp){
                    cout << "Error making output file!\n";
                    return false;
                }
                LinkedList *cur = head->next;

                while(cur){
                    if (strncmp(cur->data,"",1000) != 0){
                        fputs(cur->data,fp);
                    }
                    else{
                        fputs("\n",fp);
                    }
                    cur = cur->next;
                }
                //iterate thru linked list via head and insert line
                fclose(fp);
                quit = true;
                cout << "Closing\n";
                return true;
            }
            else if(strncmp(token,"Q",1) == 0){
                quit = true;
                return true;
            }
            else{
                return false;
            }

            return false;
        }
};



int main(int argc, char **argv)
{
    if (argc != 4){
        cout << "Error requires 3 arguments EDIT filein fileout\n";
        return 0;
    }

    if (strncmp(argv[1],"EDIT",4) != 0){
        cout << "Error syntax is ./prog EDIT filein fileout\n";
        return 0;
    }

    TextEdit edit;
    bool check = edit.readFile(argv[2]);
    memcpy(edit.fileOut,argv[3],100); //assume max file name = 100 chars

    if (!check){
        cout << "Error invalid file\n";
        return 0;
    }

    char buffer[100];

    while(!quit){
        fgets(buffer,100,stdin);
        if (!edit.command(buffer)){
            cout << "Invalid command try again!\n";
            continue;
        }
        if(!quit){
            cout << "Current Line: " << edit.currentLine << endl;
        }
    }

    return 0;
}
