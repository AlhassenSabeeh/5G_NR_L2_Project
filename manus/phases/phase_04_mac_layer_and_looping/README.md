# Phase 04: MAC Layer and Transport Block Looping

## 1. Phase Objective

The objective of this phase is to implement the Medium Access Control (MAC) layer for the 5G NR User Plane and integrate the Transport Block Looping functionality. This implementation will focus on scheduling, multiplexing, and the simulation of realistic data flow by looping uplink-generated transport blocks to the downlink, as per 3GPP TS 38.321 specifications.

## 2. Key Deliverables

*   `mac.h`: Header file defining the `MAC` class and related structures.
*   `mac.cpp`: Implementation of the `MAC` class methods.
*   `mac_test.cpp`: Unit/integration test program for the MAC layer.
*   `mac_layer_design.md`: A design document detailing the MAC PDU structure and functional architecture.
*   Integration of Transport Block Looping mechanism.

These files will be located in the `src/mac_layer/` directory and copied to `phases/phase_04_mac_layer_and_looping/deliverables/` upon completion of this phase.

## 3. Implementation Details

The `MAC` class will provide methods to process RLC PDUs from the upper layer (RLC) and generate MAC PDUs (Transport Blocks) for the physical layer. Conversely, it will also process incoming Transport Blocks from the physical layer and extract the original RLC PDUs. Key aspects include:

*   **MAC PDU (Transport Block) Structure:** Implementation of the Transport Block format, including MAC headers and subheaders.
*   **Scheduling:** Basic scheduling mechanisms to allocate resources for different logical channels.
*   **Multiplexing/Demultiplexing:** Combining RLC PDUs from various logical channels into a single Transport Block for transmission and separating them at the receiver.
*   **Transport Block Looping:** A mechanism to take the generated Transport Blocks from the uplink path and feed them directly into the downlink path, simulating a closed-loop data flow for end-to-end testing of the Layer 2 stack.

## 4. Testing & Verification

A dedicated test program (`mac_test.cpp`) will be developed to verify the MAC layer's functionality and the Transport Block Looping. This will involve:

*   Generating RLC PDUs (from the RLC layer).
*   Passing these RLC PDUs through the `MAC` layer to create Transport Blocks.
*   Verifying the correctness of MAC PDU construction and multiplexing.
*   Implementing and testing the Transport Block Looping mechanism to ensure data can flow from uplink to downlink.
*   Processing Transport Blocks to extract the original RLC PDUs and comparing them with the generated ones.

## 5. Next Steps

Upon successful implementation and testing of the MAC layer and Transport Block Looping, the project will proceed to the final stages of **Performance Profiling and Comprehensive Documentation**, including the creation of the User Manual and the Project Report.
