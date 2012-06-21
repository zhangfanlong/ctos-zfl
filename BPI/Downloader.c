/************************************************************
功能：根据URL的值下载网页
************************************************************/

void downloadHtml(char url[])
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr;
    struct hostent *host;
    int portnumber,nbytes;
    char host_addr[256];
    char host_file[1024];
    char local_file[256];
    FILE * fp;
    char request[1024];
    int send, totalsend;
    int i;
    char * pt;
    char head_line[1024];
    int everyline_number;

    ToLowerCase(url);

    GetHost(url, host_addr, host_file, &portnumber);

    if((host=gethostbyname(host_addr))==NULL)
    {

        fprintf(stderr,"Gethostname error, %s\n", strerror(errno));
        exit(1);
    }


    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        fprintf(stderr,"Socket Error:%s\a\n",strerror(errno));
        exit(1);
    }

    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(portnumber);
    server_addr.sin_addr=*((struct in_addr *)host->h_addr);

    if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
    {
        fprintf(stderr,"Connect Error:%s\a\n",strerror(errno));
        exit(1);
    }


    sprintf(request, "GET /%s HTTP/1.1\r\nAccept: */*\r\nAccept-Language: zh-cn\r\n\
User-Agent: Mozilla/5.0\r\n\
Host: %s:%d\r\nConnection: Close\r\n\r\n", host_file, host_addr, portnumber);
    printf("%s", request);



    if(host_file && *host_file)
    {
        pt = Rstrchr(host_file, '/');
    }
    else
    {
        pt = 0;
    }

    memset(local_file, 0, sizeof(local_file));

    if(pt && *pt)
    {
        if((pt + 1) && *(pt+1))
        {
            strcpy(local_file, pt + 1);
        }
        else
        {
            memcpy(local_file, host_file, strlen(host_file) - 1);
        }
    }

    else if(host_file && *host_file)
    {
        strcpy(local_file, host_file);
    }
    else
    {
        strcpy(local_file, "index.html");
    }

    printf("local filename to write:%s\n\n", local_file);

    send = 0;
    totalsend = 0;
    nbytes=strlen(request);

    while(totalsend < nbytes)
    {

        send = write(sockfd, request + totalsend, nbytes - totalsend);

        if(send==-1)
        {
            printf("send error!%s\n", strerror(errno));
            exit(0);
        }

        totalsend+=send;
        printf("%d bytes send OK!\n", totalsend);
    }

    fp = fopen(local_file, "a");

    if(!fp)
    {
        printf("create file error! %s\n", strerror(errno));
        return;
    }

    printf("\nThe following is the response header:\n");

    i=0;
    everyline_number = 0;

    createTempFile();

    while((nbytes=read(sockfd,buffer,1))==1)
    {

        if(i < 4)
        {
            if(buffer[0] == '\r' || buffer[0] == '\n')
            {
                i++;
                head_line[everyline_number] = 0;
                everyline_number = 0;
                printf("%s\n", head_line);

                ToLowerCase(head_line);
                char *ptr;

                printf("HEAD_LINE:%s.\n", head_line);



                if ((ptr = strstr(head_line, SET_COOKIE)) != NULL)
                {
                    fflush(fp);
                    saveCookie(host_addr, ptr + strlen(SET_COOKIE));
                }
            }
            else
            {
                i = 0;
                head_line[everyline_number] = buffer[0];
                everyline_number ++;
            }
        }
        else
        {
            break;
        }
    }

    char test_cookie[1024];
    if (getCookie(url, test_cookie))
    {
        printf("test_cookie:%s.\n", test_cookie);
    }
    else
    {
        pritnf("can not find the cookie in COOKIE.\n");
    }

    while ((nbytes=read(sockfd,buffer,1))==1)
    {
        fwrite(buffer, 1, 1, fp);
        i++;

        if (i % 1024 == 0)
        {
            fflush(fp);
        }
    }

    fclose(fp);
    close(sockfd);

}