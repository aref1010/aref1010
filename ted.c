//Alireza Elmifard 402106207

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <windows.h>
#include <stdbool.h>
#include <shellapi.h>
#include <sys/stat.h>

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
int run_branch(int argc , char *argv[] , char *ted_address);
int status(int argc , char *argv[] , char *ted_address);
int create_list(char *ted_address , char *file_name);
int copy_ted(char *ted_address , char *file_name);
int run_tree(int argc , char *argv[] , char *ted_address);
int run_tag(int argc , char *argv[] , char *ted_address);
int run_checkout(int argc , char *argv[] , char *ted_address);
int copy_file(const char* source_path, const char* destination_path);
int delete(char *ted_address);
int run_grep(int argc , char *argv[] , char *ted_address);
int print_green(char *word);
BOOL CopyDirectory(LPTSTR lpSourcePath, LPTSTR lpDestPath);


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
        fp = fopen("tag.txt" , "w");
        fclose(fp);
        mkdir("hbranch");
        mkdir("commits");
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
                char global_name[1024] , name[1024] , tmp3[1024] , global_email[1024] , email[1024] , tmp[1024] , tmp2[100];
                strcpy(ted_address , address);
                strcpy(tmp , address);
                strcat(tmp , "\\.ted\\name.txt");
                FILE *fp1 = fopen(tmp , "r");
                if (last_modify(tmp , name) != 0) return 1;
                if (last_modify("C:\\Users\\alire\\TED\\name.txt" , global_name) != 0) return 1;
                int scan3 = fscanf(fp1 , "%s" , tmp3);
                fclose(fp1);
                int gy , gm , gd , gh , gmin , gs , y , m , d , h , min , s;
                sscanf(global_name , "%02d/%02d/%04d%02d:%02d:%02d" , &gm , &gd , &gy , &gh , &gmin , &gs);
                sscanf(name , "%02d/%02d/%04d%02d:%02d:%02d" , &m , &d , &y , &h , &min , &s);
                if(gy == y && scan3 != EOF){
                    if(gm == m && scan3 != EOF){
                        if(gd == d && scan3 != EOF){
                            if(gh == h && scan3 != EOF){
                                if(gmin == min && scan3 != EOF){
                                    if(gs > s || scan3 == EOF){
                                        FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                                        int scan = fscanf(gname_address , "%s" , tmp2);
                                        fclose(gname_address);
                                        FILE *name_address = fopen(tmp , "w");
                                        fprintf(name_address , "%s" , tmp2);
                                        fclose(name_address);
                                    }
                                }
                                else if (gmin > min || scan3 == EOF){
                                    FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                                    int scan = fscanf(gname_address , "%s" , tmp2);
                                    fclose(gname_address);
                                    FILE *name_address = fopen(tmp , "w");
                                    fprintf(name_address , "%s" , tmp2);
                                    fclose(name_address);
                                }
                            }
                            else if(gh > h  || scan3 == EOF){
                                FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                                int scan = fscanf(gname_address , "%s" , tmp2);
                                fclose(gname_address);
                                FILE *name_address = fopen(tmp , "w");
                                fprintf(name_address , "%s" , tmp2);
                                fclose(name_address);
                            }
                        }
                        else if(gd > d || scan3 == EOF){
                            FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                            int scan = fscanf(gname_address , "%s" , tmp2);
                            fclose(gname_address);
                            FILE *name_address = fopen(tmp , "w");
                            fprintf(name_address , "%s" , tmp2);
                            fclose(name_address);
                        }
                    }
                    else if(gm > m || scan3 == EOF){
                        FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                        int scan = fscanf(gname_address , "%s" , tmp2);
                        fclose(gname_address);
                        FILE *name_address = fopen(tmp , "w");
                        fprintf(name_address , "%s" , tmp2);
                        fclose(name_address);
                    }
                }
                else if(gy > y || scan3 == EOF){
                    FILE *gname_address = fopen("C:\\Users\\alire\\TED\\name.txt" , "r");
                    int scan = fscanf(gname_address , "%s" , tmp2);
                    fclose(gname_address);
                    FILE *name_address = fopen(tmp , "w");
                    fprintf(name_address , "%s" , tmp2);
                    fclose(name_address);
                }
                strcpy(tmp , address);
                strcat(tmp , "\\.ted\\email.txt");
                FILE *fp2 = fopen(tmp , "r");
                if (last_modify(tmp , email) != 0) return 1;
                if (last_modify("C:\\Users\\alire\\TED\\email.txt" , global_email) != 0) return 1;
                int scan4 = fscanf(fp2 , "%s" , tmp3);
                fclose(fp2);
                sscanf(global_email , "%02d/%02d/%04d%02d:%02d:%02d" , &gm , &gd , &gy , &gh , &gmin , &gs);
                sscanf(email , "%02d/%02d/%04d%02d:%02d:%02d" , &m , &d , &y , &h , &min , &s);
                if(gy == y && scan4 != EOF){
                    if(gm == m && scan4 != EOF){
                        if(gd == d && scan4 != EOF){
                            if(gh == h && scan4 != EOF){
                                if(gmin == min && scan4 != EOF){
                                    if(gs > s || scan4 == EOF){
                                        FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                                        int scan = fscanf(gemail_address , "%s" , tmp2);
                                        fclose(gemail_address);
                                        FILE *email_address = fopen(tmp , "w");
                                        fprintf(email_address , "%s" , tmp2);
                                        fclose(email_address);
                                    }
                                }
                                else if(gmin > min || scan4 == EOF){
                                    FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                                    int scan = fscanf(gemail_address , "%s" , tmp2);
                                    fclose(gemail_address);
                                    FILE *email_address = fopen(tmp , "w");
                                    fprintf(email_address , "%s" , tmp2);
                                    fclose(email_address);
                                }
                            }
                            else if(gh > h || scan4 == EOF){
                                FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                                int scan = fscanf(gemail_address , "%s" , tmp2);
                                fclose(gemail_address);
                                FILE *email_address = fopen(tmp , "w");
                                fprintf(email_address , "%s" , tmp2);
                                fclose(email_address);
                            }
                        }
                        else if(gd > d || scan4 == EOF){
                            FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                            int scan = fscanf(gemail_address , "%s" , tmp2);
                            fclose(gemail_address);
                            FILE *email_address = fopen(tmp , "w");
                            fprintf(email_address , "%s" , tmp2);
                            fclose(email_address);
                        }
                    }
                    else if(gm > m || scan4 == EOF){
                        FILE *gemail_address = fopen("C:\\Users\\alire\\TED\\email.txt" , "r");
                        int scan = fscanf(gemail_address , "%s" , tmp2);
                        fclose(gemail_address);
                        FILE *email_address = fopen(tmp , "w");
                        fprintf(email_address , "%s" , tmp2);
                        fclose(email_address);
                    }
                }
                else if(gy > y || scan4 == EOF){
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
            char file_list[1024] , char_id[1024] , destination[1024];
            strcpy(destination , ted_address);
            strcat(destination , "\\.ted\\commits\\");
            sprintf(char_id , "%d" , id_value);
            strcat(destination , char_id);
            int status = mkdir(destination);
            copy_ted(ted_address , destination);
            // strcpy(file_list , "C:\\Users\\alire\\TED\\commits\\");
            // sprintf(char_id , "%d.txt" , id_value);
            // strcat(file_list , char_id);
            strcpy(file_list , ted_address);
            strcat(file_list , "\\.ted\\hbranch\\");
            strcat(file_list , current_branch);
            strcat(file_list , ".txt");
            FILE *fp2 = fopen(file_list , "w");
            fprintf(fp2 , "%d" , id_value);
            fclose(fp2);
            // create_list(ted_address , file_list);
        }
    }
    return 0;
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
    return 0;
}

