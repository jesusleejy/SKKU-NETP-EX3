#include <iostream>
#include <fstream>
#include "ns3/point-to-point-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Exer3");
int
main (int argc, char *argv[])
{
  /* Enable logging for UdpClient and UdpServer */
  LogComponentEnable ("UdpClient", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpServer", LOG_LEVEL_INFO);

  CommandLine cmd;
  cmd.Parse (argc, argv);
 
  /* Create a node container */
  NodeContainer node;
  /* Todo:  Create 2 nodes of p2p link*/


  /* Create a point-to-point link */
  PointToPointHelper p2p;
  /* Todo:   Set datarate and delay for p2p link*/
 
  /* Create a netdevice container */
  NetDeviceContainer netdev;
  
  /* Todo:
  Make a p2p link between two nodes in the node container  
  		using "NetDeviceContainer", "PointToPointHelper", and "nodecontainer"*/

 
  /* Install a protocol stack on nodes */
  InternetStackHelper internet;
  internet.Install (node);
  
  /* Allocate IP addresses */
  Ipv4AddressHelper ipv4;
  Ipv4InterfaceContainer p2pInterfaces;

  /* Todo: allocate IP addresses on netdevicecontainer
           1) set the base address of IP address to be allocated
   		using "SetBase" method of Ipv4AddressHelper 'ipv4',
		   base address "10.1.1.0", and subnet mask "255.255.255.0")
           2) allocate IP address on netdevicecontainer using "Assign" method of Ipv4AddressHelper and Ipv4InterfaceContainer */


  /* Create udpServer application */
  uint16_t port = 9;
  UdpServerHelper server (port);
  ApplicationContainer apps;

  /* Todo: Install UdpServerHelper 'server' on "node1"
   		using ApplicationContainer 'apps', and "install" method of UdpServerHelper 'server'*/

  /* Todo:  Start the server application from 0 to 10 sec */


  /* Create a UdpClient application to send UDP datagrams from node0 to node1 */
  /* Todo: Create a UdpClient using "UdpClientHelper" class 
               hint) 
	          1) UdpClientHelper client (server IP address, server port number); 
		  2) Get server IP from Ipv4InterfaceContainer "p2pInterfaces"*/


  /* Set maximum number of packets the application will send */
  uint32_t maxPacketCount = 100000; // underlying type of MaxPackets: uint32_t
  client.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));

  /* Todo: Set packet interval as 'Seconds (0.0025)' and packetsize as 1500 -> about 5Mbps*/
 
  /* Todo:  Start the client application from 1 to 10 sec */

  /* Enable pcap tracing */
  p2p.EnablePcapAll("exer3_pcap");

  /* Running a simulator */
  Simulator::Run ();
  Simulator::Destroy ();
}
