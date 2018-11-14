#!/usr/bin/python3

import dpkt
import socket


check_string = ""
old_ip = ""
new_ip = ""

with open('log.pcap', 'rb') as f:

	pcap = dpkt.pcap.Reader(f)
	for timestamp, buf in pcap:
		eth = dpkt.ethernet.Ethernet(buf)

		if not isinstance(eth.data, dpkt.ip.IP):
			continue
		ip = eth.data
		if isinstance(ip.data, dpkt.udp.UDP):
			continue
		tcp = ip.data
		new_ip = socket.inet_ntoa(ip.src)
		if((tcp.flags & dpkt.tcp.TH_SYN) and not (tcp.flags & dpkt.tcp.TH_ACK)): #SYN packet
			check_string = "s"
			old_ip = socket.inet_ntoa(ip.src)
		if((tcp.flags & dpkt.tcp.TH_SYN) and (tcp.flags & dpkt.tcp.TH_ACK) and check_string == "s" and old_ip == new_ip): #SYN-ACk packet
			check_string += "a"
		if((tcp.flags & dpkt.tcp.TH_RST) and (check_string == "s" or check_string == "sa") and old_ip == new_ip): #Reset packet
			check_string = ""
			print (socket.inet_ntoa(ip.src))
