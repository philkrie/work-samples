#include <pthread.h>
#include <stdio.h>
#include "networkdriver.h"
#include "BoundedBuffer.h"
#include "freepacketdescriptorstore__full.h"
#include "packetdescriptor.h"
#include "packetdescriptorcreator.h"

/*any global variables required for use by threads and driver routines*/
BoundedBuffer *incoming[11];
BoundedBuffer *outgoing;
int i;

/*pthreads objects*/
pthread_t thread_recieving;
pthread_t thread_sending;

struct thread_params {
    /* The fpds */
    FreePacketDescriptorStore *fpds;
    /* The network_device */
    NetworkDevice *nd;
    /* The outgoing buffer */
    BoundedBuffer **incoming;
    /* The incoming buffers */
    BoundedBuffer *outgoing;
};

struct thread_params thread_args;

/*Create recieving function to eventually pass to pthread*/
void* recieving(void* parameters) {
    struct thread_params* p = (struct thread_params*) parameters;
    PacketDescriptor *pd;
    while(1){
        blocking_get_pd(p->fpds, &pd); 
        register_receiving_packetdescriptor(p->nd, pd);
        await_incoming_packet(p->nd);
        if(nonblockingWriteBB(incoming[packet_descriptor_get_pid(pd)], pd) == 0)
            blocking_put_pd(p->fpds, pd);
    }
}

void* sending(void* parameters) {
    struct thread_params* p = (struct thread_params*) parameters;
    PacketDescriptor *pd;
    int i;
    while(1){
        pd = (PacketDescriptor*) blockingReadBB(p->outgoing);
        i = send_packet(p->nd, pd);
        if(i == 1) 
            printf("[DRIVER> Info: Sent a packet\n");
        else
            printf("[DRIVER> Info: Did not send a packet\n");
        blocking_put_pd(p->fpds, pd);
    }
}

void init_network_driver(NetworkDevice *nd, void *mem_start,
			unsigned long mem_length, FreePacketDescriptorStore **fpds) { 
	/* create Free Packet Descriptor Store and load with free packet descriptors */
	*fpds = create_fpds();
    create_free_packet_descriptors(*fpds, mem_start, mem_length);
        
	/*Initializing incoming packet buffer for each app. Each can handle two packets before filling */    
    for(i = 0; i < 11; i++){incoming[i] = createBB(2);}
    printf("Driver: 2 received packet descriptors can be queued for each of 11 applications\n");
    
	/*Initializing outgoing buffer for messages being sent. Can handle 10 packets before filling*/
	outgoing = createBB(10);
    printf("Driver: 10 packet descriptors can be queued for sending\n");    
    
    /*Setting parameters*/
    thread_args.fpds = *fpds;
    thread_args.nd = nd;
    thread_args.incoming = incoming;
    thread_args.outgoing = outgoing;

    /*Creating threads*/
    pthread_create (&thread_recieving, NULL, recieving, &thread_args);
    pthread_create (&thread_sending, NULL, sending, &thread_args);
}

void blocking_send_packet(PacketDescriptor *pd) { 
    blockingWriteBB(outgoing, pd);
}

int nonblocking_send_packet(PacketDescriptor *pd) {
    return nonblockingWriteBB(outgoing, pd);
}

void blocking_get_packet(PacketDescriptor **pd, PID pid) {
    *pd = blockingReadBB(incoming[pid]); 
}

int nonblocking_get_packet(PacketDescriptor **pd, PID pid) {
    return nonblockingReadBB(incoming[pid], (void **) pd);	
}
