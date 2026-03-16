#ifndef IP_PACKET_GENERATOR_H
#define IP_PACKET_GENERATOR_H

#include <vector>
#include <cstdint>
#include <cstring>

/**
 * @file ip_packet_generator.h
 * @brief IP Dummy Packet Generator for 5G Layer 2 Protocol Stack Testing
 * 
 * This header file defines the IPPacketGenerator class, which is responsible
 * for generating simplified IP packets with configurable sizes and header fields.
 * The generated packets are used as traffic sources for testing the Layer 2
 * protocol stack (PDCP, RLC, MAC).
 */

/**
 * @struct IPHeader
 * @brief Simplified IP Header Structure (20 bytes)
 * 
 * This structure represents a simplified IPv4 header with essential fields
 * for packet identification, routing, and fragmentation.
 */
struct IPHeader {
    uint8_t version_ihl;        ///< IP Version (4 bits) and Header Length (4 bits)
    uint8_t dscp_ecn;           ///< DSCP (6 bits) and ECN (2 bits)
    uint16_t total_length;      ///< Total length of IP packet (header + payload)
    uint16_t identification;    ///< Identification field for fragmentation
    uint16_t flags_offset;      ///< Flags (3 bits) and Fragment Offset (13 bits)
    uint8_t ttl;                ///< Time To Live
    uint8_t protocol;           ///< Protocol (e.g., TCP=6, UDP=17)
    uint16_t checksum;          ///< Header Checksum
    uint32_t src_ip;            ///< Source IP Address
    uint32_t dst_ip;            ///< Destination IP Address
};

/**
 * @class IPPacketGenerator
 * @brief Generates simplified IP packets for testing Layer 2 protocols
 * 
 * This class provides functionality to generate dummy IP packets with
 * configurable source/destination IPs, protocol types, TTL, and payload sizes.
 * The generated packets can be used to test the PDCP, RLC, and MAC layers
 * of the 5G NR protocol stack.
 */
class IPPacketGenerator {
public:
    /**
     * @brief Constructor for IPPacketGenerator
     * @param src_ip Source IP address (in network byte order)
     * @param dst_ip Destination IP address (in network byte order)
     * @param protocol Protocol number (e.g., 17 for UDP, 6 for TCP)
     * @param ttl Time To Live value (default: 64)
     */
    IPPacketGenerator(uint32_t src_ip, uint32_t dst_ip, uint8_t protocol = 17, uint8_t ttl = 64);

    /**
     * @brief Destructor
     */
    ~IPPacketGenerator();

    /**
     * @brief Generate a single IP packet with specified payload size
     * @param payload_size Size of the payload in bytes
     * @return Vector containing the complete IP packet (header + payload)
     */
    std::vector<uint8_t> generatePacket(uint16_t payload_size);

    /**
     * @brief Generate multiple IP packets
     * @param count Number of packets to generate
     * @param payload_size Size of the payload for each packet in bytes
     * @return Vector of vectors, each containing a complete IP packet
     */
    std::vector<std::vector<uint8_t>> generatePackets(uint32_t count, uint16_t payload_size);

    /**
     * @brief Set the source IP address
     * @param src_ip Source IP address (in network byte order)
     */
    void setSourceIp(uint32_t src_ip);

    /**
     * @brief Get the current source IP address
     * @return Source IP address
     */
    uint32_t getSourceIp() const;

    /**
     * @brief Set the destination IP address
     * @param dst_ip Destination IP address (in network byte order)
     */
    void setDestinationIp(uint32_t dst_ip);

    /**
     * @brief Get the current destination IP address
     * @return Destination IP address
     */
    uint32_t getDestinationIp() const;

    /**
     * @brief Set the protocol number
     * @param protocol Protocol number (e.g., 17 for UDP, 6 for TCP)
     */
    void setProtocol(uint8_t protocol);

    /**
     * @brief Get the current protocol number
     * @return Protocol number
     */
    uint8_t getProtocol() const;

    /**
     * @brief Set the Time To Live value
     * @param ttl TTL value
     */
    void setTtl(uint8_t ttl);

    /**
     * @brief Get the current TTL value
     * @return TTL value
     */
    uint8_t getTtl() const;

    /**
     * @brief Reset the packet identification counter
     */
    void resetIdentificationCounter();

    /**
     * @brief Get the total number of packets generated so far
     * @return Number of packets generated
     */
    uint32_t getPacketCount() const;

private:
    uint32_t source_ip_;                ///< Source IP address
    uint32_t destination_ip_;           ///< Destination IP address
    uint8_t protocol_;                  ///< Protocol number
    uint8_t ttl_;                       ///< Time To Live
    uint16_t identification_counter_;   ///< Counter for packet identification
    uint32_t total_packets_generated_;  ///< Total count of packets generated

    /**
     * @brief Calculate the IP header checksum (simplified)
     * @param header Pointer to the IP header structure
     * @return Calculated checksum value
     */
    uint16_t calculateChecksum(const IPHeader* header);

    /**
     * @brief Fill the payload with dummy data
     * @param payload Reference to the payload vector to fill
     * @param size Size of the payload to fill
     */
    void fillPayload(std::vector<uint8_t>& payload, uint16_t size);
};

#endif // IP_PACKET_GENERATOR_H
