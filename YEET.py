import time
import serial
import subprocess
import glob
import os
from scapy.all import rdpcap, Ether

# Configuration
serial_port = "COM6"  # Update to your Windows serial port
baud_rate = 115200
command = "10 1000\n"  # Example command to send
filter_ethertype = 0x8001  # Updated to the specified custom EtherType
capture_interface = "6"  # Update to the desired Npcap interface

# Connect to Serial Port
def send_command_to_serial(port, baudrate, cmd):
    with serial.Serial(port, baudrate, timeout=1) as ser:
        print(f"Sending command: {cmd.strip()}")
        ser.write(cmd.encode())
        time.sleep(2)  # Wait for the command to be processed

# Capture traffic using tshark
def capture_traffic(output_file, interface):
    print(f"Capturing traffic on interface {interface} to {output_file}...")
    # Use tshark to capture packets; this will also overwrite the existing file
    tshark_cmd = f"tshark -i {interface} -w {output_file} -F pcap"  # -F specifies the output format
    process = subprocess.Popen(tshark_cmd, shell=False)
    return process

# Get the most recent PCAP file created
def get_latest_pcap_file(directory):
    list_of_files = glob.glob(os.path.join(directory, '*.pcap'))
    if not list_of_files:
        return None
    latest_file = max(list_of_files, key=os.path.getmtime)
    return latest_file

# Read PCAP file and filter packets with the required EtherType
def read_pcap_and_filter(pcap_file, ether_type):
    packets_info = []
    packets = rdpcap(pcap_file)

    for index, packet in enumerate(packets):
        if Ether in packet and packet[Ether].type == ether_type:
            timestamp = packet.time
            packets_info.append((index, timestamp))
    
    return packets_info

def main():
    # Start capturing packets
    capture_file_pattern = "capture.pcap"  # Name of the PCAP file
    tshark_process = capture_traffic(capture_file_pattern, capture_interface)

    try:
        # Allow a moment for capture process to initialize
        time.sleep(2)

        # Send command to the Ethernet device
        send_command_to_serial(serial_port, baud_rate, command)

        # Monitor for a while to ensure all packets are captured
        print("Capture started. Waiting for packets...")
        time.sleep(10)  # Adjust timing to ensure enough time for packet arrival

    finally:
        # Get the PID of the running process to kill it using taskkill
        pid = tshark_process.pid
        print(f"Terminating tshark process with PID: {pid}")

        # Forcibly stop the packet capture using taskkill
        try:
            subprocess.call(f"taskkill /F /PID {pid}", shell=True)
        except Exception as e:
            print(f"An error occurred while trying to kill the process: {e}")

    # Get the latest PCAP file
    pcap_file = get_latest_pcap_file(os.getcwd())
    if pcap_file:
        print(f"Latest PCAP file: {pcap_file}")

        # Read and filter the PCAP file
        packets_data = read_pcap_and_filter(pcap_file, filter_ethertype)

        # Print the results
        print("Captured packets:")
        for packet_number, timestamp in packets_data:
            print(f"Packet Number: {packet_number}, Timestamp: {timestamp:.6f}")  # Display the timestamp with microseconds
    
    else:
        print("No PCAP files found.")

if __name__ == "__main__":
    main()