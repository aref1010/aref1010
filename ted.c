//Alireza Elmifard 402106207

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <windows.h>
#include <stdbool.h>

//prototypes
int run_init(int argc, char *argv[]);
int check_ted(int argc, char *argv[], char *ted_address);
int run_add(int argc, char *argv[] , char *ted_address);
int last_modify(char *filename , char *last_modify);
int add(char *ted_address , char *dir_name);
int check_staged_dir(char *ted_address , char *dir_name);
int run_config(int argc, char *argv[] , char *ted_address);
int run_reset(int argc, char *argv[] , char *ted_address);
int reset(char *ted_address , char *dir_name);


//functions
int run_init(int argc, char *argv[]){
    char first_address[1024] , tmp_first_address[1024];
    if (getcwd(first_address, sizeof(first_address)) == NULL) return 1;
    strcpy(tmp_first_address , first_address);
    //check exist
    if(!check_ted(argc , argv , first_address)){
        strcat(tmp_first_address , "\\.ted");
        int success = CreateDirectory(tmp_first_address , NULL);
        if (!success) return 1;
        DWORD attrubutes = GetFileAttributes(tmp_first_address);
        attrubutes |= FILE_ATTRIBUTE_HIDDEN;
        SetFileAttributes(tmp_first_address , attrubutes);
        if (chdir(tmp_first_address) != 0) return 1;
        FILE *fp = fopen("stage.txt" , "w");
        fclose(fp);
        fp = fopen("commit.txt" , "w");
        fclose(fp);
        fp = fopen("config.txt" , "w");
        fclose(fp);
        if (chdir("..") != 0) return 1;
        fprintf(stdout , "ted directory created successfully");
    }
    else {
        perror("ted directory already exists");
    }
    return 0;
}

