
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "lab1.h"
#include <cstring>

// file streams and c++ string functions

string input_text_fs(){
    cout<<"Enter text , enter \"*\" on a line by itself to stop\n";
    string text;
    string line;
    // поки не натиснута "*" + enter
    do{
        getline(cin, line);
        text += line + '\n';
    }while (int(line[0]) != 42);

    // відкидаємо 3 зайвих символи (1 зайву * і \n)
    text = text.substr(0, text.size()-3);
    return text;
}

void create_file_fs(const string filename) {
    bool entered= false;
    string choice,text;
    ofstream out_file;
    do {
        if (choice == "Y" || choice == "y") {
            out_file.open((char *) filename.c_str(), ios::app);
            text = input_text_fs();
            out_file << text;
            out_file.close();
        } else {
            if(!entered){
                out_file.open((char *) filename.c_str());
                text = input_text_fs();
                out_file << text;
                out_file.close();
                entered= true;
            }
        }
        cout << "Do you want to add more text (y/n)" << endl;
        cin >> choice;
    } while (choice == "Y" || choice == "y");
}

void output_file_fs(const string filename){

    ifstream in_file((char*)filename.c_str());
    if(!in_file){
        cerr<<"Error while reading a file!"<<endl;
    }else{
        cout<<"\n______"<< filename <<"'s contents:______\n";
        string line;
        while(getline(in_file, line)){
            cout<<line<<endl;
        }
    }
    in_file.close();
}

void new_file_from_old_fs(const string filename,const string new_filename){
    void replace_characters_fs(string &);
    string line;
    bool is_odd=true;

    ifstream in_file((char*)filename.c_str());
    ofstream new_out_file((char*)new_filename.c_str());

    if(!in_file||!new_out_file){
        cerr<<"Error while working with a file!\n"<< endl;
    }

    while (getline(in_file,line)){
        if (is_odd){


            int len = line.length();
            int cur_start_i=0,cur_end_i=len-1;

            for (int i = 0; i < len; i++) {
                if (iswspace(line[i]) || line[i] == '.' && (!iswspace(line[i + 1]) && line[i + 1] != '.')) {
                    cur_start_i = i + 1;
                }
                if (line[i] != ' ' && line[i] != '.' && (line[i + 1]=='\0'||line[i + 1] == ' ' || line[i + 1] == '.')) {
                    cur_end_i = i;
                    int word_length=cur_end_i - cur_start_i +1;

                    string word = line.substr(cur_start_i,word_length);
                    replace_characters_fs(word);
                    line.replace(cur_start_i,word_length,word);
                }
            }
            new_out_file<< line <<endl;
        }
        is_odd=!is_odd;
    }
    in_file.close();
    new_out_file.close();
};

void modify_old_file_fs(const string filename) {
    void copy_file_fs(const string, const string);
    void del_biggest_word_fs(string &line);


    bool isEven = false;
    string line, text;

    ifstream in_file((char*)filename.c_str());
    ofstream copy("temp.txt");

    if(!in_file||!copy){
        cerr <<"Error while working with a file!" << endl;
    }

    while (getline(in_file, line)) {
        if (isEven) {
            del_biggest_word_fs(line);
        }
        copy<<line<<endl;
        text += line;
        isEven = !isEven;
    };

    copy_file_fs("temp.txt",filename);
    in_file.close();
    copy.close();
}

void copy_file_fs(const string source_file, const string target_file){
    string line;
    ifstream in_file((char*)source_file.c_str());
    ofstream out_file((char*)target_file.c_str());
    while (getline(in_file,line)){
        out_file<<line<<endl;
    }
    in_file.close();out_file.close();
}

void del_biggest_word_fs(string &line) {
    int len = line.length();
    int cur_start_i=0,cur_end_i=len-1,max_length=-1,max_start_i,max_end_i;

    for (int i = 0; i < len; i++) {
        if (iswspace(line[i]) || line[i] == '.' && (!iswspace(line[i + 1]) && line[i + 1] != '.')) {
            cur_start_i = i + 1;
        }
        if (line[i] != ' ' && line[i] != '.' && (line[i + 1]=='\0'||line[i + 1] == ' ' || line[i + 1] == '.')) {
            cur_end_i = i;
            int length=cur_end_i - cur_start_i +1;
            if(length>max_length){
                max_start_i=cur_start_i;
                max_end_i=cur_end_i;
                max_length=length;
            }
        }
    }
    line.erase(max_start_i,max_length);
}

void replace_characters_fs(string &str){
    char ch=str[0];
    int pos = 1;
    while ((pos = str.find(ch, pos)) != string::npos) {
        str.replace(pos, 1, "*");
        pos += 1;
    };
}


// file pointers and c string functions

