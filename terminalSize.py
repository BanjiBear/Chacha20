# CHEN Yi pu
# 19084858d
# Assignment 1 Question 5


"""
	This file is embedded into the main C prorgam and simply to resize the terminal window
"""

import time
import sys
import os

sys.stdout.write("\x1b[8;{rows};{cols}t".format(rows = 100, cols = 150))