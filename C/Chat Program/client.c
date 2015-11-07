#include <stdlib.h>
#include <string.h>
#include "def"
#include "duckchat.h"
#include "linked_list.h"

int main(int argc, char *argv[]){
    //Intialize variables
    int sd_parent;
    int port;
    struct sockaddr_in server;
    struct hostent *hp, *gethostbyname();
    char user_name[USERNAME_MAX];

    if(argc != 4){
        printf("This program takes three arguments: host address, port number, and username\n");
        exit(0);
    }

    //Get our hostname
    if(strlen(argv[1]) > UNIX_PATH_MAX){
        printf("This host address is too long. Please make it 108 character or less\n");
        exit(0);
    }
    hp = gethostbyname(argv[1]);

    //Get our port number
    port = atoi(argv[2]);
    //Get our username
    if(strlen(argv[3]) > USERNAME_MAX){
        printf("This username is too long. Please make it 32 characters or less\n");
        exit(0);
    }
    strcpy(user_name, argv[3]);

    //Create our sockets
    sd_parent = socket (AF_INET,SOCK_DGRAM,0);

    //Configure server
    //Set server to have same socket family
    server.sin_family = AF_INET;
    //Set server to have sin_addr.s_addr to hostname addr
    memcpy(&(server.sin_addr.s_addr), hp->h_addr, hp->h_length);
    //Set server to have port number specified by user
    server.sin_port = htons(port);

    struct simple_channel_node* list = malloc(sizeof(struct simple_channel_node));
    list->next_channel = NULL;
    strcpy(list->channel_name, "Common");

    struct simple_channel_node* current_channel = list;

    pid_t pid = fork();

    if(pid == 0){
        int rc;
        struct sockaddr sender = {0};
        socklen_t sendsize = sizeof(sender);
        
        for(;;){
            //Wait for a response back
            struct text* server_text = (struct text *)malloc(sizeof(struct text_say));
            rc = recvfrom(sd_parent, server_text, sizeof(struct text_say), 
                                 0, (struct sockaddr*)&sender, &sendsize);
            (void) rc;

            //Backspaces
            int i;
            for(i = 0; i < 500; i++){
                printf("\b");
            }

            //Parse a text_say message
            if(server_text->txt_type == TXT_SAY){
                struct text_say* text_say = (struct text_say*) server_text;
                printf("[%s][%s]: %s\n >",text_say->txt_channel,text_say->txt_username,text_say->txt_text);

            }

            //Parse a text_list message
            if(server_text->txt_type == TXT_LIST){
                struct text_list* text_list = (struct text_list*) server_text;
                int num_channels = text_list->txt_nchannels;
                printf("Existing channels:\n");
                int i;
                for(i = 0; i < num_channels; i++){
                    printf("  %s\n", (char*)text_list->txt_channels+(32*i));
                }
                //Iterate through channel information to print our the number of channels
            }
            
            //Parse a text_who message
            if(server_text->txt_type == TXT_WHO){
                struct text_who* text_who = (struct text_who*) server_text;
                printf("Users on channel %s:\n", text_who->txt_channel);
                int num_users = text_who->txt_nusernames;
                int i;
                for(i = 0; i < num_users; i++){
                    printf("  %s\n", (char*)text_who->txt_users+(32*i));
                }
            }

            //Parse a text_error message
            if(server_text->txt_type == TXT_ERROR){
                printf("TXT_ERROR\n");
                struct text_error* text_error = (struct text_error*) server_text;
                printf("ERROR: %s\n", text_error->txt_error);
            }
            free(server_text);
        }
    }

    if(pid > 0){
        struct request_login login;
        login.req_type = REQ_LOGIN;
        strncpy(login.req_username, user_name, strlen(user_name));    

        //Send message to server to login
        sendto(sd_parent, &login, sizeof(struct request_login), 0, (SA *) &server, sizeof(server));

        //Join Common
        struct request_join first_join;
        first_join.req_type = REQ_JOIN;
        strcpy(first_join.req_channel, "Common");
        sendto(sd_parent, &first_join, sizeof(struct request_join), 0, (SA *) &server, sizeof(server));

        for(;;){
            //Allocate buffer and text arrays to read user input
            char *buffer = calloc(SAY_MAX, 1);
            char *text = calloc(1,1);

            //Prompt user and get input
            fgets(buffer, SAY_MAX , stdin);
            //Reallocate text and place buffer characters into text array
            text = realloc(text, strlen(buffer));
            strncat(text, buffer, strlen(buffer)); /* note a '\n' is appended here everytime */
            text[strlen(text)-1] = '\0';

            if(text[0] == '/'){
                if(strncmp(text, "/exit", 5) == 0){
                    //Build request_logout message
                    struct request_logout goodbye;
                    goodbye.req_type = REQ_LOGOUT;

                    //Send message to server
                    sendto(sd_parent, &goodbye, sizeof(struct request_logout), 
                                           0, (SA *) &server, sizeof(server));

                    struct simple_channel_node* channel_it = list;
                    struct simple_channel_node* temp;
                    while(channel_it != NULL){
                        temp = channel_it;
                        channel_it = channel_it->next_channel;
                        free(temp);
                    }
                    exit(0);    

                } else if(strncmp(text, "/join", 5) == 0){
                    //Build request_join message
                    struct request_join join;
                    join.req_type = REQ_JOIN;

                    if(strlen(text)-6 > CHANNEL_MAX){
                        printf("This channel name is too long. Please make it 32 characters or less\n");
                    } else {

                        char channel[CHANNEL_MAX];
                        strncpy(channel, text+6, strlen(text)-1);
                    
                        add_simple_channel(list, channel);

                        struct simple_channel_node* searcher;
                        searcher = list;
                        while(searcher != NULL){
                            if(strcmp(searcher->channel_name, channel)==0){
                                break; //Found channel
                            }
                            searcher = searcher->next_channel;
                        }
                        if(searcher != NULL){
                            current_channel = searcher;
                        }

                        strcpy(join.req_channel, channel);
                        //Send message to server
                        sendto(sd_parent, &join, sizeof(struct request_join), 
                                            0, (SA *) &server, sizeof(server));   
                    }

                } else if(strncmp(text, "/leave", 6) == 0){
                    //Build request_leave message
                    struct request_leave leave;
                    leave.req_type = REQ_LEAVE;
                    
                    char channel[CHANNEL_MAX];
                    strncpy(channel, text+7, strlen(text)-1);

                    struct simple_channel_node* searcher;
                    searcher = list;
                    while(searcher != NULL){
                        if(strcmp(searcher->channel_name, channel)==0){
                            break; //Found channel
                        }
                        searcher = searcher->next_channel;
                    }
                    if(searcher == NULL){
                        printf("You cannot leave a channel that you are not subscribed to\n");
                    } else if(strcmp(channel, "Common")==0){
                        printf("You cannot leave Common. It is the default channel\n");
                    } else {
                        if(strcmp(current_channel->channel_name, channel)==0){
                            current_channel = NULL;
                        }

                        delete_simple_channel(list, channel);
                    
                        strcpy(leave.req_channel, channel);
                        //Send message to server
                        sendto(sd_parent, &leave, sizeof(struct request_leave), 
                                            0, (SA *) &server, sizeof(server));  
                    }

                } else if(strncmp(text, "/list", 5) == 0){
                    //Build request_list message
                    struct request_list list;
                    list.req_type = REQ_LIST;

                    //Send message to server
                    sendto(sd_parent, &list, sizeof(struct request_list), 
                                        0, (SA *) &server, sizeof(server));                
                
                } else if(strncmp(text, "/who", 4) == 0){
                    //Build request_who message
                    struct request_who who;
                    who.req_type = REQ_WHO;
                    
                    char channel[CHANNEL_MAX];
                    strncpy(channel, text+5, strlen(text)-1);

                    strcpy(who.req_channel, channel);    
                    //Send message to server
                    sendto(sd_parent, &who, sizeof(struct request_who), 
                                        0, (SA *) &server, sizeof(server));                
                
                } else if(strncmp(text, "/switch", 7) == 0){
                    char channel[CHANNEL_MAX];
                    strncpy(channel, text+8, strlen(text)-1);
                    struct simple_channel_node* searcher;
                    searcher = list;
                    while(searcher != NULL){
                        if(strcmp(searcher->channel_name, channel)==0){
                            break; //Found channel
                        }
                        searcher = searcher->next_channel;
                    }
                    if(searcher != NULL){
                        current_channel = searcher;
                    } else {
                        printf("You are not subscribed to this channel\n");
                    }

                } else {
                    //Unknown special command.
                    //ERROR
                    printf("ERROR: Unknown special command\n");
                }
            } else {
                //Build request_say message

                if(current_channel == NULL){
                    printf("You are not currently switched to a channel. Switch to a subscribed channel or choose a new one\n");
                } else {
                    struct request_say message;
                    message.req_type = REQ_SAY;
                    strcpy(message.req_text, text);
                    strcpy(message.req_channel, current_channel->channel_name);    

                    //Send message to server
                    sendto(sd_parent, &message, sizeof(struct request_say), 
                                        0, (SA *) &server, sizeof(server));
                }
                free(text);
                free(buffer);
               
               } 
            }
        }
        return 0;
    }
