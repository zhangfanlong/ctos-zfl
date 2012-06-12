/**************************************************************
  功能：从字符串src中分析出网站地址和端口，并得到用户要下载的文件
***************************************************************/
void GetHost(char * src, char * web, char * file, int * port)
{
    char * pA;
    char * pB;

    memset(web, 0, sizeof(web));
    memset(file, 0, sizeof(file));

    *port = 0;

    if(!(*src))
    {
        return;
    }
    pA = src;
    if(!strncmp(pA, "http://", strlen("http://")))   pA = src+strlen("http://");

    else if(!strncmp(pA, "https://", strlen("https://")))   pA = src+strlen("https://");
    pB = strchr(pA, '/');
    if(pB)
    {

        memcpy(web, pA, strlen(pA) - strlen(pB));

        if(pB+1)
        {

            memcpy(file, pB + 1, strlen(pB) - 1);

            file[strlen(pB) - 1] = 0;

        }

    }

    else   memcpy(web, pA, strlen(pA));

    if(pB)   web[strlen(pA) - strlen(pB)] = 0;

    else   web[strlen(pA)] = 0;

    pA = strchr(web, ':');

    if(pA)   *port = atoi(pA + 1);

    else *port = 80;
}
/*****************************************************
功能: 根据从服务器传来的Set-Cookie:字段来提取出COOKIE
并把该COOKIE存储到文件里
******************************************************/
int saveCookie(char url[], char cookie[])
{
    FILE *fp;
    char file_name[1024] = "COOKIE/";
    char cookie_information[1024];
    char cookie_name[1024];
    char path[1024];
    char expires[1024];
    char absolute_path[1024];
    char domain[1024];
    int i;

    getCookieName(cookie, cookie_name);
    if (getSegmentData(cookie, cookie_name, "expires", expires))
    {
        strcat(file_name, url);
    }
    else
    {
        strcat(file_name, "temp");
    }


    getSegmentData(cookie, cookie_name, "path", path);
    if (getSegmentData(cookie, cookie_name, "domain", domain))
    {
        strcpy(absolute_path, domain);
    }
    else
    {
        strcpy(absolute_path, url);
    }
    strcat(absolute_path, path);

    if (checkCookieName(file_name, cookie_name, absolute_path))
    {
        deleteCookie(file_name, cookie_name, absolute_path);
        printf("deleted cookie : %s.\n", cookie_name);
    }


    deletePath(cookie);

    strcat(cookie, "; path=");
    strcat(cookie, absolute_path);
    fp = fopen(file_name, "a+");
    for (i = 0; cookie[i] != 0; i ++)
    {
        fwrite(&cookie[i], 1, 1, fp);
        fflush(fp);
    }

    fwrite("\n", 1, 1, fp);

    fflush(fp);
    fclose(fp);
}
/************************************************
功能: 获取COOKIE字段的名字
*************************************************/
void getCookieName(char cookie[], char cookie_name[])
{
    int i, k;

    for (i = 0; cookie[i] == ' '; i ++ )
    {
        ;
    }
    for (k = 0; cookie[i] != '=' && cookie[i] != 0; i ++, k ++)
    {
        cookie_name[k] = cookie[i];
    }
    cookie_name[k] = 0;
}
/***************************************************************
功能: 判断该COOKIE字段在以前出现过没有，若出现返回1，否则返回0。
***************************************************************/
int checkCookieName(char url[], char cookie_name[], char path[])
{
    char cookie_information[1024];
    int flag;
    FILE *fp;
    char *c;
    fp = fopen(url, "a+");
    flag = 0;

    printf("file %s:\n", url);
    while (1)
    {
        c = fgets(cookie_information, 1024, fp);
        if (c == NULL)
        {
            break;
        }
        cookie_information[strlen(cookie_information) - 1] = 0;
        char temp[1024];
        char temp_path[1024];
        getCookieName(cookie_information, temp);

        getSegmentData(cookie_information, temp, "path", temp_path);

        if (strcmp(temp, cookie_name) == 0 && strcmp(path, temp_path) == 0)
        {
            fclose(fp);
            return 1;

        }
    }
    fclose(fp);

    return 0;

}
/*********************************************************************
功能:删除已经存在的COOKIE值。
**********************************************************************/
void deleteCookie(char url[], char cookie_name[], char path[])
{
    FILE *fp;
    FILE *tp;
    char read_block[BLOCK_NUM];
    char temp_file_name[] = "temp_del_cookieXXXX";

    fp = fopen(url, "a+");
    if (fp == NULL)
    {
        printf("Did not have cookie %s.\n", url);
    }

    mkstemp(temp_file_name);

    tp = fopen(temp_file_name, "a+");

    if (tp == NULL)
    {
        printf("Can not create temp file.\n");
    }

    while (fgets(read_block, BLOCK_NUM, fp))
    {
        char cookie_name_line[COOKIE_NAME_NUM];
        char temp_path[1024];
        read_block[strlen(read_block) - 1] = 0;
        getCookieName(read_block, cookie_name_line);
        getSegmentData(read_block, cookie_name_line, "path", temp_path);

        if (strcmp(cookie_name, cookie_name_line) != 0 || strcmp(path, temp_path) != 0)
        {
            fputs(read_block, tp);
            fwrite("\n", 1, 1, tp);
            fflush(tp);
        }

    }

    remove(url);
    rename(temp_file_name, url);
    fflush(fp);
    fclose(fp);
}
/************************************************************************************
功能: 获取COOKIE中字段的一些信息，例如path，domain，expire等。
************************************************************************************/
int  getSegmentData(char cookie[], char cookie_name[], char segment_name[], char data[])
{

    char temp_name[1024];
    getCookieName(cookie, temp_name);

    if (strcmp(temp_name, cookie_name) != 0)
    {
        data[0] = 0;
        return 0;
    }

    int i = 0;
    while (cookie[i] != 0)
    {
        int flag = 0;
        char temp_segment_name[1024];
        int k;
        int l;

        for (; cookie[i] != 0 && (cookie[i] == ' ' || cookie[i] == ';'); i++);
        for (k = 0, l = 0; cookie[i] != 0; i ++)
        {
            if (cookie[i] == '=')
            {
                flag = 1;
            }
            else if (!flag)
            {
                temp_segment_name[k] = cookie[i];
                k++;
            }
            else if (flag == 1 && cookie[i] != ';')
            {
                data[l] = cookie[i];
                l++;
            }

            else if (cookie[i] == ';')
            {
                flag = 2;
                break;
            }
        }
        temp_segment_name[k] = 0;
        data[l] = 0;
        if (strcmp(temp_segment_name, segment_name) == 0)
        {

            return 1;
        }
    }
    return 0;

}
/**********************
功能: 创建一个临时文件，
用来存储那些没有expire
字段的COOKIE。
***********************/
void createTempFile()
{
    FILE *fp;
    char file_name[] = "COOKIE/temp";
    fp = fopen(file_name, "a+");

    fclose(fp);


}
/***************************
功能:删除存放临时COOKIE的文件。
****************************/
void removeTempFile()
{
    remove("COOKIE/temp");
}
/***************************
功能：删除原来字段中的path值
将domain和path重新组合成path
****************************/
int  deletePath(char cookie[])
{

    int i = 0;
    while (cookie[i] != 0)
    {
        int flag = 0;
        char temp_segment_name[1024];
        char data[1024];
        int k;
        int l;

        int recent = i;
        for (; cookie[i] != 0 && (cookie[i] == ' ' || cookie[i] == ';'); i++);

        for (k = 0, l = 0; cookie[i] != 0; i ++)
        {
            if (cookie[i] == '=')
            {
                flag = 1;
            }
            else if (!flag)
            {
                temp_segment_name[k] = cookie[i];
                k++;
            }
            else if (flag == 1 && cookie[i] != ';')
            {
                data[l] = cookie[i];
                l++;
            }

            else if (cookie[i] == ';')
            {
                flag = 2;
                break;
            }
        }
        temp_segment_name[k] = 0;
        data[l] = 0;

        if (strcmp(temp_segment_name, "path") == 0)
        {

            int z;
            for (z = recent; cookie[z + i - recent] != 0 ;  z++)
            {
                cookie[z] = cookie[z + i - recent];
            }
            cookie[z] = 0;
            return 1;
        }
    }

    return 0;

}
/***********************************
功能：判断URL域是否符合COOKIE的域
***********************************/
int  judgeDomainEqual(char path[], char url[])
{
    if (strstr(url, path))
    {
        return 1;
    }

    return 0;
}
/********************************************
功能：获取COOKIE的值
********************************************/
int getCookie(char url[], char cookie[])
{
    char file[1024];
    char web[1024];
    int  port;
    char file_name[1024];
    char every_line[1024];
    char path[1024];
    FILE *fp;

    GetHost(url, web, file, &port);
    strcat(url, "/");
    strcpy(file_name, "COOKIE/");
    strcat(file_name, web);

    fp = fopen(file_name, "r");
    cookie[0] = 0;
    while (fgets(every_line, 1024, fp) != NULL)
    {
        every_line[strlen(every_line) - 1] = 0;
        char cookie_name[1024];
        char data[1024];
        char expire[1024];
        printf("%s", every_line);
        getCookieName(every_line, cookie_name);
        getSegmentData(every_line,cookie_name, "path", path);
        getSegmentData(every_line,cookie_name, "expires", expire);
        printf("Path:%s.\n", path);
        printf("url :%s.\n", url);
        printf("expire:%s.\n", expire);
        if (judgeDomainEqual(path, url) && checkTime(expire))
        {
            getSegmentData(every_line, cookie_name, cookie_name, data);
            strcat(cookie, cookie_name);
            strcat(cookie, "=");
            strcat(cookie, data);
            strcat(cookie, ";");
        }
    }
    strcpy(file_name, "COOKIE/temp");
    fp = fopen(file_name, "r");
    while (fgets(every_line, 1024, fp) != NULL)
    {
        every_line[strlen(every_line) - 1] = 0;
        char cookie_name[1024];
        char data[1024];
        printf("%s", every_line);
        getCookieName(every_line, cookie_name);
        getSegmentData(every_line,cookie_name, "path", path);
        printf("Path:%s.\n", path);
        printf("url :%s.\n", url);
        if (judgeDomainEqual(path, url))
        {
            getSegmentData(every_line, cookie_name, cookie_name, data);
            strcat(cookie, cookie_name);
            strcat(cookie, "=");
            strcat(cookie, data);
            strcat(cookie, ";");
        }
    }

    if (cookie[0] != 0)
    {
        cookie[strlen(cookie) - 1] = 0;
        return 1;
    }
    else
    {
        return 0;
    }

}
/***************************************************************
功能：判断COOKIE中的expire字段是否符合要求，就是用expire字段和
当前时间做比较。如果expire字段的值大于当前时间则COOKIE有效。否则
此COOKIE过期。
**************************************************************/
int checkTime(char expires[])
{
    char month[MONTH_LENGTH];
    char every_month[MONTH_SUM][MONTH_LENGTH] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    char week[WEEK_LENGTH];
    char every_week[WEEK_SUM][WEEK_LENGTH] = {"", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    int  day;
    int year;
    int second;
    int minute;
    int hour;
    char temp[1024];
    char expire_time[1024];
    char now_time[1024];
    int month_num;
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime (&rawtime);


    sscanf(expires, "%s %d-%[a-zA-Z]-%d %d:%d:%d", week, &day, month, &year, &hour, &minute, &second);

    printf("MONTH:%s.\n", month);

    for (month_num = 1; month_num < MONTH_SUM; month_num++)
    {
        if (strcmp(every_month[month_num], month) == 0)
        {
            break;
        }

    }
    sprintf(expire_time, "%04d-%02d-%02d-%02d-%02d-%02d", year, month_num, day, hour, minute, second);
    printf("EXPIRE_TIME:%s.\n",expire_time);
    sprintf(now_time, "%04d-%02d-%02d-%02d-%02d-%02d", timeinfo -> tm_year + 1900, timeinfo -> tm_mon + 1, timeinfo -> tm_mday, timeinfo -> tm_hour, timeinfo -> tm_min, timeinfo -> tm_sec);
    printf("NOW_TIME:%s.\n", now_time);
    if (strcmp(now_time, expire_time) < 0)
    {
        return 1;
    }
    return 0;
}
