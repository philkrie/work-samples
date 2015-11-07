#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "def"
#include "duckchat.h"
#include "linked_list.h"

//Method for validating a user is logged in
int user_validate(struct user_node* list, char* sa_data){
    struct user_node* user_it = list;
            if(user_it->next_user == NULL){
                return 0;
            } 
            user_it = user_it->next_user; //Move past Server base user
            while(user_it != NULL){
                 if(strcmp(user_it->user_address.sa_data, sa_data)==0){
                    return 1;
                 }
                 user_it = user_it->next_user;
            }
            return 0;
}

int main(int argc, char *argv[]) {
    (void) argc;
    int sd; //Variable for the socket
    struct sockaddr_in server; //Structure that specifies an address to connect the socket
    int rc;

    if(argc != 3){
        printf("This program takes two arguments: host address, and port number\n");
        exit(0);
    }

    //Address family that is used to designate the type of address you communicate with. 
    //In this case, protocol v4 addresses
    server.sin_family = AF_INET; 
    //Server is bound to all available interfaces.
    if(strcmp(argv[1], "localhost")==0){
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
    } else {
        server.sin_addr.s_addr = inet_addr(argv[1]);
    }
    
    //htonl converts longs from host to network byte order. htons does same but for shorts
    server.sin_port = htons(atoi(argv[2]));

    //Assign socket to sd descriptor. Socket takes type (AF_INET),
    //type of comm (SOCK_DGRAM), and protocol to use (0).
    sd = socket(AF_INET, SOCK_DGRAM,0);

    //Sets sets local address and port of the socket
    bind(sd, (SA *) &server, sizeof(server));

    //Create channel list that tracks all current channels. Initialized with Common
    struct channel_node* channel_list = malloc(sizeof(struct channel_node));
    strcpy(channel_list->channel_name, "Common");
    channel_list->next_channel = NULL; 
    //Give the channel its first user: the Server. Never gets deleted.
    channel_list->channels_users = malloc(sizeof(struct user_node));
    strcpy(channel_list->channels_users->user_name, "Server");
    channel_list->channels_users->next_user = NULL;
    
    //Create the first user
    struct user_node* user_list = malloc(sizeof(struct user_node));
    strcpy(user_list->user_name, "Server");
    user_list->next_user = NULL;

    for(;;){
        struct sockaddr sender = {0};
        socklen_t sendsize = sizeof(sender);

        //Our request message that we will recieve
        struct request* recieving = (struct request *)malloc(sizeof(struct request_say));
        rc = recvfrom(sd, recieving, sizeof(struct request_say), 
                       0, (struct sockaddr*)&sender, &sendsize);
        (void) rc;
        
        if(recieving->req_type == REQ_LOGIN){
            //A new user has joined the server and is "logging in"
            //Send them welcome message
            //Add them to the user list. If first user, initialize user list.
            //Parse message
            printf("Received a REQ_LOGIN message\n");
            struct request_login* recieving_login = (struct request_login*) recieving;
            printf("Received login request from user %s\n", recieving_login->req_username);
            printf("Placing %s into Common channel\n", recieving_login->req_username);

            //Add user to the user list
            push_user(user_list, recieving_login->req_username, sender);
            
             //Add user to channel "Common" and add user to the user channel
            if(channel_list->channels_users == NULL){
                channel_list->channels_users = malloc(sizeof(struct user_node));
                channel_list->channels_users->user_address = sender;
                channel_list->channels_users->next_user = NULL; 
                strcpy(channel_list->channels_users->user_name, recieving_login->req_username);
                channel_list->channels_users->users_channels = malloc(sizeof(struct channel_node));
                strcpy(channel_list->channels_users->users_channels->channel_name,"Common");
                channel_list->channels_users->users_channels->next_channel = NULL;
            } else {
                push_user(channel_list->channels_users, recieving_login->req_username, sender);
            }
        }

        else if(user_validate(user_list, sender.sa_data) == 0){
            printf("This user has not yet logged in\n");
            struct text_error error;
            error.txt_type = TXT_ERROR;
            strcpy(error.txt_error, "You have not logged in. Please restart the client\n");
            sendto(sd, &error, sizeof(struct text_error), 0, (SA *) &sender, sendsize);

        }

        else if(recieving->req_type == REQ_SAY){
            //We have recieved a message from a user on a channel.
            //We want to redirect this message to everyone who is a member of the channel
            //And with the username, which we determine serverside with a sock_addr comparison
            printf("Received a REQ_SAY message\n");
            struct request_say* recieving_say = (struct request_say*) recieving;
            printf("Received message '%s' on channel %s\n", recieving_say->req_text, 
                                                            recieving_say->req_channel);
            //Find the name of the user based on the address
            char sender_name[USERNAME_MAX];
            struct user_node* user_it = user_list;
            while(user_it != NULL){
                 if(strcmp(user_it->user_address.sa_data, sender.sa_data)==0){
                    strcpy(sender_name, user_it->user_name);
                    break;
                 }
                 user_it = user_it->next_user;
            }
            //Construct our message
            struct text_say message;
            message.txt_type = TXT_SAY;
            strcpy(message.txt_text, recieving_say->req_text);
            strcpy(message.txt_username, sender_name);
            strcpy(message.txt_channel, recieving_say->req_channel);
            //Find the channel and send it to each of its users
            struct channel_node* channel_it = channel_list;
            while(channel_it != NULL){
                if(strcmp(channel_it->channel_name, recieving_say->req_channel)==0){
                    user_it = channel_it->channels_users->next_user;
                    while(user_it != NULL){
                        sendto(sd, &message, sizeof(struct text_say), 
                            0, (SA *) &(user_it->user_address), sendsize);
                        printf("Sent to %s\n", user_it->user_name);
                        user_it = user_it->next_user;
                    }
                    break;
                }
                channel_it = channel_it->next_channel; 
            }
        }
        
        else if(recieving->req_type == REQ_LOGOUT){
            //Based on the senders sock_addr, remove them from the user list, and from all channel lists
            printf("Received a REQ_LOGOUT message\n");

            char sender_name[USERNAME_MAX];
            struct user_node* it = user_list;
            while(it != NULL){
                 if(strcmp(it->user_address.sa_data, sender.sa_data)==0){
                    strcpy(sender_name, it->user_name);
                 }
                 it = it->next_user;
            }

            delete_user_from_user_list(&user_list, sender_name);
            delete_user_from_channel_list(channel_list, sender_name);

            struct text_say message;
            message.txt_type = TXT_SAY;
            strcpy(message.txt_text, "You have successfully logged out. Goodbye!");
            printf("Responding with %s\n", message.txt_text);
            sendto(sd, &message, sizeof(struct text_say), 0, (SA *) &sender, sendsize);
        }

        else if(recieving->req_type == REQ_JOIN){
            //User wants to join a channel. If the channel already exists, let them join it
            //If they are already in the channel, let them know that nothing has changed
            //If the channel doesn't exist, create a new channel, and let them know they have joined it
            printf("Received a REQ_JOIN message\n");
            struct request_join* recieving_join = (struct request_join*) recieving;
            printf("User is asking to join: %s\n", recieving_join->req_channel);


            char sender_name[USERNAME_MAX];
            struct user_node* user_it = user_list;
            while(user_it != NULL){
                 if(strcmp(user_it->user_address.sa_data, sender.sa_data)==0){
                    strcpy(sender_name, user_it->user_name);
                 }
                 user_it = user_it->next_user;
            }

            if(strcmp("Common", recieving_join->req_channel)==0){
                //You're already in this channel!
            } else {
                struct channel_node* channel_it = channel_list;
                user_it = user_list;
                int channel_exists = 0;
                int subscribed = 0;
                while(channel_it != NULL){
                    if(strcmp(channel_it->channel_name, recieving_join->req_channel)==0){
                        channel_exists = 1;
                        break; //Found channel
                    }
                    channel_it = channel_it->next_channel;
                }
                if(channel_exists == 1){
                    printf("Channel already exists. Checking if user is already subscribed\n");
                    user_it = channel_it->channels_users;
                    while(user_it != NULL){
                        if(strcmp(user_it->user_name, sender_name)==0){
                            subscribed = 1;
                            break;
                        }
                        user_it = user_it->next_user;
                    }
                    if(subscribed == 1){
                        printf("User is already subscribed to this channel\n");
                    } else {
                        printf("User isn't yet subscribed to this channel, adding\n");
                        push_user_to_channel_list(channel_list, recieving_join->req_channel, sender_name, 
                            sender);
                        push_channel_to_user_list(user_list, recieving_join->req_channel, 
                            sender_name, sender);
                    }

                } else {
                    printf("Channel does not exist. Creating channel and adding user\n");
                    push_channel(channel_list, recieving_join->req_channel, sender_name, sender);
                    push_channel_to_user_list(user_list, recieving_join->req_channel, 
                        sender_name, sender);
                }
            }
        }

        else if(recieving->req_type == REQ_LEAVE){
            //User wants to leave channel. Remove channel from users list and user from channels list
            //If this list becomes empty, delete the channel (unless it is common)
            printf("Received a request_leave message\n");
            struct request_leave* recieving_leave = (struct request_leave*) recieving;
            printf("Received request to leave channel %s\n", recieving_leave->req_channel);

            if(strcmp(recieving_leave->req_channel, "Common")==0){
                printf("You may not leave Common, it is the default channel\n");
                struct text_error error;
                error.txt_type = TXT_ERROR;
                strcpy(error.txt_error, "You may not delete Common. It is the default\n");
                sendto(sd, &error, sizeof(struct text_error), 0, (SA *) &sender, sendsize);
            }
            char sender_name[USERNAME_MAX];
            struct user_node* user_it = user_list;
            while(user_it != NULL){
                 if(strcmp(user_it->user_address.sa_data, sender.sa_data)==0){
                    strcpy(sender_name, user_it->user_name);
                    break;
                 }
                 user_it = user_it->next_user;
            }

            struct channel_node* channel_it = channel_list;
            while(channel_it != NULL){
                if(strcmp(channel_it->channel_name, recieving_leave->req_channel)==0){
                    break;
                }
                channel_it = channel_it->next_channel;
            }

            if(channel_it == NULL){
                printf("This channel does not exist. Please try another channel\n");
            } else {
                delete_user_from_user_list(&(channel_it->channels_users), sender_name);
                delete_channel_from_channel_list(&(user_it->users_channels), recieving_leave->req_channel);

                if(channel_it->channels_users->next_user == NULL){
                    delete_channel_from_channel_list(&channel_list, recieving_leave->req_channel);
                }
            }

            
        }
        else if(recieving->req_type == REQ_LIST){
            //Send the user a list of all of the channels on the server
            printf("Received a request_list message\n");

            struct channel_node* channel_it = channel_list;
            int num_channels = 0;
            while(channel_it != NULL){
                num_channels++;
                channel_it = channel_it->next_channel;
            }

            struct text_list* message = (struct text_list*) malloc(sizeof(struct text_list)
                + num_channels * sizeof(struct channel_info));
            message->txt_type = TXT_LIST;
            message->txt_nchannels = num_channels;

            channel_it = channel_list;
            int i = 0;
            while(channel_it != NULL){
                strcpy(message->txt_channels[i].ch_channel, channel_it->channel_name);
                channel_it = channel_it->next_channel;
                i++;
            }
            sendto(sd, message, sizeof(struct text_say), 0, (SA *) &sender, sendsize);
        }
        else if(recieving->req_type == REQ_WHO){
            //Send user list of all users on a channel
            printf("Received a REQUEST_WHO message\n");
            struct request_who* recieving_who = (struct request_who*) recieving;
            printf("Inquiring about users on %s\n", recieving_who->req_channel);

            int user_count = 0;
            struct channel_node* channel_it = channel_list;
            while(channel_it != NULL){
                if(strcmp(channel_it->channel_name, recieving_who->req_channel)==0){
                    struct user_node* user_it = channel_it->channels_users->next_user;
                    while(user_it != NULL){
                        user_count++;
                        user_it = user_it->next_user;
                    }
                    break;
                }
                channel_it = channel_it->next_channel;
            }

            if(channel_it == NULL){
                printf("This channel does not exist. \n");
                struct text_error error;
                error.txt_type = TXT_ERROR;
                strcpy(error.txt_error, "No such channel\n");
                sendto(sd, &error, sizeof(struct text_error), 0, (SA *) &sender, sendsize);
            } else {
                //Needs logic in case the channel isn't found
            
                struct text_who* message = (struct text_who*) malloc(sizeof(struct text_who) 
                    + user_count * sizeof(struct user_info));
                message->txt_type = TXT_WHO;
                message->txt_nusernames = user_count;
                strcpy(message->txt_channel, channel_it->channel_name);
                struct user_node* user_it= channel_it->channels_users->next_user;
                int i = 0;
                while(user_it != NULL){
                            strcpy(message->txt_users[i].us_username, user_it->user_name);
                            printf("%s\n", message->txt_users[i].us_username);
                            user_it = user_it->next_user;
                            i++;
                        }
                sendto(sd, message, sizeof(struct text_who) + user_count * sizeof(struct user_info), 
                    0, (SA *) &sender, sendsize);
                free(message);
            }
        }

        free(recieving);

        
         //Prints out our message
    }
}