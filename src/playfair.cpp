/*
 * Playfair Cipher Implementation
 *
 * A professional implementation of the Playfair cipher encryption/decryption algorithm.
 * This cipher uses a 5x5 grid of letters to encrypt pairs of characters (digraphs).
 *
 * Features:
 * - Configurable I/J mapping (treat J as I or omit Q)
 * - Automatic digraph formation and padding
 * - Support for both encryption and decryption
 */

#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <cctype>

namespace PlayfairConstants
{
    constexpr int GRID_SIZE = 5;
    constexpr int GRID_TOTAL_CELLS = GRID_SIZE * GRID_SIZE;
    constexpr char DEFAULT_KEY[] = "KEYWORD";
    constexpr char PADDING_CHAR = 'X';
    constexpr char FIRST_LETTER = 'A';
    constexpr char LAST_LETTER = 'Z';
    constexpr size_t PAIRS_PER_LINE = 26;
    constexpr int ENCRYPT_DIRECTION = +1;
    constexpr int DECRYPT_DIRECTION = -1;
}

class PlayfairCipher
{
public:
    /**
     * Process text using the Playfair cipher algorithm.
     *
     * @param encryptionKey The key used to build the cipher grid (empty uses default)
     * @param inputText Plaintext for encryption or ciphertext for decryption
     * @param shouldMapItoJ If true, treat J as I; if false, omit Q from the alphabet
     * @param isEncryption If true, encrypt; if false, decrypt
     */
    void process(const std::string& encryptionKey, 
                 const std::string& inputText, 
                 bool shouldMapItoJ, 
                 bool isEncryption)
    {
        buildCipherGrid(encryptionKey, shouldMapItoJ);
        normalizeAndPrepareText(inputText, shouldMapItoJ, isEncryption);
        transformDigraphPairs(isEncryption ? PlayfairConstants::ENCRYPT_DIRECTION 
                                           : PlayfairConstants::DECRYPT_DIRECTION);
        printFormattedOutput();
    }

private:
    /**
     * Transform digraph pairs according to Playfair cipher rules.
     * 
     * Rules:
     * - Same row: shift right (encrypt) or left (decrypt)
     * - Same column: shift down (encrypt) or up (decrypt)
     * - Rectangle: swap columns
     *
     * @param shiftDirection +1 for encryption, -1 for decryption
     */
    void transformDigraphPairs(int shiftDirection)
    {
        std::string transformedText;
        transformedText.reserve(processedText.size());

        for (size_t index = 0; index + 1 < processedText.size(); index += 2)
        {
            char firstChar = processedText[index];
            char secondChar = processedText[index + 1];

            int firstCharColumn, firstCharRow;
            int secondCharColumn, secondCharRow;
            
            if (!findCharacterPosition(firstChar, firstCharColumn, firstCharRow) ||
                !findCharacterPosition(secondChar, secondCharColumn, secondCharRow))
            {
                continue;
            }

            if (firstCharRow == secondCharRow)
            {
                // Same row: shift horizontally
                transformedText += getCharacterAtPosition(firstCharColumn + shiftDirection, firstCharRow);
                transformedText += getCharacterAtPosition(secondCharColumn + shiftDirection, secondCharRow);
            }
            else if (firstCharColumn == secondCharColumn)
            {
                // Same column: shift vertically
                transformedText += getCharacterAtPosition(firstCharColumn, firstCharRow + shiftDirection);
                transformedText += getCharacterAtPosition(secondCharColumn, secondCharRow + shiftDirection);
            }
            else
            {
                // Rectangle: swap columns
                transformedText += getCharacterAtPosition(secondCharColumn, firstCharRow);
                transformedText += getCharacterAtPosition(firstCharColumn, secondCharRow);
            }
        }

        processedText.swap(transformedText);
    }

