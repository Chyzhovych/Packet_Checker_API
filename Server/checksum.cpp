 #include "checksum.hpp"
 #include <stdio.h>

//type:
        //      1=udp
        //      2=tcp

 uint16_t checksum(uint8_t *buf, uint16_t len, uint8_t type)
{

        uint32_t sum = 0;

        if(type==1){
                sum += IP_PROTO_UDP_V; // protocol udp
                // the length here is the length of udp (data+header len)
                // =length given to this function - (IP.scr+IP.dst length)
                sum+=len-8; // = real tcp len
        }
        if(type==2){
                sum+=IP_PROTO_TCP_V; 
                // the length here is the length of tcp (data+header len)
                // =length given to this function - (IP.scr+IP.dst length)
                sum+=len-8; // = real tcp len
        }
        // build the sum of 16bit words
        while(len >1){
                sum += 0xFFFF & (*buf<<8|*(buf+1));
                buf+=2;
                len-=2;
        }
        // if there is a byte left then add it (padded with zero)
        if (len){
//--- made by SKA ---                sum += (0xFF & *buf)<<8;
                sum += 0xFFFF & (*buf<<8|0x00);
        }
        // now calculate the sum over the bytes in the sum
        // until the result is only 16bit long
        while (sum>>16){
                sum = (sum & 0xFFFF)+(sum >> 16);
        }
        // build 1's complement:
        return( (uint16_t) sum ^ 0xFFFF);
}

void calculateChecksum(uint8_t *buf)
{
        uint16_t ck;
        // clear the 2 byte checksum
        buf[IP_CHECKSUM_P] = 0;
        buf[IP_CHECKSUM_P+1] = 0;
        buf[IP_FLAGS_P] = 0x40; // don't fragment
        buf[IP_FLAGS_P + 1] = 0;  // fragement offset
        buf[IP_TTL_P] = 64; // ttl
        
        // calculate the checksum:
        ck = checksum(&buf[IP_P], IP_HEADER_LEN_V,0);
        buf[IP_CHECKSUM_P] = ck >> 8;
        buf[IP_CHECKSUM_P+1] = ck & 0xff;
        printf("CRC: %d \n", ck);
}