int status(int argc , char *argv[] , char *ted_address){
    char stage_address[1024] , commit_address[1024];
    strcpy(stage_address, ted_address);
    strcat(stage_address , "\\.ted\\stage.txt");
    FILE *file_name , *fp = fopen(stage_address , "r+");
    char last_add[1024] , address2[1024] , last_add2[1024] , tmp[1024] , tmp2[10000];
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
                    if(strstr(tmp , "$") != NULL){
                        char *token = strtok(tmp , "$");
                        while(token != NULL){
                            if(strcmp(token , argv[3]) == 0){
                                branch_check = 1;
                            }
                            token = strtok(NULL , "$");
                        }
                    }
                    else {
                        if(strcmp(tmp , argv[3]) == 0){
                            branch_check = 1;
                        }
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

int run_branch(int argc , char *argv[] , char *ted_address){
    char address[1024] , branch[1024] , commit_value[10000] , branch_commit[1024] , tmp[1024];
    if (argc == 2){
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\branches.txt");
        FILE *branches = fopen(address , "r");
        int scan = fscanf(branches , "%s" , branch);
        while(scan != EOF){
            printf("%s\n" , branch);
            scan = fscanf(branches , "%s" , branch);
        }
    }
    else {
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\branches.txt");
        FILE *branches = fopen(address , "r+");
        int check = 0 , scan = fscanf(branches , "%s" , branch);
        while(scan != EOF){
            if(strcmp(argv[2] , branch) == 0){
                check = 1;
                break;
            }
            scan = fscanf(branches , "%s" , branch);
        }
        if(check){
            printf("this branch is already exists");
            return 0;
        }
        else {
            fprintf(branches , "%s " , argv[2]);
            fclose(branches);
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\commit.txt");
            FILE *commit = fopen(address , "r");
            int first_check = 0 , commit_check = 0 , first_word = 0 , scan2 = fscanf(commit , "%s" , tmp);
            strcpy(branch_commit , tmp);
            strcat(branch_commit , " ");
            while(scan2 != EOF){
                if(strcmp(tmp , "$") == 0 && !commit_check){
                    strcat(branch_commit , tmp);
                    strcat(branch_commit , " ");
                    scan2 = fscanf(commit , "%s" , tmp);
                    strcat(branch_commit , tmp);
                    strcat(branch_commit , " ");
                    scan2 = fscanf(commit , "%s" , tmp);
                    strcat(branch_commit , tmp);
                    strcat(branch_commit , " ");
                    scan2 = fscanf(commit , "%s" , tmp);
                    strcat(branch_commit , tmp);
                    strcat(branch_commit , "$");
                    strcat(branch_commit , argv[2]);
                    strcat(branch_commit , " ");
                    scan2 = fscanf(commit , "%s" , tmp);
                    strcat(branch_commit , tmp);
                    strcat(branch_commit , " ");
                    commit_check = 1;
                    scan2 = fscanf(commit , "%s" , tmp);
                }
                if(!commit_check && first_check){
                    strcat(branch_commit , tmp);
                    strcat(branch_commit , " ");
                }
                else if (first_check){
                    if(!first_word && scan2 != EOF){
                        first_word = 1;
                        strcpy(commit_value , tmp);
                        strcat(commit_value , " ");
                    }
                    else{
                        strcat(commit_value , tmp);
                        strcat(commit_value , " ");
                    }
                }
                scan2 = fscanf(commit , "%s" , tmp);
                first_check = 1;
            }
            fclose(commit);
            commit = fopen(address , "w");
            fclose(commit);
            commit = fopen(address , "a");
            fprintf(commit , "%s%s" , branch_commit , commit_value);
            fclose(commit);
            printf("this branch created successfully");
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\hbranch\\");
            strcat(address , argv[2]);
            strcat(address , ".txt");
            FILE *fp2 = fopen(address , "w");
            int id_value;
            char address3[1024];
            strcpy(address3 , ted_address);
            strcat(address3 , "\\.ted\\id.txt");
            FILE *fp3 = fopen(address3 , "r");
            fscanf(fp3 , "%d" , &id_value);
            fprintf(fp2 , "%d" , id_value);
            fclose(fp2);
            return 0;
        }
    }
}

int create_list(char *ted_address , char *file_name){
    char address[1024] , lastmodify[1024];
    struct dirent *entry;
    DIR *dir = opendir(ted_address);
    FILE *fp;
    while ((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_DIR && strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , ".ted") != 0 && strcmp(entry->d_name , "..") != 0){
            strcpy(address , ted_address);
            strcat(address , "\\");
            strcat(address , entry->d_name);
            create_list(address , file_name);
        }
        else if(strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , ".ted") != 0 && strcmp(entry->d_name , "..") != 0){
            strcpy(address , ted_address);
            strcat(address , "\\");
            strcat(address , entry->d_name);
            fp = fopen(file_name , "a");
            if (last_modify(address , lastmodify) != 0) return 1;
            fprintf(fp , "%s %s " , entry->d_name , lastmodify);
            fclose(fp);
        }
    }
    closedir(dir);
    return 0;
}

