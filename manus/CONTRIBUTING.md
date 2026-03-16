# Contributing to 5G Layer 2 Software Implementation Project

We welcome contributions to this project! To ensure a smooth and collaborative development process, please follow these guidelines.

## How to Contribute

1.  **Fork the Repository:** Start by forking the `5G_L2_Project` repository to your GitHub account.
2.  **Clone Your Fork:** Clone your forked repository to your local machine:
    ```bash
    git clone https://github.com/YOUR_USERNAME/5G_L2_Project.git
    cd 5G_L2_Project
    ```
3.  **Create a New Branch:** Create a new branch for your feature or bug fix. Use a descriptive name (e.g., `feature/add-rohc`, `bugfix/pdcp-checksum-error`).
    ```bash
    git checkout -b feature/your-feature-name
    ```
4.  **Make Your Changes:** Implement your feature or fix the bug. Ensure your code adheres to the coding style guidelines (see below).
5.  **Test Your Changes:** Write or update unit and integration tests to cover your changes. Ensure all existing tests pass.
6.  **Update Documentation:** If your changes affect any functionality or introduce new features, update the relevant documentation (e.g., design documents, phase READMEs).
7.  **Commit Your Changes:** Commit your changes with a clear and concise commit message. Follow the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) specification (e.g., `feat: add ROHC compression to PDCP`).
    ```bash
    git commit -m "feat: brief description of your changes"
    ```
8.  **Push to Your Fork:** Push your changes to your forked repository.
    ```bash
    git push origin feature/your-feature-name
    ```
9.  **Create a Pull Request (PR):** Open a pull request from your branch to the `main` branch of the upstream `5G_L2_Project` repository. Provide a detailed description of your changes and reference any related issues.

## Coding Style Guidelines

*   **Language:** C++17 or newer.
*   **Formatting:** Use `clang-format` with a consistent style (e.g., Google or LLVM style). A `.clang-format` file might be provided in the future.
*   **Naming Conventions:**
    *   Classes: `CamelCase`
    *   Functions: `camelCase`
    *   Variables: `snake_case`
    *   Constants: `UPPER_SNAKE_CASE`
*   **Comments:** Use Doxygen-style comments for classes, functions, and complex logic to facilitate documentation generation.

## Reporting Bugs

If you find a bug, please open an issue on the GitHub repository. Provide a clear description of the bug, steps to reproduce it, expected behavior, and actual behavior.

## Feature Requests

For new feature ideas, please open an issue to discuss it first. This helps ensure that the feature aligns with the project goals and avoids duplicate work.

## Code of Conduct

We expect all contributors to adhere to a respectful and inclusive code of conduct. Please refer to the [Contributor Covenant](https://www.contributor-covenant.org/) for details.
