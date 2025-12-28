# 🔐 Playfair Cipher Implementation

[![C++](https://img.shields.io/badge/C++-11-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()

A professional **C++ implementation** of the classic Playfair cipher encryption/decryption algorithm. This cipher uses a 5x5 grid of letters to encrypt pairs of characters (digraphs), providing a robust and historically significant cryptographic method.

## ✨ Features

- 🔒 **Full Encryption/Decryption** - Complete implementation of the Playfair cipher algorithm
- 🎯 **Configurable I/J Mapping** - Choose between treating J as I or omitting Q from the alphabet
- 🔄 **Automatic Digraph Formation** - Smart handling of duplicate letters and padding
- 📊 **Formatted Output** - Clean, readable output with organized digraph pairs
- 🛡️ **Input Validation** - Automatic text normalization and filtering
- 🎨 **Professional Code** - Well-documented, object-oriented C++ implementation
- ⚡ **Cross-Platform** - Works on Windows, Linux, and macOS
- 🔧 **Interactive CLI** - User-friendly command-line interface

## 🛠️ Technology Stack

| Technology      | Version  | Purpose                   |
| --------------- | -------- | ------------------------- |
| **C++**         | C++11    | Core programming language |
| **g++/clang++** | Latest   | C++ compiler              |
| **STL**         | Standard | Standard Template Library |

## 📁 Project Structure

```
Playfair/
├── 📄 README.md                    # Project documentation
├── 📄 LICENSE                      # BSD 3-Clause License
├── 📄 .gitignore                   # Git ignore patterns
├── 📄 build.sh                     # Build script (Linux/macOS)
├── 📄 build.bat                    # Build script (Windows)
│
├── 📂 src/                         # Source code
│   └── playfair.cpp                # Main implementation file
│
└── 📂 build/                       # Build output directory
    └── playfair.exe                # Compiled executable (Windows)
    └── playfair                    # Compiled executable (Linux/macOS)
```

## 🚀 Quick Start

### Prerequisites

- **C++ Compiler**: g++ (GCC) or clang++ (Clang)
  - **Windows**: MSYS2, MinGW-w64, or Visual Studio
  - **Linux**: `sudo apt-get install g++` (Ubuntu/Debian) or `sudo yum install gcc-c++` (RHEL/CentOS)
  - **macOS**: Xcode Command Line Tools (`xcode-select --install`)

### Installation

1. **Clone the repository**

   ```bash
   git clone https://github.com/yourusername/Playfair.git
   cd Playfair
   ```

2. **Compile the project**

   **Option 1: Using build scripts (Recommended)**

   **Windows:**

   ```bash
   build.bat
   ```

   **Linux/macOS:**

   ```bash
   chmod +x build.sh
   ./build.sh
   ```

   **Option 2: Manual compilation**

   **Windows (MSYS2/MinGW):**

   ```bash
   g++ -o build/playfair.exe src/playfair.cpp -std=c++11
   ```

   **Linux/macOS:**

   ```bash
   g++ -o build/playfair src/playfair.cpp -std=c++11
   ```

   **Alternative compilers:**

   ```bash
   # Using clang++
   clang++ -o build/playfair src/playfair.cpp -std=c++11

   # Using MSVC (Windows)
   cl.exe /EHsc /std:c++11 src/playfair.cpp /Fe:build/playfair.exe
   ```

## 📖 Usage

### Running the Program

**Windows:**

```bash
.\build\playfair.exe
```

**Linux/macOS:**

```bash
./build/playfair
```

### Interactive Mode

The program will prompt you for:

1. **Mode Selection**: Choose `E` for encryption or `D` for decryption
2. **Encryption Key**: Enter your cipher key (or leave empty for default "KEYWORD")
3. **I/J Mapping**: Choose `Y` to map J to I, or `N` to omit Q from the alphabet
4. **Input Text**: Enter the text you want to encrypt or decrypt

### Example Session

```
(E)ncode or (D)ecode? E
Enter a en/decryption key: SECRETKEY
I <-> J (Y/N): Y
Enter the text: HELLO WORLD

 OUTPUT:
=========
GY IZ SC OK CF BU

Press any key to continue . . .
```

### Decryption Example

```
(E)ncode or (D)ecode? D
Enter a en/decryption key: SECRETKEY
I <-> J (Y/N): Y
Enter the text: GYIZSCOKCFBU

 OUTPUT:
=========
HE LX LO WO RL DX

Press any key to continue . . .
```

## 🔐 How It Works

### Playfair Cipher Algorithm

The Playfair cipher encrypts pairs of letters (digraphs) using a 5×5 grid:

1. **Grid Construction**:

   - Fill a 5×5 grid with a keyword followed by the remaining alphabet
   - Remove duplicate letters
   - Handle I/J or Q based on configuration

2. **Text Preparation**:

   - Convert to uppercase
   - Remove non-alphabetic characters
   - Insert padding (X) between duplicate letters in pairs
   - Add padding if text length is odd

3. **Encryption Rules**:

   - **Same Row**: Shift each letter right (wraps around)
   - **Same Column**: Shift each letter down (wraps around)
   - **Rectangle**: Swap columns (form rectangle, take opposite corners)

4. **Decryption**: Reverse the encryption process

### Configuration Options

- **I/J Mapping**:

  - `Y`: Treats J as I (25-letter alphabet)
  - `N`: Omits Q from alphabet (25-letter alphabet)

- **Default Key**: If no key is provided, uses "KEYWORD"

## 🔧 Development

### Building from Source

```bash
# Clone repository
git clone https://github.com/yourusername/Playfair.git
cd Playfair

# Create build directory (if it doesn't exist)
mkdir -p build

# Compile with optimizations
g++ -o build/playfair src/playfair.cpp -std=c++11 -O2

# Compile with debug symbols
g++ -o build/playfair src/playfair.cpp -std=c++11 -g
```

### Code Structure

The implementation follows object-oriented principles:

- **`PlayfairCipher` Class**: Main cipher implementation

  - `process()`: Main encryption/decryption method
  - `buildCipherGrid()`: Constructs the 5×5 grid
  - `normalizeAndPrepareText()`: Prepares input text
  - `transformDigraphPairs()`: Applies cipher rules
  - `printFormattedOutput()`: Displays results

- **Helper Functions**:
  - `getUserMode()`: Gets encryption/decryption mode
  - `getUserMappingPreference()`: Gets I/J mapping preference

### Code Style

This project follows:

- **C++11** standard
- **Object-oriented** design principles
- **Comprehensive documentation** with comments
- **Clear naming conventions**

## 📊 Algorithm Details

### Grid Example

With key "SECRETKEY" and I/J mapping:

```
S E C R T
A B D F G
H I K L M
N O P Q U
V W X Y Z
```

### Encryption Example

**Input**: "HELLO"

- Forms pairs: HE, LX, LO (X added for padding)
- HE → GY (rectangle rule)
- LX → IZ (same row)
- LO → SC (rectangle rule)

**Output**: "GYIZSC"

## 🐛 Troubleshooting

### Common Issues

**Issue**: `g++: command not found`

- **Solution**: Install a C++ compiler:
  - **Windows**: Install MSYS2 from https://www.msys2.org/
  - **Linux**: `sudo apt-get install g++` or `sudo yum install gcc-c++`
  - **macOS**: Install Xcode Command Line Tools

**Issue**: `error: 'array' in namespace 'std' did not name a type`

- **Solution**: Ensure you're using C++11 or later: `g++ -std=c++11`

**Issue**: Program crashes on input

- **Solution**: Ensure your compiler supports C++11 standard library features

**Issue**: Output formatting looks incorrect

- **Solution**: The program outputs digraph pairs separated by spaces, which is normal behavior

## 📝 API Reference

### PlayfairCipher Class

#### `void process(const std::string& encryptionKey, const std::string& inputText, bool shouldMapItoJ, bool isEncryption)`

Main method to encrypt or decrypt text.

**Parameters:**

- `encryptionKey`: The key used to build the cipher grid (empty uses default "KEYWORD")
- `inputText`: Plaintext for encryption or ciphertext for decryption
- `shouldMapItoJ`: If true, treat J as I; if false, omit Q from alphabet
- `isEncryption`: If true, encrypt; if false, decrypt

**Example:**

```cpp
PlayfairCipher cipher;
cipher.process("SECRETKEY", "HELLO WORLD", true, true);  // Encrypt
cipher.process("SECRETKEY", "GYIZSCOKCFBU", true, false); // Decrypt
```

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/AmazingFeature`
3. **Commit your changes**: `git commit -m 'Add some AmazingFeature'`
4. **Push to the branch**: `git push origin feature/AmazingFeature`
5. **Open a Pull Request**

### Contribution Guidelines

- Follow C++11 coding standards
- Add comments for complex logic
- Test your changes on multiple platforms
- Update documentation as needed
- Ensure code compiles without warnings

## 📄 License

This project is licensed under the BSD 3-Clause License - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**Ahmed Mohamed**

- GitHub: [@3bsalam-1](https://github.com/3bsalam-1)
- LinkedIn: [Ahmed Abdulsalam](https://linkedin.com/in/ahmed-abdulsalam1)

## 🙏 Acknowledgments

- The Playfair cipher was invented by Charles Wheatstone in 1854
- Named after Lord Playfair who promoted its use
- One of the first practical digraph substitution ciphers

## 📚 Additional Resources

- [Playfair Cipher on Wikipedia](https://en.wikipedia.org/wiki/Playfair_cipher)
- [C++ Reference](https://en.cppreference.com/)
- [C++11 Standard Documentation](https://isocpp.org/std/the-standard)

---

<div align="center">

**⭐ Star this repository if you find it helpful!**

Made with ❤️ by Ahmed Abdulsalam

</div>