int copy_ted(char *ted_address , char *destination){
    char address[1024] , address2[1024];
    struct dirent *entry;
    DIR *dir = opendir(ted_address);
    FILE *fp;
    while ((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_DIR && strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , ".ted") != 0 && strcmp(entry->d_name , "..") != 0){
            strcpy(address , ted_address);
            strcat(address , "\\");
            strcat(address , entry->d_name);
            strcpy(address2 , destination);
            strcat(address2 , "\\");
            strcat(address2 , entry->d_name);
            int status = mkdir(address2);
            copy_ted(address , address2);
        }
        else if(strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , ".ted") != 0 && strcmp(entry->d_name , "..") != 0){
            strcpy(address , ted_address);
            strcat(address , "\\");
            strcpy(address2 , destination);
            strcat(address2 , "\\");
            strcat(address , entry->d_name);
            strcat(address2 , entry->d_name);
            copy_file(address , address2);
        }
    }
    closedir(dir);
    return 0;
}

int run_tree(int argc , char *argv[] , char *ted_address){
    char address[1024] , tmp[1024] , master[1024] , branch[1024];
    int master_id[1000] , branch_id[1000];
    strcpy(address , ted_address);
    strcat(address , "\\.ted\\commit.txt");
    FILE *commit = fopen(address , "r");
    int first_check = 0 , count = 0 , branch_count = 0 , master_count = 0 , id , scan = fscanf(commit , "%s" , tmp); 
    while(scan != EOF){
        if(strcmp(tmp , "$") == 0){
            scan = fscanf(commit , "%s" , tmp);
            scan = fscanf(commit , "%s" , tmp);
            sscanf(tmp , "%d" , &id);
            scan = fscanf(commit , "%s" , tmp);
            if(!first_check){
                first_check = 1;
                if(strstr(tmp , "$") != NULL){
                    char *token = strtok(tmp , "$");
                    strcpy(master , token);
                    token = strtok(NULL , "$");
                    strcpy(branch , token);
                    count = 1;
                    branch_count ++;
                    master_count ++;
                    master_id[master_count] = id;
                    branch_id[branch_count] = id;
                }
                else {
                    strcpy(master , tmp);
                    master_count ++;
                    master_id[master_count] = id;
                }
            }
            else {
                if(strstr(tmp , "$") != NULL){
                    char *token = strtok(tmp , "$");
                    token = strtok(NULL , "$");
                    strcpy(branch , token);
                    master_count ++;
                    branch_count ++;
                    if(strcmp(master , "master") == 0){
                        count = master_count;
                    }
                    else {
                        count = branch_count;
                    }
                    master_id[master_count] = id;
                    branch_id[branch_count] = id;
                }
                else {
                    if(strcmp(master , tmp) == 0){
                        master_count ++;
                        master_id[master_count] = id;
                    }
                    else {
                        branch_count ++;
                        branch_id[branch_count] = id;
                    }
                }
            }
        }
        scan = fscanf(commit , "%s" , tmp);
    }
    if(strcmp(master , "master") == 0){
        for(int i = master_count ; i >= count ; i--){
            printf("\n%02d\n|" , master_id[i]);
        }
        printf(" \\\n");
        for(int i = 1 ; i <= branch_count-1 ; i++){
            if(count-i <= 0){
                if(i == branch_count-1){
                    if(count - branch_count != 0){
                        printf("| %02d\n| /\n" , branch_id[branch_count-i]);
                    }
                    else{
                        printf("| %02d\n" , branch_id[branch_count-i]);
                    }
                }
                else{
                    printf("| %02d\n| |\n" , branch_id[branch_count-i]);
                }
            }
            else {
                if(i == branch_count-1){
                    if(count - branch_count != 0){
                        printf("%02d %02d\n| /\n" , master_id[count-i] , branch_id[branch_count-i]);
                    }
                    else{
                        printf("%02d %02d\n" , master_id[count-i] , branch_id[branch_count-i]);
                    }
                }
                else{
                    printf("%02d %02d\n| |\n" , master_id[count-i] , branch_id[branch_count-i]);
                }
            }
        }
        if(branch_count == 1){
            printf("| /\n");
        }
        for(int i = 1 ; i <= count-branch_count ; i++){
            printf("%02d\n" , master_id[count - branch_count + 1 - i]);
            if(i != count-branch_count){
                printf("|\n");
            }
        }
    }
    else {
        for(int i = branch_count ; i >= count ; i--){
            printf("\n%02d\n|" , branch_id[i]);
        }
        printf(" \\\n");
        for(int i = 1 ; i <= master_count-1 ; i++){
            if(count-i <= 0){
                if(i == master_count-1){
                    if(count - master_count != 0){
                        printf("| %02d\n| /\n" , master_id[master_count-i]);
                    }
                    else{
                        printf("| %02d\n" , master_id[master_count-i]);
                    }
                }
                else{
                    printf("| %02d\n| |\n" , master_id[master_count-i]);
                }
            }
            else {
                if(i == master_count-1){
                    if(count - master_count != 0){
                        printf("%02d %02d\n| /\n" , branch_id[count-i] , master_id[master_count-i]);
                    }
                    else{
                        printf("%02d %02d\n" , branch_id[count-i] , master_id[master_count-i]);
                    }
                }
                else{
                    printf("%02d %02d\n| |\n" , branch_id[count-i] , master_id[master_count-i]);
                }
            }
        }
        if(master_count == 1){
            printf("| /\n");
        }
        for(int i = 1 ; i <= count-master_count ; i++){
            printf("%02d\n" , branch_id[count - master_count + 1 - i]);
            if(i != count-master_count){
                printf("|\n");
            }
        }
    }
    return 0;
}

