# Phase 03: RLC Layer Implementation

## 1. Phase Objective

The objective of this phase is to implement the Radio Link Control (RLC) layer for the 5G NR User Plane. This implementation will focus on the core functionalities of RLC, including segmentation, retransmission (ARQ), and reassembly, as per 3GPP TS 38.322 specifications.

## 2. Key Deliverables

*   `rlc.h`: Header file defining the `RLC` class and related structures.
*   `rlc.cpp`: Implementation of the `RLC` class methods.
*   `rlc_test.cpp`: Unit/integration test program for the RLC layer.
*   `rlc_layer_design.md`: A design document detailing the RLC PDU structure and functional architecture.

These files will be located in the `src/rlc_layer/` directory and copied to `phases/phase_03_rlc_layer/deliverables/` upon completion of this phase.

## 3. Implementation Details

The `RLC` class will provide methods to process PDCP PDUs from the upper layer (PDCP) and generate RLC PDUs for the lower layer (MAC). Conversely, it will also process incoming RLC PDUs from the MAC layer and extract the original PDCP PDUs. Key aspects include:

*   **RLC PDU Structure:** Implementation of different RLC PDU formats (e.g., Data PDU, Control PDU) and their headers.
*   **Segmentation and Reassembly:** Breaking down larger PDCP PDUs into smaller RLC PDUs for transmission and reassembling them at the receiver.
*   **Automatic Repeat Request (ARQ):** Mechanisms for detecting lost or corrupted RLC PDUs and requesting their retransmission to ensure reliable data delivery.
*   **Sequence Number (SN) Management:** Managing RLC SNs for reordering and duplicate detection within the RLC layer.

## 4. Testing & Verification

A dedicated test program (`rlc_test.cpp`) will be developed to verify the RLC layer's functionality. This will involve:

*   Generating PDCP PDUs (from the PDCP layer).
*   Passing these PDCP PDUs through the `RLC` layer to create RLC PDUs.
*   Verifying the correctness of RLC PDU segmentation and header assignment.
*   Simulating packet loss and testing the ARQ mechanism.
*   Processing RLC PDUs to extract the original PDCP PDUs and comparing them with the generated ones.

## 5. Next Steps

Upon successful implementation and testing of the RLC layer, the project will proceed to **Phase 04: MAC Layer and Transport Block Looping**, where the Medium Access Control Protocol and the transport block looping mechanism will be developed.
