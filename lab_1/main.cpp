#include <iostream>
#include "lab1.h"
#include <string.h>

int main(int argc, char* argv[])
{
    string filename_fs = "test.txt";
    string new_filename_fs = "test1.txt";
    char* filename_fp = "test.txt";
    char* new_filename_fp = "test1.txt";

    if (argc<3){
        cerr << "Specify the mode ( -mode fp or -mode fs )\n" << endl;
        return 1;
    }

    if(!strcmp(argv[2],"fp")){

        create_file_fp(filename_fp); // створення файлу
        output_file_fp(filename_fp); // відображення вмісту

        new_file_from_old_fp(filename_fp,new_filename_fp); // створення нового файлу на основі старого
        output_file_fp(new_filename_fp); // відображення вмісту створеного файлу

        modify_old_file_fp(filename_fp); //зміна вмісту старого файлу
        output_file_fp(filename_fp); //відображення вмісту зміненого файлу

    } else if(!strcmp(argv[2],"fs")){

        create_file_fs(filename_fs); // створення файлу
        output_file_fs(filename_fs); // відображення вмісту

        new_file_from_old_fs(filename_fs,new_filename_fs); // створення нового файлу на основі старого
        output_file_fs(new_filename_fs); // відображення вмісту створеного файлу

        modify_old_file_fs(filename_fs); //зміна вмісту старого файлу
        output_file_fs(filename_fs); //відображення вмісту зміненого файлу
    }
    return 0;
}