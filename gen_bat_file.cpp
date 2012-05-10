#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<conio.h>

int main()
{
    char line[100];
    char make_string[500];
    char input_file_name[30];
    char output_file_name[30];
    DIR *dir = opendir(".");
    //error
    if(dir == NULL)
    {
        printf("Incorrect directory");
        getch();
        return 0;
    }
    struct dirent *ent;

    while((ent = readdir(dir)) != NULL)
    {
        strcpy(input_file_name, ent->d_name);
        if(   input_file_name[strlen(input_file_name)-1] == 't'
           && input_file_name[strlen(input_file_name)-2] == 'x'
           && input_file_name[strlen(input_file_name)-3] == 't')
        {
            FILE *f = fopen(input_file_name, "r");

            strcpy(output_file_name, input_file_name);
            output_file_name[strlen(output_file_name) - 2] = 'a';
            output_file_name[strlen(output_file_name) - 3] = 'b';
            //clear or create file
            FILE *g = fopen(output_file_name, "w");
            fprintf(g, "");
            fclose(g);

            g = fopen(output_file_name, "a");
            fprintf(g, "%s", "@echo off\n");
            while( fgets(line, 100, f))
            {
                line[strlen(line)-1] = '\0';
                strcpy(make_string, "set address=\"");
                strcat(make_string, line);
                strcat(make_string, "\"\n");
                strcat(make_string, "set attributes=attrib %address%\n");
                strcat(make_string, "for /F \"tokens=*\" %%i in ('%attributes%') do set var=%%i\n");
                strcat(make_string, "set var=%var: =%\n");
                strcat(make_string, "if %var:~1,1%==H (attrib -H %address%)\n");
                strcat(make_string, "if NOT %var:~1,1%==H (attrib +H %address%)\n\n");
                fprintf(g, "%s", make_string);
            }
	    printf("%s\n", input_file_name);
	    fprintf(g, "%s", "@echo on\n");
            fclose(g);
            fclose(f);


        }
    }
    closedir(dir);
    return 0;
}