int check_ted(int argc, char *argv[] , char *ted_address){
    char first_address[1024];
    if (getcwd(first_address, sizeof(first_address)) == NULL) return 1;
    //fin .ted
    char address[1024];
    int exists = 0;
    struct dirent *entry;
    do {
        // update current working directory
        if (getcwd(address, sizeof(address)) == NULL) return 1;
        
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".ted") == 0){
                exists = 1;
                char global_name[1024] , name[1024] , global_email[1024] , email[1024] , tmp[1024] , tmp2[100];
                strcpy(ted_address , address);
                strcpy(tmp , address);
                strcat(tmp , "\\.ted\\name.txt");
                if (last_modify(tmp , name) != 0) return 1;
                if (last_modify("C:\\Users\\alire\\TED\\name.txt" , global_name) != 0) return 1;
                int gy , gm , gd , gh , gmin , gs , y , m , d , h , min , s;
                sscanf(global_name , "%02d/%02d/%04d%02d:%02d:%02d" , &gd , &gm , &gy , &gh , &gmin , &gs);
                sscanf(name , "%02d/%02d/%04d%02d:%02d:%02d" , &d , &m , &y , &h , &min , &s);
                if(gy <= y){
                    if(gm <= m){
                        if(gd <= d){
                            if(gh <= h){
                                if(gmin <= min){
                                    if(gs > s){
                                        FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                                        int scan = fscanf(gname_address , "%s" , tmp2);
                                        fclose(gname_address);
                                        FILE *name_address = fopen(tmp , "w");
                                        fprintf(name_address , "%s" , tmp2);
                                        fclose(name_address);
                                    }
                                }
                                else {
                                    FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                                    int scan = fscanf(gname_address , "%s" , tmp2);
                                    fclose(gname_address);
                                    FILE *name_address = fopen(tmp , "w");
                                    fprintf(name_address , "%s" , tmp2);
                                    fclose(name_address);
                                }
                            }
                            else {
                                FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                                int scan = fscanf(gname_address , "%s" , tmp2);
                                fclose(gname_address);
                                FILE *name_address = fopen(tmp , "w");
                                fprintf(name_address , "%s" , tmp2);
                                fclose(name_address);
                            }
                        }
                        else {
                            FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                            int scan = fscanf(gname_address , "%s" , tmp2);
                            fclose(gname_address);
                            FILE *name_address = fopen(tmp , "w");
                            fprintf(name_address , "%s" , tmp2);
                            fclose(name_address);
                        }
                    }
                    else {
                        FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                        int scan = fscanf(gname_address , "%s" , tmp2);
                        fclose(gname_address);
                        FILE *name_address = fopen(tmp , "w");
                        fprintf(name_address , "%s" , tmp2);
                        fclose(name_address);
                    }
                }
                else {
                    FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                    int scan = fscanf(gname_address , "%s" , tmp2);
                    fclose(gname_address);
                    FILE *name_address = fopen(tmp , "w");
                    fprintf(name_address , "%s" , tmp2);
                    fclose(name_address);
                }
                strcpy(tmp , address);
                strcat(tmp , "\\.ted\\email.txt");
                if (last_modify(tmp , email) != 0) return 1;
                if (last_modify("C:\\Users\\alire\\TED\\email.txt" , global_email) != 0) return 1;
                sscanf(global_email , "%02d/%02d/%04d%02d:%02d:%02d" , &gd , &gm , &gy , &gh , &gmin , &gs);
                sscanf(email , "%02d/%02d/%04d%02d:%02d:%02d" , &d , &m , &y , &h , &min , &s);
                if(gy <= y){
                    if(gm <= m){
                        if(gd <= d){
                            if(gh <= h){
                                if(gmin <= min){
                                    if(gs > s){
                                        FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                                        int scan = fscanf(gemail_address , "%s" , tmp2);
                                        fclose(gemail_address);
                                        FILE *email_address = fopen(tmp , "w");
                                        fprintf(email_address , "%s" , tmp2);
                                        fclose(email_address);
                                    }
                                }
                                else {
                                    FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                                    int scan = fscanf(gemail_address , "%s" , tmp2);
                                    fclose(gemail_address);
                                    FILE *email_address = fopen(tmp , "w");
                                    fprintf(email_address , "%s" , tmp2);
                                    fclose(email_address);
                                }
                            }
                            else {
                                FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                                int scan = fscanf(gemail_address , "%s" , tmp2);
                                fclose(gemail_address);
                                FILE *email_address = fopen(tmp , "w");
                                fprintf(email_address , "%s" , tmp2);
                                fclose(email_address);
                            }
                        }
                        else {
                            FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                            int scan = fscanf(gemail_address , "%s" , tmp2);
                            fclose(gemail_address);
                            FILE *email_address = fopen(tmp , "w");
                            fprintf(email_address , "%s" , tmp2);
                            fclose(email_address);
                        }
                    }
                    else {
                        FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                        int scan = fscanf(gemail_address , "%s" , tmp2);
                        fclose(gemail_address);
                        FILE *email_address = fopen(tmp , "w");
                        fprintf(email_address , "%s" , tmp2);
                        fclose(email_address);
                    }
                }
                else {
                    FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                    int scan = fscanf(gemail_address , "%s" , tmp2);
                    fclose(gemail_address);
                    FILE *email_address = fopen(tmp , "w");
                    fprintf(email_address , "%s" , tmp2);
                    fclose(email_address);
                }
                break;
            }
        }
        closedir(dir);
        
        // change cwd to parent
        if (strcmp(address, "C:\\") != 0) {
            if (chdir("..") != 0) return 1;
        }

    } while (strcmp(address, "C:\\") != 0);
    // return to the initial cwd
    if (chdir(first_address) != 0) return 1;
    return exists;
}

