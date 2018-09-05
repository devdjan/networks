#include <stdio.h>              // i/o
#include <stdlib.h>             //
#include <getopt.h>             //
#include <string.h>             //
#include <limits.h>             //
#include <fcntl.h>              //
#include <sys/types.h>          //
#include <sys/socket.h>         //
#include <arpa/inet.h>          //
#include <net/if.h>             //
#include <net/ethernet.h>       //
#include <netinet/if_ether.h>   //
#include <netinet/in.h>         //

//include firewall_v1.h - for external libs, constants

/* global variables */
char option_string[] = {PROTOCOL,      ':',
                        SRC_IPADDR,    ':',
                        DEST_IPADDR,   ':',
                        SRC_PORT,      ':',
                        DEST_PORT,     ':',
                        SRC_NET_MASK,  ':',
                        DEST_NET_MASK, ':',
                        ACTION,        ':',
                        PERMIT,        ':',
                        DELETE,        ':',
                        PRINT,         '\0'

};

int global_fd = 0;
int in_out_flag = INT_MAX;    // flag to check whether the rule is for inbound pr outbound packets
char inbound[] = "in";
char outbound[] = "out";

/* function headers */
void Convert_To_Lower_Case(const char *argv, char *str);
void Set_Hook_Entry(my_iptable *my_ipt, char *optarg);
void Set_IP(const char *optarg, unsigned char is_source, my_iptable *my_ipt);
void Set_Net_Mask(const char *optarg, unsigned char is_source, my_iptable *my_ipt);
void Set_Port(const char *optarg, unsigned char is_source, my_iptable *my_ipt);
void Set_Protocol(const char *optarg, my_iptable *my_ipt);
void Set_Action(const char *optarg, my_iptable, *my_ipt);
void Parse_Rules(const my_iptable *my_ipt);
void Delete_Rule(const int *fd, const char *optarg, my_iptable *my_ipt);
void Permit_User(const int *fd, const char *optarg, const int optind,
                 const int argc, char *const argv[], my_iptable *my_ipt);
void Error_Handler(const int fd, my_iptable *my_ipt);
void Read_From_Proc(int *fd);


int main() {
  const char *errstr;     // character constant;
  int opt;                // integer
  my_iptable *my_ipt = NULL;
  my_ipt = (my_iptable *)malloc(sizeof(my_iptable));
  memset(my_ipt, '\0', sizeof(my_iptable));           // fills block of memory
  //1(pointer to the block of memory);2(value to be set);3(number of bytes to be set my_iptable - size)

  int fd = open("/proc/minifw", O_WRONGLY, O_APPEND);
  if (fd < 0) {
    fprintf(stderr, "%s\n", "Error: in opening /proc/minifw file. Please check if it is registered in /proc\n");
    return 1;
    // why use fprintf instead of printf | sprintf ?
    // printf("format", args) - outputs to the standard ouput stream (stdout)
    // fprinf(FILE *fp, "format", args) - goes to a file handle (FILE *)
    // sprintf(char *, 'format', args) - goes to a buffer you allocated (char *)
  }
  global_fd = fd;
  while(1) {
    static struct option long_options[] = {
      {"out",             no_argument,                &in_out_flag, 1},
      {"it",              no_argument,                &in_out_flag, 0},
      {"proto",           required_argument,      0,         PROTOCOL},
      {"srcip",           required_argument,      0,       SRC_IPADDR},
      {"destip",          required_argument,      0,      DEST_IPADDR},
      {"srcport",         required_argument,      0,         SRC_PORT},
      {"destport",        required_argument,      0,        DEST_PORT},
      {"srcnetmask",      required_argument,      0,     SRC_NET_MASK},
      {"destnetmask",     required_argument,      0,    DEST_NET_MASK},
      {"action",          required_argument,      0,           ACTION},
      {"permit",          required_argument,      0,           PERMIT},
      {"delete",          required_argument,      0,           DELETE},
      {"print",           required_argument,      0,            PRINT},
      {0, 0, 0, 0}
    };

    int option_index = 0;
    opt = getopt_long(argc, argv, option_string, long_options, &option_index);

    if(opt == -1)
      break;

    switch(opt) {
      case 0:
        if(long_options[option_index].flag != 0)    // means that flag has been set
          break;

    if(optarg)
    printf("\n");
    break;

      case PROTOCOL:
        //set smth
        break;

      case SRC_IPADDR:
        //set smth
        break;

      case DEST_IPADDR:
        //set smth
        break;

      case SRC_PORT:
        //set smth
        break;

      case DEST_PORT:
        //set smth
        break;

      case SRC_NET_MASK:
        //set smth
        break;

      case DEST_NET_MASK:
        //set smth
        break;

      case ACTION:
        //set smth
        break;

      case PERMIT:
        //set smth
        break;

      case DELETE:
        //set smth
        break;

      case PRINT:
        //set smth
        break;
    }





  }



}







//d
