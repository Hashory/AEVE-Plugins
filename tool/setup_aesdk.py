import argparse
import os
import shutil
import subprocess
import sys
import zipfile
import boto3
from botocore.exceptions import ClientError

# --- Configuration ---
# Hardcoded SDK version as per user request
SDK_VERSION = "25.2_20"

def parse_args():
    """Parses command-line arguments."""
    parser = argparse.ArgumentParser(
        description="Download and set up the Adobe After Effects SDK from an S3-compatible endpoint."
    )
    parser.add_argument(
        "--endpoint-url",
        required=True,
        help="The endpoint URL for the S3 service."
    )
    parser.add_argument(
        "--access-key-id",
        required=True,
        help="The AWS Access Key ID for S3 authentication."
    )
    parser.add_argument(
        "--secret-access-key",
        required=True,
        help="The AWS Secret Access Key for S3 authentication."
    )
    return parser.parse_args()

def download_from_s3(args, bucket_name, s3_key, local_path):
    """Downloads a file from S3 using credentials."""
    print(f"Attempting to download s3://{bucket_name}/{s3_key} to {local_path}...")
    try:
        s3 = boto3.client(
            's3',
            endpoint_url=args.endpoint_url,
            aws_access_key_id=args.access_key_id,
            aws_secret_access_key=args.secret_access_key
        )
        s3.download_file(bucket_name, s3_key, local_path)
        print("Download successful.")
        return True
    except ClientError as e:
        print(f"Error: Failed to download file from S3. {e}")
        return False
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        return False

def extract_and_setup_sdk(zip_path, unzip_dir, post_extract_script, dest_sdk_path):
    """Extracts the SDK, runs the post-extraction script, and moves files."""
    print(f"--- Starting extraction and setup for {zip_path} ---")

    # 1. Extract the zip file
    print(f"Extracting {zip_path} to {unzip_dir}...")
    try:
        with zipfile.ZipFile(zip_path, 'r') as zip_ref:
            zip_ref.extractall(unzip_dir)
        print("Extraction complete.")
    except Exception as e:
        print(f"Error: Failed to extract zip file. {e}")
        return False

    # 2. Run the post-extraction script
    # The path structure is based on the original YAML files
    script_dir = os.path.join(unzip_dir, f"ae{SDK_VERSION}.64bit.AfterEffectsSDK")
    script_path = os.path.join(script_dir, post_extract_script)

    print(f"Looking for post-extraction script at: {script_path}")
    if not os.path.exists(script_path):
        print(f"Error: Post-extraction script not found at {script_path}")
        return False

    print(f"Executing {post_extract_script}...")
    try:
        if sys.platform != "win32":  # On macOS/Linux
            # Add execute permissions
            os.chmod(script_path, 0o755)
            # Execute shell script
            subprocess.run(["./" + post_extract_script], check=True, cwd=script_dir)
        else: # On Windows
            # Execute batch script
            subprocess.run([script_path], check=True, cwd=script_dir, shell=True)

        print("Post-extraction script executed successfully.")
    except (subprocess.CalledProcessError, FileNotFoundError) as e:
        print(f"Error: Failed to execute post-extraction script. {e}")
        return False

    # 3. Copy example files to destination
    source_examples_path = os.path.join(script_dir, "AfterEffectsSDK", "Examples")
    print(f"Copying examples from {source_examples_path} to {dest_sdk_path}...")
    try:
        # Ensure destination exists
        os.makedirs(dest_sdk_path, exist_ok=True)
        # Copy contents of source to destination
        shutil.copytree(source_examples_path, dest_sdk_path, dirs_exist_ok=True)
        print("SDK Examples copied successfully.")
    except Exception as e:
        print(f"Error: Failed to copy SDK examples. {e}")
        return False

    print("--- SDK setup process completed successfully! ---")
    return True

def main():
    """
    Main function to orchestrate the download, extraction, and setup of the AE SDK.
    """
    args = parse_args()
    print("--- Starting After Effects SDK setup ---")
    print(f"SDK Version: {SDK_VERSION}")

    # Determine OS-specific filenames and scripts
    if sys.platform == "darwin":
        platform_name = "mac"
        post_extract_script = "extractzstd.sh"
    elif sys.platform == "win32":
        platform_name = "win"
        post_extract_script = "extractzstd.bat"
    else:
        print(f"Error: Unsupported platform '{sys.platform}'. This script supports 'darwin' (macOS) and 'win32' (Windows).")
        sys.exit(1)

    zip_filename = f"AfterEffectsSDK_{SDK_VERSION}_{platform_name}.zip"
    unzip_dir = f"AfterEffectsSDK_{SDK_VERSION}_{platform_name}"

    print(f"Detected Platform: {sys.platform} ({platform_name})")
    print(f"Target SDK zip file: {zip_filename}")
    print(f"Post-extraction script: {post_extract_script}")

    s3_bucket = "ae-sdk"
    local_zip_path = zip_filename  # Download to current directory

    if not download_from_s3(args, s3_bucket, zip_filename, local_zip_path):
        sys.exit(1)

    dest_sdk_path = "AfterEffectsSDK"
    if not extract_and_setup_sdk(local_zip_path, unzip_dir, post_extract_script, dest_sdk_path):
        sys.exit(1)


if __name__ == "__main__":
    main()
