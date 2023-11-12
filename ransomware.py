def encrypt_file(input_file, output_file, key):
    with open(input_file, 'rb') as file_in, open(output_file, 'wb') as file_out:
        key_index = 0
        while True:
            byte = file_in.read(1)
            if not byte:
                break
            encrypted_byte = bytes([byte[0] ^ ord(key[key_index % len(key)])])  # XOR operation with the key
            file_out.write(encrypted_byte)
            key_index += 1

    print("File encrypted successfully!")

def decrypt_file(input_file, output_file, key):
    with open(input_file, 'rb') as file_in, open(output_file, 'wb') as file_out:
        key_index = 0
        while True:
            byte = file_in.read(1)
            if not byte:
                break
            encrypted_byte = bytes([byte[0] ^ ord(key[key_index % len(key)])])  # XOR operation with the key
            file_out.write(encrypted_byte)
            key_index += 1
        print("File decrypted successfully!")


input_file_name = 'test_encrypted.txt'  # Replace this with your input file name
output_file_name = 'test_decrypted.txt'  # Replace this with your output file name
encryption_key = 'MySecretKey'  # Replace this with your encryption key

decrypt_file(input_file_name, output_file_name, encryption_key)
