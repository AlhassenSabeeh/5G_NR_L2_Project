# PDCP Layer Design for 5G NR

## 1. Introduction

This document details the design and implementation plan for the Packet Data Convergence Protocol (PDCP) layer, a crucial component of the 5G New Radio (NR) Layer 2 protocol stack. The PDCP layer is responsible for several key functions that ensure efficient and secure data transfer between the User Equipment (UE) and the network. This design will align with the 3GPP TS 38.323 specification [1].

## 2. PDCP Layer Overview

The PDCP layer resides above the Radio Link Control (RLC) layer and below the IP layer (or SDAP in the User Plane). Its primary functions include:

*   **Header Compression:** Efficiently compressing IP headers (e.g., using ROHC) to reduce overhead on the radio interface.
*   **Ciphering (Encryption):** Protecting the confidentiality of user data and control plane signaling.
*   **Integrity Protection:** Ensuring the integrity of control plane signaling to prevent unauthorized modification.
*   **Sequence Number (SN) Management:** Assigning and managing PDCP SNs for reordering, duplicate detection, and retransmission handling at the RLC layer.
*   **In-sequence Delivery and Duplicate Detection:** Delivering PDCP Service Data Units (SDUs) to the upper layers in order and discarding duplicates.
*   **Timer-based Discard:** Discarding PDCP SDUs that have not been delivered within a configured time.

For this project, we will focus on **SN Management**, **Ciphering**, and **Integrity Protection** as core functionalities, along with the basic PDCP PDU (Protocol Data Unit) structure.

## 3. PDCP PDU Structure

The PDCP PDU carries either user data (Data PDU) or control information (Control PDU). For the user plane, we will primarily deal with Data PDUs. The structure of a PDCP Data PDU depends on whether it's carrying user data or control data, and the length of the PDCP SN.

### 3.1. PDCP Data PDU Format

We will consider the most common format for user data, which includes a PDCP Header and the Data field (which contains the IP packet from the lower layer).

| Field Name      | Size (bits) | Description                                                              |
| :-------------- | :---------- | :----------------------------------------------------------------------- |
| **PDCP SN**     | 5, 7, 12, 18 | PDCP Sequence Number. Length is configurable.                            |
| **D/C**         | 1           | Data/Control Indicator (0 for Control PDU, 1 for Data PDU)               |
| **PDU Type**    | 3           | Only for Control PDU. Not present in Data PDU.                           |
| **Reserved**    | Variable    | Padding bits to align the header.                                        |
| **Data**        | Variable    | The IP packet (or compressed IP packet) from the upper layer.            |
| **MAC-I**       | 32          | Message Authentication Code for Integrity (optional, for control plane). |

For user plane data, the D/C bit will be '1'. The PDCP SN length is a critical configuration parameter. We will initially support a 12-bit PDCP SN, which is common for user plane data.

### 3.2. Simplified PDCP Header for User Plane Data (12-bit SN)

| Field Name      | Size (bits) | Description                                                              |
| :-------------- | :---------- | :----------------------------------------------------------------------- |
| **D/C**         | 1           | Data/Control Indicator (1 for Data PDU)                                  |
| **PDCP SN**     | 12          | PDCP Sequence Number (0 to 4095)                                         |
| **Reserved**    | 3           | Reserved bits for byte alignment.                                        |

**Total Header Size:** 2 bytes (16 bits)

## 4. PDCP Layer Functional Architecture

We will design a `PDCP` class that will handle the functionalities of the PDCP layer. It will interact with the `IPPacketGenerator` (upper layer) and the RLC layer (lower layer).

### 4.1. Class Definition

