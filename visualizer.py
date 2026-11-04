import subprocess
import time
import re

layers = [
    "Application",
    "Presentation",
    "Session",
    "Transport",
    "Network",
    "Data Link",
    "Physical"
]

print("Starting C server...")
server = subprocess.Popen(
    ["./server"],
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT,
    text=True
)

# Give the server a moment to start listening
time.sleep(1)

print("Running C client...\n")
client = subprocess.run(
    ["./client"],
    capture_output=True,
    text=True
)

# The client connects to the server and sends the message
server_output, _ = server.communicate(timeout=10)

print("=== C CLIENT OUTPUT ===")
print(client.stdout)

print("=== C SERVER OUTPUT ===")
print(server_output)

# Find the original message delivered to the server application
match = re.search(
    r"\[Application \(RX\)\] Data: (.*)",
    server_output
)

if match:
    received_message = match.group(1)

    print("\n=== PYTHON VISUALIZER: ACTUAL SOCKET MESSAGE ===")
    print("Message received:", received_message)

    print("\nSender: encapsulation")
    for i, layer in enumerate(layers, start=1):
        print(f"  {layer:15} ↓")
        if i % 2 == 0:
            print(f"  Progress: {i}/7 layers completed\n")

    print("        ===== TCP SOCKET =====\n")

    print("Receiver: decapsulation")
    for i, layer in enumerate(reversed(layers), start=1):
        print(f"  ↑ {layer:15}")
        if i % 2 == 0:
            print(f"  Progress: {i}/7 layers completed\n")

    print("\nMessage delivered:", received_message)
else:
    print("Could not find the received application message.")
    print("Check the C server output above.")