int run_add(int argc, char *argv[] , char *ted_address){
    char first_address[1024] , tmp_first_address[1024] , tmp2[1024] , file_address[1024];
    if (getcwd(first_address, sizeof(first_address)) == NULL) return 1;
    struct dirent *entry;
    int j;
    if(strcmp(argv[2] , "-f") == 0){
        j = 3;
    }
    else if(strcmp(argv[2] , "-n") == 0){
        j = argc - 1;
    }
    else {
        j = 2;
    }
    for (int i = j; i < argc; i++){
        int exist_check = 0 , star_check , backslash = -1;
        strcpy(tmp_first_address , first_address);
        for(int k = strlen(argv[i])-1 ; k >=0 ; k--){
            if(argv[i][k] == '\\'){
                backslash = k;
                strcpy(file_address , argv[i]);
                strcpy(tmp2 , argv[i] + k + 1);
                argv[i][k] = '\0';
                break;
            }
        }
        DIR *dir;
        if(backslash == -1) {
            dir = opendir(".");
            strcpy(file_address , argv[i]);
        }
        else {
            dir = opendir(argv[i]);
            strcpy(argv[i] , tmp2);
        }
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if(strcmp(argv[2] , "-n") == 0){
                int stage_check = 0;
                char stage_address[1024] , last_add[1024] , lastmodify[1024];
                strcpy(stage_address, ted_address);
                strcat(stage_address , "\\.ted\\stage.txt");
                FILE *fp = fopen(stage_address , "r");
                if (entry->d_type == DT_DIR && strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , "..") != 0 && strcmp(entry->d_name , ".ted") != 0){
                    if(check_staged_dir(ted_address , entry->d_name) != 2){
                        printf("%s staged\n" , entry->d_name);
                    }
                    else {
                        printf("%s unstaged\n" , entry->d_name);
                    }
                }
                else {
                    while (1){
                        int scan = fscanf(fp , "%s" , last_add);
                        if (scan != EOF){
                            if(strcmp(last_add , entry->d_name) == 0){
                                if (last_modify(entry->d_name , lastmodify) != 0) return 1;
                                scan = fscanf(fp , "%s" , last_add);
                                if(strcmp(last_add , lastmodify) == 0){
                                    stage_check = 1;
                                    break;
                                }
                            }
                        }                    
                        else {
                            break;
                        }
                    }
                    if(stage_check && strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , "..") != 0 && strcmp(entry->d_name , ".ted") != 0){
                        printf("%s staged\n" , entry->d_name);
                    }
                    else if(strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , "..") != 0 && strcmp(entry->d_name , ".ted") != 0){
                        printf("%s unstaged\n" , entry->d_name);
                    }
                }
                fclose(fp);
            }
            else {
                if (entry->d_type == DT_DIR && strcmp(entry->d_name, argv[i]) == 0){
                    if (add(ted_address , entry->d_name) != 0) return 1;
                    exist_check = 1;
                }
                else if(strcmp(entry->d_name, argv[i]) == 0){
                    exist_check = 1;
                    char stage_address[1024];
                    strcpy(stage_address, ted_address);
                    strcat(stage_address , "\\.ted\\stage.txt");
                    FILE *fp = fopen(stage_address , "r+");
                    char last_add[1024] , lastmodify[1024] , tmp[1024];
                    int check = 0 , len = 0;
                    while (1){
                        int scan = fscanf(fp , "%s" , last_add);
                        if (scan != EOF){
                            if(strcmp(last_add , argv[i]) == 0){
                                if (last_modify(file_address , lastmodify) != 0) return 1;
                                scan = fscanf(fp , "%s" , last_add);
                                if(strcmp(last_add , lastmodify) != 0){
                                    sprintf(tmp , "%s %s" , entry->d_name , lastmodify);
                                    fseek(fp , len , SEEK_SET);
                                    fwrite(tmp , sizeof(char) , strlen(tmp) , fp);
                                    fprintf(stdout , "%s added successfuly\n" , entry->d_name);
                                }
                                else {
                                    fprintf(stdout , "%s is already added to stage\n" , entry->d_name);
                                }
                                check = 1;
                                break;
                            }
                        }                    
                        else {
                            break;
                        }
                        len += strlen(last_add) + 1;
                    }
                    if (!check){
                        if (last_modify(file_address , lastmodify) != 0) return 1;
                        fprintf(fp , "%s %s " , argv[i] , lastmodify);
                        fprintf(stdout , "%s added successfuly\n" , argv[i]);
                    }
                    fclose(fp);
                }
            }
        }
        if (!exist_check && strcmp(argv[2] , "-n") != 0){
            printf("this file or directory not exists\n");
        }
        closedir(dir);
    }
    return 0;
}

int last_modify(char *filename , char *last_modify) {
  // Define a WIN32_FIND_DATA structure.
    WIN32_FIND_DATAA fd;
    
  // Create a file handle.
    HANDLE hFind = FindFirstFileA(filename , &fd);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        return 1;
    }
    
  // Get the last write time.
    FILETIME ftLastWriteTime = fd.ftLastWriteTime;

  // Close the file handle.
    FindClose(hFind);

  // Convert the last write time to a readable format.
    SYSTEMTIME stLastWriteTime;
    FileTimeToSystemTime(&ftLastWriteTime, &stLastWriteTime);

  // Print the last write time.
    sprintf(last_modify , "%02d/%02d/%04d%02d:%02d:%02d",
        stLastWriteTime.wMonth, stLastWriteTime.wDay, stLastWriteTime.wYear,
        stLastWriteTime.wHour, stLastWriteTime.wMinute, stLastWriteTime.wSecond);

    return 0;
}

