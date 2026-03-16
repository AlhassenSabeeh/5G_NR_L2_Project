# Phase 02: PDCP Layer Implementation

## 1. Phase Objective

The objective of this phase is to implement the Packet Data Convergence Protocol (PDCP) layer for the 5G NR User Plane. This implementation will focus on the core functionalities of PDCP, including Sequence Number (SN) management, ciphering, and integrity protection, as per 3GPP TS 38.323 specifications.

## 2. Key Deliverables

*   `pdcp.h`: Header file defining the `PDCP` class and related structures.
*   `pdcp.cpp`: Implementation of the `PDCP` class methods.
*   `pdcp_test.cpp`: Unit/integration test program for the PDCP layer.
*   `pdcp_layer_design.md`: A design document detailing the PDCP PDU structure and functional architecture.

These files will be located in the `src/pdcp_layer/` directory and copied to `phases/phase_02_pdcp_layer/deliverables/` upon completion of this phase.

## 3. Implementation Details

The `PDCP` class will provide methods to process IP packets from the upper layer (IP Dummy Packet Generator) and generate PDCP PDUs for the lower layer (RLC). Conversely, it will also process incoming PDCP PDUs from the RLC layer and extract the original IP packets. Key aspects include:

*   **Simplified PDCP Header:** A 2-byte header for user plane data, incorporating a 1-bit Data/Control indicator and a 12-bit PDCP Sequence Number (SN).
*   **SN Management:** The `tx_sn_counter_` will manage sequence numbers for outgoing PDCP PDUs, ensuring correct incrementing and wrapping based on the configured SN length.
*   **Ciphering/Deciphering:** Placeholder functions for encryption and decryption will be implemented, initially using a simple XOR operation for demonstration purposes. These will be modular to allow for integration of more robust algorithms later.
*   **Integrity Protection:** Placeholder functions for adding and verifying integrity will be included, primarily for control plane signaling but present for completeness.

## 4. Testing & Verification

A dedicated test program (`pdcp_test.cpp`) will be developed to verify the PDCP layer's functionality. This will involve:

*   Generating IP packets using the `IPPacketGenerator`.
*   Passing these IP packets through the `PDCP` layer to create PDCP PDUs.
*   Verifying the correctness of the PDCP header and SN assignment.
*   Testing the ciphering and deciphering process to ensure data integrity.
*   Processing PDCP PDUs to extract the original IP packets and comparing them with the generated ones.

## 5. Next Steps

Upon successful implementation and testing of the PDCP layer, the project will proceed to **Phase 03: RLC Layer Implementation**, where the Radio Link Control Protocol will be developed to manage data segmentation, retransmission, and reassembly.