void create_file_in_mode_fp(char* filename,char* mode){

    FILE *fptr=fopen(filename,mode);
    if(!fptr){
        cerr<<"Error while working with file \"" << filename << "\"!\n";
    }

    char line[257];

    cout<<"Enter text (max line size is 256), enter \"*\" on a line by itself to stop\n";

    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '*' && line[1] == '\n') {
            break;
        }
        int line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0';
            line_len--;
        }
        fprintf(fptr,"%s\n",line);
    }

    fclose(fptr);
}

void create_file_fp(char* filename){
    void create_file_in_mode_fp(char* filename,char* mode);

    bool entered=false;
    string choice;
    do {
        if (choice == "Y" || choice == "y") {
            create_file_in_mode_fp(filename,(char*)"a");
        } else {
            if(!entered){
                create_file_in_mode_fp(filename,(char*)"w");
                entered= true;
            }
        }
        cout << "Do you want to add more text (y/n)" << endl;
        cin >> choice;
        cin.ignore();
    } while (choice == "Y" || choice == "y");
}

void output_file_fp(char* filename){
    FILE *fptr=fopen(filename,"r");
    char ch;

    if (fptr==NULL) {
        cerr<<"Error while working with a file!\n"<< endl;
        return;
    }

    cout<<"\n______"<< filename <<"'s contents:______\n";

    do {
        ch = fgetc(fptr);
        printf("%c", ch);
    } while (ch != EOF);

}

void new_file_from_old_fp(char* filename,char* new_filename){
    void replace_characters_fp(char*,int,int);
    FILE* in_file=fopen(filename,(char*)"r");
    FILE* new_out_file=fopen(new_filename,(char*)"w");

    if(in_file==NULL||new_out_file==NULL){
        cerr<<"Error while working with a file!\n"<< endl;
        return;
    }

    int count=0,ch;
    char line[256];
    bool is_odd=true;

    while (fgets(line, sizeof(line), in_file)){
        if (is_odd){
            //do some fun stuff with an odd line

            int len =strlen(line);
            int cur_start_i=0,cur_end_i=len-1;

            for (int i = 0; i < len; i++) {
                if (line[i]==' ' || line[i] == '.' && (line[i + 1]!=' ' && line[i + 1] != '.')) {
                    cur_start_i = i + 1;
                }
                if (line[i] != ' ' && line[i] != '.' && (line[i + 1]=='\n'||line[i + 1] == ' ' || line[i + 1] == '.')) {
                    cur_end_i = i;
                    int word_length=cur_end_i - cur_start_i +1;
                    replace_characters_fp(line,cur_start_i,cur_end_i);
                }
            }
            fprintf(new_out_file,"%s",line);
            strset(line,0);

        }
        count++;
        is_odd=!is_odd;
    }

    fclose(in_file);
    fclose(new_out_file);

};

void replace_characters_fp(char* line,int word_start,int word_end){
    char ch=line[word_start];

    for(int i=word_start+1;i<=word_end;i++){
        if(ch==line[i]){
            line[i]='*';
        }
    }
}

void modify_old_file_fp(char* filename){
    void copy_file_fp(char*, char*);
    void del_biggest_word_fp(char*);


    bool isEven = false;
    char line[257];

    FILE *in_file=fopen(filename,"r");
    FILE *copy=fopen("temp.txt","w");

    if(!in_file||!copy){
        cerr <<"Error while working with a file!" << endl;
    }

    while (fgets(line, sizeof(line), in_file)) {
        if (isEven) {
            del_biggest_word_fp(line);
        }
        fprintf(copy,"%s",line);
        isEven = !isEven;
    };
    fclose(copy);

    copy_file_fp((char*)"temp.txt",filename);
    fclose(in_file);

};

void del_biggest_word_fp(char* line){
    int len = strlen(line);
    int cur_start_i=0,cur_end_i=len-1,max_length=-1,max_start_i,max_end_i;

    for (int i = 0; i < len; i++) {
        if (line[i]==' ' || line[i] == '.' && (line[i + 1] !=' ' && line[i + 1] != '.')) {
            cur_start_i = i + 1;
        }
        if (line[i] != ' ' && line[i] != '.' && (line[i + 1]=='\0'||line[i + 1] == ' ' || line[i + 1] == '.')) {
            cur_end_i = i;
            int length=cur_end_i - cur_start_i +1;
            if(length>max_length){
                max_start_i=cur_start_i;
                max_end_i=cur_end_i;
                max_length=length;
            }
        }
    }
    strcpy(line + max_start_i, line + max_start_i + max_length);
}

void copy_file_fp(char* source, char* target){
    int ch;
    FILE *source_file = fopen(source,"r");
    FILE *target_file = fopen(target,"w");

    if(source_file==NULL||target_file==NULL){
        cerr <<"Error while working with a file!" << endl;
    }

    while ((ch=getc(source_file))!=EOF)putc(ch,target_file);
    fclose(source_file);fclose(target_file);
}