int run_tag(int argc , char *argv[] , char *ted_address){
    char address[1024] , tmp[1024] , date[1024];
    strcpy(address , ted_address);
    strcat(address , "\\.ted\\tag.txt");
    FILE *tag;
    if(argc == 2){
        char tags[100][1024];
        int count = 0;
        tag = fopen(address , "r");
        int scan = fscanf(tag , "%s" , tmp);
        strcpy(tags[count] , tmp);
        count ++;
        while(scan != EOF){
            if(strcmp(tmp , "$") == 0){
                scan = fscanf(tag , "%s" , tmp);
                if(scan != EOF){
                    strcpy(tags[count] , tmp);
                    count ++;
                }
            }
            scan = fscanf(tag , "%s" , tmp);
        }
        fclose(tag);
        for(int i = 0 ; i < count ; i++){
            for(int j = 0 ; j < count-i-1 ; j++){
                if(strcmp(tags[j] , tags[j+1]) > 0){
                    strcpy(tmp , tags[j]);
                    strcpy(tags[j] , tags[j+1]);
                    strcpy(tags[j+1] , tmp);
                }
            }
        }
        for(int i = 0 ; i < count ; i++){
            printf("%s\n" , tags[i]);
        }
    }
    else if (strcmp(argv[2] , "-a") == 0){
        tag = fopen(address , "r");
        int check = 0 , scan = fscanf(tag , "%s" , tmp);
        if(strcmp(tmp , argv[3]) == 0){
            printf("this tag is already exsits");
            check = 1;
        }
        else {
            while(scan != EOF){
                if(strcmp(tmp , "$") == 0){
                    scan = fscanf(tag , "%s" , tmp);
                    if(scan != EOF){
                        if(strcmp(tmp , argv[3]) == 0){
                            printf("this tag is already exsits");
                            check = 1;
                        }
                    }
                }
                scan = fscanf(tag , "%s" , tmp);
            }
        }
        fclose(tag);
        if(!check){
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\tag.txt");
            tag = fopen(address , "a");
            fprintf(tag , "%s " , argv[3]);
            if(argc > 4){
                if(strcmp(argv[4] , "-m") == 0){
                    if(argc > 6){
                        fprintf(tag , "%s " , argv[7]);
                    }
                    else {
                        strcpy(address , ted_address);
                        strcat(address , "\\.ted\\commit.txt");
                        FILE *commit = fopen(address , "r");
                        int scan2 = fscanf(commit , "%s" , tmp);
                        while(scan2 != EOF){
                            if(strcmp(tmp , "$") == 0){
                                scan2 = fscanf(commit , "%s" , tmp);
                                scan2 = fscanf(commit , "%s" , tmp);
                                fprintf(tag , "%s " , tmp);
                                fclose(commit);
                                break;
                            }
                            scan2 = fscanf(commit , "%s" , tmp);
                        }
                    }
                    strcpy(address , ted_address);
                    strcat(address , "\\.ted\\name.txt");
                    FILE *name = fopen(address , "r");
                    fscanf(name , "%s" , tmp);
                    fprintf(tag , "%s " , tmp);
                    fclose(name);
                    strcpy(address , ted_address);
                    strcat(address , "\\.ted\\email.txt");
                    FILE *email = fopen(address , "r");
                    fscanf(email , "%s" , tmp);
                    fprintf(tag , "%s " , tmp);
                    fclose(email);
                    strcpy(address , ted_address);
                    strcat(address , "\\.ted\\tag.txt");
                    fclose(tag);
                    if (last_modify(address , date) != 0) return 1;
                    tag = fopen(address , "a");
                    fprintf(tag , "%s " , date);
                    fprintf(tag , "%s $ " , argv[5]);
                    fclose(tag);
                }
                else if(strcmp(argv[4] , "-c") == 0){
                    fprintf(tag , "%s " , argv[5]);
                    strcpy(address , ted_address);
                    strcat(address , "\\.ted\\name.txt");
                    FILE *name = fopen(address , "r");
                    fscanf(name , "%s" , tmp);
                    fprintf(tag , "%s " , tmp);
                    fclose(name);
                    strcpy(address , ted_address);
                    strcat(address , "\\.ted\\email.txt");
                    FILE *email = fopen(address , "r");
                    fscanf(email , "%s" , tmp);
                    fprintf(tag , "%s " , tmp);
                    fclose(email);
                    strcpy(address , ted_address);
                    strcat(address , "\\.ted\\tag.txt");
                    fclose(tag);
                    if (last_modify(address , date) != 0) return 1;
                    tag = fopen(address , "a");
                    fprintf(tag , "%s " , date);
                    fprintf(tag , "$ ");
                    fclose(tag);
                }
            }
            else {
                strcpy(address , ted_address);
                strcat(address , "\\.ted\\commit.txt");
                FILE *commit = fopen(address , "r");
                int scan3 = fscanf(commit , "%s" , tmp);
                while(scan3 != EOF){
                    if(strcmp(tmp , "$") == 0){
                        scan3 = fscanf(commit , "%s" , tmp);
                        scan3 = fscanf(commit , "%s" , tmp);
                        fprintf(tag , "%s " , tmp);
                        fclose(commit);
                        break;
                    }
                    scan3 = fscanf(commit , "%s" , tmp);
                }
                strcpy(address , ted_address);
                strcat(address , "\\.ted\\name.txt");
                FILE *name = fopen(address , "r");
                fscanf(name , "%s" , tmp);
                fprintf(tag , "%s " , tmp);
                fclose(name);
                strcpy(address , ted_address);
                strcat(address , "\\.ted\\email.txt");
                FILE *email = fopen(address , "r");
                fscanf(email , "%s" , tmp);
                fprintf(tag , "%s " , tmp);
                fclose(email);
                strcpy(address , ted_address);
                strcat(address , "\\.ted\\tag.txt");
                fclose(tag);
                if (last_modify(address , date) != 0) return 1;
                tag = fopen(address , "a");
                fprintf(tag , "%s " , date);
                fprintf(tag , "$ " , argv[5]);
                fclose(tag);
            }
            printf("tag %s created successfully");
        }
    }
    else if (strcmp(argv[2] , "show") == 0){
        tag = fopen(address , "r");
        int scan = fscanf(tag , "%s" , tmp);
        if(strcmp(tmp , argv[3]) == 0){
            printf("tag %s\n" , tmp);
            scan = fscanf(tag , "%s" , tmp);
            printf("commit %s\n" , tmp);
            scan = fscanf(tag , "%s" , tmp);
            printf("Author: %s " , tmp);
            scan = fscanf(tag , "%s" , tmp);
            printf("<%s>\n" , tmp);
            scan = fscanf(tag , "%s" , tmp);
            printf("Date: %s\n" , tmp);
            scan = fscanf(tag , "%s" , tmp);
            printf("Message: ");
            while (strcmp(tmp , "$") != 0){
                printf("%s " , tmp);
                scan = fscanf(tag , "%s" , tmp);
            }
        }
        else {
            while(scan != EOF){
                if(strcmp(tmp , "$") == 0){
                    scan = fscanf(tag , "%s" , tmp);
                    if(strcmp(tmp , argv[3]) == 0 && scan != EOF){
                        printf("tag %s\n" , tmp);
                        scan = fscanf(tag , "%s" , tmp);
                        printf("commit %s\n" , tmp);
                        scan = fscanf(tag , "%s" , tmp);
                        printf("Author: %s " , tmp);
                        scan = fscanf(tag , "%s" , tmp);
                        printf("<%s>\n" , tmp);
                        scan = fscanf(tag , "%s" , tmp);
                        printf("Date: %s\n" , tmp);
                        scan = fscanf(tag , "%s" , tmp);
                        printf("Message: ");
                        while (strcmp(tmp , "$") != 0){
                            printf("%s " , tmp);
                            scan = fscanf(tag , "%s" , tmp);
                        }
                        break;
                    }
                }
                scan = fscanf(tag , "%s" , tmp);
            }
        }
    }
    return 0;
}

