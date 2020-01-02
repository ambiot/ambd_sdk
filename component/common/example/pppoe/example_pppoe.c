#include <platform_opts.h>

#if CONFIG_EXAMPLE_PPPOE
#include <FreeRTOS.h>
#include <task.h>
#include <platform/platform_stdlib.h>
#include <lwip_netconf.h>

#define PPPOE_USER      "user"
#define PPPOE_PASSWD    "password"

#if LWIP_VERSION_MAJOR >= 2
#include "netif/ppp/ppp_impl.h"
#include "netif/ppp/pppapi.h"
#include "netif/ppp/pppoe.h"
#include "lwip/dns.h"

#if !PPP_SUPPORT || !PPPOE_SUPPORT || !PAP_SUPPORT || !CHAP_SUPPORT || !EAP_SUPPORT
#error "Please enable PPP_SUPPORT &&  PPPOE_SUPPORT && PAP_SUPPORT && CHAP_SUPPORT && EAP_SUPPORT in lwipopts.h"
#endif

extern struct netif xnetif[];

/* The PPP control block */
ppp_pcb *ppp;
/* The PPP IP interface */
struct netif ppp_netif;

/* PPP status callback example */
static void status_cb(ppp_pcb *pcb, int err_code, void *ctx) {
	struct netif *pppif = ppp_netif(pcb);
	LWIP_UNUSED_ARG(ctx);

	switch(err_code) {
		case PPPERR_NONE: {
#if LWIP_DNS
			const ip_addr_t *ns;
#endif /* LWIP_DNS */
			printf("status_cb: Connected\n");
#if PPP_IPV4_SUPPORT
			printf("   our_ipaddr  = %s\n", ipaddr_ntoa(&pppif->ip_addr));
			printf("   his_ipaddr  = %s\n", ipaddr_ntoa(&pppif->gw));
			printf("   netmask     = %s\n", ipaddr_ntoa(&pppif->netmask));
#if LWIP_DNS
			ns = dns_getserver(0);
			printf("   dns1        = %s\n", ipaddr_ntoa(ns));
			ns = dns_getserver(1);
			printf("   dns2        = %s\n", ipaddr_ntoa(ns));
#endif /* LWIP_DNS */
#endif /* PPP_IPV4_SUPPORT */
#if PPP_IPV6_SUPPORT
			printf("   our6_ipaddr = %s\n", ip6addr_ntoa(netif_ip6_addr(pppif, 0)));
#endif /* PPP_IPV6_SUPPORT */
			break;
		}
		case PPPERR_PARAM: {
			printf("status_cb: Invalid parameter\n");
			break;
		}
		case PPPERR_OPEN: {
			printf("status_cb: Unable to open PPP session\n");
			break;
		}
		case PPPERR_DEVICE: {
			printf("status_cb: Invalid I/O device for PPP\n");
			break;
		}
		case PPPERR_ALLOC: {
			printf("status_cb: Unable to allocate resources\n");
			break;
		}
		case PPPERR_USER: {
			printf("status_cb: User interrupt\n");
			break;
		}
		case PPPERR_CONNECT: {
			printf("status_cb: Connection lost\n");
			break;
		}
		case PPPERR_AUTHFAIL: {
			printf("status_cb: Failed authentication challenge\n");
			break;
		}
		case PPPERR_PROTOCOL: {
			printf("status_cb: Failed to meet protocol\n");
			break;
		}
		case PPPERR_PEERDEAD: {
			printf("status_cb: Connection timeout\n");
			break;
		}
		case PPPERR_IDLETIMEOUT: {
			printf("status_cb: Idle Timeout\n");
			break;
		}
		case PPPERR_CONNECTTIME: {
			printf("status_cb: Max connect time reached\n");
			break;
		}
		case PPPERR_LOOPBACK: {
			printf("status_cb: Loopback detected\n");
			break;
		}
		default: {
			printf("status_cb: Unknown error code %d\n", err_code);
			break;
		}
	}

	/*
	* This should be in the switch case, this is put outside of the switch
	* case for example readability.
	*/

	if (err_code == PPPERR_NONE) {
		return;
	}

	/* ppp_close() was previously called, don't reconnect */
	if (err_code == PPPERR_USER) {
		/*
		* Freeing a PPP connection
		* ========================
		*/

		/*
		* Free the PPP control block, can only be called if PPP session is in the
		* dead state (i.e. disconnected). You need to call ppp_close() before.
		*/
		ppp_free(ppp);
		return;
	}

	/*
	* Try to reconnect in 30 seconds, if you need a modem chatscript you have
	* to do a much better signaling here ;-)
	*/
	ppp_connect(pcb, 30);
	/* OR ppp_listen(pcb); */
}

