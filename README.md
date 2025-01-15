# Rivest-Shamir-Adleman (RSA) Implementation

## How to make it run

### 1. Install dependencies and package manager
```bash
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg integrate install
./vcpkg install openssl:x64-windows
```

### 2. Copy the path where you cloned vcpkg
Likely it's in ```C:\Users\<YourUser>\vcpkg```

### 3. Set the VCPKG_ROOT environment variable:

```
   - Search "Environment Variables" in Windows search
   - Under "User variables" click "New"
   - Variable name: `VCPKG_ROOT`
   - Variable value: Your vcpkg path (e.g. `C:\Users\<YourUser>\vcpkg`)
```

### 4. Set new Path variable that points to OpenSSL binaries
Likely it's in this folder but it depends where your vcpkg is: ```C:\Users\<YourUser>\vcpkg\installed\x64-windows\bin\```

Add this folder to your PATH

### 4. Restart your IDE (Optional)

## Overview

This project is a complete implementation of the RSA encryption algorithm from scratch, without relying on external libraries. The goal is to understand and demonstrate how RSA works, while optimizing for clean, efficient, and modular code.

## Features

- **Custom BigNumber Class**: Handles large integers for encryption and decryption.
- **RSA Key Generation**: Generates secure public and private key pairs.
- **Message Encryption**: Converts strings into encrypted BigNumbers.
- **Message Decryption**: Decrypts encrypted BigNumbers back into readable strings.
- **Test-Driven Development**: Fully tested implementation for reliability.

## Highlights

- Implements the RSA algorithm step-by-step, following efficient, modular techniques.
- Entire workflow for encryption and decryption demonstrated in the `main` function.
- Adheres to Google-style coding standards for readability and maintainability.


## Purpose

This implementation is designed for learning, experimentation, and achieving a deeper understanding of RSA. The custom implementation avoids external dependencies for greater efficiency and control.