int run_checkout(int argc , char *argv[] , char *ted_address){
    char tmp[1024];
    // strcpy(tmp , ted_address);
    // strcat(tmp , "\\.ted\\tmp.txt");
    // create_list(ted_address , tmp);
    if(argv[2][0] >= '0' && argv[2][0] <= '9'){
        char address[1024] , tmp[1024] , current_branch[1024];
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\commits\\");
        strcat(address , argv[2]);
        delete(ted_address);
        copy_ted(address , ted_address);
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\commit.txt");
        FILE *commit = fopen(address , "r");
        int scan = fscanf(commit , "%s" , tmp);
        while(scan != EOF){
            if(strcmp(tmp , "$") == 0){
                scan = fscanf(commit , "%s" , tmp);
                scan = fscanf(commit , "%s" , tmp);
                if(strcmp(argv[2] , tmp) == 0){
                    scan = fscanf(commit , "%s" , tmp);
                    strcpy(current_branch , tmp);
                    break;
                }
            }
            scan = fscanf(commit , "%s" , tmp);
        }
        fclose(commit);
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\current_branch.txt");
        printf("%s\n" , current_branch);
        FILE *branch = fopen(address , "w");
        fprintf(branch , "%s" , current_branch);
        fclose(branch);
    }
    else if(argv[2][0] == 'H' && argv[2][1] == 'E' && argv[2][2] == 'A' && argv[2][3] == 'D'){
        if(strlen(argv[2]) == 4){
            char address[1024] , id[1024] , current_branch[1024];
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\current_branch.txt");
            FILE *cbranch = fopen(address , "r");
            fscanf(cbranch , "%s" , current_branch);
            fclose(cbranch);
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\hbranch\\");
            strcat(address , current_branch);
            strcat(address , ".txt");
            FILE *branch = fopen(address , "r");
            fscanf(branch , "%s" , id);
            fclose(branch);
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\commits\\");
            strcat(address , id);
            delete(ted_address);
            copy_ted(address , ted_address);
        }
        else {
            char address[1024] , current_branch[1024] , sid[1024];
            int id , n;
            char *token = strtok(argv[2] , "-");
            token = strtok(NULL , "-");
            sscanf(token , "%d" , &n);
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\current_branch.txt");
            FILE *cbranch = fopen(address , "r");
            fscanf(cbranch , "%s" , current_branch);
            fclose(cbranch);
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\hbranch\\");
            strcat(address , current_branch);
            strcat(address , ".txt");
            FILE *branch = fopen(address , "r");
            fscanf(branch , "%d" , &id);
            fclose(branch);
            sprintf(sid , "%d" , id-n);
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\commits\\");
            strcat(address , sid);
            delete(ted_address);
            copy_ted(address , ted_address);
        }
    }
    else {
        char address[1024] , id[1024];
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\hbranch\\");
        strcat(address , argv[2]);
        strcat(address , ".txt");
        FILE *branch = fopen(address , "r");
        fscanf(branch , "%s" , id);
        fclose(branch);
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\commits\\");
        strcat(address , id);
        delete(ted_address);
        copy_ted(address , ted_address);
        strcpy(address , ted_address);
        strcat(address , "\\.ted\\current_branch.txt");
        branch = fopen(address , "w");
        fprintf(branch , "%s" , argv[2]);
        fclose(branch);
    }
    printf("checkout complete successfully");
    return 0;
}

