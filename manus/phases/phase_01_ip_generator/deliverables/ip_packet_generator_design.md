# IP Dummy Packet Generator Design

## 1. Introduction

This document outlines the design for the IP Dummy Packet Generator, a crucial component for simulating IP traffic in the 5G Layer 2 Software Implementation project. The generator will be implemented in C++ and will allow for configurable packet sizes and a simple IP header structure.

## 2. IP Packet Structure

For the purpose of this simulation, a simplified IP packet structure will be used. This structure will include essential fields to represent a basic IP packet, allowing for differentiation and basic routing if needed in future extensions. The packet will consist of a header and a payload.

### 2.1. Simplified IP Header

The IP header will be a fixed-size structure containing the following fields:

| Field Name      | Type     | Size (bytes) | Description                                       |
| :-------------- | :------- | :----------- | :------------------------------------------------ |
| `version_ihl`   | `uint8_t`| 1            | IP Version (4 bits) and Header Length (4 bits)    |
| `dscp_ecn`      | `uint8_t`| 1            | Differentiated Services Code Point (6 bits) & ECN (2 bits) |
| `total_length`  | `uint16_t`| 2            | Total length of the IP packet (header + data)     |
| `identification`| `uint16_t`| 2            | Identification field for fragmentation            |
| `flags_offset`  | `uint16_t`| 2            | Flags (3 bits) and Fragment Offset (13 bits)      |
| `ttl`           | `uint8_t`| 1            | Time To Live                                      |
| `protocol`      | `uint8_t`| 1            | Protocol (e.g., TCP, UDP)                         |
| `checksum`      | `uint16_t`| 2            | Header Checksum                                   |
| `src_ip`        | `uint32_t`| 4            | Source IP Address                                 |
| `dst_ip`        | `uint32_t`| 4            | Destination IP Address                            |

**Total Header Size:** 20 bytes

### 2.2. IP Packet Data (Payload)

The payload will consist of arbitrary data, primarily used to fill the packet to the desired `total_length`. For testing purposes, this data can be a repeating pattern or random bytes.

## 3. IP Dummy Packet Generator Architecture

The `IPPacketGenerator` class will be responsible for creating IP packets based on user-defined parameters. Its architecture will be straightforward, focusing on ease of use and configurability.

### 3.1. Class Definition

```cpp
class IPPacketGenerator {
public:
    // Constructor
    IPPacketGenerator(uint32_t src_ip, uint32_t dst_ip, uint8_t protocol, uint8_t ttl);

    // Method to generate a single IP packet
    std::vector<uint8_t> generatePacket(uint16_t payload_size);

    // Method to set source IP
    void setSourceIp(uint32_t src_ip);

    // Method to set destination IP
    void setDestinationIp(uint32_t dst_ip);

    // Method to set protocol
    void setProtocol(uint8_t protocol);

    // Method to set TTL
    void setTtl(uint8_t ttl);

private:
    uint32_t source_ip_;
    uint32_t destination_ip_;
    uint8_t protocol_;
    uint8_t ttl_;
    uint16_t identification_counter_;

    // Helper function to calculate IP checksum (simplified for dummy packets)
    uint16_t calculateChecksum(const std::vector<uint8_t>& header_data);
};
```

### 3.2. Key Functionalities

*   **Constructor:** Initializes the generator with default or specified source IP, destination IP, protocol, and TTL.
*   **`generatePacket(uint16_t payload_size)`:** This is the core method. It will construct an IP header, fill the payload with dummy data of the specified `payload_size`, and return the complete IP packet as a `std::vector<uint8_t>`.
    *   The `total_length` field in the header will be calculated as `header_size + payload_size`.
    *   The `identification` field will be incremented for each new packet generated.
    *   A simplified checksum calculation will be performed for the header.
*   **Setter Methods:** Provide flexibility to change source IP, destination IP, protocol, and TTL dynamically.

## 4. Usage Example

```cpp
#include <iostream>
#include <vector>
#include <cstdint>

// Assuming IPPacketGenerator class is defined as above

int main() {
    // Create a generator instance
    // Source IP: 192.168.1.1 (0xC0A80101)
    // Destination IP: 192.168.1.100 (0xC0A80164)
    // Protocol: UDP (17)
    // TTL: 64
    IPPacketGenerator generator(0xC0A80101, 0xC0A80164, 17, 64);

    // Generate a packet with 100 bytes payload
    std::vector<uint8_t> packet1 = generator.generatePacket(100);
    std::cout << "Generated Packet 1 Size: " << packet1.size() << " bytes" << std::endl;

    // Generate another packet with 500 bytes payload
    std::vector<uint8_t> packet2 = generator.generatePacket(500);
    std::cout << "Generated Packet 2 Size: " << packet2.size() << " bytes" << std::endl;

    return 0;
}
```

## 5. Future Considerations

*   **Checksum Calculation:** The current checksum will be simplified. For a more robust implementation, a standard IP header checksum algorithm should be used.
*   **Fragmentation:** The `flags_offset` and `identification` fields are included but not actively used for fragmentation in this basic generator. This can be extended later.
*   **Packet Content:** The payload is currently dummy data. This can be extended to include more meaningful data for specific testing scenarios.
*   **Packet Rate Control:** Adding functionality to generate packets at a specific rate (e.g., packets per second).