int add(char *ted_address , char *dir_name){
    char lastmodify[1024] , address[1024];
    struct dirent *subentry;
    DIR *subdir = opendir(dir_name);
    if (subdir == NULL) {
        perror("Error opening current directory");
        return 1;
    }
    while ((subentry = readdir(subdir)) != NULL) {
        if (subentry->d_type == DT_DIR && strcmp(subentry->d_name , ".") != 0 && strcmp(subentry->d_name , "..") != 0){
            sprintf(address , "%s\\%s" , dir_name , subentry->d_name);
            add(ted_address , address);
        }
        else if(strcmp(subentry->d_name , ".") != 0 && strcmp(subentry->d_name , "..") != 0){
            char stage_address[1024];
            strcpy(stage_address, ted_address);
            strcat(stage_address , "\\.ted\\stage.txt");
            FILE *fp = fopen(stage_address , "r+");
            char last_add[1024] , tmp[1024];
            int check = 0 , len = 0;
            while (1){
                int scan = fscanf(fp , "%s" , last_add);
                if (scan != EOF){
                    if(strcmp(last_add , subentry->d_name) == 0){
                        sprintf(address , "%s\\%s" , dir_name , subentry->d_name);
                        if (last_modify(address , lastmodify) != 0) return 1;
                        scan = fscanf(fp , "%s" , last_add);
                        if(strcmp(last_add , lastmodify) != 0){
                            sprintf(tmp , "%s %s" , subentry->d_name , lastmodify);
                            fseek(fp , len , SEEK_SET);
                            fwrite(tmp , sizeof(char) , strlen(tmp) , fp);
                            fprintf(stdout , "%s added successfuly\n" , subentry->d_name);
                        }
                        else {
                            fprintf(stdout , "%s is already added to stage\n" , subentry->d_name);
                        }
                        check = 1;
                        break;
                    }
                    len += strlen(last_add) + 1;
                }
                else {
                    break;
                }
            }
            if (!check){
                sprintf(address , "%s\\%s" , dir_name , subentry->d_name);
                if (last_modify(address , lastmodify) != 0) return 1;
                fprintf(fp , "%s %s " , subentry->d_name , lastmodify);
                fprintf(stdout , "%s added successfuly\n" , subentry->d_name);
            }
            fclose(fp);
        }
    }
    closedir(subdir);
    return 0;
}

int check_staged_dir(char *ted_address , char *dir_name){
    char lastmodify[1024] , address[1024];
    struct dirent *subentry;
    DIR *subdir = opendir(dir_name);
    if (subdir == NULL) {
        perror("Error opening current directory");
        return 1;
    }
    while ((subentry = readdir(subdir)) != NULL) {
        if (subentry->d_type == DT_DIR && strcmp(subentry->d_name , ".") != 0 && strcmp(subentry->d_name , "..") != 0){
            sprintf(address , "%s\\%s" , dir_name , subentry->d_name);
            check_staged_dir(ted_address , address);
        }
        else if(strcmp(subentry->d_name , ".") != 0 && strcmp(subentry->d_name , "..") != 0){
            char stage_address[1024];
            strcpy(stage_address, ted_address);
            strcat(stage_address , "\\.ted\\stage.txt");
            FILE *fp = fopen(stage_address , "r+");
            char last_add[1024] , tmp[1024];
            int check = 0 , len = 0;
            while (1){
                int scan = fscanf(fp , "%s" , last_add);
                if (scan != EOF){
                    if(strcmp(last_add , subentry->d_name) == 0){
                        sprintf(address , "%s\\%s" , dir_name , subentry->d_name);
                        if (last_modify(address , lastmodify) != 0) return 1;
                        scan = fscanf(fp , "%s" , last_add);
                        if(strcmp(last_add , lastmodify) != 0){
                            return 2;
                        }
                        check = 1;
                        break;
                    }
                    len += strlen(last_add) + 1;
                }
                else {
                    break;
                }
            }
            if (!check){
                return 2;
            }
            fclose(fp);
        }
    }
    closedir(subdir);
    return 0;
}