int delete(char *ted_address){
    char address[1024] , address2[1024];
    struct dirent *entry;
    DIR *dir = opendir(ted_address);
    FILE *fp;
    while ((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_DIR && strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , ".ted") != 0 && strcmp(entry->d_name , "..") != 0){
            strcpy(address , ted_address);
            strcat(address , "\\");
            strcat(address , entry->d_name);
            delete(address);
            RemoveDirectory(address);
        }
        else if(strcmp(entry->d_name , "ted.c") != 0 && strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name , ".ted") != 0 && strcmp(entry->d_name , "..") != 0){
            strcpy(address , ted_address);
            strcat(address , "\\");
            strcat(address , entry->d_name);
            _unlink(address);
        }
    }
    closedir(dir);
    return 0;
}

int copy_file(const char* source_path, const char* destination_path) {
  // باز کردن فایل مبدا در حالت خواندن
  FILE* source_file = fopen(source_path, "r");
  if (source_file == NULL) {
    perror("Error opening source file");
    return 1;
  }

  // باز کردن فایل مقصد در حالت نوشتن
  FILE* destination_file = fopen(destination_path, "w");
  if (destination_file == NULL) {
    perror("Error opening destination file");
    fclose(source_file);
    return 1;
  }

  // خواندن و نوشتن محتویات فایل به صورت بلوک
  char buffer[1024];
  size_t bytes_read;
  while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
    fwrite(buffer, 1, bytes_read, destination_file);
  }

  // بستن فایل ها
  fclose(source_file);
  fclose(destination_file);

  return 0;
}

