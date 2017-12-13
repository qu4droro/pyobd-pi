#include <stdio.h>
#include <can.h>
#include "cJSON.h"

#define PF_CAN 0
#define SOCK_RAW 005
#define CAN_RAW 606

struct {
  struct bcm_msg_head msg_head;
  struct can_frame frame[5];
} msg;


void build_msg(){
  msg.msg_head.opcode  = RX_SETUP;
  msg.msg_head.can_id  = 0x42;
  msg.msg_head.flags   = 0;
  msg.msg_head.nframes = 5;
  U64_DATA(&msg.frame[0]) = 0xFF00000000000000ULL; /* MUX mask */
  U64_DATA(&msg.frame[1]) = 0x01000000000000FFULL; /* data mask (MUX 0x01) */
  U64_DATA(&msg.frame[2]) = 0x0200FFFF000000FFULL; /* data mask (MUX 0x02) */
  U64_DATA(&msg.frame[3]) = 0x330000FFFFFF0003ULL; /* data mask (MUX 0x33) */
  U64_DATA(&msg.frame[4]) = 0x4F07FC0FF0000000ULL; /* data mask (MUX 0x4F) */
}

void map_ecu(){
  //Incomplete
}

int main() {
  int s;
  int nbytes;
  struct can_frame frame;
  struct sockaddr_can addr;
  struct ifreq ifr;
  socklen_t len = sizeof(addr);
  
  s = socket(PF_CAN, SOCKET_RAW, CAN_RAW)
  
  //Read
  /*nbytes = read(s, &frame, sizeof(struct can_frame));
  if (nbytes < 0) {
    perror("can raw socket read");
    return 1;
  }
  if (nbytes < sizeof(struct can_frame)) {
    fprintf(stderr, "read: incomplete CAN frame\n");
    return 1;
  }*/
  
  
  nbytes = recvfrom(s, &frame, sizeof(struct can_frame), 0, (struct sockaddr*)&addr, &len);

  // get interface name of the received CAN frame
  ifr.ifr_ifindex = addr.can_ifindex;
  //ioctl(s, SIOCGIFNAME, &ifr);
  //printf("Received a CAN frame from interface %s", ifr.ifr_name);
  
  //Write
  //nbytes = write(s, &frame, sizeof(struct can_frame));
  strcpy(ifr.ifr_name, "can0");
  ioctl(s, SIOCGIFINDEX, &ifr);
  addr.can_ifindex = ifr.ifr_ifindex;
  addr.can_family  = AF_CAN;

  nbytes = sendto(s, &frame, sizeof(struct can_frame), 0, (struct sockaddr*)&addr, sizeof(addr));
}
