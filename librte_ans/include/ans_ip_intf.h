/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2015-2017 Ansyun <anssupport@163.com>. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Ansyun <anssupport@163.com> nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*-
 * Copyright (c) 1982, 1986, 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following edsclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following edsclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE EDSCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef __ANS_IP_INTF_H__ 
#define __ANS_IP_INTF_H__

/**
 * @file
 *
 * ANS IP API defines.
 *
 */

/*
 *  define queue id
*/
struct ans_qmaping
{
    uint8_t lcore_id;
    uint8_t queue_id;
};

/*
 *  define queue to lcore mapping of port. 
*/

struct ans_port_queue
{
    uint8_t rxq_nb;
    struct ans_qmaping rx_qmapping[ANS_MAX_NB_LCORE];

    uint8_t txq_nb;
    struct ans_qmaping tx_qmapping[ANS_MAX_NB_LCORE];
};

 /**
 * Handle the received packets by ans stack
 *
 * @param portid  
 *    port id.
 * @param rx_pkts 
 *    packet buffer array. 
 * @param nb_pkts  
 *    packets number.
 *
 * @return  void
 *
 */
void ans_eth_rx_burst(uint8_t portid, struct rte_mbuf **rx_pkts, const uint16_t nb_pkts);

/**
 * Send packets in the buffer.
 *
 * @param port_id  
 *    port id.
 *
 * @return  
 *
 */
 void ans_eth_tx_flush(uint16_t port_id);

/**
 * Statistics dropped packets by port
 *
 * @param portid  
 *    port id.
 * @param packets_nb 
 *    droped packets number. 
 *
 * @return  
 *
 */
void ans_eth_stats(uint8_t portid, uint16_t packets_nb, uint16_t droped_nb);

/**
 * Add an interface.
 *
 * @param port      
 *   port of the interface 
 * @param kni_index      
 *   kni index in kernel 
 * @param if_name   
 *   name of the interface 
 * @param mac_addr  
 *   mac address of the interface
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_iface_add(uint8_t port, uint16_t kni_index, char *if_name, struct rte_ether_addr *mac_addr);

/**
 * Delete an interface.
 *
 * @param if_name  
 *    name of the interface 
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_iface_delete(char *if_name);

/**
 * Retrieves MTU value for an interface.
 *
 * @param name      
 *   name of the interface for which the MTU is retrieved
 * @param mtu 
 *   value of retrieved MTU
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_iface_get_mtu(char *if_name, uint16_t *mtu);


/**
 * Set MTU value for an interface.
 *
 * @param name    
 *   name of the interface for which the MTU is set
 * @param mtu  
 *   value of MTU to be set
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_iface_set_mtu(char *if_name, uint16_t mtu);

/**
 * Retrieves rx queue to lcore mapping for an interface.
 *
 * @param name      
 *   name of the interface for which the queue mapping is retrieved
 * @param port_queue 
 *   retrieved tx/rx queue of the port.
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_iface_get_queue(char *if_name, struct ans_port_queue *port_queue);


/**
 * Set rx queue to lcore mapping for an interface.
 *
 * @param name      
 *   name of the interface for which the queue mapping is retrieved
 * @param port_queue 
 *   tx/rx queue of the port.
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_iface_set_queue(char *if_name, struct ans_port_queue *port_queue);

/**
 * Routing table addition.
 *
 * @param dest_ipaddr  
 *   ip address of the destination for which the route is being added, host byte order
 * @param gateway_addr 
 *   ip address of gateway, host byte order
 * @param netmask   
 *   netmask to be used with route
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_add_route(uint32_t dest_ipaddr, uint8_t netmask, uint32_t gateway_addr);

/**
 * Routing table deletion.
 *
 * @param dest_ipaddr  
 *   ip address of the destination for which the route is being deleted, host byte order.
 * @param netmask   
 *   netmask to be used with route
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_del_route(uint32_t dest_ipaddr, uint8_t netmask);

/**
 * Show ANS routing table.
 *
 *
 * @return  
 *
 */
 void ans_show_route(void);

/**
 * Add IP address on a interface.
 *
 * @param ifname  
 *   interface name
 * @param ip_addr   
 *   IP address, host byte order
 * @param netmask
 *   netmask length
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_add_ipaddr(char *ifname, uint32_t ip_addr, uint8_t netmask);

/**
 * Delete IP address on a interface.
 *
 * @param ifname  
 *   interface name
 * @param ip_addr   
 *   IP address, host byte order
 * @param netmask
 *   netmask length
 *
 * @return  0 - SUCCESS, non-zero - FAILURE
 *
 */
int ans_del_ipaddr(char *ifname, uint32_t ip_addr, uint8_t netmask);

/**
 * Show all IP address on all interface.
 *
 *
 * @return  
 *
 */
void ans_show_ipaddr(void);


#endif 