```cpp
class PDCP {
public:
    // Constructor
    PDCP(uint32_t rnti, uint8_t sn_len = 12); // RNTI for context, SN length

    // Method to process an incoming IP packet (from upper layer) and generate a PDCP PDU
    std::vector<uint8_t> processIpPacket(const std::vector<uint8_t>& ip_packet);

    // Method to process an incoming PDCP PDU (from lower layer) and extract IP packet
    std::vector<uint8_t> processPdcpPdu(const std::vector<uint8_t>& pdcp_pdu);

    // Setter for SN length (if dynamic configuration is needed)
    void setSnLength(uint8_t sn_len);

    // Get current SN
    uint16_t getCurrentSn() const;

private:
    uint33_t rnti_; // Radio Network Temporary Identifier
    uint8_t pdcp_sn_len_; // PDCP SN length (e.g., 5, 7, 12, 18)
    uint16_t tx_sn_counter_; // Transmit SN counter
    uint16_t rx_sn_counter_; // Receive SN counter (for reordering/duplicate detection)

    // Placeholder for ciphering/deciphering functions
    std::vector<uint8_t> cipher(const std::vector<uint8_t>& data, uint16_t sn);
    std::vector<uint8_t> decipher(const std::vector<uint8_t>& data, uint16_t sn);

    // Placeholder for integrity protection/verification functions
    std::vector<uint8_t> addIntegrity(const std::vector<uint8_t>& data, uint16_t sn);
    bool verifyIntegrity(const std::vector<uint8_t>& data, uint16_t sn);

    // Helper to construct PDCP header
    std::vector<uint8_t> createPdcpHeader(uint16_t sn);

    // Helper to parse PDCP header
    uint16_t parsePdcpHeader(const std::vector<uint8_t>& pdcp_pdu);
};
```

### 4.2. Key Functionalities

*   **`PDCP(uint32_t rnti, uint8_t sn_len)` (Constructor):** Initializes the PDCP entity with a Radio Network Temporary Identifier (RNTI) and the configured PDCP SN length. RNTI is used to identify the UE context.
*   **`processIpPacket(const std::vector<uint8_t>& ip_packet)`:** This method will take an IP packet (from the `IPPacketGenerator`) as input. It will:
    1.  Assign a PDCP SN from `tx_sn_counter_` and increment the counter.
    2.  Construct the PDCP header based on the SN and configured SN length.
    3.  Perform ciphering on the IP packet (payload).
    4.  Prepend the PDCP header to the ciphered IP packet.
    5.  Return the complete PDCP PDU.
*   **`processPdcpPdu(const std::vector<uint8_t>& pdcp_pdu)`:** This method will take a PDCP PDU (from the RLC layer) as input. It will:
    1.  Parse the PDCP header to extract the PDCP SN.
    2.  Perform deciphering on the PDCP PDU payload.
    3.  Perform duplicate detection and in-sequence delivery (initially, a basic implementation).
    4.  Return the extracted IP packet.
*   **`cipher()` and `decipher()`:** Placeholder functions for encryption/decryption. Initially, these can be simple XOR operations or a null cipher for demonstration. In a real implementation, standard algorithms like AES would be used.
*   **`addIntegrity()` and `verifyIntegrity()`:** Placeholder functions for integrity protection/verification. These are primarily for the control plane but can be included as stubs for completeness.
*   **SN Management:** `tx_sn_counter_` will manage the sequence numbers for outgoing PDCP PDUs, ensuring they wrap around correctly based on `pdcp_sn_len_`.

## 5. Integration with IP Dummy Packet Generator

The `PDCP` class will receive `std::vector<uint8_t>` representing IP packets from the `IPPacketGenerator`. The output of the `PDCP` layer (PDCP PDUs) will then be passed to the RLC layer.

## 6. Next Steps

1.  **Implement `PDCP` Class:** Write the C++ code for the `PDCP` class, including the header and source files.
2.  **Basic Ciphering/Deciphering:** Implement simple placeholder functions for ciphering and deciphering (e.g., XOR with a fixed key) to demonstrate the flow.
3.  **SN Management:** Ensure correct incrementing and wrapping of the PDCP SN.
4.  **Testing:** Create a test program to verify the PDCP PDU construction, SN management, and the basic ciphering/deciphering process. This will involve generating IP packets, passing them through the PDCP layer, and then attempting to decipher and extract the original IP packet.

## 7. References

[1] 3GPP TS 38.323 - Packet Data Convergence Protocol (PDCP) specification. [https://www.etsi.org/deliver/etsi_ts/138300_138399/138323/18.05.00_60/ts_138323v180500p.pdf](https://www.etsi.org/deliver/etsi_ts/138300_138399/138323/18.05.00_60/ts_138323v180500p.pdf)
