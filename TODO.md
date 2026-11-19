# Key Generation:
- Creates an RSA key pair (public/private keys)
- Generates random AES keys for each password

# Security to Add:
- Error handling, secure memory wiping, and key storage protection
- The protect the RSA private key with a *master password*
- Consider adding salt and key derivation functions for the *master password*
- Add integrity checks to detect tampering

# Recall/To-Implement
## Encryption Process:
- Each password gets its own AES key (for better security)
- The password is encrypted using AES-256 (fast and secure)
- The AES key is then encrypted using RSA (this is called key wrapping)
- Everything is packaged together in a single payload

## Decryption Process:
- The RSA private key decrypts the AES key
- The decrypted AES key is then used to decrypt the password
- Padding is removed to get the original password
