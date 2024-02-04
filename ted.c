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
int run_commit(int argc, char *argv[] , char *ted_address);
int run_set(int argc, char *argv[] , char *ted_address);
int shortcut_function(int argc, char *argv[] , char *ted_address);
int run_status(int argc, char *argv[] , char *ted_address , char *dir_name);
int run_log(int argc , char *argv[] , char *ted_address);


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
        fp = fopen("name.txt" , "w");
        fclose(fp);
        fp = fopen("email.txt" , "w");
        fclose(fp);
        fp = fopen("id.txt" , "w");
        fprintf(fp , "0");
        fclose(fp);
        fp = fopen("current_branch.txt" , "w");
        fprintf(fp , "master");
        fclose(fp);
        fp = fopen("shortcuts.txt" , "w");
        fclose(fp);
        fp = fopen("last_add.txt" , "w");
        fclose(fp);
        fp = fopen("tmp.txt" , "w");
        fclose(fp);
        fp = fopen("branches.txt" , "w");
        fprintf(fp , "master ");
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
                sscanf(global_name , "%02d/%02d/%04d%02d:%02d:%02d" , &gm , &gd , &gy , &gh , &gmin , &gs);
                sscanf(name , "%02d/%02d/%04d%02d:%02d:%02d" , &m , &d , &y , &h , &min , &s);
                if(gy == y){
                    if(gm == m){
                        if(gd == d){
                            if(gh == h){
                                if(gmin == min){
                                    if(gs > s){
                                        FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                                        int scan = fscanf(gname_address , "%s" , tmp2);
                                        fclose(gname_address);
                                        FILE *name_address = fopen(tmp , "w");
                                        fprintf(name_address , "%s" , tmp2);
                                        fclose(name_address);
                                    }
                                }
                                else if (gmin > min){
                                    FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                                    int scan = fscanf(gname_address , "%s" , tmp2);
                                    fclose(gname_address);
                                    FILE *name_address = fopen(tmp , "w");
                                    fprintf(name_address , "%s" , tmp2);
                                    fclose(name_address);
                                }
                            }
                            else if(gh > h){
                                FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                                int scan = fscanf(gname_address , "%s" , tmp2);
                                fclose(gname_address);
                                FILE *name_address = fopen(tmp , "w");
                                fprintf(name_address , "%s" , tmp2);
                                fclose(name_address);
                            }
                        }
                        else if(gd > d){
                            FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                            int scan = fscanf(gname_address , "%s" , tmp2);
                            fclose(gname_address);
                            FILE *name_address = fopen(tmp , "w");
                            fprintf(name_address , "%s" , tmp2);
                            fclose(name_address);
                        }
                    }
                    else if(gm > m){
                        FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                        int scan = fscanf(gname_address , "%s" , tmp2);
                        fclose(gname_address);
                        FILE *name_address = fopen(tmp , "w");
                        fprintf(name_address , "%s" , tmp2);
                        fclose(name_address);
                    }
                }
                else if(gy > y){
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
                sscanf(global_email , "%02d/%02d/%04d%02d:%02d:%02d" , &gm , &gd , &gy , &gh , &gmin , &gs);
                sscanf(email , "%02d/%02d/%04d%02d:%02d:%02d" , &m , &d , &y , &h , &min , &s);
                if(gy == y){
                    if(gm == m){
                        if(gd == d){
                            if(gh == h){
                                if(gmin == min){
                                    if(gs > s){
                                        FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                                        int scan = fscanf(gemail_address , "%s" , tmp2);
                                        fclose(gemail_address);
                                        FILE *email_address = fopen(tmp , "w");
                                        fprintf(email_address , "%s" , tmp2);
                                        fclose(email_address);
                                    }
                                }
                                else if(gmin > min){
                                    FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                                    int scan = fscanf(gemail_address , "%s" , tmp2);
                                    fclose(gemail_address);
                                    FILE *email_address = fopen(tmp , "w");
                                    fprintf(email_address , "%s" , tmp2);
                                    fclose(email_address);
                                }
                            }
                            else if(gh > h){
                                FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                                int scan = fscanf(gemail_address , "%s" , tmp2);
                                fclose(gemail_address);
                                FILE *email_address = fopen(tmp , "w");
                                fprintf(email_address , "%s" , tmp2);
                                fclose(email_address);
                            }
                        }
                        else if(gd > d){
                            FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                            int scan = fscanf(gemail_address , "%s" , tmp2);
                            fclose(gemail_address);
                            FILE *email_address = fopen(tmp , "w");
                            fprintf(email_address , "%s" , tmp2);
                            fclose(email_address);
                        }
                    }
                    else if(gm > m){
                        FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                        int scan = fscanf(gemail_address , "%s" , tmp2);
                        fclose(gemail_address);
                        FILE *email_address = fopen(tmp , "w");
                        fprintf(email_address , "%s" , tmp2);
                        fclose(email_address);
                    }
                }
                else if(gy > y){
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
    char first_address[1024] , tmp_first_address[1024] , tmp2[1024] , file_address[1024] , last_add_address[1024];
    strcpy(last_add_address , ted_address);
    strcat(last_add_address , "\\.ted\\last_add.txt");
    FILE *last_add = fopen(last_add_address , "w");
    fclose(last_add);
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
                                stage_check = 1;
                                //if (last_modify(entry->d_name , lastmodify) != 0) return 1;
                                //scan = fscanf(fp , "%s" , last_add);
                                //if(strcmp(last_add , lastmodify) == 0){
                                  //  stage_check = 1;
                                    //break;
                                //}
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
                                    FILE *last_add = fopen(last_add_address , "a");
                                    fprintf(last_add , "%s\n" , entry->d_name);
                                    fclose(last_add);
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
                        FILE *last_add = fopen(last_add_address , "a");
                        fprintf(last_add , "%s\n" , argv[i]);
                        fclose(last_add);
                    }
                    fclose(fp);
                }
            }
        }
        if (!exist_check && strcmp(argv[2] , "-n") != 0){
            printf("%s not exists\n" , argv[i]);
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
    char lastmodify[1024] , address[1024] , last_add_address[1024];
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
                            strcpy(last_add_address , ted_address);
                            strcat(last_add_address , "\\.ted\\last_add.txt");
                            FILE *last_add = fopen(last_add_address , "a");
                            fprintf(last_add , "%s\n" , subentry->d_name);
                            fclose(last_add);
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
                strcpy(last_add_address , ted_address);
                strcat(last_add_address , "\\.ted\\last_add.txt");
                FILE *last_add = fopen(last_add_address , "a");
                fprintf(last_add , "%s\n" , subentry->d_name);
                fclose(last_add);
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
                        // if(strcmp(last_add , lastmodify) != 0){
                        //     return 2;
                        // }
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
    char first_address[1024] , tmp_first_address[1024] , tmp2[1024] , file_address[1024] , last_add_address[1024];;
    strcpy(last_add_address , ted_address);
    strcat(last_add_address , "\\.ted\\last_add.txt");
    if (getcwd(first_address, sizeof(first_address)) == NULL) return 1;
    struct dirent *entry;
    int j;
    if(strcmp(argv[2] , "-f") == 0){
        j = 3;
    }
    else if(strcmp(argv[2] , "-undo") == 0){
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
            if(strcmp(argv[2] , "-undo") == 0){
                exist_check = 1;
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
                                fseek(fp , len*sizeof(char) , SEEK_SET);
                                for(int k  = 0 ; k < line_len ; k++){
                                    fwrite("a" , 1 , 1 , fp);
                                }
                                printf("%s changed to unstaged\n" , argv[i]);
                                // if(strcmp(last_add , lastmodify) != 0){
                                //     fprintf(stdout , "%s is unstaged\n" , argv[i]);
                                // }
                                // else {
                                //     fseek(fp , len*sizeof(char) , SEEK_SET);
                                //     for(int k  = 0 ; k < line_len ; k++){
                                //         fwrite("a" , 1 , 1 , fp);
                                //     }
                                //     printf("%s changed to unstaged\n" , argv[i]);
                                // }
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
        if (!exist_check && strcmp(argv[2] , "-undo") != 0){
            printf("this file or directory not exists\n");
        }
        else if(strcmp(argv[2] , "-undo") == 0){
            FILE *last_add = fopen(last_add_address , "r");
            while (1){
                int scan = fscanf(last_add , "%s" , last_add_address);
                if (scan != EOF){
                    printf("%s\n" , last_add_address);
                }                    
                else {
                    break;
                }
            }
            fclose(last_add);
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
                        fseek(fp , len*sizeof(char) , SEEK_SET);
                        for(int k = 0; k < line_len ; k++){
                            fwrite("a" , 1 , 1 , fp);
                        }
                        printf("%s changed to unstaged\n" , subentry->d_name);
                        // if(strcmp(last_add , lastmodify) != 0){
                        //     fprintf(stdout , "%s is unstaged\n" , subentry->d_name);
                        // }
                        // else {
                        //     fseek(fp , len*sizeof(char) , SEEK_SET);
                        //     for(int k = 0; k < line_len ; k++){
                        //         fwrite("a" , 1 , 1 , fp);
                        //     }
                        //     printf("%s changed to unstaged\n" , subentry->d_name);
                        // }
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

int run_commit(int argc, char *argv[] , char *ted_address){
    if(argc > 4){
        printf("commit message is invalid");
        return 0;
    }
    else if(strlen(argv[3]) > 72){
        printf("commit message is too large");
    }
    else {
        char tmp[1024], commit_value[10000], shortcuts_value[1024] , file_address[1024] , stage_value[10000] , date[1024] , username[1024] , current_branch[1024];
        int commit_number = 0 , id_value , check = 0 , check2 = 0 , check3 = 0;
        if(strcmp(argv[2] , "-s") == 0){
            strcpy(file_address , ted_address);
            strcat(file_address , "\\.ted\\shortcuts.txt");
            FILE *shortcuts = fopen(file_address , "r");
            while(1){
                int scan = fscanf(shortcuts , "%s" , tmp);
                if (scan != EOF){
                    if(strcmp(tmp , argv[3]) == 0){
                        scan = fscanf(shortcuts , "%s" , tmp);
                        strcpy(argv[3] , tmp);
                        while(1){
                            scan = fscanf(shortcuts , "%s" , tmp);
                            if(strcmp(tmp , "tedpatern") == 0){
                                break;
                            }
                            else {
                                strcat(argv[3] , " ");
                                strcat(argv[3] , tmp);
                            }
                        }
                        check3 = 1;
                        break;
                    }
                }
                else {
                    break;
                }
            }
            if(!check3){
                printf("this shortcut is not exists");
            }
        }
        if((strcmp(argv[2] , "-s") == 0 && check3) || strcmp(argv[2] , "-s") != 0){
            strcpy(file_address , ted_address);
            strcat(file_address , "\\.ted\\stage.txt");
            FILE *stage = fopen(file_address , "r");
            while(1){
                int scan = fscanf(stage , "%s" , tmp);
                if (scan != EOF){
                    if((tmp[0] != 'a' || tmp[1] != 'a' || tmp[2] != 'a')){
                        if(check){
                            strcat(stage_value , tmp);
                        }
                        else {
                            strcpy(stage_value , tmp);
                        }
                        strcat(stage_value , " ");
                        commit_number ++;
                        check = 1;
                    }
                }
                else {
                    if(!check){
                        printf("stage is empty");
                        return 1;
                    }
                    break;
                }
            }
            fclose(stage);
            stage = fopen(file_address , "w");
            if (last_modify(file_address , date) != 0) return 1;
            fclose(stage);
            strcpy(file_address , ted_address);
            strcat(file_address , "\\.ted\\id.txt");
            FILE *id = fopen(file_address , "r");
            if (fscanf(id , "%d" , &id_value) == EOF) return 1;
            fclose(id);
            id_value ++;
            id = fopen(file_address , "w");
            fprintf(id , "%d" , id_value);
            fclose(id);
            strcpy(file_address , ted_address);
            strcat(file_address , "\\.ted\\name.txt");
            FILE *name = fopen(file_address , "r");
            if (fscanf(name , "%s" , username) == EOF) return 1;
            fclose(name);
            strcpy(file_address , ted_address);
            strcat(file_address , "\\.ted\\current_branch.txt");
            FILE *branch = fopen(file_address , "r");
            if (fscanf(branch , "%s" , current_branch) == EOF) return 1;
            fclose(branch);
            strcpy(file_address , ted_address);
            strcat(file_address , "\\.ted\\commit.txt");
            FILE *commit = fopen(file_address , "r");
            while(1){
                int scan = fscanf(commit , "%s" , tmp);
                if (scan != EOF){
                    if((tmp[0] != 'a' || tmp[0] != 'a' || tmp[0] != 'a')){
                        if(check2){
                            strcat(commit_value , tmp);
                        }
                        else {
                            strcpy(commit_value , tmp);
                        }
                        strcat(commit_value , " ");
                        check2 = 1;
                    }
                }
                else {
                    break;
                }
            }
            fclose(commit);
            fopen(file_address , "w");
            fclose(commit);
            strcpy(file_address , ted_address);
            strcat(file_address , "\\.ted\\commit.txt");
            commit = fopen(file_address , "a");
            char *token = strtok(stage_value , " ");
            while (token != NULL){
                fprintf(commit , "%s " , token);
                token = strtok(NULL , " ");
                fprintf(commit , "%s " , token);
                token = strtok(NULL , " ");
            }
            fprintf(commit , "information: %s %s $ %s %d %s %d " , date , argv[3] , username , id_value , current_branch , commit_number/2);
            fprintf(commit , "%s" , commit_value);
            fclose(commit);
            printf("commit %s added successfuly at %s with %d id" , argv[3] , date , id_value);
        }
    }
}

int run_set(int argc, char *argv[] , char *ted_address){
    char file_address[1024];
    strcpy(file_address , ted_address);
    strcat(file_address , "\\.ted\\shortcuts.txt");
    FILE *shortcuts = fopen(file_address , "a");
    fprintf(shortcuts , "%s %s tedpatern " , argv[5] , argv[3]);
    fclose(shortcuts);
}

int shortcut_function(int argc, char *argv[] , char *ted_address){
    char file_address[1024] , tmp[1024];
    int len = 0 , check = 0 , line_len = 0;
    strcpy(file_address , ted_address);
    strcat(file_address , "\\.ted\\shortcuts.txt");
    FILE *shortcuts = fopen(file_address , "r+");
    while(1){
        int scan = fscanf(shortcuts , "%s" , tmp);
        if (scan != EOF){
            if (strcmp(argv[argc-1] , tmp) == 0){
                line_len += strlen(argv[argc-1]) + 1;
                while(strcmp(tmp , "tedpatern") != 0){
                    scan = fscanf(shortcuts , "%s" , tmp);
                    line_len += strlen(tmp) + 1;
                }
                fseek(shortcuts , len*sizeof(char) , SEEK_SET);
                for(int i = 0; i < line_len - 1; i++){
                    fwrite("a" , sizeof(char) , 1 , shortcuts);
                }
                if(strcmp(argv[1] , "replace") == 0){
                    fclose(shortcuts);
                    shortcuts = fopen(file_address , "a");
                    fprintf(shortcuts , "%s %s tedpatern " , argv[argc-1] , argv[3]);
                    printf("shortcut replace successfuly");
                }
                else {
                    printf("shortcut remove successfuly");
                }
                check = 1;
                break;
            }
            len += strlen(tmp) + 1;
        }
        else {
            break;
        }
    }
    if (!check){
        printf("this shortcut is not exists");
    }
    fclose(shortcuts);
}

int run_status(int argc, char *argv[] , char *ted_address , char *dir_name){
    char lastmodify[1024] , address[1024] , address2[1024] , address3[1024] , last_add_address[1024];
    FILE *file_name;
    struct dirent *subentry;
    DIR *subdir = opendir(dir_name);
    if (subdir == NULL) {
        perror("Error opening current directory");
        return 1;
    }
    while ((subentry = readdir(subdir)) != NULL) {
        int stage_check = 0;
        if(subentry->d_type != DT_DIR){
            printf("%s " , subentry->d_name);
            strcpy(address2 , ted_address);
            strcat(address2 , "\\.ted\\tmp.txt");
            file_name = fopen(address2 , "a");
            fprintf(file_name , "%s " , subentry->d_name);
            fclose(file_name);
            char stage_address[1024];
            strcpy(stage_address, ted_address);
            strcat(stage_address , "\\.ted\\stage.txt");
            FILE *fp = fopen(stage_address , "r+");
            char last_add[1024] , tmp[1024];
            while (1){
                int scan = fscanf(fp , "%s" , last_add);
                if (scan != EOF){
                    if(strcmp(last_add , subentry->d_name) == 0){
                        stage_check = 1;
                        sprintf(address , "%s\\%s" , dir_name , subentry->d_name);
                        if (last_modify(address , lastmodify) != 0) return 1;
                        scan = fscanf(fp , "%s" , last_add);
                        if(strcmp(last_add , lastmodify) != 0){
                            printf("+M\n");
                        }
                        else {
                            printf("+C\n");
                        }
                        break;
                    }
                }
                else {
                    break;
                }
            }
            fclose(fp);
            strcpy(stage_address, ted_address);
            strcat(stage_address , "\\.ted\\commit.txt");
            fp = fopen(stage_address , "r+");
            while(!stage_check){
                int scan = fscanf(fp , "%s" , last_add);
                if (scan != EOF){
                    if(strcmp(last_add , subentry->d_name) == 0){
                        stage_check = 1;
                        sprintf(address , "%s\\%s" , dir_name , subentry->d_name);
                        if (last_modify(address , lastmodify) != 0) return 1;
                        scan = fscanf(fp , "%s" , last_add);
                        if(strcmp(last_add , lastmodify) != 0){
                            printf("-M\n");
                        }
                        else {
                            printf("-C\n");
                        }
                        break;
                    }
                }
                else {
                    break;
                }
            }
            fclose(fp);
            if(!stage_check){
                printf("-A\n");
            }
        }
        else if(strcmp(subentry->d_name , ".") != 0 && strcmp(subentry->d_name , "..") != 0 && strcmp(subentry->d_name , ".ted") != 0){
            sprintf(address , "%s\\%s" , dir_name , subentry->d_name);
            run_status(argc , argv , ted_address , address);
        }
    }
    closedir(subdir);
    char stage_address[1024] , commit_address[1024];
    strcpy(stage_address, ted_address);
    strcat(stage_address , "\\.ted\\stage.txt");
    FILE *fp = fopen(stage_address , "r+");
    char last_add[1024] , last_add2[1024] , tmp[1024] , tmp2[10000];
    int exist_check = 0;
    strcpy(address2 , ted_address);
    strcat(address2 , "\\.ted\\tmp.txt");
    while (1){
        exist_check = 0;
        int scan = fscanf(fp , "%s" , last_add);
        if (scan != EOF){
            file_name = fopen(address2 , "a+");
            int scan2 = fscanf(file_name , "%s" , tmp2);
            while (scan2 != EOF){
                if (strcmp(tmp2 , last_add) == 0){
                    exist_check = 1;
                }
                scan2 = fscanf(file_name , "%s" , tmp2);
            }
            fclose(file_name);
            if(!exist_check && last_add[2] != '/'){
                file_name = fopen(address2 , "a");
                printf("%s +D\n" , last_add);
                fprintf(file_name , "%s " , last_add);
                fclose(file_name);
            }
        }
        else {
            break;
        }
    }
    fclose(fp);
    strcpy(commit_address, ted_address);
    strcat(commit_address , "\\.ted\\commit.txt");
    fp = fopen(commit_address , "r+");
    int stage_check = 0;
    while (1){
        exist_check = 0;
        stage_check = 0;
        int scan = fscanf(fp , "%s" , last_add);
        if (scan != EOF){
            file_name = fopen(address2 , "a+");
            int scan2 = fscanf(file_name , "%s" , tmp2);
            while (scan2 != EOF){
                if (strcmp(tmp2 , last_add) == 0){
                    exist_check = 1;
                }
                scan2 = fscanf(file_name , "%s" , tmp2);
            }
            fclose(file_name);
            if(!exist_check && last_add[2] != '/'  && (last_add[0] > '9' || last_add[0] < '1') && (last_add[0] != 'a' || last_add[1] != 'a' || last_add[2] != 'a')){
                strcpy(last_add2 , last_add);
                scan = fscanf(fp , "%s" , last_add);
                if(last_add[2] == '/' && strcmp(last_add2 , "information:") != 0){
                    file_name = fopen(address2 , "a");
                    printf("%s -D\n" , last_add2);
                    fprintf(file_name , "%s " , last_add2);
                    fclose(file_name);
                }
            }
        }
        else {
            break;
        }
    }
    fclose(fp);
    fclose(file_name);
    return 0;
}

int run_log(int argc , char *argv[] , char *ted_address){
    char address[1024] , tmp[1024] , statement[10000];
    strcpy(address , ted_address);
    strcat(address , "\\.ted\\commit.txt");
    FILE *commit = fopen(address , "r");
    if(argc == 2){
        int scan = fscanf(commit , "%s" , tmp);
        while(scan != EOF){
            if(strcmp(tmp , "information:") == 0){
                scan = fscanf(commit , "%s" , tmp);
                printf("%s " , tmp);
                scan = fscanf(commit , "%s" , tmp);
                printf("\"%s" , tmp);
                scan = fscanf(commit , "%s" , tmp);
                while(strcmp(tmp , "$") != 0){
                    printf(" %s" , tmp);
                    scan = fscanf(commit , "%s" , tmp);
                }
                printf("\" ");
                scan = fscanf(commit , "%s" , tmp);
                printf("%s " , tmp);
                scan = fscanf(commit , "%s" , tmp);
                printf("%s " , tmp);
                scan = fscanf(commit , "%s" , tmp);
                printf("%s " , tmp);
                scan = fscanf(commit , "%s" , tmp);
                printf("%s \n" , tmp);
            }
            scan = fscanf(commit , "%s" , tmp);
        }
    }
    else if(strcmp(argv[2] , "-n") == 0){
        int n = 0 , main_n;
        sscanf(argv[3] , "%d" , &main_n);
        int scan = fscanf(commit , "%s" , tmp);
        while(n < main_n){
            if(strcmp(tmp , "information:") == 0){
                n ++;
                scan = fscanf(commit , "%s" , tmp);
                printf("%s " , tmp);
                scan = fscanf(commit , "%s" , tmp);
                printf("\"%s" , tmp);
                scan = fscanf(commit , "%s" , tmp);
                while(strcmp(tmp , "$") != 0){
                    printf(" %s" , tmp);
                    scan = fscanf(commit , "%s" , tmp);
                }
                printf("\" ");
                scan = fscanf(commit , "%s" , tmp);
                printf("%s " , tmp);
                scan = fscanf(commit , "%s" , tmp);
                printf("%s " , tmp);
                scan = fscanf(commit , "%s" , tmp);
                printf("%s " , tmp);
                scan = fscanf(commit , "%s" , tmp);
                printf("%s \n" , tmp);
            }
            scan = fscanf(commit , "%s" , tmp);
        }
    }
    else if(strcmp(argv[2] , "-branch") == 0){
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\branches.txt");
        FILE *branches = fopen(address , "r");
        int check = 0;
        int scan2 = fscanf(branches , "%s" , tmp);
        while (scan2 != EOF) {
            if(strcmp(tmp , argv[3]) == 0){
                check = 1;
                break;
            }
            scan2 = fscanf(branches , "%s" , tmp);
        }
        fclose(branches);
        if (check){
            int scan = fscanf(commit , "%s" , tmp);
            while(scan != EOF){
                int branch_check = 0;
                if(strcmp(tmp , "information:") == 0){
                    scan = fscanf(commit , "%s" , tmp);
                    strcpy(statement , tmp);
                    strcat(statement , " ");
                    scan = fscanf(commit , "%s" , tmp);
                    strcat(statement , "\"");
                    strcat(statement , tmp);
                    scan = fscanf(commit , "%s" , tmp);
                    while(strcmp(tmp , "$") != 0){
                        strcat(statement , " ");
                        strcat(statement , tmp);
                        scan = fscanf(commit , "%s" , tmp);
                    }
                    strcat(statement , "\" ");
                    scan = fscanf(commit , "%s" , tmp);
                    strcat(statement , tmp);
                    strcat(statement , " ");
                    scan = fscanf(commit , "%s" , tmp);
                    strcat(statement , tmp);
                    strcat(statement , " ");
                    scan = fscanf(commit , "%s" , tmp);
                    strcat(statement , tmp);
                    strcat(statement , " ");
                    if(strcmp(tmp , argv[3]) == 0){
                        branch_check = 1;
                    }
                    scan = fscanf(commit , "%s" , tmp);
                    strcat(statement , tmp);
                    strcat(statement , " ");
                    if(branch_check){
                        printf("%s\n" , statement);
                    }
                }
                scan = fscanf(commit , "%s" , tmp);
            }
        }
        else {
            printf("%s not exists" , argv[3]);
        }
    }
    else if(strcmp(argv[2] , "-author") == 0){
        int scan = fscanf(commit , "%s" , tmp);
        while(scan != EOF){
            int author_check = 0;
            if(strcmp(tmp , "information:") == 0){
                scan = fscanf(commit , "%s" , tmp);
                strcpy(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , "\"");
                strcat(statement , tmp);
                scan = fscanf(commit , "%s" , tmp);
                while(strcmp(tmp , "$") != 0){
                    strcat(statement , " ");
                    strcat(statement , tmp);
                    scan = fscanf(commit , "%s" , tmp);
                }
                strcat(statement , "\" ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                if(strcmp(tmp , argv[3]) == 0){
                    author_check = 1;
                }
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                if(author_check){
                    printf("%s\n" , statement);
                }
            }
            scan = fscanf(commit , "%s" , tmp);
        }
    }
    else if(strcmp(argv[2] , "-since") == 0){
        int scan = fscanf(commit , "%s" , tmp);
        while(scan != EOF){
            int date_check = 0;
            if(strcmp(tmp , "information:") == 0){
                scan = fscanf(commit , "%s" , tmp);
                strcpy(statement , tmp);
                strcat(statement , " ");
                int gy , gm , gd , gh , gmin , gs , y , m , d , h , min , s;
                sscanf(tmp , "%02d/%02d/%04d%02d:%02d:%02d" , &gm , &gd , &gy , &gh , &gmin , &gs);
                sscanf(argv[3] , "%02d/%02d/%04d" , &m , &d , &y);
                sscanf(argv[4] , "%02d:%02d:%02d" , &h , &min , &s);
                if(gy == y){
                    if(gm == m){
                        if(gd == d){
                            if(gh == h){
                                if(gmin == min){
                                    if(gs > s){
                                        date_check = 1;
                                    }
                                }
                                else if(gmin > min){
                                    date_check = 1;
                                }
                            }
                            else if(gh > h){
                                date_check = 1;
                            }
                        }
                        else if(gd > d){
                            date_check = 1;
                        }
                    }
                    else if(gm > m){
                        date_check = 1;
                    }
                }
                else if(gy > y){
                    date_check = 1;
                }
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , "\"");
                strcat(statement , tmp);
                scan = fscanf(commit , "%s" , tmp);
                while(strcmp(tmp , "$") != 0){
                    strcat(statement , " ");
                    strcat(statement , tmp);
                    scan = fscanf(commit , "%s" , tmp);
                }
                strcat(statement , "\" ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                if(date_check){
                    printf("%s\n" , statement);
                }
            }
            scan = fscanf(commit , "%s" , tmp);
        }
    }
    else if(strcmp(argv[2] , "-before") == 0){
        int scan = fscanf(commit , "%s" , tmp);
        while(scan != EOF){
            int date_check = 0;
            if(strcmp(tmp , "information:") == 0){
                scan = fscanf(commit , "%s" , tmp);
                strcpy(statement , tmp);
                strcat(statement , " ");
                int gy , gm , gd , gh , gmin , gs , y , m , d , h , min , s;
                sscanf(argv[3] , "%02d/%02d/%04d" , &gm , &gd , &gy);
                sscanf(argv[4] , "%02d:%02d:%02d" , &gh , &gmin , &gs);
                sscanf(tmp , "%02d/%02d/%04d%02d:%02d:%02d" , &m , &d , &y , &h , &min , &s);
                if(gy == y){
                    if(gm == m){
                        if(gd == d){
                            if(gh == h){
                                if(gmin == min){
                                    if(gs > s){
                                        date_check = 1;
                                    }
                                }
                                else if(gmin > min){
                                    date_check = 1;
                                }
                            }
                            else if(gh > h){
                                date_check = 1;
                            }
                        }
                        else if(gd > d){
                            date_check = 1;
                        }
                    }
                    else if(gm > m){
                        date_check = 1;
                    }
                }
                else if(gy > y){
                    date_check = 1;
                }
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , "\"");
                strcat(statement , tmp);
                scan = fscanf(commit , "%s" , tmp);
                while(strcmp(tmp , "$") != 0){
                    strcat(statement , " ");
                    strcat(statement , tmp);
                    scan = fscanf(commit , "%s" , tmp);
                }
                strcat(statement , "\" ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                if(date_check){
                    printf("%s\n" , statement);
                }
            }
            scan = fscanf(commit , "%s" , tmp);
        }
    }
    else if(strcmp(argv[2] , "-search") == 0){
        int scan = fscanf(commit , "%s" , tmp);
        while(scan != EOF){
            int search_check = 0;
            if(strcmp(tmp , "information:") == 0){
                scan = fscanf(commit , "%s" , tmp);
                strcpy(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , "\"");
                strcat(statement , tmp);
                for(int i = 3 ; i < argc ; i ++){
                    if(strstr(argv[i] , "$") != NULL){
                        for(int j = 0; j < strlen(argv[i]) - strlen(strstr(argv[i] , "$")) ; j ++){
                            if(argv[i][j] != tmp[j]){
                                search_check = 0;
                                break;
                            }
                            else {
                                search_check = 1;
                            }
                        }
                        if(search_check){
                            for(int j = 1 ; j < strlen(strstr(argv[i] , "$")) ; j ++){
                                if(argv[i][strlen(argv[i])-j] != tmp[strlen(tmp)-j]){
                                    search_check = 0;
                                    break;
                                }
                                else {
                                    search_check = 1;
                                }
                            }
                        }
                    }
                    else {
                        if(strcmp(tmp , argv[i]) == 0){
                            search_check = 1;
                        }
                    }
                }
                scan = fscanf(commit , "%s" , tmp);
                while(strcmp(tmp , "$") != 0){
                    for(int i = 3 ; i < argc ; i ++){
                        if(strstr(argv[i] , "$") != NULL){
                            int search_check2 = 0;
                            for(int j = 0; j < strlen(argv[i]) - strlen(strstr(argv[i] , "$")) ; j ++){
                                if(argv[i][j] != tmp[j]){
                                    search_check2 = 0;
                                    break;
                                }
                                else {
                                    search_check2 = 1;
                                }
                            }
                            if(search_check2){
                                for(int j = 1 ; j < strlen(strstr(argv[i] , "$")) ; j ++){
                                    if(argv[i][strlen(argv[i])-j] != tmp[strlen(tmp)-j]){
                                        search_check2 = 0;
                                        break;
                                    }
                                    else {
                                        search_check2 = 1;
                                    }
                                }
                            }
                            if(search_check2){
                                search_check = 1;
                            }
                        }
                        else {
                            if(strcmp(tmp , argv[i]) == 0){
                                search_check = 1;
                            }
                        }
                    }
                    strcat(statement , " ");
                    strcat(statement , tmp);
                    scan = fscanf(commit , "%s" , tmp);
                }
                strcat(statement , "\" ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                scan = fscanf(commit , "%s" , tmp);
                strcat(statement , tmp);
                strcat(statement , " ");
                if(search_check){
                    printf("%s\n" , statement);
                }
            }
            scan = fscanf(commit , "%s" , tmp);
        }
        fclose(commit);
        fopen(address , "r");
    }
    fclose(commit);
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
    else if(strcmp(argv[1] , "commit") == 0){
        if(argc < 4){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return run_commit(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
    else if(strcmp(argv[1] , "set") == 0){
        if(argc < 6){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return run_set(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
    else if(strcmp(argv[1] , "replace") == 0 || strcmp(argv[1] , "remove") == 0){
        if(argc < 6 && strcmp(argv[1] , "replace") == 0){
            printf("Invalid input!");
            return 0;
        }
        else if(argc < 4 && strcmp(argv[1] , "remove") == 0){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return shortcut_function(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
    else if(strcmp(argv[1] , "status") == 0){
        if(argc < 2){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            FILE *file_name , *file_name2;
            char address[1024];
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\tmp.txt");
            file_name = fopen(address , "w+");
            fprintf(file_name , ". ");
            fclose(file_name);
            return run_status(argc , argv , ted_address , ".");
        }
        else {
            printf("There is no repository");
        }
    }
    else if(strcmp(argv[1] , "log") == 0){
        if(argc < 2){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return run_log(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
}