import serial
import time
import sys
import matplotlib.pyplot as plt

PORT = "COM5"
BAUDRATE = 9600

data = dict()
errors = dict()

def count_errors(message):
    errors = 0
    next = message[0]
    for i in range(0, len(message)):
        if next == message[i]:
            if message[i] == b'0':
                next = b'1'
            else:
                next = b'0'
        else:
            errors += 1
            next = message[i + 1]
    return errors

def test_delay(instring):
    inChar = -1
    message = list()
    delay_list = list()
    errors_list = list()

    print("here")
    #lets arduino know to start sending data
    bluetooth.write(bytearray('s', 'utf-8'))
    print("here")

    #Loop for all the messages
    while(inChar != b'd'):
        message.clear()
        inChar = -1
        
        #Time before receiving input
        start = time.perf_counter()

        #Loop for each message
        while(inChar != b'x' and inChar != b'd'):
            inChar = bluetooth.read()
            message.append(inChar)
        end = time.perf_counter()

        #Pop off the final stop byte
        message.pop()
        message_size = len(message)

        if(message_size != 0):
            err_count = count_errors(message)
            errors_list.append(err_count)
            delay_list.append(end - start)

        print("size", message_size, "error count", err_count, "delay", end - start)

    #Adds the delay string to the data global that's
    #used to make graphs
    data[instring] = delay_list
    errors[instring] = errors_list

def graph_delays():
    fig = plt.figure()
    ax1 = fig.add_subplot(111)

    #Add all datasets
    for obj in data:
        x = range(0, len(data[obj]))
        ax1.scatter(x, data[obj], s=10, marker="o", label=obj)

    ax1.set_title("Classic Bluetooth size of data transmitted vs delay")
    ax1.set_xlabel("Size of message (Bytes)")
    ax1.set_ylabel("Delay (sec)")
    
    plt.legend(loc='upper left');
    plt.show()

def graph_errors():
    fig = plt.figure()
    ax1 = fig.add_subplot(111)

    #Add all datasets
    for obj in errors:
        x = range(0, len(errors[obj]))
        ax1.scatter(x, errors[obj], s=10, marker="o", label=obj)

    ax1.set_title("Classic Bluetooth size of data transmitted vs errors")
    ax1.set_xlabel("Size of message (Bytes)")
    ax1.set_ylabel("Total Errors")
    
    plt.legend(loc='upper left');
    plt.show()

if "__main__" == __name__:
    bluetooth=serial.Serial(port=PORT, baudrate=BAUDRATE)
    bluetooth.flushInput()
    
    while(True):
        
        print(">> Enter name of set (x to exit and see graph) >> ", end="")
        instring = input()

        if(instring == "x"):
            bluetooth.close()
            graph_delays()
            graph_errors()
            sys.exit(0)
        else:
            test_delay(instring)
