#include <iostream>
#include <fstream>
#include "ns3/point-to-point-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Exer3");

PointToPointHelper* CreatePointToPointHelper(NodeContainer nodes, std::string dataRate, std::string delay) {
    PointToPointHelper *pointToPoint_p =  new PointToPointHelper;
    pointToPoint_p->SetDeviceAttribute("DataRate", StringValue(dataRate));
    pointToPoint_p->SetChannelAttribute("Delay", StringValue(delay));
    return pointToPoint_p;
}

Ipv4InterfaceContainer CreateIpv4InterfaceContainer(NetDeviceContainer devices, Ipv4Address network, Ipv4Mask mask) {
    Ipv4AddressHelper *address_p = new Ipv4AddressHelper;
    address_p->SetBase(network, mask);
    return address_p->Assign(devices);
}

UdpServerHelper* CreateUdpServerHelper(uint16_t port) {
    return new UdpServerHelper(port);
}

UdpClientHelper* CreateUdpClientHelper(Address destIp, uint16_t port, uint32_t maxPackets, uint32_t packetSize, Time interval) {
    UdpClientHelper *echoClient_p = new UdpClientHelper(destIp, port);
    echoClient_p->SetAttribute("MaxPackets", UintegerValue(maxPackets));
    echoClient_p->SetAttribute("PacketSize", UintegerValue(packetSize));
    echoClient_p->SetAttribute("Interval", TimeValue(interval));
    return echoClient_p;
}

int main(int argc, char *argv[]) {
    /* Enable logging for UdpClient and UdpServer */
    LogComponentEnable("UdpClient", LOG_LEVEL_INFO);
    LogComponentEnable("UdpServer", LOG_LEVEL_INFO);

    /* Get command line arguments */
    CommandLine cmd;
    cmd.Parse(argc, argv);

    /* Create a node container */
    NodeContainer nodes;
    nodes.Create(2);

    /* Create a point to point */
    PointToPointHelper *pointToPoint_p = CreatePointToPointHelper(nodes, "5Mbps", "10us");

    /* Create a netdevice container */
    NetDeviceContainer netDevices = pointToPoint_p->Install(nodes);

    /* Install a protocol stack on nodes */
    InternetStackHelper internetStack;
    internetStack.Install(nodes);

    /* Allocate IP addresses */
    Ipv4InterfaceContainer interfaces = CreateIpv4InterfaceContainer(netDevices, "10.1.1.0", "255.255.255.0");

    /* Create udpServer application */
    uint16_t port = 9;

    ApplicationContainer serverApps;
    serverApps.Add(CreateUdpServerHelper(port)->Install(nodes.Get(1)));
    serverApps.Start(Seconds(0));
    serverApps.Stop(Seconds(10));

    /* Create a UdpClient application to send UDP datagrams from node0 to node1 */
    Address serverIp = interfaces.GetAddress(1);
    uint32_t maxPacketCount = 100000;
    uint32_t packetSize = 1500;
    Time interval = Seconds(0.0025);

    ApplicationContainer clientApps;
    clientApps.Add(CreateUdpClientHelper(serverIp, port, maxPacketCount, packetSize, interval)->Install(nodes.Get(0)));
    clientApps.Start(Seconds(1));
    clientApps.Stop(Seconds(10));

    /* Enable pcap tracing */
    pointToPoint_p->EnablePcapAll("Exercise3");

    /* Running a simulator */
    Simulator::Run();
    Simulator::Destroy();
}
