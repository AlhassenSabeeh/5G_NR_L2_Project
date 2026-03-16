#include "ip_packet_generator.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <arpa/inet.h>

/**
 * @file ip_packet_generator_example.cpp
 * @brief Example program demonstrating the IP Dummy Packet Generator
 * 
 * This program demonstrates how to use the IPPacketGenerator class to
 * generate IP packets with various configurations and payload sizes.
 */

/**
 * @brief Print an IP address in dotted decimal notation
 * @param ip_addr IP address in network byte order
 */
void printIpAddress(uint32_t ip_addr) {
    struct in_addr addr;
    addr.s_addr = ip_addr;
    std::cout << inet_ntoa(addr);
}

/**
 * @brief Print the contents of a packet in hexadecimal format
 * @param packet The packet data to print
 * @param max_bytes Maximum number of bytes to print (0 = all)
 */
void printPacketHex(const std::vector<uint8_t>& packet, size_t max_bytes = 0) {
    size_t bytes_to_print = (max_bytes == 0) ? packet.size() : std::min(max_bytes, packet.size());
    
    for (size_t i = 0; i < bytes_to_print; ++i) {
        if (i % 16 == 0 && i > 0) {
            std::cout << std::endl;
        }
        std::cout << std::setfill('0') << std::setw(2) << std::hex 
                  << static_cast<int>(packet[i]) << " ";
    }
    std::cout << std::dec << std::endl;
}

/**
 * @brief Parse and display the IP header information
 * @param packet The packet containing the IP header
 */
void printPacketInfo(const std::vector<uint8_t>& packet) {
    if (packet.size() < 20) {
        std::cout << "Error: Packet too small to contain IP header" << std::endl;
        return;
    }

    // Extract header fields
    const IPHeader* header = reinterpret_cast<const IPHeader*>(packet.data());

    std::cout << "IP Header Information:" << std::endl;
    std::cout << "  Version: " << static_cast<int>(header->version_ihl >> 4) << std::endl;
    std::cout << "  Header Length: " << static_cast<int>((header->version_ihl & 0x0F) * 4) << " bytes" << std::endl;
    std::cout << "  Total Length: " << ntohs(header->total_length) << " bytes" << std::endl;
    std::cout << "  Identification: " << ntohs(header->identification) << std::endl;
    std::cout << "  TTL: " << static_cast<int>(header->ttl) << std::endl;
    std::cout << "  Protocol: " << static_cast<int>(header->protocol) << " (";
    
    switch (header->protocol) {
        case 6:
            std::cout << "TCP";
            break;
        case 17:
            std::cout << "UDP";
            break;
        case 1:
            std::cout << "ICMP";
            break;
        default:
            std::cout << "Other";
            break;
    }
    std::cout << ")" << std::endl;
    
    std::cout << "  Source IP: ";
    printIpAddress(header->src_ip);
    std::cout << std::endl;
    
    std::cout << "  Destination IP: ";
    printIpAddress(header->dst_ip);
    std::cout << std::endl;
    
    std::cout << "  Checksum: 0x" << std::hex << ntohs(header->checksum) << std::dec << std::endl;
    std::cout << "  Payload Size: " << (ntohs(header->total_length) - 20) << " bytes" << std::endl;
}

/**
 * @brief Main function demonstrating various use cases
 */
int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "IP Dummy Packet Generator - Example Program" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;

    // Example 1: Basic packet generation
    std::cout << "Example 1: Generate a single packet with 100-byte payload" << std::endl;
    std::cout << "---" << std::endl;
    
    // Create a generator instance
    // Source IP: 192.168.1.1 (0xC0A80101)
    // Destination IP: 192.168.1.100 (0xC0A80164)
    // Protocol: UDP (17)
    // TTL: 64
    uint32_t src_ip = inet_addr("192.168.1.1");
    uint32_t dst_ip = inet_addr("192.168.1.100");
    
    IPPacketGenerator generator(src_ip, dst_ip, 17, 64);
    
    std::vector<uint8_t> packet1 = generator.generatePacket(100);
    std::cout << "Generated Packet 1 Size: " << packet1.size() << " bytes" << std::endl;
    printPacketInfo(packet1);
    std::cout << std::endl;

    // Example 2: Generate multiple packets with different sizes
    std::cout << "Example 2: Generate multiple packets with different payload sizes" << std::endl;
    std::cout << "---" << std::endl;
    
    uint16_t payload_sizes[] = {50, 100, 200, 500, 1000};
    
    for (uint16_t size : payload_sizes) {
        std::vector<uint8_t> packet = generator.generatePacket(size);
        std::cout << "Payload Size: " << std::setw(4) << size << " bytes | "
                  << "Total Packet Size: " << std::setw(4) << packet.size() << " bytes" << std::endl;
    }
    std::cout << std::endl;

    // Example 3: Change generator settings
    std::cout << "Example 3: Change generator settings (TCP protocol, TTL=128)" << std::endl;
    std::cout << "---" << std::endl;
    
    generator.setProtocol(6);  // TCP
    generator.setTtl(128);
    
    std::vector<uint8_t> packet3 = generator.generatePacket(256);
    printPacketInfo(packet3);
    std::cout << std::endl;

    // Example 4: Generate multiple packets at once
    std::cout << "Example 4: Generate 5 packets with 128-byte payload at once" << std::endl;
    std::cout << "---" << std::endl;
    
    generator.setProtocol(17);  // UDP
    generator.setTtl(64);
    
    std::vector<std::vector<uint8_t>> packets = generator.generatePackets(5, 128);
    
    for (size_t i = 0; i < packets.size(); ++i) {
        const IPHeader* header = reinterpret_cast<const IPHeader*>(packets[i].data());
        std::cout << "Packet " << (i + 1) << ": ID=" << ntohs(header->identification) 
                  << ", Size=" << packets[i].size() << " bytes" << std::endl;
    }
    std::cout << std::endl;

    // Example 5: Display packet statistics
    std::cout << "Example 5: Packet Statistics" << std::endl;
    std::cout << "---" << std::endl;
    
    std::cout << "Total Packets Generated: " << generator.getPacketCount() << std::endl;
    std::cout << "Current Source IP: ";
    printIpAddress(generator.getSourceIp());
    std::cout << std::endl;
    std::cout << "Current Destination IP: ";
    printIpAddress(generator.getDestinationIp());
    std::cout << std::endl;
    std::cout << "Current Protocol: " << static_cast<int>(generator.getProtocol()) << std::endl;
    std::cout << "Current TTL: " << static_cast<int>(generator.getTtl()) << std::endl;
    std::cout << std::endl;

    // Example 6: Hex dump of a packet
    std::cout << "Example 6: Hexadecimal dump of a 64-byte packet (first 80 bytes)" << std::endl;
    std::cout << "---" << std::endl;
    
    std::vector<uint8_t> packet6 = generator.generatePacket(64);
    printPacketHex(packet6, 80);
    std::cout << std::endl;

    // Example 7: Reset and verify counter
    std::cout << "Example 7: Reset identification counter and generate new packets" << std::endl;
    std::cout << "---" << std::endl;
    
    generator.resetIdentificationCounter();
    
    for (int i = 0; i < 3; ++i) {
        std::vector<uint8_t> packet = generator.generatePacket(100);
        const IPHeader* header = reinterpret_cast<const IPHeader*>(packet.data());
        std::cout << "Packet " << (i + 1) << ": ID=" << ntohs(header->identification) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "Example program completed successfully!" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