int run_config(int argc, char *argv[] , char *ted_address){
    char address[1024];
    if(strcmp(argv[2] , "-global") == 0 && strcmp(argv[3] , "user.name") == 0){
        FILE *name = fopen("C:\\Users\\alire\\TED\\name.txt" , "w");
        fprintf(name , "%s" , argv[4]);
        fclose(name);
    }
    else if(strcmp(argv[2] , "-global") == 0 && strcmp(argv[3] , "user.email") == 0){
        FILE *email = fopen("C:\\Users\\alire\\TED\\email.txt" , "w");
        fprintf(email , "%s" , argv[4]);
        fclose(email);
    }
    else if(strcmp(argv[2] , "user.email") == 0){
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\email.txt");
        FILE *email = fopen(address , "w");
        fprintf(email , "%s" , argv[3]);
        fclose(email);
    }
    else if(strcmp(argv[2] , "user.name") == 0){
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\name.txt");
        FILE *name = fopen(address , "w");
        fprintf(name , "%s" , argv[3]);
        fclose(name);
    }
    printf("information is changed successfuly");
}

int run_reset(int argc, char *argv[] , char *ted_address){
    char first_address[1024] , tmp_first_address[1024] , tmp2[1024] , file_address[1024];
    if (getcwd(first_address, sizeof(first_address)) == NULL) return 1;
    struct dirent *entry;
    int j;
    if(strcmp(argv[2] , "-f") == 0){
        j = 3;
    }
    else {
        j = 2;
    }
    for (int i = j; i < argc; i++){
        int exist_check = 0 , star_check , backslash = -1;
        strcpy(tmp_first_address , first_address);
        for(int k = strlen(argv[i])-1 ; k >=0 ; k--){
            if(argv[i][k] == '\\'){
                backslash = k;
                strcpy(file_address , argv[i]);
                strcpy(tmp2 , argv[i] + k + 1);
                argv[i][k] = '\0';
                break;
            }
        }
        DIR *dir;
        if(backslash == -1) {
            dir = opendir(".");
            strcpy(file_address , argv[i]);
        }
        else {
            dir = opendir(argv[i]);
            strcpy(argv[i] , tmp2);
        }
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if(strcmp(argv[2] , "-n") == 0){
                int stage_check = 0;
                char stage_address[1024] , last_add[1024] , lastmodify[1024];
                strcpy(stage_address, ted_address);
                strcat(stage_address , "\\.ted\\stage.txt");
                FILE *fp = fopen(stage_address , "r");
                if (entry->d_type == DT_DIR && strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , "..") != 0 && strcmp(entry->d_name , ".ted") != 0){
                    if(check_staged_dir(ted_address , entry->d_name) != 2){
                        printf("%s staged\n" , entry->d_name);
                    }
                    else {
                        printf("%s unstaged\n" , entry->d_name);
                    }
                }
                else {
                    while (1){
                        int scan = fscanf(fp , "%s" , last_add);
                        if (scan != EOF){
                            if(strcmp(last_add , entry->d_name) == 0){
                                if (last_modify(entry->d_name , lastmodify) != 0) return 1;
                                scan = fscanf(fp , "%s" , last_add);
                                if(strcmp(last_add , lastmodify) == 0){
                                    stage_check = 1;
                                    break;
                                }
                            }
                        }                    
                        else {
                            break;
                        }
                    }
                    if(stage_check && strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , "..") != 0 && strcmp(entry->d_name , ".ted") != 0){
                        printf("%s staged\n" , entry->d_name);
                    }
                    else if(strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , "..") != 0 && strcmp(entry->d_name , ".ted") != 0){
                        printf("%s unstaged\n" , entry->d_name);
                    }
                }
                fclose(fp);
            }
            else {
                if (entry->d_type == DT_DIR && strcmp(entry->d_name, argv[i]) == 0){
                    if (reset(ted_address , entry->d_name) != 0) return 1;
                    exist_check = 1;
                }
                else if(strcmp(entry->d_name, argv[i]) == 0){
                    exist_check = 1;
                    char stage_address[1024];
                    strcpy(stage_address, ted_address);
                    strcat(stage_address , "\\.ted\\stage.txt");
                    FILE *fp = fopen(stage_address , "r+");
                    char last_add[1024] , lastmodify[1024] , tmp[1024];
                    int check = 0 , len = 0 , line_len = 0;
                    while (1){
                        line_len = 0;
                        int scan = fscanf(fp , "%s" , last_add);
                        line_len += strlen(last_add) + 1;
                        if (scan != EOF){
                            if(strcmp(last_add , argv[i]) == 0){
                                if (last_modify(file_address , lastmodify) != 0) return 1;
                                scan = fscanf(fp , "%s" , last_add);
                                line_len += strlen(last_add);
                                if(strcmp(last_add , lastmodify) != 0){
                                    fprintf(stdout , "%s is unstaged\n" , argv[i]);
                                }
                                else {
                                    fseek(fp , len*sizeof(char) , SEEK_SET);
                                    for(int k  = 0 ; k < line_len ; k++){
                                        fwrite("a" , 1 , 1 , fp);
                                    }
                                    printf("%s changed to unstaged\n" , argv[i]);
                                }
                                check = 1;
                                break;
                            }
                        }                    
                        else {
                            break;
                        }
                        len += strlen(last_add) + 1;
                    }
                    if (!check){
                        fprintf(stdout , "%s is unstaged\n" , argv[i]);
                    }
                    fclose(fp);
                }
            }
        }
        if (!exist_check && strcmp(argv[2] , "-n") != 0){
            printf("this file or directory not exists\n");
        }
        closedir(dir);
    }
    return 0;
}

