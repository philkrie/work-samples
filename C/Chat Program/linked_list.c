#include <stdlib.h>
#include <string.h>
#include "def"
#include "raw.h"
#include "duckchat.h"
#include "linked_list.h"

//Destroys a linked list of users. Never called on the main list of users.
//Destroys everything except for the first user, known always as "Server." Default user, always present.
void destroy_users(struct user_node *head){
    struct user_node *current = head;
    struct user_node *next;
    while (current != NULL)
    {
       next = current->next_user;
       free(current);
       current = next;
    }
    head = NULL;
}

//Destroys a linked list of channels. Never called on the main list of channels
//Destroys everything except for the first channel, known always as "Common." Default channel.
void destroy_channels(struct channel_node *head){
    struct channel_node *current = head;
    struct channel_node *next;
    while (current != NULL)
    {
       next = current->next_channel;
       free(current);
       current = next;
    }
    head = NULL;
}

//Pushes a user onto the userlist specified. Also starts the channel_list attached to the user.
void push_user(struct user_node* user_list, char* name, struct sockaddr address) {
    struct user_node* current = user_list;
    while(current->next_user != NULL) {
        current = current->next_user;
    }
    /* now we can add a new variable */
    current->next_user = malloc(sizeof(struct user_node));
    current->next_user->user_address = address;
    strcpy(current->next_user->user_name, name);
    current->next_user->next_user = NULL;
    current->next_user->users_channels = malloc(sizeof(struct channel_node));
    strcpy(current->next_user->users_channels->channel_name,"Common");
    current->next_user->users_channels->next_channel = NULL;
}

//Pushes a channel onto the channellist specified. Also starts the user_list attached to the channel.
void push_channel(struct channel_node* channel_list, char* name, char* first_user, 
    struct sockaddr first_address) {
    struct channel_node* current = channel_list;
    while (current->next_channel != NULL) {
        current = current->next_channel;
    }
    /* now we can add a new variable */
    current->next_channel = malloc(sizeof(struct channel_node));
    strcpy(current->next_channel->channel_name, name);
    current->next_channel->next_channel = NULL;
    current->next_channel->channels_users = malloc(sizeof(struct user_node));
    strcpy(current->next_channel->channels_users->user_name, "Server");
    current->next_channel->channels_users->next_user = malloc(sizeof(struct user_node));
    strcpy(current->next_channel->channels_users->next_user->user_name, first_user);
    current->next_channel->channels_users->next_user->user_address = first_address;
}

//Deletes the user from the user list. We cannot delete the first node, which is the Server node.
void delete_user_from_user_list(struct user_node** user_list, char* name) {
    struct user_node* current = *user_list;
    struct user_node* temp_node = NULL;
    while (current->next_user != NULL) {
        if (strcmp(current->next_user->user_name, name) == 0) {
            temp_node = current->next_user;
            current->next_user = temp_node->next_user;
            //destroy_channels(temp_node->users_channels);
            free(temp_node);
            printf("Deleted a user\n");
            break;
        }
        if(current->next_user == NULL){
            break;
        } else {
            current = current->next_user;
        }
        
    }
}

//Deletes the user from a channel's list, by accessing channel's user_list and calling
//delete_user_from_user_list.
void delete_user_from_channel_list(struct channel_node* channel_list, char* name){
    struct channel_node* current = channel_list;
    while(current != NULL){
        printf("entering channel %s\n", current->channel_name);
        delete_user_from_user_list(&(current->channels_users), name);
        if(current->channels_users->next_user == NULL && strcmp(current->channel_name, "Common")!=0){
            delete_channel_from_channel_list(&channel_list, current->channel_name);
            current = channel_list;
        } else {
            current = current->next_channel;
        }
        
    } 
}

//Pushes user to a channel's user list, by accessing channel's user list and calling push_user
void push_user_to_channel_list(struct channel_node* channel_list, char* channel_name, char* user_name, 
    struct sockaddr address){
    struct channel_node* current = channel_list;
    while(current != NULL){
        if(strcmp(current->channel_name, channel_name)==0){
            push_user(current->channels_users, user_name, address);
            break;
        }
        current = current->next_channel;
    }
}

//Pushes channel to a user's channel list, bt accessing user's channel list and calling push_channel.
void push_channel_to_user_list(struct user_node* user_list, char* channel_name, char* user_name, 
    struct sockaddr user_address){
    struct user_node* current = user_list;
    while(current != NULL){
        if(strcmp(current->user_name, user_name)==0){
            push_channel(current->users_channels, channel_name, user_name, user_address);
            break;
        }
        current = current->next_user;
    }
}

//Delete channel from the channel list. We cannot delete the first node, which is always "Common."
void delete_channel_from_channel_list(struct channel_node** channel_list, char* name) {
    struct channel_node* current = *channel_list;
    struct channel_node* temp_node = NULL;
    if(strcmp(name, "Common") == 0){
        printf("You cannot delete channel common");
    } else {
        while (current->next_channel != NULL) {
            if (strcmp(current->next_channel->channel_name, name) == 0) {
                temp_node = current->next_channel;
                current->next_channel = temp_node->next_channel;
                //destroy_users(current->channels_users);
                free(temp_node);
                printf("Deleted a channel");
            }
        if(current->next_channel == NULL){
            break;
        } else {
            current = current->next_channel;
        }
        
        }
    }
    
    printf("No channel deleted");
}

//Deletes channel from a user's list, by accessing channel's user_list anc calling
//delete_channel_from_channel_list
void delete_channel_from_user_list(struct user_node* user_list, char* name){
    struct user_node* current = user_list;
    while(current != NULL){
        delete_channel_from_channel_list(&(current->users_channels), name);
        current = current->next_user;
    }
} 

void add_simple_channel(struct simple_channel_node* list, char* name){
    struct simple_channel_node* current = list;
    while(current->next_channel != NULL){
        current = current->next_channel;
    }
    current->next_channel = malloc(sizeof(struct simple_channel_node));
    strcpy(current->next_channel->channel_name, name);
    current->next_channel->next_channel = NULL;
}

void delete_simple_channel(struct simple_channel_node* list, char* name){
    struct simple_channel_node* current = list;
    struct simple_channel_node* temp;
    //Currently cannot delete Common
    while(current->next_channel != NULL){
        if(strcmp(current->next_channel->channel_name, name) == 0){
            temp = current->next_channel;
            current->next_channel = temp->next_channel;
            free(temp);
            break;
        }
        current = current->next_channel;
    }
}