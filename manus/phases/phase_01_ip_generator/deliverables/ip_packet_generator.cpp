#include "ip_packet_generator.h"
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <arpa/inet.h>

/**
 * @file ip_packet_generator.cpp
 * @brief Implementation of the IP Dummy Packet Generator
 * 
 * This file contains the implementation of the IPPacketGenerator class,
 * providing functionality to generate simplified IP packets for testing
 * the 5G Layer 2 protocol stack.
 */

/**
 * @brief Constructor for IPPacketGenerator
 * 
 * Initializes the generator with the specified IP addresses, protocol,
 * and TTL. The identification counter is set to 0 and will be incremented
 * for each new packet generated.
 */
IPPacketGenerator::IPPacketGenerator(uint32_t src_ip, uint32_t dst_ip, 
                                     uint8_t protocol, uint8_t ttl)
    : source_ip_(src_ip),
      destination_ip_(dst_ip),
      protocol_(protocol),
      ttl_(ttl),
      identification_counter_(0),
      total_packets_generated_(0) {
    // Seed the random number generator for payload generation
    srand(static_cast<unsigned int>(time(nullptr)));
}

/**
 * @brief Destructor
 */
IPPacketGenerator::~IPPacketGenerator() {
    // No dynamic memory allocation, so nothing to clean up
}

/**
 * @brief Generate a single IP packet with specified payload size
 * 
 * This method constructs an IP header with the current generator settings,
 * fills it with the appropriate values, calculates the checksum, and
 * appends the payload data.
 * 
 * @param payload_size Size of the payload in bytes
 * @return Vector containing the complete IP packet (header + payload)
 */
std::vector<uint8_t> IPPacketGenerator::generatePacket(uint16_t payload_size) {
    // Create the IP header structure
    IPHeader header;

    // Set version (4) and header length (5 for 20 bytes)
    header.version_ihl = (4 << 4) | 5;

    // Set DSCP and ECN (both 0 for simplicity)
    header.dscp_ecn = 0;

    // Set total length (header 20 bytes + payload size)
    header.total_length = htons(20 + payload_size);

    // Set identification and increment counter
    header.identification = htons(identification_counter_++);

    // Set flags (0) and fragment offset (0) - no fragmentation
    header.flags_offset = 0;

    // Set TTL
    header.ttl = ttl_;

    // Set protocol
    header.protocol = protocol_;

    // Set source and destination IPs
    header.src_ip = source_ip_;
    header.dst_ip = destination_ip_;

    // Calculate and set checksum (initially set to 0)
    header.checksum = 0;
    header.checksum = calculateChecksum(&header);

    // Create the packet vector
    std::vector<uint8_t> packet;

    // Add the header (20 bytes)
    uint8_t* header_ptr = reinterpret_cast<uint8_t*>(&header);
    packet.insert(packet.end(), header_ptr, header_ptr + sizeof(IPHeader));

    // Add the payload
    fillPayload(packet, payload_size);

    // Increment the total packets generated counter
    total_packets_generated_++;

    return packet;
}

/**
 * @brief Generate multiple IP packets
 * 
 * This method generates multiple packets with the same payload size.
 * 
 * @param count Number of packets to generate
 * @param payload_size Size of the payload for each packet in bytes
 * @return Vector of vectors, each containing a complete IP packet
 */
std::vector<std::vector<uint8_t>> IPPacketGenerator::generatePackets(uint32_t count, 
                                                                      uint16_t payload_size) {
    std::vector<std::vector<uint8_t>> packets;
    for (uint32_t i = 0; i < count; ++i) {
        packets.push_back(generatePacket(payload_size));
    }
    return packets;
}

/**
 * @brief Set the source IP address
 * @param src_ip Source IP address
 */
void IPPacketGenerator::setSourceIp(uint32_t src_ip) {
    source_ip_ = src_ip;
}

/**
 * @brief Get the current source IP address
 * @return Source IP address
 */
uint32_t IPPacketGenerator::getSourceIp() const {
    return source_ip_;
}

/**
 * @brief Set the destination IP address
 * @param dst_ip Destination IP address
 */
void IPPacketGenerator::setDestinationIp(uint32_t dst_ip) {
    destination_ip_ = dst_ip;
}

/**
 * @brief Get the current destination IP address
 * @return Destination IP address
 */
uint32_t IPPacketGenerator::getDestinationIp() const {
    return destination_ip_;
}

/**
 * @brief Set the protocol number
 * @param protocol Protocol number
 */
void IPPacketGenerator::setProtocol(uint8_t protocol) {
    protocol_ = protocol;
}

/**
 * @brief Get the current protocol number
 * @return Protocol number
 */
uint8_t IPPacketGenerator::getProtocol() const {
    return protocol_;
}

/**
 * @brief Set the Time To Live value
 * @param ttl TTL value
 */
void IPPacketGenerator::setTtl(uint8_t ttl) {
    ttl_ = ttl;
}

/**
 * @brief Get the current TTL value
 * @return TTL value
 */
uint8_t IPPacketGenerator::getTtl() const {
    return ttl_;
}

/**
 * @brief Reset the packet identification counter
 */
void IPPacketGenerator::resetIdentificationCounter() {
    identification_counter_ = 0;
}

/**
 * @brief Get the total number of packets generated so far
 * @return Number of packets generated
 */
uint32_t IPPacketGenerator::getPacketCount() const {
    return total_packets_generated_;
}

/**
 * @brief Calculate the IP header checksum (simplified)
 * 
 * This function calculates a simplified checksum for the IP header.
 * It sums all 16-bit words in the header and performs one's complement.
 * 
 * @param header Pointer to the IP header structure
 * @return Calculated checksum value
 */
uint16_t IPPacketGenerator::calculateChecksum(const IPHeader* header) {
    // Convert header to 16-bit words
    const uint16_t* words = reinterpret_cast<const uint16_t*>(header);
    uint32_t sum = 0;

    // Sum all 16-bit words (header is 20 bytes = 10 words)
    for (int i = 0; i < 10; ++i) {
        // Skip the checksum field (at index 8)
        if (i != 8) {
            sum += ntohs(words[i]);
        }
    }

    // Add carry-over bits
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    // Return one's complement
    return htons(~sum & 0xFFFF);
}

/**
 * @brief Fill the payload with dummy data
 * 
 * This function fills the payload with a repeating pattern of bytes.
 * The pattern is a simple incrementing sequence (0, 1, 2, ..., 255, 0, 1, ...).
 * 
 * @param payload Reference to the packet vector to append payload to
 * @param size Size of the payload to fill
 */
void IPPacketGenerator::fillPayload(std::vector<uint8_t>& payload, uint16_t size) {
    for (uint16_t i = 0; i < size; ++i) {
        // Use a simple repeating pattern (0-255)
        payload.push_back(static_cast<uint8_t>(i % 256));
    }
}