int run_grep(int argc , char *argv[] , char *ted_address){
    if(argc > 6){
        if(strcmp(argv[6] , "-c") == 0){
            char address[1024];
            strcpy(address , ted_address);
            strcat(address , "\\.ted\\commits\\");
            strcat(address , argv[7]);
            char *tmp , tmp2[10000] , tmp3[1024];
            strcpy(tmp2 , " ");
            FILE *fp = fopen(address , "r");
            while (fgets(tmp , 1000 , fp) != NULL){
                strcat(tmp2 , tmp);
            }
            print_green(tmp2);
            for(int i = 0 ; i < strlen(tmp2) ; i++){
                if(tmp2[i] == '\n'){
                    tmp2[i] == '$';
                }
            }
            char *token = strtok(tmp2 , " ");
            strcpy(tmp3 , token);
            int check = 0 , n = 1;
            while(token != NULL){
                if(strcmp(token , "$") == 0){
                    if(check){
                        printf("%s\n" , tmp3);
                        if(argc == 9){
                            printf("%d\n" , n);
                        }
                    }
                    n ++;
                    token = strtok(NULL , " ");
                    if(token != NULL){
                        strcpy(tmp3 , token);
                    }
                    else {
                        break;
                    }
                }
                else if(strcmp(token , argv[5]) == 0){
                    printf("%s " , tmp3);
                    print_green(argv[5]);
                    strcpy(tmp3 , " ");
                    check = 1;
                }
                strcat(tmp3 , " ");
                strcat(tmp3 , token);
                token = strtok(NULL , " ");
            }
        }
        else if(strcmp(argv[6] , "-n") == 0){
            char *tmp , tmp2[10000] , tmp3[1024];
            strcpy(tmp2 , " ");
            FILE *fp = fopen(argv[3] , "r");
            while (fgets(tmp , 1000 , fp) != NULL){
                strcat(tmp2 , tmp);
            }
            print_green(tmp2);
            for(int i = 0 ; i < strlen(tmp2) ; i++){
                if(tmp2[i] == '\n'){
                    tmp2[i] == '$';
                }
            }
            char *token = strtok(tmp2 , " ");
            strcpy(tmp3 , token);
            int check = 0 , n = 1;
            while(token != NULL){
                if(strcmp(token , "$") == 0){
                    if(check){
                        printf("%s\n" , tmp3);
                        printf("%d\n" , n);
                    }
                    n++;
                    token = strtok(NULL , " ");
                    if(token != NULL){
                        strcpy(tmp3 , token);
                    }
                    else {
                        break;
                    }
                }
                else if(strcmp(token , argv[5]) == 0){
                    printf("%s " , tmp3);
                    print_green(argv[5]);
                    strcpy(tmp3 , " ");
                    check = 1;
                }
                strcat(tmp3 , " ");
                strcat(tmp3 , token);
                token = strtok(NULL , " ");
            }
        }
    }
    else {
        char *tmp , tmp2[10000] , tmp3[1024];
        strcpy(tmp2 , " ");
        FILE *fp = fopen(argv[3] , "r");
        while (fgets(tmp , 1000 , fp) != NULL){
            strcat(tmp2 , tmp);
        }
        print_green(tmp2);
        for(int i = 0 ; i < strlen(tmp2) ; i++){
            if(tmp2[i] == '\n'){
                tmp2[i] == '$';
            }
        }
        char *token = strtok(tmp2 , " ");
        strcpy(tmp3 , token);
        int check = 0;
        while(token != NULL){
            if(strcmp(token , "$") == 0){
                if(check){
                    printf("%s\n" , tmp3);
                }
                token = strtok(NULL , " ");
                if(token != NULL){
                    strcpy(tmp3 , token);
                }
                else {
                    break;
                }
            }
            else if(strcmp(token , argv[5]) == 0){
                printf("%s " , tmp3);
                print_green(argv[5]);
                strcpy(tmp3 , " ");
                check = 1;
            }
            strcat(tmp3 , " ");
            strcat(tmp3 , token);
            token = strtok(NULL , " ");
        }
    }
    return 0;
}