    /**
     * Print the processed digraph pairs in a formatted output.
     * Pairs are separated by spaces and wrapped after a fixed number per line.
     */
    void printFormattedOutput() const
    {
        std::cout << "\n\n OUTPUT:\n=========" << std::endl;
        
        size_t pairCount = 0;

        for (size_t index = 0; index + 1 < processedText.size(); index += 2)
        {
            std::cout << processedText[index] << processedText[index + 1] << ' ';
            
            if (++pairCount >= PlayfairConstants::PAIRS_PER_LINE)
            {
                std::cout << std::endl;
                pairCount = 0;
            }
        }

        std::cout << std::endl << std::endl;
    }

    /**
     * Get character at the specified grid position with wrap-around.
     * Uses modular arithmetic to handle negative or out-of-range indices.
     *
     * @param column Column index (0-4, wraps around)
     * @param row Row index (0-4, wraps around)
     * @return Character at the specified position
     */
    char getCharacterAtPosition(int column, int row) const
    {
        int wrappedColumn = (column % PlayfairConstants::GRID_SIZE + PlayfairConstants::GRID_SIZE) % PlayfairConstants::GRID_SIZE;
        int wrappedRow = (row % PlayfairConstants::GRID_SIZE + PlayfairConstants::GRID_SIZE) % PlayfairConstants::GRID_SIZE;
        return cipherGrid[wrappedRow][wrappedColumn];
    }

