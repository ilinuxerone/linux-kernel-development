
/*
 * reference the  drivers\net\cs89x0.c and drivers/net/dm9000.c
 */

#include <linux/module.h>
#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/skbuff.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/ip.h>

#include <asm/system.h>
#include <asm/io.h>
#include <asm/irq.h>

static struct net_device *vnet_dev;


static void emulator_rx_packet(struct sk_buff *skb, struct net_device  *dev)
{
	unsigned char  *type;
	struct iphdr   *ih;
	struct ethhdr  *ethhdr;
	__be32 *saddr, *daddr, tmp;
	unsigned char tmp_dev_addr[ETH_ALEN];

	struct sk_buff  *rx_skb;

	/*read data from NIC and save data*/
	/*exchange the mac address of source and distination address*/
	ethhdr = (struct ethhdr *)skb->data;
	memcpy(tmp_dev_addr, ethhdr->h_dest, ETH_ALEN);
	memcpy(ethhdr->h_dest, ethhdr->h_source, ETH_ALEN);
	memcpy(ethhdr->h_source, tmp_dev_addr, ETH_ALEN);

	/*exchange the ip address of source and destination address*/
	ih = (struct iphdr *)(skb->data + sizeof(struct ethhdr));
	saddr = &ih->saddr;
	daddr = &ih->daddr;

	tmp = *saddr;
	*saddr = *daddr;
	*daddr = tmp;

	type = skb->data + sizeof(struct ethhdr) + sizeof(struct iphdr);
	*type = 0;

	ih->check = 0;
	ih->check = ip_fast_csum((unsigned char *)ih, ih->ihl);

	/*constuct a skb buffer*/
	rx_skb = dev_alloc_skb(skb->len + 2);
	skb_reserve(rx_skb,2);
	memcpy(skb_put(rx_skb, skb->len), skb->data, skb->len);


	/*write data ,and then pass to the receive level*/
	rx_skb->dev =dev;
	rx_skb->protocol = eth_type_trans(rx_skb, dev);
	rx_skb->ip_summed = CHECKSUM_UNNECESSARY;
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += skb->len;

	/*submit skb buff*/
	netif_rx(rx_skb);
}

static int virt_net_send_packet(struct sk_buff *skb, struct net_device *dev)
{
	static int cnt = 0;
	printk("virt_net_send_packet cnt = %d\n", ++cnt);

	/*for real NIC, send the data in skb out through the NIC */
	netif_stop_queue(dev);  	/*stop the NIC queue*/
	/*......*/			/*write the skb data in NIC*/
	
	/*construct a false skb_buff*/
	emulator_rx_packet(skb, dev);

	netif_wake_queue(dev);		/*wake up the queue on data send out*/

	/* ¸update statistics */
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	
	dev_kfree_skb(skb);		/*free skb buffer*/	
	return 0;
}

static const struct net_device_ops virt_net_ops = {
	.ndo_start_xmit = virt_net_send_packet,
};



static int virt_net_init(void)
{
	/* 1. allocate a struct net_device structure */
	vnet_dev = alloc_netdev(0, "vnet%d", ether_setup);;  /* alloc_etherdev */

	/* 2. set */
	vnet_dev->netdev_ops = &virt_net_ops;

	/* set mac address */
	 vnet_dev->dev_addr[0] = 0x08;
         vnet_dev->dev_addr[1] = 0x89;
         vnet_dev->dev_addr[2] = 0x89;
         vnet_dev->dev_addr[3] = 0x89;
         vnet_dev->dev_addr[4] = 0x89;
         vnet_dev->dev_addr[5] = 0x11;

	/*set flags and features for my emulator_rx_packet function*/
	vnet_dev->flags  	|=  IFF_NOARP;
	vnet_dev->features	|=  NETIF_F_NO_CSUM;

	/* 3. register*/
	//register_netdevice(vnet_dev);
	register_netdev(vnet_dev);
	
	return 0;
}

static void virt_net_exit(void)
{
	unregister_netdev(vnet_dev);
	free_netdev(vnet_dev);
}

module_init(virt_net_init);
module_exit(virt_net_exit);

MODULE_LICENSE("GPL");