int print_green(char *word){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsole, &info);
    WORD old_attributes = info.wAttributes;

  // تنظیم رنگ متن
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
  // چاپ کلمه
    printf("%s" , word);
  // بازگرداندن رنگ به حالت پیش فرض
    SetConsoleTextAttribute(hConsole, old_attributes);
    return 0;
}

BOOL CopyDirectory(LPTSTR lpSourcePath, LPTSTR lpDestPath) {
  SHFILEOPSTRUCT FileOp;

  ZeroMemory(&FileOp, sizeof(SHFILEOPSTRUCT));
  FileOp.hwnd = NULL;
  FileOp.wFunc = FO_COPY;
  FileOp.pFrom = lpSourcePath;
  FileOp.pTo = lpDestPath;
  FileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI;

  return (SHFileOperation(&FileOp) == 0);
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
            return status(argc , argv , ted_address);
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
    else if(strcmp(argv[1] , "branch") == 0){
        if(argc < 2){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return run_branch(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
    else if(strcmp(argv[1] , "checkout") == 0){
        if(argc < 3){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return run_checkout(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
    else if(strcmp(argv[1] , "tree") == 0){
        if(argc < 2){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return run_tree(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
    else if(strcmp(argv[1] , "tag") == 0){
        if(argc < 2){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return run_tag(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
    else if(strcmp(argv[1] , "grep") == 0){
        if(argc < 6){
            printf("Invalid input!");
            return 0;
        }
        else if(check_ted(argc , argv , ted_address)){
            return run_grep(argc , argv , ted_address);
        }
        else {
            printf("There is no repository");
        }
    }
    return 0;
}