    /**
     * Find the position of a character in the cipher grid.
     *
     * @param character The character to find
     * @param column Output parameter for the column index
     * @param row Output parameter for the row index
     * @return True if character found, false otherwise
     */
    bool findCharacterPosition(char character, int& column, int& row) const
    {
        for (int rowIndex = 0; rowIndex < PlayfairConstants::GRID_SIZE; ++rowIndex)
        {
            for (int columnIndex = 0; columnIndex < PlayfairConstants::GRID_SIZE; ++columnIndex)
            {
                if (cipherGrid[rowIndex][columnIndex] == character)
                {
                    column = columnIndex;
                    row = rowIndex;
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Normalize input text and prepare digraph pairs for encryption.
     * 
     * Steps:
     * 1. Convert to uppercase and filter non-alphabetic characters
     * 2. Apply I/J or Q mapping based on configuration
     * 3. For encryption: insert padding between duplicate letters
     * 4. Ensure even length by appending padding character if needed
     *
     * @param inputText The raw input text
     * @param shouldMapItoJ Mapping configuration flag
     * @param isEncryption Whether this is for encryption (affects digraph formation)
     */
    void normalizeAndPrepareText(const std::string& inputText, bool shouldMapItoJ, bool isEncryption)
    {
        processedText.clear();
        processedText.reserve(inputText.size());

        // Normalize: convert to uppercase and filter valid letters
        for (char character : inputText)
        {
            unsigned char unsignedChar = static_cast<unsigned char>(character);
            char uppercaseChar = static_cast<char>(std::toupper(unsignedChar));
            
            if (uppercaseChar < PlayfairConstants::FIRST_LETTER || 
                uppercaseChar > PlayfairConstants::LAST_LETTER)
            {
                continue;
            }

            // Apply character mapping
            if (uppercaseChar == 'J' && shouldMapItoJ)
            {
                uppercaseChar = 'I';
            }
            else if (uppercaseChar == 'Q' && !shouldMapItoJ)
            {
                continue;
            }

            processedText.push_back(uppercaseChar);
        }

        // For encryption, handle duplicate letters in pairs
        if (isEncryption)
        {
            std::string digraphPairs;
            digraphPairs.reserve(processedText.size() + 1);
            
            for (size_t index = 0; index < processedText.size(); index += 2)
            {
                digraphPairs.push_back(processedText[index]);
                
                if (index + 1 < processedText.size())
                {
                    // Insert padding if duplicate letters found
                    if (processedText[index] == processedText[index + 1])
                    {
                        digraphPairs.push_back(PlayfairConstants::PADDING_CHAR);
                    }
                    digraphPairs.push_back(processedText[index + 1]);
                }
            }
            
            processedText.swap(digraphPairs);
        }

        // Ensure even length by padding if necessary
        if (processedText.length() % 2 == 1)
        {
            processedText.push_back(PlayfairConstants::PADDING_CHAR);
        }
    }

    /**
     * Build the 5x5 cipher grid from the encryption key.
     * 
     * Process:
     * 1. Use default key if provided key is empty
     * 2. Append full alphabet to key
     * 3. Extract unique characters in order
     * 4. Fill grid row by row
     *
     * @param encryptionKey The key string (may be empty)
     * @param shouldMapItoJ Mapping configuration flag
     */
    void buildCipherGrid(std::string encryptionKey, bool shouldMapItoJ)
    {
        if (encryptionKey.empty())
        {
            encryptionKey = PlayfairConstants::DEFAULT_KEY;
        }
        
        encryptionKey += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        std::string uniqueCharacters;
        uniqueCharacters.reserve(PlayfairConstants::GRID_TOTAL_CELLS);

        // Extract unique characters in order
        for (char& character : encryptionKey)
        {
            unsigned char unsignedChar = static_cast<unsigned char>(character);
            char uppercaseChar = static_cast<char>(std::toupper(unsignedChar));
            
            if (uppercaseChar < PlayfairConstants::FIRST_LETTER || 
                uppercaseChar > PlayfairConstants::LAST_LETTER)
            {
                continue;
            }

            // Skip characters based on mapping configuration
            if ((uppercaseChar == 'J' && shouldMapItoJ) || 
                (uppercaseChar == 'Q' && !shouldMapItoJ))
            {
                continue;
            }

            // Add if not already present
            if (uniqueCharacters.find(uppercaseChar) == std::string::npos)
            {
                uniqueCharacters.push_back(uppercaseChar);
            }
        }

        // Fill grid row by row
        for (size_t index = 0; index < PlayfairConstants::GRID_TOTAL_CELLS; ++index)
        {
            cipherGrid[index / PlayfairConstants::GRID_SIZE][index % PlayfairConstants::GRID_SIZE] = 
                uniqueCharacters[index];
        }
    }

    std::string processedText;
    std::array<std::array<char, PlayfairConstants::GRID_SIZE>, PlayfairConstants::GRID_SIZE> cipherGrid{};
};

/**
 * Get user input for encryption/decryption mode.
 *
 * @return True for encryption, false for decryption
 */
bool getUserMode()
{
    std::string modeChoice;
    std::cout << "(E)ncode or (D)ecode? ";
    std::getline(std::cin, modeChoice);
    
    if (!modeChoice.empty())
    {
        char firstChar = modeChoice[0];
        return (firstChar == 'e' || firstChar == 'E');
    }
    
    return false;
}

/**
 * Get user input for I/J mapping preference.
 *
 * @return True if J should be mapped to I, false if Q should be omitted
 */
bool getUserMappingPreference()
{
    std::string mappingChoice;
    std::cout << "I <-> J (Y/N): ";
    std::getline(std::cin, mappingChoice);
    
    if (!mappingChoice.empty())
    {
        char firstChar = mappingChoice[0];
        return (firstChar == 'y' || firstChar == 'Y');
    }
    
    return false;
}

/**
 * Main entry point for the Playfair cipher application.
 * Handles user interaction and orchestrates the encryption/decryption process.
 */
int main()
{
    bool isEncryption = getUserMode();
    
    std::string encryptionKey;
    std::cout << "Enter a en/decryption key: ";
    std::getline(std::cin, encryptionKey);
    
    bool shouldMapItoJ = getUserMappingPreference();
    
    std::string inputText;
    std::cout << "Enter the text: ";
    std::getline(std::cin, inputText);
    
    PlayfairCipher cipher;
    cipher.process(encryptionKey, inputText, shouldMapItoJ, isEncryption);
    
    // Pause for Windows users; portable behavior on other platforms
#ifdef _WIN32
    system("pause");
#else
    std::cout << "Press Enter to exit..." << std::endl;
    std::string dummy;
    std::getline(std::cin, dummy);
#endif
    
    return 0;
}
