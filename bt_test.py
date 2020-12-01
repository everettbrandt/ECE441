import serial
import sys
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QMainWindow, QLabel, QGridLayout, QWidget
from PyQt5.QtWidgets import QPushButton

PORT = "COM5"
BAUDRATE = 9600
bluetooth=serial.Serial(PORT, BAUDRATE)

class MainWindow(QWidget):
    def __Init__(self):
        QMainWindow.__init__(self)

    def keyPressEvent(self, event):
        key_num = event.key()
        if key_num == 16777236:
            print("r")
            self.send_message('r')
        elif key_num == 16777234:
            print("l")
            self.send_message('l')
        elif key_num == 16777235:
            print("u")
            self.send_message('u')
        elif key_num == 16777237:
            print("d") 
            self.send_message('d')
        elif key_num == 32:
            print("space")
            self.send_message(" ")
        return
    
    def send_message(self, char):
        bluetooth.write(bytearray(str(char), 'utf-8'))
        print(bluetooth.read())
        return

if "__main__" == __name__:
    bluetooth.flushInput()
    app = QtWidgets.QApplication(sys.argv)
    mainWin = MainWindow()
    mainWin.show()
    sys.exit( app.exec_())
    bluetooth.close()