# 5G Layer 2 Software Implementation Project

This repository contains the implementation of components for the Layer 2 protocol stack for 5G New Radio (5G NR) from the User Equipment (UE) perspective, covering both uplink and downlink data paths. The project adheres to the 3GPP 38-series specifications and is structured to facilitate modular development, testing, and collaboration.

## Project Overview

The primary objective of this project is to gain hands-on experience with 5G protocol implementation, understand the complexities of Layer 2 protocols (PDCP, RLC, MAC), and analyze their performance. The project is divided into several phases, each focusing on a specific aspect of the Layer 2 stack.

## Project Structure

The repository is organized as follows:

```
5G_L2_Project/
├── .git/                     # Git version control metadata
├── .github/                  # GitHub specific configurations (e.g., CI/CD workflows)
├── docs/                     # Project documentation, guidelines, and design documents
├── src/                      # Source code for all protocol layers and utilities
│   ├── common/               # Common utilities, data structures, or helper functions
│   ├── ip_generator/         # Source code for the IP Dummy Packet Generator
│   ├── pdcp_layer/           # Source code for the PDCP Layer
│   ├── rlc_layer/            # Source code for the RLC Layer
│   └── mac_layer/            # Source code for the MAC Layer
├── tests/                    # Unit and integration tests for each component
├── build/                    # Directory for compiled binaries and build artifacts
├── phases/                   # Phase-specific documentation and deliverables
│   ├── phase_01_ip_generator/
│   ├── phase_02_pdcp_layer/
│   ├── phase_03_rlc_layer/
│   └── phase_04_mac_layer_and_looping/
├── README.md                 # Main project README (this file)
├── CONTRIBUTING.md           # Guidelines for contributors
└── LICENSE                   # Project license information
```

## Getting Started

### Prerequisites

*   C++ compiler (g++ recommended)
*   Make or CMake (for building)
*   Git (for version control)

### Building the Project

Instructions for building the entire project will be provided here once a comprehensive build system (e.g., CMake) is set up. For now, refer to individual phase READMEs for specific compilation instructions.

### Running Tests

Details on how to run unit and integration tests will be provided as the project progresses.

## Phases

This project is structured into the following phases:

*   **Phase 1: IP Dummy Packet Generator**
    *   Implementation of a configurable IP packet generator to simulate traffic.
*   **Phase 2: PDCP Layer Implementation**
    *   Implementation of the Packet Data Convergence Protocol, including SN management, ciphering, and integrity protection.
*   **Phase 3: RLC Layer Implementation**
    *   Development of the Radio Link Control Protocol for segmentation, retransmission, and reassembly.
*   **Phase 4: MAC Layer and Transport Block Looping**
    *   Implementation of the Medium Access Control Protocol and the transport block looping mechanism.

Each phase has a dedicated `README.md` file within its respective `phases/` subdirectory, providing detailed information about its objectives, deliverables, and implementation.

## Contributing

Refer to `CONTRIBUTING.md` for guidelines on how to contribute to this project.

## License

This project is licensed under the [License Name] - see the `LICENSE` file for details.
