# LSB Image Steganography in C

## Overview
This project implements Least Significant Bit (LSB) based image steganography
to hide a secret text message inside a BMP image using C.

## Concepts Used
- Bitwise operations
- Binary file handling
- LSB steganography
- Encoding and decoding logic

## How it works
- Each bit of secret data is stored in the LSB of an image byte
- Message length is stored first (32 bits)
- Decoding extracts length and reconstructs the message

## Author
Satwik M Kotian
