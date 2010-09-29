#!/usr/bin/python
debug = 0

def dMsg(msg):
	global debug
	if debug == 1:
		print msg

def setDbgOn():
	global debug
	debug = 1

def setDbgOff():
	global debug
	debug = 0