static void example_pppoe_thread(void *param)
{
	int ppp_desc = -1;

	// Delay to wait for IP by DHCP
	vTaskDelay(10000);

	printf("\n Example: PPPOE\n");
	xnetif[0].flags &= ~(NETIF_FLAG_ETHARP | NETIF_FLAG_IGMP); /* no ARP */
	xnetif[0].flags |= NETIF_FLAG_ETHERNET;                    /* pure ethernet */

	/*
	 * Create a new PPPoE interface
	 *
	 * ppp_netif, netif to use for this PPP link, i.e. PPP IP interface
	 * ethif, already existing and setup Ethernet interface to use
	 * service_name, PPPoE service name discriminator (not supported yet)
	 * concentrator_name, PPPoE concentrator name discriminator (not supported yet)
	 * status_cb, PPP status callback, called on PPP status change (up, down, ??)
	 * ctx_cb, optional user-provided callback context pointer
	 */
	ppp = pppoe_create(&ppp_netif,
	       &xnetif[0],
	       NULL, NULL,
	       status_cb, NULL);

	/*
	 * Initiate PPP client connection
	 * ==============================
	 */

	/* Set this interface as default route */
	ppp_set_default(ppp);

	/*
	 * Basic PPP client configuration. Can only be set if PPP session is in the
	 * dead state (i.e. disconnected). We don't need to provide thread-safe
	 * equivalents through PPPAPI because those helpers are only changing
	 * structure members while session is inactive for lwIP core. Configuration
	 * only need to be done once.
	 */

	/* Ask the peer for up to 2 DNS server addresses. */
	ppp_set_usepeerdns(ppp, 1);

	/* Auth configuration, this is pretty self-explanatory */
	ppp_set_auth(ppp, PPPAUTHTYPE_ANY, PPPOE_USER, PPPOE_PASSWD);

	/*
	 * Initiate PPP negotiation, without waiting (holdoff=0), can only be called
	 * if PPP session is in the dead state (i.e. disconnected).
	 */
	u16_t holdoff = 0;
	ppp_connect(ppp, holdoff);

	if(ppp_desc >= 0) {
		while(1) {
			int if_up = 0;
			ppp_ioctl(ppp, PPPCTLG_UPSTATUS, &if_up);
			if(if_up)
				break;
			else
				vTaskDelay(1000);
		}

		printf("Close PPPOE after 10 seconds\n");
		vTaskDelay(10000);
		/*
		 * Closing PPP connection
		 * ======================
		 */

		/*
		 * Initiate the end of the PPP session, without carrier lost signal
		 * (nocarrier=0), meaning a clean shutdown of PPP protocols.
		 * You can call this function at anytime.
		 */
		u8_t nocarrier = 0;
		ppp_close(ppp, nocarrier);
		/*
		 * Then you must wait your status_cb() to be called, it may takes from a few
		 * seconds to several tens of seconds depending on the current PPP state.
		 */
	}

exit:
	vTaskDelete(NULL);
}

#else

#include <../netif/ppp/ppp_impl.h>
#include <netif/ppp_oe.h>

extern struct netif xnetif[];

void pppLinkStatusCallback(void *ctx, int errCode, void *arg)
{
	switch(errCode) {
		case PPPERR_NONE: {
			struct ppp_addrs *ppp_addrs = arg;
			printf("pppLinkStatusCallback: PPPERR_NONE\n");
			printf(" our_ipaddr=%s\n", ip_ntoa(&ppp_addrs->our_ipaddr));
			printf(" his_ipaddr=%s\n", ip_ntoa(&ppp_addrs->his_ipaddr));
			printf(" netmask   =%s\n", ip_ntoa(&ppp_addrs->netmask));
			printf(" dns1      =%s\n", ip_ntoa(&ppp_addrs->dns1));
			printf(" dns2      =%s\n", ip_ntoa(&ppp_addrs->dns2));
			dns_setserver(0, &ppp_addrs->dns1);
			dns_setserver(1, &ppp_addrs->dns2);
			break;
		}
		default:
			printf("pppLinkStatusCallback: errCode(%d)\n", errCode);
			break;
	}
}

static void example_pppoe_thread(void *param)
{
	int ppp_desc = -1;

	// Delay to wait for IP by DHCP
	vTaskDelay(10000);
	printf("\nExample: PPPOE\n");

	xnetif[0].flags &= ~(NETIF_FLAG_ETHARP | NETIF_FLAG_IGMP); /* no ARP */
	xnetif[0].flags |= NETIF_FLAG_ETHERNET;                    /* pure ethernet */

	pppInit();
	pppSetAuth(PPPAUTHTYPE_ANY, PPPOE_USER, PPPOE_PASSWD);
	ppp_desc = pppOverEthernetOpen(&xnetif[0], NULL, NULL, pppLinkStatusCallback, NULL);

	if(ppp_desc >= 0) {
		while(1) {
			int if_up = 0;
			pppIOCtl(ppp_desc, PPPCTLG_UPSTATUS, &if_up);
			if(if_up)
				break;
			else
				vTaskDelay(1000);
		}

		printf("Close PPPOE after 10 seconds\n");
		vTaskDelay(10000);
		pppClose(ppp_desc);
	}

exit:
	vTaskDelete(NULL);
}

#endif

void example_pppoe(void)
{
	if(xTaskCreate(example_pppoe_thread, ((const char*)"example_pppoe_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(init_thread) failed", __FUNCTION__);
}

#endif /* CONFIG_EXAMPLE_PPPOE */