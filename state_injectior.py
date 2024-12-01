from serial_handler import SerialHandler
import time

serial_handler = SerialHandler(port='COM3', baudrate=9600)
serial_handler.connect()

try:
    while True:
    
    # Send a command to Arduino
    serial_handler.send_msg("EMPTY")

    time.sleep(0.5)

    # Read messages from Arduino
    messages = serial_handler.read_update()
    for message in messages:
        print(f"Received: {message}")

        time.sleep(1.0)
finally:
    # Close connection when done
    serial_handler.close()
