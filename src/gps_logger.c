#include <stdio.h>
#include <stdlib.h>
#include <gps.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define SD_RECORD_PATH "config"
static int block = 0;
static int partition = 1;


void make_directory(void)
{
    char dir_path[255] = {0};
    struct stat st = {0};

	sprintf(dir_path, "/media/mmcblk%dp%d/%s", block, partition, SD_RECORD_PATH);
    
    if (stat(dir_path, &st) == -1) {
        mkdir(dir_path, 0777);
    }

    fprintf(stderr, "%s with %s \n", __FUNCTION__, dir_path);
}

/* create Schedule or MD alarm recording file name */
void create_storage_filename(char* name_string)
{
    time_t timep;
    struct tm *tp;
	char MM[2], DD[2];

    time(&timep);
    tp = localtime(&timep);

	if ((1 + tp->tm_mon) < 10)
		sprintf(MM, "0%d", (1 + tp->tm_mon));
	else
		sprintf(MM, "%d", (1 + tp->tm_mon));

	if (tp->tm_mday < 10)
		sprintf(DD, "0%d", tp->tm_mday);
	else
		sprintf(DD, "%d", tp->tm_mday);

	sprintf(name_string, "/media/mmcblk%dp%d/%s/%d-%s-%s.log", block, partition, SD_RECORD_PATH, 
		(1900 + tp->tm_year), MM, DD);

	//fprintf(stderr, "%s with %s \n", __FUNCTION__, name_string);

}


void get_cur_date(char* date_string)
{
    time_t timep;
    struct tm *tp;
	char MM[2], DD[2];

    time(&timep);
    tp = localtime(&timep);

	if ((1 + tp->tm_mon) < 10)
		sprintf(MM, "0%d", (1 + tp->tm_mon));
	else
		sprintf(MM, "%d", (1 + tp->tm_mon));

	if (tp->tm_mday < 10)
		sprintf(DD, "0%d", tp->tm_mday);
	else
		sprintf(DD, "%d", tp->tm_mday);

	sprintf(date_string, "%d%s%s",
		(1900 + tp->tm_year), MM, DD);

	//fprintf(stderr, "%s with %s \n", __FUNCTION__, time_string);

}


void get_cur_time(char* time_string)
{
    time_t timep;
    struct tm *tp;
	char MM[2], DD[2], hh[2], mm[2], ss[2];

    time(&timep);
    tp = localtime(&timep);

	if ((1 + tp->tm_mon) < 10)
		sprintf(MM, "0%d", (1 + tp->tm_mon));
	else
		sprintf(MM, "%d", (1 + tp->tm_mon));

	if (tp->tm_mday < 10)
		sprintf(DD, "0%d", tp->tm_mday);
	else
		sprintf(DD, "%d", tp->tm_mday);

	if (tp->tm_hour < 10)
		sprintf(hh, "0%d", tp->tm_hour);
	else
		sprintf(hh, "%d", tp->tm_hour);

	if (tp->tm_min < 10)
		sprintf(mm, "0%d", tp->tm_min);
	else
		sprintf(mm, "%d", tp->tm_min);

	if (tp->tm_sec < 10)
		sprintf(ss, "0%d", tp->tm_sec);
	else
		sprintf(ss, "%d", tp->tm_sec);

	sprintf(time_string, "%d%s%s-%s%s%s",
		(1900 + tp->tm_year), MM, DD, hh, mm, ss);

	//fprintf(stderr, "%s with %s \n", __FUNCTION__, time_string);

}

int main(void) {
    
    char name_string[255] = {0};
    char time_string[40];
    char date_string[40] = {0};
    char gps_string[255];

    //int file_write_err_cnt = 5000;
    //make_directory();
    
    get_cur_date(date_string);    
    create_storage_filename(name_string);

    // Open
    gps_init();

    loc_t data;
    fprintf(stderr, "%s with %s \n", __FUNCTION__, name_string);
    while (1) {
        char temp_date_string[40] = {0};
        get_cur_date(temp_date_string);  
        if(strcmp(date_string, temp_date_string)) {
            memset(date_string, 0, 40);
            get_cur_date(date_string);  
            create_storage_filename(name_string);
        }

        FILE *fp = fopen(name_string, "a");
        if (fp) {
          
            memset(time_string, 0, 40);
            memset(gps_string, 0, 255);
        
            get_cur_time(time_string);
            gps_location(&data);

            sprintf(gps_string, "%s,%lf,%lf,%lf,%lf,%lf,%s\r\n", time_string, data.latitude, data.longitude,
                                                            data.speed, data.altitude,data.course, data.buffer);
        
            fwrite(gps_string, sizeof(char), strlen(gps_string), fp);
            //printf("gps-->%s\n", gps_string);

            fclose(fp);
        }
        else {
            gps_location(&data);
            //file_write_err_cnt--;
            //if(file_write_err_cnt < 0) {
            //    printf("FAT table check and recovery..\n");
            //    system("reboot");
        }

        //}
    }


    return EXIT_SUCCESS;
}

