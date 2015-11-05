#ifndef LINKED_LIST_H
#define LINKED_LIST_H

//Linked list structure
struct user_node {
    struct sockaddr user_address; //How we know where to send the message
    char user_name[USERNAME_MAX]; //Name of the user
    struct user_node* next_user; //Next user in the linked list
    struct channel_node* users_channels; //Channels that the user is subbed to.
};

struct channel_node {
    char channel_name[CHANNEL_MAX]; //name of the channel
    struct channel_node* next_channel; //Next channel in the list.
    struct user_node* channels_users; //Users that subscribe to the channel
};

struct simple_channel_node {
    char channel_name[CHANNEL_MAX];
    struct simple_channel_node* next_channel;
};

void destroy_users(struct user_node *);
void destroy_channels(struct channel_node *);
void push_user(struct user_node* user_list, char* name, struct sockaddr address);
void push_channel(struct channel_node* channel_list, char* name, char* first_user, struct sockaddr first_address);
void delete_user_from_user_list(struct user_node** user_list, char* name);
void delete_user_from_channel_list(struct channel_node* channel_list, char* name);
void push_user_to_channel_list(struct channel_node* channel_list, char* channel_name, char* user_name, struct sockaddr address);
void push_channel_to_user_list(struct user_node* user_list, char* channel_name, char* user_name, struct sockaddr user_address);
void delete_channel_from_channel_list(struct channel_node** channel_list, char* name) ;
void delete_channel_from_user_list(struct user_node* user_list, char* name);
void add_simple_channel(struct simple_channel_node* list, char* name);
void delete_simple_channel(struct simple_channel_node* list, char* name);

#endif