int reset(char *ted_address , char *dir_name){
    char lastmodify[1024] , address[1024];
    struct dirent *subentry;
    DIR *subdir = opendir(dir_name);
    if (subdir == NULL) {
        perror("Error opening current directory");
        return 1;
    }
    while ((subentry = readdir(subdir)) != NULL) {
        if (subentry->d_type == DT_DIR && strcmp(subentry->d_name , ".") != 0 && strcmp(subentry->d_name , "..") != 0){
            sprintf(address , "%s\\%s" , dir_name , subentry->d_name);
            reset(ted_address , address);
        }
        else if(strcmp(subentry->d_name , ".") != 0 && strcmp(subentry->d_name , "..") != 0){
            char stage_address[1024];
            strcpy(stage_address, ted_address);
            strcat(stage_address , "\\.ted\\stage.txt");
            FILE *fp = fopen(stage_address , "r+");
            char last_add[1024] , tmp[1024];
            int check = 0 , len = 0 , line_len = 0;
            while (1){
                line_len = 0;
                int scan = fscanf(fp , "%s" , last_add);
                line_len += strlen(last_add) + 1;
                if (scan != EOF){
                    if(strcmp(last_add , subentry->d_name) == 0){
                        sprintf(address , "%s\\%s" , dir_name , subentry->d_name);
                        if (last_modify(address , lastmodify) != 0) return 1;
                        scan = fscanf(fp , "%s" , last_add);
                        line_len += strlen(last_add);
                        if(strcmp(last_add , lastmodify) != 0){
                            fprintf(stdout , "%s is unstaged\n" , subentry->d_name);
                        }
                        else {
                            fseek(fp , len*sizeof(char) , SEEK_SET);
                            for(int k = 0; k < line_len ; k++){
                                fwrite("a" , 1 , 1 , fp);
                            }
                            printf("%s changed to unstaged\n" , subentry->d_name);
                        }
                        check = 1;
                        break;
                    }
                    len += strlen(last_add) + 1;
                }
                else {
                    break;
                }
            }
            if (!check){
                fprintf(stdout , "%s is unstaged\n" , subentry->d_name);
            }
            fclose(fp);
        }
    }
    closedir(subdir);
    return 0;
}


//main
int main(int argc, char *argv[]){
    char ted_address[1024];
    if(argc < 2){
        printf("Invalid input!");
        return 0;
    }
    else if(strcmp(argv[1] , "init") == 0){
        return run_init(argc , argv);
    }
    else if(strcmp(argv[1] , "add") == 0){
        if(argc < 3){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return run_add(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
    else if(strcmp(argv[1] , "config") == 0){
        if(argc < 4){
            printf("Invalid input!");
            return 0;
        }
        else if(strcmp(argv[2] , "-global") != 0){
            if(check_ted(argc , argv , ted_address)){
                return run_config(argc , argv , ted_address);
            }
            else {
                printf("There is no repository");
            }
        }
        else {
            return run_config(argc , argv , ted_address);
        }
    }
    else if(strcmp(argv[1] , "reset") == 0){
        if(argc < 3){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return run_reset(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
}